.section .rodata
result_msg:
    .string "Result: %d\n"

.text
.globl main
.type main, @function

main:
    pushl %ebp
    movl %esp, %ebp
    subl $16, %esp
    
    # Initialize values
    movl $10, -4(%ebp)   # x = 10
    movl $5, -8(%ebp)    # y = 5
    movl $3, -12(%ebp)   # z = 3
    
    # Arithmetic operations using registers
    movl -4(%ebp), %eax   # eax = x
    movl -8(%ebp), %ebx   # ebx = y
    movl -12(%ebp), %ecx  # ecx = z
    
    # Basic arithmetic
    addl %ebx, %eax       # eax = x + y
    addl %ecx, %eax       # eax = (x+y) + z
    
    # Multiplication
    imull -4(%ebp), %ebx  # ebx = y * x
    imull $48, -8(%ebp), %edx  # edx = y * 48
    
    # Division (integer)
    movl $100, %eax
    movl $7, %ecx
    xorl %edx, %edx       # Clear high bits for division
    idivl %ecx            # eax = 100 / 7, edx = 100 % 7
    
    # Shift operations
    movl $0x0F0F0F0F, %eax
    shll $2, %eax         # Left shift by 2 (multiply by 4)
    shrl $1, %eax         # Right shift by 1 (divide by 2)
    
    # LEA examples (Load Effective Address)
    movl $5, %eax
    movl $3, %ebx
    leal (%eax, %ebx), %ecx      # ecx = eax + ebx = 8
    leal (,%eax,4), %edx         # edx = eax * 4 = 20
    leal 10(%ebx,%ebx,8), %esi   # esi = ebx*9 + 10 = 37
    
    # Print final result
    pushl %ecx
    pushl $result_msg
    call printf
    addl $8, %esp
    
    movl $0, %eax
    leave
    ret