#pragma once

#include "TestCaseClientDetails.hxx"

class ConnectionOpenListenerImplGlobal : public galaxy::api::GlobalConnectionOpenListener
{
public:
	using on_connection_open_success_func_t = std::function<void(const char* connectionString, ConnectionID)>;
	using on_connection_open_failure_func_t = std::function<void(const char* connectionString, FailureReason)>;

private:
	on_connection_open_success_func_t on_connection_open_success;
	on_connection_open_failure_func_t on_connection_open_failure;

public:
	ConnectionOpenListenerImplGlobal(
		on_connection_open_success_func_t on_connection_open_success = nullptr,
		on_connection_open_failure_func_t on_connection_open_failure = nullptr) :
		on_connection_open_success{ on_connection_open_success },
		on_connection_open_failure{ on_connection_open_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ConnectionOpenListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionOpenSuccess(const char* connectionString, ConnectionID connectionID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionString: {} connectionID: {}",
			connectionString, connectionID
		).c_str());


		if (on_connection_open_success != nullptr) {
			on_connection_open_success(connectionString, connectionID);
		}
	}

	virtual void OnConnectionOpenFailure(const char* connectionString, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionString: {} failureReason: {}",
			connectionString, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_connection_open_failure != nullptr) {
			on_connection_open_failure(connectionString, failureReason);
		}
	}
};

class ConnectionOpenListenerImplLocal : public galaxy::api::IConnectionOpenListener
{
public:
	using on_connection_open_success_func_t = std::function<void(const char* connectionString, ConnectionID)>;
	using on_connection_open_failure_func_t = std::function<void(const char* connectionString, FailureReason)>;

private:
	on_connection_open_success_func_t on_connection_open_success;
	on_connection_open_failure_func_t on_connection_open_failure;

public:
	ConnectionOpenListenerImplLocal(
		on_connection_open_success_func_t on_connection_open_success = nullptr,
		on_connection_open_failure_func_t on_connection_open_failure = nullptr) :
		on_connection_open_success{ on_connection_open_success },
		on_connection_open_failure{ on_connection_open_failure } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ConnectionOpenListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionOpenSuccess(const char* connectionString, ConnectionID connectionID) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionString: {} connectionID: {}",
			connectionString, connectionID
		).c_str());


		if (on_connection_open_success != nullptr) {
			on_connection_open_success(connectionString, connectionID);
		}
	}

	virtual void OnConnectionOpenFailure(const char* connectionString, FailureReason failureReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionString: {} failureReason: {}",
			connectionString, magic_enum::enum_name(failureReason)
		).c_str());


		if (on_connection_open_failure != nullptr) {
			on_connection_open_failure(connectionString, failureReason);
		}
	}
};
