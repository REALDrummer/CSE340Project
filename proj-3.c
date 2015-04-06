//CSE340 Project 3
//@author Zach Josephson and Connor Davey


 #include <threads.h>

//Global variables
int x = 0;

struct Semaphore* run_sem;

void counter(){
	do{
		P(run_sem);
		x++;
		V(run_sem);
	} while(true)
}

void printCounter(){
	do {
		P(run_sem);
		printf("%d", x);
		V(run_sem);
	} while(true)
}


