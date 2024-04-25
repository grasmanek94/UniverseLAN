#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cinttypes>

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory>
#include <chrono>

#include <Unet/guid.hpp>

#include <Unet/json.hpp>
using json = nlohmann::json;

#include <Unet/Utils.h>
#include <Unet/System.h>

namespace Unet
{
	class IContext;
	class ICallbacks;

	class Lobby;
	class Service;

	namespace Internal
	{
		class Context;
	}
}
