/* crtend.o: GCC 3.3.4 crtstuff.c, CRT_END for i386-linux.  Built with the
   runtime's own -O2 flags. */

typedef void (*func_ptr) (void);

static func_ptr __CTOR_END__[1]
	__attribute__ ((unused, section (".ctors"), aligned (sizeof (func_ptr))))
	= { (func_ptr) 0 };

static func_ptr __DTOR_END__[1]
	__attribute__ ((unused, section (".dtors"), aligned (sizeof (func_ptr))))
	= { (func_ptr) 0 };

/* Terminate the frame unwind info section with a 4byte 0 as a sentinel. */
static const int __FRAME_END__[]
	__attribute__ ((unused, section (".eh_frame"), aligned (4)))
	= { 0 };

static void *__JCR_END__[1]
	__attribute__ ((unused, section (".jcr"), aligned (sizeof (void *))))
	= { 0 };

static void __attribute__ ((used))
__do_global_ctors_aux (void)
{
	func_ptr *p;

	for ( p = __CTOR_END__ - 1; *p != (func_ptr) -1; p-- )
		(*p) ();
}

/* i386-linux CRT_CALL_STATIC_FUNCTION: a bare call dropped into .init.  */
__asm__ ("\t.section\t.init\n\tcall __do_global_ctors_aux\n\t.text");
