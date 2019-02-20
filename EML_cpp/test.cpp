#include "ecore.h"

const Pin led = PD10;
const Pin adc = PD7;
const Pin dac = PE9;
uint16 result = 0;

void setup() {
  setCoreClock(72);
	pinMode(led, OUTPUT);
	pinMode(adc, INPUT_ANALOG);
  pinMode(dac, OUTPUT_ANALOG);
}

void loop() {
	togglePin(led);
  result = analogRead(adc);
  analogWrite(dac, 1024);
  delayMicroseconds(1000*1000);
}
