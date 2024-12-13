#include "ChatController.h"
#include <sstream>
#include <iostream>

// Constructor initializes ChatController and opens file stream for reading fragments from a file 
ChatController::ChatController(const std::string& filename) : requeueCount(0) {
    fileStream.open(filename);

    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
}

// Destructor closes file stream if it is open 
ChatController::~ChatController() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

// Read N fragments from the input file and enqueue them based on weight 
void ChatController::readFragments(int N) {
    std::string line;
    int count = 0;

    while (count < N && std::getline(fileStream, line)) {
        try {
            int conversationId, sequenceNumber, messageLength;
            std::stringstream ss(line);

            if (!(ss >> conversationId >> sequenceNumber >> messageLength)) {
                continue; // Skip malformed lines
            }

            std::string message;
            if (std::getline(fileStream, message)) {
                // Assign weight (customizable logic here)
                auto fragment = new Fragment(conversationId, sequenceNumber, messageLength, message);

                // Weighted enqueue
                fragmentQueue.enqueue(fragment);
                count++;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error processing fragment: " << e.what() << std::endl;
        }
    }
}

// Handle adding a Fragment to its corresponding Conversation or create one if it doesn't exist 
bool ChatController::handleFragment(Fragment* fragment) {
    if (!fragment) return false;

    try {
        Conversation* conversation = conversationList.findConversation(fragment->getConversationId());

        if (!conversation) {
            conversation = new Conversation(fragment->getConversationId());
            conversationList.addConversation(conversation);
        }

        if (conversation->canAddFragment(fragment)) {
            conversation->addFragment(fragment);
            requeueCount = 0;
            return true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling fragment: " << e.what() << std::endl;
    }

    delete fragment; // Cleanup on failure
    return false;
}

// Process all fragments in the queue until empty or max requeue attempts reached 
void ChatController::processQueue() {
    while (!fragmentQueue.isEmpty()) {
        Fragment* fragment = fragmentQueue.dequeue();

        if (!handleFragment(fragment)) {
            requeueCount++;

            if (requeueCount >= MAX_REQUEUE_ATTEMPTS) {
                std::cerr << "Maximum requeue attempts reached. Discarding fragment.\n";
                delete fragment;
                requeueCount = 0;
            }
            else {
                try {
                    // Re-enqueue the fragment with weight consideration
                    fragmentQueue.enqueue(fragment);
                }
                catch (const std::exception& e) {
                    std::cerr << "Failed to requeue fragment: " << e.what() << std::endl;
                    delete fragment;
                }
            }
        }
    }
}

// Check if the Fragment queue is empty 
bool ChatController::isQueueEmpty() const {
    return fragmentQueue.isEmpty();
}

// Check if end of file has been reached during reading process 
bool ChatController::isFileEOF() const {
    return fileStream.eof();
}

// Print current conversations 
void ChatController::printConversations() {
    conversationList.printConversations();
}
