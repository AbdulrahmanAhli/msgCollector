#pragma once
#include <string>

class Fragment {
private:
    int conversationId;
    int sequenceNumber;
    int messageLength;
    std::string message;
    int weight;  // New attribute for weight

public:
    // Constructor with weight initialization
    Fragment(int convId, int seqNum, int msgLen, const std::string& msg)
        : conversationId(convId), sequenceNumber(seqNum),
        messageLength(msgLen), message(msg), weight(msgLen) {
        weight = 1000 - sequenceNumber + messageLength;
    }

    // Accessors
    int getConversationId() const;
    int getSequenceNumber() const;
    int getMessageLength() const;
    const std::string& getMessage() const;

    // Getter for the weight
    int getWeight() const;
};
