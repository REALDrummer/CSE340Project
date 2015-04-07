//CSE340 Project 3
//@author Zach Josephson and Connor Davey

#include "sem.h"

//Global variables
int x = 0;

struct Semaphore* run_sem;

void counter(){
	do{
		P(run_sem);
		x++;
		V(run_sem);
	} while (1);
}

void printCounter(){
	do {
		P(run_sem);
		printf("%d\n", x);
		V(run_sem);
	} while (1);
}



int main() {
	run_sem = newSemaphore(0);

	run_queue = newQueue();

	start_thread(counter);
	start_thread(printCounter);

	run();

	return 0;
}