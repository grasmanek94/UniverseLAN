#pragma once

#include "TestCaseClientDetails.hxx"

#if GALAXY_BUILD_FEATURE_HAS_ICUSTOMNETWORKING
class ConnectionDataListenerImplGlobal : public galaxy::api::GlobalConnectionDataListener
{
public:
	using on_connection_data_received_func_t = std::function<void(ConnectionID, uint32_t dataSize)>;

private:
	on_connection_data_received_func_t on_connection_data_received;

public:
	ConnectionDataListenerImplGlobal(
		on_connection_data_received_func_t on_connection_data_received = nullptr) :
		on_connection_data_received{ on_connection_data_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ConnectionDataListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionDataReceived(ConnectionID connectionID, uint32_t dataSize) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionID: {} dataSize: {}",
			connectionID, dataSize
		).c_str());


		if (on_connection_data_received != nullptr) {
			on_connection_data_received(connectionID, dataSize);
		}
	}
};

class ConnectionDataListenerImplLocal : public galaxy::api::IConnectionDataListener
{
public:
	using on_connection_data_received_func_t = std::function<void(ConnectionID, uint32_t dataSize)>;

private:
	on_connection_data_received_func_t on_connection_data_received;

public:
	ConnectionDataListenerImplLocal(
		on_connection_data_received_func_t on_connection_data_received = nullptr) :
		on_connection_data_received{ on_connection_data_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~ConnectionDataListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnConnectionDataReceived(ConnectionID connectionID, uint32_t dataSize) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"connectionID: {} dataSize: {}",
			connectionID, dataSize
		).c_str());


		if (on_connection_data_received != nullptr) {
			on_connection_data_received(connectionID, dataSize);
		}
	}
};
#endif
