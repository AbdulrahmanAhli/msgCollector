

#include "FragmentQueue.h"

// Initialize an empty queue with front and rear pointers set to nullptr and size to 0
FragmentQueue::FragmentQueue() : front(nullptr), rear(nullptr), size(0) {}

// Destructor that dequeues all fragments and deletes them to free memory
FragmentQueue::~FragmentQueue() {
	while (!isEmpty()) {
		Fragment* fragment = dequeue(); // Dequeue each fragment
		delete fragment;	// Delete the fragment to free memory
	}
}

// Add a new Fragment to the rear of the queue
void FragmentQueue::enqueue(Fragment* fragment) {
	if (!fragment) {
		throw std::invalid_argument("Cannot enqueue null fragment"); // Ensure fragment is not null
	}

	if (isFull()) {
		throw std::runtime_error("Queue is full"); // Check if queue has reached its max size
	}
	

	Node* newNode = new Node(fragment); // Create a new node for the fragment
	if (!newNode) {
		throw std::bad_alloc(); // Handle memory allocation failure for new node
	}

	if (isEmpty()) {
		front = newNode; // If queue is empty, set front to new node
	}
	else {
		rear->next = newNode; // Link new node at the end of the queue
	}

	rear = newNode; // Update rear pointer to point to new node
	size++;		// Increment size of the queue
}

// Remove and return a Fragment from the front of the queue
Fragment* FragmentQueue::dequeue() {
	if (isEmpty()) return nullptr; // Return null if queue is empty

	Node* temp = front;		// Store current front node for deletion
	Fragment* fragment = temp->data; // Get data from front node

	front = front->next; // Move front pointer to next node

	if (front == nullptr) { // If queue becomes empty, update rear pointer as well
		rear = nullptr;
	}

	delete temp;// Delete old front node to free memory
	size--;	// Decrement size of the queue
	return fragment;	// Return dequeued fragment
}

// Check if the queue is empty by comparing size with zero
bool FragmentQueue::isEmpty() const { return size == 0; }

// Check if the queue is full by comparing size with maximum allowed size
bool FragmentQueue::isFull() const { return size >= MAX_QUEUE_SIZE; }

// Return current number of elements in the queue
int FragmentQueue::getSize() const { return size; }
