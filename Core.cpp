/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Core class implementation.
 */

#include "Core.h"



Core::Core()
{
	_current_process = 0;
	_process_endTime = 0;
}


Core::~Core()
{
}



void Core::addProcess(Process* process, float startTime)
{
	process->setCurrentState(Running);
	_process_endTime = startTime + process->getCurrentActionTime();
	process->updateCurrentCoreTime(process->getCurrentActionTime());
	_current_process = process;
}


Process* Core::processReady(float current_time)
{
	if (_process_endTime <= current_time && _current_process)
	{
		Process* temp = _current_process;
		endProcess();
		temp->deleteCurrentAction();
		return temp;
	}
	else
		return 0;
}


bool Core::empty()
{
	return (!_current_process);
}


void Core::endProcess()
{
	_current_process = 0;
}
