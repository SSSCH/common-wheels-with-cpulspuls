/*********************************************************************************
  *Copyright(C),Your Company
  *FileName:
  *Author:chenhui.shi
  *Version:
  *Date:3/25/21
  *Description: singleton mode
  *Function List:
  *History:
     1.Date:
       Author:
       Modification:
     2.…………
**********************************************************************************/

#ifndef COMMON_WHEELS_WITH_CPULSPULS_SINGLETON_H
#define COMMON_WHEELS_WITH_CPULSPULS_SINGLETON_H
#include <atomic>
#include <mutex>
#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class singleton {
public:
/* 注意：shared_ptr初始化时会调用默认构造函数和拷贝构造函数，所以不能delete，此外如果基类delete了构造函数，则在继承类中无需再delete了
 * shared_ptr无法访问私有的构造函数，析构函数
  singleton() = delete;
    singleton(const singleton<T>&) = delete;*/
    singleton<T>& operator=(const singleton<T>&) = delete;

    virtual ~singleton(){
        cout << "singleton desconstruct" << endl;
    }

    static shared_ptr<T>& GetInstance(){
        cout << "get singleton instance" << endl;
        if(_Instance == nullptr)
            std::call_once(_flag, [&](){_Instance = make_shared<T>();});
        //cout << "instance use count:" << _Instance.use_count() << endl;
        else
            cout << "instance is exist" << endl;
        return _Instance;
    }

private:
    static shared_ptr<T> _Instance;
    static std::once_flag _flag;

};

template<typename T>
shared_ptr<T> singleton<T>::_Instance(nullptr);
template<typename T>
std::once_flag singleton<T>::_flag;

#endif //COMMON_WHEELS_WITH_CPULSPULS_SINGLETON_H
