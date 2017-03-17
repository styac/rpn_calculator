#pragma once

/*
 * Copyright (C) 2017 Istvan Simon -- stevens37 at gmail dot com
 *
 * This program is free software; 
 * PUBLIC DOMAIN
 * 
 * Created on March 17, 2017, 4:29 PM
 */

#ifndef RPNCALCULATOR_H
#define RPNCALCULATOR_H

#include    <vector>
#include    <cstdint>
#include    <string>
#include    <sstream>
#include    <iostream>
#include    <cmath>

//
//
// operators
//  + 
//  - 
//  * 
//  /
// 
//  ^ pop 
//  ! negate
//  ~ dup 
//  r  1.0 / x
//
// 
//  swap 
//  sin
//  cos
//  tan
//  log
//  exp
//

namespace rpnCalculator
{
    
class RpnCalculator {
    
public:
    RpnCalculator() {}
    
    ~RpnCalculator() {}
    
    bool eval( std::stringstream& inp )
    {    
        double val1;
        double val2;
        std::string op;
        while(!inp.eof()) {    
            std::stringstream::pos_type pos = inp.tellg();
            inp >> val1; // try to interpret as number
            if( inp.good() ) {
                stack.push_back(val1);
                continue;
            }
            inp.clear(); // in c++11 not needed
            inp.seekg(pos); // back - get it as string
            op.clear();
            inp >> op;
            if( op.size() == 1 ) {
                switch( op[0] ) {
                case '+' :
                    if( stack.size() < 2 )
                        return false;
                    val1 = pop();
                    val2 = pop();
                    push(val1 + val2);                
                    continue;                
                case '-' :
                    if( stack.size() < 2 )
                        return false;
                    val1 = pop();
                    val2 = pop();
                    push(val2 - val1);                
                    continue;
                case '/' :
                    if( stack.size() < 2 )
                        return false;
                    val1 = pop();
                    val2 = pop();
                    push(val2 / val1);                
                    continue;
                case '*' :
                    if( stack.size() < 2 )
                        return false;
                    val1 = pop();
                    val2 = pop();
                    push(val1 * val2);                
                    continue;                
                case '^' : // pop stack top 
                    if( stack.size() < 1 )
                        return false;
                    pop();
                    continue;
                case '~' : // duplicate
                    if( stack.size() < 1 )
                        return false;
                    push( stack[0] );                
                    continue;
                case '!' : // negate
                    if( stack.size() < 1 )
                        return false;
                    set(-get());
                    continue;
                case 'r' : // reciproc
                    if( stack.size() < 1 )
                        return false;
                    set(1.0/get());
                    continue;
                default:
                    return false;
                }
                
            } else {
                if( op == "swap" ) {
                    if( stack.size() < 2 )
                        return false;
                    val1 = pop();
                    val2 = pop();
                    push(val1);                
                    push(val2);                
                } else if ( op == "sin" ) {
                    if( stack.size() < 1 )
                        return false;
                    set(std::sin(get()));
                } else if ( op == "cos" ) {
                    if( stack.size() < 1 )
                        return false;
                    set(std::cos(get()));
                } else if ( op == "tan" ) {
                    if( stack.size() < 1 )
                        return false;
                    set(std::tan(get()));
                } else if ( op == "log" ) {
                    if( stack.size() < 1 )
                        return false;
                    set(std::log(get()));
                } else if ( op == "exp" ) {
                    if( stack.size() < 1 )
                        return false;
                    set(std::exp(get()));
                } else if ( op == "mod" ) {
                    if( stack.size() < 2 )
                        return false;
                    val1 = pop();
                    val2 = pop();
                    push( std::fmod( val2, val1 ) );                
                } else {
                    return false;                    
                }                                       
            }
        }
        return true;
    }
    
    bool hasResult() const
    {
        return stack.size() > 0;
    }
    
    void clear()
    {
        stack.clear();
    }
    
    double result() const
    {
        if( stack.size() > 0 )
            return stack.back();
        return 0.0;
    }
    
private:
    double pop()
    {
        double val = stack.back();
        stack.pop_back();
        return val;        
    }
    void push(double val)
    {
        stack.push_back(val);
    }
    double get()
    {
        return stack.back();
    }
    void set(double val)
    {
        stack.back() = val;
    }
    std::vector<double> stack;    
};
    
}

#endif /* RPNCALCULATOR_H */

