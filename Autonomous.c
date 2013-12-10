#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  none)
#pragma config(Sensor, S2,     IROne,          sensorI2CCustom)
#pragma config(Sensor, S3,     IRTwo,          sensorI2CCustom)
#pragma config(Sensor, S4,     lightSensor,    sensorLightActive)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//
// RoboSeek.c - This program uses the HiTechnic IR Seeker V2
// sensor to follow an IR source. This program requires the
// HTIRS2-driver.h driver provided with RobotC.


#include "JoystickDriver.c"
#include "hitechnic-irseeker-v2.h"
bool foundIR;

void initializeRobot()
{
	servo[servo1] = 255;
	servo[servo2] = 0;
	wait1Msec(10);
}

void score()
{
	servoChangeRate[servo1] = 20;
	servoChangeRate[servo2] = 20;
	servo[servo1] = 0;
	servo[servo2] = 255;
	wait1Msec(2000);
	servo[servo1] = 255;
	servo[servo2] = 0;
	wait1Msec(2000);
}

void turnHalfLeft()
{
	int ticks = 1031;
	motor[motorD] = -35;
	motor[motorE] = 35;
	nMotorEncoder[motorE] = 0;
	while(nMotorEncoder[motorE] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
}

void turnTinyLeft()
{
	int ticks = 50;
	motor[motorD] = -35;
	motor[motorE] = 35;
	nMotorEncoder[motorE] = 0;
	while(nMotorEncoder[motorE] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
}

void turnHalfRight()
{
	int ticks = 1325;
	motor[motorD] = 50;
	motor[motorE] = -50;
	nMotorEncoder[motorD] = 0;
	while(nMotorEncoder[motorD] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
}

void turnLeft()
{
	int ticks = 1875;
	motor[motorD] = -50;
	motor[motorE] = 50;
	nMotorEncoder[motorE] = 0;
	while(nMotorEncoder[motorE] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	wait1Msec(1);
}

void turnRight()
{
	int ticks = 1975;
	motor[motorD] = 35;
	motor[motorE] = -35;
	nMotorEncoder[motorD] = 0;
	while(nMotorEncoder[motorD] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	wait1Msec(1);
}

int getIrReading(tSensors irReceiverPin)
{
	// IRLED 38 kHz for at least 2 ms
	wait1Msec(1);                              // Wait 1 ms
	int ir = SensorValue[irReceiverPin];       // IR receiver -> ir variable
	wait1Msec(1);                              // Down time before recheck
	return ir;
}

void detectedIR()
{
	int count = 1;
	while (count < 5)
	{
		if (getIrReading(IROne) == 5 || getIrReading(IRTwo) == 5) //5 is most likely the number that I will be using, though it may be different
			//Is called a zone
		{
			//there is something within the threshold range
			foundIR = true;
		}
		else
		{
			//nothing in the threshold range
			count++;
		}
	}
	foundIR = false;
}

void placeAutonomousBlock()
{
	int ticks = 287;// 4.5 inches	//have ticks set for the distance from the first crate
	motor[motorD] = 35;
	motor[motorE] = 35;
	nMotorEncoder[motorD] = 0;
	while(nMotorEncoder[motorD] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	turnHalfRight();
	ticks = 0;	//have ticks set for the distance to park in front of first crate
	motor[motorD] = 35;
	motor[motorE] = 35;
	nMotorEncoder[motorD] = 0;
	while(nMotorEncoder[motorD] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	int count = 0;
	while(!foundIR && count < 4)
	{
		ticks = 917; // 10 inches //have ticks set for the distance between the bins
		motor[motorD] = 35;
		motor[motorE] = 35;
		nMotorEncoder[motorD] = 0;
		while(nMotorEncoder[motorD] < ticks)
		{
			wait10Msec(1);
		}
		motor[motorD] = 0;
		motor[motorE] = 0;
		count++;
		ticks = 0; //Middle distance
	}
	turnRight();
	ticks = 0; //have ticks set for the distance from the robot to the bins
	motor[motorD] = 35;
	motor[motorE] = 35;
	nMotorEncoder[motorD] = 0;
	while(nMotorEncoder[motorD] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	//servo[] = ; //has the servo drop the block
	//servo[] = ;
}

void reposition()
{
	int ticks = 0; //same as the ticks that are just above
	motor[motorD] = -35;
	motor[motorE] = -35;
	nMotorEncoder[motorD] = 0;
	while(nMotorEncoder[motorD] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	turnRight();
}

//void detectLine()
//{
//				Timer[T1] = 0;
//  	  	while(Timer[T1] < 10000)                           // Infinite loop
//   			{
//     			 if(SensorValue(lightSensor) < 45)  // If the Light Sensor reads a value less than 45:
//   			   {
//  			      motor[motorD] = 0;
//  			      motor[motorE] = 0;
//  			      wait10Msec(1);
//   			   }
//   			   else                               // If the Light Sensor reads a value greater than or equal to 45:
//    			  {
//    			  	motor[motorD] = 35;
//    			  	motor[motorE] = 35;
//    			  	wait10Msec(1);
//     			  }
//  			}
//have the robot detect the first line of white tape (not worth trying to block an enemy robot by going to their side of
//the field, because at this point it is likely they are already there, and that would only mess with us
//}

void climbRamp()
{
	int ticks = 0; //distance from first crate to when the robot should make the first halfLeftTurn(); - distanceTraveled
	motor[motorD] = 35;
	motor[motorE] = -35;
	nMotorEncoder[motorD] = 0;
	while(nMotorEncoder[motorD] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	turnHalfLeft();
	ticks = 0; //ticks are set to the distance until the next half turn
	turnHalfLeft();
	//  			detectLine();
}
void turnCircle()
{
	turnLeft();
	wait1Msec(2000);
	turnLeft();
	wait1Msec(2000);
	turnLeft();
	wait1Msec(2000);
	turnLeft();
}

void move(int leftPower, int rightPower, int ticks)
{
	motor[motorD] = leftPower;//15
	motor[motorE] = rightPower;//15
	nMotorEncoder[motorD] = 0;
	while(nMotorEncoder[motorD] < ticks)
	{
		wait10Msec(1);
	}
	motor[motorD] = 0;
	motor[motorE] = 0;
	wait1Msec(1000);
}

// main task
task main()
{
	//initializeRobot();
	//wait1Msec(3000);
	//waitForStart();

	//get off the wall
	move(15,15,750);
	//set parrallel to baskets
	turnHalfRight();
	wait1Msec(1000);
	//score basket 1
	move(15,26,650);
	score();
	//score bastket 2
	move(15,26,1000);
	score();
	//score basket 3
	move(15,26,2150);
	score();
	//score basket 4
	move(15,26,1000);
	score();
	//move past last basket
	move(15,15,2250);
	//turn towards ramp
	turnLeft();
	wait1Msec(1000);
	//line up with ramp
	move(15,15,4000);
	//turn to line up with ramp
	turnLeft();
	wait1Msec(1000);
	//move up ramp
	move(45,50,4000);
	//nxtDisplayCenteredBigTextLine(6, "Sig=%d", SensorValue[lightSensor]);
}
//http://www.hitechnic.com/cgi-bin/commerce.cgi?preadd=action&key=SPR2010
//
