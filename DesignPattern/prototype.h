/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:
  *Author:chenhui.shi
  *Version:
  *Date:2021/4/12
  *Description: 原型模式
  *Others:prototype的意义在于：你拿到一个Base*，它指向某个Derived对象，你想克隆出Derived对象，但代码中不写出Derived的具体类型，
  * 因为它有很多派生类，这种情况下你用构造函数是搞不定的，type-switch是bad smells.拷贝构造函数生成的新对象只能是类本身，原型模式生成的
  * 新对象可能是一个Derived对象。
  * 使用智能指针实现prototype
  * override 关键字代替virtual 关键字
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
  *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/

#ifndef COMMON_WHEELS_WITH_CPULSPULS_PROTOTYPE_H
#define COMMON_WHEELS_WITH_CPULSPULS_PROTOTYPE_H
#include <iostream>
#include <memory>

class prototype {
public:
    virtual std::unique_ptr<prototype> clone(){return std::make_unique<prototype>();}
    virtual void print(){std::cout<< "this is protoype" <<std::endl;}
private:
};

class Diveried : public prototype{
public:
     std::unique_ptr<prototype> clone() override{return std::make_unique<Diveried>();}
     void print() override{std::cout << "this is prototype Divered" << std::endl;};
private:
};


#endif //COMMON_WHEELS_WITH_CPULSPULS_PROTOTYPE_H
