/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:
  *Author:chenhui.shi
  *Version:
  *Date:3/25/21
  *Description:
  *Function List:
  *History:
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/

#ifndef COMMON_WHEELS_WITH_CPULSPULS_THREADPOLL_H
#define COMMON_WHEELS_WITH_CPULSPULS_THREADPOLL_H


#include <list>
#include <thread>
#include <functional>
#include <atomic>
#include "SyncQueue.h"

class ThreadPoll {
public:
    using Task = std::function<void()>;
    ThreadPoll(const int MaxCount);
    ~ThreadPoll();
    void start();
    void stop();
    void AddTask(Task&& task);
    void AddTask(const Task& task);
private:
    void runInThread();
    void stopThreadGroup();
    std::list<std::shared_ptr<std::thread> > _threadGroup;
    int numThreads;
    SyncQueue<Task> _queue;
    atomic_bool _threadPollRunning;
    std::once_flag _flag;
};



#endif //COMMON_WHEELS_WITH_CPULSPULS_THREADPOLL_H
