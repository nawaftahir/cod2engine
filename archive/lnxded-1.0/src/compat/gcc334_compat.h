/* gcc 3.3.4 compatibility shim */
#ifndef GCC334_COMPAT_H
#define GCC334_COMPAT_H

/* gcc 3.3.4 doesn't support static_assert or _Pragma */
#define static_assert(expr, msg)
#define _Pragma(x)

#ifdef __cplusplus
#define _Bool bool
#endif

#endif
