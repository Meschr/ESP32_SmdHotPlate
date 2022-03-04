#ifndef _MAX6675_hf
#define _MAX6675_hf

#include "driver/spi_master.h"

class MAX6675
{
public:
    MAX6675(int pinNumCs);
    double ReadTemperatureCelcius(void);
    double ReadKelvin(void);
    double ReadFahrenheit(void);

private:
    spi_device_handle_t mSpiDeviceHdl;

    double CelsiusToKelvin(const double celsius);
    double CelsiusToFahrenheit(const double celsius);
};

#endif // ifndef _MAX6675_hf