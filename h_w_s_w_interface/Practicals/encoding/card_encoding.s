	.file	"card_encoding.c"
	.text
	.globl	sameSuitP
	.type	sameSuitP, @function
sameSuitP:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movb	%dl, -4(%rbp)
	movb	%al, -8(%rbp)
	movsbl	-4(%rbp), %eax
	andl	$48, %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movsbl	-8(%rbp), %edx
	andl	$48, %edx
	xorl	%edx, %eax
	testl	%eax, %eax
	setne	%al
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	sameSuitP, .-sameSuitP
	.globl	greaterValue
	.type	greaterValue, @function
greaterValue:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movb	%dl, -4(%rbp)
	movb	%al, -8(%rbp)
	movsbl	-4(%rbp), %eax
	andl	$15, %eax
	movsbl	-8(%rbp), %edx
	andl	$15, %edx
	cmpl	%eax, %edx
	setb	%al
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	greaterValue, .-greaterValue
	.section	.rodata
	.align 8
.LC0:
	.string	"Comparing 7\357\270\217\342\203\243 \342\235\244\357\270\217 and 2\357\270\217\342\203\243 \342\235\244\357\270\217:"
.LC1:
	.string	" Same suit. \342\234\205"
.LC2:
	.string	" Different suits. \342\235\214"
.LC3:
	.string	" Greater value. \342\234\205"
.LC4:
	.string	" Not greater value. \342\235\214"
	.align 8
.LC5:
	.string	"\nComparing 7\357\270\217\342\203\243 \342\235\244\357\270\217 and 5\357\270\217\342\203\243 \342\231\246\357\270\217:"
	.align 8
.LC6:
	.string	"\nComparing 7\357\270\217\342\203\243 \342\235\244\357\270\217 and 7\357\270\217\342\203\243 \342\231\240\357\270\217 (Equal values):"
.LC7:
	.string	"  Same suit. \342\235\214"
.LC8:
	.string	"  Different suits. \342\234\205"
.LC9:
	.string	"  Greater value. \342\235\214"
.LC10:
	.string	"  Not greater value. \342\234\205"
	.align 8
.LC11:
	.string	"\nComparing 2\357\270\217\342\203\243 \342\235\244\357\270\217 and 5\357\270\217\342\203\243 \342\231\246\357\270\217:"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movb	$39, -4(%rbp)
	movb	$34, -3(%rbp)
	movb	$21, -2(%rbp)
	movb	$55, -1(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movsbl	-3(%rbp), %edx
	movsbl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	sameSuitP
	testb	%al, %al
	je	.L6
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L7
.L6:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L7:
	movsbl	-3(%rbp), %edx
	movsbl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	greaterValue
	testb	%al, %al
	je	.L8
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L9
.L8:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L9:
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movsbl	-2(%rbp), %edx
	movsbl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	sameSuitP
	testb	%al, %al
	je	.L10
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L11
.L10:
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L11:
	movsbl	-2(%rbp), %edx
	movsbl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	greaterValue
	testb	%al, %al
	je	.L12
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L13
.L12:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L13:
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movsbl	-1(%rbp), %edx
	movsbl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	sameSuitP
	testb	%al, %al
	je	.L14
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L15
.L14:
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L15:
	movsbl	-1(%rbp), %edx
	movsbl	-4(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	greaterValue
	testb	%al, %al
	je	.L16
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L17
.L16:
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L17:
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movsbl	-2(%rbp), %edx
	movsbl	-3(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	sameSuitP
	testb	%al, %al
	je	.L18
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L19
.L18:
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L19:
	movsbl	-2(%rbp), %edx
	movsbl	-3(%rbp), %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	greaterValue
	testb	%al, %al
	je	.L20
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L21
.L20:
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L21:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
