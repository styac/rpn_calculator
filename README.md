# rpn_calculator
# rpn (reverse polish) calculator

- one header file
- easy to interface with a c++ project

## operators
```
   @     : copy stack to variable                    
   $     : push variable to stack
   |     : swap variable with stack
   +
   -
   /
   *
   ^      : pop stack top 
   ~      : duplicate
   !      : negate

  swap   : swap stack top stack top+1
  dupn   : push stack[n] to stack
  mod    : modulo (double)
  rrot   : right rotate
  lrot   : left rotate 
  rec    : reciprocal  
  sin    
  cos      
  tan      
  log      
  exp      
  abs      
  exp2      
  expm1      
  log10      
  log2      
  log1p      
  sqrt      
  cbrt      
  asin      
  acos      
  atan      
  sinh      
  cosh      
  tanh      
  asinh      
  acosh      
  atanh      
  max      
  min      
  rema   : remainder
  fdim      
  atan2      
  addn   : add n numbers with long double precision
  multn  : mult n numbers with long double precision
  clrs   : clear stack
  clrv   : clear variables


  swap   swap the 2 elements on the stack
  dupn   push the stack[n] to the top of stack; n is on the top of stack and will be first popped
  rrot   rigth rotation
                    1 2 3 4 5 rrot                    
          result    1 2 5 3 4
          
  lrot   left rotation
                    1 2 3 4 5 lrot                    
          result    1 2 4 5 3

```
## variable operations
```
with valiable name: v1 

  @v1 copy top of stack to variable v1; if v1 exists overwrite it
  $v1 push variable v1 to stack
  |v1 swap variable v1 with top of stack
  
  variables are accessible from outside
  
```
