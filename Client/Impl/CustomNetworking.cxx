#include "CustomNetworking.hxx"

namespace galaxy
{
	namespace api
	{
		CustomNetworkingImpl::~CustomNetworkingImpl()
		{
		}

		void CustomNetworkingImpl::OpenConnection(const char* connectionString, IConnectionOpenListener* const listener) {

		}

		void CustomNetworkingImpl::CloseConnection(ConnectionID connectionID, IConnectionCloseListener* const listener) {

		}

		void CustomNetworkingImpl::SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) {

		}

		uint32_t CustomNetworkingImpl::GetAvailableDataSize(ConnectionID connectionID) {
			return 0;
		}

		void CustomNetworkingImpl::PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) {

		}

		void CustomNetworkingImpl::ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) {

		}

		void CustomNetworkingImpl::PopData(ConnectionID connectionID, uint32_t dataSize) {

		}
	}
}
