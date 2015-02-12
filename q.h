//CSE430 Project 1
//@author Zach Josephson and Connor Davey

#include <stdio.h>  // included for NULL

struct Queue {
	struct Element* first = NULL;
	struct Element* last = NULL;
// int size = 0;
};

struct Element {
	void* payload;
	struct Element* next = NULL;
	struct Element* previous = NULL;
};

// STATIC UTILITIES
static struct Element* newElement(void* payload) {
	struct Element* new_element = malloc(sizeof(struct Element));
	new_element->payload = payload;
	new_element->next = NULL;
	new_element->previous = NULL;
	return new_element;
}

//GLOBAL VARIABLES

//FORWARD DECLATATIONS
/** This function adds a new element to the end of the Queue.
 * <hr>
 * NOTE: This method will not copy the payload into the given Queue; it will only keep the pointer to the payload given.
 * Avoid dangling pointers!
 * 
 * @para queue
 * 		is a pointer to the Queue
 * @param payload 
 * 		is a pointer to the data to put inside the new Queue Element.
 *
 * @return a pointer to the Element created to contain the given payload.*/
struct Element* enqueue(struct Queue* queue, void* payload) {
	// create a new Element with the given payload
	struct Element* new_element = newElement(payload);

	if (queue->last != NULL) {  // if the Queue is not empty, add the new Element to the end of the given Queue
		queue->last->next = new_element;
		new_element->previous = queue->last;
	} else
		// if the Queue was empty, new_element is also the first Element
		queue->first = new_element;
	queue->last = new_element;

	// return the new Element
	return new_element;
}

/** This function removes the Element at the beginning the given Queue.
 * <hr>
 * NOTE: This function will deallocate the memory space of the Element removed, but it will not deallocate the memory space of the payload itself!
 * Make sure you do that yourself if needed! Also note that this function returns the pointer to that payload, so you could simply use the code below to ensure
 * that payload is deallocated immediately: <pre>
 * 		free(dequeue(queue));
 * </pre>
 * 
 * @param queue
 * 		is a pointer to the Queue that will have its first element dequeued.
 * 
 * @return a pointer to the payload of the Element that was removeed from the Queue. */
void* dequeue(struct Queue* queue) {
	// if the Queue is empty, return NULL
	if (queue->first == NULL)
		return NULL;

	// if the Queue only has one Element, leave it as am empty Queue
	if (queue->first == queue->last)
		queue->first = queue->last = NULL;

	// make a copy of the payload pointer for safe keeping
	void* payload = queue->last->payload;
}

/** This function "peeks" at the last Element in the Queue.
 * 
 * @param queue
 * 		is a pointer to the queue which we want the payload of the last Element from.
 * 
 * @return a pointer to the payload of the last Element in the Queue */
void* peek(struct Queue* queue);

/** This function creates and initializes a new Queue.
 * 
 * @return a pointer to the new Queue struct.*/
struct Queue* newQueue();

/** This function deletes the given Queue.
 * 
 * @param queue
 * 		is a pointer to the Queue to be deleted.
 * 
 * @return the number of Elements that were present in the deleted Queue. */
int deleteQueue(struct Queue* queue);

/** This function moves the header pointer to the next element in the queue. 
 *	This is equivalent to AddQ(&head, DeleteQ(&head)).
 *
 * @param queue
 *		is a pointer to the queue which we want to roate the head of
 *
 * @return void
 */
void rotateQ(struct Queue* queue);
