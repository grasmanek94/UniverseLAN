#ifndef GALAXY_I_LOGGER_H
#define GALAXY_I_LOGGER_H

/**
 * @file
 * Contains data structures and interfaces related to logging.
 */

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * The interface for logging.
		 */
		class ILogger
		{
		public:

			virtual ~ILogger()
			{
			}

			/**
			 * Creates a log entry with level TRACE.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Trace(const char* format, ...) = 0;

			/**
			 * Creates a log entry with level DEBUG.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Debug(const char* format, ...) = 0;

			/**
			 * Creates a log entry with level INFO.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Info(const char* format, ...) = 0;

			/**
			 * Creates a log entry with level WARNING.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Warning(const char* format, ...) = 0;

			/**
			 * Creates a log entry with level ERROR.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Error(const char* format, ...) = 0;

			/**
			 * Creates a log entry with level FATAL.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Fatal(const char* format, ...) = 0;
		};

		/** @} */
	}
}

#endif
