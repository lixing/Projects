/**
 * pqueue-linked-list.h
 * priority-queue
 *
 * Created by Jerry Cain on 10/23/10.
 * Copyright 2010 Stanford University. All rights reserved.
 */

#ifndef __linked_list_pqueue_cs106__
#define __linked_list_pqueue_cs106__

#include "pqueue.h"

class LinkedListPQueue : public PQueue {
public:
	LinkedListPQueue();
	~LinkedListPQueue();
	
	static LinkedListPQueue *merge(LinkedListPQueue *one, LinkedListPQueue *two);
	
	void enqueue(string elem);
	string extractMin();
	string peek();
	
private:
	struct node {
		string value;
		node *next;
	};
	node *tail;
	node *head;
	int size;

};

#endif
