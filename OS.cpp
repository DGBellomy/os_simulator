/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		OS implementation file.
 */

#include "OS.h"

OS::OS()
{
	_total_processes = 0;
	_terminated_processing_time = 0;
	_clock = 0;
	_processor = 0;
	_IO = 0;
	_disk = 0;
}


OS::~OS()
{
	if (_processor) {
		delete _processor;
		_processor = 0;
	}

	while (!_processes.empty()) {
		delete _processes.front();
		_processes.pop();
	}

	while (!_HQ.empty()) {
		delete _HQ.front();
		_HQ.pop();
	}

	while (!_LQ.empty()) {
		delete _LQ.front();
		_LQ.pop();
	}

	while (!_DQ.empty()) {
		delete _DQ.front();
		_DQ.pop();
	}
}


bool OS::setUp()
{
	_processor = new Processor(2);
	_clock = new Clock;
	_IO = new I_O;
	_disk = new Disk;

	std::vector<ProcessDescription> process_description_list;

	if (!_readInput(process_description_list))
		return false;

	_createProcesses(_processes, _ALL_PROCESSES, process_description_list);

	_total_processes = _processes.size();

	_placeLabels();

	return true;
}


void OS::run()
{
	while (!_endOfProcesses())
	{
		_clock->updateClock();

		_pushNewProcessesToHQ();

		_checkForEmptyCores();

		_checkCoreProcesses();

		_checkForEmptyDisk();

		_checkIOProcesses();

		_checkDiskProcess();
	}
}









bool OS::_readInput(std::vector<ProcessDescription>& process_list)
{
	bool core_next = false;
	bool start_next = true;
	bool other_next = false;

	while (std::cin) {
		char temp[128];
		ProcessDescription current_process;

		std::cin >> temp;
		current_process.action = temp;

		if (current_process.action == "START")
		{
            		if (start_next)
            		{
                		std::cin >> current_process.action_value;
                		start_next = false;
                		core_next = true;
            		}
            		else return false;
		}
        	else if (current_process.action == "I/O" || current_process.action == "DISK")
        	{
            		if (other_next)
            		{
                		std::cin >> current_process.action_value;
                		other_next = false;
                		core_next = true;
            		}
            		else return false;
        	}
        	else if (current_process.action == "CORE")
        	{
            		if (core_next)
            		{
                		std::cin >> current_process.action_value;
                		core_next = false;
                		other_next = true;
            		}
            		else return false;
        	}
		else if (current_process.action == "END")
		{
            		if (other_next)
            		{
                		current_process.action_value = -1;
                		other_next = false;
                		start_next = true;
            		}
            		else continue;
		}

		else continue;

		process_list.push_back(current_process);
	}

	return true;
}


void OS::_createProcesses(std::queue<Process*>& processes, std::vector<Process*>& all_processes, std::vector<ProcessDescription>& pd)
{
	Process* newProcess = 0;

	for (size_t i = 0; i < pd.size(); i++)
	{
		if (pd[i].action == "START")
		{
			newProcess = new Process(pd[i].action_value);
		}
		else if (pd[i].action == "I/O")
		{
			newProcess->addAction(IO, pd[i].action_value);
		}
		else if (pd[i].action == "DISK")
		{
			newProcess->addAction(DISK, pd[i].action_value);
		}
		else if (pd[i].action == "CORE")
		{
			newProcess->addAction(CORE, pd[i].action_value);
		}
		else // action == "END"
		{
			newProcess->addAction(END, pd[i].action_value);
			processes.push(newProcess);
			all_processes.push_back(newProcess);
			newProcess = 0;
		}
	}
}


int OS::_totalProcessingTime()
{
	int total = 0;

	for (size_t i = 0; i < _ALL_PROCESSES.size(); i++)
	{
		total += _ALL_PROCESSES[i]->getTotalCoreTime();
	}

	total += _terminated_processing_time;

	return total;
}


void OS::_placeLabels()
{
	for (size_t i = 0; i < _ALL_PROCESSES.size(); i++)
	{
		_ALL_PROCESSES[i]->setLabel(i);
	}
}


void OS::_removeTerminated()
{
	for (size_t i = 0; i < _ALL_PROCESSES.size(); i++)
	{
		if (_ALL_PROCESSES[i]->getCurrentState() == Terminated)
		{
			_terminated_processing_time += _ALL_PROCESSES[i]->getTotalCoreTime();
			delete _ALL_PROCESSES[i];
			_ALL_PROCESSES.erase(_ALL_PROCESSES.begin() + i);
		}
	}
}


