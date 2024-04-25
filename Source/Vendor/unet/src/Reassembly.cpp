#include <Unet_common.h>
#include <Unet/Reassembly.h>
#include <Unet/Context.h>
#include <Unet/xxhash.h>

#define RELIABLE_MASK (0x80)
#define SEQUENCE_MASK (0x7F)

Unet::Reassembly::Reassembly(Internal::Context* ctx)
{
	m_ctx = ctx;
}

Unet::Reassembly::~Reassembly()
{
	Clear();
}

void Unet::Reassembly::HandleMessage(ServiceID peer, int channel, uint8_t* msgData, size_t packetSize)
{
	uint8_t sequenceId = *(msgData++);
	packetSize--;

	if ((sequenceId & RELIABLE_MASK) == 0) {
		// If this is actually an unreliable packet, just handle it as a single message
		auto newMessage = new NetworkMessage(msgData, packetSize);
		newMessage->m_channel = channel;
		newMessage->m_peer = peer;
		m_ready.push(newMessage);
		return;
	}
	sequenceId &= SEQUENCE_MASK;

	auto existingMsg = std::find_if(m_staging.begin(), m_staging.end(), [sequenceId](NetworkMessage * msg) {
		return msg->m_sequenceId == sequenceId;
	});

	if (existingMsg != m_staging.end()) {
		auto msg = *existingMsg;
		assert(msg->m_sequenceSize > 0);

		msg->Append(msgData, packetSize);

		assert(msg->m_size <= msg->m_sequenceSize);
		if (msg->m_size == msg->m_sequenceSize) {
			uint32_t finalHash = XXH32(msg->m_data, msg->m_size, 0);
			if (finalHash != msg->m_sequenceHash) {
				m_ctx->GetCallbacks()->OnLogError(strPrintF("Sequence hash for fragmented packet does not match! Packet size: %d", (int)msg->m_size));
			}

			m_staging.erase(existingMsg);
			m_ready.push(msg);
		}
		return;
	}

	uint32_t sequenceSize = *(uint32_t*)msgData;
	msgData += 4;
	packetSize -= 4;

	if (sequenceSize == packetSize) {
		// We have the full packet size already, we're not expecting any more packets
		auto newMessage = new NetworkMessage(msgData, packetSize);
		newMessage->m_channel = channel;
		newMessage->m_peer = peer;
		m_ready.push(newMessage);

	} else {
		uint32_t packetHash = *(uint32_t*)msgData;
		msgData += 4;
		packetSize -= 4;

		// We're expecting multiple packets, so at this point the sequence size must be bigger than the data we have left
		assert(sequenceSize > packetSize);

		auto newMessage = new NetworkMessage(msgData, packetSize);
		newMessage->m_sequenceId = sequenceId;
		newMessage->m_sequenceSize = sequenceSize;
		newMessage->m_sequenceHash = packetHash;
		newMessage->m_channel = channel;
		newMessage->m_peer = peer;
		m_staging.emplace_back(newMessage);
	}
}

Unet::NetworkMessage* Unet::Reassembly::PopReady()
{
	if (m_ready.size() == 0) {
		return nullptr;
	}

	auto ret = m_ready.front();
	m_ready.pop();
	return ret;
}

void Unet::Reassembly::Clear()
{
	for (auto msg : m_staging) {
		delete msg;
	}
	m_staging.clear();

	while (m_ready.size() > 0) {
		delete m_ready.front();
		m_ready.pop();
	}
}

void Unet::Reassembly::SplitMessage(uint8_t* data, size_t size, PacketType type, size_t sizeLimit, const std::function<void(uint8_t*, size_t)> &callback)
{
	m_sequenceId++;
	m_sequenceId &= SEQUENCE_MASK;

	if (type == PacketType::Unreliable) {
		m_tempBuffer.resize(size + 1);
		m_tempBuffer[0] = m_sequenceId;
		m_tempBuffer[1] = 0;
		memcpy(m_tempBuffer.data() + 1, data, size);
		callback(m_tempBuffer.data(), m_tempBuffer.size());
		return;
	}

	// Subtract 3 to ensure that, in the case of these being relay packets, we can still send them
	sizeLimit -= 3; //TODO: Do this selectively, only if relay is actually required?

	assert(size <= 0xFFFFFFFF); // Size is sent as a 32 bit unsigned integer, so you can't send packets bigger than 4GB

	bool shouldSplit = (size > sizeLimit - 5);

	XXH32_hash_t hashData = 0;
	if (shouldSplit) {
		hashData = XXH32(data, size, 0);
	}

	bool firstPacket = true;

	uint8_t* ptr = data;
	while (ptr < data + size) {
		size_t bytesLeft = size - (ptr - data);
		size_t dataSize = 0;

		if (firstPacket) {
			firstPacket = false;

			size_t extraData = 0;
			extraData += 1; // Sequence ID
			extraData += 4; // Full packet size
			if (shouldSplit) {
				extraData += 4; // Full packet hash
			}

			dataSize = std::min(bytesLeft, sizeLimit - extraData);

			m_tempBuffer.resize(dataSize + extraData);
			m_tempBuffer[0] = m_sequenceId | RELIABLE_MASK;

			uint32_t shortSize = (uint32_t)size;
			memcpy(m_tempBuffer.data() + 1, &shortSize, 4);

			if (shouldSplit) {
				memcpy(m_tempBuffer.data() + 5, &hashData, 4);
			}

			memcpy(m_tempBuffer.data() + extraData, ptr, dataSize);

			callback(m_tempBuffer.data(), m_tempBuffer.size());

		} else {
			size_t extraData = 1;

			dataSize = std::min(bytesLeft, sizeLimit - extraData);

			m_tempBuffer.resize(dataSize + extraData);
			m_tempBuffer[0] = m_sequenceId | RELIABLE_MASK;
			memcpy(m_tempBuffer.data() + extraData, ptr, dataSize);

			callback(m_tempBuffer.data(), m_tempBuffer.size());
		}

		ptr += dataSize;
	}
}
