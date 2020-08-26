;; To run: clang division_solution.ll && ./a.out

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
  %num = add i32 0, 13
  %denom = add i32 0, 3

  ; Jump to start of your code.
  ; Note that there is no fall-through; we must jump to a label or return.
  br label %code


; You do not need to modify code above here.
code:
  ; Let's see how memory works!
  ; To motivate memory, please note that registers are "static single assignment" (SSA).
  ; This means that only one line in the program can assign to a particular register!!!!
  %q = alloca i32
  %r = alloca i32
  %z = alloca i32
  %pr = alloca i32
  %pz = alloca i32
  %n = alloca i32

  store i32 0, i32* %q
  store i32 %num, i32* %n

  br label %MY_CODE

MY_CODE:
  store i32 1, i32* %r
  store i32 1, i32* %pr
  store i32 %denom, i32* %z

  %rg0 = load i32, i32* %z
  store i32 %rg0, i32* %pz

  %rgz = load i32, i32* %z
  %rgz2 = load i32, i32* %n
  %cond = icmp sle i32 %rgz, %rgz2
  br i1 %cond, label %WHILE_LOOP, label %WHILE_LOOP_END

WHILE_LOOP:
  %00 = load i32, i32* %r
  store i32 %00, i32* %pr
  %01 = load i32, i32* %z
  store i32 %01, i32* %pz

  %rg1 = load i32, i32* %z
  %rg2 = load i32, i32* %z
  %rg3 = add i32 %rg1, %rg2
  store i32 %rg3, i32* %z

  %rg4 = load i32, i32* %r
  %rg5 = load i32, i32* %r
  %rg6 = add i32 %rg4, %rg5
  store i32 %rg6, i32* %r

  %02 = load i32, i32* %z
  %03 = load i32, i32* %n
  %cond2 = icmp sle i32 %02, %03
  br i1 %cond2, label %WHILE_LOOP, label %WHILE_LOOP_END

WHILE_LOOP_END:
  %4 = load i32, i32* %pz ; n = n - pz
  %5 = load i32, i32* %n
  %6 = sub i32 %5, %4
  store i32 %6, i32* %n

  %7 = load i32, i32* %pr; res = res + pr
  %8 = load i32, i32* %q
  %9 = add i32 %8, %7
  store i32 %9, i32* %q

  %10 = load i32, i32* %n ; if (n >= denom)
  %cond3 = icmp sge i32 %10, %denom
  br i1 %cond3, label %MY_CODE, label %MY_CODE_END

MY_CODE_END:
  %quotient = load i32, i32* %q
  %remainder = load i32, i32* %n

  call i32 (i8*, ...) @printf(i8* %str, i32 %quotient)
  call i32 (i8*, ...) @printf(i8* %str, i32 %remainder)

  ret i32 0
}

