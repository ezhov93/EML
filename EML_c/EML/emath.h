/*
 * @file  emath.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief   Math header.
 */

#ifndef EMATH_H
#define EMATH_H

#include "etypes.h"

#define PI          3.1415926535897932384626433832795
#define HALF_PI     1.5707963267948966192313216916398
#define TWO_PI      6.283185307179586476925286766559
#define DEG_TO_RAD  0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
 
#define EULER 2.718281828459045235360287471352
#define SERIAL  0x0
#define DISPLAY 0x1 

#define min(a,b)                ((a)<(b)?(a):(b))
#define max(a,b)                ((a)>(b)?(a):(b))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)                ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg)            ((deg)*DEG_TO_RAD)
#define degrees(rad)            ((rad)*RAD_TO_DEG)
#define sq(x)                   ((x)*(x))

void randomSeed(unsigned int seed);
long random(long max);
long randomRange(long min, long max);
int32 map(int32 value, int32 fromStart, int32 fromEnd, int32 toStart, int32 toEnd);

#endif // EMATH_H
