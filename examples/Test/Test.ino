/*
 Name:		Test.ino
 Author:	Sindre Halbjørhus
*/

#define DEBUG

#include <OneWire.h>
#include "DS2401.h"

OneWire oneWire(2);

DS2401 ds24(&oneWire);

void setup() {
	Serial.begin(9600);
	delay(10);
	Serial.println("DEBUG:");


	if (ds24.init())
	{
		#ifdef DEBUG
		Serial.println(F("Found OneWire Device"));
		#endif // DEBUG
	}
	else
	{
		#ifdef DEBUG
		Serial.println(F("ERROR: No OneWire Device Found"));
		#endif // DEBUG
	}

	if (ds24.isDS2401())
	{
		#ifdef DEBUG
		Serial.println(F("IS DS2401"));
		#endif // DEBUG
	}
	else
	{
		#ifdef DEBUG
		Serial.println(F("ERROR: Is Not DS2401"));
		#endif // DEBUG
	}

}


void loop() {
	Serial.println(ds24.GetSerial());
	delay(2000);
	ds24.Refresh();
}
