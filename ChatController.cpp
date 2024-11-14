
#include "ChatController.h"
#include <sstream>

// Constructor initializes ChatController and opens file stream for reading fragments from a file 
ChatController::ChatController(const std::string& filename) : requeueCount(0) {
	fileStream.open(filename); // Open specified file for reading fragments

	if (!fileStream.is_open()) {
		throw std::runtime_error("Could not open file: " + filename); // Throw error if file cannot be opened 
	}
}

// Destructor closes file stream if it is open 
ChatController::~ChatController() {
	if (fileStream.is_open()) {
		fileStream.close(); // Close file stream on destruction 
	}
}

// Read N fragments from the input file and enqueue them into the fragment queue 
void ChatController::readFragments(int N) {
	std::string line;
	int count = 0;

	while (count < N && std::getline(fileStream, line)) { // Read lines until N fragments are read or EOF reached 
		try {
			int conversationId, sequenceNumber, messageLength;
			std::stringstream ss(line);

			if (!(ss >> conversationId >> sequenceNumber >> messageLength)) {
				continue; // Skip malformed lines that do not contain valid data 
			}

			std::string message;
			if (std::getline(fileStream, message)) {
				auto fragment = new Fragment(conversationId, sequenceNumber,
					messageLength, message); // Create a new Fragment object 
				fragmentQueue.enqueue(fragment); // Enqueue created Fragment into queue 
				count++; // Increment count of successfully read fragments 
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Error processing fragment: " << e.what() << std::endl;
			continue; // Log error and continue processing next line 
		}
	}
}

// Handle adding a Fragment to its corresponding Conversation or create one if it doesn't exist 
bool ChatController::handleFragment(Fragment* fragment) {
	if (!fragment) return false;

	try {
		Conversation* conversation = conversationList.findConversation(
			fragment->getConversationId());

		if (!conversation) {
			conversation = new Conversation(fragment->getConversationId());
			conversationList.addConversation(conversation); // Create and add new Conversation if it doesn't exist 
		}

		if (conversation->canAddFragment(fragment)) {
			conversation->addFragment(fragment);	// Add Fragment to Conversation 
			requeueCount = 0;	// Reset requeue count on successful addition 
			return true;// Return success status 
		}

	}
	catch (const std::exception& e) {
		std::cerr << "Error handling fragment: " << e.what() << std::endl;
		delete fragment;// Clean up memory on error 
		return false;
	}

	return false;	// Return failure status if unable to handle Fragment 
}

// Process all Fragments in the queue until it's empty or max requeue attempts reached 
void ChatController::processQueue() {
	while (!fragmentQueue.isEmpty()) {
		Fragment* fragment = fragmentQueue.dequeue();

		if (!handleFragment(fragment)) {// Attempt to handle dequeued Fragment 
			requeueCount++;// Increment requeue count on failure 

			if (requeueCount >= MAX_REQUEUE_ATTEMPTS) {// Check against max requeue attempts limit 
				std::cerr << "Maximum requeue attempts reached for fragment. Discarding.\n";
				delete fragment;// Discard Fragment after max attempts reached  
				requeueCount = 0;// Reset requeue count  
			}
			else {
				try {
					fragmentQueue.enqueue(fragment);// Re-enqueue failed Fragment for future processing  
				}
				catch (const std::exception& e) {
					std::cerr << "Failed to requeue fragment: " << e.what() << std::endl;
					delete fragment;// Clean up memory on failure to requeue  
				}
			}
		}
	}
}

// Check if the Fragment queue is empty 
bool ChatController::isQueueEmpty() const {
	return fragmentQueue.isEmpty(); // Return result of queue empty check  
}

// Check if end of file has been reached during reading process 
bool ChatController::isFileEOF() const {
	return fileStream.eof();// Return result of EOF check on file stream  
}

void ChatController::printConversations() {
	conversationList.printConversations();// Call method to print conversations  
}

