/**
 * pqueue-vector.h
 * priority-queue
 *
 * Created by Jerry Cain on 10/23/10.
 * Copyright 2010 Stanford University. All rights reserved.
 */

#ifndef __vector_pqueue_cs106__
#define __vector_pqueue_cs106__

#include "pqueue.h"

class VectorPQueue : public PQueue {
public:
	VectorPQueue();
	~VectorPQueue();
	
	static VectorPQueue *merge(VectorPQueue *one, VectorPQueue *two);
	
	void enqueue(string elem);
	string extractMin();
	string peek();
	
private:
	// update the private section with the list of 
	// data members and helper methods needed to implement
	// the vector-backed version of the PQueue.
	void grow();

	string *elements;
	int allocatedSize;
};

#endif