/* crtn.o: the _init/_fini epilogues split from glibc 2.1 csu/initfini.c as
   egcs 1.1.2 compiled it (see crti.S).  */

	.file	"initfini.c"
	.version	"01.01"
gcc2_compiled.:
	.section .init
	movl -4(%ebp),%ebx
	leave
	ret

	.section .fini
	movl -4(%ebp),%ebx
	leave
	ret

	.ident	"GCC: (GNU) egcs-2.91.66 19990314/Linux (egcs-1.1.2 release)"
