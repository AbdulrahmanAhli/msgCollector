// ConversationList.cpp

#include "ConversationList.h"

// Initialize an empty ConversationList
ConversationList::ConversationList() {}

// Destructor that deletes all conversations in the list
ConversationList::~ConversationList() {
	for (Conversation* conv : conversations) {
		delete conv; // Free memory for each Conversation object
	}
}

// Find and return a Conversation by its ID, or nullptr if not found
Conversation* ConversationList::findConversation(int conversationId) {
	for (Conversation* conv : conversations) {
		if (conv && conv->getConversationId() == conversationId) {
			return conv; // Return the matching Conversation
		}
	}
	return nullptr; // Return nullptr if not found
}

// Add a new Conversation to the list, throwing an error if null or max size reached
void ConversationList::addConversation(Conversation* conversation) {
	if (!conversation) {
		throw std::invalid_argument("Cannot add null conversation"); // Validate input
	}

	if (conversations.size() >= MAX_CONVERSATIONS) {
		throw std::runtime_error("Maximum number of conversations reached"); // Check size limit
	}

	conversations.push_back(conversation); // Add the conversation to the vector
}

// Print details of all stored conversations to standard output
void ConversationList::printConversations() const {
	for (const Conversation* conv : conversations) {
		if (conv) {
			std::cout << conv->toString() << "\n"; // Output string representation of each conversation
		}
	}
}

// Return the current number of conversations in the list
size_t ConversationList::size() const {
	return conversations.size(); // Return size of the vector
}
