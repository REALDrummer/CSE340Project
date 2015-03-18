#include "tcb.h"
#include "q.h"
#include "threads.h"

// struct Queue run_queue = newQueue();  (had to be located in q.h)

unsigned int x = 0;

void incrementX() {
    x++;
}

void printEvenXs() {
    if ((x & 1) == 0)
        printf("%d", x);
}

void printOddXs() {
    if ((x & 1) == 1)
        printf("%d", x);
}

int main() {
    // initialize the run queue
    run_queue = newQueue();

    // start three threads using the three functions in this file
    start_thread(incrementX);
    start_thread(printEvenXs);
    start_thread(printOddXs);

    // run!
    run();
}