//
// Created by connor on 4/6/15.
//

#ifndef _CSE340_PROJECT_3_SEM_H_
#define _CSE340_PROJECT_3_SEM_H_

#include <stdio.h>
#include <stdlib.h>
#include "tcb.h"
#include "q.h"

struct Semaphore {
    int value;
    struct Queue* queue;
};

struct Semaphore* newSemaphore(int initial_value) {
    struct Semaphore* new_semaphore = malloc(sizeof(struct Semaphore));

    new_semaphore->value = initial_value;
    new_semaphore->queue = newQueue();
}

void P(struct Semaphore* semaphore) {
    semaphore->value--;

    while (semaphore->value <= 0);
}

void V(struct Semaphore* semaphore) {
    semaphore->value++;

    if (semaphore->value <= 0) {
        TCB_t* task_to_run = (TCB_t*) dequeue(semaphore->queue, FALSE);
        enqueue(run_queue, task_to_run);
    }
}

#endif //_CSE340_PROJECT_3_SEM_H_
