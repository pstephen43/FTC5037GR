/**
*
*  @file abs_initialize.h
*
*  @brief A header file that handles the initialization when we start the game
*
*  @param None n/a
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/

#ifndef ABS_INITIALIZE_H
#define ABS_INITIALIZE_H

#include "abs_screen.h"
#include "abs_gyro_wrapper.h"
#include "abs_sensors.h"
#include "abs_datalog.h"
#include "abs_log.h"
#include "abs_reset_angle_sensor.h"
#include "abs_calibrate_light.h"
#include "abs_selection_program.h"
#include "abs_control_light_sensor.h"

void abs_initialize()
{
	StartTask(abs_screen);
	disableDiagnosticsDisplay();
	servoChangeRate[abdd] = 3;
	servo[roger_slide] = 127;
	servo[abdd] = g_abdd_down;
	servo[grabber_left] = GRABBER_LEFT_CLOSE;
	servo[grabber_right] = GRABBER_RIGHT_CLOSE;
	servo[light_sensor] = LIGHT_SERVO_UP;
	abs_control_light_sensor(INACTIVE);
	memset(g_input_array,0,INPUT_ARRAY_SIZE);
	abs_selection_program();
	PlaySoundFile("! Click.rso");
	//g_drift = abs_gyro_cal(g_gyro_cal_time);
	g_drift = abs_gyro_wrapper();

	if(!HTACreadAllAxes(HTAC, g_x_axis, g_y_axis, g_z_axis))
	{
		g_error = ERR_ACCELERMOETER;
		g_error_type = ERROR_NONLETHAL;
	}
	if(g_gyro_noise>10)
	{
		g_error = ERR_GYRO_CAL;
		g_error = ERROR_LETHAL;
	}
	if(HTSMUXreadPowerStatus(SENSOR_MUX))
	{
		g_error = ERR_SENSOR_MUX;
		g_error_type = ERROR_NONLETHAL;
	}
	if(HTSMUXreadPowerStatus(GYRO_MUX))
	{
		g_error = ERR_GYRO_MUX;
		g_error = ERROR_LETHAL;
	}

	if(g_error != 0)
	{
		g_screen_state = S_ERROR;
		while(true)
		{
			g_gyro_true = true;
			PlayTone (250,25);
			wait1Msec(500);
			if(nNxtButtonPressed == kEnterButton && g_error_type == ERROR_NONLETHAL)break;
		}
	}
	LogData=true;
	g_screen_state = S_READY;
	StartTask(abs_sensors);
	abs_reset_angle_sensor_val(HARD_RESET);

	PlayTone(700, 100);

#if WAIT == 0
	waitForStart();

#else
while(nNxtButtonPressed == kEnterButton){}
if(nNxtButtonPressed != kEnterButton) wait1Msec(5000);
#endif

	abs_log(__FILE__ ,"auto start",nPgmTime,0,0,0);

	StartTask(abs_datalog);
	eraseDisplay();
	g_start_time = nPgmTime;
	g_screen_state = S_DELAY_WAIT;
	dl_change_event = true;
	dl_ce_detail = dl_ce_start_delay;
	dl_speed = g_start_delay*1000;
	wait1Msec(g_start_delay*1000);
	eraseDisplay();
	g_screen_state = S_GYRO_SHOW;
}

#endif /* !ABS_INITIALIZE_H */
