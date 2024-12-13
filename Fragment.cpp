#include "Fragment.h"

int Fragment::getConversationId() const {
    return conversationId;
}

int Fragment::getSequenceNumber() const {
    return sequenceNumber;
}

int Fragment::getMessageLength() const {
    return messageLength;
}

const std::string& Fragment::getMessage() const {
    return message;
}

int Fragment::getWeight() const {
    return weight;
}
