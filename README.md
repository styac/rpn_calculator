# rpn_calculator
# rpn (reverse polish) calculator

- one header file
- easy to interface with a c++ project

## operators
```
  + 
  - 
  * 
  /
 
  ^ pop 
  ! negate
  ~ dup 
  r  1.0 / x ( reciprocal )

 
  swap   swap the 2 elements on the stack
  dupn   push the stack[n] to the top of stack; n is on the top of stack and will be first popped
  rrot   rigth rotation
                    1 2 3 4 5 rrot                    
          result    1 2 5 3 4
          
  lrot   left rotation
                    1 2 3 4 5 lrot                    
          result    1 2 4 5 3
  sin 
  cos
  tan
  log
  exp
  mod : modulo with double
  
```
## variable operations
```
with valiable name: v1 

  @v1 copy top of stack to variable v1; if v1 exists overwrite it
  $v1 push variable v1 to stack
  
  variables are accessible from outside
  
```
