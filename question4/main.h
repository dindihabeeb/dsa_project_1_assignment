#ifndef MAIN_H
#define MAIN_H

#define MAX_LINE 256

typedef struct medicine {
    char code[16];
    char name[64];
    int quantity;
    int unit_price;
    struct medicine *left;
    struct medicine *right;
} medicine;

/* bst.c */
medicine *create_node(const char *code, const char *name, int qty, int price);
medicine *insert(medicine *root, const char *code, const char *name, int qty, int price);
medicine *search(medicine *root, const char *code);
void inorder(const medicine *root);
void free_tree(medicine *root);

/* file.c */
medicine *load_inventory(const char *filename, int *loaded, int *skipped);

#endif
