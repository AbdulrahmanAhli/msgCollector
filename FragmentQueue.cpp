// FragmentQueue.h

#pragma once
#include "Fragment.h"
#include <stdexcept>

// Class representing a queue for managing Fragment objects
class FragmentQueue {
private:
	// Node structure to hold Fragment data and the next pointer
	struct Node {
		Fragment* data; // Pointer to the Fragment data
		Node* next;     // Pointer to the next node in the queue

		// Constructor to initialize a Node with a Fragment
		Node(Fragment* fragment) : data(fragment), next(nullptr) {}
	};
	Node* front; // Pointer to the front of the queue
	Node* rear;  // Pointer to the rear of the queue
	int size;    // Current size of the queue
	const int MAX_QUEUE_SIZE = 1000; // Maximum allowed size of the queue

public:
	// Constructor to initialize an empty queue
	FragmentQueue();

	// Destructor to clean up all nodes in the queue
	~FragmentQueue();

	// Method to add a Fragment to the rear of the queue
	void enqueue(Fragment* fragment);

	// Method to remove and return a Fragment from the front of the queue
	Fragment* dequeue();

	// Method to check if the queue is empty
	bool isEmpty() const;

	// Method to get the current size of the queue
	int getSize() const;
	bool isFull() const;
};