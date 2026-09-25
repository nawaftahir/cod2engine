/* crtbegin.o: GCC 3.3.4 crtstuff.c, CRT_BEGIN for i386-linux (non-PIC,
   frame registry, JCR).  Built with the runtime's own -O2 flags. */

typedef void (*func_ptr) (void);

struct object
{
	void *pc_begin;
	void *tbase;
	void *dbase;
	union
	{
		struct
		{
			void *tbase;
			void *dbase;
		} bases;
		void *single;
	} u;
};

extern void __register_frame_info_bases (void *, struct object *, void *, void *)
	__attribute__ ((weak));
extern void __deregister_frame_info_bases (void *)
	__attribute__ ((weak));
extern void _Jv_RegisterClasses (void *) __attribute__ ((weak));

static func_ptr __CTOR_LIST__[1]
	__attribute__ ((unused, section (".ctors"), aligned (sizeof (func_ptr))))
	= { (func_ptr) (-1) };

static func_ptr __DTOR_LIST__[1]
	__attribute__ ((section (".dtors"), aligned (sizeof (func_ptr))))
	= { (func_ptr) (-1) };

static const char __EH_FRAME_BEGIN__[]
	__attribute__ ((section (".eh_frame"), aligned (4)))
	= { };

static void *__JCR_LIST__[]
	__attribute__ ((unused, section (".jcr"), aligned (sizeof (void *))))
	= { };

/* Zero in the main program; hidden so every module keeps its own.  */
extern void *__dso_handle __attribute__ ((__visibility__ ("hidden")));
void *__dso_handle = 0;

/* Get the base of the GOT; i386-linux non-PIC variant.  */
#define CRT_GET_RFIB_DATA(BASE)						\
  __asm__ ("call\t.LPR%=\n"						\
	   ".LPR%=:\n\t"						\
	   "popl\t%0\n\t"						\
	   /* Due to a GAS bug, this cannot use EAX.  That encodes	\
	      smaller than the traditional EBX, which results in the	\
	      offset being off by one.  */				\
	   "addl\t$_GLOBAL_OFFSET_TABLE_+[.-.LPR%=],%0"			\
	   : "=d"(BASE))

static void __attribute__ ((used))
__do_global_dtors_aux (void)
{
	static func_ptr *p = __DTOR_LIST__ + 1;
	static _Bool completed;
	func_ptr f;

	if (!completed)
	{
		while ((f = *p))
		{
			p++;
			f ();
		}

		if (__deregister_frame_info_bases)
			__deregister_frame_info_bases (__EH_FRAME_BEGIN__);

		completed = 1;
	}
}

/* i386-linux CRT_CALL_STATIC_FUNCTION: a bare call dropped into .fini.  */
__asm__ ("\t.section\t.fini\n\tcall __do_global_dtors_aux\n\t.text");

static void __attribute__ ((used))
frame_dummy (void)
{
	static struct object object;
	void *tbase, *dbase;

	tbase = 0;
	CRT_GET_RFIB_DATA (dbase);
	if (__register_frame_info_bases)
		__register_frame_info_bases (__EH_FRAME_BEGIN__, &object, tbase, dbase);

	if (__JCR_LIST__[0] && _Jv_RegisterClasses)
		_Jv_RegisterClasses (__JCR_LIST__);
}

/* i386-linux CRT_CALL_STATIC_FUNCTION: a bare call dropped into .init.  */
__asm__ ("\t.section\t.init\n\tcall frame_dummy\n\t.text");
