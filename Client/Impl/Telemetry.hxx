#ifndef LSFDRMFG_IMPL_TELEMETRY_H
#define LSFDRMFG_IMPL_TELEMETRY_H

/**
 * @file
 * Contains data structures and interfaces related to telemetry.
 */

#include "ITelemetry.h"
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
		 * The interface for handling telemetry.
		 */
		class Telemetry : public ITelemetry
		{
		public:

			virtual ~Telemetry();

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


			/**
			 * Sets a sampling class to be applied next time you call SendTelemetryEvent()
			 * or SendAnonymousTelemetryEvent().
			 *
			 * @param [in] name The name of the sampling class.
			 */
			virtual void SetSamplingClass(const char* name) override;

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
		};

		/** @} */
	}
}



#endif
