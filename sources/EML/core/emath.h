/*
 * @file  emath.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief   Math header.
 */

#ifndef EMATH_H
#define EMATH_H

#include "etypes.h"

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

#define EULER 2.718281828459045235360287471352

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define constrain(amt, low, high) \
  ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define round(x) ((x) >= 0 ? (long)((x) + 0.5) : (long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x) * (x))
#define inRange(amt, low, high) ((amt - high) * (amt - low) <= 0)
#define MAP(value, fromStart, fromEnd, toStart, toEnd) \
  (((value - fromStart) * (toEnd - toStart)) / (fromEnd - fromStart) + toStart)

void randomSeed(unsigned int seed);
long random(long max);
long random(long min, long max);
static inline int32 map(int32 value, int32 fromStart, int32 fromEnd,
                        int32 toStart, int32 toEnd) {
  return ((int64)(value - fromStart) * (toEnd - toStart)) /
             (fromEnd - fromStart) +
         toStart;
}

extern uint16 makeWord(uint16 w);
extern uint16 makeWord(uint8 h, uint8 l);
#define word(...) makeWord(__VA_ARGS__)

#endif  // EMATH_H
