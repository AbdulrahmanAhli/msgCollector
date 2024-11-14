// Fragment.cpp

#include "Fragment.h"

Fragment::Fragment(int convId, int seqNum, int msgLen, const std::string& msg)
	: conversationId(convId), sequenceNumber(seqNum), messageLength(msgLen), message(msg) {}

int Fragment::getConversationId() const { return conversationId; }
int Fragment::getSequenceNumber() const { return sequenceNumber; }
int Fragment::getMessageLength() const { return messageLength; }
const std::string& Fragment::getMessage() const { return message; }





