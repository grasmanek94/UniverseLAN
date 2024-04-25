#include <Unet_common.h>
#include <Unet/LobbyFile.h>
#include <Unet/xxhash.h>

Unet::LobbyFile::LobbyFile(const std::string &filename)
{
	m_filename = filename;
}

Unet::LobbyFile::~LobbyFile()
{
	if (m_buffer != nullptr) {
		free(m_buffer);
	}
}

void Unet::LobbyFile::Prepare(size_t size, uint64_t hash)
{
	if (m_buffer != nullptr) {
		free(m_buffer);
	}

	m_buffer = (uint8_t*)malloc(size);
	m_size = size;
	m_availableSize = 0;

	m_hash = hash;
}

std::string Unet::LobbyFile::GetCachePath() const
{
	return strPrintF("UnetCache/%016X", m_hash);
}

void Unet::LobbyFile::LoadFromCache()
{
	if (!System::FolderExists("UnetCache")) {
		return;
	}

	std::string path = GetCachePath();

	FILE* fh = fopen(path.c_str(), "rb");
	if (fh == nullptr) {
		return;
	}
	fclose(fh);

	LoadFromFile(path);
}

void Unet::LobbyFile::LoadFromFile(const std::string &filenameOnDisk)
{
	//TODO: Don't keep buffer in memory and just read from file when needed

	if (m_buffer != nullptr) {
		free(m_buffer);
		m_buffer = nullptr;
	}

	FILE* fh = fopen(filenameOnDisk.c_str(), "rb");
	if (fh == nullptr) {
		// File does not exist!
		assert(false);
		return;
	}

	fseek(fh, 0, SEEK_END);
	m_size = ftell(fh);
	m_availableSize = m_size;
	m_buffer = (uint8_t*)malloc(m_size);
	fseek(fh, 0, SEEK_SET);

	fread(m_buffer, 1, m_size, fh);
	fclose(fh);

	m_hash = XXH64(m_buffer, m_size, 0);
}

void Unet::LobbyFile::Load(uint8_t* buffer, size_t size)
{
	if (m_buffer != nullptr) {
		free(m_buffer);
	}

	m_size = size;
	m_availableSize = size;
	m_buffer = (uint8_t*)malloc(size);
	memcpy(m_buffer, buffer, size);

	m_hash = XXH64(m_buffer, m_size, 0);
}

void Unet::LobbyFile::AppendData(uint8_t* buffer, size_t size)
{
	assert(m_availableSize + size <= m_size);

	memcpy(m_buffer + m_availableSize, buffer, size);
	m_availableSize += size;
}

void Unet::LobbyFile::SaveToCache() const
{
	assert(IsValid());

	if (!System::FolderExists("UnetCache")) {
		System::FolderCreate("UnetCache");
	}

	std::string path = GetCachePath();

	FILE* fh = fopen(path.c_str(), "wb");
	if (fh == nullptr) {
		return;
	}
	fwrite(m_buffer, 1, m_size, fh);
	fclose(fh);
}

bool Unet::LobbyFile::IsValid() const
{
	if (m_buffer == nullptr) {
		return false;
	}

	if (m_availableSize != m_size) {
		return false;
	}

	uint64_t hash = XXH64(m_buffer, m_size, 0);
	if (hash != m_hash) {
		return false;
	}

	return true;
}

double Unet::LobbyFile::GetPercentage() const
{
	return m_availableSize / (double)m_size;
}

double Unet::LobbyFile::GetPercentage(const struct OutgoingFileTransfer &transfer) const
{
	return transfer.CurrentPos / (double)m_size;
}
