#include "ChatController.h"
#include <random>
#include <iostream>

int main() {
    try {
        // Initialize ChatController with input file
        ChatController controller("conversation.txt");

        // Random number generator setup
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(5, 10);  // Random read size between 5 and 10

        bool hasMoreData = true;
        int iterationCount = 0;

        // Main processing loop
        while (hasMoreData) {
            // Check if processing is done
            if (controller.isQueueEmpty() && controller.isFileEOF()) {
                std::cout << "\nAll conversations have been processed.\n";
                break;
            }

            iterationCount++;
            int N = dis(gen);  // Random number of fragments to read
            std::cout << "\nIteration " << iterationCount << ": Reading " << N << " fragments...\n";

            // Read new fragments from file into queue
            controller.readFragments(N);

            // Check again if the queue is empty after reading
            if (controller.isQueueEmpty() && controller.isFileEOF()) {
                std::cout << "\nAll conversations have been processed.\n";
                break;
            }
            else {
                // Process queue based on fragment weight
                controller.processQueue();

                std::cout << "\nCurrent state of conversations:\n";
                controller.printConversations();
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
