	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"%d"
	.text
.globl g
	.type	g, @function
g:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	8(%ebp), %eax
	addl	$3, %eax
	leave
	ret
	.size	g, .-g
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	g
	leave
	ret
	.size	f, .-f
.globl t
	.type	t, @function
t:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %eax
	addl	$65, %eax
	movb	%al, -9(%ebp)
	movl	$1, 8(%esp)
	leal	-9(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	write
	leave
	ret
	.size	t, .-t
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$10, 28(%esp)
	cmpl	$10, 28(%esp)
	jle	.L8
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	t
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	g
	jmp	.L7
.L8:
	movl	$8, (%esp)
	call	f
	addl	$1, %eax
.L7:
	leave
	ret
