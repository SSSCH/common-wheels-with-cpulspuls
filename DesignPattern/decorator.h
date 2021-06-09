/**
 * @file        decorator.h
 * @brief	    This is a brief description.
 * @details	    This is the detail description.
 * @author		
 * @date		2021/6/8
 * @version	    v1.0
 * @par Copyright(c): 	Copyright (c) 2021 cygnus
 * @par History:         
 * @par Change History:         
 *----------------------------------------------------------------------------*
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  2021/6/8    | 1.0.0.1   |                | Create file                    *
 *----------------------------------------------------------------------------*
*/


#pragma once


#include<iostream>
#include <utility>
//abstruct base class
class stream{
public:
    virtual char read() = 0;
    virtual void write() = 0;
    virtual ~stream(){};
private:

};

//devried  clss
class fileStream : public stream{
public:
    char read() override{
        std::cout << "fileStream read" << std::endl;
    }
    void write() override{
        std::cout << "fileStream write" << std::endl;
    }
private:
};

class netWorkStream: public stream{
public:
    char read() override{
        std::cout << "netWorkStream read" << std::endl;
    }
    void write() override{
        std::cout << "netWorkStream write" << std::endl;
    }
private:
};


/*************** bad idea  *********************/
/*class cryptoStream : public stream{
public:
    cryptoStream(stream* stm) : _stm(stm){}
    void write() override{
        _stm->write();
        doCrypto();
    }
    char read() override{
        _stm->read();
        doCrypto();
    }
private:
    stream* _stm;
    void doCrypto(){}
};

class cacheStream : public stream{
public:
    cacheStream(stream* stm) : _stm(stm){}
    char read() override{
        _stm->read();
        doCache();
    }
    void write() override{
        _stm->write();
        doCache();
    }
private:
    stream* _stm;
    void doCache(){}
};*/

class decoratorStream : public stream{
public:
    explicit decoratorStream(std::shared_ptr<stream> stm) : _stm(std::move(stm)){}

protected:
    //stream* _stm;
    std::shared_ptr<stream> _stm;
};

class cryptoStream : public decoratorStream{
public:
    explicit cryptoStream(std::shared_ptr<stream> stm) : decoratorStream(std::move(stm)){}
    void write() override{
        _stm->write();
        doCrypto();
    }
    char read() override{
        _stm->read();
        doCrypto();
    }
private:
    void doCrypto(){
        std::cout << "do Crypto" << std::endl;
    }
};

class cacheStream : public decoratorStream{
public:
    explicit cacheStream(std::shared_ptr<stream> stm) : decoratorStream(std::move(stm)){}
    char read() override{
        _stm->read();
        doCache();
    }
    void write() override{
        _stm->write();
        doCache();
    }
private:
    void doCache(){
        std::cout << "do cache" << std::endl;
    }
};