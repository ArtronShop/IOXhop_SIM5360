/* File              : SIM5360_SMS.h  
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#ifndef SIM5360_SMS_H__
#define SIM5360_SMS_H__

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "SIM5360.h"

class SIM5360_SMS {
  public:
    SIM5360_SMS(SIM5360* obj) : MainObj(obj) { }

	bool begin() ;
    bool send(String phone_number, String msg) ;

    int length() ;
    bool read(int index) ;
	bool remove(int index) ;
	
    String phone() {
      return _from;
    }
    String date() {
      return _date;
    }
    String message() {
      return _msg;
    }

  private:
    String _from, _date, _msg;
	bool _isBegin = false;
	SIM5360* MainObj;

}
;

#endif
