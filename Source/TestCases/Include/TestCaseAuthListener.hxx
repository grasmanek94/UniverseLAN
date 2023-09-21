#pragma once

#include "TestCaseClientDetails.hxx"

class AuthListenerImplGlobal : public galaxy::api::GlobalAuthListener
{
public:
	using on_auth_success_func_t = std::function<void(void)>;
	using on_auth_failure_func_t = std::function<void(FailureReason)>;
	using on_auth_lost_func_t = std::function<void(void)>;

private:
	on_auth_success_func_t on_auth_success;
	on_auth_failure_func_t on_auth_failure;
	on_auth_lost_func_t on_auth_lost;

public:
	AuthListenerImplGlobal(
		on_auth_success_func_t on_auth_success = nullptr,
		on_auth_failure_func_t on_auth_failure = nullptr,
		on_auth_lost_func_t on_auth_lost = nullptr) :
		on_auth_success{ on_auth_success },
		on_auth_failure{ on_auth_failure },
		on_auth_lost{ on_auth_lost } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~AuthListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAuthSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_auth_success) {
			on_auth_success();
		}
	}

	virtual void OnAuthFailure(FailureReason reason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"reason: {}",
			magic_enum::enum_name(reason)
		).c_str());

		if (on_auth_failure) {
			on_auth_failure(reason);
		}
	}

	virtual void OnAuthLost() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_auth_lost) {
			on_auth_lost();
		}
	}
};

class AuthListenerImplLocal : public galaxy::api::IAuthListener
{
public:
	using on_auth_success_func_t = std::function<void(void)>;
	using on_auth_failure_func_t = std::function<void(FailureReason)>;
	using on_auth_lost_func_t = std::function<void(void)>;

private:
	on_auth_success_func_t on_auth_success;
	on_auth_failure_func_t on_auth_failure;
	on_auth_lost_func_t on_auth_lost;

public:
	AuthListenerImplLocal(
		on_auth_success_func_t on_auth_success = nullptr,
		on_auth_failure_func_t on_auth_failure = nullptr,
		on_auth_lost_func_t on_auth_lost = nullptr) :
		on_auth_success{ on_auth_success },
		on_auth_failure{ on_auth_failure },
		on_auth_lost{ on_auth_lost } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~AuthListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAuthSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_auth_success) {
			on_auth_success();
		}
	}

	virtual void OnAuthFailure(FailureReason reason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"reason: {}",
			magic_enum::enum_name(reason)
		).c_str());

		if (on_auth_failure) {
			on_auth_failure(reason);
		}
	}

	virtual void OnAuthLost() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_auth_lost) {
			on_auth_lost();
		}
	}
};

#if GALAXY_BUILD_FEATURE_GAME_SERVER_API

class GameServerAuthListenerImplGlobal : public galaxy::api::GameServerGlobalAuthListener
{
public:
	using on_auth_success_func_t = std::function<void(void)>;
	using on_auth_failure_func_t = std::function<void(FailureReason)>;
	using on_auth_lost_func_t = std::function<void(void)>;

private:
	on_auth_success_func_t on_auth_success;
	on_auth_failure_func_t on_auth_failure;
	on_auth_lost_func_t on_auth_lost;

public:
	GameServerAuthListenerImplGlobal(
		on_auth_success_func_t on_auth_success = nullptr,
		on_auth_failure_func_t on_auth_failure = nullptr,
		on_auth_lost_func_t on_auth_lost = nullptr) :
		on_auth_success{ on_auth_success },
		on_auth_failure{ on_auth_failure },
		on_auth_lost{ on_auth_lost } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~GameServerAuthListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnAuthSuccess() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_auth_success) {
			on_auth_success();
		}
	}

	virtual void OnAuthFailure(FailureReason reason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"reason: {}",
			magic_enum::enum_name(reason)
		).c_str());

		if (on_auth_failure) {
			on_auth_failure(reason);
		}
	}

	virtual void OnAuthLost() {
		tracer::Trace trace{ "", __FUNCTION__ };

		if (on_auth_lost) {
			on_auth_lost();
		}
	}
};

#endif
