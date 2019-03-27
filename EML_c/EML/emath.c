/*
 * @file  ecore.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief   Math file.
 */

#include "emath.h"
#include <stdlib.h>

inline void randomSeed(unsigned int seed) {
	if (seed != 0)
		srand(seed);
}

inline long random(long howbig) {
	if (howbig == 0)
		return 0;
	return rand() % howbig;
}

inline long randomRange(long howsmall, long howbig) {
	if (howsmall >= howbig)
		return howsmall;
	long diff = howbig - howsmall;
	return random(diff) + howsmall;
}

inline int32 map(int32 value, int32 fromStart, int32 fromEnd, int32 toStart, int32 toEnd) {
     return ((int64)(value - fromStart) * (toEnd - toStart)) / (fromEnd - fromStart) +
         toStart;
 }

