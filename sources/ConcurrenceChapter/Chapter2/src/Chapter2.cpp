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

void CcChapter2FuncOopsWithException(const char* msgIn, char* msgOut)
{
	int some_local_state = 0;
	Func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		// do something in current thread;
	}
	catch (std::exception& e)
	{
		t.join();	// 1. make sure thread t will be called if exception happened
		throw;
	}
	t.join();		// 2. join thread
}

void CcChapter2FuncOopsWithRAII(const char* msgIn, char* msgOut)
{
	int some_local_state = 0;
	Func my_func(some_local_state);

	std::thread t(my_func);
	ThreadGuard g(t);	// 1. call destruct method
	// do something in current thread;
}

void CcChapter2EditDocument(const char* msgIn, char* msgOut)
{
	auto edit_document = [](std::string const& filename)
	{
		// open_document_and_display_gui(filename);
		//while (!done_editing())
		//{
		//	user_command cmd = get_user_input();
		//	if (cmd.type == open_new_document)
		//	{
		//		std::string const new_name = get_filename_from_user();
		//		std::thread t(edit_document, new_name);  // 1
		//		t.detach();  // 2
		//	}
		//	else
		//	{
		//		process_user_input(cmd);
		//	}
		//}
	};
}

void CcChapter2ConversionFuncArgs(const char* msgIn, char* msgOut)
{
	auto oops = [](int some_param)
	{
		char buffer[1024];
		sprintf(buffer, "%i", some_param);
		std::thread t(f, 3, buffer);
		t.detach();
	};
}

void CcChapter2ConversionFuncArgsNoOops(const char* msgIn, char* msgOut)
{
	auto not_oops = [](int some_param)
	{
		char buffer[1024];
		sprintf(buffer, "%i", some_param);
		std::thread t(f, 3, std::string(buffer));	// 1. no oops
		t.detach();
	};
}

void CcChapter2RefOopsAgain(const char* msgIn, char* msgOut)
{
	/*
	** @props: 当线程调用update_data_for_widget函数时，传递给函数的参数是data变量内部拷贝的引用，而非数据本身的引用
	*/
	// widget_data data;
	// std::thread t(update_data_for_widget, w, data);
	// display_status();
	// t.join();
	// process_widget_data(data);
}

void CcChapter2RefNoOops(const char* msgIn, char* msgOut)
{
	// widget_data data;
	// std::thread t(update_data_for_widget, w, std::ref(data));
	// display_status();
	// t.join();
	// process_widget_data(data);
}

void CcChapter2ConveyThreadObj(const char* msgIn, char* msgOut)
{
	class X
	{
	public:
		void do_lengthy_work() {};
	};
	X my_x;
	std::thread t(&X::do_lengthy_work, &my_x);
}

void CcChapter2ConveyThreadObjWithParam(const char* msgIn, char* msgOut)
{
	class X
	{
	public:
		void do_length_work(int) {};
	};
	X my_x;
	int num = 0;
	std::thread t(&X::do_length_work, &my_x, num);
}

void CcChapter2CheckThreadId(const char* msgIn, char* msgOut)
{
	std::thread::id master_thread;
	if (std::this_thread::get_id() == master_thread)
	{
		// do_master_thread_work();
	}
	//do_common_work();
}

