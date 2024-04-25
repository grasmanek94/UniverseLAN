#pragma once

#include <Unet_common.h>

namespace Unet
{
	namespace System
	{
		std::string ResolvePathName(const std::string &path);

		bool FolderExists(const char* path);
		void FolderCreate(const char* path);
	}
}
