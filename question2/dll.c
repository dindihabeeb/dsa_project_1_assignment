#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

static void print_sample(const sample *s)
{
    printf("  ID: %-10s Type: %-12s Priority: %d\n", s->id, s->type, s->priority);
}

sample *create_node(const char *id, const char *type, int priority)
{
    sample *node = malloc(sizeof(sample));
    if (node == NULL) {
        fprintf(stderr, "Error: out of memory\n");
        exit(1);
    }
    strncpy(node->id, id, sizeof node->id - 1);
    node->id[sizeof node->id - 1] = '\0';
    strncpy(node->type, type, sizeof node->type - 1);
    node->type[sizeof node->type - 1] = '\0';
    node->priority = priority;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

/* O(1) because we keep a tail pointer */
void insert_end(queue *q, sample *node)
{
    if (q->head == NULL) {
        q->head = q->tail = q->current = node;
        return;
    }
    node->prev = q->tail;
    q->tail->next = node;
    q->tail = node;
}

void move_next(queue *q)
{
    if (q->current == NULL) {
        printf("Queue is empty.\n");
    } else if (q->current->next == NULL) {
        printf("Already at the last sample.\n");
    } else {
        q->current = q->current->next;
        display_current(q);
    }
}

void move_prev(queue *q)
{
    if (q->current == NULL) {
        printf("Queue is empty.\n");
    } else if (q->current->prev == NULL) {
        printf("Already at the first sample.\n");
    } else {
        q->current = q->current->prev;
        display_current(q);
    }
}

void display_current(const queue *q)
{
    if (q->current == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Current sample:\n");
    print_sample(q->current);
}

void review_forward(const queue *q)
{
    if (q->head == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Reviewing queue head -> tail:\n");
    for (sample *s = q->head; s != NULL; s = s->next) {
        print_sample(s);
        usleep(300000);
    }
    printf("End of queue reached.\n");
}

void review_backward(const queue *q)
{
    if (q->tail == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Reviewing queue tail -> head:\n");
    for (sample *s = q->tail; s != NULL; s = s->prev) {
        print_sample(s);
        usleep(300000);
    }
    printf("Beginning of queue reached.\n");
}

void free_queue(queue *q)
{
    sample *s = q->head;
    while (s != NULL) {
        sample *next = s->next;
        free(s);
        s = next;
    }
    q->head = q->tail = q->current = NULL;
}
