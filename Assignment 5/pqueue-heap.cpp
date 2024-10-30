/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"
#include <iostream>
using namespace std;
HeapPriorityQueue::HeapPriorityQueue() {
	
	alocSize = START_ALOCATED_SIZE;
	logSize = 0;
	data = new string[alocSize];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete [] data;
}

int HeapPriorityQueue::size() {	
	return logSize;
}

bool HeapPriorityQueue::isEmpty() {
	return size()==0;
}

void HeapPriorityQueue::enqueue(string value) {
	checkAlocSize();
	data[logSize] = value;
	logSize++;
	bubbleUp();
}

string HeapPriorityQueue::peek() {
	if(isEmpty()) error("The queue is empty!");
	return data[0];
}

string HeapPriorityQueue::dequeueMin() {
	if(isEmpty()) error("The queue is empty!");
	string result = peek();
	swapFirstAndLast();
	bubbleDown();
	return result;
}

void HeapPriorityQueue::swap(int index1, int index2){
	string tmp = data[index1];
	data[index1] = data[index2];
	data[index2] = tmp;
}

void HeapPriorityQueue::swapFirstAndLast(){
	swap(0, logSize-1);
	logSize--;
}

int HeapPriorityQueue::getPossibleDirection(int child1, int child2){
	if (child2 < logSize){
		if (data[child1] <= data[child2]){
			return child1;
		}else return child2;
	} 
	if (child1 < logSize) return child1;
	return SENTINEL;
}

void HeapPriorityQueue::bubbleDown(){
	int parent = 0;		
	string value = data[parent];

	int child1 = 2*parent+1;
	int child2 = 2*parent+2;

	int child = getPossibleDirection(child1, child2);

	while(parent < logSize && child != SENTINEL && value > data[child]){
		swap(parent, child);
		parent = child;
		child1 = 2*parent+1;
		child2 = 2*parent+2;
		child = getPossibleDirection(child1, child2);
	}
}

void HeapPriorityQueue::bubbleUp(){
	int child = logSize-1;
	int parent = logSize/2 - 1;

	string value = data[child];

	while (child > 0 && value < data[parent] ){
		swap(parent, child);
		child = parent;
		parent = (child-1)/2;
	}
	
}

void HeapPriorityQueue::checkAlocSize(){
	if(size() == alocSize){
		string* tmp = data;
		alocSize = alocSize*2;
		data = new string[alocSize];
		for (int i = 0; i<logSize; i++){
			data[i] = tmp[i];
		}

		delete [] tmp;
	}
}


