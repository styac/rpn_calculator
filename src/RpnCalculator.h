#pragma once

/*
 * Copyright (C) 2017 Istvan Simon -- stevens37 at gmail dot com
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE 
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#ifndef RPNCALCULATOR_H
#define RPNCALCULATOR_H

#include    <cstdint>
#include    <cstdlib>
#include    <string>
#include    <sstream>
#include    <iostream>
#include    <cmath>
#include    <vector>
#include    <map>
#include    <limits>
//#include    <algorithm>
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
// + a lot of other math
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
        ecIllegalNumber,    // illegal number
        ecIllegalVar,       // illegal variable
        ecIndexTooBig,      // index too big        
        ecIndexTooSmall     // index too small        
    };

    EC eval( const std::string& inp )
    {            
        std::stringstream ss(inp);
        return eval(ss);
    }
    
    // __attribute__ ((noinline)) is gcc specific    
    EC __attribute__ ((noinline))  eval( std::stringstream& inp )
    {            
        double val1 = 0.0;
        double val2 = 0.0;
        double val3 = 0.0;
        std::string op;
        inp.clear();
        while( !inp.eof() ) {    
            inp >> op;
            if( op.size() == 1 ) {
                switch( op[0] ) { // 1 char op
                case '+' :
                    if( stack.size() < 2 ) return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val1 + val2);                
                    continue;                
                case '-' :
                    if( stack.size() < 2 ) return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val2 - val1);                
                    continue;
                case '/' :
                    if( stack.size() < 2 ) return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val2 / val1);                
                    continue;
                case '*' :
                    if( stack.size() < 2 ) return EC::ecStackLow;
                    val1 = pop();
                    val2 = pop();
                    push(val1 * val2);                
                    continue;                
                case '^' : // pop stack top 
                    if( stack.size() < 1 ) return EC::ecStackLow;
                    drop();
                    continue;
                case '~' : // duplicate
                    if( stack.size() < 1 ) return EC::ecStackLow;
                    push( stack[0] );                
                    continue;
                case '!' : // negate
                    if( stack.size() < 1 ) return EC::ecStackLow;
                    set(-get());
                    continue;
                case '0' : 
                case '1' : 
                case '2' : 
                case '3' : 
                case '4' : 
                case '5' : 
                case '6' : 
                case '7' : 
                case '8' : 
                case '9' : 
                    val1 = int(op[0] - 0x30);
                    push(val1);
                    continue;                    
// reserved                    
//                case '&' : 
//                    continue;                    
//                case '`' : 
//                    continue;                    
//                case '?' : 
//                    continue;                    
//                case '<' : 
//                    continue;                    
//                case '>' : 
//                    continue;                    
//                case '=' : 
//                    continue;                    
//                case ',' : 
//                    continue;                    
//                case ':' : 
//                    continue;                    
//                case ';' : 
//                    continue;                    
//                case '[' : 
//                    continue;                    
//                case ']' : 
//                    continue;                    
//                case '(' : 
//                    continue;                    
//                case ')' : 
//                    continue;                    
//                case '{' : 
//                    continue;                    
//                case '}' : 
//                    continue;                    
//                case '%' : 
//                    continue;                    
                default: return EC::ecIllegalOp;                    
                } // end switch                
            } else { // long op
                switch( op[0] ) {
                case '.' : 
                case '+' : 
                case '-' : 
                case '0' : 
                case '1' : 
                case '2' : 
                case '3' : 
                case '4' : 
                case '5' : 
                case '6' : 
                case '7' : 
                case '8' : 
                case '9' : 
                    {  // convert to number
                        char *end;
                        val1 = std::strtod( op.data(), &end );
                        if( (end - op.data()) < op.size() ) return EC::ecIllegalNumber;                                                                        
                        push(val1);                    
                    }
                    continue;                    
                case 'a' : 
                    if ( op == "abs" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::abs(get()));
                    } else if ( op == "asin" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::asin(get()));                    
                    } else if ( op == "acos" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::acos(get()));
                    } else if ( op == "atan" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::atan(get()));                    
                    } else if ( op == "asinh" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::asinh(get()));
                    } else if ( op == "acosh" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::acosh(get()));
                    } else if ( op == "atanh" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::atanh(get()));                   
                    } else if ( op == "atan2" ) {
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        push(std::atan2(val1,val2));   
                    } else if ( op == "addn" ) {    // summarize n numbers with long double precision
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();   // count
                        if( val1 >= std::numeric_limits<uint32_t>::max() ) return EC::ecIndexTooBig;                    
                        if( val1 < 1.0 ) return EC::ecIndexTooSmall;
                        uint32_t count = uint32_t(val1); // truncated
                        if( count == 1 ) continue; // 1 operand
                        if( stack.size() < count ) return EC::ecIndexTooBig; 
                        long double val = pop();
                        for(uint32_t i=0; i<count-1; ++i ) {
                            val += pop();
                        }                    
                        push(val);   
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
//                case 'b' : 
//                    continue;                    
                case 'c' : 
                    if ( op == "cos" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::cos(get()));
                    } else if ( op == "cbrt" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::cbrt(get()));                                        
                    } else if ( op == "cosh" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::cosh(get()));
                    } else if ( op == "clrs" ) {    // clear stack
                        stack.clear();
                    } else if ( op == "clrv" ) {    // clear variables
                        vars.clear();                        
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
                case 'd' : 
                    if ( op == "dupn" ) {    // push stack[n] to stack
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();   // index
                        if( val1 >= std::numeric_limits<uint32_t>::max() ) return EC::ecIndexTooBig;
                        if( val1 < 0 ) return EC::ecIndexTooSmall;
                        uint32_t index = uint32_t(val1);
                        if( stack.size() <= index )  return EC::ecIndexTooBig;                    
                        val2 = get(index);
                        push(val2);
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
                case 'e' : 
                    if ( op == "exp" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::exp(get()));                    
                    } else if ( op == "exp2" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::exp2(get()));                    
                    } else if ( op == "expm1" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::expm1(get()));
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
                case 'f' : 
                    if ( op == "fdim" ) {
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        push(std::fdim(val1,val2));                                  
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
//                case 'g' : 
//                    continue;                    
//                case 'h' : 
//                    continue;                    
//                case 'i' : 
//                    continue;                    
//                case 'j' : 
//                    continue;                    
//                case 'k' : 
//                    continue;                    
                case 'l' : 
                    if ( op == "lrot" ) {    // left rotate 
                        if( stack.size() < 3 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        val3 = pop();
                        push( val2 );                     
                        push( val1 );                     
                        push( val3 );                     
                    } else if ( op == "log" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::log(get()));                    
                    } else if ( op == "log10" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::log10(get()));
                    } else if ( op == "log2" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::log2(get()));
                    } else if ( op == "log1p" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::log1p(get()));
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
                case 'm' : 
                    if ( op == "mod" ) {     // fmod
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        push( std::fmod( val2, val1 ) ); 
                    } else if ( op == "max" ) {
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        push(std::fmax(val1,val2));                
                    } else if ( op == "min" ) {
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        push(std::fmin(val1,val2));                                    
                    } else if ( op == "multn" ) {   // mult n numbers with long double precision
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();   // count
                        if( val1 >= std::numeric_limits<uint32_t>::max() ) return EC::ecIndexTooBig;
                        if( val1 < 1.0 ) return EC::ecIndexTooSmall;
                        uint32_t count = uint32_t(val1);   // truncated                 
                        if( count == 1 )
                            continue; // 1 operand
                        if( stack.size() < count ) return EC::ecIndexTooBig; 
                        long double val = pop();
                        for(uint32_t i=0; i<count-1; ++i ) {
                            val *= pop();
                        }                    
                        push(val);   
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
//                case 'n' : 
//                    continue;                    
//                case 'o' : 
//                    continue;                    
//                case 'p' : 
//                    continue;                    
//                case 'q' : 
//                    continue;                    
                case 'r' : 
                    if ( op == "rrot" ) {    // right rotate
                        if( stack.size() < 3 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        val3 = pop();
                        push( val1 );                     
                        push( val3 );                     
                        push( val2 );                     
                    } else if ( op == "rec" ) {     // reciprocal  
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(1.0/get());
                    } else if ( op == "rema" ) {    // remainder
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        push(std::remainder(val1,val2));                
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
                case 's' : 
                    if( op == "swap" ) {            // swap stack top stack top+1
                        if( stack.size() < 2 ) return EC::ecStackLow;
                        val1 = pop();
                        val2 = pop();
                        push(val1);                
                        push(val2);                                    
                    } else if ( op == "sin" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::sin(get()));
                    } else if ( op == "sqrt" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::sqrt(get()));
                    } else if ( op == "sinh" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::sinh(get()));
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
                case 't' : 
                    if ( op == "tan" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::tan(get()));
                    } else if ( op == "tanh" ) {
                        if( stack.size() < 1 ) return EC::ecStackLow;
                        set(std::tanh(get()));
                    } else {
                        return EC::ecIllegalOp;                    
                    } 
                    continue;                    
//                case 'u' : 
//                    continue;                    
//                case 'v' : 
//                    continue;                    
//                case 'w' : 
//                    continue;                    
//                case 'x' : 
//                    continue;                    
//                case 'y' : 
//                    continue;                    
//                case 'z' : 
//                    continue;                    
                case '@' : // copy stack to variable  
                    if( stack.size() < 1 ) return EC::ecStackLow;
                    vars[op.substr(1)] = get(); // chop prefix
                    continue;                    
                case '$' : // push variable to stack
                    if( !hasResult(op.substr(1)) ) return EC::ecIllegalVar;
                    push(vars[op.substr(1)]);     
                    continue;                    
                case '|' : // swap variable with stack
                    if( !hasResult(op.substr(1)) ) return EC::ecIllegalVar;
                    val1 = vars[op.substr(1)];
                    vars[op.substr(1)] = get();
                    set(val1);
                    continue;                    
                default:
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
    bool hasResult( const std::string& var ) const
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

    void dumpStack( std::string& out )
    {
        out = " ";
        for( auto& p : stack )
            out += std::to_string(p) + " ";                    
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
    void push( double val )
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

