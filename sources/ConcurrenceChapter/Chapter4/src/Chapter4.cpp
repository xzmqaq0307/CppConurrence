#include "Chapter4.h"
#include "../func/func_list.h"

#include <thread>
#include <mutex>

bool flag;
std::mutex m;

void CcChapter4WaitForFlag(char* msgIn, char* msgOut)
{
    auto wait_for_flag = []()
    {
        std::unique_lock<std::mutex> lk(m);
        while (!flag)
        {
            lk.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            lk.lock();
        }
    };
    wait_for_flag();
}

#include <queue>
#include <condition_variable>
std::mutex                  mut;
std::queue<int>             data_queue;
std::condition_variable     data_cond;
void CcChapter4ProcessData(char* msgIn, char* msgOut)
{
    auto more_data_to_prepare = []()
    {
        return false;
    };

    auto prepare_data = []()
    {
        return 1;
    };

    auto data_preparation_thread = [&]()
    {
        while (more_data_to_prepare())
        {
            int data = prepare_data();
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(data);
            data_cond.notify_one();
        }
    };

    auto data_process_thread = [&]()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lk(mut);
            data_cond.wait(lk, []() {return !data_queue.empty(); });
            int data = data_queue.front();
            data_queue.pop();
            lk.unlock();
            std::cout << data << std::endl;

        }
    };
}

