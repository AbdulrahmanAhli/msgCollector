#include "ChatController.h"
#include <random>
#include <iostream>

int main()
{

	ChatController controller("conversation.txt");
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(5, 10); // Random number generate between 5 & 10

	bool hasMoreData = true;	// denotes whether there is any more fragments yet to be processed
	int iterationCount = 0;

	while (hasMoreData)
	{
		if (controller.isQueueEmpty() && controller.isFileEOF())	//check if all fragments exhausted
		{
			std::cout << "\nAll conversations have been processed.\n";
			break;
		}
		iterationCount++;
		int N = dis(gen); // Read 5-10 fragments each time randomly
		std::cout << "\nIteration " << iterationCount << ": Reading " << N << " fragments...\n";

		// Try to read new fragments
		controller.readFragments(N);

		// If queue is empty and no more file data, we're done
		if (controller.isQueueEmpty() && controller.isFileEOF())
		{
			std::cout << "\nAll conversations have been processed.\n";
			break;
		}
		else
		{
			// Process whatever is in the queue
			controller.processQueue();
			std::cout << "\nCurrent state of conversations:\n";
			controller.printConversations();
		}
	}

	return 0;
}
