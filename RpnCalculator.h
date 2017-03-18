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

#include    <cstdint>
#include    <string>
#include    <sstream>
#include    <iostream>
#include    <cmath>
#include    <vector>
#include    <map>
#include    <limits>
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
//  dupn   push the stack[n] to the top of stack; n is on the top of stack and will be first popped
//
// variables
//  @v1 copy top of stack to variable v1; if v1 exists overwrite it
//  $v1 push variable v1 to stack
//


namespace rpnCalculator
{
    
class RpnCalculator {
    
public:
    typedef std::map< std::string, double > varmap_t;
    
    RpnCalculator() {}
    
    ~RpnCalculator() {}
    
    enum class EC : int {   // error code
        ecOk,               // no error
        ecStackLow,         // stack is too low - non existent value
        ecIllegalOp,        // illegal operator
        ecIllegalVar,       // illegal variable
        ecIndexToobig,      // index too big        
    };
    
    // __attribute__ ((noinline)) is gcc specific
    
    EC __attribute__ ((noinline))  eval( std::stringstream& inp )
    {            
        double val1;
        double val2;
        double val3;
        std::string op;
        inp.clear();
        while(!inp.eof()) {    
            std::stringstream::pos_type pos = inp.tellg();
            inp >> val1; // try to interpret as number
            if( !inp.fail() ) {
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
                        return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val1 + val2);                
                    continue;                
                case '-' :
                    if( stack.size() < 2 )
                        return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val2 - val1);                
                    continue;
                case '/' :
                    if( stack.size() < 2 )
                        return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val2 / val1);                
                    continue;
                case '*' :
                    if( stack.size() < 2 )
                        return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val1 * val2);                
                    continue;                
                case '^' : // pop stack top 
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    drop();
                    continue;
                case '~' : // duplicate
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    push( stack[0] );                
                    continue;
                case '!' : // negate
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    set(-get());
                    continue;
                case 'r' : // reciproc
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    set(1.0/get());
                    continue;
                default:
                    return EC::ecIllegalOp;                    
                } // end switch                
            } else {
                if( op == "swap" ) {
                    if( stack.size() < 2 )
                        return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val1);                
                    push(val2);                
                } else if ( op == "sin" ) {
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    set(std::sin(get()));
                } else if ( op == "cos" ) {
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    set(std::cos(get()));
                } else if ( op == "tan" ) {
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    set(std::tan(get()));
                } else if ( op == "log" ) {
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    set(std::log(get()));
                } else if ( op == "exp" ) {
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    set(std::exp(get()));
                } else if ( op == "dupn" ) { // push stack[n] to stack
                    if( stack.size() < 2 ) // index + at least 1 variable
                        return EC::ecStackLow;
                    val1 = pop();   // index
                    if( val1 >= std::numeric_limits<uint32_t>::max() ) // too big number
                        return EC::ecIndexToobig;
                    uint32_t index = uint32_t(val1);
                    if( stack.size()-1 < index )  // stack size : 1.. index: 0 ..
                        return EC::ecIndexToobig;                    
                    val2 = get(index);
                    push(val2);
                } else if ( op == "mod" ) {
                    if( stack.size() < 2 )
                        return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push( std::fmod( val2, val1 ) ); 
                } else if ( op == "rrot" ) {
                    if( stack.size() < 3 )
                        return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    val3 = pop();
                    push( val1 );                     
                    push( val3 );                     
                    push( val2 );                     
                } else if ( op == "lrot" ) {
                    if( stack.size() < 3 )
                        return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    val3 = pop();
                    push( val2 );                     
                    push( val1 );                     
                    push( val3 );                     
                // @ is a prefix no space after!
                } else if ( op[0] == '@' ) { // copy stack to variable                    
                    if( stack.size() < 1 )
                        return EC::ecStackLow;
                    vars[op.substr(1)] = get();  // chop prefix
                // $ is a prefix no space after!
                } else if ( op[0] == '$' ) { // push variable to stack
                    if( !hasResult(op.substr(1)) ) // chop prefix
                        return EC::ecIllegalVar;
                    push(vars[op.substr(1)]);                    
                } else {
                    return EC::ecIllegalOp;                    
                } 
            } 
        } // end while
        return EC::ecOk;
    }
    
    // result from stack 
    bool hasResult() const
    {
        return stack.size() > 0;
    }
    
    // result from variable
    bool hasResult(const std::string& var) const
    {
        return vars.find(var) !=  vars.end();
    }
    
    void clear()
    {
        stack.clear();
        vars.clear();
    }
    
    // result from stack
    double result() const
    {
        if( stack.size() > 0 )
            return stack.back();
        return 0.0;
    }
    
    // result from variable
    double result( const std::string& var)
    {
        return vars[var];
    }
    
    varmap_t& variables()
    {
        return vars;
    }
    
private:
    double pop()
    {
        double val = stack.back();
        stack.pop_back();
        return val;        
    }
    void drop()
    {
        stack.pop_back();
    }
    void push(double val)
    {
        stack.push_back(val);
    }
    double get() const
    {
        return stack.back();
    }
    double get( uint32_t index ) const
    {
        return stack[stack.size()-1-index];
    }
    void set(double val)
    {
        stack.back() = val;
    }
    
    // members
    std::vector<double> stack;    
    varmap_t vars;    
};
    
} // end namespace rpnCalculator

#endif /* RPNCALCULATOR_H */

