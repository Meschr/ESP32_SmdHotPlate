#include "MAX6675.h"
#include "SpiBusHandler.h"

#include "esp_log.h"
#include "driver/gpio.h"

#include <cmath>

static const char* TAG = "MAX6675";

MAX6675::MAX6675(int pinNumCs)
{
    spi_device_interface_config_t spi_device_cfg = {
        .command_bits = 0,
        .address_bits = 0,
        .mode = 0,
        .cs_ena_pretrans = 1,
        .clock_speed_hz = 1000000,
        .spics_io_num = pinNumCs,
        .queue_size = 7
    };
    CSpiBusHandler::GetInstance()->AddDevice(spi_device_cfg, mSpiDeviceHdl);
    ESP_LOGI(TAG, "Added to SPI-Bus");
}

double MAX6675::ReadTemperatureCelcius()
{
    spi_transaction_t cmd;
    cmd.length = 16;
    cmd.cmd = 0x00;
    cmd.tx_buffer = NULL;
    cmd.rxlength = 16;
    cmd.flags = SPI_TRANS_USE_RXDATA;
    spi_device_transmit(mSpiDeviceHdl, &cmd);

    uint16_t databuf = SPI_SWAP_DATA_RX(*(uint16_t*)cmd.rx_data,16);
    
    if(databuf & 0x40)
    {
        ESP_LOGE(TAG,"No MAX6675 connected.");
        return NAN;
    }
    databuf >>=3;
    double temp = databuf*0.25;

    ESP_LOGI(TAG,"read Temperatur: %f",temp);
    return temp;
}

double MAX6675::ReadTemperatureKelvin()
{
    return CelsiusToKelvin(ReadTemperatureCelcius());
}

double MAX6675::ReadTemperatureFahrenheit()
{
    return CelsiusToFahrenheit(ReadTemperatureCelcius());
}

double MAX6675::CelsiusToKelvin(const double celsius) 
{
	return (celsius + 273.15);
}

double MAX6675::CelsiusToFahrenheit(const double celsius)
{
	return (celsius * 1.8 + 32);
}