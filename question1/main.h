#ifndef MAIN_H
#define MAIN_H

#define MAX_ORDERS 1000
#define MAX_LINE 256

/* One line of orders.txt: OrderID CustomerName ProductCategory OrderValue */
typedef struct {
    char order_id[32];
    char customer_name[64];
    char product_category[64];
    long long order_value; /* RWF - totals overflow a plain int */
} order;


int compare_orders(const order *a, const order *b);

void quick_sort(order *arr, int start, int end);
int partition(order *arr, int start, int end);

#endif
