/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	head = new Node;
	head->next = NULL;
	head->prev = NULL;
	currSize = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (head != NULL){
		Node* tmp = head;
		head = head->next;
		delete tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return currSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {	
	return size() == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	currSize++;
	Node* newNode = new Node;
	newNode->value = value;
		
	if (size() == 1){
		head = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
		return;
	}
	
	if (value <= head->value){
		head->prev = newNode;
		newNode->next = head;
		newNode->prev =NULL;
		head = newNode;
		return;
	}

	Node* currNode = head;

	while (value > currNode->value){
		if (currNode->next == NULL){
			currNode->next = newNode;
			newNode->prev = currNode;
			newNode->next = NULL;
			return;
		}
		currNode = currNode->next;
	}

	newNode->prev = currNode->prev;
	newNode->next = currNode;

	newNode->prev->next = newNode;
	newNode->next->prev = newNode;
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) error("The queue is empty!");
	return head -> value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) error ("The queue is empty!");
	string result = peek();
	currSize--;
	
	Node* tmp = head;
	head = head->next;
	delete tmp;
	if (head != NULL){
		head->prev=NULL;
	}

	return result;
}

