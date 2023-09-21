#pragma once

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

#include "TestCaseClientDetails.hxx"

class FriendInvitationListenerImplGlobal : public galaxy::api::GlobalFriendInvitationListener
{
public:
	using on_friend_invitation_received_func_t = std::function<void(GalaxyID userID, uint32_t sendTime)>;

private:
	on_friend_invitation_received_func_t on_friend_invitation_received;

public:
	FriendInvitationListenerImplGlobal(
		on_friend_invitation_received_func_t on_friend_invitation_received = nullptr) :
		on_friend_invitation_received{ on_friend_invitation_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendInvitationListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationReceived(GalaxyID userID, uint32_t sendTime) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} sendTime: {}",
			userID, sendTime
		).c_str());


		if (on_friend_invitation_received != nullptr) {
			on_friend_invitation_received(userID, sendTime);
		}
	}
};

class FriendInvitationListenerImplLocal : public galaxy::api::IFriendInvitationListener
{
public:
	using on_friend_invitation_received_func_t = std::function<void(GalaxyID userID, uint32_t sendTime)>;

private:
	on_friend_invitation_received_func_t on_friend_invitation_received;

public:
	FriendInvitationListenerImplLocal(
		on_friend_invitation_received_func_t on_friend_invitation_received = nullptr) :
		on_friend_invitation_received{ on_friend_invitation_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendInvitationListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendInvitationReceived(GalaxyID userID, uint32_t sendTime) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} sendTime: {}",
			userID, sendTime
		).c_str());


		if (on_friend_invitation_received != nullptr) {
			on_friend_invitation_received(userID, sendTime);
		}
	}
};

#endif
