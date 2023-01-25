#ifndef FUNC_LIST_H
#define FUNC_LIST_H
#include <iostream>
#include <thread>
#include <mutex>

#pragma region struction

// 1. ×°ÊÎ·½·¨
class HierarchicalMutex
{
	std::mutex internal_mutex;
	
	unsigned long const hierarchy_value;
	unsigned long previous_hierarchy_value;

	static thread_local unsigned long this_thread_hierarchy_value;

	void check_for_hierarchy_violation()
	{
		if (this_thread_hierarchy_value <= hierarchy_value)
		{
			throw std::logic_error("mutex hierarchy violated");
		}
	}

	void update_hirerachy_value()
	{
		previous_hierarchy_value = this_thread_hierarchy_value;
		this_thread_hierarchy_value = hierarchy_value;
	}

public:
	explicit HierarchicalMutex(unsigned long value) :
		hierarchy_value(value),
		previous_hierarchy_value(0)
	{}

	void lock()
	{
		check_for_hierarchy_violation();
		internal_mutex.lock();
		update_hirerachy_value();
	}

	void unlock()
	{
		this_thread_hierarchy_value = previous_hierarchy_value;
		internal_mutex.unlock();
	}

	bool try_lock()
	{
		check_for_hierarchy_violation();
		if (!internal_mutex.try_lock())
		{
			return false;
		}
		update_hirerachy_value();
		return true;
	}
};
#pragma endregion
#pragma region func

void f(int i, std::string const& s);

#pragma endregion

#endif