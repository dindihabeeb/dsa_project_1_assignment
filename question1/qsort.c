#include <stdio.h>
#include <string.h>
#include "main.h"

/*
 * Warehouse priority rule. Returns:
 *   < 0  if a should come BEFORE b
 *   > 0  if a should come AFTER b
 *   0    if they are identical on all three keys
 *
 * 1. order_value     descending
 * 2. customer_name   ascending
 * 3. order_id        ascending
 */
int compare_orders(const order *a, const order *b)
{
    if (a->order_value != b->order_value)
        return (a->order_value > b->order_value) ? -1 : 1;

    int name_cmp = strcmp(a->customer_name, b->customer_name);
    if (name_cmp != 0)
        return name_cmp;

    return strcmp(a->order_id, b->order_id);
}

//for swapping two orders
static void swap(order *a, order *b)
{
    order temp = *a;
    *a = *b;
    *b = temp;
}


int partition(order *arr, int start, int end)
{
    order pivot = arr[end];
    int pIndex = start;

    for (int i = start; i < end; i++) {
        if (compare_orders(&arr[i], &pivot) <= 0) {
            swap(&arr[i], &arr[pIndex]);
            pIndex++;
        }
    }
    swap(&arr[pIndex], &arr[end]);
    return pIndex;
}

void quick_sort(order *arr, int start, int end)
{
    if (start < end) {
        int pIndex = partition(arr, start, end);
        quick_sort(arr, start, pIndex - 1);
        quick_sort(arr, pIndex + 1, end);
    }
}
