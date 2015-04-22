//CSE340 Project 4
//@author Zach Josephson and Connor Davey

#include "sem.h"
#include <stdio.h>

#define true 1

struct Semaphore* reading;
struct Semaphore* writing;
struct Semaphore* readingBlock;
struct Semaphore* writingBlock;

struct Queue* run_queue;

int next_number = 0;


//Global Variables
int rc = 0;
int wc = 0;

void reader1() {
	while (true) {
        P(readingBlock);
        V(readingBlock);
		P(reading);
        rc++;
        if(rc == 1){
            P(writingBlock);
        }
        V(reading);
		
		FILE* file = fopen("test file.txt", "r");
		if (file == NULL) {
			printf("Reader 1 couldn't open the file!\n");
			exit(2);
		}
        
		unsigned int read_number;
		while (fscanf(file, "%d\n", &read_number) != EOF)
			printf("R1 read %d\n", read_number);
			
		fclose(file);
        
        P(reading);
        rc--;
        if(rc == 0){
            V(writingBlock);
        }
		
		V(reading);
		yield();
	}
}

void reader2() {
	while (true) {
        P(readingBlock);
        V(readingBlock);
        P(reading);
        rc++;
        if(rc == 1){
            P(writingBlock);
        }
        V(reading);

		
		FILE* file = fopen("test file.txt", "r");
		if (file == NULL) {
			printf("Reader 2 couldn't open the file!\n");
			exit(2);
		}
		
		unsigned int read_number;
		while (fscanf(file, "%d\n", &read_number) != EOF)
			printf("R2 read %d\n", read_number);
			
		fclose(file);
		
        P(reading);
        rc--;
        if(rc == 0){
            V(writingBlock);
        }
        
        V(reading);
        yield();
	}
}

void reader3() {
	while (true) {
        P(readingBlock);
        V(readingBlock);
        P(reading);
        rc++;
        if(rc == 1){
            P(writingBlock);
        }
        V(reading);
		
		FILE* file = fopen("test file.txt", "r");
		if (file == NULL) {
			printf("Reader 3 couldn't open the file!\n");
			exit(2);
		}
		
		unsigned int read_number;
		while (fscanf(file, "%d\n", &read_number) != EOF)
			printf("R3 read %d\n", read_number);
			
		fclose(file);
		
        P(reading);
        rc--;
        if(rc == 0){
            V(writingBlock);
        }
        
        V(reading);
        yield();
    }
}

void writer1() {
	while (true) {
		P(writing);
        wc++;
        if(wc == 1){
            P(readingBlock);
        }
        V(writing);
        
        P(writingBlock);
		
		FILE* file = fopen("test file.txt", "a");
		if (file == NULL) {
			printf("Writer 1 couldn't open the file!\n");
			exit(2);
		}
		
		fprintf(file, "%d\n", ++next_number);
		printf("W1 wrote %d\n", next_number);
		
		fclose(file);
        
		
        V(writingBlock);
        P(writing);
        wc = wc - 1;
        if(wc == 0){
            V(readingBlock);
            
        }
		V(writing);
		
		yield();
	}
}

void writer2() {
	while (true) {
        P(writing);
        wc++;
        if(wc == 1){
            P(readingBlock);
        }
        V(writing);
        P(writingBlock);
		
		FILE* file = fopen("test file.txt", "a");
		if (file == NULL) {
			printf("Writer 2 couldn't open the file!\n");
			exit(2);
		}
		
		fprintf(file, "%d\n", ++next_number);
		printf("W2 wrote %d\n", next_number);
		
		fclose(file);
		
        V(writingBlock);
        P(writing);
        wc = wc - 1;
        if(wc == 0){
            V(readingBlock);
            
        }
        V(writing);
        
        yield();
	}
}


int main(){
	reading = newSemaphore(1);
	writing = newSemaphore(1);
    readingBlock = newSemaphore(1);
    writingBlock = newSemaphore(1);
	

    
	run_queue = newQueue();
	
	start_thread(reader1);
	start_thread(reader2);
	start_thread(reader3);
	
	start_thread(writer1);
	start_thread(writer2);
	
	run();
    
    return 0;
}
