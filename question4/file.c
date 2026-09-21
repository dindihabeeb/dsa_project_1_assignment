#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/* returns 1 and stores the value if s is a non-negative integer */
static int parse_int(const char *s, int *out)
{
    char *end;
    if (s == NULL || *s == '\0')
        return 0;
    long v = strtol(s, &end, 10);
    if (*end != '\0' || v < 0 || v > 1000000000)
        return 0;
    *out = (int)v;
    return 1;
}

/* splits "code|name|qty|price"; returns 1 if the record is valid */
static int parse_record(char *line, char **code, char **name, int *qty, int *price)
{
    line[strcspn(line, "\r\n")] = '\0';

    *code = strtok(line, "|");
    *name = strtok(NULL, "|");
    char *qty_s = strtok(NULL, "|");
    char *price_s = strtok(NULL, "|");
    char *extra = strtok(NULL, "|");

    if (*code == NULL || *name == NULL || qty_s == NULL || price_s == NULL || extra != NULL)
        return 0;
    if (strlen(*code) == 0 || strlen(*name) == 0)
        return 0;
    return parse_int(qty_s, qty) && parse_int(price_s, price);
}

medicine *load_inventory(const char *filename, int *loaded, int *skipped)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open %s\n", filename);
        return NULL;
    }

    medicine *root = NULL;
    char line[MAX_LINE];
    int line_no = 0;
    *loaded = *skipped = 0;

    while (fgets(line, sizeof line, fp) != NULL) {
        line_no++;
        if (line[0] == '\n' || line[0] == '\r')
            continue;

        char *code, *name;
        int qty, price;
        if (!parse_record(line, &code, &name, &qty, &price)) {
            fprintf(stderr, "Skipping malformed record on line %d\n", line_no);
            (*skipped)++;
            continue;
        }
        root = insert(root, code, name, qty, price);
        (*loaded)++;
    }
    fclose(fp);
    return root;
}
