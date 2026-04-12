.section .rodata
result_msg:
    .string "factorial(%d) = %d\n"

.text
.globl main
.type main, @function

fact_while:
    pushl %ebp
    movl %esp, %ebp
    
    movl $1, %eax        # result = 1
    movl 8(%ebp), %ecx   # ecx = n
    
    # Jump to condition check (while loop optimization)
    jmp .L_condition
    
.L_loop:
    imull %ecx, %eax     # result *= n
    decl %ecx            # n--
    
.L_condition:
    cmpl $1, %ecx        # compare n with 1
    jg .L_loop           # if n > 1, continue loop
    
    leave
    ret

fact_do_while:
    pushl %ebp
    movl %esp, %ebp
    
    movl $1, %eax        # result = 1
    movl 8(%ebp), %ecx   # ecx = n
    
.L_do_loop:
    imull %ecx, %eax     # result *= n
    decl %ecx            # n--
    cmpl $1, %ecx        # compare n with 1
    jg .L_do_loop        # if n > 1, continue
    
    leave
    ret

# Power function using exponentiation by squaring
ipwr_for:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx           # Save callee-saved register
    
    movl $1, %eax        # result = 1
    movl 8(%ebp), %ebx   # ebx = x
    movl 12(%ebp), %ecx  # ecx = p
    
    # Jump to condition (for loop optimization)
    jmp .L_power_cond
    
.L_power_loop:
    # Check if p is odd
    testl $1, %ecx
    jz .L_even
    imull %ebx, %eax     # result *= x
    
.L_even:
    imull %ebx, %ebx     # x *= x
    shrl $1, %ecx        # p >>= 1
    
.L_power_cond:
    testl %ecx, %ecx     # test if p != 0
    jnz .L_power_loop    # if p != 0, continue
    
    popl %ebx
    leave
    ret

main:
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    
    # Call fact_while(5)
    pushl $5
    call fact_while
    addl $4, %esp
    
    # Print result
    pushl %eax
    pushl $5
    pushl $result_msg
    call printf
    addl $12, %esp
    
    movl $0, %eax
    leave
    ret