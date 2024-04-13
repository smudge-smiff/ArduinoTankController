#ifndef threadConnectorStruct_H_
#define threadConnectorStruct_H_
    struct ibusRXStruct{
        uint16_t channels[14];
    };
    extern ibusRXStruct ibusRX;

    struct attitudeStruct {
        int16_t pitch;
        int16_t pitchRate;
        int16_t roll;
        int16_t rollRate;
        int16_t yaw;
        int16_t yawRate;
        int16_t lateralAcceleration;
        int16_t longitudinalAcceleration;
        int16_t verticalAcceleration;
        unsigned long lastUpdate;
    };
    extern attitudeStruct attitude;

    struct altitudeStruct {
        double altitude;
        double pressure;
        double pressureSeaLevel;
        double Temperature;
        unsigned long lastUpdate;
    };
    extern altitudeStruct altitude;
    /*
    struct gpsStruct {

    }
    extern gpsStruct gps;*/
#endif