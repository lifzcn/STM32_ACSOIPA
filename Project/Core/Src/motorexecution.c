#include "motorexecution.h"

void MotorExecution()
{
	StepMotor_Start(2 * 3.14, 0);
	StepMotor_Stop();
}
