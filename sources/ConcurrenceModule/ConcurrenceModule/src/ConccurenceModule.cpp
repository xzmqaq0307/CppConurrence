#include "ConcurrencePath.h"

#include <iostream>
#include <Windows.h>
#include <initializer_list>
#include <unordered_map>

#define BUFF_SIZE 1024
char result[BUFF_SIZE];

void CcCallChapter(std::string chapter, std::string func, std::string data)
{
	/**
	* How To Call a DLL ?
	* 1. Define a wide char path dir variable
	* 2. Turn string to wstring. You can use ::MultiByteToWideChar
	* 3. Load dll with Absolute Path(LoadLibraryEx) or Relative Path(LoadLibraryA)
	* 4. Show DWORD to see error (126 means your dll lacks of some dependences)
	* 5. Load dll function with function name (GetProcAddress)
	* 6. Show DWORD to see error (127 means your function lacks of extern "C")
	* 7. Finished Load.
	* 8. Remember Free dll handle, UvU!
	*/

	WCHAR wszDLLDir[256] = { 0 };
	memset(wszDLLDir, 0, sizeof wszDLLDir);

	std::string outputPath = CcGetOutPutDir();
	std::string outputDLL = outputPath + chapter + ".dll";
	
	MultiByteToWideChar(CP_ACP, 0, outputDLL.c_str(), (int)(outputDLL.size() + 1), wszDLLDir, sizeof(wszDLLDir) / sizeof(wszDLLDir[0]));
	auto module = LoadLibraryEx(wszDLLDir, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	if (module == nullptr)
	{
		DWORD word = GetLastError();
		std::cout << word << ": Means your DLL lacks of some dependences" << std::endl;
		return;
	}
	else
	{
		// Receive an input, and return an output
		typedef void(*ChapterFunc)(const char*, char*);
		auto fn_Chapter = (ChapterFunc)GetProcAddress(module, func.c_str());
		if (fn_Chapter == nullptr)
		{
			DWORD word = GetLastError();
			std::cout << word << ": Means you dll function lacks of extern C" << std::endl;
		}
		
		try
		{
			fn_Chapter(data.c_str(), result);
			std::cout << result << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}

		FreeLibrary(module);
	}
}

std::string CcBuildParam(int cnt, ...)
{
	if (cnt % 2 != 0)
	{
		std::cout << "args should be even ...";
		system("pause");
	}

	va_list args;
	va_start(args, cnt);
	
	std::unordered_map<std::string, std::string> heap;
	for (int i = 0; i < cnt; i += 2)
	{
		std::string key = va_arg(args, const char*);
		std::string value = va_arg(args, const char*);
		heap.insert(std::make_pair(key, value));
	}

	return "";
}

int main()
{
#pragma region chapter_1
	CcCallChapter("Chapter1", "CcChapter1HelloWorld", "");

#pragma endregion

	return 0;
}