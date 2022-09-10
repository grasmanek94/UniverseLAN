#include "Networking.hxx"

namespace galaxy
{
	namespace api
	{
		Networking::~Networking()
		{
		}

		bool Networking::SendP2PPacket(GalaxyID galaxyID, const void* data, uint32_t dataSize, P2PSendType sendType, uint8_t channel) {
			return false;
		}

		bool Networking::PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
			return false;
		}

		bool Networking::IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel) {
			return false;
		}

		bool Networking::ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
			return false;
		}

		void Networking::PopP2PPacket(uint8_t channel) {

		}

		int Networking::GetPingWith(GalaxyID galaxyID) {
			return -1;
		}

		void Networking::RequestNatTypeDetection() {

		}

		NatType Networking::GetNatType() {
			return NAT_TYPE_NONE;
		}

		ConnectionType Networking::GetConnectionType(GalaxyID userID) {
			return CONNECTION_TYPE_DIRECT;
		}
	}
}


