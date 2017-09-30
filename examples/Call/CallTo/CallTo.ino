/* File              : CallTo.ino
   Codeing By IOXhop : www.ioxhop.com
   Sonthaya Nongnuch : www.fb.me/maxthai */

#include <SoftwareSerial.h>
#include "SIM5360.h"
#include "SIM5360_GENERAL.h"
#include "SIM5360_CALL.h"

SIM5360 sim(new SoftwareSerial(7, 8));
SIM5360_GENERAL gen(&sim);
SIM5360_CALL call(&sim);

String phone_number = "084107977x";

void setup() {
  Serial.begin(9600);
  sim.begin(9600);

  // Power ON
  Serial.println("Power on module");
  gen.power_on(true); // wait module ready

  Serial.println("Start call to " + phone_number);
  call.call(phone_number); // Call to ...
  delay(30000); // wait 30S
  call.hangUp(); // Hang up
  Serial.println("end call to " + phone_number);
}

void loop() {
  
}
