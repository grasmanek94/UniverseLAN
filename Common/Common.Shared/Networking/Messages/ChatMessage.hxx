#pragma once
#include <Networking/SendableEventMessage.hxx>
#include <string>

class ChatMessage
{
private:
	std::wstring message;
	size_t sender;

public:
	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(message, sender);
	}

	UniqueClassId_Declare(ChatMessage);

	ChatMessage();

	const std::wstring GetContents() const;
	const size_t GetSender() const;

	void SetContents(const std::wstring& msg);
	void SetSender(size_t id);
};
