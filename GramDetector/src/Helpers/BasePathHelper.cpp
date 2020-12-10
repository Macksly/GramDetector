#include "BasePathHelper.h"

using namespace GramDetector;

std::string Helpers::get_base_path()
{
	char path[MAX_PATH] = "";
	GetModuleFileNameA(NULL, path, MAX_PATH);
	std::string exePath = std::string(path);
	int index = std::string(exePath).find_last_of('\\');
	return exePath.substr(0, index);
}
