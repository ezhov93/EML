/*
 * @file   etypes.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Library type definitions.
 */

#ifndef ETYPES_H
#define ETYPES_H

#ifndef __cplusplus
typedef enum {false, true=!false } bool;
#endif
/*
#ifdef __cplusplus
#define EML_ADD_TEMPLATE_SIZE(name) template class name<Eml::Size1>;    \
                                    template class name<Eml::Size2>;    \
                                    template class name<Eml::Size4>;    \
                                    template class name<Eml::Size8>;    \
                                    template class name<Eml::Size16>;   \
                                    template class name<Eml::Size32>;   \
                                    template class name<Eml::Size64>;   \
                                    template class name<Eml::Size128>;  \
                                    template class name<Eml::Size256>;  \
                                    template class name<Eml::Size512>;  \
                                    template class name<Eml::Size1024>; \
                                    template class name<Eml::Size2048>; \
                                    template class name<Eml::Size4096>; \
                                    template class name<Eml::Size8192>; \
                                    
namespace Eml {
  typedef enum  {
    Size1    =   1,
    Size2    =   2,
    Size4    =   4,
    Size8    =   8,
    Size16   =  16,
    Size32   =  32,
    Size64   =  64,
    Size128  = 128,
    Size256  = 256,
    Size512  = 512,
    Size1024 = 1024,
    Size2048 = 2048,
    Size4096 = 4096,
    Size8192 = 8192
  } Size;
}
#endif
*/

#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef signed char int8;
typedef short int16;
typedef int int32;
typedef long long int64;

typedef uint8  byte;
typedef uint16 word;
typedef uint32 dword;

/* custom type */
typedef float real;
typedef bool boolean;
typedef enum { FALSE,TRUE } BOOL;
typedef enum { LSBFIRST, MSBFIRST } BitOrder;

typedef void (*func_ptr)(void);
typedef void (*argFunc_ptr)(void *);
typedef bool (*signal_ptr)(void);

#define __IO volatile
#define __attr_flash __attribute__((section (".USER_FLASH")))
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif
#define __deprecated __attribute__((__deprecated__))
#define __weak __attribute__((weak))
#ifndef __always_inline
#define __always_inline __attribute__((always_inline))
#endif
#ifndef __unused
#define __unused __attribute__((unused))
#endif

#ifndef NULL
#define NULL 0
#endif

#if (__ARMCOMPILER_VERSION < 6000000)
#define nullptr (void*)NULL;
#endif

#define null NULL

#ifdef __cplusplus
}
#endif

#endif // ETYPES_H
