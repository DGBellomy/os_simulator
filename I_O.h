/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		IO holds a vector of Processes.
 */

#ifndef IO_H
#define IO_H

#include <vector>

#include "Process.h"

class I_O
{
private:
	std::vector<Process*> _IO_list;
	std::vector<float> _end_times;

public:
	I_O();
	~I_O();

	void addProcess(Process* process, float startTime);
	Process* checkIO(float current_time);
};

#endif
