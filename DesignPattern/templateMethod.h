/**
 * @file        templateMethod.h
 * @brief	    This is a brief description.
 * @details	    This is the detail description.
 * @author		
 * @date		5/29/21
 * @version	    v1.0
 * @par Copyright(c): 	Copyright (c) 2021 cygnus
 * @par History:         
 * @par Change History:         
 *----------------------------------------------------------------------------*
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  5/29/21    | 1.0.0.1   |                | Create file                    *
 *----------------------------------------------------------------------------*
*/
#pragma once

#include <iostream>
namespace sam{
    class ball{
    public:
        ball(){};
        ball(const ball&) = delete;
        const ball& operator=(const ball&) = delete;
        virtual ~ball(){};
        void play(){
            step1();
            step2();
            step3();
            step4();
        }

    private:
        void step1(){
            std::cout << "step1" << std::endl;
        }
        void step2(){
            std::cout << "step2" << std::endl;
        }
        virtual void step3() = 0;
        virtual void step4() = 0;
    };

    class basketball : public ball{
    public:
        //~basketball(){};
    private:
        void step3() override{
            std::cout << "basketBall step3" << std::endl;
        }
        void step4() override{
            std::cout << "basketBall step4" << std::endl;
        }
    };
    class football : public ball{
    public:
        //~football(){};
    private:
        void step3() override{
            std::cout << "football step3" << std::endl;
        }
        void step4() override{
            std::cout << "football step4" << std::endl;
        }
    };
}



