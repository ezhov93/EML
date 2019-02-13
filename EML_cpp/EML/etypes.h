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
typedef void (*arg_ptr)(void *);

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
#define nullptr (void*)NULL;
#define null NULL

#ifdef __cplusplus
}
#endif

#endif // ETYPES_H
