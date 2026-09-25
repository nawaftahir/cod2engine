/* crt1.o: glibc 2.1 csu/init.c as egcs 1.1.2 compiled it, which records the
   stdio version the program was linked against:
	const int _IO_stdin_used = _G_IO_IO_FILE_VERSION;
   egcs is not in the toolchain image, so its output is kept here.  */

	.file	"init.c"
	.version	"01.01"
gcc2_compiled.:
.globl _IO_stdin_used
.section	.rodata
	.align 4
	.type	 _IO_stdin_used,@object
	.size	 _IO_stdin_used,4
_IO_stdin_used:
	.long 131073
	.ident	"GCC: (GNU) egcs-2.91.66 19990314/Linux (egcs-1.1.2 release)"
