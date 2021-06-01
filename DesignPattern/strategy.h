/**
 * @file        strategy.h
 * @brief	    This is a brief description.
 * @details	    This is the detail description.
 * @author		
 * @date		5/31/21
 * @version	    v1.0
 * @par Copyright(c): 	Copyright (c) 2021 cygnus
 * @par History:         
 * @par Change History:         
 *----------------------------------------------------------------------------*
 *  <Date>     | <Version> | <Author>       | <Description>                   *
 *----------------------------------------------------------------------------*
 *  5/31/21    | 1.0.0.1   |                | Create file                    *
 *----------------------------------------------------------------------------*
*/
#pragma once
#include <iostream>

/***todo complete trategyFactory class***/
namespace sam{
    class context{
    public:

    private:
    };

    class TaxStrategy
    {
    public:
        virtual double calculate(const context& ctx) = 0;
        virtual ~TaxStrategy();
    private:
    };

    /**todo complete strategyFactory**/
    class strategyFactory{
    public:
        TaxStrategy * newStrategy(){};
    private:
    };

    class CNTax : public TaxStrategy{
    public:
        double calculate(const context &ctx) override{
            std::cout << "this is cn tax" << std::endl;
        }
    private:

    };

    class USTax : public TaxStrategy{
    public:
        double calculate(const context &ctx) override{
            std::cout << "this is cn tax" << std::endl;
        }
    private:
    };

    class salesOrder{
    public:
        salesOrder(strategyFactory *sf){
            _ts = sf->newStrategy();
        }
        ~salesOrder(){
            delete _ts;
        }
        double calaulateTax(){
            return _ts->calculate(*_ctx);
        }
    private:
        TaxStrategy *_ts;
        context     *_ctx;
    };
}




