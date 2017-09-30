/* File              : SIM5360_GENERAL.h
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_GENERAL_H__
#define SIM5360_GENERAL_H__

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SIM5360.h"

class SIM5360_GENERAL {
  public:
    SIM5360_GENERAL(SIM5360* obj) : MainObj(obj) { }
	
	bool power_on(bool wait_ready = true, int pin = 9) ;
	bool power_off(int timeout = 1000, int pin = 9) ;
	bool test() ;
	String imei() ;
	
  private:
	SIM5360* MainObj;

}
;

#endif
