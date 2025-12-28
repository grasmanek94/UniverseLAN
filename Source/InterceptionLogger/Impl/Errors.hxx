#ifndef UNIVERSELAN_IMPL_ERRORS_H
#define UNIVERSELAN_IMPL_ERRORS_H

/**
 * @file
 * Contains classes representing exceptions.
 */

#include <GalaxyFunctional.hxx>

#include <GalaxyExport.h>
#include <Errors.h>

namespace universelan::client {
	using namespace galaxy::api;

	 /**
	  * Base interface for exceptions.
	  */
	class Error : public IError
	{
	public:
		using FuncT = functional::xt<std::function<const IError* GALAXY_CALLTYPE(void)>>;
		using FuncPtr = typename FuncT::PTR;

	private:
		FuncT::F intf;

	public:
		Error(FuncT::F intf);

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

		virtual bool HasError() const;
	};
	/** @} */
}

#endif
