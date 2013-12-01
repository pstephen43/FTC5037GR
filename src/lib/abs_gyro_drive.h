/**
*
*  @file abs_gyro_drive.h
*
*  @brief handles the speed control for the motors based on the gyro
*
*  @param speed tells the robot how fast to go
*
*  @param dir Tells the robot what direction to go
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_GYRO_DRIVE_H
#define ABS_GYRO_DRIVE_H

/** macros */


//=======================================
// gyro drive
//=======================================
void abs_gyro_drive(int speed,e_drive_direction dir)
{
	int error = drive_heading - relHeading;

	if(dir == FORWARD)
	{
		motor[left_motor] = speed + (error*g_GYRO_ADJUST);
		motor[right_motor] = speed - (error*g_GYRO_ADJUST);
	}
	else
	{
		motor[left_motor] = -(abs(speed) + (error*g_GYRO_ADJUST));
		motor[right_motor] = -(abs(speed) - (error*g_GYRO_ADJUST));
	}
}
#endif /* !ABS_GYRO_DRIVE_H */
