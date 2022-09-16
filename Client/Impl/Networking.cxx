#include "Networking.hxx"

namespace galaxy
{
	namespace api
	{
		NetworkingImpl::NetworkingImpl(InterfaceInstances* intf) :
			intf{ intf }, listeners{ intf->listener_registrar_impl.get() }
		{}

		NetworkingImpl::~NetworkingImpl()
		{
		}

		bool NetworkingImpl::SendP2PPacket(GalaxyID galaxyID, const void* data, uint32_t dataSize, P2PSendType sendType, uint8_t channel) {
			return false;
		}

		bool NetworkingImpl::PeekP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
			return false;
		}

		bool NetworkingImpl::IsP2PPacketAvailable(uint32_t* outMsgSize, uint8_t channel) {
			return false;
		}

		bool NetworkingImpl::ReadP2PPacket(void* dest, uint32_t destSize, uint32_t* outMsgSize, GalaxyID& outGalaxyID, uint8_t channel) {
			return false;
		}

		void NetworkingImpl::PopP2PPacket(uint8_t channel) {

		}

		int NetworkingImpl::GetPingWith(GalaxyID galaxyID) {
			return -1;
		}

		void NetworkingImpl::RequestNatTypeDetection() {

		}

		NatType NetworkingImpl::GetNatType() {
			return NAT_TYPE_NONE;
		}

		ConnectionType NetworkingImpl::GetConnectionType(GalaxyID userID) {
			return CONNECTION_TYPE_DIRECT;
		}
	}
}


