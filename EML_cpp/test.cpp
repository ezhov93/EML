#include "ecore.h"
#include "etimer.h"
#include "eserial.h"
#include "estring.h"

const Pin led = PD10;
const Pin adc = PD7;
const Pin dac = PE9;
ETimer timer(1, ETimer::MS);
ESerial<Eml::Size64> serial(2, PF1, PF0);
uint16 result = 0;

void timerEvent();
void recvEvent();

void setup() {
  setCoreClock(72);
	pinMode(led, OUTPUT);
	pinMode(adc, INPUT_ANALOG);
  pinMode(dac, OUTPUT_ANALOG);
  timer.attachInterrupt(timerEvent);
  timer.start(1000);
  serial.attachInterrupt(serial.ReceivedData, recvEvent);
  serial.begin(9600);
}

void loop() {
  result = analogRead(adc);
  analogWrite(dac, 1024);
  if (!serial.availableForWrite()) {
    EString str("hello");
    str.toUpperCase();
    serial.println(str);
    serial.println(3.12345678, 3);
    serial.println(0x123);
    serial.println(0x123, serial.BIN);  
  }
  delay(1000);
}

void timerEvent() {
  togglePin(led);
}

void recvEvent() {
  while (serial.available())
    serial.write(serial.read());
}
