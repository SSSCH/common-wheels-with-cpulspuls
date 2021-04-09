/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:
  *Author:chenhui.shi
  *Version:
  *Date:2021/4/7
  *Description:建造者模式
  *Others: 应用场景：1.当一个类的构造函数参数个数超过(4个）时，而且这些参数有些是可选参数时，可以考虑使用建造者模式
  *                2.如果我们需要将一个复杂对象的构建与他的表示分离，是的同样的构建过程可以创建不同的表示的意图时，可以考虑使用builder模式
  *Function List:  //主要函数列表，每条记录应包含函数名及功能简要说明
     1.…………
     2.…………
  *History:  //修改历史记录列表，每条修改记录应包含修改日期、修改者及修改内容简介
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/

#ifndef COMMON_WHEELS_WITH_CPULSPULS_BUILDER_H
#define COMMON_WHEELS_WITH_CPULSPULS_BUILDER_H


#include <iostream>

using namespace std;

class computer{
public:
    computer() = delete;
    computer(const computer&) = delete;
    computer& operator=(const computer&) = delete;
    void show();

    class computerBuilder{
    public:
        //computerBuilder() = delete;
        computerBuilder(const computerBuilder&) = delete;
        computerBuilder& operator=(const computerBuilder&) = delete;
        //computerBuilder(const string cpu, const string arm);
        computerBuilder();
        computerBuilder& setCpu(const string cpu);
        computerBuilder& setRam(const string ram);
        computerBuilder& setKeyBoard(const string keyBoard);
        computerBuilder& setUsbCount(const int usbCount);
        computerBuilder& setdisplay(const string display);
        string getCpu();
        string getRam();
        string getkeyBoard();
        int getUsbCount();
        string getdisplay();

        computer* build();
    private:
        std::string cpu;
        std::string ram;
        int usbCount;
        std::string keyBoard;
        std::string display;
    };
    static computerBuilder builder;
private:
    std::string cpu;
    std::string ram;
    int usbCount;
    std::string keyBoard;
    std::string display;
    computer(computerBuilder& builder);

};


#endif //COMMON_WHEELS_WITH_CPULSPULS_BUILDER_H


