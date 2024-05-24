#ifndef GALAXY_I_TELEMETRY_H
#define GALAXY_I_TELEMETRY_H

/**
 * @file
 * Contains data structures and interfaces related to telemetry.
 */

#include "IListenerRegistrar.h"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * Listener for the event of sending a telemetry event.
		 */
		class ITelemetryEventSendListener : public GalaxyTypeAwareListener<TELEMETRY_EVENT_SEND_LISTENER>
		{
		public:

			/**
			 * Notification for the event of sending a telemetry event.
			 *
			 * @param [in] eventType The type of the event.
			 * @param [in] sentEventIndex The internal index of the sent event.
			 */
			virtual void OnTelemetryEventSendSuccess(const char* eventType, uint32_t sentEventIndex) = 0;

			/**
			 * The reason of a failure in sending a telemetry event.
			 */
			enum FailureReason
			{
				FAILURE_REASON_UNDEFINED, ///< Unspecified error.
				FAILURE_REASON_CLIENT_FORBIDDEN, ///< Sending telemetry events is forbidden for this application.
				FAILURE_REASON_INVALID_DATA, ///< The event of given type and form does not match specification.
				FAILURE_REASON_CONNECTION_FAILURE, ///< Unable to communicate with backend services.
				FAILURE_REASON_NO_SAMPLING_CLASS_IN_CONFIG, ///< The event sampling class not present in configuration.
				FAILURE_REASON_SAMPLING_CLASS_FIELD_MISSING, ///< Sampling class' field not present in the event.
				FAILURE_REASON_EVENT_SAMPLED_OUT ///< The event did not match sampling criteria.
			};

			/**
			 * Notification for the event of a failure in sending a telemetry event.
			 *
			 * @param [in] eventType The type of the event.
			 * @param [in] sentEventIndex The internal index of the sent event.
			 * @param [in] failureReason The cause of the failure.
			 */
			virtual void OnTelemetryEventSendFailure(const char* eventType, uint32_t sentEventIndex, FailureReason failureReason) = 0;
		};

		/**
		 * Globally self-registering version of ITelemetryEventSendListener.
		 */
		typedef SelfRegisteringListener<ITelemetryEventSendListener> GlobalTelemetryEventSendListener;


		/**
		* Globally self-registering version of ITelemetryEventSendListener for the Game Server.
		*/
		typedef SelfRegisteringListener<ITelemetryEventSendListener, GameServerListenerRegistrar> GameServerGlobalTelemetryEventSendListener;

		/**
		 * The interface for handling telemetry.
		 */
		class ITelemetry
		{
		public:

			virtual ~ITelemetry()
			{
			}

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
			virtual void AddStringParam(const char* name, const char* value) = 0;

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
			virtual void AddIntParam(const char* name, int32_t value) = 0;

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
			virtual void AddFloatParam(const char* name, double value) = 0;

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
			virtual void AddBoolParam(const char* name, bool value) = 0;

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
			virtual void AddObjectParam(const char* name) = 0;

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
			virtual void AddArrayParam(const char* name) = 0;

			/**
			 * Closes an object or array parameter and leaves its scope.
			 *
			 * This allows for adding parameters to the upper scope.
			 *
			 * @remark Once closed, an object or array cannot be extended with new parameters.
			 *
			 * @remark Has no effect on simple parameters as well as on the event object itself.
			 */
			virtual void CloseParam() = 0;

			/**
			 * Clears all parameters that may have been set so far at any level.
			 *
			 * This allows for safely starting to build an event from scratch.
			 */
			virtual void ClearParams() = 0;


			/**
			 * Sets a sampling class to be applied next time you call SendTelemetryEvent()
			 * or SendAnonymousTelemetryEvent().
			 *
			 * @param [in] name The name of the sampling class.
			 */
			virtual void SetSamplingClass(const char* name) = 0;

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
			 * @param [in] listener The listener for specific operation [EXPERIMENTAL].
			 * @return Internal event index.
			 */
			virtual uint32_t SendTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener = NULL) = 0;

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
			 * @param [in] listener The listener for specific operation [EXPERIMENTAL].
			 * @return Internal event index.
			 */
			virtual uint32_t SendAnonymousTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener = NULL) = 0;

			/**
			 * Retrieves current VisitID.
			 *
			 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
			 *
			 * @return Visit ID.
			 */
			virtual const char* GetVisitID() = 0;

			/**
			 * Copies current VisitID.
			 *
			 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
			 *
			 * @param [in, out] buffer The output buffer.
			 * @param [in] bufferLength The size of the output buffer.
			 */
			virtual void GetVisitIDCopy(char* buffer, uint32_t bufferLength) = 0;

			/**
			 * Resets current VisitID.
			 *
			 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
			 */
			virtual void ResetVisitID() = 0;
		};

		/** @} */
	}
}

#endif
