/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Disk implementation file.
 */

#include "Disk.h"



Disk::Disk()
{
	_current_process = 0;
}


Disk::~Disk()
{
}



void Disk::addProcess(Process* process, float current_time)
{
	_end_time = current_time + process->getCurrentActionTime();
	process->deleteCurrentAction();
	_current_process = process;
}


Process* Disk::checkDisk(float current_time)
{
	if (current_time >= _end_time)
	{
		Process* temp = _current_process;
		_current_process = 0;
		return temp;
	}

	return 0;
}


bool Disk::empty()
{
	return (!_current_process);
}
