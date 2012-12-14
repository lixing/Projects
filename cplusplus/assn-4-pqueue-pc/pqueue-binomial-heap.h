/**
 * pqueue-binomial-heap.h
 * priority-queue
 *
 * Created by Jerry Cain on 10/23/10.
 * Copyright 2010 Stanford University. All rights reserved.
 */

#ifndef __binomial_heap_pqueue_cs106__
#define __binomial_heap_pqueue_cs106__

#include "pqueue.h"

class BinomialHeapPQueue : public PQueue {
public:
	BinomialHeapPQueue();
	~BinomialHeapPQueue();
	
	static BinomialHeapPQueue *merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two);
	
	void enqueue(string elem);
	string extractMin();
	string peek();
	
private:
	void swapValues(int swap1, int swap2);
    string *heapValues;
	int allocatedSize;
};

#endif
