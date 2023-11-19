#include <ibus.h>
#include <stdint.h>
#include <STM32FreeRTOS.h>
#include <threadConnectorStruct.h>
#include <threadConnectorMutex.h>
#include <tools/debugConfig.h>
int IBUS::update()
{
    readBuffer();
    processChannels();
    return 1;
}
int IBUS::readBuffer()
{
    if (_ibusRX->available() >= 32)
    {
        if (_ibusRX->read() == 0x20)
        {
            uint8_t i;
            for (i = 1; i < 32; i++)
            {
                buffer[i] = _ibusRX->read();
            }
            return 1;
        } else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

int IBUS::processChannels()
{
    xSemaphoreTake(ibusVarMutex, portMAX_DELAY);
;   for (int channel_index = 0, byte_position = 2; channel_index < 14; channel_index++, byte_position += 2)
    {
        uint16_t ch = buffer[byte_position + 1] << 8 | buffer[byte_position];
        ibusRX.channels[channel_index] =ch;
    }
    //varDEBUG(ibusRX.channels[2]);
    //DEBUG("IBUS THREAD");
    xSemaphoreGive(ibusVarMutex);
    return 1;
}

