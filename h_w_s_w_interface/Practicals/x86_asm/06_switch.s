.section .rodata
.align 4
.L_jump_table:
    .long .L_default    # case 0
    .long .L_case1      # case 1
    .long .L_case2      # case 2
    .long .L_case3      # case 3
    .long .L_default    # case 4
    .long .L_case56     # case 5
    .long .L_case56     # case 6

.section .rodata
.day_names:
    .string "Invalid"
    .string "Monday"
    .string "Tuesday"
    .string "Wednesday"
    .string "Thursday"
    .string "Friday"
    .string "Saturday"
    .string "Sunday"

.text
.globl switch_example
.type switch_example, @function

switch_example:
    pushl %ebp
    movl %esp, %ebp
    
    movl $1, %eax        # w = 1
    movl 8(%ebp), %ecx   # ecx = x
    movl 12(%ebp), %edx  # edx = y
    movl 16(%ebp), %esi  # esi = z
    
    # Check if x is in range 0-6
    cmpl $6, %ecx
    ja .L_default        # if x > 6, goto default
    
    # Jump through jump table
    jmp *.L_jump_table(,%ecx,4)
    
.L_case1:
    # w = y * x
    movl %edx, %eax
    imull %ecx, %eax
    jmp .L_done
    
.L_case2:
    # w = y / x (fall through to case 3)
    movl %edx, %eax
    xorl %edx, %edx
    divl %ecx            # eax = y / x
    # Fall through
    
.L_case3:
    # w += z
    addl %esi, %eax
    jmp .L_done
    
.L_case56:
    # w -= z
    movl $1, %eax
    subl %esi, %eax
    jmp .L_done
    
.L_default:
    movl $2, %eax        # w = 2
    
.L_done:
    leave
    ret

# Jump table for day names
get_day_name:
    pushl %ebp
    movl %esp, %ebp
    
    movl 8(%ebp), %eax   # eax = day
    
    # Check bounds
    cmpl $1, %eax
    jl .L_invalid
    cmpl $7, %eax
    jg .L_invalid
    
    # Valid day - use jump table (simplified with array lookup)
    movl $.day_names, %ecx
    movl (%ecx,%eax,4), %eax
    jmp .L_done_name
    
.L_invalid:
    movl $.day_names, %eax
    
.L_done_name:
    leave
    ret

main:
    pushl %ebp
    movl %esp, %ebp
    subl $8, %esp
    
    # Call switch_example for multiple values
    movl $0, -4(%ebp)    # x = 0
    
.L_loop:
    cmpl $7, -4(%ebp)
    jg .L_loop_done
    
    # Call switch_example(x, 10, 5)
    pushl $5
    pushl $10
    pushl -4(%ebp)
    call switch_example
    addl $12, %esp
    
    # Print result (printf call would go here)
    
    incl -4(%ebp)
    jmp .L_loop
    
.L_loop_done:
    movl $0, %eax
    leave
    ret