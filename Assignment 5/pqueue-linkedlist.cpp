/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	currSize = 0;
	head = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (head != NULL){
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return currSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	currSize++;
	Node* newNode = new Node;
	newNode->value = value;

	if (size() == 1){
		head = newNode;
		newNode->next = NULL;
		return;
	}

	if (value <= head->value){
		newNode->next = head;
		head = newNode;
		return;
	}

	Node* currNode = head;
 	Node* prevNode = NULL;
	
	while (value > currNode->value){
		prevNode = currNode;
		currNode = currNode->next;
		if (currNode == NULL){
			prevNode->next = newNode;
			newNode->next = NULL;
			return;
		}
	}

	prevNode->next = newNode;
	newNode->next = currNode;
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty()) error("The queue is empty!");
	return head -> value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) error ("The queue is empty!");
	string result = peek();	
	currSize--;
	Node* tmp = head;
	head = head->next;
	delete tmp;
	return result;
}

