/**
*
*  @file abs_datalog.h
*
*  @brief A function that handels the data log
*
*  @param N/A
*
*  @return Returns nothing
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_DATALOG_H
#define ABS_DATALOG_H

/** macros */

//=======================================
// data log
//=======================================
task abs_datalog()
{
	const string LogFileName = "DATALOG.txt";
	TFileIOResult LogIoResult;
	TFileHandle LogFileHandle;
	long LogFileSize = 36000;
	string sString;
	string CRLF = (char)13+(char)10;

	Delete(LogFileName, LogIoResult);
	OpenWrite(LogFileHandle, LogIoResult, LogFileName, LogFileSize);

	for(int i=1;i<6;i++)//dl_cur_dist
	{
		StringFormat(sString, "%2d\t", g_input_array[i]);
		WriteText(LogFileHandle, LogIoResult, sString);
	}
	StringFormat(sString, "");
	strcat(sString,CRLF);
	WriteText(LogFileHandle, LogIoResult, sString);

	while(!LogData){EndTimeSlice();}
	while(LogData)
	{
		StringFormat(sString, "%4d\t", dl_step);
		WriteText(LogFileHandle, LogIoResult, sString);
		StringFormat(sString, "%4d\t", nPgmTime);
		WriteText(LogFileHandle, LogIoResult, sString);

		switch(dl_robot_action_state)
		{
		case dl_robot_stop:
			StringFormat(sString, "Stop\t");								//robot state name
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "None\t");									//extra detail
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "0\t");											//speed
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "0\t");											//distance
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_rel_heading);		//relitive heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_const_heading);	//constant heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			break;

		case dl_gyro_move:
			if(dl_IR==true) StringFormat(sString, "gyro_move_IR\t");							//robot state name
			else StringFormat(sString, "gyro_move\t");
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, g_datalog_details_names[dl_robot_action_detail]);	//extra detail
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "\t");																						//added the tab (\t)
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_speed);					//speed
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_dist);		    	//distance
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_rel_heading);		//relitive heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_const_heading);	//constant heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_cur_dist);	//current distance value for end triger, could be angle/IR
			WriteText(LogFileHandle, LogIoResult, sString);
			break;

		case dl_gyro_turn:
			StringFormat(sString, "gyro_turn\t");								  	//robot state name
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, g_datalog_details_names[dl_robot_action_detail]);	//extra detail
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "\t");																						//added the tab (\t)
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_speed);					//speed
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_dist);		    	//distance
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_rel_heading);		//relitive heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_const_heading);	//constant heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			break;

		case dl_run_abdd:
			StringFormat(sString, "abdd\t");								  	//robot state name
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, g_datalog_details_names[dl_robot_action_detail]);	//extra detail
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "\t");																						//added the tab (\t)
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_speed);					//speed
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_dist);		    	//distance
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_rel_heading);		//relitive heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_const_heading);	//constant heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			break;

		case dl_wait:
			StringFormat(sString, "wait\t");								  	//robot state name
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, g_datalog_details_names[0]);	//extra detail
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "\t");																						//added the tab (\t)
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_speed);					//speed
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", dl_dist);		    	//distance
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_rel_heading);		//relitive heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, "%4d\t", g_const_heading);	//constant heading for gyro
			WriteText(LogFileHandle, LogIoResult, sString);
			break;
		case dl_change_event:
			switch(dl_robot_action_detail)
			{
			case dl_ce_program_start: StringFormat(sString, "program start\t"); break;
			case dl_ce_start_delay: StringFormat(sString, "start delay\t"); break;
			case dl_ce_end_delay: StringFormat(sString, "end delay\t"); break;
			case dl_ce_score_start: StringFormat(sString, "score\t"); break;
			case dl_ce_end_point: StringFormat(sString, "end point\t"); break;
			}
			WriteText(LogFileHandle, LogIoResult, sString);
			StringFormat(sString, g_datalog_change_event_names[dl_robot_action_detail]);	//extra detail
			WriteText(LogFileHandle, LogIoResult, sString);
			break;
		}
		StringFormat(sString, "");
		strcat(sString,CRLF);
		WriteText(LogFileHandle, LogIoResult, sString);
		wait1Msec(50);									// sample frequency
	}
	Close(LogFileHandle, LogIoResult);		// close the file once we are told to stop
	wait10Msec(20);
}

#endif /* !ABS_DATALOG_H */
