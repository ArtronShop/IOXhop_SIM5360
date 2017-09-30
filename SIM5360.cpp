/* File              : SIM5360.cpp
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_CPP__
#define SIM5360_CPP__

#include "SIM5360.h"

void SIM5360::begin(int speed) {
  GSMSerial->begin(speed);
}

bool SIM5360::SendCMD(String cmd, bool newLine = true, int timeout = 0) {
  clsBuffer();

  if (newLine) GSMSerial->println(cmd);
  else GSMSerial->print(cmd);
  String ros = readString(0, timeout, cmd);
  return ros.indexOf(cmd) >= 0;
}

String SIM5360::readString(int len = 0, int timeout = 0, String find = "") {
  int timeout_local = (timeout == 0 ? timeOut : timeout);
  long lastPut = millis();
  String bufString = "";
  while ((millis() - lastPut) <= timeout_local) {
    if (GSMSerial->available() > 0) {
      bufString += (char)GSMSerial->read();
	  // Serial.println(bufString);
      if ((len != 0 && len == bufString.length()) || (find.length() > 0 && bufString.indexOf(find) >= 0)) break;
      lastPut = millis();
    } else {
		// Serial.println(millis() - lastPut);
		delay(10);
	}
  }

  // Serial.println("[SIM] " + bufString);
  return bufString;
}

bool SIM5360::findOK(int timeout = 1000) {
  String ros = readString(0, timeout, "\r\nOK\r\n");
  return ros.indexOf("\r\nOK\r\n") >= 0;
}

void SIM5360::clsBuffer() {
  while (GSMSerial->available() > 0) GSMSerial->read();
}

String SIM5360::getError() {
	return _error_msg;
}

#endif