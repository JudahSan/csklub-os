# ============================================================
# swap.s — x86-64 Assembly: Stack Frames & Register Conventions
# ============================================================

    .section .rodata
fmt_hdr:    .string "\n=== %s ===\n"
title_swap: .string "x86-64 swap demo"
title_reg:  .string "callee-save register demo"
fmt_before: .string "  Before: a=%d  b=%d\n"
fmt_after:  .string "  After : a=%d  b=%d\n"
fmt_callee: .string "  callee_demo(%d) -> %d  (rbx saved+restored)\n"

    .section .bss
val_a:  .long 0
val_b:  .long 0

    .section .text
    .globl main

# swap64(*xp, *yp): pure register call, no stack frame
swap64:
    movq (%rdi), %rax
    movq (%rsi), %rcx
    movq %rcx, (%rdi)
    movq %rax, (%rsi)
    ret

# callee_save_demo(x): uses %rbx, must save/restore it
callee_save_demo:
    pushq %rbp
    movq  %rsp, %rbp
    pushq %rbx
    movl  %edi, %ebx
    addl  $98195, %ebx
    movl  %ebx, %eax
    popq  %rbx
    popq  %rbp
    ret

main:
    pushq %rbp
    movq  %rsp, %rbp
    pushq %r12
    pushq %r13

    # -- Swap demo --
    leaq  fmt_hdr(%rip), %rdi
    leaq  title_swap(%rip), %rsi
    xorl  %eax, %eax
    call  printf

    movl  $15213, val_a(%rip)
    movl  $98195, val_b(%rip)

    leaq  fmt_before(%rip), %rdi
    movl  $15213, %esi
    movl  $98195, %edx
    xorl  %eax, %eax
    call  printf

    leaq  val_a(%rip), %rdi
    leaq  val_b(%rip), %rsi
    call  swap64

    leaq  fmt_after(%rip), %rdi
    movl  val_a(%rip), %esi
    movl  val_b(%rip), %edx
    xorl  %eax, %eax
    call  printf

    # -- Callee-save demo --
    leaq  fmt_hdr(%rip), %rdi
    leaq  title_reg(%rip), %rsi
    xorl  %eax, %eax
    call  printf

    movl  $15213, %edi
    call  callee_save_demo
    movl  %eax, %r12d

    leaq  fmt_callee(%rip), %rdi
    movl  $15213, %esi
    movl  %r12d, %edx
    xorl  %eax, %eax
    call  printf

    xorl  %eax, %eax
    popq  %r13
    popq  %r12
    popq  %rbp
    ret

    .section .note.GNU-stack,"",@progbits
