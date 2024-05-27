/*	SCCS Id: @(#)tradstdc.h 3.4	1993/05/30	*/
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef TRADSTDC_H
#define TRADSTDC_H

/*
 * ANSI X3J11 detection.
 * Makes substitutes for compatibility with the old C standard.
 */

#ifdef NEED_VARARGS		/* only define these if necessary */
/*
 * These have changed since 3.4.3.  VA_END() now provides an explicit
 * closing brace to complement VA_DECL()'s hidden opening brace, so code
 * started with VA_DECL() needs an extra opening brace to complement
 * the explicit final closing brace.  This was done so that the source
 * would look less strange, where VA_DECL() appeared to introduce a
 * function whose opening brace was missing; there are now visible and
 * invisible braces at beginning and end.  Sample usage:
void foo VA_DECL(int, arg)  --macro expansion has a hidden opening brace
{  --new, explicit opening brace (actually introduces a nested block)
  VA_START(bar);
  ...code for foo...
  VA_END();  --expansion now provides a closing brace for the nested block
}  --existing closing brace, still pairs with the hidden one in VA_DECL()
 * Reading the code--or using source browsing tools which match braces--
 * results in seeing a matched set of braces.  Usage of VA_END() is
 * potentially trickier, but nethack uses it in a straightforward manner.
 */

#include <stdarg.h>
#define VA_DECL(typ1,var1)	(typ1 var1, ...) { va_list the_args;
#define VA_DECL2(typ1,var1,typ2,var2)	\
	(typ1 var1, typ2 var2, ...) { va_list the_args;
#define VA_INIT(var1,typ1)
#define VA_NEXT(var1,typ1)	var1 = va_arg(the_args, typ1)
#define VA_ARGS		the_args
#define VA_START(x)		va_start(the_args, x)
#define VA_END()		va_end(the_args); }

#endif /* NEED_VARARGS */

/*
 * Allow gcc2 to check parameters of printf-like calls with -Wformat;
 * append this to a prototype declaration (see pline() in extern.h).
 */
#ifdef __GNUC__
# if __GNUC__ >= 2
#define PRINTF_F(f,v) __attribute__ ((format (printf, f, v)))
# endif
#endif
#ifndef PRINTF_F
#define PRINTF_F(f,v)
#endif

/*
 * If we don't have C23 <stdckdint.h>, fall back to GCC
 * __builtin_*_overflow functions.  If we don't have those either,
 * fall back to implementation using C11 _Generic.
 */
#if __has_include(<stdckdint.h>)
# include <stdckdint.h>
#else
# ifdef __GNUC__
#  define ckd_add(R, A, B) __builtin_add_overflow ((A), (B), (R))
#  define ckd_sub(R, A, B) __builtin_sub_overflow ((A), (B), (R))
#  define ckd_mul(R, A, B) __builtin_mul_overflow ((A), (B), (R))
# else
#  define max_int_value(I)						\
	_Generic((I),							\
		 signed char: SCHAR_MAX,				\
		 short: SHRT_MAX,					\
		 int: INT_MAX,						\
		 long: LONG_MAX,					\
		 long long: LLONG_MAX,					\
		 unsigned char: UCHAR_MAX,				\
		 unsigned short: USHRT_MAX,				\
		 unsigned int: UINT_MAX,				\
		 unsigned long: ULONG_MAX,				\
		 unsigned long long: ULLONG_MAX,			\
		 default: LARGEST_INT)
#  define min_int_value(I)						\
	_Generic((I),							\
		 signed char: SCHAR_MIN,				\
		 short: SHRT_MIN,					\
		 int: INT_MIN,						\
		 long: LONG_MIN,					\
		 long long: LLONG_MIN,					\
		 default: 0)
#  define ckd_add(R, A, B)						\
	((((A) > 0) && ((B) > max_int_value(*(R)) - (A)))		\
	 ? (*(R) = ((A) + min_int_value(*(R))) + ((B) + min_int_value(*(R))), TRUE) \
	 : ((((A) < 0) && ((B) < min_int_value(*(R)) - (A)))		\
	    ? (*(R) = ((A) - min_int_value(*(R))) + ((B) - min_int_value(*(R))), TRUE) \
	    : (*(R) = ((A) + (B)), FALSE)))
#  define ckd_sub(R, A, B) ckd_add((R), (A), -(B))
/* Lazy implementation: only works for 32-bit types */
#  define ckd_mul(R, A, B) (*(R) = (long long)(A) * (B), ((long long)(A) * (B)) > max_int_value(*(R)))
# endif /* __GNUC__ */
#endif /* __has_include(<stdckdint.h>) */

#endif /* TRADSTDC_H */
