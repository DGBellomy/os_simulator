/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Disk holds a single Process.
 */

#ifndef Disk_H
#define Disk_H

#include "Process.h"

class Disk
{
private:
	Process* _current_process;
	float _end_time;

public:
	Disk();
	~Disk();

	void addProcess(Process* process, float current_time);
	Process* checkDisk(float current_time);
	bool empty();
};

#endif
