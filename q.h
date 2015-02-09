//CSE430 Project 1
//@author Zach Josephson and Connor Davey

struct Queue {
	struct Element* head = NULL;
	struct Element* tail = NULL;
	// int size = 0;
};

struct Element {
	void* payload;
	struct Element* next;
	struct Element* previous;
};

//GLOBAL VARIABLES

//FORWARD DECLATATIONS
/** This function adds a new element to the end of the Queue.
 * 
 * @param payload 
 * 		is a pointer to the data to put inside the new Queue Element.
 * @return a pointer to the Element created to contain the given payload.*/
struct Element* enqueue(void* payload);

/** This function removes the Element at the beginning the given Queue.
 * 
 * @param queue
 * 		is a pointer to the Queue that will have its first element dequeued.
 * 
 * @return a pointer to the payload of the Element that was removeed from the Queue. */
void* dequeue(struct Queue* queue);

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
