#include "ecore.h"
#include "etimer.h"
#include "eserial.h"

const Pin led = PD10;
const Pin adc = PD7;
const Pin dac = PE9;
ETimer timer(1, ETimer::MS);
#define ESERIAL_DATA_SIZE 32
ESerial serial(2, PF1, PF0);
uint16 result = 0;

void timerEvent();

void setup() {
  setCoreClock(72);
	pinMode(led, OUTPUT);
	pinMode(adc, INPUT_ANALOG);
  pinMode(dac, OUTPUT_ANALOG);
  timer.attachInterrupt(timerEvent);
  timer.start(1000);
  serial.begin(9600);
}

void loop() {
	// togglePin(led);
  result = analogRead(adc);
  analogWrite(dac, 1024);
  
  delay(1000);
}

void timerEvent() {
  togglePin(led);
}
