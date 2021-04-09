/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:
  *Author:chenhui.shi
  *Version:
  *Date:2021/4/7
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

#include "builder.h"
computer::computerBuilder computer::builder;

computer::computer(computer::computerBuilder &builder) {
    this->cpu = builder.getCpu();
    this->ram = builder.getRam();
    this->display = builder.getdisplay();
    this->keyBoard = builder.getkeyBoard();
    this->usbCount = builder.getUsbCount();
}

void computer::show() {
    std::cout << "cpu:" << cpu
              << ",ram:" << ram
              << ",keyBoard:" << keyBoard
              << ",display:" << display
              << ",usbCount:" << usbCount << std::endl;
}

computer::computerBuilder& computer::computerBuilder::setKeyBoard(const string keyBoard) {
    computer::builder.keyBoard = keyBoard;
    return computer::builder;
}

computer::computerBuilder& computer::computerBuilder::setUsbCount(const int usbCount) {
    computer::builder.usbCount = usbCount;
    return computer::builder;
}
computer::computerBuilder& computer::computerBuilder::setdisplay(const string display) {
    computer::builder.display = display;
    return computer::builder;
}
computer::computerBuilder& computer::computerBuilder::setCpu(const string cpu) {
    computer::builder.cpu = cpu;
    return computer::builder;
}
computer::computerBuilder& computer::computerBuilder::setRam(const string ram) {
    computer::builder.ram = ram;
    return computer::builder;
}
computer* computer::computerBuilder::build() {
    return new computer(computer::builder);

}

string computer::computerBuilder::getCpu() {
    return this->cpu;
}

string computer::computerBuilder::getRam() {
    return this->ram;
}

string computer::computerBuilder::getdisplay() {
    return this->display;
}

string  computer::computerBuilder::getkeyBoard() {
    return this->keyBoard;
}

int computer::computerBuilder::getUsbCount() {
    return this->usbCount;
}

computer::computerBuilder::computerBuilder() : cpu("null"), ram("null"), keyBoard("null"), usbCount(0), display("null") {

}
