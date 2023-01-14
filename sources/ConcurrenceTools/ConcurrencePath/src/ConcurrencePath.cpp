#include "ConcurrencePath.h"
#include "Windows.h"

#include <vector>
#include <string>

std::vector<std::string> CcSpiltStringBySeparator(
	const std::string& sourceStr,
	const std::string& separator
)
{
	std::vector<std::string> results;
	std::string::size_type pos1 = std::string::npos;
	std::string::size_type pos2 = std::string::npos;

	pos2 = sourceStr.find(separator);
	pos1 = 0;

	while (std::string::npos != pos2)
	{
		results.push_back(sourceStr.substr(pos1, pos2 - pos1));
		pos1 = pos2 + separator.size();
		pos2 = sourceStr.find(separator, pos1);
	}

	if (pos1 != sourceStr.length())
	{
		results.push_back(sourceStr.substr(pos1));
	}

	return results;
}

std::string CcGetOutPutDir()
{
	char path[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, path, MAX_PATH);

	std::string source(path);
	std::string separator("\\");
	std::vector<std::string> splitResult = CcSpiltStringBySeparator(source, separator);

	std::string controllerDir = "";
	int cnt = (int)splitResult.size() - 1;
	for (int i = 0; i < cnt; i++)
	{
		controllerDir.append(splitResult[i]);
		controllerDir.append("\\");
	}

	//if (std::string::npos == controllerDir.find("ConcurrenceModule"))
	//{
	//	controllerDir.append("ConcurrenceModule\\");
	//}

	return controllerDir;
}