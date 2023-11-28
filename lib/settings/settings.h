#ifndef Settings_h
#define Settings_h

struct packed_settings {
    uint16_t power_cycle;
    uint16_t b;
};
typedef union
{
  packed_settings settings;
  uint8_t bytes[sizeof(settings)];
} test;

#endif