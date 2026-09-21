#include <stdio.h>
#include <stdlib.h>
#include "main.h"

node *create_node(int id)
{
    node *n = malloc(sizeof(node));
    if (n == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(1);
    }
    n->id = id;
    n->left = n->right = NULL;
    return n;
}

/*
 * Construction rule (binary search tree insertion):
 *   - the first identifier in the array becomes the root
 *   - each following identifier is compared from the root downwards:
 *       smaller than the current node -> go left
 *       larger  than the current node -> go right
 *     until an empty spot is found, where the new node is attached
 *   - duplicates are ignored
 */
node *insert(node *root, int id)
{
    if (root == NULL)
        return create_node(id);
    if (id < root->id)
        root->left = insert(root->left, id);
    else if (id > root->id)
        root->right = insert(root->right, id);
    return root;
}

node *build_tree(const int *ids, int n)
{
    node *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, ids[i]);
    return root;
}

node *search(node *root, int id)
{
    while (root != NULL && root->id != id)
        root = (id < root->id) ? root->left : root->right;
    return root;
}

/* returns NULL for the root or a non-existent id */
node *find_parent(node *root, int id)
{
    node *parent = NULL;
    while (root != NULL && root->id != id) {
        parent = root;
        root = (id < root->id) ? root->left : root->right;
    }
    return (root == NULL) ? NULL : parent;
}

/* in-order traversal, printing only nodes with no children */
void print_leaves(const node *root)
{
    if (root == NULL)
        return;
    print_leaves(root->left);
    if (root->left == NULL && root->right == NULL)
        printf("%d ", root->id);
    print_leaves(root->right);
}

static int print_children(const node *n)
{
    int count = 0;
    if (n == NULL)
        return 0;
    if (n->left)  { printf("%d ", n->left->id);  count++; }
    if (n->right) { printf("%d ", n->right->id); count++; }
    return count;
}

void print_grandchildren(const node *n)
{
    printf("Grandchildren: ");
    int count = print_children(n->left) + print_children(n->right);
    if (count == 0)
        printf("none");
    printf("\n");
}

void free_tree(node *root)
{
    if (root == NULL)
        return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
