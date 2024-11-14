






// Conversation.h

#pragma once
#include "Fragment.h"
#include <unordered_map>
#include <string>
#include <sstream>
#include <stdexcept>

// Class representing a conversation that holds fragments
class Conversation {
private:
	// Node structure for linked list of fragments
	struct Node {
		Fragment* data; // Pointer to the Fragment data
		Node* next;     // Pointer to the next node in the list

		// Constructor to initialize a Node with a Fragment
		Node(Fragment* fragment);
	};

	Node* head; // Pointer to the head of the linked list
	int conversationId; // Unique identifier for the conversation
	std::unordered_map<int, Node*> fragmentMap;
public:
	explicit Conversation(int convId); // Constructor with conversation ID
	~Conversation(); // Destructor to clean up allocated memory

	bool canAddFragment(Fragment* fragment) const; // Check if a fragment can be added
	void addFragment(Fragment* fragment); // Add a fragment to the conversation
	int getConversationId() const; // Get the conversation ID
	std::string toString() const; // Convert conversation details to string format
};