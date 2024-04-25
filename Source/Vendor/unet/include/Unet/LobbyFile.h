#pragma once

#include <Unet_common.h>
#include <Unet/ServiceID.h>

namespace Unet
{
	class LobbyFile
	{
	public:
		std::string m_filename;
		uint64_t m_hash = 0;

		uint8_t* m_buffer = nullptr;
		size_t m_size = 0;
		size_t m_availableSize = 0;

	public:
		LobbyFile(const std::string &filename);
		~LobbyFile();

		void Prepare(size_t size, uint64_t hash);

		std::string GetCachePath() const;

		void LoadFromCache();
		void LoadFromFile(const std::string &filenameOnDisk);
		void Load(uint8_t* buffer, size_t size);

		void AppendData(uint8_t* buffer, size_t size);
		void SaveToCache() const;

		// Checks whether the data captured in this file is complete and valid. Note
		// that this also computes and compares a hash for the entire buffer, so
		// consider that while working in performance-critical code.
		bool IsValid() const;

		double GetPercentage() const;
		double GetPercentage(const struct OutgoingFileTransfer &transfer) const;
	};

	struct OutgoingFileTransfer
	{
		uint64_t FileHash = 0;
		int MemberPeer = 0;
		size_t CurrentPos = 0;
	};
}
