/* File              : Send_SMS.ino
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */
   
#include <SoftwareSerial.h>
#include "SIM5360.h"
#include "SIM5360_GENERAL.h"
#include "SIM5360_SMS.h"

SIM5360 sim(new SoftwareSerial(7, 8));
SIM5360_GENERAL gen(&sim);
SIM5360_SMS sms(&sim);

void setup() {
  Serial.begin(9600);
  sim.begin(9600);

  // Power ON
  Serial.println("Power on module");
  gen.power_on(true); // wait module ready

  Serial.println("Start use SMS");
  sms.begin();
  
  Serial.print("Send SMS..... ");
  bool ros = sms.send("084107977x", "Hello, send from SIM5360"); // phone number, message
  if (ros) {
    Serial.println("OK");
  } else {
    Serial.println("Fail!");
  }

  // Power OFF
  Serial.println("Power off module");
  gen.power_off();
}

void loop() {
  
}
