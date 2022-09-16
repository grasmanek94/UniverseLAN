#pragma once

#include "Messages/EventConnect.hxx"
#include "Messages/EventDisconnect.hxx"

#include "Messages/ConnectionAccepted.hxx"
#include "Messages/KeyChallenge.hxx"
#include "Messages/UserHelloDataMessage.hxx"

#define SHARED_NETWORK_DECLARE_MESSAGE_FOR(class_name) \
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<class_name>& data) = 0

#define SHARED_NETWORK_OVERRIDE_MESSAGE_FOR(class_name) \
		virtual void Handle(ENetPeer* peer, const std::shared_ptr<class_name>& data) override

#define SHARED_NETWORK_IMPLEMENT_ALL_CASES() \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(ConnectionAccepted); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(KeyChallenge); \
	SHARED_NETWORK_IMPLEMENT_CASE_FOR(UserHelloDataMessage)

#define SHARED_NETWORK_DECLARE_MESSAGE_HANDLERS() \
	SHARED_NETWORK_DECLARE_MESSAGE_FOR(ConnectionAccepted); \
	SHARED_NETWORK_DECLARE_MESSAGE_FOR(KeyChallenge); \
	SHARED_NETWORK_DECLARE_MESSAGE_FOR(UserHelloDataMessage)

#define SHARED_NETWORKOVERRIDE_MESSAGE_HANDLERS() \
	SHARED_NETWORK_OVERRIDE_MESSAGE_FOR(ConnectionAccepted); \
	SHARED_NETWORK_OVERRIDE_MESSAGE_FOR(KeyChallenge); \
	SHARED_NETWORK_OVERRIDE_MESSAGE_FOR(UserHelloDataMessage)
