#include <stdio.h>
#include "main.h"

static const int participants[] = {
    42, 17, 68, 9, 23, 55, 81, 4, 13, 20, 31, 49, 61, 75, 90, 2, 7, 11, 15,
    19, 21, 27, 35, 45, 52, 58, 64, 72, 78, 85, 95, 1, 3, 5, 6, 8, 10, 12,
    14, 16, 18, 22, 24, 26, 29, 33, 37, 41, 44, 47, 50, 54, 57, 60, 63, 66,
    70, 74, 77, 80, 83, 87, 92, 97, 25, 28, 30, 34, 39
};

static void query_node(node *root)
{
    int id;
    printf("Enter participant identifier: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    node *n = search(root, id);
    if (n == NULL) {
        printf("Participant %d does not exist in the tournament tree.\n", id);
        return;
    }

    node *parent = find_parent(root, id);
    if (parent == NULL) {
        printf("Parent: none (%d is the root)\n", id);
        printf("Sibling: none\n");
    } else {
        printf("Parent: %d\n", parent->id);
        node *sibling = (parent->left == n) ? parent->right : parent->left;
        if (sibling)
            printf("Sibling: %d\n", sibling->id);
        else
            printf("Sibling: none\n");
    }

    if (n->left == NULL && n->right == NULL)
        printf("%d is a leaf (no children).\n", id);
    print_grandchildren(n);
}

int main(void)
{
    int n = sizeof participants / sizeof participants[0];
    node *root = build_tree(participants, n);
    int choice;

    printf("Tournament tree built from %d participants.\n", n);
    do {
        printf("\n1. Display root\n2. Display leaves\n3. Query a participant\n0. Exit\n> ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (choice) {
        case 1: printf("Root: %d\n", root->id); break;
        case 2: printf("Leaves: "); print_leaves(root); printf("\n"); break;
        case 3: query_node(root); break;
        case 0: break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free_tree(root);
    printf("Exiting. Memory freed.\n");
    return 0;
}
