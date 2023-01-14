#ifndef CC_TOOL_H
#define CC_TOOL_H

#include <vector>
#include <string>

#if defined(CC_TOOL_LIB)
#define CC_TOOL_API __declspec(dllexport)
#else
#define CC_TOOL_API __declspec(dllimport)
#endif



#endif