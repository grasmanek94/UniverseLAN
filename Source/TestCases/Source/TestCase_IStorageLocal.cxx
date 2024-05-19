#if !GALAXY_BUILD_FEATURE_HAS_ISTORAGE
int main() { return 0; }
#else

#define USE_TESTING_MAIN

#include <TestCaseClientDetails.hxx>

#include <unordered_map>
#include <string>
#include <vector>

using file_data_t = std::vector<unsigned char>;
using file_map_t = std::unordered_map<std::string, file_data_t>;
using file_entry_t = file_map_t::value_type;

file_data_t create_entry(const std::string& data) {
	return file_data_t{ data.begin(), data.end() };
}

file_map_t files;

void perform_test() {
	files["test1.txt"] = create_entry(R"STR(
Test data
With a few newlines
To check if this works
And maybe add some UTF-8 encoded characters here: łakomo
żyć też się tutaj da.
		)STR");

	files["test2.bin"] = {
		0x9B,0x3E,0x34,0x87,
		0xFD,0x24,0xB4,0x64,
		0xBA,0x80,0x04,0xFD,
		0xDF,0x23,0x41,0xEE,
		0x00,0x00,0x00,0x00,
		0xAC,0xF9,0x8F,0x00
	};


	auto storage_ptr = GET_GALAXY_API(Storage());

	for (auto& file : files) {
		storage_ptr->FileDelete(file.first.c_str());
	}

	for (auto& file : files) {
		bool status =
			(storage_ptr->FileExists(file.first.c_str()) == false) &&
			(storage_ptr->GetFileSize(file.first.c_str()) == 0)
			;

		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} FileSize: {} FileCount: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), storage_ptr->GetFileSize(file.first.c_str()), storage_ptr->GetFileCount(),
				status
			));
	}

	char buffer[256];

	for (auto& file : files) {
		uint32_t read_bytes = storage_ptr->FileRead(file.first.c_str(), buffer, sizeof(buffer));
		bool status = read_bytes == 0;
		tracer::Trace::write_all(
			std::format(
				"File: {} FileRead: {} Status: {}",
				file.first, read_bytes, status
			));
	}

	for (auto& file : files) {
		bool status = storage_ptr->FileExists(file.first.c_str()) == false;
		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), status
			));
	}

	char start_char = 'f';
	for (auto& file : files) {
		static char i = 0;
		++i;
		std::string out(20, start_char + i);
		storage_ptr->FileWrite(file.first.c_str(), out.c_str(), (uint32_t)(out.length() + 1));

		tracer::Trace::write_all(
			std::format(
				"File: {} FileWrite: {} Size: {}",
				file.first, out, out.length() + 1
			));
	}

	for (auto& file : files) {
		bool status =
			(storage_ptr->FileExists(file.first.c_str()) == true) &&
			(storage_ptr->GetFileSize(file.first.c_str()) == 21)
			;
		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} FileSize: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), storage_ptr->GetFileSize(file.first.c_str()),
				status
			));
	}

	for (auto& file : files) {
		static char i = 0;
		++i;
		std::string out(20, start_char + i);

		std::memset(buffer, 0xCC, sizeof(buffer));

		uint32_t read_bytes = storage_ptr->FileRead(file.first.c_str(), buffer, sizeof(buffer));
		bool match = compare_equal(buffer, out);
		bool check = compare_equal(buffer + read_bytes, 0xCC, sizeof(buffer) - read_bytes);
		bool status = match && check && (read_bytes == (out.length() + 1));
		tracer::Trace::write_all(
			std::format(
				"File: {} FileRead: {} Match: {} Check: {} Status: {}",
				file.first, read_bytes, match, check, status
			));
	}

	for (auto& file : files) {
		storage_ptr->FileDelete(file.first.c_str());
	}

	for (auto& file : files) {
		bool status = storage_ptr->FileExists(file.first.c_str()) == false;
		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), status
			));
	}

	for (auto& file : files) {
		storage_ptr->FileWrite(file.first.c_str(), file.second.data(), (uint32_t)file.second.size());

		tracer::Trace::write_all(
			std::format(
				"File: {} FileWrite: (size){}",
				file.first, file.second.size()
			));
	}

	for (auto& file : files) {
		bool status =
			(storage_ptr->FileExists(file.first.c_str()) == true) &&
			(storage_ptr->GetFileSize(file.first.c_str()) == file.second.size()) &&
			(storage_ptr->GetFileCount() > 1)
			;

		tracer::Trace::write_all(
			std::format(
				"File: {} Exists: {} FileSize: {} FileCount: {} Status: {}",
				file.first, storage_ptr->FileExists(file.first.c_str()), storage_ptr->GetFileSize(file.first.c_str()), storage_ptr->GetFileCount(),
				status
			));
	}

	for (size_t i = 0; i < storage_ptr->GetFileCount(); ++i) {
		tracer::Trace::write_all(
			std::format(
				"GetFileByIndex{}: {}",
				i, storage_ptr->GetFileNameByIndex((uint32_t)i)
			));
	}

	for (auto& file : files) {
		std::memset(buffer, 0xCC, sizeof(buffer));

		uint32_t read_bytes = storage_ptr->FileRead(file.first.c_str(), buffer, sizeof(buffer));
		bool match = compare_equal(buffer, file.second);
		bool check = compare_equal(buffer + read_bytes, 0xCC, sizeof(buffer) - read_bytes);
		bool status = match && check && (read_bytes == file.second.size());

		tracer::Trace::write_all(
			std::format(
				"File: {} FileRead: {} Match: {} Check: {} Status: {}",
				file.first, read_bytes, match, check, status
			));
	}
}

void register_listeners() {}
bool should_keep_running() { return true; }

#endif
