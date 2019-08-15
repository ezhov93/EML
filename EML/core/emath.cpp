/*
 * @file  ecore.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief   Math file.
 */

#include "emath.h"
#include <stdlib.h>

void randomSeed(unsigned int seed) {
  if (seed != 0) srand(seed);
}

long random(long howbig) {
  if (howbig == 0) return 0;
  return rand() % howbig;
}

long random(long howsmall, long howbig) {
  if (howsmall >= howbig) return howsmall;
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}

extern uint16 makeWord(uint16 w) { return w; }

extern uint16 makeWord(uint8 h, uint8 l) { return (h << 8) | l; }
