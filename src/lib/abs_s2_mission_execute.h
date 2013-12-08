/**
 *
 *  @file abs_s2_mission_execute.h
 *
 *  @brief runs the missions from the starting point S2
 *
 *  @param None n/a
 *
 *  @return returns nothing
 *
 *  @copyright Copyright 2013, Got Robot? FTC Team 5037
 *
 */
#ifndef ABS_S2_MISSION_EXECUTE_H
#define ABS_S2_MISSION_EXECUTE_H

void abs_s2_mission_execute()
{
	switch(g_mission_number)
	{
	case 0:
		g_screen_state = S_ANGLE_SHOW;
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/600, 50, true);
		break;

	case 1:
		abs_drive(BACKWARD, E_IR_DETECT, 3, 40, true);
		PlayTone(200,20);
		//if(g_IR_angle_dist_complete == true) g_end_point = 12;
		if(g_end_point == 2)
		{
			if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(62*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_forward_crate4_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(100*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_forward_crate3_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(137*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_forward_crate2_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(162*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_forward_crate1_to_turn_dist;
		}
		else if(g_end_point == 3)
		{
			if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(62*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_backwards_crate4_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(100*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_backwards_crate3_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(137*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_backwards_crate2_to_turn_dist;
			else if(abs(HTANGreadAccumulatedAngle(angle_sensor))<(162*INT_ANGLE_SENSOR_CIRCUMFERENCE)) g_to_turn_dist = g_backwards_crate1_to_turn_dist;
		}
		wait1Msec(1000);
		abs_drive(FORWARD, E_ANGLE, /*distance in cm*/6, 50, true);
		wait1Msec(500);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 2:
		if(g_end_point == 3)g_to_turn_dist = g_backwards_crate4_to_turn_dist;
		else g_to_turn_dist = g_forward_crate4_to_turn_dist;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/40, 50, true);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 3:
		if(g_end_point == 3)g_to_turn_dist = g_backwards_crate3_to_turn_dist;
		else g_to_turn_dist = g_forward_crate3_to_turn_dist;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/65, 50, true);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 4:
		if(g_end_point == 3)g_to_turn_dist = g_backwards_crate2_to_turn_dist;
		else g_to_turn_dist = g_forward_crate2_to_turn_dist;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/115, 50, true);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 5:
		if(g_end_point == 3)g_to_turn_dist = g_backwards_crate1_to_turn_dist;
		else g_to_turn_dist = g_forward_crate1_to_turn_dist;
		abs_drive(BACKWARD, E_ANGLE, /*distance in cm*/140, 50, true);
		wait1Msec(2000);
		servo[abdd] = g_abdd_up;
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		break;

	case 6:
		abs_turn(CLOCKWISE, POINT, TURN, 75, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 190, 50, true);
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 75, 60);
		abs_drive(FORWARD, E_ANGLE, 80, 50, true);
		break;

	case 7:
		abs_turn(COUNTERCLOCKWISE, POINT, TURN, 98, 60);
		wait1Msec(200);
		abs_drive(FORWARD, E_ANGLE, 87, 50, true);
		motor[block_lift_motor] = 40;
		motor[block_lift_motor2] = 40;
		abs_turn(CLOCKWISE, POINT, TURN, 103, 60);
		motor[block_lift_motor] = 0;
		motor[block_lift_motor2] = 0;
		abs_drive(FORWARD, E_ANGLE, 80, 50, true);
		break;

	case 140:
		int dist = 30;
		bool done = false;
		while(done == false)
		{
			int ac_start_time = nPgmTime;
			int i = 0;
			while((g_accelermoeter_sensor < dist+5) && (g_accelermoeter_sensor > dist-5) && ((ac_start_time - nPgmTime)<500))
			{
				i++;
				PlayTone(20,20);
				wait1Msec(1);
			}
			if(i > 490) done = true;
			PlayTone(20,20);
		}
		break;
	}
	wait1Msec(g_end_delay*1000);
	switch(g_end_point)
	{
	case 1:
		wait1Msec(2000);
		servo[abdd] = g_abdd_down;
		abs_stop_robot();
		break;
	case 2:
		abs_end_r1(2000,40);
		break;
	case 3:
		abs_end_r2(2000,40);
		break;
	}
}

#endif /* !ABS_S2_MISSION_EXECUTE_H */
