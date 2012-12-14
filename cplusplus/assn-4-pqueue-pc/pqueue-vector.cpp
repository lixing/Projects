#include "pqueue-vector.h"

VectorPQueue::VectorPQueue() {
    const int INITIALIZE_SIZE = 4;
	logSize = 0;
	allocatedSize = INITIALIZE_SIZE;
	elements = new string[allocatedSize];
}

VectorPQueue::~VectorPQueue() {
    delete[] elements;
}

string VectorPQueue::peek() { 
	if (isEmpty())
		Error("This is an empty pqueue!");

	string minValue = elements[0];
	for (int i = 1; i < logSize; i++) {
		if (elements[i] < minValue) {
			minValue = elements[i];
		}
	}
	return minValue; 
}

string VectorPQueue::extractMin() {

	if (isEmpty())
		Error("This is an empty pqueue!");
		
	int minIndex = 0;	
	string minValue = elements[0];
	for (int i = 1; i < logSize; i++) {
		if (elements[i] < minValue) {
			minValue = elements[i];
			minIndex = i;
		}
	}

	for (int i = minIndex; i < logSize-1; i++) {
		elements[i] = elements[i+1];
	}
	
	logSize --;
	return minValue;
}

void VectorPQueue::enqueue(string elem) {
	if (logSize == allocatedSize) {
		grow();
	}
	elements[logSize] = elem;
	logSize ++;
}

VectorPQueue *VectorPQueue::merge(VectorPQueue *one, VectorPQueue *two) {
	int count = 0;
	VectorPQueue *newVector = new VectorPQueue;
	newVector -> logSize = one->size() + two->size();
	newVector -> allocatedSize = newVector -> logSize * 2;
	string *temp = new string [newVector -> allocatedSize];
	for (int i = 0; i < one->size(); i++) {
		temp[i] = one -> elements[i];
	}
	for (int i = one->size(); i < newVector->size(); i++) {
		temp[i] = two -> elements[count];
		count ++;
	}

	newVector -> elements = temp;
	return newVector;
}

void VectorPQueue::grow() {
	string *newArray = new string[2 * allocatedSize];
	for (int i = 0; i < logSize; i++) {
		newArray[i] = elements[i];
	}
	allocatedSize *= 2;
	delete[] elements;
	elements = newArray;
}


