/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Processor holds a vector of Cores and manages them.
 */

#ifndef Processor_H
#define Processor_H

#include <vector>

#include "Core.h"

class Processor
{
private:
	std::vector<Core*> _cores;

public:
	Processor(int numOfCores);
	~Processor();

	void storeInEmptyCore(Process* process, float startTime);
	bool hasEmptyCore();
	Process* checkCores(float current_time);
	int numOfBusyCores();
};

#endif
