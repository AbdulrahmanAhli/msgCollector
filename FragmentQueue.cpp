#include "FragmentQueue.h"

// Initialize an empty queue
FragmentQueue::FragmentQueue() : front(nullptr), rear(nullptr), size(0) {}

// Destructor to free memory
FragmentQueue::~FragmentQueue() {
    while (!isEmpty()) {
        Fragment* fragment = dequeue();
        delete fragment;
    }
}

// Add a new Fragment based on its weight
void FragmentQueue::enqueue(Fragment* fragment) {
    if (!fragment) {
        throw std::invalid_argument("Cannot enqueue null fragment");
    }

    if (isFull()) {
        throw std::runtime_error("Queue is full");
    }

    Node* newNode = new Node(fragment);
    if (!newNode) {
        throw std::bad_alloc();
    }

    // If the queue is empty, add as the only node
    if (isEmpty()) {
        front = rear = newNode;
    }
    // Insert at the front if the fragment has the highest weight
    else if (fragment->getWeight() > front->data->getWeight()) {
        newNode->next = front;
        front = newNode;
    }
    else {
        // Find the correct position
        Node* current = front;
        while (current->next != nullptr &&
            current->next->data->getWeight() >= fragment->getWeight()) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;

        // Update rear if new node is added at the end
        if (newNode->next == nullptr) {
            rear = newNode;
        }
    }
    size++;
}

// Remove and return the highest-weight Fragment
Fragment* FragmentQueue::dequeue() {
    if (isEmpty()) return nullptr;

    Node* temp = front;
    Fragment* fragment = temp->data;

    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    size--;
    return fragment;
}

// Check if the queue is empty
bool FragmentQueue::isEmpty() const { return size == 0; }

// Check if the queue is full
bool FragmentQueue::isFull() const { return size >= MAX_QUEUE_SIZE; }

// Return current size of the queue
int FragmentQueue::getSize() const { return size; }
