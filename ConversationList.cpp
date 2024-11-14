// ConversationList.h

#pragma once
#include "Conversation.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>

// Class to manage a list of conversations
class ConversationList {
private:
	std::vector<Conversation*> conversations; // Vector to store pointers to Conversation objects
	const size_t MAX_CONVERSATIONS = 1000; // Maximum allowed number of conversations

public:
	ConversationList(); // Constructor to initialize an empty conversation list
	~ConversationList(); // Destructor to clean up allocated Conversation objects

	Conversation* findConversation(int conversationId); // Find a conversation by its ID
	void addConversation(Conversation* conversation); // Add a new conversation to the list
	void printConversations() const; // Print details of all conversations in the list
	size_t size() const; // Return the current number of conversations in the list
};