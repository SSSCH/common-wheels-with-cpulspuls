/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:
  *Author:chenhui.shi
  *Version:
  *Date:2021/4/12
  *Description:适配器模式
  *Others:将一个类的接口转换为客户希望的另一个接口。Adpter模式用于那些原本接口不兼容的的类可以一起工作,有三个类：
  * target是目标系统
  * adaptee是被适配系统
  * adapter是适配器
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
  *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/

#ifndef COMMON_WHEELS_WITH_CPULSPULS_ADAPTER_H
#define COMMON_WHEELS_WITH_CPULSPULS_ADAPTER_H

#include <iostream>
using namespace std;

class target{
public:
    virtual void getName(){std::cout << "this is adapter target" << std::endl;};
private:
};

class adaptee{
public:
    virtual void getMyName(){std::cout << "this adapter adaptee" << std::endl;};
private:
};

class adapter : public target{
public:
    adapter(std::shared_ptr<adaptee> ad) : _ad(ad){}
    void getName() override{
        _ad->getMyName();
    }
private:
    std::shared_ptr<adaptee> _ad;
};
#endif //COMMON_WHEELS_WITH_CPULSPULS_ADAPTER_H
