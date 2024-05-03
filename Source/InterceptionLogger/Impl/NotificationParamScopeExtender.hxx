#pragma once

#include <concepts>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

namespace universelan::client {
	class NotificationParamScopeExtender {
		std::optional<std::string> data;
	public:
		void swap(NotificationParamScopeExtender& other);

		NotificationParamScopeExtender();
		NotificationParamScopeExtender(const char* const str);
		NotificationParamScopeExtender(const std::string& str);
		NotificationParamScopeExtender(const NotificationParamScopeExtender& other);
		NotificationParamScopeExtender(NotificationParamScopeExtender&& b) noexcept;
		~NotificationParamScopeExtender();
		NotificationParamScopeExtender& operator=(NotificationParamScopeExtender b);
		operator const char* const() const noexcept;
	};


	template<typename V>
	inline typename std::enable_if<!std::is_same<V, NotificationParamScopeExtender>::value, V&&>::type 
		notification_param_push_identity(V&& v)
	{
		return std::forward<V>(v);
	}

	template<typename V>
	inline typename std::enable_if<std::is_same<V, NotificationParamScopeExtender>::value, char*&&>::type 
		notification_param_push_identity(V&& v)
	{
		return std::forward<char*>(v);
	}

	template<typename T>
	inline T&& notification_param_extend_life(typename std::enable_if<
		!std::same_as<typename std::remove_reference<T>::type, const char*> &&
		!std::same_as<typename std::remove_reference<T>::type, char*>, T&&>::type v)
	{
		return std::forward<T>(std::move(v));
	}

	template<typename T>
	inline char*&& notification_param_extend_life(char*&& v)
	{
		// Hey there, 
		// if you're debugging this code, and passing char* 's to a notification, 
		// make sure there will be no lifetime/scope issues!
		// Here I'm just forwarding the char* ptr..
		// If you want to use automatic life extension then consider casting it to const char*.
		return std::forward<char*>(std::move(v));
	}

	template<typename T>
	inline NotificationParamScopeExtender notification_param_extend_life(const char*&& v)
	{
		return std::forward<NotificationParamScopeExtender>(std::move(NotificationParamScopeExtender(v)));
	}
}
