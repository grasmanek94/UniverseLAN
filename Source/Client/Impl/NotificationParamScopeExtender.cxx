#include "NotificationParamScopeExtender.hxx"

#include <string>

namespace universelan::client {

	void NotificationParamScopeExtender::swap(NotificationParamScopeExtender& other) {
		other.data.swap(data);
	}

	NotificationParamScopeExtender::NotificationParamScopeExtender() : data{} {}
	NotificationParamScopeExtender::NotificationParamScopeExtender(const char* const str) : data{} {
		if (str != nullptr) {
			data = std::string(str);
		}
	}
	NotificationParamScopeExtender::NotificationParamScopeExtender(const std::string& str) : data{ str } {}
	NotificationParamScopeExtender::NotificationParamScopeExtender(const NotificationParamScopeExtender& other) : data{ other.data } {}
	NotificationParamScopeExtender::NotificationParamScopeExtender(NotificationParamScopeExtender&& b) noexcept {
		b.swap(*this);
	}
	NotificationParamScopeExtender::~NotificationParamScopeExtender() {}
	NotificationParamScopeExtender& NotificationParamScopeExtender::operator=(NotificationParamScopeExtender b) {
		b.swap(*this);
		return *this;
	}

	NotificationParamScopeExtender::operator const char* const () const noexcept {
		if (data) {
			return data->c_str();
		}
		return nullptr;
	}
}
