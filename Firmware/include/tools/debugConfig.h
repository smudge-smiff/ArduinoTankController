#ifndef debugConfig_H_
#define debugConfig_H_

#define stringify(x) #x
#define tstr(a) stringify(a)
#ifdef BUILD_DEBUG
    #define DEBUG(x) Serial.println(F(x))
    #define varDEBUG(x) Serial.println(x)
    #define DEBUG_HEX(x) Serial.println(x, HEX);
    #define DEBUG_INIT() Serial.begin(9600); \
                         Serial.dtr(false); \
                         delay(5000); \
                         Serial.print(F("Build Date: ")); \
                         Serial.println(F(__DATE__));  \
                         Serial.print(F("Build Time: ")); \
                         Serial.println(F(__TIME__)); \
                         Serial.print(F("Build Version: ")); \
                         Serial.println(F(tstr(VERSION))); \
                         Serial.print(F("Build for CPU: ")); \
                         Serial.println(F(tstr(CPU))); \
                         Serial.println(F("boop"));
#else
    #define DEBUG(x)
    #define DEBUG_INIT()
#endif

#endif