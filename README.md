# rpn_calculator
# rpn (reverse polish) calculator

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

 
  swap - swap the 2 elements on the stack
  dupn   push the stack[n] to the top of stack; n is on the top of stack and will be first popped
 
  sin 
  cos
  tan
  log
  exp
```
## variable operations
```
with valiable name: v1 

  @v1 copy top of stack to variable v1; if v1 exists overwrite it
  $v1 push variable v1 to stack
```
