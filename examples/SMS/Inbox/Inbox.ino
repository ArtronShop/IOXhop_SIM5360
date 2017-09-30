/* File              : Inbox.ino
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
  
  Serial.print("Read SMS Inbox");
  int count = sms.length(); // Raad count SMS in inbox
  if (count == -1) {
    Serial.println("Error: " + sim.getError());
    return;
  }
  Serial.println("Inbox count is " + String(count));
  for (int index = 0; index < count; index++) { // Read all sms in inbox
    if (!sms.read(index)) {
      Serial.println("Error: " + sim.getError());
      continue;
    }

    Serial.println("--------------------");
    Serial.println("From: " + sms.phone());
    Serial.println("Date: " + sms.date());
    Serial.println(".:: Message ::.\r\n" + sms.message());
    Serial.println("--------------------");

    // Delete SMS
    if (!sms.remove(index)) {
      Serial.println("Error delete: " + sim.getError());
    }
  }
}

void loop() {
  
}
