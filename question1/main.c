#include <stdio.h>
#include <string.h>
#include "main.h"

int main(void)
{
    order orders[MAX_ORDERS];
    char buffer[MAX_LINE];
    int count = 0;
    long long total_value = 0;

    /* 1. Read orders.txt into the array */
    FILE *fp = fopen("orders.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open orders.txt\n");
        return 1;
    }

    while (fgets(buffer, sizeof buffer, fp) != NULL) {
        if (count >= MAX_ORDERS) {
            fprintf(stderr, "Warning: more than %d orders, ignoring the rest\n", MAX_ORDERS);
            break;
        }

        order *o = &orders[count];
        int fields = sscanf(buffer, "%31s %63s %63s %lld",
                            o->order_id, o->customer_name,
                            o->product_category, &o->order_value);

        /* skip blank or malformed lines */
        if (fields != 4)
            continue;

        total_value += o->order_value;
        count++;
    }
    fclose(fp);

    /* 2. Sort by warehouse priority */
    quick_sort(orders, 0, count - 1);

    /* 3. Write sorted orders in the same format */
    FILE *out = fopen("priority_orders.txt", "w");
    if (out == NULL) {
        fprintf(stderr, "Error: could not create priority_orders.txt\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        fprintf(out, "%s %s %s %lld\n",
                orders[i].order_id, orders[i].customer_name,
                orders[i].product_category, orders[i].order_value);
    }
    fclose(out);

    /* 4. Summary */
    printf("Orders processed: %d\n", count);
    printf("Total order value: %lld RWF\n", total_value);

    return 0;
}
