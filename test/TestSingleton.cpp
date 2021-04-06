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
int main(){

    shared_ptr<singletonSon> instance =  singleton<singletonSon>::GetInstance();
    //shared_ptr<int> instance1 =  singleton<int>::GetInstance();
    //instance->a = 777;
    //std::cout << "i am a instance:" << *instance << "instance use count:" << instance.use_count()<< std::endl;
    instance->printa();
}
