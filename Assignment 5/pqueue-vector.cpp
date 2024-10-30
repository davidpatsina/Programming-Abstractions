/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {

}

VectorPriorityQueue::~VectorPriorityQueue() {
	
}

int VectorPriorityQueue::size() {
	return queue.size();
}

bool VectorPriorityQueue::isEmpty() {
	return size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	queue.add(value);
}

string VectorPriorityQueue::peek() {
	
	if (size() == 0){
		error("Queue is empty!");
	} else {
		indexForDequeue = 0;
		string result = queue[0];
		for (int i = 0; i < queue.size(); i++){
			if (result > queue[i]) {
				indexForDequeue = i;	
				result = queue[i];
			}
			
		}
		return result;
	}
}


string VectorPriorityQueue::dequeueMin() {
	if (size() == 0){
		error("Queue is empty!");
	} else {
		string result = peek();
		queue.remove(indexForDequeue);
		return result;
	}
}

