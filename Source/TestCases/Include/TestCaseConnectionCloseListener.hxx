#pragma once

#include "TestCaseClientDetails.hxx"

class ConnectionCloseListenerImplGlobal : public galaxy::api::GlobalConnectionCloseListener
{
public:
	using on_connection_closed_func_t = std::function<void(ConnectionID, CloseReason)>;

private:
	on_connection_closed_func_t on_connection_closed;

public:
	ConnectionCloseListenerImplGlobal(
		on_connection_closed_func_t on_connection_closed = nullptr) :
		on_connection_closed{ on_connection_closed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ConnectionCloseListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionClosed(ConnectionID connectionID, CloseReason closeReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionID: {} closeReason: {}",
			connectionID, magic_enum::enum_name(closeReason)
		).c_str());


		if (on_connection_closed != nullptr) {
			on_connection_closed(connectionID, closeReason);
		}
	}
};

class ConnectionCloseListenerImplLocal : public galaxy::api::IConnectionCloseListener
{
public:
	using on_connection_closed_func_t = std::function<void(ConnectionID, CloseReason)>;

private:
	on_connection_closed_func_t on_connection_closed;

public:
	ConnectionCloseListenerImplLocal(
		on_connection_closed_func_t on_connection_closed = nullptr) :
		on_connection_closed{ on_connection_closed } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ConnectionCloseListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionClosed(ConnectionID connectionID, CloseReason closeReason) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionID: {} closeReason: {}",
			connectionID, magic_enum::enum_name(closeReason)
		).c_str());


		if (on_connection_closed != nullptr) {
			on_connection_closed(connectionID, closeReason);
		}
	}
};
