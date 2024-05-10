#include "filesystem_container_metadata.hxx"

#include <chrono>
#include <cstdint>
#include <string>
#include <type_traits>

namespace filesystem_container {
	namespace {
		const std::string timestamp_key = "timestamp";

		std::chrono::system_clock::rep time_since_epoch() {
			static_assert(
				std::is_integral<std::chrono::system_clock::rep>::value,
				"Representation of ticks isn't an integral value."
				);
			auto now = std::chrono::system_clock::now().time_since_epoch();
			return std::chrono::duration_cast<std::chrono::seconds>(now).count();
		}
	}

	file_entry_metadata_container::file_entry_metadata_container() :
		mtx{}, data{} {}

	void file_entry_metadata_container::set(const std::string& key, int64_t value) {
		lock_t lock{ mtx };

		data[key] = std::to_string(value);
	}

	int64_t file_entry_metadata_container::get_ll(const std::string& key, int64_t default_value) const {
		lock_t lock{ mtx };

		auto entry = data.find(key);
		if (entry == data.end()) {
			return default_value;
		}

		return std::stoll(entry->second);
	}

	std::string file_entry_metadata_container::get_str(const std::string& key, const std::string& default_value) const {
		lock_t lock{ mtx };

		auto entry = data.find(key);
		if (entry == data.end()) {
			return default_value;
		}

		return entry->second;
	}

	std::vector<std::string> file_entry_metadata_container::get_keys() const
	{
		lock_t lock{ mtx };

		std::vector<std::string> v{};
		v.reserve(data.size());
		for (auto& k : data) {
			v.push_back(k.first);
		}

		return v;
	}

	std::vector<std::string> file_entry_metadata_container::get_values() const
	{
		lock_t lock{ mtx };

		std::vector<std::string> v{};
		v.reserve(data.size());
		for (auto& k : data) {
			v.push_back(k.second);
		}

		return v;
	}

	file_entry_metadata_container_t file_entry_metadata_container::get_all() const
	{
		lock_t lock{ mtx };

		return data;
	}

	void file_entry_metadata_container::clear()
	{
		lock_t lock{ mtx };
		data.clear();
	}

	bool file_entry_metadata_container::empty() const
	{
		lock_t lock{ mtx };
		return data.empty();
	}

	file_entry_metadata_container& file_entry_metadata_container::operator=(const file_entry_metadata_container& other)
	{
		if (this == &other) // not a self-assignment
		{
			return *this;
		}

		std::unique_lock<mutex_t> lk1(mtx, std::defer_lock);
		std::unique_lock<mutex_t> lk2(other.mtx, std::defer_lock);
		std::lock(lk1, lk2);

		data = other.data;

		return *this;
	}

	void file_entry_metadata_container::set(const std::string& key, const std::string& value) {
		lock_t lock{ mtx };

		data[key] = value;
	}

	file_entry_metadata::file_entry_metadata() : share_id{ 0 }, user_metadata{}, system_metadata{} {}

	void file_entry_metadata::set_timestamp(int64_t timestamp) {

		system_metadata.set(timestamp_key, timestamp);
	}

	int64_t file_entry_metadata::get_timestamp() const {
		return system_metadata.get_ll(timestamp_key);
	}

	void file_entry_metadata::reset()
	{
		share_id = 0;
		system_metadata.clear();
		user_metadata.clear();
	}

	bool file_entry_metadata::empty() const
	{
		return
			system_metadata.empty() &&
			user_metadata.empty() &&
			(share_id == 0);
	}

	void file_entry_metadata::touch_timestamp() {
		set_timestamp(time_since_epoch());
	}
}
