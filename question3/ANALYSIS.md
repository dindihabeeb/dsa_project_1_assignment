# Tree Construction Rule and Insertion Complexity

## Construction rule

The tree is built by inserting the identifiers one at a time, in array
order, using the **binary search tree rule**:

- The first identifier (42) becomes the root.
- Each later identifier starts at the root and walks down: if it is
  smaller than the current node it goes left, if larger it goes right,
  until it reaches an empty child slot, where a new node is attached.
- Duplicates are ignored (none occur in the given array).

The given array is already in level order of a balanced tree (42, then
17/68, then 9/23/55/81, ...), so inserting in that order produces a
well-balanced tree of height 7 for the 69 identifiers.

Note: the brief says 68 identifiers but lists 69; the program uses the
array exactly as given.

## Time complexity of inserting a new node (n nodes in the tree)

`insert()` does one comparison per level as it walks from the root to the
empty slot, then one `malloc` and one pointer assignment. The work is
therefore proportional to the **height h** of the tree:

```
T(n) = O(h)
```

How `h` relates to `n` depends on the tree's shape.

### Balanced tree — best case

When every level is full (or nearly), each step halves the remaining
subtree, so `h = ⌊log₂ n⌋`. Insertion is **O(log n)**. This is the case
for the given data: 69 nodes, height 7 ≈ log₂ 69.

### Skewed tree — worst case

If identifiers arrive already sorted (e.g. 1, 2, 3, ...), every new node
goes right of the previous one and the tree degenerates into a linked
list with `h = n - 1`. Insertion must walk past every existing node, so it
is **O(n)**.

### Average case

For identifiers inserted in random order the expected height is about
`2 ln n ≈ 1.39 log₂ n`, so insertion is **O(log n)** on average.

| Tree shape          | Height h   | Insert complexity |
|---------------------|------------|-------------------|
| Balanced            | log₂ n     | O(log n)          |
| Random insert order | ≈1.39 log₂ n | O(log n)        |
| Skewed (sorted in)  | n - 1      | O(n)              |

## Other operations

`search()` and `find_parent()` follow the same root-to-node path, so they
are also O(h). `print_leaves()` and `free_tree()` visit every node once,
so they are O(n) regardless of shape.

## Implication for the tournament

As long as new participants arrive in an order that keeps the tree
roughly balanced, adding one costs O(log n) — a few dozen comparisons even
for thousands of participants. If the identifiers were allocated
sequentially (increasing ids), the plain BST rule would degrade to O(n)
per insert; a self-balancing variant (AVL / red-black) would be needed to
guarantee O(log n).
