#pragma once

#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>

#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace filesystem_container {
	using file_entry_metadata_container_t = std::map<std::string, std::string>;

	class file_entry_metadata_container {
	public:
		using mutex_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mutex_t>;

	private:
		mutable mutex_t mtx;
		file_entry_metadata_container_t data;

	public:
		template<class Archive>
		void serialize(Archive& ar)
		{
			lock_t lock{ mtx };
			ar(data);
		}

		file_entry_metadata_container();

		void set(const std::string& key, int64_t value);
		void set(const std::string& key, const std::string& value);
		int64_t get_ll(const std::string& key, int64_t default_value = 0) const;
		std::string get_str(const std::string& key, const std::string& default_value = "") const;

		template <typename T>
		T run_locked(std::function<T(file_entry_metadata_container_t& data)> function) {
			lock_t lock{ mtx };
			return function(data);
		}

		template <typename T>
		T run_locked_const(std::function<T(const file_entry_metadata_container_t& data)> function) const {
			lock_t lock{ mtx };
			return function(data);
		}

		std::vector<std::string> get_keys() const;
		std::vector<std::string> get_values() const;
		file_entry_metadata_container_t get_all() const;

		void clear();
		bool empty() const;

		file_entry_metadata_container& operator=(const file_entry_metadata_container& other);


	};

	struct file_entry_metadata {
		uint64_t share_id;

		template<class Archive>
		void serialize(Archive& ar)
		{
			ar(share_id, user_metadata, system_metadata);
		}

		file_entry_metadata();

		file_entry_metadata_container user_metadata;
		file_entry_metadata_container system_metadata;

		void set_timestamp(int64_t timestamp);
		void touch_timestamp();
		int64_t get_timestamp() const;

		void reset();
		bool empty() const;
	};
}
