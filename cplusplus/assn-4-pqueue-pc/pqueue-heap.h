/**
 * pqueue-heap.h
 * priority-queue
 *
 * Created by Jerry Cain on 10/23/10.
 * Copyright 2010 Stanford University. All rights reserved.
 */

#ifndef __binary_heap_pqueue_cs106__
#define __binary_heap_pqueue_cs106__

#include "pqueue.h"

class HeapPQueue : public PQueue {
public:
	HeapPQueue();
	~HeapPQueue();
	
	static HeapPQueue *merge(HeapPQueue *one, HeapPQueue *two);
	
	void enqueue(string elem);
	string extractMin();
	string peek();
	
private:
    void grow();
	void insertValue(int heapInsert);
	void swapValues(int swap1, int swap2);
	void moveRootDown(int rootLocation);
	void heapSort(int arraySize);
    void shiftDown(int root, int bottom);
    string *heapValues;
	int allocatedSize;

};

#endif