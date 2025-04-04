
/***************************************************
 *@file CAN_GernalType.h
 *@brief CAN General Types header File
 *@details This file includes some definition about type and kind of structure in CAN Driver in AUTOSAR
 *@version 1.0
 *@date 10-31-20244
 *@author Hoang Long Vu
 ****************************************************/


/* See CopmpilerAbstraction.pdf */
#ifndef COMPILER_H
#define COMPILER_H



#define STATIC 	static
#define NULL_PTR	((void *)0)

#if defined(__GNUC__)
#define CC_EXTENSION 	__extension__
#elif defined(__CWCC__)
#define CC_EXTENSION
#pragma read_only_switch_tables on
#elif defined(__DCC__)
#define CC_EXTENSION
#endif





#if defined(__GNUC__)
#define __balign(x)       __attribute__ ((aligned (x)))
#elif defined(__CWCC__)
#define __balign(x)       __attribute__ ((aligned (x)))
#elif defined(__DCC__)
#define __balign(x)       __attribute__ ((aligned (x)))
#elif defined(__ICCHCS12__)
#define Pragma(x) _Pragma(#x)
#define __balign(x)       Pragma(data_alignment=x)
#else
#error Compiler not defined.
#endif

#define SECTION_BALIGN(x)  __balign(x)

#if defined(__ICCHCS12__)
#define restrict
#define DECLARE_WEAK
#define __simple __simple
#else
#define DECLARE_WEAK			__attribute__ ((weak))
#define __simple
#endif

/* Does this really work on all compilers.... */
#define INLINE __inline__


#define FUNC(rettype,memclass) rettype

#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *

#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *

#define CONSTP2VAR(ptrtype,memclass,ptrclass) ptrtype * const

#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const

#define P2FUNC(rettype,ptrclass,fctname) rettype (*fctname)

#ifndef CONST // for WIN32
#define CONST(consttype,memclass) const consttype
#endif

#define VAR(vartype,memclass) vartype


#endif /* COMPILER_H */	
