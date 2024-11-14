#include "Conversation.h"

// Initialize a Node with a given Fragment
Conversation::Node::Node(Fragment* fragment) : data(fragment), next(nullptr) {}

// Constructor initializes an empty conversation with a given ID
Conversation::Conversation(int convId)
	: head(nullptr), conversationId(convId) {
}

// Destructor cleans up all nodes in the linked list and their associated fragments
Conversation::~Conversation() {
	Node* current = head;
	while (current != nullptr) {
		Node* temp = current;
		current = current->next;
		delete temp->data; // Delete Fragment data
		delete temp; // Delete Node itself
	}
}

// Check if a fragment can be added based on its sequence number
bool Conversation::canAddFragment(Fragment* fragment) const {
	if (!fragment) {
		throw std::invalid_argument("Cannot add null fragment"); // Ensure fragment is not null
	}
	int seqNum = fragment->getSequenceNumber(); // Get sequence number of the fragment
	return fragmentMap.count(seqNum) == 0; // Return true if sequence number is not already in use
}

// Add a new Fragment to the conversation, replacing if it already exists
void Conversation::addFragment(Fragment* fragment) {
	if (!fragment) {
		throw std::invalid_argument("Cannot add null fragment"); // Ensure fragment is not null
	}

	int seqNum = fragment->getSequenceNumber(); // Get sequence number for checking duplicates
	Node* newNode = new Node(fragment); // Create a new node for the new Fragment

	if (fragmentMap.count(seqNum) == 0) { // If the sequence number is unique
		if (head == nullptr) { // If list is empty, set head to new node
			head = newNode;
		}
		else { // Otherwise, traverse to the end of the list and add it there
			Node* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
		}
		fragmentMap[seqNum] = newNode; // Map the sequence number to the new node
	}
	else { // If sequence number already exists, replace existing Fragment data
		Node* existingNode = fragmentMap[seqNum];
		delete existingNode->data; // Delete old Fragment data to prevent memory leak
		existingNode->data = fragment; // Update with new Fragment data
		delete newNode; // No need for new node since we're reusing existing one
	}
}

// Return the unique identifier for this conversation
int Conversation::getConversationId() const {
	return conversationId;
}

// Convert conversation details into a string representation for display purposes
std::string Conversation::toString() const {
	std::stringstream ss;
	ss << "Conversation " << conversationId << ":\n"; // Start with conversation ID header
	Node* current = head; // Start from head of linked list

	while (current != nullptr) { // Traverse through all fragments in the conversation
		ss << "  Fragment " << current->data->getSequenceNumber()
			<< ": " << current->data->getMessage() << "\n"; // Append each fragment's details to stringstream
		current = current->next; // Move to next node in the list
	}

	return ss.str(); // Return constructed string representation of conversation details
}


