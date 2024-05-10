#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE

#include "CloudStorage.hxx"

#include "UniverseLAN.hxx"

#include <SafeStringCopy.hxx>

#include <string>
#include <utility>

namespace universelan::client {
	using namespace galaxy::api;

	CloudStorageImpl::CloudStorageImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
		sfu{ intf->sfu.get() }, last_container{ "" },
		last_subcontainer_ref{ nullptr }, container_file_list {},
		last_metadata_request{}
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };
	}

	CloudStorageImpl::~CloudStorageImpl() {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };
	}

	void CloudStorageImpl::GetFileList(const char* container, ICloudStorageGetFileListListener* listener) {		
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		last_container = util::safe_fix_null_char_ptr_ret(container);

		last_subcontainer_ref = sfu->cloud->get_subcontainer(container);
		container_file_list = last_subcontainer_ref->get_file_list();

		listeners->NotifyAll(
			listener,
			&ICloudStorageGetFileListListener::OnGetFileListSuccess,
			(uint32_t)container_file_list.size(),
			sfu->GetTotalDiskSpace(last_subcontainer_ref),
			sfu->GetUsedDiskSpace(last_subcontainer_ref));
	}

	const char* CloudStorageImpl::GetFileNameByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (index >= container_file_list.size()) {
			return nullptr;
		}

		static thread_local char buffer[256];

		std::string name = container_file_list[index]->get_path().string();
		universelan::util::safe_copy_str_n(name, buffer, sizeof(buffer));

		return buffer;
	}

	uint32_t CloudStorageImpl::GetFileSizeByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (index >= container_file_list.size()) {
			return 0;
		}

		return (uint32_t)container_file_list[index]->get_size();
	}

	uint32_t CloudStorageImpl::GetFileTimestampByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (index >= container_file_list.size()) {
			return 0;
		}

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_PUTFILE_TIMESTAMP
		return (uint32_t)container_file_list[index]->get_timestamp_metadata();
#else
		return (uint32_t)container_file_list[index]->get_timestamp();
#endif
	}

