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


using namespace std;

template<typename T>
class singleton {
public:
    singleton() = delete;
    singleton<T>& operator=(const singleton<T>&) = delete;
    //virtual ~singleton() = 0;
    static T* GetInstance(){
        if(_Instance == nullptr)
            std::call_once(_flag, [](){_Instance = new(T);});
        return _Instance;
    }
    void print(){
        std::cout << "this is a singleton instance" << std::endl;
    }

private:
    static atomic<T*> _Instance;
    static std::once_flag _flag;
    class Garbo{
    public:
        ~Garbo(){
            if(_Instance != nullptr){
                delete _Instance;
                _Instance = nullptr;
            }
        }
    };
    static Garbo _garbo;
};
template<typename T>
atomic<T*> singleton<T>::_Instance(nullptr);
template<typename T>
std::once_flag singleton<T>::_flag;

#endif //COMMON_WHEELS_WITH_CPULSPULS_SINGLETON_H
