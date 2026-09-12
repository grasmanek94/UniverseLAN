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
	inline typename std::enable_if<!std::is_same_v<std::remove_cvref_t<V>, NotificationParamScopeExtender>, V&&>::type
		notification_param_push_identity(V&& v)
	{
		return std::forward<V>(v);
	}

	template<typename V>
	inline typename std::enable_if<std::is_same_v<std::remove_cvref_t<V>, NotificationParamScopeExtender>, const char*>::type
		notification_param_push_identity(V&& v)
	{
		return static_cast<const char*>(v);
	}

	template<typename T>
	inline NotificationParamScopeExtender notification_param_extend_life(T&& v)
		/*
			std::remove_cvref_t<T> removes:
			- top-level const/volatile qualifiers
			- reference qualifiers (& and &&)

			therefore this overload matches:

			- const char*
			- const char* const
			- const char*&
			- const char*&&
			- const char* const&
			- const char* const&&
		*/
		requires (std::same_as<std::remove_cvref_t<T>, const char*>)
	{
		return NotificationParamScopeExtender(v);
	}

	template<typename T>
	inline T&& notification_param_extend_life(T&& v)
		requires (!std::same_as<std::remove_cvref_t<T>, const char*>)
	{
		// Hey there, 
		// if you're debugging this code, and passing char* 's to a notification, 
		// make sure there will be no lifetime/scope issues!
		// Here I'm just forwarding the char* ptr..
		// If you want to use automatic life extension then consider casting it to const char*.
		return std::forward<T>(v);
	}
}
