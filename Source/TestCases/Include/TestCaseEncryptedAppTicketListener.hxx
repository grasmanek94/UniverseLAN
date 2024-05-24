#pragma once

#include "TestCaseClientDetails.hxx"

#if GALAXY_BUILD_FEATURE_ENCRYPTED_APP_TICKET
class EncryptedAppTicketListenerImplGlobal : public galaxy::api::GlobalEncryptedAppTicketListener
{
public:
	using on_encrypted_app_ticket_retrieve_success_func_t = std::function<void()>;
	using on_encrypted_app_ticket_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_encrypted_app_ticket_retrieve_success_func_t on_encrypted_app_ticket_retrieve_success;
	on_encrypted_app_ticket_retrieve_failure_func_t on_encrypted_app_ticket_retrieve_failure;

public:
	EncryptedAppTicketListenerImplGlobal(
		on_encrypted_app_ticket_retrieve_success_func_t on_encrypted_app_ticket_retrieve_success = nullptr,
		on_encrypted_app_ticket_retrieve_failure_func_t on_encrypted_app_ticket_retrieve_failure = nullptr) :
		on_encrypted_app_ticket_retrieve_success{ on_encrypted_app_ticket_retrieve_success },
		on_encrypted_app_ticket_retrieve_failure{ on_encrypted_app_ticket_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~EncryptedAppTicketListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnEncryptedAppTicketRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_encrypted_app_ticket_retrieve_success != nullptr) {
			on_encrypted_app_ticket_retrieve_success();
		}
	}

	virtual void OnEncryptedAppTicketRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_encrypted_app_ticket_retrieve_failure != nullptr) {
			on_encrypted_app_ticket_retrieve_failure(failureReason);
		}
	}
};

class EncryptedAppTicketListenerImplLocal : public galaxy::api::IEncryptedAppTicketListener
{
public:
	using on_encrypted_app_ticket_retrieve_success_func_t = std::function<void()>;
	using on_encrypted_app_ticket_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_encrypted_app_ticket_retrieve_success_func_t on_encrypted_app_ticket_retrieve_success;
	on_encrypted_app_ticket_retrieve_failure_func_t on_encrypted_app_ticket_retrieve_failure;

public:
	EncryptedAppTicketListenerImplLocal(
		on_encrypted_app_ticket_retrieve_success_func_t on_encrypted_app_ticket_retrieve_success = nullptr,
		on_encrypted_app_ticket_retrieve_failure_func_t on_encrypted_app_ticket_retrieve_failure = nullptr) :
		on_encrypted_app_ticket_retrieve_success{ on_encrypted_app_ticket_retrieve_success },
		on_encrypted_app_ticket_retrieve_failure{ on_encrypted_app_ticket_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~EncryptedAppTicketListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnEncryptedAppTicketRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_encrypted_app_ticket_retrieve_success != nullptr) {
			on_encrypted_app_ticket_retrieve_success();
		}
	}

	virtual void OnEncryptedAppTicketRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_encrypted_app_ticket_retrieve_failure != nullptr) {
			on_encrypted_app_ticket_retrieve_failure(failureReason);
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerEncryptedAppTicketListenerImplGlobal : public galaxy::api::GameServerGlobalEncryptedAppTicketListener
{
public:
	using on_encrypted_app_ticket_retrieve_success_func_t = std::function<void()>;
	using on_encrypted_app_ticket_retrieve_failure_func_t = std::function<void(FailureReason)>;

private:
	on_encrypted_app_ticket_retrieve_success_func_t on_encrypted_app_ticket_retrieve_success;
	on_encrypted_app_ticket_retrieve_failure_func_t on_encrypted_app_ticket_retrieve_failure;

public:
	GameServerEncryptedAppTicketListenerImplGlobal(
		on_encrypted_app_ticket_retrieve_success_func_t on_encrypted_app_ticket_retrieve_success = nullptr,
		on_encrypted_app_ticket_retrieve_failure_func_t on_encrypted_app_ticket_retrieve_failure = nullptr) :
		on_encrypted_app_ticket_retrieve_success{ on_encrypted_app_ticket_retrieve_success },
		on_encrypted_app_ticket_retrieve_failure{ on_encrypted_app_ticket_retrieve_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerEncryptedAppTicketListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnEncryptedAppTicketRetrieveSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };


		if (on_encrypted_app_ticket_retrieve_success != nullptr) {
			on_encrypted_app_ticket_retrieve_success();
		}
	}

	virtual void OnEncryptedAppTicketRetrieveFailure(FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"failureReason: {}",
			magic_enum::enum_name(failureReason)
		).c_str());


		if (on_encrypted_app_ticket_retrieve_failure != nullptr) {
			on_encrypted_app_ticket_retrieve_failure(failureReason);
		}
	}
};

#endif
#endif