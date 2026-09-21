Quick Sort Analysis

## Running time

`partition()` loops over the sub-array once, so it does `cn` work for `n`
elements. Quick Sort then recurses on the two sides of the pivot:

```
T(n) = T(left size) + T(right size) + cn
```

**Best case** — the pivot lands in the middle every time, so both sides
are `n/2`:

```
T(n) = 2T(n/2) + cn
```

Each level of recursion does `cn` work in total and the array halves each
level, so there are `log₂ n` levels:

```
T(n) = cn log₂ n   →   O(n log n)
```

**Worst case** — the pivot is always the largest or smallest element (this
happens with a last-element pivot when the input is already sorted). One
side is empty and the other has `n - 1`:

```
T(n) = T(n - 1) + cn
     = cn + c(n-1) + c(n-2) + ... + c
     = c · n(n+1)/2   →   O(n²)
```

**Average case** — on random input the pivot splits the array unevenly but
not extremely, e.g. 1/4 – 3/4. Even an uneven split still shrinks the
array by a constant fraction each level, so the depth is still
logarithmic and each level still costs `cn`:

```
T(n) ≈ T(n/4) + T(3n/4) + cn   →   O(n log n)
```

| Case    | Recurrence              | Big-O      |
|---------|-------------------------|------------|
| Best    | `T(n) = 2T(n/2) + cn`   | O(n log n) |
| Average | uneven but proportional split | O(n log n) |
| Worst   | `T(n) = T(n-1) + cn`    | O(n²)      |

## Auxiliary space

The sort is in-place: `partition()` only uses a temporary `order` for the
pivot and swaps, so O(1) per call. The extra memory comes from the
recursion stack, one frame per active `quick_sort()` call:

- Best/average: depth `log₂ n` → **O(log n)**
- Worst: depth `n` → **O(n)**

## Why Quick Sort over Insertion Sort

- **Dataset size.** Insertion Sort is O(n²) on average; Quick Sort is
  O(n log n). For 100 orders the difference is small. For 1,000,000
  orders Insertion Sort does ~10¹² operations versus ~2 × 10⁷ for Quick
  Sort — the difference between hours and under a second.

- **Expected running time.** The export file is in arrival order, not
  value order, so the input is effectively random. That is Quick Sort's
  O(n log n) average case and Insertion Sort's O(n²) average case.

- **Scalability.** Doubling the number of orders multiplies Insertion
  Sort's time by 4 but Quick Sort's by only ~2. As the company grows Quick
  Sort keeps up; Insertion Sort falls behind fast.

- **Best / average / worst case.**

  | Case    | Insertion Sort | Quick Sort |
  |---------|----------------|------------|
  | Best    | O(n) (already sorted) | O(n log n) |
  | Average | O(n²)          | O(n log n) |
  | Worst   | O(n²)          | O(n²) (already sorted, last-element pivot) |

  Insertion Sort's only win is its O(n) best case, which needs the input
  to be nearly sorted already — not true for a daily export sorted by a
  three-level key nobody upstream produces. Quick Sort's O(n²) worst case
  is rare on real data and can be avoided with a random or
  median-of-three pivot.

- **Data comes from a file.** Reading the file is O(n) either way and
  the whole batch is available before sorting starts, so nothing favours
  an "online" algorithm like Insertion Sort. Once the data is in an array,
  Quick Sort has the random access it needs and sorts in place, so no
  second copy of the data is required.

Quick Sort is the better choice because its average cost grows almost
linearly with the number of orders, whereas Insertion Sort's grows
quadratically.
