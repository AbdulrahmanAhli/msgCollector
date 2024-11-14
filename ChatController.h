#pragma once
#include "FragmentQueue.h"
#include "ConversationList.h"
#include <fstream>
#include <string>
#include <memory>

class ChatController {
private:
	std::ifstream fileStream;       // File stream for reading input data from a file 
	FragmentQueue fragmentQueue;     // Queue for managing incoming Fragments  
	ConversationList conversationList;// List of active conversations being managed  

	const int MAX_REQUEUE_ATTEMPTS = 100;  // Maximum allowed attempts for requeuing Fragments before discarding them  
	int requeueCount;                     // Counter tracking how many times a Fragment has been requeued 

public:
	explicit ChatController(const std::string& filename);   // Constructor that initializes controller with input filename  
	~ChatController();                                     // Destructor that cleans up resources 

	void readFragments(int N);     // Read N Fragments from input file and enqueue them  
	void processQueue();          // Process Fragments in queue until empty or max attempts reached  
	void printConversations();               // Print all conversations stored so far 

	bool isQueueEmpty() const;       // Check whether the Fragment queue is empty  
	bool isFileEOF() const;  // Check whether end of file has been reached during reading 

private:
	bool handleFragment(Fragment* fragment);              // Handle adding a single Fragment into its corresponding Conversation  
};


