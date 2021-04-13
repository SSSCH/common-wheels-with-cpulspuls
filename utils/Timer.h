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

#ifndef COMMON_WHEELS_WITH_CPULSPULS_TIMER_H
#define COMMON_WHEELS_WITH_CPULSPULS_TIMER_H

#include <functional>
#include <thread>
#include <iostream>
#include <ctime>
#include <mutex>
#include <atomic>
#include <sys/timerfd.h>
#include <map>
#include <sys/epoll.h>
#include <memory>

using namespace std;

using func = std::function<void()>;

class TimerId{
public:
    TimerId& operator=(const TimerId&) = delete;
    explicit TimerId(const int &timerId);
    int getTimerId() const;
    void setTimerId(const int &timerId);
private:
    int _timerId;
};

class Timer {
public:
    Timer& operator=(Timer&) = delete;
    Timer(const Timer&) = delete;
    Timer(func  callBack, long interval, bool isRepate);
    const func& getCallBack();
    int getTimerId();
    long getInterval();
    bool isRepate();
private:
    func _callBack;
    int _timerId;
    long _interval;
    bool _isRepate;
};

class TimerQueue{
public:
    TimerQueue& operator=(const TimerQueue&) = delete;
    TimerQueue(const TimerQueue&) = delete;
    TimerQueue();
    ~TimerQueue();
    void startTimer();
    TimerId addTimer(const func& callBack, long interval, bool isRepate);
    void stopTimer();
    void stopTimer(const TimerId& id);
    int TimerNum();
private:
    std::mutex _mMutex;
    //<timerFd, timer>
    std::map<int, std::unique_ptr<Timer>> _timerMap;
    int _epollFd;
    std::atomic<bool> _isTImerRunning;
    void _runInTimer();
    std::unique_ptr<std::thread> up;
    void _delTimer(const int timerFd);
    int _timerInit(const func& callBack, long interval, bool isRepate) const;
    int _epollCtl(const int timerFd, const int op) const;
};

#endif //COMMON_WHEELS_WITH_CPULSPULS_TIMER_H
