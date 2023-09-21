#pragma once

#include "TestCaseClientDetails.hxx"

#if GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER

class FriendAddListenerImplGlobal : public galaxy::api::GlobalFriendAddListener
{
public:
	using on_friend_added_func_t = std::function<void(GalaxyID userID, InvitationDirection)>;

private:
	on_friend_added_func_t on_friend_added;

public:
	FriendAddListenerImplGlobal(
		on_friend_added_func_t on_friend_added = nullptr) :
		on_friend_added{ on_friend_added } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendAddListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendAdded(GalaxyID userID, InvitationDirection invitationDirection) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} invitationDirection: {}",
			userID, magic_enum::enum_name(invitationDirection)
		).c_str());


		if (on_friend_added != nullptr) {
			on_friend_added(userID, invitationDirection);
		}
	}
};

class FriendAddListenerImplLocal : public galaxy::api::IFriendAddListener
{
public:
	using on_friend_added_func_t = std::function<void(GalaxyID userID, InvitationDirection)>;

private:
	on_friend_added_func_t on_friend_added;

public:
	FriendAddListenerImplLocal(
		on_friend_added_func_t on_friend_added = nullptr) :
		on_friend_added{ on_friend_added } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~FriendAddListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnFriendAdded(GalaxyID userID, InvitationDirection invitationDirection) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} invitationDirection: {}",
			userID, magic_enum::enum_name(invitationDirection)
		).c_str());


		if (on_friend_added != nullptr) {
			on_friend_added(userID, invitationDirection);
		}
	}
};

#endif
