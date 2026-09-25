/* crt1.o: glibc sysdeps/i386/elf/start.S, the form that passes _init and
   _fini straight to __libc_start_main.  The ELF entry point. */

	.text
	.globl	_start
	.type	_start,@function
_start:
	xorl	%ebp, %ebp
	popl	%esi			/* argc */
	movl	%esp, %ecx		/* argv */
	andl	$0xfffffff8, %esp
	pushl	%eax			/* garbage: keeps the stack aligned */
	pushl	%esp			/* stack end */
	pushl	%edx			/* rtld_fini */
	pushl	$_fini
	pushl	$_init
	pushl	%ecx			/* argv */
	pushl	%esi			/* argc */
	pushl	$main
	call	__libc_start_main
	hlt				/* __libc_start_main never returns */
	.size	_start,.-_start

/* To fulfill the System V/i386 ABI we need this symbol.  Yuck, it's so
   meaningless since we don't support machines < 80386.  */
	.section .rodata
	.globl	_fp_hw
_fp_hw:	.long	3
	.size	_fp_hw, 4
	.type	_fp_hw,@object

/* Define a symbol for the first piece of initialized data.  */
	.data
	.globl	__data_start
__data_start:
	.long	0
	.weak	data_start
	data_start = __data_start
