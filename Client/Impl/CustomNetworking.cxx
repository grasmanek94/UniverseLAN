#include "CustomNetworking.hxx"

namespace galaxy
{
	namespace api
	{
		CustomNetworking::~CustomNetworking()
		{
		}

		void CustomNetworking::OpenConnection(const char* connectionString, IConnectionOpenListener* const listener) {

		}

		void CustomNetworking::CloseConnection(ConnectionID connectionID, IConnectionCloseListener* const listener) {

		}

		void CustomNetworking::SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) {

		}

		uint32_t CustomNetworking::GetAvailableDataSize(ConnectionID connectionID) {
			return 0;
		}

		void CustomNetworking::PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) {

		}

		void CustomNetworking::ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) {

		}

		void CustomNetworking::PopData(ConnectionID connectionID, uint32_t dataSize) {

		}
	}
}


