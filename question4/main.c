#include <stdio.h>
#include "main.h"

int main(int argc, char *argv[])
{
    const char *filename = (argc > 1) ? argv[1] : "inventory.txt";
    int loaded, skipped;

    medicine *root = load_inventory(filename, &loaded, &skipped);
    if (root == NULL) {
        printf("No valid records loaded from %s. Nothing to search.\n", filename);
        return 1;
    }
    printf("Loaded %d records (%d skipped) from %s\n", loaded, skipped, filename);

    int choice;
    char code[16];
    do {
        printf("\n1. Search by medicine code\n2. Display inventory (in-order)\n0. Exit\n> ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
        case 1:
            printf("Medicine code: ");
            if (scanf("%15s", code) != 1) break;
            medicine *m = search(root, code);
            if (m == NULL) {
                printf("Medicine %s not found.\n", code);
            } else {
                printf("Code:       %s\nName:       %s\nQuantity:   %d\nUnit price: %d\n",
                       m->code, m->name, m->quantity, m->unit_price);
            }
            break;
        case 2:
            printf("%-6s %-34s %5s %6s\n", "Code", "Name", "Qty", "Price");
            inorder(root);
            break;
        case 0:
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free_tree(root);
    printf("Exiting. Memory freed.\n");
    return 0;
}
