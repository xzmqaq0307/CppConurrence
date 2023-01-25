## Chapter3 线程间共享数据

### 3.1 共享数据带来的问题

#### 3.1.1 不变量

- **不变量：**通常会在一次更新中被破坏，特别是比较复杂的数据结构，或者一次更新就要改动很大的数据结构
- 线程间的潜在问题就是**修改共享数据，导致不变量遭到破坏**

#### 3.1.2 条件竞争

- **良性竞争：**即使改变执行顺序，也不对数据操作结果影响
- **恶心竞争：**并发的去修改一个独立对象，通常发生于对多于一个的数据块的修改时候

### 3.2 使用互斥量保护共享数据

#### 3.2.1 使用互斥量

- `std::mutex`创建互斥量
- 直接调用成员函数：通过`lock`进行上锁，通过`unlock`进行解锁
- 或者通过`RAII`语法的模板类：`std::lock_guard`进行上锁、构造时上锁，析构时解锁

```cpp
#include <list>
#include <mutex>
#include <algorithm>

std::list<int> some_list;    // 1
std::mutex some_mutex;    // 2

void add_to_list(int new_value)
{
  std::lock_guard<std::mutex> guard(some_mutex);    // 3
  some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
  std::lock_guard<std::mutex> guard(some_mutex);    // 4
  return std::find(some_list.begin(),some_list.end(),value_to_find) != some_list.end();
}
```

- **互斥量通常会与保护的数据放在同一个类中**，而不是定义成全局变量
- 执行函数过程一般作为类的成员函数

#### 3.2.2 保护共享数据

- **切勿将受保护数据的指针或引用传递到互斥锁作用域之外**，无论是函数返回值，还是存储在外部可见内存，亦或是以参数的形式传递到用户提供的函数中去。

#### 3.2.3 消除接口间的条件竞争

- **传入一个引用**

```cpp
std::vector<int> result;
some_stack.pop(result);
```

- **无异常抛出的拷贝构造函数或移动构造函数**
- **返回指向弹出值的指针**

```cpp
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack: std::exception
{
  const char* what() const throw() {
    return "empty stack!";
  };
};

template<typename T>
class threadsafe_stack
{
private:
  std::stack<T> data;
  mutable std::mutex m;

public:
  threadsafe_stack()
    : data(std::stack<int>()){}

  threadsafe_stack(const threadsafe_stack& other)
  {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data; // 1 在构造函数体中的执行拷贝
  }

  threadsafe_stack& operator=(const threadsafe_stack&) = delete;

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
  }

  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack(); // 在调用pop前，检查栈是否为空

    std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 在修改堆栈前，分配出返回值
    data.pop();
    return res;
  }

  void pop(T& value)
  {
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();

    value=data.top();
    data.pop();
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};
```

#### 3.2.4 死锁描述以及解决方案

- 使用`std::lock`对多个实例进行同时上锁，避免死锁状态
- **避免嵌套锁：**一个线程已获得一个锁的时候，不要再获得第二个锁
- **避免在持有锁时调用用户提供的代码：**
- **使用固定顺序获取锁：**
  - 当硬性条件要求你获取两个以上(包括两个)的锁，并且不能使用`std::lock`单独操作来获取它们;那么最好在每个线程上，用固定的顺序获取它们获取它们(锁)。
  - 这里提供一种避免死锁的方式，定义遍历的顺序，所以一个线程必须先锁住A才能获取B的锁，在锁住B之后才能获取C的锁。
- **使用锁的层次结构**
  - 