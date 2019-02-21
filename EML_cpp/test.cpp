#include "ecore.h"
#include "etimer.h"

const Pin led = PD10;
const Pin adc = PD7;
const Pin dac = PE9;
ETimer timer1(1, ETimer::MSEC);
uint16 result = 0;

void blink();

void setup() {
  setCoreClock(72);
	pinMode(led, OUTPUT);
	pinMode(adc, INPUT_ANALOG);
  pinMode(dac, OUTPUT_ANALOG);
  timer1.attachInterrupt(timer1Event);
  timer1.setSingleShot(true);
  timer1.start(1000);
}

void loop() {
	// togglePin(led);
  result = analogRead(adc);
  analogWrite(dac, 1024);
  delayMicroseconds(1000*1000);
}

void timer1Event() {
  togglePin(led);
}
