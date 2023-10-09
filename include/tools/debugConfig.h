#ifndef debugConfig_H_
#define debugConfig_H_

#define stringify(x) #x
#define tstr(a) stringify(a)
#ifdef BUILD_DEBUG
    #define DEBUG(x) Serial.println(x)
    #define DEBUG_INIT() Serial.begin(9600); \
                         Serial.dtr(false); \
                         delay(5000); \
                         Serial.print("Build Date: "); \
                         Serial.println(__DATE__);  \
                         Serial.print("Build Time: "); \
                         Serial.println(__TIME__); \
                         Serial.print("Build Version: "); \
                         Serial.println(tstr(VERSION)); \
                         Serial.print("Build for CPU: "); \
                         Serial.println(tstr(CPU)); \
                         Serial.println("boop");
#else
    #define DEBUG(x)
    #define DEBUG_INIT()
#endif

#endif