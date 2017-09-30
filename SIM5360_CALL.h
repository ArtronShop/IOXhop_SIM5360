/* File              : SIM5360_CALL.h
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_CALL_H__
#define SIM5360_CALL_H__

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SIM5360.h"

class SIM5360_CALL {
  public:
    SIM5360_CALL(SIM5360* obj) : MainObj(obj) { }
	
	bool call(String phone) ;
	bool answer() ;
	bool hangUp() ;

  private:
	SIM5360* MainObj;

}
;

#endif
