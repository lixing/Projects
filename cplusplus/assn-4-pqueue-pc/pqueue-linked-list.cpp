#include "pqueue-linked-list.h"

LinkedListPQueue::LinkedListPQueue() {
	head = NULL;
	size = 0;
	tail = NULL;
	logSize = 0;
}
LinkedListPQueue::~LinkedListPQueue() {
    for (node *curr = head; curr != NULL;) {
		node *toDelete = curr;
		curr = curr->next;
		logSize --;
		delete toDelete;
	}
}

string LinkedListPQueue::peek() { 
    if (isEmpty())
		Error("This is an empty pqueue!");

    node *toBeDeleted = head;
 	string value = head->value;
 	head = head->next; 	
	return value; 
}

string LinkedListPQueue::extractMin() {
    if (isEmpty())
		Error("This is an empty pqueue!");
	
 	node *toBeDeleted = head;
 	string value = head->value;
 	head = head->next; 	
	delete toBeDeleted;
	logSize --;
	return value;
}

void LinkedListPQueue::enqueue(string elem) {
	node *curr, *prev, *newNode = new node;
 	newNode->value = elem;
 	
 	for (prev = NULL, curr = head; curr != NULL; prev=curr, curr = curr->next) {
 		if (elem < curr->value) break;
 	}

 	newNode->next = curr;
 	if (prev) 
 		prev->next = newNode;
 	else 
 		head = newNode;
	logSize ++;
}


LinkedListPQueue *LinkedListPQueue::merge(LinkedListPQueue *one, LinkedListPQueue *two) {
    LinkedListPQueue *newLinkedList = one;

	for (node *curr = two -> head; curr != NULL; curr = curr->next) {
		newLinkedList -> enqueue(curr -> value);
	}

	return newLinkedList;
}

