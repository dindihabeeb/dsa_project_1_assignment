#ifndef MAIN_H
#define MAIN_H

typedef struct node {
    int id;
    struct node *left;
    struct node *right;
} node;

/* tree.c */
node *create_node(int id);
node *insert(node *root, int id);
node *build_tree(const int *ids, int n);
node *search(node *root, int id);
node *find_parent(node *root, int id);
void print_leaves(const node *root);
void print_grandchildren(const node *n);
void free_tree(node *root);

#endif
