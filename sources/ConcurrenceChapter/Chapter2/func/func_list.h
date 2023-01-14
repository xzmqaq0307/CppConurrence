#ifndef FUNC_LIST_H
#define FUNC_LIST_H
#include <iostream>

class BackgroundTask
{
public:
	void do_something() const
	{
		std::cout << "do_something" << std::endl;
	}

	void do_something_else() const
	{
		std::cout << "do something else" << std::endl;
	}

	void operator()() const
	{
		do_something();
		do_something_else();
	}
};


struct Func
{
	int& i;
	Func(int &i_) : i(i_) {}

	void do_something(int i_)
	{
		std::cout << i_ << std::endl;
	}

	void operator()()
	{
		for (unsigned j = 0; j < 1000000; ++j)
		{
			do_something(i);
		}
	}
};
#endif