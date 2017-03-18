/*
/*
 * Copyright (C) 2017 Istvan Simon -- stevens37 at gmail dot com
 *
 * This program is free software; 
 * PUBLIC DOMAIN
 * 
 * Created on March 17, 2017, 4:29 PM
 */


#include <cstdlib>
#include <iostream>
#include "RpnCalculator.h"

using namespace std;
using namespace rpnCalculator;
using RPNEC = rpnCalculator::RpnCalculator::EC;

/*
 * 
 */

int main(int argc, char** argv) 
{
    
    RpnCalculator rpn;
    {
        rpn.clear();
        std::string str( "2 4 +" );
        std::stringstream ss(str);
        std::cout << "---eval add: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;   
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 6 )  << std::endl;   
                
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "2 +" );
        std::stringstream ss(str);
        std::cout << "---eval illegal1: "     << str << std::endl;    
        if( RPNEC::ecStackLow == rpn.eval(ss) ) {
            std::cout << "* ok" << std::endl;                            
        } else {
            std::cout << "* error"  << std::endl;                            
        }
    }    
    {
        rpn.clear();
        std::string str( "2 4 -" );
        std::stringstream ss(str);
        std::cout << "---eval substact: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == -2 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "2 4 *" );
        std::stringstream ss(str);
        std::cout << "---eval mult: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 8 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "2 4 /" );
        std::stringstream ss(str);
        std::cout << "---eval divide: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 0.5 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "2 4 swap /" );
        std::stringstream ss(str);
        std::cout << "---eval swap divide: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 2 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "2 ~ ~ * *" );
        std::stringstream ss(str);
        std::cout << "---eval dup dup: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 8 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "2 !" );
        std::stringstream ss(str);
        std::cout << "---eval negate: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == -2 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "2 3 4 ^" );
        std::stringstream ss(str);
        std::cout << "---eval pop: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 3 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "2 log" );
        std::stringstream ss(str);
        std::cout << "---eval log: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == std::log(2.0) )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }
    {
        rpn.clear();
        std::string str( "3.1415 2 / sin" );
        std::stringstream ss(str);
        std::cout << "---eval sin: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == std::sin(3.1415 / 2.0) )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }    
    {
        rpn.clear();
        std::string str( "3.1415 cos" );
        std::stringstream ss(str);
        std::cout << "---eval cos: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == std::cos( 3.1415 ) )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }    
    {
        rpn.clear();
        std::string str( "3.1415 2 * tan" );
        std::stringstream ss(str);
        std::cout << "---eval tan: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == std::tan( 3.1415 *2.0 ) )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }    
    {
        rpn.clear();
        std::string str( "2 exp" );
        std::stringstream ss(str);
        std::cout << "---eval exp: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == std::exp( 2.0 ) )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }   
    {
        rpn.clear();
        std::string str( "18 5 mod" );
        std::stringstream ss(str);
        std::cout << "---eval exp: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 3)  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }   
    {
        rpn.clear();
        std::string str( "3.0 r" );
        std::stringstream ss(str);
        std::cout << "---eval reciproc: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 1.0 / 3.0 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    }  
    {
        rpn.clear();
        std::string str( "2 3 4 5 + - *" );
        std::stringstream ss(str);
        std::cout << "---eval reciproc: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == -12 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    } 

    {
        rpn.clear();
        std::string v1("v1");
        std::string v2("v2");
        std::string v3("v3");
        std::string str( "2 @v1 3 @v2 ^ ^ $v1 $v2 +" );
        std::stringstream ss(str);
        std::cout << "---eval set var: " << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult(v1) ) {
                std::cout << "result: "    << rpn.result(v1) << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result(v1) == 2 )  << std::endl;   
            } else {
                std::cout << "var empty " << v1  << std::endl;                
            }            
            if( rpn.hasResult(v2) ) {
                std::cout << "result: "    << rpn.result(v2) << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result(v2) == 3 )  << std::endl;   
            } else {
                std::cout << "var empty " << v2 << std::endl;                
            }            
            if( !rpn.hasResult(v3) ) {
                std::cout << "result false: ok" << std::endl;                
            } 
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 5 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }                        
            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    } 
    {
        rpn.clear();
        // stack data 0 .. 6
        // index 4 (from 0..)
        // 
        std::string str( "1.1 2.2 3.3 4.4 5.5 6.6 4 dupn" );
        std::stringstream ss(str);
        std::cout << "---eval dupn: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                std::cout << "result: "    << rpn.result() << std::endl;                
                std::cout << std::boolalpha  << "* "    << bool( rpn.result() == 2.2 )  << std::endl;   
            } else {
                std::cout << "stack empty" << std::endl;                
            }            
        } else {
            std::cout << "error"  << std::endl;                
            
        }
    } 
}

