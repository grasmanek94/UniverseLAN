#include "Errors.hxx"

namespace galaxy
{
	namespace api
	{
		Error::~Error()
		{
		}

		const char* Error::GetName() const {
			return "Generic Unknown Error";
		}

		const char* Error::GetMsg() const {
			return "Generic Unknown Error";
		}

		IError::Type Error::GetType() const {
			return RUNTIME_ERROR;
		}

		IError::Type UnauthorizedAccessError::GetType() const {
			return UNAUTHORIZED_ACCESS;
		}

		IError::Type InvalidArgumentError::GetType() const {
			return INVALID_ARGUMENT;
		}

		IError::Type InvalidStateError::GetType() const {
			return INVALID_STATE;
		}

		IError::Type RuntimeError::GetType() const {
			return RUNTIME_ERROR;
		}
	}
}
