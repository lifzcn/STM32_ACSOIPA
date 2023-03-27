#ifndef __BMP280_H__
#define __BMP280_H__

#include "stm32f1xx_hal.h"
#include "main.h"
#include "spi.h"

uint8_t read8(unsigned char reg);
uint16_t read16(unsigned char reg);
uint16_t read16_LE(unsigned char reg);
int16_t readS16_LE(unsigned char reg);
void BMP280_Init();
float BMP280_GetTemperature(void);
float BMP280_GetPressure(void);

#endif
