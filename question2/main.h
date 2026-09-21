#ifndef MAIN_H
#define MAIN_H

typedef struct sample {
    char id[32];
    char type[32];
    int priority; /* 1 = urgent, 2 = normal, 3 = routine */
    struct sample *next;
    struct sample *prev;
} sample;

typedef struct {
    sample *head;
    sample *tail;
    sample *current; /* the technician's position in the queue */
} queue;

/* dll.c */
sample *create_node(const char *id, const char *type, int priority);
void insert_end(queue *q, sample *node);
void move_next(queue *q);
void move_prev(queue *q);
void display_current(const queue *q);
void review_forward(const queue *q);
void review_backward(const queue *q);
void free_queue(queue *q);

#endif
