#include <Arduino.h>
#include <Wire.h>
#include <config/peripheralConfig.h>
#include <tools/debugConfig.h>
#include "i2cScanner.h"
i2cScanner i2scan;
void setup() {
  pinMode(ON_BOARD_LED, OUTPUT);
  gpsSerial.begin(57600);
  DEBUG_INIT()
  CONFIGURE_I2C()
  Wire.begin();
  Serial.println("i2c scan");
  i2scan.scan();

}
void loop(){
  DEBUG("DEBUG");
  digitalWrite(ON_BOARD_LED, HIGH);
  delay(250);
  digitalWrite(ON_BOARD_LED, LOW);
  delay(250);
}
/*
void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
 
  delay(5000);           // wait 5 seconds for next scan
}
*/