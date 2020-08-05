;; To run: gcc division.ll && ./a.out

; The first two statements declare a string and a function that are used for printing to stdout. You can ignore these.
@.str = private constant [12 x i8] c"Output: %d\0A\00"
declare i32 @printf(i8*, ...)

; In this problem, we will be implementing a simple division algorithm in LLVM,
; which is an assembly-like language.

; You will need to understand the following commands:

; Memory: alloca, store, load
; Arithmetic: add, sub
; Conditionals: icmp [integer compare], br [branch]

; Language Reference: http://llvm.org/docs/LangRef.html


define i32 @main() {
start:
  ; Convenience: %str can be used for printing.
  %str = getelementptr inbounds [12 x i8], [12 x i8]* @.str, i32 0, i1 0

  ; Input: numerator & denominator, as registers.
  %num = add i32 0, 300
  %denom = add i32 0, 7

  ; Jump to start of your code.
  ; Note that there is no fall-through; we must jump to a label or return.
  br label %code


; You do not need to modify code above here.
code:
  ; Let's see how memory works!
  ; To motivate memory, please note that registers are "static single assignment" (SSA).
  ; This means that only one line in the program can assign to a particular register.
  %memory_example = alloca i32 ; Allocate some memory. Memory is mutable, unlike registers.
  store i32 0, i32* %memory_example ; We must initialize our memory before using it.
  %register = load i32, i32* %memory_example ; In order to operate on data, we must load it into an immutable register.
  %register2 = add i32 10, %register ; We can create a new register based on the first one.
  store i32 %register2, i32* %memory_example ; And we can then store the result back into the original memory

  ; Here's a silly division algorithm that's almost always wrong.
  %quotient = add i32 %denom, %denom
  %remainder = add i32 0, 0
  call i32 (i8*, ...) @printf(i8* %str, i32 %quotient)
  call i32 (i8*, ...) @printf(i8* %str, i32 %remainder)
  ret i32 0
}

