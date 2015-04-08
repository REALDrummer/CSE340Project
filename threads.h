#ifndef THREAD_H
#define THREAD_H

#include "tcb.h"
#include "q.h"

#define STACK_SIZE 8192

TCB_t* start_thread(void (*function)(void)) {
    TCB_t* new_TCB = malloc(sizeof(TCB_t));
    void* stack = malloc(STACK_SIZE);

    init_TCB(new_TCB, function, stack, STACK_SIZE);

    enqueue(run_queue, new_TCB);

    return new_TCB;
}

TCB_t* run() {
    ucontext_t parent;      // allocate space to hold a fake context to context switch from
    getcontext(&parent);    // magic sauce that creates a fake context since we are currently without a context to

    // TODO TEMP
    printf("running...\n");

    TCB_t* new_context = (TCB_t*) run_queue->first->payload;  // get the new context from the run queue

    // TODO TEMP
    printf("got the new context; swapping in...\n");

    // TODO TEMP
    printf("new_context=%d\n", (int) new_context);

    // TODO TEMP
    printf("new_context->context=%d\n", (int) &new_context->context);

    swapcontext(&parent, &new_context->context);    // start the first thread

    // TODO TEMP
    printf("Hi!\n");

    return new_context;
}

TCB_t* yield() {
    ucontext_t* current_context = &((TCB_t*) run_queue->first->payload)->context;     // keep track of the old context we're switching out of

    rotateQueue(run_queue);     // rotate the run queue

    TCB_t* new_context = (TCB_t*) run_queue->first->payload;   // get the new context from the run queue

    swapcontext(current_context, &new_context->context);     // switch to the new context now at the front of the run queue

    return new_context;
}

#endif