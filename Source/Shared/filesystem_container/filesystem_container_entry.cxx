#include "filesystem_container_entry.hxx"
#include "filesystem_container_metadata.hxx"
#include "filesystem_container.hxx"

#include <cereal/archives/binary.hpp>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace filesystem_container {
	namespace {
		constexpr auto file_write_mode = std::ios::out | std::ios::trunc | std::ios::binary;
		constexpr auto file_read_mode = std::ios::in | std::ios::binary;
	}

	filesystem_entry::filesystem_entry(filesystem_container* parent_file_container, std::filesystem::path path) :
		parent_fc{ parent_file_container },
		path{ path },
		abs_file_path{ parent_file_container->get_path(path) },
		abs_metadata_path{ parent_file_container->get_path_metadata(path) },
		metadata{}
	{
		if (std::filesystem::exists(abs_metadata_path)) {
			std::fstream metadata_stream{ abs_metadata_path, file_read_mode };

			if (metadata_stream) {
				try
				{
					cereal::BinaryInputArchive iarchive(metadata_stream);
					iarchive(metadata);
				}
				catch (const std::exception& ex)
				{
					throw std::runtime_error(ex.what() + std::string(" [occurred when trying to deserialize metadata archive]: " + abs_metadata_path.string()));
				}
			}
		}
	}

	filesystem_entry::filesystem_entry(filesystem_container* parent_file_container, std::filesystem::path path, uint64_t share_id) :
		filesystem_entry{parent_file_container, path}
	{
		metadata.share_id = share_id;
	}

	filesystem_entry::~filesystem_entry() {
		// write out metadata
	}

	std::filesystem::path filesystem_entry::get_path() const
	{
		return path;
	}

	std::filesystem::path filesystem_entry::get_abs_path() const
	{
		return abs_file_path;
	}

	std::filesystem::path filesystem_entry::get_abs_metadata_path() const
	{
		return abs_metadata_path;
	}

	bool filesystem_entry::exists()
	{
		return std::filesystem::exists(abs_file_path);
	}

	bool filesystem_entry::unlink()
	{
		bool exists_file = std::filesystem::exists(abs_file_path);
		bool exists_metadata = std::filesystem::exists(abs_metadata_path);
		bool success = exists_file || exists_metadata;

		[[likely]]
		if (exists_file && !std::filesystem::remove(abs_file_path)) {
			success = false;
		}

		if (exists_metadata && !std::filesystem::remove(abs_metadata_path)) {
			success = false;
		}

		if (success) {
			metadata.reset();
		}

		return parent_fc->remove(shared_from_this(), true);
	}

	bool filesystem_entry::copy_to(const std::filesystem::path& other_file_path) const
	{	
		std::error_code ec;
		std::filesystem::create_directories(std::filesystem::path(other_file_path).remove_filename(), ec);

		return std::filesystem::copy_file(abs_file_path, other_file_path);
	}

	bool filesystem_entry::copy_metadata_to(const std::filesystem::path& other_file_path) const
	{
		std::error_code ec;
		std::filesystem::create_directories(std::filesystem::path(other_file_path).remove_filename(), ec);

		return std::filesystem::copy_file(abs_metadata_path, other_file_path);
	}

	bool filesystem_entry::notify_copy_start(const filesystem_entry& source) {
		return true;
	}

	void filesystem_entry::notify_copy_done(const filesystem_entry& source, bool copied_file, bool copied_metadata) {
		metadata.share_id = 0;
		metadata.system_metadata = source.metadata.system_metadata;
		metadata.user_metadata = source.metadata.user_metadata;

		parent_fc->notify_file_copied(shared_from_this());
	}

	bool filesystem_entry::copy_to(filesystem_entry& other_entry) const
	{
		if (!other_entry.notify_copy_start(*this)) {
			return false;
		}

		std::error_code ec;
		std::filesystem::create_directories(std::filesystem::path(other_entry.get_abs_path()).remove_filename(), ec);
		std::filesystem::create_directories(std::filesystem::path(other_entry.get_abs_metadata_path()).remove_filename(), ec);

		bool file = std::filesystem::copy_file(abs_metadata_path, other_entry.get_abs_path());
		bool metadata = std::filesystem::copy_file(abs_metadata_path, other_entry.get_abs_metadata_path());

		other_entry.notify_copy_done(*this, file, metadata);

		return file && metadata;
	}

	bool filesystem_entry::copy_to(fs_entry_ptr other_entry) const
	{
		if (!other_entry) {
			return false;
		}

		return copy_to(*other_entry);
	}

	uint64_t filesystem_entry::get_timestamp() const
	{
		try {
			return std::filesystem::last_write_time(abs_file_path).time_since_epoch() / std::chrono::seconds(1);
		}
		catch (std::exception) {
			return 0;
		}
	}

	uint64_t filesystem_entry::get_timestamp_metadata() const
	{
		return metadata.get_timestamp();
	}

	void filesystem_entry::set_timestamp_metadata(int64_t timestamp)
	{
		metadata.set_timestamp(timestamp);
	}

	uint64_t filesystem_entry::get_share_id() const
	{
		return metadata.share_id;
	}

	void filesystem_entry::set_share_id(uint64_t share_id)
	{
		metadata.share_id = share_id;
	}

	uint64_t filesystem_entry::get_size() const
	{
		try {
			return std::filesystem::file_size(abs_file_path);
		}
		catch (std::exception) {
			return 0;
		}
	}

	std::fstream filesystem_entry::open(std::ios::openmode mode) const
	{
		return std::fstream { abs_file_path, mode };
	}

	std::vector<char> filesystem_entry::read()
	{
		std::fstream data_stream{ abs_file_path, file_read_mode };
		if (!data_stream) {
			return {};
		}

		// Stop eating new lines in binary mode!!!
		data_stream.unsetf(std::ios::skipws);

		// get its size:
		std::streampos file_size;

		data_stream.seekg(0, std::ios::end);
		file_size = data_stream.tellg();
		data_stream.seekg(0, std::ios::beg);

		// reserve capacity
		std::vector<char> vec;
		vec.reserve((size_t)file_size);

		// read the data:
		vec.insert(vec.begin(),
			std::istream_iterator<char>(data_stream),
			std::istream_iterator<char>());

		return vec;
	}

	size_t filesystem_entry::read(char* data, size_t data_length, size_t offset)
	{
		std::fstream data_stream{ abs_file_path, file_read_mode };
		if (!data_stream) {
			return 0;
		}

		// Stop eating new lines in binary mode!!!
		data_stream.unsetf(std::ios::skipws);

		data_stream.seekg(offset);
		data_stream.read(data, data_length);
		return data_stream.gcount();
	}

	bool filesystem_entry::write(const char* data, size_t data_length)
	{
		std::error_code ec;
		std::filesystem::create_directories(std::filesystem::path(abs_file_path).remove_filename(), ec);

		std::fstream data_stream{ abs_file_path, file_write_mode };
		if (!data_stream) {
			return false;
		}

		data_stream.unsetf(std::ios::skipws);
		data_stream.write(data, data_length);

		return true;
	}

	bool filesystem_entry::write(const std::vector<char>& data)
	{
		return write(data.data(), data.size());
	}

	void filesystem_entry::set_metadata(const std::string& key, const std::string& value)
	{
		metadata.user_metadata.set(key, value);
	}

	std::string filesystem_entry::get_metadata(const std::string& key, const std::string& default_value) const
	{
		return metadata.user_metadata.get_str(key, default_value);
	}

	std::vector<std::string> filesystem_entry::get_metadata_keys() const
	{
		return metadata.user_metadata.get_keys();
	}

	std::vector<std::string> filesystem_entry::get_metadata_values() const
	{
		return metadata.user_metadata.get_values();
	}

	file_entry_metadata_container_t filesystem_entry::get_metadata() const
	{
		return metadata.user_metadata.get_all();
	}

	bool filesystem_entry::save_metadata()
	{
		std::error_code ec;
		std::filesystem::create_directories(std::filesystem::path(abs_metadata_path).remove_filename(), ec);

		std::fstream metadata_stream{ abs_metadata_path, file_write_mode };

		if (!metadata_stream) {
			return false;
		}

		try
		{
			cereal::BinaryOutputArchive oarchive(metadata_stream);
			oarchive(metadata);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	void filesystem_entry::create_empty_file_if_not_exist()
	{
		if (exists()) {
			return;
		}

		std::error_code ec;
		std::filesystem::create_directories(std::filesystem::path(abs_file_path).remove_filename(), ec);

		std::fstream data_stream{ abs_file_path, file_write_mode };
	}
}
