/**
*
*  @file abs_s1_mission_execute.h
*
*  @brief runs the missions from the starting point S1
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_S1_MISSION_EXECUTE_H
#define ABS_S1_MISSION_EXECUTE_H

#include "abs_drive.h"
#include "abs_turn.h"
#include "abs_stop_robot.h"
#include "abs_end_ramp.h"
#include "abs_log.h"
#include "abs_get_angle_sensor_val.h"

void abs_s1_mission_execute()
{
	switch(g_mission_number)
	{
	case 0:		//test option only used for tests, currently angle sensor
		g_screen_state = S_ANGLE_SHOW;
		abs_drive(FORWARD, E_ANGLE, 600, 50, true, g_drive_type);
		break;

	case 1:	//IR mission
		dist_record=true;			//set to record the following movement for end movement distance
		g_screen_state = S_ANGLE_SHOW;
		abs_drive(FORWARD, E_IR_DETECT, FORWARD_IR_THRESHOLD, 40, true, g_drive_type);
		if(abs_get_angle_sensor_val(RELATIVE_BPU) < 38)		//if robot did not drive minimal distance drive to first crate
		{
			dist_record = true;
			abs_drive(FORWARD, E_ANGLE, 40 - abs_get_angle_sensor_val(RELATIVE_BPU), 40, true, g_drive_type);
		}
		break;

	case 2:	//deliver to crate 4 mission
		dist_record=true;
		abs_drive(FORWARD, E_ANGLE, 150, 50, true, g_drive_type);
		break;

	case 3://deliver to crate 3 mission
		dist_record=true;
		abs_drive(FORWARD, E_ANGLE, 125, 50, true, g_drive_type);
		break;

	case 4:	//deliver to crate 2 mission
		dist_record=true;
		abs_drive(FORWARD, E_ANGLE, 75, 50, true, g_drive_type);
		break;

	case 5:	//deliver to crate 1 mission
		dist_record=true;
		abs_drive(FORWARD, E_ANGLE, 50, 50, true, g_drive_type);
		break;

	case 6:	//test option to read the gyro, will be defence mission 1
		g_screen_state = S_SMOKE_RUN2;
		motor[right_motor] = 0;
		motor[left_motor] = 0;
		while(true)
		{
			g_sensor_value = g_rel_heading;
			g_sensor_value2 = g_rel_heading2;
		}
		break;

	case 7: //will be defence mission 2
		g_screen_state = S_SMOKE_RUN2;
		motor[right_motor] = 0;
		motor[left_motor] = 0;
		while(true)
		{
			g_sensor_value = abs_get_angle_sensor_val(RELATIVE_ASU);
			g_sensor_value2 = abs_get_angle_sensor_val(RELATIVE_BPU);
		}
		break;
	}
	abs_log(__FILE__,"abdd up",2,g_abdd_up,0,0);	//open and log abdd
	servo[abdd] = g_abdd_up;
	StartTask (abs_calibrate_light);	//calibrate the light sensor to find the white line
	wait1Msec(2000);
	servoChangeRate[abdd] = abdd_down_speed;
	servo[abdd] = g_abdd_down;	//return and log the abdd
	abs_log(__FILE__,"abdd down",2,g_abdd_down,0,0);

	wait1Msec(g_end_delay * DELAY_MULTIPLICATION_FACTOR); //wait for end delay, number option tab 4

	abs_log(__FILE__,"start of end",g_end_point,0,0,0);
}

#endif /* !ABS_S1_MISSION_EXICUTE_H */
