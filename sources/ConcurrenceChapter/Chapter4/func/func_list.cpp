#include "func_list.h"

#include <iostream>
void hello_func()
{
	std::cout << "Hello Concurrent World\n";
}

void f(int i, std::string const& s)
{
	std::cout << i << " " << s.c_str() << std::endl;
}

void do_something()
{
	std::cout << "do something" << std::endl;
}
