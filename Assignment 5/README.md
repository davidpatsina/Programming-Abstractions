
# Programming Abstractions in C++ : CS106B Stanford
- [Assignment 5: Priority Queue](http://web.stanford.edu/class/archive/cs/cs106b/cs106b.1136/handouts/180%20Assignment%205.pdf)

There are multiple ways to implement each of the collections classes. My
assignment is to implement a priority queue class in four different ways. Those are:

•Unsorted Vector. The elements in the priority queue are stored unsorted in a Vector.

•Sorted linked list. The elements are stored in a sorted, singly-linked list.

•Unsorted linked list. The elements are stored in an unsorted, doubly-linked list.

•Binary heap. The elements are stored in a binary heap, a specialized data structure well-suited
to priority queues.

### Prerequisites
Ensure you have the following installed on your machine:

- [Java Development Kit (JDK)](https://www.oracle.com/java/technologies/downloads/#java17) (version 17)
- g++ 


## Running Tests

To build the program, run the following command

```bash
  rm *.o libStanfordCPPLib.a PriorityQueue
  make
```

To run the test, run the following command (before running ensure the program is built)
```bash
./PriorityQueue
```

