#include <Unet_common.h>
#include <Unet/System.h>

#include <sys/stat.h>

std::string Unet::System::ResolvePathName(const std::string &path)
{
	char* newPath = realpath(path.c_str(), nullptr);
	std::string ret = newPath;
	free(newPath);
	return ret;
}

bool Unet::System::FolderExists(const char* path)
{
	struct stat sb;
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return true;
	return false;
}

void Unet::System::FolderCreate(const char* path)
{
	mkdir(path, 0775);
}
