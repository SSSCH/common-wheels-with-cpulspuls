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

#ifndef COMMON_WHEELS_WITH_CPULSPULS_SYNCQUEUE_H
#define COMMON_WHEELS_WITH_CPULSPULS_SYNCQUEUE_H

#include <mutex>
#include <list>
#include <thread>
#include <pthread.h>
#include <iostream>
#include <condition_variable>


using namespace std;

template<typename T>
class SyncQueue {
public:
    SyncQueue() = delete;
    SyncQueue<T>& operator=(const SyncQueue<T> &) = delete;
    SyncQueue(const SyncQueue<T>&) = delete;

    SyncQueue(int size) : maxSize(size), isNeddStop(false){

    }
    ~SyncQueue(){
        _queue.clear();
    }
    void put(const T& t){
        Add(t);
    }
    void put(T&& t){
        Add(std::forward<T>(t));
    }
    bool take(std::list<T>& queue){
        std::unique_lock<std::mutex> locker(_mutex);
        _notEmpty.wait(locker, [this]{return isNeddStop || notEmpty(); });
        if(isNeddStop)
            return false;
        queue = std::move(_queue);
        cout << "take one task,current taskNum:" << _queue.size() << endl;
        _notEmpty.notify_one();
        return true;
    }
    bool take(T& t){
        std::unique_lock<std::mutex> locker(_mutex);
        _notEmpty.wait(locker, [this]{return isNeddStop || notEmpty(); });
        if(isNeddStop)
            return false;
        t = _queue.front();
        _queue.pop_front();
        cout << "take one task,current taskNum:" << _queue.size() << endl;
        _notEmpty.notify_one();
        return true;
    }
    bool isEmpty() const{
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.empty();
    }
    bool isFull() const{
        std::lock_guard<std::mutex> locker(_mutex);
        return _queue.size() == maxSize;
    }
    void stop(){
        {
            std::lock_guard<std::mutex> locker(_mutex);
            isNeddStop = true;
        }
        _notEmpty.notify_all(); //make all take() back
        _notFull.notify_all();  //make all Add() back

    }

private:
    std::list<T> _queue;
    std::mutex _mutex;
    std::condition_variable _notEmpty;
    std::condition_variable _notFull;
    size_t maxSize; //queue max size
    bool isNeddStop;
    bool notEmpty() const{
        bool empty = _queue.empty();
        if(empty)
            cout << "syncQueue is empty...unsyncThreadid：" << this_thread::get_id() << endl;
        return !empty;
    }
    bool notFull() const{
        bool full = _queue.size() >= maxSize;
        if(full)
            cout << "syncQueue is full...unsyncTheradid:" << this_thread::get_id() << endl;
        return !full;
    }

    template<typename F>
    void Add(F&& f){
        std::unique_lock<std::mutex> locker(_mutex);
        _notFull.wait(locker, [this]{return isNeddStop || notFull();});
        if(isNeddStop)
            return;

        _queue.push_back(std::forward<F>(f));
        std::cout << "add one task, current task num:" << _queue.size() << std::endl;
        _notEmpty.notify_one();
    }

};


#endif //COMMON_WHEELS_WITH_CPULSPULS_SYNCQUEUE_H
