/* crt1.o: glibc csu/abi-note.S.  The ELF note that tags the program as a
   GNU/Linux binary needing at least kernel 2.0.0.  */

	.section .note.ABI-tag, "a"
	.p2align 2
	.long	1f - 0f			/* name length */
	.long	3f - 2f			/* data length */
	.long	1			/* note type */
0:	.asciz	"GNU"			/* vendor name */
1:	.p2align 2
2:	.long	0			/* OS: Linux */
	.long	2, 0, 0			/* kernel 2.0.0 */
3:	.p2align 2
