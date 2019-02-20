/*
 * @file  main.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Main file.
 */
 
#include "estartup.h"
 
extern void setup(void);
extern void loop(void);

int main(void) {
  disableAllInterupts();
  disableAllPorts();
  systickSetup();	
  
	setup();
	while (1)
		loop();
}
