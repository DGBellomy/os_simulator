/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Core holds a single Process.
 */

#ifndef Core_H
#define Core_H

#include "Process.h"

class Core
{
private:
	Process* _current_process;
	float _process_endTime;

public:
	Core();
	~Core();

	void addProcess(Process* process, float startTime);
	Process* processReady(float current_time);
	bool empty();
	void endProcess();
};

#endif
