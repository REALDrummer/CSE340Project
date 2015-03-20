//CSE340 Project 2
//Authors: Zach Josephson and Connor Davey
#include "threads.h"

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
		if ((x % 2) == 0){
			printf("%d - even\n", x);
		}
		yield();
	} while (true);
}

void printOdd(){
	do {
		if ((x % 2) == 1){
			printf("%d - odd\n", x);
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
