/**
 * File: pqueue-test.cpp
 * ---------------------
 * Created by Jerry Cain on 10/10/10.
 * Modified by Chris Piech on 20/July/11
 */

#include "genlib.h"
#include "pqueue.h"
#include "lexicon.h"
#include "map.h"
#include "random.h"
#include <iostream>

const int TEST_SIZE = 10000;

void SortedTest(PQueue::PQueueType pqtype, Lexicon& english, int size);
void ScrambledTest(PQueue::PQueueType pqtype, Lexicon& english, int size);
void RandomizedTest(PQueue::PQueueType pqtype, int size);
void MergeTest(PQueue::PQueueType pqtype, Lexicon& english, int size);

int main() {
	Randomize();
	Lexicon english("lexicon.dat");
	Vector<PQueue::PQueueType> tests;
	tests.add(PQueue::UnsortedVector);
	tests.add(PQueue::LinkedList);
	tests.add(PQueue::Heap);
	for (int i = 0; i < tests.size(); i++) {
		string name = PQueue::typeToName(tests[i]);
		cout << "Exercising the " << name << endl;
		cout << "---------------" << string(name.size(), '-') << endl;
		SortedTest(tests[i], english, TEST_SIZE);
		ScrambledTest(tests[i], english, TEST_SIZE);
		RandomizedTest(tests[i], TEST_SIZE);
		MergeTest(tests[i], english, TEST_SIZE / 10);
		cout << endl;
	}
	
	return 0;
}

/***********************************************************************
 *                    Code For Testing Pqueues                         *
 ***********************************************************************/

template <typename Iterable>
 PQueue *BuildPQueue(PQueue::PQueueType pqtype, Iterable iter, int size) {
	PQueue *pq = PQueue::createPQueue(pqtype);
	int count = 0;
	foreach (string key in iter) {
		pq->enqueue(key);
		count++;
		if (count == size) break;
	}
	
	cout << "+ Inserted " << pq->size() << " words." << endl;
	return pq;
}

 void ExtractElements(PQueue::PQueueType pqtype, PQueue *pq) {
	string leastSoFar;
	cout << "+ Extracting all elements, and confirming they come in alphabetical order." << endl;
	cout << "     [You'll see a dot for every 1000 extracted.]" << endl << "     ";

	int count = 0;
	int numExtractionsExpected = pq->size();
	while (!pq->isEmpty()) {
		string next = pq->extractMin();
		if (next < leastSoFar) Error("Priority Queue is returning elements in the wrong order.");
		leastSoFar = next;
		count++;
		if (count % 1000 == 0) {
			cout << ".";
			cout.flush();
			if (count % 40000 == 0) {
				cout << endl << "     ";
				cout.flush();
			}
		}
	}
	
	cout << endl;
	if (count != numExtractionsExpected) {
		ostringstream os;
		os << "Priority queue of type " << PQueue::typeToName(pqtype) << " had " << numExtractionsExpected <<
			  " elements, but we only extracted " << count << " of them." << endl;
		Error(os.str());
	}
	cout << "+ Properly extracted all " << count << " elements from the priority queue." << endl;
}

 void SortedTest(PQueue::PQueueType pqtype, Lexicon& english, int size) {
	PQueue *pq = BuildPQueue(pqtype, english, size);
	ExtractElements(pqtype, pq);
	delete pq;
	cout << "+ SortedTest seems to work well with the " << PQueue::typeToName(pqtype) << ", provided destructor works properly." << endl;
}

 void ScrambledTest(PQueue::PQueueType pqtype, Lexicon& english, int size) {
	Map<bool> map;
	foreach (string word in english) map[word] = true;
	PQueue *pq = BuildPQueue(pqtype, map, size);
	ExtractElements(pqtype, pq);
	delete pq;
	cout << "+ ScrambledTest seems to work well with the " << PQueue::typeToName(pqtype) << ", provided destructor works properly." << endl;
}

 string CreateRandomString() {
	string s(16, '-');
	for (int i = 0; i < s.size(); i++) 
		s[i] = RandomInteger('a', 'z');
	return s;
}

 void RandomizedTest(PQueue::PQueueType pqtype, int size) {
	Vector<string> randomStrings;
	size = min(size, 100000);
	for (int i = 0; i < size; i++) randomStrings.add(CreateRandomString());
	PQueue *pq = BuildPQueue(pqtype, randomStrings, size);
	ExtractElements(pqtype, pq);
	delete pq;
	cout << "+ RandomizedTest seems to work well with the " << PQueue::typeToName(pqtype) << ", provided destructor works properly." << endl;
}

 void MergeTest(PQueue::PQueueType pqtype, Lexicon& english, int size) {
	Map<bool> map;
	foreach (string word in english) map[word] = true;
	cout << "+ Constructing two priority queues to exercise merge." << endl;
	PQueue *pq1 = BuildPQueue(pqtype, map, size);
	PQueue *pq2 = BuildPQueue(pqtype, map, size);
	int size1 = pq1->size();
	int size2 = pq2->size();
	PQueue *pq = PQueue::merge(pq1, pq2);

	if (pq == NULL) {
		cout << "+ MergeTest can only work once you implement the merge operation." << endl;
		return;
	}
		
	if (size1 + size2 != pq->size()) {
		Error("Priority Queue merge clearly failed, because size of merge doesn't equal the sum of the two original sizes.");
	}
		
	while (!pq->isEmpty()) {
		string one = pq->extractMin();
		string two = pq->extractMin();
		if (one != two) Error("Merge of two identical priority queues should have two copies of all entries.");
		map.remove(one);
	}
	
	delete pq;
	cout << "+ MergeTest seems to work well with the " << PQueue::typeToName(pqtype) << ", provided destructor works properly." << endl;
}



