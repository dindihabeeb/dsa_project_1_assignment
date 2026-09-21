# Time Complexity Analysis

## Inserting a new sample at the end (n samples in the list)

My implementation keeps a `tail` pointer in the `queue` struct alongside
`head`. `insert_end()` therefore does a fixed number of steps no matter how
long the list is:

```c
node->prev = q->tail;      // 1. link new node back to old tail
q->tail->next = node;      // 2. link old tail forward to new node
q->tail = node;            // 3. move tail
```

Three pointer assignments (plus a NULL check for the empty case). None of
them depend on `n`, so insertion at the end is **O(1)**.

### Without a tail pointer

If only `head` were stored, the function would first have to walk to the
last node:

```c
sample *s = q->head;
while (s->next != NULL)    // n - 1 steps
    s = s->next;
s->next = node;
node->prev = s;
```

The walk visits `n - 1` nodes, so insertion would be **O(n)**. On a busy
day with `n` samples already queued, every new arrival would cost `n`
steps, and adding `m` samples in a row would cost O(n·m) — roughly O(n²)
if the queue grows from empty. Maintaining the tail pointer is what keeps
the "add sample while running" operation constant-time regardless of how
much the workload grows, at the cost of one extra pointer and one extra
assignment per insert.

## Traversing all n samples in either direction

`review_forward()` starts at `head` and follows `next` until it hits
`NULL`; `review_backward()` starts at `tail` and follows `prev`. Each
visits every node exactly once and does constant work per node, so both
directions are **O(n)**. The doubly linked list makes the backward
traversal just as cheap as the forward one — with a singly linked list
going backwards would require either O(n) extra memory (a stack) or O(n²)
time (re-walking from the head for each step).

## Summary

| Operation                | Complexity | Reason                          |
|--------------------------|------------|---------------------------------|
| Insert at end (with tail)| O(1)       | constant pointer updates        |
| Insert at end (no tail)  | O(n)       | must walk to the last node      |
| Traverse forward         | O(n)       | one visit per node via `next`   |
| Traverse backward        | O(n)       | one visit per node via `prev`   |
| Move next / previous     | O(1)       | follow one pointer              |
