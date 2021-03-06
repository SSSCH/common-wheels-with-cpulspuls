/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:
  *Author:chenhui.shi
  *Version:
  *Date:2021/4/6
  *Description:  //用于主要说明此程序文件完成的主要功能
                //与其他模块或函数的接口、输出值、取值范围、
                //含义及参数间的控制、顺序、独立及依赖关系
  *Others:  //其他内容说明
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
  *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/
#include "singleton.h"
#include "ThreadPoll.h"
#include "builder.h"
#include "prototype.h"
#include "adapter.h"
#include "bridge.h"
#include "Timer.h"
#include "templateMethod.h"
#include "strategy.h"
#include "obsever.h"
#include "decorator.h"

#include <thread>
#include <atomic>
#include <unistd.h>
#include <vector>


/** test singleton**/
class singletonSon : public singleton<singletonSon>{
public:

    virtual ~singletonSon(){
        cout << "singletonSon desconstruct" << endl;
    }
    void printa(){
        cout << "this is singletonSon,a =" << a << endl;
    }

private:
    int a = 0;
};

/***test threadpoll***/

ThreadPoll tp(40);
atomic_int threadPollTestNum;
void runInThread(){
    for (int i = 0; i < 20; ++i) {
        tp.AddTask([&](){++threadPollTestNum;});
    }
}

void timerCallBack(int a){
    auto timeNow = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    std::cout << "[" << timeNow.count() <<"]hello world" << a << std::endl;
}
void timerCallBack1(){
    auto timeNow = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    std::cout << "[" << timeNow.count() <<"]hello world1" << std::endl;
}

void startTimer(TimerQueue* tq, const int j){
    for (int i = 0; i < 5; ++i) {
        tq->addTimer(std::bind(timerCallBack, i+j), 1, true);
    }
/*    sleep(3);
    tq->stopTimer();*/
}
int main(){
    /** test singleton**/
    shared_ptr<singletonSon> instance =  singleton<singletonSon>::GetInstance();
    instance->printa();

    /**test threadpoll**/
    threadPollTestNum = 0;
    tp.start();
    std::thread th1(runInThread);
    std::thread th2(runInThread);
    std::thread th3(runInThread);
    std::thread th4(runInThread);
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    sleep(3);
    cout << "threadPollTestNum:" << threadPollTestNum << endl;
    tp.stop();

    /****test builder****/
    computer* mComputer = computer::builder.setCpu("intel")
                                          .setRam("sanxing")
                                          .setdisplay("jdf")
                                          .setUsbCount(7)
                                          .setKeyBoard("cherry")
                                          .build();
    mComputer->show();
    delete mComputer;


    /*****test prototype****/
    Diveried m;
    prototype n;
    auto mClone = m.clone();
    auto nClone = n.clone();
    mClone->print();
    nClone->print();

    /****test adapter****/
    auto adpe = std::make_shared<adaptee>();
    adpe->getMyName();

    auto mtarget = std::make_shared<adapter>(adpe);
    mtarget->getName();

    /****test bridge****/
    auto game = std::make_shared<concreteGame1>();
    auto phone = new conretePhone1;
    phone->setGame(game);
    phone->play();


    /***test timer***/
    auto mTq = new TimerQueue();
    mTq->startTimer();
    std::thread t(startTimer, mTq, 0);
    std::thread t1(startTimer, mTq, 5);
    std::thread t2(startTimer, mTq, 10);
    sleep(5);
    mTq->stopTimer();
    sleep(5);
    std::thread t3(startTimer, mTq, 0);
    mTq->startTimer();
    sleep(5);
    mTq->stopTimer();

    /***test template method**/

    sam::ball *mBall =  new sam::basketball() ;
    sam::ball *nBall = new sam::football();
    mBall->play();
    nBall->play();
    delete mBall;
    delete nBall;

    /*** test obsever***/
    auto  ob = std::make_shared<rrc>();
    auto sub = std::make_shared<os>();
    sub->Attach(ob);
    sub->sndMsg();
    sub->Detach(ob);

    /*** test decorator***/
    auto s1 = std::make_shared<fileStream>();
    auto s2 = std::make_shared<netWorkStream>();
    std::vector<std::unique_ptr<stream>> vec;
    vec.push_back(std::make_unique<cryptoStream>(s1));
    vec.push_back(std::make_unique<cryptoStream>(s2));
    vec.push_back(std::make_unique<cacheStream>(s1));
    vec.push_back(std::make_unique<cacheStream>(s2));
    for(const auto &stm : vec){
        stm->write();
        stm->read();
    }

  while (1){
        sleep(1);
    };
}
