#ifndef CC_PATH_H
#define CC_PATH_H

#include <string>
#include <vector>
#if defined(CC_PATH_LIB)
#define CC_PATH_API __declspec(dllexport)
#else
#define CC_PATH_API __declspec(dllimport)
#endif

CC_PATH_API std::vector<std::string> CcSpiltStringBySeparator(const std::string& sourceStr, const std::string& separator);

CC_PATH_API std::string CcGetOutPutDir();

#endif