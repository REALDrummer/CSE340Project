//
// Created by connor on 4/6/15.
//

#ifndef _CSE340_PROJECT_3_SEM_H_
#define _CSE340_PROJECT_3_SEM_H_

#include <stdio.h>
#include <stdlib.h>
#include "threads.h"
#include "q.h"

struct Semaphore {
    int value;
    struct Queue* queue;
};

struct Semaphore* newSemaphore(int initial_value) {
    struct Semaphore* new_semaphore = malloc(sizeof(struct Semaphore));

    new_semaphore->value = initial_value;
    new_semaphore->queue = newQueue();

    return new_semaphore;
}

void P(struct Semaphore* semaphore) {
    semaphore->value--;

    // move a task from the run queue to this queue
    if (semaphore->value < 0) {
        TCB_t *task_to_block = (TCB_t *) dequeue(run_queue, FALSE);
        if (task_to_block != NULL)
            enqueue(semaphore->queue, task_to_block);

        yield();
    }
}

void V(struct Semaphore* semaphore) {
	// TODO TEMP
	printf("entering V...\n");

    semaphore->value++;

    if (semaphore->value <= 0) {
        TCB_t *task_to_run = (TCB_t *) dequeue(semaphore->queue, FALSE);
        if (task_to_run != NULL)
            enqueue(run_queue, task_to_run);
    }

	// TODO TEMP
	printf("leaving V on a yield...\n");	
	
    yield();
}

#endif //_CSE340_PROJECT_3_SEM_H_