#if GALAXY_BUILD_FEATURE_HAS_ICLOUDSTORAGE_GETFILEHASHBYINDEX
	const char* CloudStorageImpl::GetFileHashByIndex(uint32_t index) const
	{
		return "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	}
#endif

	void CloudStorageImpl::GetFile(const char* container, const char* name, void* userParam, WriteFunc writeFunc, ICloudStorageGetFileListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (writeFunc == nullptr) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_WRITE_FUNC_ERROR);

			return;
		}

		auto subcontainer = sfu->cloud->get_subcontainer(container);
		if (!subcontainer->exists(util::safe_fix_null_char_ptr_ret(name))) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_NOT_FOUND);

			return;
		}

		std::string container_str = util::safe_fix_null_char_ptr_ret(container);
		std::string file_name = util::safe_fix_null_char_ptr_ret(name);

		intf->delay_runner->Add([=, this] {
			auto file_entry = subcontainer->get(file_name);
			if (!file_entry) {
				this->listeners->NotifyAllNow(
					listener,
					&ICloudStorageGetFileListener::OnGetFileFailure, container_str.c_str(), file_name.c_str(), ICloudStorageGetFileListener::FAILURE_REASON_NOT_FOUND);

				return;
			}

			auto data = file_entry->read();
			if (writeFunc(userParam, data.data(), (uint32_t)data.size()) < 0) {
				this->listeners->NotifyAllNow(
					listener,
					&ICloudStorageGetFileListener::OnGetFileFailure, container_str.c_str(), file_name.c_str(), ICloudStorageGetFileListener::FAILURE_REASON_WRITE_FUNC_ERROR);

				return;
			}

			last_metadata_request = file_entry->get_metadata_vector();

			this->listeners->NotifyAllNow(
				listener,
				&ICloudStorageGetFileListener::OnGetFileSuccess, container_str.c_str(), file_name.c_str(), (uint32_t)data.size(), (uint32_t)last_metadata_request.size());
		});
	}

	void CloudStorageImpl::GetFile(const char* container, const char* name, void* buffer, uint32_t bufferLength, ICloudStorageGetFileListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (buffer == nullptr) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_BUFFER_TOO_SMALL);

			return;
		}

		auto subcontainer = sfu->cloud->get_subcontainer(container);
		if (!subcontainer->exists(util::safe_fix_null_char_ptr_ret(name))) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_NOT_FOUND);

			return;
		}

		auto file_entry = subcontainer->get(util::safe_fix_null_char_ptr_ret(name));

		if (!file_entry) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_NOT_FOUND);

			return;
		}

		size_t written = file_entry->read((char*)buffer, bufferLength);
		if (written != bufferLength) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_BUFFER_TOO_SMALL);

			return;
		}


		last_metadata_request = file_entry->get_metadata_vector();

		listeners->NotifyAll(
			listener,
			&ICloudStorageGetFileListener::OnGetFileSuccess, container, name, (uint32_t)written, (uint32_t)last_metadata_request.size());
	}

	void CloudStorageImpl::GetFileMetadata(const char* container, const char* name, ICloudStorageGetFileListener* listener) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		auto subcontainer = sfu->cloud->get_subcontainer(container);
		if (!subcontainer->exists(util::safe_fix_null_char_ptr_ret(name))) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_NOT_FOUND);

			return;
		}

		auto file_entry = subcontainer->get(util::safe_fix_null_char_ptr_ret(name));

		if (!file_entry) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageGetFileListener::OnGetFileFailure, container, name, ICloudStorageGetFileListener::FAILURE_REASON_NOT_FOUND);

			return;
		}

		last_metadata_request = file_entry->get_metadata_vector();

		listeners->NotifyAll(
			listener,
			&ICloudStorageGetFileListener::OnGetFileSuccess, container, name, (uint32_t)file_entry->get_size(), (uint32_t)last_metadata_request.size());
	}

	const char* CloudStorageImpl::GetFileMetadataKeyByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (index >= last_metadata_request.size()) {
			return nullptr;
		}

		return last_metadata_request[index].first.c_str();
	}

	const char* CloudStorageImpl::GetFileMetadataValueByIndex(uint32_t index) const {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (index >= last_metadata_request.size()) {
			return nullptr;
		}

		return last_metadata_request[index].second.c_str();
	}

	void CloudStorageImpl::PutFile(
		const char* container,
		const char* name,
		void* userParam,
		ReadFunc readFunc,
		RewindFunc rewindFunc,
		ICloudStoragePutFileListener* listener,
		const char* const* metadataKeys,
		const char* const* metadataValues,
		uint32_t timeStamp
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (name == nullptr || *name == NULL || readFunc == nullptr) {
			listeners->NotifyAll(
				listener,
				&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		auto subcontainer = sfu->cloud->get_subcontainer(container);
		auto file_entry = subcontainer->get_or_create(util::safe_fix_null_char_ptr_ret(name));

		if (!file_entry) {
			listeners->NotifyAll(
				listener,
				&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_UNDEFINED);

			return;
		}


		auto file_stream = file_entry->open(std::ios::out | std::ios::trunc | std::ios::binary);
		if (!file_stream) {
			listeners->NotifyAll(
				listener,
				&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_UNDEFINED);

			return;
		}

		static const int buffer_size = 1024;
		static thread_local char buffer[buffer_size];
		int read_size = 0;

		do {
			read_size = readFunc(userParam, buffer, (int)buffer_size);
			if (read_size > 0) {
				file_stream.write(buffer, std::min(buffer_size, read_size));
			}
		} while(read_size > 0);

		if (read_size < 0) {
			listeners->NotifyAll(
				listener,
				&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_READ_FUNC_ERROR);

			return;
		}

		if (metadataKeys != nullptr && metadataValues != nullptr) {
			int index = 0;
			while (metadataKeys[index] && metadataValues[index]) {
				file_entry->set_metadata(util::safe_fix_null_char_ptr_ret(metadataKeys[index]), util::safe_fix_null_char_ptr_ret(metadataValues[index]));
				++index;
			}
		}

		if (timeStamp == 0) {
			file_entry->touch_timestamp_metadata();
		}

		// TODO: maybe check exit value?
		file_entry->save_metadata();

		listeners->NotifyAll(
			listener,
			&ICloudStoragePutFileListener::OnPutFileSuccess, container, name);
	}

	void CloudStorageImpl::PutFile(
		const char* container,
		const char* name,
		const void* buffer,
		uint32_t bufferLength,
		ICloudStoragePutFileListener* listener,
		const char* const* metadataKeys,
		const char* const* metadataValues,
		uint32_t timeStamp
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (name == nullptr || *name == NULL || buffer == nullptr) {
			listeners->NotifyAll(
				listener,
				&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		auto subcontainer = sfu->cloud->get_subcontainer(container);
		auto file_entry = subcontainer->get_or_create(util::safe_fix_null_char_ptr_ret(name));

		if (!file_entry) {
			listeners->NotifyAll(
				listener,
				&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_UNDEFINED);

			return;
		}

		if (!file_entry->write((const char*)buffer, bufferLength)) {
			listeners->NotifyAll(
				listener,
				&ICloudStoragePutFileListener::OnPutFileFailure, container, name, ICloudStoragePutFileListener::FAILURE_REASON_UNDEFINED);

			return;
		}

		if (metadataKeys != nullptr && metadataValues != nullptr) {
			int index = 0;
			while (metadataKeys[index] && metadataValues[index]) {
				file_entry->set_metadata(util::safe_fix_null_char_ptr_ret(metadataKeys[index]), util::safe_fix_null_char_ptr_ret(metadataValues[index]));
				++index;
			}		
		}

		if (timeStamp == 0) {
			file_entry->touch_timestamp_metadata();
		}

		// TODO: maybe check exit value?
		file_entry->save_metadata();

		listeners->NotifyAll(
			listener,
			&ICloudStoragePutFileListener::OnPutFileSuccess, container, name);
	}

	void CloudStorageImpl::PutFile(
		const char* container,
		const char* name,
		void* userParam,
		ReadFunc readFunc,
		RewindFunc rewindFunc,
		ICloudStoragePutFileListener* listener,
		const char* const* metadataKeys,
		const char* const* metadataValues
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		PutFile(container, name, userParam, readFunc, rewindFunc, listener, metadataKeys, metadataValues, 0);
	}

	void CloudStorageImpl::PutFile(
		const char* container,
		const char* name,
		const void* buffer,
		uint32_t bufferLength,
		ICloudStoragePutFileListener* listener,
		const char* const* metadataKeys,
		const char* const* metadataValues
	) {
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		PutFile(container, name, buffer, bufferLength, listener, metadataKeys, metadataValues, 0);
	}

#pragma push_macro("DeleteFile")
#undef DeleteFile
	void CloudStorageImpl::DeleteFile(const char* container, const char* name, ICloudStorageDeleteFileListener* listener)
#pragma pop_macro ("DeleteFile")
	{
		tracer::Trace trace{ nullptr, __FUNCTION__, tracer::Trace::ICLOUDSTORAGE };

		if (name == nullptr || *name == NULL) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageDeleteFileListener::OnDeleteFileFailure, container, name, ICloudStorageDeleteFileListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		auto subcontainer = sfu->cloud->get_subcontainer(container);
		auto file_entry = subcontainer->get(util::safe_fix_null_char_ptr_ret(name));

		if (!file_entry) {
			listeners->NotifyAll(
				listener,
				&ICloudStorageDeleteFileListener::OnDeleteFileFailure, container, name, ICloudStorageDeleteFileListener::FAILURE_REASON_UNDEFINED);
			return;
		}

		file_entry->unlink();

		listeners->NotifyAll(
			listener,
			&ICloudStorageDeleteFileListener::OnDeleteFileSuccess, container, name);
	}
}

#endif
