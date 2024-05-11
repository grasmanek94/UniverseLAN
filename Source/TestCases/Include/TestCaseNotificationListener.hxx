#pragma once

#include "TestCaseClientDetails.hxx"

#if GALAXY_BUILD_FEATURE_HAS_INOTIFICATIONLISTENER
class NotificationListenerImplGlobal : public galaxy::api::GlobalNotificationListener
{
public:
	using on_notification_received_func_t = std::function<void(NotificationID, uint32_t typeLength, uint32_t contentSize)>;

private:
	on_notification_received_func_t on_notification_received;

public:
	NotificationListenerImplGlobal(
		on_notification_received_func_t on_notification_received = nullptr) :
		on_notification_received{ on_notification_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~NotificationListenerImplGlobal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"notificationID: {} typeLength: {} contentSize: {}",
			notificationID, typeLength, contentSize
		).c_str());


		if (on_notification_received != nullptr) {
			on_notification_received(notificationID, typeLength, contentSize);
		}
	}
};

class NotificationListenerImplLocal : public galaxy::api::INotificationListener
{
public:
	using on_notification_received_func_t = std::function<void(NotificationID, uint32_t typeLength, uint32_t contentSize)>;

private:
	on_notification_received_func_t on_notification_received;

public:
	NotificationListenerImplLocal(
		on_notification_received_func_t on_notification_received = nullptr) :
		on_notification_received{ on_notification_received } {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual ~NotificationListenerImplLocal() {
		tracer::Trace trace{ "", __FUNCTION__ };
	}

	virtual void OnNotificationReceived(NotificationID notificationID, uint32_t typeLength, uint32_t contentSize) {
		tracer::Trace trace{ "", __FUNCTION__ };

		trace.write_all(std::format(
			"notificationID: {} typeLength: {} contentSize: {}",
			notificationID, typeLength, contentSize
		).c_str());


		if (on_notification_received != nullptr) {
			on_notification_received(notificationID, typeLength, contentSize);
		}
	}
};
#endif
