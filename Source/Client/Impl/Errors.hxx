#ifndef UNIVERSELAN_IMPL_ERRORS_H
#define UNIVERSELAN_IMPL_ERRORS_H

/**
 * @file
 * Contains classes representing exceptions.
 */

#include <Errors.h>
#include <GalaxyExport.h>

namespace universelan::client {
	using namespace galaxy::api;

	 /**
	  * Base interface for exceptions.
	  */
	class Error : public IError
	{
	public:

		virtual ~Error();

		/**
		 * Returns the name of the error.
		 *
		 * @return The name of the error.
		 */
		virtual const char* GetName() const override;

		/**
		 * Returns the error message.
		 *
		 * @return The error message.
		 */
		virtual const char* GetMsg() const override;

		/**
		 * Returns the type of the error.
		 *
		 * @return The type of the error.
		 */
		virtual Type GetType() const override;
	};

	/**
	 * The exception thrown when calling Galaxy interfaces while
	 * the user is not signed in and thus not authorized for any interaction.
	 */
	class UnauthorizedAccessError : public Error
	{
		/**
		 * Returns the type of the error.
		 *
		 * @return The type of the error.
		 */
		virtual Type GetType() const override;
	};

	/**
	 * The exception thrown to report that a method was called with an invalid argument.
	 */
	class InvalidArgumentError : public Error
	{
		/**
		 * Returns the type of the error.
		 *
		 * @return The type of the error.
		 */
		virtual Type GetType() const override;
	};

	/**
	 * The exception thrown to report that a method was called while the callee is in
	 * an invalid state, i.e. should not have been called the way it was at that time.
	 */
	class InvalidStateError : public Error
	{
		/**
		 * Returns the type of the error.
		 *
		 * @return The type of the error.
		 */
		virtual Type GetType() const override;
	};

	/**
	 * The exception thrown to report errors that can only be detected during runtime.
	 */
	class RuntimeError : public Error
	{
		/**
		 * Returns the type of the error.
		 *
		 * @return The type of the error.
		 */
		virtual Type GetType() const override;
	};

	/** @} */
}

#endif
