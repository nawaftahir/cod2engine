/* crti.o: glibc 2.1 csu/initfini.c as egcs 1.1.2 compiled it; the build
   splits that output into the _init/_fini prologues (here) and epilogues
   (crtn.S).  crtbegin/crtend drop their calls between the two.  */

	.file	"initfini.c"
	.version	"01.01"
gcc2_compiled.:
	.section .init
	.align 4
.globl _init
	.type	 _init,@function
_init:
	pushl %ebp
	movl %esp,%ebp
	pushl %ebx
	call .L1
.L1:
	popl %ebx
	addl $_GLOBAL_OFFSET_TABLE_+[.-.L1],%ebx
	cmpl $0,__gmon_start__@GOT(%ebx)
	je .L3
	call __gmon_start__@PLT
.L3:
	.align 4

	.section .fini
	.align 4
.globl _fini
	.type	 _fini,@function
_fini:
	pushl %ebp
	movl %esp,%ebp
	pushl %ebx
	call .L4
.L4:
	popl %ebx
	addl $_GLOBAL_OFFSET_TABLE_+[.-.L4],%ebx

	.weak	__gmon_start__
	.ident	"GCC: (GNU) egcs-2.91.66 19990314/Linux (egcs-1.1.2 release)"
