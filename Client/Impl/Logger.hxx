#ifndef LSFDRMFG_IMPL_LOGGING_H
#define LSFDRMFG_IMPL_LOGGING_H

/**
 * @file
 * Contains data structures and interfaces related to logging.
 */
#include <ILogger.h>

#include <fstream>

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
		class LoggerImpl : public ILogger
		{
		private:
			std::ofstream logfile;

		public:
			LoggerImpl();

			virtual ~LoggerImpl() override;

			/**
			 * Creates a log entry with level TRACE.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Trace(const char* format, ...) override;

			/**
			 * Creates a log entry with level DEBUG.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Debug(const char* format, ...) override;

			/**
			 * Creates a log entry with level INFO.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Info(const char* format, ...) override;

			/**
			 * Creates a log entry with level WARNING.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Warning(const char* format, ...) override;

			/**
			 * Creates a log entry with level ERROR.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Error(const char* format, ...) override;

			/**
			 * Creates a log entry with level FATAL.
			 *
			 * @param [in] format Format string.
			 * @param [in] ... Parameters for the format string.
			 */
			virtual void Fatal(const char* format, ...) override;
		};

		/** @} */
	}
}

#endif
