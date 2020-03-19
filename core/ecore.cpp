/*
 * @file   ecore.cpp
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  Main include source file.
 */

#include "ecore.h"
#include "econfig.h"

float coreClock() { return (float)CONFIG_CORE_CLOCK; }
void restart() { Config_restart(); };
