/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		IO implementation file.
 */

#include "I_O.h"



I_O::I_O()
{
}


I_O::~I_O()
{
}



void I_O::addProcess(Process* process, float startTime)
{
	float end_time = startTime + process->getCurrentActionTime();
	_end_times.push_back(end_time);

	_IO_list.push_back(process);
	process->deleteCurrentAction();
}


Process* I_O::checkIO(float current_time)
{
	for (size_t i = 0; i < _end_times.size(); i++)
	{
		if (_end_times[i] <= current_time)
		{
			Process* temp = _IO_list[i];
			_IO_list.erase(_IO_list.begin() + i);
			_end_times.erase(_end_times.begin() + i);
			return temp;
		}
	}

	return 0;
}
