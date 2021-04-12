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

#include <thread>
#include <list>
#include <functional>

#include "SyncQueue.h"
#include "ThreadPoll.h"

ThreadPoll::ThreadPoll(int MaxTaskCount)
        : numThreads(std::thread::hardware_concurrency()), _queue(MaxTaskCount), _threadPollRunning(false)
{
}
ThreadPoll::~ThreadPoll() {
    stop();
}


void ThreadPoll::start() {
    _threadPollRunning = true;
    std::cout << "Threadpoll start " << numThreads << "threads" << std::endl;

    for(int i = 0; i < numThreads; ++i){
        _threadGroup.push_back(std::make_shared<std::thread>(&ThreadPoll::runInThread, this));
    }
}

void ThreadPoll::runInThread() {
    while (_threadPollRunning){
        std::list<Task> _tasklist;
        //two ways to get&exec task
/*        if(_queue.take(_tasklist)){
            for(auto&  task : _tasklist){
                if(!_threadPollRunning)
                    return;
                else
                    task();
            }
        }*/

        Task task;
        if(_queue.take(task))
            task();
    }
}

void ThreadPoll::stopThreadGroup() {
    std::cout << "ThreadPoll stoped" << std::endl;
    _queue.stop();
    _threadPollRunning = false;
    for(auto& thread : _threadGroup){
        if (thread->joinable()) {
            thread->join();
        }
    }
    _threadGroup.clear();
}

void ThreadPoll::AddTask(Task &&task) {
    _queue.put(std::forward<Task>(task));
}

void ThreadPoll::AddTask(const Task &task) {
    _queue.put(task);
}

void ThreadPoll::stop() {
    //make sure call onec int muti thread
    std::call_once(_flag, [this]{stopThreadGroup();});
}