#include "tcb.h"
#include "q.h"
#include "threads.h"

// struct Queue run_queue = newQueue();  (had to be located in q.h)

unsigned int x = 0;

void incrementX() {
    x++;

    yield();
}

void printEvenXs() {
    if ((x & 1) == 0)
        printf("%d\n", x);

    yield();
}

void printOddXs() {
    if ((x & 1) == 1)
        printf("%d\n", x);

    yield();
}

int main() {
    // initialize the run queue
    run_queue = newQueue();

    // TODO TEMP
    printf("0\n");

    // start three threads using the three functions in this file
    start_thread(incrementX);
    start_thread(printEvenXs);
    start_thread(printOddXs);

    // TODO TEMP
    printf("%s", toString(run_queue));

    // run!
    run();

    // TODO TEMP
    printf("%s", toString(run_queue));

    // TODO TEMP
    printf("2\n");

    return 0;
}