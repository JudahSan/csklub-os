.section .rodata
before_msg:
    .string "Before swap: x=%d, y=%d\n"
after_msg:
    .string "After swap:  x=%d, y=%d\n"

.text
.globl main
.type main, @function

main:
    pushl %ebp
    movl %esp, %ebp
    subl $16, %esp
    
    # Initialize local variables
    movl $5, -4(%ebp)   # x = 5
    movl $10, -8(%ebp)  # y = 10
    
    # Print before
    pushl -8(%ebp)
    pushl -4(%ebp)
    pushl $before_msg
    call printf
    addl $12, %esp
    
    # 32-bit swap (using registers)
    movl -4(%ebp), %eax  # t0 = x
    movl -8(%ebp), %ecx  # t1 = y
    movl %ecx, -4(%ebp)  # x = t1
    movl %eax, -8(%ebp)  # y = t0
    
    # Print after
    pushl -8(%ebp)
    pushl -4(%ebp)
    pushl $after_msg
    call printf
    addl $12, %esp
    
    movl $0, %eax
    leave
    ret