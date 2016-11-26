#Reverse Polish Notation Converter in C99

##Dependencies
* Ubuntu 14.04
* GNU GCC
* GNU Make
* Libcheck

```
$ sudo apt-get install gcc make check
```

##Notes/Assumptions
* The RPN to Infix implementation is omitted intentionally after receiving new instructions that the second half of the exercise is now optional due to the unexpectedly high number of hours to complete.
* The `rpn-string` library intentionally does not report errors. It's intended only for use with `rpn-convert`, not as a general purpose String library.
* The `in` array and `out` array are at least as large as the `length` parameter and the caller is responsible for this invariant. No errors are reported by `rpn-convert` for mismatched string lengths.
* ~`length / 2` bytes of stack memory are available in addition to the `in` and `out` array.
* All of these assumptions could be coded for in the event that the production application required it.

##Make Targets
```
$ make check	#Run Tests
$ make build	#Build convert-rpn.o
$ make clean	#Delete Build Files
```

##Approach
`infixToReversePolish(const char *in, char *out, int length)`

The library function requires input and output array parameters and a length parameter. The algorithm uses a fixed length array-list stack implementation.

###Advantages
* Faster.
* Memory usage never exceeds `length / 2` memory.
* No heap allocation minimizes opportunities for memory leaks.
* Advantages increase as complexity of the expressions increase. Expressions with many parens or mixed-precedence operators require more stack operations to process.

###Trade-offs
* Always allocates maximum memory.
* Longer initialization. All memory allocated up front.
* All trade-offs worsen as `length` increases.

##Error Codes

###`RPN_INVALID_ARGS (1)`

* `in` was the `NULL` pointer
* `out` was the `NULL` pointer
* `length` was less than `0`

###`RPN_PARSE_ERROR_INVALID_OPERAND (2)`

Valid operands: `/[a-z]{1}/`

Expected the next character to be an operand and encountered something else. All expressions should begin with an operand. Every operator should be followed by an operand or `(`.

###`RPN_PARSE_ERROR_INVALID_OPERATOR (3)`

Valid operators: `/[+-*/^]{1}/`

Expected the next character to be an operator character and encountered something else. Every operand should be followed by an operator or `)`

###`RPN_PARSE_ERROR_UNMATCHED_OPEN_PAREN (4)`

Encountered an open paren `(` without a matching close paren `)`. For example: `a-(b+c`

###`RPN_PARSE_ERROR_UNMATCHED_CLOSE_PAREN (5)`

Encountered an close paren `)` without a matching open paren `(`. For example: `a+b)-c`


##Credits
[Algorithm Approach - Pace CS](http://csis.pace.edu/~wolf/CS122/infix-postfix.htm)
