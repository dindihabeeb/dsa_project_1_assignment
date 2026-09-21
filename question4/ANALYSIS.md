# Question 4 — BST Search Complexity and Conceptual Analysis

## 1. Implementation notes

- `file.c` reads `inventory.txt` line by line with `fgets`, splits on `|`,
  and rejects records with a missing/extra field, empty code or name, or a
  quantity/price that is not a non-negative integer. Blank lines are
  skipped and every rejected line is reported with its line number.
- `bst.c` keeps the tree ordered by `strcmp` on the medicine code. A
  duplicate code adds the new quantity to the existing node instead of
  creating a second node.
- The tree is built once; the menu then allows any number of searches and
  in-order listings before the tree is freed on exit.

## 2. Time complexity of searching (n nodes)

`search()` starts at the root and, at each node, compares the target code
and moves to one child. It never revisits a node, so the number of
comparisons is at most the depth of the node found (or the height `h` of
the tree for a miss):

```
T_search(n) = O(h)
```

### Best case — O(1)

The medicine is at the root: one comparison.

### Average case — O(log n)

If codes are inserted in random order the tree is reasonably balanced and
its expected height is about `2 ln n ≈ 1.39 log₂ n`. Each comparison
discards roughly half the remaining tree, so a search costs
**O(log n)** — for 40 medicines about 6 comparisons, for 1,000,000 about 20.

### Worst case — O(n)

If the codes arrive already sorted (as they do in the given file:
M1001, M1002, ..., M1040) every insert goes to the right child and the
tree degenerates into a linked list of height `n - 1`. A search for the
last code, or for a missing code larger than all of them, visits every
node: **O(n)** — no better than scanning the file.

### How the shape of the tree matters

The cost is really O(h), and `h` ranges from `log₂ n` (perfectly
balanced) to `n - 1` (fully skewed). The shape is determined entirely by
insertion order, not by the data itself. A self-balancing BST (AVL or
red-black) would guarantee `h = O(log n)` for any insertion order; a plain
BST like this one relies on the input not being sorted.

| Shape             | Height     | Search   |
|-------------------|------------|----------|
| Balanced          | log₂ n     | O(log n) |
| Random order      | ≈1.39 log₂ n | O(log n) |
| Skewed (sorted in)| n - 1      | O(n)     |

## 3. Binary Tree vs Binary Search Tree

A **binary tree** is any tree in which each node has at most two children
(left and right). There is no rule about which values go where; it is just
a shape. Finding a value in a general binary tree requires visiting every
node in the worst case — O(n).

A **binary search tree** is a binary tree with an extra ordering property:
for every node, all keys in its left subtree are smaller and all keys in
its right subtree are larger. That property is what lets a search discard
a whole subtree at each step, giving O(h) instead of O(n). It also means
an in-order traversal (left, node, right) visits the keys in ascending
order — which is how the inventory listing is produced.

## 4. Linear file search vs BST search

### Linear search through the file

Each search opens the file and reads records one by one until the code
matches or the file ends:

- Cost per search: **O(n)** record reads, and these are disk reads — much
  slower than memory accesses.
- No setup cost.
- `k` searches cost **O(k · n)**.

### BST search after loading into memory

- One-time construction: reading `n` records is O(n), and inserting each
  is O(h), so building the tree is **O(n log n)** for a balanced tree
  (O(n²) in the skewed worst case).
- Cost per search: **O(log n)** memory comparisons for a balanced tree.
- `k` searches cost **O(n log n + k log n)**.

### When does the BST win?

The BST is only worth building if the searches it speeds up outweigh the
construction cost. Comparing totals:

```
linear:  k · n
BST:     n log n + k · log n
```

For a single search (`k = 1`) the linear scan is cheaper — it reads the
file once, whereas the BST reads the file once *and* builds the tree.
Break-even is roughly when `k · n ≈ n log n`, i.e. **`k ≈ log n`**
searches. For the 40-medicine file that is about 6 searches; for 100,000
medicines about 17. Beyond that, every extra search costs `log n` with the
BST versus `n` with the file, so the gap widens rapidly.

In a pharmacy the inventory is loaded once in the morning and queried
hundreds or thousands of times during the day, so `k ≫ log n` and the BST
approach is clearly the better choice. The same is true of the in-order
listing: it is O(n) from the tree, while producing a sorted list from the
raw file would need a full sort first.

The one caveat is the skewed case: because the file is sorted by code,
this plain BST actually builds a degenerate O(n)-height tree. To get the
promised O(log n) searches in practice, either insert in a shuffled order
or use a self-balancing BST.
