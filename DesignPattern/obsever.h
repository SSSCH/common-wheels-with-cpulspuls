/**
 * @file        obsever.h
 * @brief	    This is a brief description.
 * @details	    This is the detail description.
 * @author		
 * @date		6/5/21
 * @version	    v1.0
 * @par Copyright(c): 	Copyright (c) 2021 cygnus
 * @par History:         
 * @par Change History:         
 *----------------------------------------------------------------------------*
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  6/5/21    | 1.0.0.1   |                | Create file                    *
 *----------------------------------------------------------------------------*
*/
#include <iostream>
#include <memory>
#include <list>

class observer{
public:
    virtual void update() = 0;
    virtual ~observer() = default;
private:
};

class rrc : public observer{
public:
    rrc(){std::cout << "construct rrc" << std::endl;}
    void update() override{
        std::cout << "hi rrc" << std::endl;
    }
    ~rrc(){
        std::cout << "destruct rrc" << std::endl;
    }
private:

};
class subject{
public:
    void notify(){
        for(const auto & ob : _obList)
            ob->update();
    }
    void Attach(const std::shared_ptr<observer>& ob){
        _obList.push_back(ob);
        std::cout << "observer num:" << _obList.size() << std::endl;
    }
    void Detach(const std::shared_ptr<observer>& ob){
        _obList.remove(ob);
        std::cout << "observer num:" << _obList.size() << std::endl;
    }
    virtual ~subject() = default;
private:
    std::list<std::shared_ptr<observer>> _obList;
};



class os : public subject{
public:
    void getMsg(){}
    void sndMsg(){
        notify();
    }
    ~os(){
        std::cout << "destruct os" << std::endl;
    }
private:
};