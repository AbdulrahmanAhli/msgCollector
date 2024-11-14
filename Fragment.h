#pragma once
#include <string>

class Fragment {
private:
	int conversationId;
	int sequenceNumber;
	int messageLength;
	std::string message;

public:
	Fragment(int convId, int seqNum, int msgLen, const std::string& msg);
	int getConversationId() const;
	int getSequenceNumber() const;
	int getMessageLength() const;
	const std::string& getMessage() const;
};