#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

medicine *create_node(const char *code, const char *name, int qty, int price)
{
    medicine *m = malloc(sizeof(medicine));
    if (m == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(1);
    }
    strncpy(m->code, code, sizeof m->code - 1);
    m->code[sizeof m->code - 1] = '\0';
    strncpy(m->name, name, sizeof m->name - 1);
    m->name[sizeof m->name - 1] = '\0';
    m->quantity = qty;
    m->unit_price = price;
    m->left = m->right = NULL;
    return m;
}

/* BST keyed on code; a duplicate code adds to the existing quantity */
medicine *insert(medicine *root, const char *code, const char *name, int qty, int price)
{
    if (root == NULL)
        return create_node(code, name, qty, price);

    int cmp = strcmp(code, root->code);
    if (cmp < 0)
        root->left = insert(root->left, code, name, qty, price);
    else if (cmp > 0)
        root->right = insert(root->right, code, name, qty, price);
    else {
        root->quantity += qty;
        printf("Duplicate code %s: quantity updated to %d\n", code, root->quantity);
    }
    return root;
}

medicine *search(medicine *root, const char *code)
{
    while (root != NULL) {
        int cmp = strcmp(code, root->code);
        if (cmp == 0)
            return root;
        root = (cmp < 0) ? root->left : root->right;
    }
    return NULL;
}

void inorder(const medicine *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%-6s %-34s %5d %6d\n", root->code, root->name, root->quantity, root->unit_price);
    inorder(root->right);
}

void free_tree(medicine *root)
{
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
