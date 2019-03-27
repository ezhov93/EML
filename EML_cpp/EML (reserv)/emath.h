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

/**
 * @brief Initialize the pseudo-random number generator.
 * @param seed the number used to initialize the seed; cannot be zero.
 */
void randomSeed(unsigned int seed);

/**
 * @brief Generate a pseudo-random number with upper bound.
 * @param max An upper bound on the returned value, exclusive.
 * @return A pseudo-random number in the range [0,max).
 * @see randomSeed()
 */
long random(long max);

/**
 * @brief Generate a pseudo-random number with lower and upper bounds.
 * @param min Lower bound on the returned value, inclusive.
 * @param max Upper bound on the returned value, exclusive.
 * @return A pseudo-random number in the range [min, max).
 * @see randomSeed()
 */
long random(long min, long max);

/**
 * @brief Remap a number from one range to another.
 *
 * That is, a value equal to fromStart gets mapped to toStart, a value
 * of fromEnd to toEnd, and other values are mapped proportionately.
 *
 * Does not constrain value to lie within [fromStart, fromEnd].
 *
 * If a "start" value is larger than its corresponding "end", the
 * ranges are reversed, so map(n, 1, 10, 10, 1) would reverse the
 * range [1,10].
 *
 * Negative numbers may appear as any argument.
 *
 * @param value the value to map.
 * @param fromStart the beginning of the value's current range.
 * @param fromEnd the end of the value's current range.
 * @param toStart the beginning of the value's mapped range.
 * @param toEnd the end of the value's mapped range.
 * @return the mapped value.
 */
  static inline int32 map(int32 value, int32 fromStart, int32 fromEnd,
     int32 toStart, int32 toEnd) {
     return ((int64)(value - fromStart) * (toEnd - toStart)) / (fromEnd - fromStart) +
         toStart;
 }

extern uint16 makeWord( uint16 w ) ;
extern uint16 makeWord( uint8 h, uint8 l ) ;
#define word(...) makeWord(__VA_ARGS__)

#endif // EMATH_H