bool OS::_endOfProcesses()
{
	return (_terminated.size() == _total_processes);
}










void OS::_pushNewProcessesToHQ()
{
	if (!_processes.empty())
	{
		if (_processes.front()->getStartTime() <= _clock->getTime())
		{
			_HQ.push(_processes.front());
			_processes.pop();
			_HQ.front()->setCurrentState(Ready);
		}
	}
}


void OS::_checkForEmptyCores()
{
	if (!_HQ.empty())
	{
		if (_processor->hasEmptyCore())
		{
			_processor->storeInEmptyCore(_HQ.front(), _clock->getTime());
			_HQ.pop();
		}
	}
	else if (!_LQ.empty())
	{
		if (_processor->hasEmptyCore())
		{
			_processor->storeInEmptyCore(_LQ.front(), _clock->getTime());
			_LQ.pop();
		}
	}
}


void OS::_checkCoreProcesses()
{
	if (Process* temp = _processor->checkCores(_clock->getTime()))
	{
		temp->setCurrentState(Busy);
		if (temp->getCurrentAction() == DISK)
		{
			_DQ.push(temp);
		}
		else if (temp->getCurrentAction() == IO)
		{
			_IO->addProcess(temp, _clock->getTime());
		}
		else if (temp->getCurrentAction() == CORE)
		{
			temp->setCurrentState(Ready);
			_HQ.push(temp);
		}
		else // END
		{
			temp->setCurrentState(Terminated);
			temp->deleteCurrentAction();
			_terminated.push(temp);
			_checkForEmptyCores();
			_print();
		}
	}
}


void OS::_checkForEmptyDisk()
{
	if (!_DQ.empty())
	{
		if (_disk->empty())
		{
			_disk->addProcess(_DQ.front(), _clock->getTime());
			_DQ.pop();
		}
	}
}


void OS::_checkIOProcesses()
{
	if (Process* temp = _IO->checkIO(_clock->getTime()))
	{
		temp->setCurrentState(Ready);
		_HQ.push(temp);
	}
}


void OS::_checkDiskProcess()
{
	if (Process* temp = _disk->checkDisk(_clock->getTime()))
	{
		temp->setCurrentState(Ready);
		_LQ.push(temp);
	}
}








void OS::_print()
{
	_printCurrentTime();
	_printNumOfBusyCores();
	_printAvgOfBusyCores();
	_printQueue("HIGH-PRIORITY READY QUEUE:", _HQ);
	_printQueue("LOW-PRIORITY READY QUEUE:", _LQ);
	_printQueue("DISK QUEUE:", _DQ);
	_printProcessTable();
	_removeTerminated();
	std::cout << std::endl << std::endl;
}




void OS::_printCurrentTime()
{
	std::cout << "CURRENT STATE OF THE SYSTEM AT TIME " << _clock->getTime() << ":" << std::endl;
}


void OS::_printNumOfBusyCores()
{
	std::cout << "Current number of busy Cores: " << _processor->numOfBusyCores() << std::endl;
}


void OS::_printAvgOfBusyCores()
{
	float avg = (float)_totalProcessingTime() / (float)_clock->getTime();
	if (avg > 2) avg = 2;
	std::cout << "Average number of busy Cores: " << avg << std::endl;
}


void OS::_printQueue(std::string title, std::queue<Process*> qList)
{
	std::cout << title << std::endl;
	size_t end = qList.size();

	if (qList.size() == 0)
		std::cout << "empty" << std::endl;
	else
		for (size_t i = 0; i < end; i++)
		{
			std::cout << "Process " << qList.front()->getLabel() << std::endl;
			qList.pop();
		}
}


void OS::_printProcessTable()
{
	std::cout << "PROCESS TABLE:" << std::endl;

	for (size_t i = 0; i < _ALL_PROCESSES.size(); i++)
	{
		std::cout
			<< "Process " << i << " started at " << _ALL_PROCESSES[i]->getStartTime()
			<< ", got " << _ALL_PROCESSES[i]->getTotalCoreTime() << " ms of CORE time and is "
			<< _ALL_PROCESSES[i]->getCurrentStateString() << std::endl;
	}
}
