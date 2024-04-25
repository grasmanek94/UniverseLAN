#include <Unet_common.h>
#include <Unet/System.h>

#include <Windows.h>

#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include <ShlObj.h>
#pragma comment(lib, "Shell32.lib")

std::string Unet::System::ResolvePathName(const std::string &path)
{
	char fullPath[MAX_PATH];
	GetFullPathNameA(path.c_str(), MAX_PATH, fullPath, nullptr);
	return fullPath;
}

bool Unet::System::FolderExists(const char* path)
{
	if (PathIsDirectoryA(path)) {
		return true;
	}
	return false;
}

void Unet::System::FolderCreate(const char* path)
{
	std::string resolvedPath = ResolvePathName(path);
	SHCreateDirectoryExA(NULL, resolvedPath.c_str(), NULL);
}
