#include "ecore.h"

const Pin led = PD10;

void setup() {
	pinMode(led, OUTPUT);
}

void loop() {
	digitalWrite(led, HIGH);
	
}

