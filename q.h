//CSE430 Project 1
//Zach Josephson and Connor Davey

struct Element {
	int payload;
	struct Element* next;
	struct Element* previous;
};

//GLOBAL VARIABLES


//FORWARD DECLATATIONS
struct Element* NewItem();
struct Element* InitQueue(struct Element* head);
void AddQueue(struct Element* head, struct Element* item);
struct Element* DelQueue(struct Element* head);
void RotateQ(struct Element* head);





