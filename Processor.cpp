/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Processor implementation file.
 */

#include "Processor.h"



Processor::Processor(int numOfCores)
{
	for (int i = 0; i < numOfCores; i++)
	{
		Core* tempCore = new Core();
		_cores.push_back(tempCore);
	}
}


Processor::~Processor()
{
}



void Processor::storeInEmptyCore(Process* process, float startTime)
{
	for (size_t i = 0; i < _cores.size(); i++)
	{
		if (_cores[i]->empty())
		{
			_cores[i]->addProcess(process, startTime);
			return;
		}
	}
}


bool Processor::hasEmptyCore()
{
	for (size_t i = 0; i < _cores.size(); i++)
	{
		if (_cores[i]->empty()) return true;
	}

	return false;
}


Process* Processor::checkCores(float current_time)
{
	Process* temp;
	
	for (size_t i = 0; i < _cores.size(); i++)
	{
		if ((temp = _cores[i]->processReady(current_time))) {
			return temp;
		}
	}

	return 0;
}


int Processor::numOfBusyCores()
{
	int busyCores = 0;

	for (size_t i = 0; i < _cores.size(); i++)
	{
		if (!_cores[i]->empty()) busyCores++;
	}

	return busyCores;
}
