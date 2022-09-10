/**
 * @file
 * Contains data structures and interfaces related to logging.
 */
#include "ILogger.h"

#include "Logger.hxx"

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

		Logger::~Logger()
		{
		}

		/**
		 * Creates a log entry with level TRACE.
		 *
		 * @param [in] format Format string.
		 * @param [in] ... Parameters for the format string.
		 */
		void Logger::Trace(const char* format, ...) {

		}

		/**
		 * Creates a log entry with level DEBUG.
		 *
		 * @param [in] format Format string.
		 * @param [in] ... Parameters for the format string.
		 */
		void Logger::Debug(const char* format, ...) {

		}

		/**
		 * Creates a log entry with level INFO.
		 *
		 * @param [in] format Format string.
		 * @param [in] ... Parameters for the format string.
		 */
		void Logger::Info(const char* format, ...) {

		}

		/**
		 * Creates a log entry with level WARNING.
		 *
		 * @param [in] format Format string.
		 * @param [in] ... Parameters for the format string.
		 */
		void Logger::Warning(const char* format, ...) {

		}

		/**
		 * Creates a log entry with level ERROR.
		 *
		 * @param [in] format Format string.
		 * @param [in] ... Parameters for the format string.
		 */
		void Logger::Error(const char* format, ...) {

		}

		/**
		 * Creates a log entry with level FATAL.
		 *
		 * @param [in] format Format string.
		 * @param [in] ... Parameters for the format string.
		 */
		void Logger::Fatal(const char* format, ...) {

		}

		/** @} */
	}
}


