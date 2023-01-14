#include "Chapter1.h"
#include "../func/func_list.h"

#include <thread>
void CcChapter1HelloWorld(const char* msgIn, char* msgOut)
{
	std::thread t(hello_func);
	t.join();
}