//CSE430 Project 1
//@author Zach Josephson and Connor Davey
#ifndef Q_H
#define Q_H

#include <stdio.h>  // included for NULL

struct Queue {
	struct Element* first;
	struct Element* last;
};

struct Queue* run_queue;

struct Element {
	void* payload;
	struct Element* next;
	struct Element* previous;
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

//FORWARD DECLARATIONS
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
 * 
 * @param queue
 * 		is a pointer to the Queue that will have its first element dequeued.
 * @param free_payload
 * 		determines whether or not the payload of the dequeued Element should be removed from memory. <br>
 * 		The <b>char</b> here is used according to C truthiness: 0 = false, anything else = true.
 * 
 * @return a pointer to the payload of the Element that was removeed from the Queue. */
void* dequeue(struct Queue* queue, char free_payload) {
	// if the Queue is empty, return NULL
	if (queue->first == NULL)
		return NULL;

	// make a copy of the payload pointer for safe keeping
	void* payload = queue->first->payload;

	// if the Queue only has one Element, leave it as am empty Queue
	if (queue->first == queue->last) {
		free(queue->first);
		queue->first = queue->last = NULL;
	} else {  // otherwise, remove the first Element
		struct Element* new_first = queue->first->next;
		free(queue->first);
		queue->first = new_first;
	}

	if (free_payload)
		free(payload);

	return payload;
}

/** This function "peeks" at the first Element in the Queue.
 * 
 * @param queue
 * 		is a pointer to the queue which we want the payload of the first Element from.
 * 
 * @return a pointer to the payload of the first Element in the Queue */
void* peek(struct Queue* queue) {
	return queue->first->payload;
}

/** This function creates and initializes a new Queue.
 * 
 * @return a pointer to the new Queue struct.*/
struct Queue* newQueue() {
	struct Queue* new_queue = malloc(sizeof(struct Queue));
	new_queue->first = NULL;
	new_queue->last = NULL;
	return new_queue;
}

/** This function deletes the given Queue.
 * 
 * @param queue
 * 		is a pointer to the Queue to be deleted.
 * @param free_payloads
 * 		determines whether or not the payloads of the Elements in this Queue should be removed from memory. <br>
 * 		The <b>char</b> here is used according to C truthiness: 0 = false, anything else = true.
 * 
 * @return the number of Elements that were present in the deleted Queue. */
unsigned int deleteQueue(struct Queue* queue, char free_payloads) {
	// if the Queue is empty, just free its pointers and return 0
	if (queue->first == NULL) {
		free(queue);
		return 0;
	}

	// keep track of the number of Elements removed to return it at the end
	unsigned int size_of_queue = 1;  // init to 1 since we know we have 1+ Elements anyway

	// first, keep removing Elements until we're down to one
	while (queue->first != queue->last) {
		size_of_queue++;

		void* payload = dequeue(queue, 1);
		if (free_payloads)
			free(payload);
	}

	// finally, free the last Element, free the Queue, and return the number of Elements we removed
	free(queue->first);
	free(queue);
	return size_of_queue;
}

/** This function effectively shifts the given Queue forward one item, making the third item the second, the second item the first, and
 * moving the first item down to the end of the Queue.
 *
 * @param queue
 * 				is the Queue that will be rotated.
 *
 * @return a pointer to the payload of the Element that was first in the given Queue prior to rotation (at the end of the Queue after rotation).
 *  */
void* rotateQueue(struct Queue* queue) {
	// if the given Queue is empty, do nothing and return a NULL payload
	if (queue->first == NULL)
		return NULL;
	// if the given Queue only has one Element, do nothing and return that Element's payload
	else if (queue->first == queue->last)
		return queue->first->payload;

	// keep track of the Element to be moved to the end
	struct Element* rotated_element = queue->first;

	// disconnect the rotated Element from the front of the Queue
	queue->first = queue->first->next;
	rotated_element->next = NULL;
	queue->first->previous = NULL;

	// connect the rotated Element to the end of the Queue
	queue->last->next = rotated_element;
	rotated_element->previous = queue->last;
	queue->last = rotated_element;

	return rotated_element->payload;
}

#endif