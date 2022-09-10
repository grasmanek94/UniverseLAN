/**
 * @file
 * Contains classes representing exceptions.
 */

#include "Errors.h"
#include "GalaxyExport.h"

#include "Errors.hxx"

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		 /**
		  * Base interface for exceptions.
		  */


		Error::~Error()
		{
		}

		/**
		 * Returns the name of the error.
		 *
		 * @return The name of the error.
		 */
		const char* Error::GetName() const {
			return "Generic Unknown Error";
		}

		/**
		 * Returns the error message.
		 *
		 * @return The error message.
		 */
		const char* Error::GetMsg() const {
			return "Generic Unknown Error";
		}

		/**
		 * Returns the type of the error.
		 *
		 * @return The type of the error.
		 */
		IError::Type Error::GetType() const {
			return RUNTIME_ERROR;
		}

		/**
		 * The exception thrown when calling Galaxy interfaces while
		 * the user is not signed in and thus not authorized for any interaction.
		 */

		 /**
		  * Returns the type of the error.
		  *
		  * @return The type of the error.
		  */
		IError::Type UnauthorizedAccessError::GetType() const {
			return UNAUTHORIZED_ACCESS;
		}


		/**
		 * The exception thrown to report that a method was called with an invalid argument.
		 */

		 /**
		  * Returns the type of the error.
		  *
		  * @return The type of the error.
		  */
		IError::Type InvalidArgumentError::GetType() const {
			return INVALID_ARGUMENT;
		}

		/**
		 * The exception thrown to report that a method was called while the callee is in
		 * an invalid state, i.e. should not have been called the way it was at that time.
		 */

		 /**
		  * Returns the type of the error.
		  *
		  * @return The type of the error.
		  */
		IError::Type InvalidStateError::GetType() const {
			return INVALID_STATE;
		}

		/**
		 * The exception thrown to report errors that can only be detected during runtime.
		 */

		 /**
		  * Returns the type of the error.
		  *
		  * @return The type of the error.
		  */
		IError::Type RuntimeError::GetType() const {
			return RUNTIME_ERROR;
		}

		/** @} */
	}
}
