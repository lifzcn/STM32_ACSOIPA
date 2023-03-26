#include "addheat.h"

void addHeat()
{
	HAL_GPIO_WritePin(HeatingPlate_GPIO_Port, HeatingPlate_Pin, GPIO_PIN_SET);
}
