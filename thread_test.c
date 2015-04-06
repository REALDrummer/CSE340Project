//CSE340 Project 2
//Authors: Zach Josephson and Connor Davey
#include "threads.h"
#include "sem.h"

#define true 1

//Global variables
struct Queue* run_queue;

int x = 0;

void counter(){
	do {
		x++;
		yield();
	} while (true);
} 

void printEven(){
	do {
		if ((x % 3) == 0){
			printf("%d - |3\n", x);
		}
		yield();
	} while (true);
}

void printOdd(){
	do {
		if ((x % 5) == 0){
			printf("%d - |5\n", x);
		}
		yield();
	} while (true);
}

void main (){
	//initialize the run queue
	run_queue = newQueue();

	//start threads
	start_thread(counter);
	start_thread(printEven);
	start_thread(printOdd);

	run();
	
}
