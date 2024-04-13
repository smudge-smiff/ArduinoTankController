#include <Arduino.h>
#include <config/peripheralConfig.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <tools/debugConfig.h>
#include <TinyGPSPlus.h>

void position_task(void* args)
{
    TinyGPSPlus gps;
    HardwareSerial gpsSerial(UART2_RX, UART2_TX);
    gpsSerial.begin(57600);
    int8_t i =1;
    long start = millis();
    for(;;)
	{
        while(gpsSerial.available() > 0){
            //Serial.write(gpsSerial.read());
            //Serial.println(gpsSerial.readStringUntil('\n'));
            if(gps.encode(gpsSerial.read())){
                if (gps.location.isValid())
                {
                    Serial.print(gps.location.lat(), 6);
                    Serial.print(F(","));
                    Serial.print(gps.location.lng(), 6);
                    Serial.print(F(","));
                    Serial.print(gps.location.age());
                    Serial.print(F(","));
                    Serial.print(gps.altitude.meters());
                    Serial.print(F(","));
                    Serial.println(gps.failedChecksum());
                }
            }
        }
        //bool isGNGGAFound = false;
        //isGNGGAFound=gpsSerial.find("GNGGA");
        //if(isGNGGAFound){
        //    Serial.print("found");
        //    Serial.print(" , ");
        //    Serial.println(millis()-start);
        //}
        //while(numBytes > 0){
            
           // for (n = 0; n < numBytes; n++) {
           //     inputBuffer[n] = Serial.read();
           // }

            //Serial.write(gpsSerial.read());
            /*if(gps.encode(gpsSerial.read())){
                if (gps.location.isValid())
                {
                    Serial.print(gps.location.lat(), 6);
                    Serial.print(F(","));
                    Serial.print(gps.location.lng(), 6);
                    Serial.print(F(","));
                    Serial.print(gps.location.age());
                    Serial.print(F(","));
                    Serial.println(gps.failedChecksum());
                }
            }*/
        //}
        
        vTaskDelay(25 / portTICK_PERIOD_MS);
	}
}

/*
void position_task(void* args)
{
    //RF24 radio(PB0, PA4);
    //const byte address[6] = "00001";
    //radio.begin();
    //radio.setPALevel(RF24_PA_MAX);
    HardwareSerial gpsSerial(UART2_RX, UART2_TX);
    gpsSerial.begin(57600);
    int8_t i =1;
    for(;;)
	{
		//while(gpsSerial.available() > 0){
        //    Serial.write(gpsSerial.read());
        //}
        radio.openWritingPipe(address);
  
        //Set module as transmitter
        radio.stopListening();
        
        //const char text[] = "Hello World";
        radio.write(&i, sizeof(i));
        Serial.println("sent");
        delay(1000);
        i++;
        if(i>100){
            i=0;
        }
	}
}
*/