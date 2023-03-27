#include "bmp280.h"

unsigned char rx_data[32] = {0};
unsigned char tx_data[32] = {0};
typedef struct
{
	uint16_t dig_T1;
  int16_t  dig_T2;
  int16_t  dig_T3;

  uint16_t dig_P1;
  int16_t  dig_P2;
  int16_t  dig_P3;
  int16_t  dig_P4;
  int16_t  dig_P5;
  int16_t  dig_P6;
  int16_t  dig_P7;
  int16_t  dig_P8;
  int16_t  dig_P9;

  uint8_t  dig_H1;
  int16_t  dig_H2;
  uint8_t  dig_H3;
  int16_t  dig_H4;
  int16_t  dig_H5;
  int8_t   dig_H6;
}
bmp280_calib_data;
		
static bmp280_calib_data bmp280_calib; 
long t_fine;
enum
{
	BMP280_REGISTER_DIG_T1 = 0x88,
  BMP280_REGISTER_DIG_T2 = 0x8A,
  BMP280_REGISTER_DIG_T3 = 0x8C,
	BMP280_REGISTER_DIG_P1 = 0x8E,
	BMP280_REGISTER_DIG_P2 = 0x90,
	BMP280_REGISTER_DIG_P3 = 0x92,
	BMP280_REGISTER_DIG_P4 = 0x94,
  BMP280_REGISTER_DIG_P5 = 0x96,
  BMP280_REGISTER_DIG_P6 = 0x98,
  BMP280_REGISTER_DIG_P7 = 0x9A,
  BMP280_REGISTER_DIG_P8 = 0x9C,
  BMP280_REGISTER_DIG_P9 = 0x9E,
	BMP280_REGISTER_CHIPID = 0xD0,
  BMP280_REGISTER_VERSION = 0xD1,
  BMP280_REGISTER_SOFTRESET = 0xE0,
	BMP280_REGISTER_CAL26 = 0xE1,
	BMP280_REGISTER_CONTROL = 0xF4,
  BMP280_REGISTER_CONFIG = 0xF5,
  BMP280_REGISTER_PRESSUREDATA = 0xF7,
  BMP280_REGISTER_TEMPDATA = 0xFA,
};

uint8_t read8(unsigned char reg)
{
  uint8_t value;
	tx_data[0] = reg;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 2, 0x10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	
	value = rx_data[1];
  return value;
}

uint16_t read16(unsigned char reg)
{
  uint16_t value;
	tx_data[0] = reg;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 3, 0x10);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);	
	value = (rx_data[1]<<8) + rx_data[2];
  return value;
}

uint16_t read16_LE(unsigned char reg) 
{
  uint16_t temp = read16(reg);
  return (temp >> 8) | (temp << 8);
}

int16_t readS16(unsigned char reg)
{
  return (int16_t)read16(reg);
}

int16_t readS16_LE(unsigned char reg)
{
  return (int16_t)read16_LE(reg);
}

void BMP280_Init()
{
	tx_data[0] = 0xD0;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 2, 0x10);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);		
	HAL_Delay(100);
		
  bmp280_calib.dig_T1 = read16_LE(BMP280_REGISTER_DIG_T1);
  bmp280_calib.dig_T2 = readS16_LE(BMP280_REGISTER_DIG_T2);
  bmp280_calib.dig_T3 = readS16_LE(BMP280_REGISTER_DIG_T3);

  bmp280_calib.dig_P1 = read16_LE(BMP280_REGISTER_DIG_P1);
  bmp280_calib.dig_P2 = readS16_LE(BMP280_REGISTER_DIG_P2);
  bmp280_calib.dig_P3 = readS16_LE(BMP280_REGISTER_DIG_P3);
  bmp280_calib.dig_P4 = readS16_LE(BMP280_REGISTER_DIG_P4);
  bmp280_calib.dig_P5 = readS16_LE(BMP280_REGISTER_DIG_P5);
  bmp280_calib.dig_P6 = readS16_LE(BMP280_REGISTER_DIG_P6);
  bmp280_calib.dig_P7 = readS16_LE(BMP280_REGISTER_DIG_P7);
  bmp280_calib.dig_P8 = readS16_LE(BMP280_REGISTER_DIG_P8);
  bmp280_calib.dig_P9 = readS16_LE(BMP280_REGISTER_DIG_P9);
		
	tx_data[0] = 0x74;
	tx_data[1] = 0xff;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 2, 0x10);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

float BMP280_GetTemperature(void)
{
  int32_t var1, var2;
  
  int32_t adc_T = read16(BMP280_REGISTER_TEMPDATA);
  adc_T <<= 8;
  adc_T |= read8(BMP280_REGISTER_TEMPDATA+2);
  adc_T >>= 4;

  var1  = ((((adc_T>>3) - ((int32_t)bmp280_calib.dig_T1 <<1))) * 
	   ((int32_t)bmp280_calib.dig_T2)) >> 11;

  var2  = (((((adc_T>>4) - ((int32_t)bmp280_calib.dig_T1)) * 
	     ((adc_T>>4) - ((int32_t)bmp280_calib.dig_T1))) >> 12) * 
	   ((int32_t)bmp280_calib.dig_T3)) >> 14;

  t_fine = var1 + var2;

  float T  = (t_fine * 5 + 128) >> 8;
  return T/100;
}

float BMP280_GetPressure(void)
{
  int64_t var1, var2, p;
  
  int32_t adc_P = read16(BMP280_REGISTER_PRESSUREDATA);
  adc_P <<= 8;
  adc_P |= read8(BMP280_REGISTER_PRESSUREDATA+2);
  adc_P >>= 4;

  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)bmp280_calib.dig_P6;
  var2 = var2 + ((var1*(int64_t)bmp280_calib.dig_P5)<<17);
  var2 = var2 + (((int64_t)bmp280_calib.dig_P4)<<35);
  var1 = ((var1 * var1 * (int64_t)bmp280_calib.dig_P3)>>8) +
    ((var1 * (int64_t)bmp280_calib.dig_P2)<<12);
  var1 = (((((int64_t)1)<<47)+var1))*((int64_t)bmp280_calib.dig_P1)>>33;
 
  if (var1 == 0) {
    return 0;
  }
  p = 1048576 - adc_P;
  p = (((p<<31) - var2)*3125) / var1;
  var1 = (((int64_t)bmp280_calib.dig_P9) * (p>>13) * (p>>13)) >> 25;
  var2 = (((int64_t)bmp280_calib.dig_P8) * p) >> 19;

  p = ((p + var1 + var2) >> 8) + (((int64_t)bmp280_calib.dig_P7)<<4);
  return (float)p/256;
}