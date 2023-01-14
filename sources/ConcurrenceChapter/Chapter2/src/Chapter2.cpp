#include "Chapter2.h"
#include "../func/func_list.h"

#include <thread>
void CcChapter2BackgroundTask(const char* msgIn, char* msgOut)
{
	// 1. default build bt
	// 2. overload (): bt()
	// 3. copy obj to new thread space;
	// 4. avoid vexing parase. 
	//		4.1 std::thread my_thread(background_task()) a function ptr
	//		4.2 std::thread my_thread{background_task()}
	//		4.3 lambda expression
	BackgroundTask bt;
	std::thread t(bt);
	t.join();
}


void CcChapter2FuncOops(const char* msgIn, char* msgOut)
{
	// 1. it wll cause call a destroyed variety error
	int some_local_state = 0;
	Func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();
}

