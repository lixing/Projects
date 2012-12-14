#include "pqueue-heap.h"

HeapPQueue::HeapPQueue() {
	int INITIALIZE_SIZE = 10;
	allocatedSize = INITIALIZE_SIZE;
	heapValues = new string[INITIALIZE_SIZE];
	logSize = 0;
}

HeapPQueue::~HeapPQueue() {
	delete[] heapValues;
}

string HeapPQueue::peek() { 
	if (isEmpty())
		Error("no more values");

	else{
		return heapValues[0];
	}
	return ""; 
}

string HeapPQueue::extractMin() {
	if (isEmpty())
		Error("no more values");
	else{
		string returnValue = heapValues[0];
		logSize--;
		heapValues[0] = heapValues[logSize];
		moveRootDown(1);
		return returnValue;
	}
	return "";
}

//to test which one of the next two are the smallest, and switch it and the root.
void HeapPQueue::moveRootDown(int rootLocation){
	int leftValue = (rootLocation * 2);
	int rightValue = (rootLocation * 2) + 1;
	int smallest =-1;
	if (leftValue <= logSize)
		smallest = leftValue;
	if (rightValue <= logSize)
		if (heapValues[smallest - 1] > heapValues[rightValue - 1])
			smallest = rightValue;
	if (smallest == -1) return;
	if (heapValues[rootLocation - 1] > heapValues[smallest - 1]){
		swapValues(rootLocation - 1, smallest - 1);
		moveRootDown(smallest);
	}
}

void HeapPQueue::grow(){
	string *temp = new string[2 * allocatedSize];
	for (int i = 0; i < logSize; i++){
		temp[i] = heapValues[i];
	}
	allocatedSize *=2;
	delete[] heapValues;
	heapValues = temp;
	
}

void HeapPQueue::swapValues(int swap1, int swap2){
	string tmp = heapValues[swap1];
	heapValues[swap1] = heapValues[swap2];
	heapValues[swap2] = tmp;
}

void HeapPQueue::insertValue(int index){
	int i = index;
	if (index > 0){
		index--;

		if (index == 1) 
			index=0; 
		else index/=2;

		// swap the values if parent node is larger than the present node
		if (heapValues[index] > heapValues[i]){
			swapValues(index, i);
			return insertValue(index);
		}
	}
	return;
}

void HeapPQueue::enqueue(string elem) {
	if (allocatedSize == logSize){
		grow();
	}
	heapValues[logSize] = elem;
	insertValue(logSize);
	logSize++;
}


void HeapPQueue::heapSort(int arraySize){
  for (int i = (arraySize / 2)-1; i >= 0; i--)
    shiftDown(i, arraySize);

  for (int i = arraySize-1; i >= 1; i--) {
    swapValues(0, i);
    shiftDown(0, i-1);
  }
}

//to determine if it need to shiftdown or not.
void HeapPQueue::shiftDown(int root, int bottom){
  int maxChild;
  bool done = false;

  while ((root*2 <= bottom) && (!done))  {
    if (root*2 == bottom)
		maxChild = root * 2;

    else if (heapValues[root * 2] > heapValues[root * 2 + 1])
		maxChild = root * 2;
    else
		maxChild = root * 2 + 1;
    
    if (heapValues[root] < heapValues[maxChild]){
		swapValues(root, maxChild);
		root = maxChild;
    }
    else done = true;
  }
}

HeapPQueue *HeapPQueue::merge(HeapPQueue *one, HeapPQueue *two) {
    HeapPQueue *newHeap = new HeapPQueue;
	newHeap -> logSize = one -> logSize + two -> logSize;
	newHeap -> allocatedSize = newHeap -> logSize * 2;
	string *sortHeap = new string[newHeap -> allocatedSize];
    int count = 0;

	//get the combination array of one and two
	for(int i = 0; i < one->size(); i++){
		sortHeap[i] = one ->heapValues[i];
	}

	for(int i = one -> size() + 1; i < two->size(); i++){
		sortHeap[i] = two -> heapValues[count];
		count ++;
	}

	newHeap -> heapValues = sortHeap;
	//sort the array
	newHeap -> heapSort(newHeap -> logSize);

	return newHeap;
}