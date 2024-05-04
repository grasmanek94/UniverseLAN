#ifndef UNIVERSELAN_IMPL_ERRORS_H
#define UNIVERSELAN_IMPL_ERRORS_H

/**
 * @file
 * Contains classes representing exceptions.
 */

#include <Errors.h>

namespace universelan::client {
	using namespace galaxy::api;
	struct InterfaceInstances;

	 /**
	  * Base interface for exceptions.
	  */
	class Error : public IError
	{
	private:
		InterfaceInstances* intf;

	public:
		Error(InterfaceInstances* intf);

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
	/** @} */
}

#endif
