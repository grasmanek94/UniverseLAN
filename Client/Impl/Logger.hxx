#ifndef LSFDRMFG_IMPL_LOGGING_H
#define LSFDRMFG_IMPL_LOGGING_H

/**
 * @file
 * Contains data structures and interfaces related to logging.
 */
#include "InterfaceInstances.hxx"

#include <ILogger.h>

#include <fstream>
#include <mutex>

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
			using mtx_t = std::mutex;
			using lock_t = std::scoped_lock<mtx_t>;

			InterfaceInstances* intf;
			mtx_t mtx;
			std::ofstream logfile;

			void Log(const char* type, const char* format, ...);

		public:
			LoggerImpl(InterfaceInstances* intf);

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
