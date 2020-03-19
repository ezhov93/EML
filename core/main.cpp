/*
 * @file  main.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Main file.
 */

#include "econfig.h"

extern void setup(void);
extern void loop(void);

static __attribute__((constructor(101))) void premain() { Config_Time_setup(); }

int main(void) {
   setup();
  while (1) loop();
}
