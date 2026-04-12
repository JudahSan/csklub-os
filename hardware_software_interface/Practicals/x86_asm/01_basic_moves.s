.section .rodata
format_str:
    .string "Result: %d\n"

.text
.globl main
.type main, @function

main:
    pushl %ebp
    movl %esp, %ebp
    
    # Basic MOV operations
    movl $42, %eax      # Immediate to register
    movl %eax, %ebx     # Register to register
    movl $100, %ecx     # Another immediate
    
    # Memory operations
    subl $8, %esp       # Make space on stack
    movl $200, -4(%ebp) # Store to stack memory
    movl -4(%ebp), %edx # Load from stack memory
    
    # Different sizes
    movb $0xFF, %al     # Move byte (8-bit)
    movw $0xFFFF, %bx   # Move word (16-bit)
    movl $0xFFFFFFFF, %ecx  # Move long (32-bit)
    
    # Zero extension
    movzbl %al, %eax    # Zero extend byte to long
    movzwl %bx, %ebx    # Zero extend word to long
    
    # Sign extension
    movsbl %al, %eax    # Sign extend byte to long
    movswl %bx, %ebx    # Sign extend word to long
    
    # Print result
    pushl %eax
    pushl $format_str
    call printf
    addl $8, %esp
    
    movl $0, %eax
    leave
    ret