/*
 * @file   epin_private.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Private pin header.
 */

#ifndef EPIO_PRIVATE_H
#define EPIO_PRIVATE_H

#include "MDR32F9Qx_port.h"
#include "etypes.h"

#define NONE -1

typedef struct PinMap {
  MDR_PORT_TypeDef *port;
  int pin;
  int rstClk;
  int chAdc;
  int chDac;
} PinMap;

extern const PinMap pinMap[];

#endif  // EPIO_PRIVATE_H
