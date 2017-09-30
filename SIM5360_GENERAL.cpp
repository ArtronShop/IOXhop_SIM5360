/* File              : SIM5360_GENERAL.cpp
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_GENERAL_CPP__
#define SIM5360_GENERAL_CPP__

#include "SIM5360_GENERAL.h"

bool SIM5360_GENERAL::power_on(bool wait_ready = true, int pin = 9) {
	if (!test()) {
		// Serial.print("Power on module... ");
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
		delay(100);
		digitalWrite(pin, HIGH);
		if (wait_ready) {
			MainObj->clsBuffer();
			String ros = MainObj->readString(0, 10000, "PB DONE");
			MainObj->clsBuffer();
			return ros.indexOf("PB DONE") >= 0;
		}
	}
	return true;
}

bool SIM5360_GENERAL::power_off(int timeout = 1000, int pin = 9) {
	if (test()) {
		digitalWrite(pin, LOW);
		MainObj->SendCMD("AT+CPOF");
		return MainObj->findOK(timeout);
	}
	return true;
}

bool SIM5360_GENERAL::test() {
	MainObj->SendCMD("AT");
	return MainObj->findOK();
}

String SIM5360_GENERAL::imei() {
	MainObj->SendCMD("AT+CGSN");
	MainObj->readString(0, 0, "\r\n");
	String imei = MainObj->readString(0, 0, "\r\n");
	imei = imei.substring(0, imei.length() - 2);
	if (!MainObj->findOK()) return "";
	return imei;
}

#endif