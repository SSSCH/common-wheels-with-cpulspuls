/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:
  *Author:chenhui.shi
  *Version:
  *Date:2021/4/12
  *Description:桥接模式
  *Others:用于将抽象化(abstraction)和实现化(implementaion)解耦，使得二者可以独立的变化
  * 抽象化：存在于多个实体中的共同的概念性关系，就是抽象化。作为一个过程，抽象化就是忽略一些细节，从而把不同的实体当做同样的实体对待，即Base类
  * 实现化：抽象化给出的具体实现，就是实现化，即Diveried
  * 脱耦：所谓耦合，就是两个实体的行为的某种强关联。而将他们的强关联去掉，就是耦合的解脱，或称脱耦。在这里，脱耦是指将抽象化和实现化之间的耦合解脱开，将强关联改为若关联。
  * 将两个类之间的关系从继承关系改为聚合关系，就是将它们之间的强关联换成弱关联。因此，桥接模式中的脱耦，就是指在一个软件系统的抽象化和实现化之间使用组合/聚合关系而不是继承关系，
  * 从而使两者可以相对独立的变化。
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
  *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/

#ifndef COMMON_WHEELS_WITH_CPULSPULS_BRIDGE_H
#define COMMON_WHEELS_WITH_CPULSPULS_BRIDGE_H
#include <iostream>
#include <memory>

using namespace std;

class abstractGame{
public:
    virtual void play() = 0;
private:
};


class abstractPhone{
public:
    virtual void setGame(const shared_ptr<abstractGame> &game) = 0;
    virtual void play() = 0;
private:
    std::shared_ptr<abstractGame> _game;
};


class concreteGame1 : public abstractGame{
public:
    void play() override{std::cout << "playing game1" << std::endl;}
private:
};

class conretePhone1 : public abstractPhone{
public:
    void setGame(const shared_ptr<abstractGame> &game) override{
        this->_game = game;
    }
    void play() override{
        this->_game->play();
    };
private:
    std::shared_ptr<abstractGame> _game;
};
#endif

