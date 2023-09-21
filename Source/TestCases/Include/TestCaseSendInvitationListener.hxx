#pragma once

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER

#include "TestCaseClientDetails.hxx"

class SendInvitationListenerImplGlobal : public galaxy::api::GlobalSendInvitationListener
{
public:
	using on_invitation_send_success_func_t = std::function<void(GalaxyID userID, const char* connectionString)>;
	using on_invitation_send_failure_func_t = std::function<void(GalaxyID userID, const char* connectionString, FailureReason)>;

private:
	on_invitation_send_success_func_t on_invitation_send_success;
	on_invitation_send_failure_func_t on_invitation_send_failure;

public:
	SendInvitationListenerImplGlobal(
		on_invitation_send_success_func_t on_invitation_send_success = nullptr,
		on_invitation_send_failure_func_t on_invitation_send_failure = nullptr) :
		on_invitation_send_success{ on_invitation_send_success },
		on_invitation_send_failure{ on_invitation_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~SendInvitationListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnInvitationSendSuccess(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());


		if (on_invitation_send_success != nullptr) {
			on_invitation_send_success(userID, connectionString);
		}
	}

	virtual void OnInvitationSendFailure(GalaxyID userID, const char* connectionString, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {} failureReason: {}",
			userID, connectionString, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_invitation_send_failure != nullptr) {
			on_invitation_send_failure(userID, connectionString, failureReason);
		}
	}
};

class SendInvitationListenerImplLocal : public galaxy::api::ISendInvitationListener
{
public:
	using on_invitation_send_success_func_t = std::function<void(GalaxyID userID, const char* connectionString)>;
	using on_invitation_send_failure_func_t = std::function<void(GalaxyID userID, const char* connectionString, FailureReason)>;

private:
	on_invitation_send_success_func_t on_invitation_send_success;
	on_invitation_send_failure_func_t on_invitation_send_failure;

public:
	SendInvitationListenerImplLocal(
		on_invitation_send_success_func_t on_invitation_send_success = nullptr,
		on_invitation_send_failure_func_t on_invitation_send_failure = nullptr) :
		on_invitation_send_success{ on_invitation_send_success },
		on_invitation_send_failure{ on_invitation_send_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~SendInvitationListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnInvitationSendSuccess(GalaxyID userID, const char* connectionString) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {}",
			userID, connectionString
		).c_str());


		if (on_invitation_send_success != nullptr) {
			on_invitation_send_success(userID, connectionString);
		}
	}

	virtual void OnInvitationSendFailure(GalaxyID userID, const char* connectionString, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"userID: {} connectionString: {} failureReason: {}",
			userID, connectionString, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_invitation_send_failure != nullptr) {
			on_invitation_send_failure(userID, connectionString, failureReason);
		}
	}
};

#endif
