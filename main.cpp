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

#include <cstdlib>
#include <iostream>
#include "RpnCalculator.h"

using namespace std;
using namespace rpnCalculator;
using RPNEC = rpnCalculator::RpnCalculator::EC;
using varmap_t = rpnCalculator::RpnCalculator::varmap_t;

/*
 * 
 * TEST CASES
 * 
 */

int main(int argc, char** argv) 
{
    int testfailed = 0;
    RPNEC rpres;
    RpnCalculator rpn;
    {
        std::cout << "\n****** push ****\n" << std::endl;    
        rpn.clear();
        std::string str( "-1 +1 +.5 -1 -.5 1" );
        std::stringstream ss(str);
        std::cout << "       eval push: "     << str << std::endl;    
        if( RPNEC::ecOk == (rpres = rpn.eval(ss))  ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 1);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                std::cout << "stack empty" << std::endl;                
                ++testfailed;
            }            
        } else {
            std::cout << "error " << int(rpres) << std::endl;                            
            ++testfailed;
        }
    }
    {
        std::cout << "\n****** push illegal number ****\n" << std::endl;    
        rpn.clear();
        std::string str( "-1x0" );
        std::stringstream ss(str);
        std::cout << "       eval push: "     << str << std::endl;    
        if( RPNEC::ecOk != (rpres = rpn.eval(ss))  ) {
            std::cout << "error ok: " << int(rpres) << std::endl;                                        
        } else {
            std::cout << "error " << int(rpres) << std::endl;                            
            ++testfailed;
        }
    }    
    {
        std::cout << "\n****** add ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 4 +" );
        std::stringstream ss(str);
        std::cout << "       eval add: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 6);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                std::cout << "stack empty" << std::endl;                
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                            
            ++testfailed;
        }
    }
    {
        std::cout << "\n****** illegal: stack empty ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 +" );
        std::stringstream ss(str);
        std::cout << "       eval illegal1: "     << str << std::endl;    
        if( RPNEC::ecStackLow == rpn.eval(ss) ) {
            std::cout << "result: ok" << std::endl;                            
        } else {
            std::cout << "* error"  << std::endl;                            
            ++testfailed;
        }
    }    
    {
        std::cout << "\n****** substract ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 4 -" );
        std::stringstream ss(str);
        std::cout << "       eval substract: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == -2);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                std::cout << "stack empty" << std::endl;                
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;           
        }
    }
    {
        std::cout << "\n****** multiply ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 4 *" );
        std::stringstream ss(str);
        std::cout << "       eval mult: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 8);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    {
        std::cout << "\n****** divide ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 4 /" );
        std::stringstream ss(str);
        std::cout << "       eval divide: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 0.5);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    {
        std::cout << "\n****** swap divide ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 4 swap /" );
        std::stringstream ss(str);
        std::cout << "       eval swap divide: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 2);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    {
        std::cout << "\n****** dup dup multiply ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 ~ ~ * *" );
        std::stringstream ss(str);
        std::cout << "       eval dup dup: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 8 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    {
        std::cout << "\n****** negate ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 !" );
        std::stringstream ss(str);
        std::cout << "       eval negate: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == -2);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    {
        std::cout << "\n****** drop ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 3 4 ^" );
        std::stringstream ss(str);
        std::cout << "       eval pop: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 3);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    {
        std::cout << "\n****** logarithm ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 log" );
        std::stringstream ss(str);
        std::cout << "       eval log: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == std::log(2.0) );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    {
        std::cout << "\n****** sine ****\n" << std::endl;  
        rpn.clear();
        std::string str( "3.1415 2 / sin" );
        std::stringstream ss(str);
        std::cout << "       eval sin: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == std::sin(3.1415 / 2.0) );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }    
    {
        std::cout << "\n****** cosine ****\n" << std::endl;  
        rpn.clear();
        std::string str( "3.1415 cos" );
        std::stringstream ss(str);
        std::cout << "       eval cos: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == std::cos( 3.1415 ) );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }    
    {
        std::cout << "\n****** tangent ****\n" << std::endl;  
        rpn.clear();
        std::string str( "3.1415 2 * tan" );
        std::stringstream ss(str);
        std::cout << "       eval tan: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == std::tan( 3.1415 *2.0 ) );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }    
    {
        std::cout << "\n****** exponent ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 exp" );
        std::stringstream ss(str);
        std::cout << "       eval exp: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == std::exp( 2.0 ) );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }   
    {
        std::cout << "\n****** modulus ****\n" << std::endl;  
        rpn.clear();
        std::string str( "18 5 mod" );
        std::stringstream ss(str);
        std::cout << "       eval exp: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 3);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }   
    {
        std::cout << "\n****** reciprocal ****\n" << std::endl;  
        rpn.clear();
        std::string str( "3.0 rec" );
        std::stringstream ss(str);
        std::cout << "       eval reciproc: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 1.0 / 3.0);
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                ++testfailed;
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }  
    {
        std::cout << "\n****** more operations ****\n" << std::endl;  
        rpn.clear();
        std::string str( "2 3 4 5 + - *" );
        std::stringstream ss(str);
        std::cout << "       eval reciproc: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == -12 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    } 

    {
        std::cout << "\n****** left rotation ****\n" << std::endl;  
        rpn.clear();
        std::string str( "1 2 3 4 5 lrot" );
        std::stringstream ss(str);
        std::cout << "       eval left rot: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 3 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                } else {
                    std::string str( "^" );
                    ss.str(str);
                    std::cout << "     --  eval left rot drop: "  << str << std::endl;    
                    if( RPNEC::ecOk == rpn.eval(ss) ) {
                        bool res = bool( rpn.result() == 5 );
                        std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                        if( !res ) {
                            ++testfailed;                    
                        }                        
                    } else {
                        ++testfailed;
                    }                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    } 
    {
        std::cout << "\n****** right rotation ****\n" << std::endl;  
        rpn.clear();
        std::string str( "1 2 3 4 5 rrot" );
        std::stringstream ss(str);
        std::cout << "       eval right rot: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 4 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                } else {
                    std::string str( "^" );
                    ss.str(str);
                    std::cout << "     --  eval right rot drop: "  << str << std::endl;    
                    if( RPNEC::ecOk == rpn.eval(ss) ) {
                        bool res = bool( rpn.result() == 3 );
                        std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                        if( !res ) {
                            ++testfailed;                    
                        }                        
                    } else {
                        ++testfailed;
                    }                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    } 

    {
        std::cout << "\n****** using variables ****\n" << std::endl;  
        rpn.clear();
        std::string v1("v1");
        std::string v2("v2");
        std::string v3("v3");
        std::string str( "2 @v1 3 @v2 ^ ^ $v1 $v2 +" );
        std::stringstream ss(str);
        std::cout << "       eval set var: " << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult(v1) ) {
                bool res = bool( rpn.result(v1) == 2 );
                std::cout << "result: "    << rpn.result(v1) << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                std::cout << "var empty " << v1  << std::endl;                
                ++testfailed;                                   
            }            
            if( rpn.hasResult(v2) ) {
                bool res = bool( rpn.result(v2) == 3 );
                std::cout << "result: "    << rpn.result(v2) << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                std::cout << "var empty " << v2 << std::endl;                
                ++testfailed;                                   
            }            
            if( !rpn.hasResult(v3) ) {
                std::cout << "result false: ok" << std::endl;                
            } 
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 5 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                std::cout << "stack empty" << std::endl;                
                ++testfailed;                                   
            }                                    
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                                   
        }
    } 
    {
        std::cout << "\n****** swap variable with stack ****\n" << std::endl;  
        rpn.clear();
        std::string v1("v1");
        std::string str( "2 @v1 3 |v1" );
        std::stringstream ss(str);
        std::cout << "       eval swap var: " << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult(v1) ) {
                bool res = bool( rpn.result(v1) == 3 );
                std::cout << "result: "    << rpn.result(v1) << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
                res = bool( rpn.result() == 2 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            } else {
                std::cout << "var empty " << v1  << std::endl;                
                ++testfailed;                                   
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                                   
        }
    } 
    {
        std::cout << "\n****** dup from n level ****\n" << std::endl;  
        rpn.clear();
        // stack data 0 .. 6
        // index 4 (from 0..)
        // 
        std::string str( "1.1 2.2 3.3 4.4 5.5 6.6 4 dupn" );
        std::stringstream ss(str);
        std::cout << "       eval dupn: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 2.2 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    
    {
        std::cout << "\n****** using variables externally ****\n" << std::endl;  
        rpn.clear();
        varmap_t& vars = rpn.variables();
        std::string v1("v1");
        std::string v2("v2");
        std::string str( "1.1 2.2  @v1 ^ @v2" );
        std::stringstream ss(str);
        std::cout << "       eval acces variables: "  << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {            
            bool res = bool( vars[v1] == 2.2 );
            std::cout << "result: " << v1 << "=" << vars[v1] << std::boolalpha << " " << res << std::endl;  
            if( !res ) {
                ++testfailed;                    
            }
            res = bool( vars[v2] == 1.1 );
            std::cout << "result: " << v2 << "=" << vars[v2] << std::boolalpha << " " << res << std::endl;  
            if( !res ) {
                ++testfailed;                    
            }
            std::string str1( "$v1 $v2 + @res" );
            ss.str(str1);
            std::cout << "     --  eval add vars: "  << str1 << std::endl;    
            if( RPNEC::ecOk == rpn.eval(ss) ) {   
                double result = 3.3;
                bool res = bool( std::abs( vars["res"] - result ) < 1.0e-15 );
                std::cout << "result: " << vars["res"] << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }

            } else {
                std::cout << "error"  << std::endl;                
                ++testfailed;                       
            }
            
                        
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
        
        std::string str1( "$v1 $v2 + @res" );
        ss.str(str1);
        vars[v1] = 3.3;
        vars[v2] = 4.4;
        std::cout << "       eval acces result: "  << str1 << " input: v1  " << vars[v1] << " v2 " << vars[v2] << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {            
            bool res = bool( vars["res"] == 7.7 );
            std::cout << "result: " << vars["res"] << std::boolalpha << " " << res << std::endl;  
            if( !res ) {
                ++testfailed;                    
            }
                        
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
        
    }
    {
        std::cout << "\n****** add n numbers ****\n" << std::endl;  
        rpn.clear();
        std::string str( "1 2 3 4 5 6 6 addn" );
        std::stringstream ss(str);
        std::cout << "       eval addn: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 21 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
        
    {
        std::cout << "\n****** multiply n numbers ****\n" << std::endl;  
        rpn.clear();
        std::string str( "1 2 3 4 5 6 6 multn" );
        std::stringstream ss(str);
        std::cout << "       eval addn: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(ss) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 720 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }

    {
        std::cout << "\n****** use string interface ****\n" << std::endl;  
        rpn.clear();
        std::string str( "1 2 3 4 5 6 6 multn" );
        std::cout << "       eval addn: "     << str << std::endl;    
        if( RPNEC::ecOk == rpn.eval(str) ) {
            if( rpn.hasResult() ) {
                bool res = bool( rpn.result() == 720 );
                std::cout << "result: "    << rpn.result() << std::boolalpha << " " << res << std::endl;  
                if( !res ) {
                    ++testfailed;                    
                }
            }            
        } else {
            std::cout << "error"  << std::endl;                
            ++testfailed;                       
        }
    }
    
    // end result
    
    if(testfailed) {
        std::cout << "\n\n------ failed test count=" << testfailed << std::endl;                      
    } else {
        std::cout << "\n\n++++++ test result ok" << std::endl;                              
    }
}

