#include <stdio.h>
#include <string.h>
#include "main.h"

static void read_sample(queue *q)
{
    char id[32], type[32];
    int priority;

    printf("Sample ID: ");
    if (scanf("%31s", id) != 1) return;
    printf("Sample type: ");
    if (scanf("%31s", type) != 1) return;
    printf("Priority (1=urgent, 2=normal, 3=routine): ");
    if (scanf("%d", &priority) != 1 || priority < 1 || priority > 3) {
        printf("Invalid priority, sample not added.\n");
        return;
    }
    insert_end(q, create_node(id, type, priority));
    printf("Sample %s added to the end of the queue.\n", id);
}

int main(void)
{
    queue q = { NULL, NULL, NULL };
    int n, choice;

    printf("How many samples to load initially? ");
    if (scanf("%d", &n) != 1) n = 0;
    for (int i = 0; i < n; i++) {
        printf("--- Sample %d ---\n", i + 1);
        read_sample(&q);
    }

    do {
        printf("\n1. Next sample\n2. Previous sample\n3. Display current\n"
               "4. Add sample\n5. Review forward\n6. Review backward\n0. Exit\n> ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
        case 1: move_next(&q); break;
        case 2: move_prev(&q); break;
        case 3: display_current(&q); break;
        case 4: read_sample(&q); break;
        case 5: review_forward(&q); break;
        case 6: review_backward(&q); break;
        case 0: break;
        default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    free_queue(&q);
    printf("Exiting. Memory freed.\n");
    return 0;
}
