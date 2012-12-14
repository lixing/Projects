#include "pqueue-binomial-heap.h"

BinomialHeapPQueue::BinomialHeapPQueue() {
	int INITIALIZE_SIZE = 10;
	allocatedSize = INITIALIZE_SIZE;
	heapValues = new string[INITIALIZE_SIZE];
	logSize = 0;
}
BinomialHeapPQueue::~BinomialHeapPQueue() {
	delete[] heapValues;
}

string BinomialHeapPQueue::peek() { 
	int best = 0;
	int current = 0;
	for(int current = 0; current < logSize; current ++){
		if(heapValues[current] < heapValues[best])
			swapValues(current, best);
	}
	return heapValues[best]; 
}

void BinomialHeapPQueue::swapValues(int swap1, int swap2){
	string tmp = heapValues[swap1];
	heapValues[swap1] = heapValues[swap2];
	heapValues[swap2] = tmp;
}

string BinomialHeapPQueue::extractMin() {
/* pseudo code.

    rootlist = 0;
	current = child[min];
	while(current != NULL){
	   parent[current] = NULL;
	   rootlist = current + rootlist;
	}
	string *newHeap;
	head[newHeap] = rootlist[0];
	heapValues = unify(heapValues, newHeap);

*/
	return peek();
}

void BinomialHeapPQueue::enqueue(string elem) {
/* pseudo code.

    string *newHeap;
	head[newHeap] = element;
	parent[newHeap] = element;
	sibling[newHeap] = null;
	chile[newHeap] = null;
	degree[newHeap] = 1;
	unify(heapValues, newHeap);

*/
}


/* pseudo code.
string BinomialHeapPQueue::unify(string heap1[], string heap2[]){
    string *returnHeap;
	if(head[returnHeap] = NULL){
	   return returnHeap;
	}

	previous = NULL;
	current = head[returnHeap];
	next = sibling[current];

	while(next != NULL){
	   bool merge = true;
	   if(degree[current] != degree[next])
	       merge = false;
	   if(sibling[next] != NULL && degree[sibling[next]] = degree[next])
	       merge = false;
	   if(merge){
	       if(key[current] <= key[next]){
		      sibling[current] = sibling[next];
			  link(current, next);
			  }
		  else if(previous != Null){
		      sibling[previous] = next;
			  link[next, current];
		  }
		  else{
		      head[returnHeap] = next;
			  link(next, current);
		  }
	   }
	   else{
	      previous = current;
		  current = next;
	  }
	  next = sibling[current];
	  }
}

void BinomialHeapPQueue::link(string root, string branch){
    parent[branch] = root;
	sibling[branch] = chile[root];
	chile[root] = branch;
	degree[root] = degree[root] + 1;
}



*/
BinomialHeapPQueue *BinomialHeapPQueue::merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two) {
    BinomialHeapPQueue *newHeap;
	int current, currentOne, currentTwo, tail;

	int logSize = one -> logSize + two -> logSize;
	int allocatedSize = logSize * 2;
	string *sortHeap = new string[allocatedSize];

	string *sortHeapOne = new string[one -> logSize * 2];
	string *sortHeapTwo = new string[two -> logSize * 2];
	sortHeapOne = one ->heapValues;
	sortHeapTwo = two -> heapValues;
	
	if(sortHeapOne[0] < sortHeapTwo[0]){
		sortHeap[0] = sortHeapOne[0];
		currentTwo = 1;
		currentOne = 0;
	}
	else {
	    sortHeap[0] = sortHeapTwo[0];
		currentTwo = 0;
		currentOne = 1;
	}
	current = 0;

	while(currentOne <= one->logSize || currentTwo <= two->logSize){
		if(sortHeapOne[currentOne] > sortHeapTwo[currentTwo]){
			current ++;
			sortHeap[current] = sortHeapTwo[currentTwo];
			currentTwo += 1;
		}
		else {
			current ++;
			sortHeap[current] = sortHeapOne[currentOne];
			currentOne += 1;
		}
	
	}

	if(currentOne > one->logSize){
		tail = currentTwo;
		while(tail < one ->logSize){
			sortHeap[current] = sortHeapTwo[tail];
		    tail ++;
		}
	}
	else{ 
		tail = currentOne;
		while(tail < two ->logSize){
			sortHeap[current] = sortHeapOne[tail];
		    tail ++;
	    }
	}

	newHeap -> heapValues = sortHeap;

	return newHeap;
}
