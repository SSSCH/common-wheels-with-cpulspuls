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

#include <memory.h>
#include <error.h>
#include <unistd.h>
#include "Timer.h"
#include "ThreadPoll.h"


TimerId::TimerId(const int &timerId) : _timerId(timerId){}
int TimerId::getTimerId() const {
    return this->_timerId;
}
void TimerId::setTimerId(const int &timerId) {
    this->_timerId = timerId;
}



Timer::Timer(const func &callBack, long interval, bool isRepate) : _callBack(callBack), _interval(interval), _isRepate(isRepate){

}
const func & Timer::getCallBack() {
    return std::move(_callBack);
}

const int Timer::getTimerId() {
    return _timerId;
}

const bool Timer::isRepate() {
    return _isRepate;
}

const long Timer::getInterval() {
    return _interval;
}

TimerQueue::TimerQueue() : _epollFd(epoll_create(1)), _isTImerRunning(false){
    //std::cout << "_epollFd:" << _epollFd << std::endl;
}

TimerId TimerQueue::addTimer(const func& callBack, long interval, bool isRepate) {
    TimerId ret(0);
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));

    int timer_fd = _timerInit(callBack, interval, isRepate);
    if(timer_fd <= 0)
    {
        return ret;
    }

    if(_epollCtl(timer_fd, EPOLL_CTL_ADD) != 0){
        return ret;
    }

    _timerMap.emplace(std::make_pair(int(timer_fd), std::make_unique<Timer>(callBack, interval, isRepate)));
    ret.setTimerId(timer_fd);

    return ret;
}

void TimerQueue::startTimer() {
    {
        std::lock_guard<std::mutex> locker(_mMutex);
        if(_isTImerRunning)
            return;
        _isTImerRunning = true;
    }
    up = std::make_unique<std::thread>(&TimerQueue::_runInTimer, this);
}

void TimerQueue::stopTimer() {
    {
        std::lock_guard<std::mutex> locker(_mMutex);
        if(!_isTImerRunning)
            return;
        _isTImerRunning = false;
    }
    if(up->joinable())
        up->join();
    for(const auto &pair : _timerMap){
        _epollCtl(pair.first, EPOLL_CTL_DEL);
        close(pair.first);
        std::cout << "stop timer[" << pair.first << "]" << std::endl;
    }
    _timerMap.clear();

}

void TimerQueue::stopTimer(const TimerId &id) {
    _delTimer(id.getTimerId());
}

void TimerQueue::_delTimer(const int timerFd) {
    if(_timerMap.count(timerFd) == 1){
        _epollCtl(timerFd, EPOLL_CTL_DEL);
        close(timerFd);
        _timerMap.erase(timerFd);
        std::cout << "stop timer[" << timerFd << "]" << std::endl;
    }
}

void TimerQueue::_runInTimer() {
    epoll_event events[1024];
    int eventLen = 1024;
    if(_epollFd <= 0)
    {
        std::cout << "invalid epoll fd" << std::endl;
        return;
    }
    while(_isTImerRunning){
        uint64_t data = 0;
        memset(events, 0, sizeof(epoll_event)*1024);
        int activeFd = epoll_wait(_epollFd, events, eventLen, 1000);
        if(activeFd == 0)
        {
            //超时
            continue;
        }
        else if(activeFd < 0)
        {
            //调用出错
            //被信号中断
            if(errno == EINTR)
            {
                continue;
            }
            return;
        }

        for(int i = 0; i < activeFd; ++i)
        {
            if(events[i].events & EPOLLIN)
            {
                int timerFd = events[i].data.fd;
                //EPOLLET mode, if not read, only tiggred timerFd 1 time,EPOLLLT mode, if not read ,always tiggred timerFd
                read(timerFd, &data, sizeof(data));
                if(_timerMap.count(timerFd) == 1){
                    auto func = _timerMap[timerFd]->getCallBack();
                    func();
                }
            }
/*            else if(events[i].events & EPOLLOUT)
            {
                //可写事件就绪
            }
            else if(events[i].events & EPOLLERR)
            {
                //处理出错事件
            }*/
        }
    }
    std::cout << "TimerQueue::_runInTimer loop end" << std::endl;
}

TimerQueue::~TimerQueue() {
    close(_epollFd);
}

int TimerQueue::_timerInit(const func &callBack, long interval, bool isRepate) {
    struct itimerspec ts;
    memset(&ts, 0, sizeof(ts));

    int timer_fd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK | TFD_CLOEXEC);
    std::cout << "addTimer-timerId:" << timer_fd << "|interval:" << interval << "|isRepate:" << isRepate << std::endl;
    if(timer_fd <= 0){
        std::cout << "timerfd_create failed" << std::endl;
        return -1;
    }
    if(_epollFd <= 0){
        std::cout << "_epollFd is unormal" << std::endl;
        return -2;
    }
    ts.it_interval.tv_sec = isRepate ? interval : 0;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = interval;
    ts.it_value.tv_nsec = 0;

    if(timerfd_settime(timer_fd, 0, &ts, nullptr) < 0){
        std::cout << "timerfd_settime failed!" << errno << strerror(errno)<< std::endl;
        return -3;
    }
    return timer_fd;
}

int TimerQueue::_epollCtl(const int timerFd, const int op) {
    struct epoll_event ev;
    memset(&ev, 0, sizeof(ev));

    if(op == EPOLL_CTL_ADD){
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = timerFd;
        if(epoll_ctl(_epollFd, EPOLL_CTL_ADD, timerFd, &ev) != 0){
            std::cout << "epoll_ctl add timerfd failed" << std::endl;
            return -1;
        }
    }
    else if(op == EPOLL_CTL_DEL){
        epoll_ctl(_epollFd, EPOLL_CTL_DEL, timerFd, nullptr);
    }
    return 0;
}

int TimerQueue::TimerNum() {
    return _timerMap.size();
}




