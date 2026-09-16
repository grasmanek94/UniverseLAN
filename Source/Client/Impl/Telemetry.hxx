#pragma once
#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY

/**
 * @file
 * Contains data structures and interfaces related to telemetry.
 */

#include "ListenerRegistrar.hxx"

#include <ITelemetry.h>
#include <IListenerRegistrar.h>

#include <atomic>
#include <fstream>
#include <mutex>
#include <string>

namespace universelan::client {
	using namespace galaxy::api;
	struct InterfaceInstances;

	/**
	 * @addtogroup api
	 * @{
	 */

	 /**
	  * The interface for handling telemetry.
	  */
	class TelemetryImpl : public ITelemetry
	{
	public:
		using mtx_t = std::recursive_mutex;
		using lock_t = std::scoped_lock<mtx_t>;

	private:
		InterfaceInstances* intf;
		ListenerRegistrarImpl* listeners;
		mtx_t mtx;
		std::ofstream telemetry_file;
		std::atomic_uint32_t counter;
		std::string visit_id;

	public:

		TelemetryImpl(InterfaceInstances* intf);
		virtual ~TelemetryImpl();

		/**
		 * Adds a string parameter to be applied next time you call SendTelemetryEvent()
		 * or SendAnonymousTelemetryEvent().
		 *
		 * @remark You can add multiple parameters of different types.
		 *
		 * @remark All object parameters must have a unique name.
		 *
		 * @param [in] name The name of the parameter or NULL when adding a value to an array.
		 * @param [in] value The value of the parameter.
		 */
		virtual void AddStringParam(const char* name, const char* value) override;

		/**
		 * Adds an integer parameter to be applied next time you call SendTelemetryEvent()
		 * or SendAnonymousTelemetryEvent().
		 *
		 * @remark You can add multiple parameters of different types.
		 *
		 * @remark All object parameters must have a unique name.
		 *
		 * @param [in] name The name of the parameter or NULL when adding a value to an array.
		 * @param [in] value The value of the parameter.
		 */
		virtual void AddIntParam(const char* name, int32_t value) override;

		/**
		 * Adds a float parameter to be applied next time you call SendTelemetryEvent()
		 * or SendAnonymousTelemetryEvent().
		 *
		 * @remark You can add multiple parameters of different types.
		 *
		 * @remark All object parameters must have a unique name.
		 *
		 * @param [in] name The name of the parameter or NULL when adding a value to an array.
		 * @param [in] value The value of the parameter.
		 */
		virtual void AddFloatParam(const char* name, double value) override;

		/**
		 * Adds a boolean parameter to be applied next time you call SendTelemetryEvent()
		 * or SendAnonymousTelemetryEvent().
		 *
		 * @remark You can add multiple parameters of different types.
		 *
		 * @remark All object parameters must have a unique name.
		 *
		 * @param [in] name The name of the parameter or NULL when adding a value to an array.
		 * @param [in] value The value of the parameter.
		 */
		virtual void AddBoolParam(const char* name, bool value) override;

		/**
		 * Adds an object parameter to be applied next time you call SendTelemetryEvent()
		 * or SendAnonymousTelemetryEvent().
		 *
		 * Subsequent calls to add parameters operate within the newly created object parameter.
		 * In order to be able to add parameters on the upper level, you need to call
		 * ITelemetry::CloseParam().
		 *
		 * @remark You can add multiple parameters of different types.
		 *
		 * @remark All object parameters must have a unique name.
		 *
		 * @param [in] name The name of the parameter or NULL when adding a value to an array.
		 */
		virtual void AddObjectParam(const char* name) override;

		/**
		 * Adds an array parameter to be applied next time you call SendTelemetryEvent()
		 * or SendAnonymousTelemetryEvent().
		 *
		 * Subsequent calls to add parameters operate within the newly created array parameter.
		 * In order to be able to add parameters on the upper level, you need to call
		 * ITelemetry::CloseParam().
		 *
		 * @remark You can add multiple parameters of different types.
		 *
		 * @remark All object parameters must have a unique name.
		 *
		 * @param [in] name The name of the parameter or NULL when adding a value to an array.
		 */
		virtual void AddArrayParam(const char* name) override;

		/**
		 * Closes an object or array parameter and leaves its scope.
		 *
		 * This allows for adding parameters to the upper scope.
		 *
		 * @remark Once closed, an object or array cannot be extended with new parameters.
		 *
		 * @remark Has no effect on simple parameters as well as on the event object itself.
		 */
		virtual void CloseParam() override;

		/**
		 * Clears all parameters that may have been set so far at any level.
		 *
		 * This allows for safely starting to build an event from scratch.
		 */
		virtual void ClearParams() override;


#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY_SAMPLING_CLASS
		/**
		 * Sets a sampling class to be applied next time you call SendTelemetryEvent()
		 * or SendAnonymousTelemetryEvent().
		 *
		 * @param [in] name The name of the sampling class.
		 */
		virtual void SetSamplingClass(const char* name) override;
#endif

		/**
		 * Sends a telemetry event.
		 *
		 * This call is asynchronous. Responses come to the ITelemetryEventSendListener.
		 *
		 * @remark After each call to SendTelemetryEvent() or SendAnonymousTelemetryEvent()
		 * all parameters are cleared automatically as if you called ClearParams().
		 *
		 * @remark Internal event index returned by this method should only be used
		 * to identify sent events in callbacks that come to the ITelemetryEventSendListener.
		 *
		 * @param [in] eventType The type of the event.
		 * @param [in] listener The listener for specific operation.
		 * @return Internal event index.
		 */
		virtual uint32_t SendTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener = NULL) override;

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_6_UPDATE
		/**
		 * Sends an anonymous telemetry event.
		 *
		 * This call is asynchronous. Responses come to the ITelemetryEventSendListener.
		 *
		 * @remark After each call to SendTelemetryEvent() or SendAnonymousTelemetryEvent()
		 * all parameters are cleared automatically as if you called ClearParams().
		 *
		 * @remark Internal event index returned by this method should only be used
		 * to identify sent events in callbacks that come to the ITelemetryEventSendListener.
		 *
		 * @param [in] eventType The type of the event.
		 * @param [in] listener The listener for specific operation.
		 * @return Internal event index.
		 */
		virtual uint32_t SendAnonymousTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener = NULL) override;
#endif

#if GALAXY_BUILD_FEATURE_ITELEMETRY_1_139_7_UPDATE
		/**
		 * Retrieves current VisitID.
		 *
		 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
		 *
		 * @return Visit ID.
		 */
		virtual const char* GetVisitID() override;

		/**
		 * Copies current VisitID.
		 *
		 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
		 *
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		virtual void GetVisitIDCopy(char* buffer, uint32_t bufferLength) override;

		/**
		 * Resets current VisitID.
		 *
		 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
		 */
		virtual void ResetVisitID() override;
#endif

	};

	/** @} */
}

#endif
