#include "ChatMessage.hxx"

ChatMessage::ChatMessage()
{ }

const std::wstring ChatMessage::GetContents() const
{
	return message;
}

void ChatMessage::SetContents(const std::wstring& msg)
{
	message = msg;
}

const size_t ChatMessage::GetSender() const
{
	return sender;
}

void ChatMessage::SetSender(size_t id)
{
	sender = id;
}
