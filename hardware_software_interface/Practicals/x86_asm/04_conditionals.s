.section .rodata
msg_abs:
    .string "absdiff(%d, %d) = %d\n"

.text
.globl main
.type main, @function

absdiff:
    pushl %ebp
    movl %esp, %ebp
    
    movl 8(%ebp), %eax   # eax = x
    movl 12(%ebp), %edx  # edx = y
    
    # Compare x and y
    cmpl %edx, %eax
    jle .L_else          # if x <= y, jump to else
    
    # Then branch: x > y
    subl %edx, %eax      # result = x - y
    jmp .L_done
    
.L_else:
    # Else branch: x <= y
    movl %edx, %eax
    subl 8(%ebp), %eax   # result = y - x
    
.L_done:
    leave
    ret

# absdiff using conditional move (more efficient)
absdiff_cmov:
    pushl %ebp
    movl %esp, %ebp
    
    movl 8(%ebp), %eax   # eax = x
    movl 12(%ebp), %edx  # edx = y
    
    # Compute both results
    movl %eax, %ecx
    subl %edx, %ecx      # ecx = x - y
    
    movl %edx, %esi
    subl %eax, %esi      # esi = y - x
    
    # Conditional move
    cmpl %edx, %eax      # compare x and y
    cmovle %esi, %ecx    # if x <= y, ecx = esi
    
    movl %ecx, %eax      # result = ecx
    
    leave
    ret

main:
    pushl %ebp
    movl %esp, %ebp
    subl $16, %esp
    
    # Test pairs
    movl $10, -4(%ebp)   # x = 10
    movl $5, -8(%ebp)    # y = 5
    
    # Call absdiff
    pushl -8(%ebp)
    pushl -4(%ebp)
    call absdiff
    addl $8, %esp
    
    # Print result
    pushl %eax
    pushl -8(%ebp)
    pushl -4(%ebp)
    pushl $msg_abs
    call printf
    addl $16, %esp
    
    movl $0, %eax
    leave
    ret