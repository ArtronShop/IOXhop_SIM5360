/* File              : SIM5360_INTERNET.h
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_INTERNET_H__
#define SIM5360_INTERNET_H__

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SIM5360.h"

class SIM5360_INTERNET: public SIM5360 {
  public:
	SIM5360_INTERNET(SIM5360* obj) : MainObj(obj) { }

    bool AutoAPN(String Operator) ;
    void SetAPN(String APN, String Username, String Password) ;
    bool start() ;
    bool stop() ;

  private:
    String _APN_NAME, _APN_USERNAME, _APN_PASSWORD;
	SIM5360* MainObj;

}
;

#endif
