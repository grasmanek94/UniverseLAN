/**
 * @file
 * Contains data structures and interfaces related to telemetry.
 */

#include "ITelemetry.h"
#include "IListenerRegistrar.h"

#include "Telemetry.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		  * The interface for handling telemetry.
		  */
		Telemetry::~Telemetry()
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
		void Telemetry::AddStringParam(const char* name, const char* value) {

		}

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
		void Telemetry::AddIntParam(const char* name, int32_t value) {

		}

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
		void Telemetry::AddFloatParam(const char* name, double value) {

		}

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
		void Telemetry::AddBoolParam(const char* name, bool value) {

		}

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
		void Telemetry::AddObjectParam(const char* name) {

		}

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
		void Telemetry::AddArrayParam(const char* name) {

		}

		/**
		 * Closes an object or array parameter and leaves its scope.
		 *
		 * This allows for adding parameters to the upper scope.
		 *
		 * @remark Once closed, an object or array cannot be extended with new parameters.
		 *
		 * @remark Has no effect on simple parameters as well as on the event object itself.
		 */
		void Telemetry::CloseParam() {

		}

		/**
		 * Clears all parameters that may have been set so far at any level.
		 *
		 * This allows for safely starting to build an event from scratch.
		 */
		void Telemetry::ClearParams() {

		}


		/**
		 * Sets a sampling class to be applied next time you call SendTelemetryEvent()
		 * or SendAnonymousTelemetryEvent().
		 *
		 * @param [in] name The name of the sampling class.
		 */
		void Telemetry::SetSamplingClass(const char* name) {

		}

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
		uint32_t Telemetry::SendTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
			return 0;
		}

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
		uint32_t Telemetry::SendAnonymousTelemetryEvent(const char* eventType, ITelemetryEventSendListener* const listener) {
			return 0;
		}

		/**
		 * Retrieves current VisitID.
		 *
		 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
		 *
		 * @return Visit ID.
		 */
		const char* Telemetry::GetVisitID() {
			return "0";
		}

		/**
		 * Copies current VisitID.
		 *
		 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
		 *
		 * @param [in, out] buffer The output buffer.
		 * @param [in] bufferLength The size of the output buffer.
		 */
		void Telemetry::GetVisitIDCopy(char* buffer, uint32_t bufferLength) {

		}

		/**
		 * Resets current VisitID.
		 *
		 * Visit ID is used to link subsequent telemetry events that corresponds to the same action (e.x. game session).
		 */
		void Telemetry::ResetVisitID() {

		}

		/** @} */
	}
}


