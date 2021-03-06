#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S2,     IROne,          sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"
#include "hitechnic-irseeker-v2.h"

task main()
{
	servo[servo1] = 255;
	servo[servo2] = 0;
	wait1Msec(10);
	servoChangeRate[servo1] = 5;
	servoChangeRate[servo2] = 5;
	waitForStart();
	time1[T1] =0;
	while(SensorValue[IROne] != 5 && time1[T1] < 5000)
	{
		motor[motorD] = 100;
		motor[motorE] = 100;
		wait1Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	wait1Msec(1);
	servo[servo1] = 0;
	servo[servo2] = 255;
	wait1Msec(100);
}
