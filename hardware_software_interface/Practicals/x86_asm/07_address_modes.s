.section .rodata
array_msg:
    .string "arr[%d] = %d\n"
struct_msg:
    .string "p.%s = %d\n"

.text
.globl main
.type main, @function

main:
    pushl %ebp
    movl %esp, %ebp
    subl $64, %esp      # Make space for local variables
    
    # Array initialization
    movl $10, -20(%ebp) # arr[0]
    movl $20, -16(%ebp) # arr[1]
    movl $30, -12(%ebp) # arr[2]
    movl $40, -8(%ebp)  # arr[3]
    movl $50, -4(%ebp)  # arr[4]
    
    # Different addressing modes
    
    # 1. Direct addressing (immediate)
    movl $42, -24(%ebp)  # Direct: value = 42
    
    # 2. Register indirect
    leal -20(%ebp), %eax # eax = address of arr
    movl (%eax), %ebx    # ebx = arr[0]
    
    # 3. Displacement addressing
    movl 8(%eax), %ecx   # ecx = arr[2] (offset 8 bytes)
    
    # 4. Indexed addressing
    movl $2, %edx        # edx = index
    movl -20(%ebp,%edx,4), %esi  # esi = arr[2]
    
    # 5. Base-index addressing
    movl $1, %edi        # edi = row
    movl $2, %ebp        # ebp = col (using ebp carefully)
    # For 2D array: address = base + (row * COLS + col) * element_size
    # Simplified example
    
    # Scaled index addressing example
    movl $3, %eax        # index
    movl -20(%ebp,%eax,4), %ebx  # arr[3] using scaled index
    
    # LEA for address calculation
    leal (%eax,%eax,2), %ecx     # ecx = eax * 3
    leal 0(,%eax,8), %edx        # edx = eax * 8
    leal 10(%eax,%eax,4), %esi   # esi = eax*5 + 10
    
    # Print some results
    pushl %ebx
    pushl $3
    pushl $array_msg
    call printf
    addl $12, %esp
    
    movl $0, %eax
    leave
    ret