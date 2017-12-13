/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		OS manages active Processes and keeps track of information about all running processes
 *		as well as managing where they go and when.
 */

#ifndef OS_H
#define OS_H

#include <iostream>
#include <fstream>
#include <queue>

#include "ProcessDescription.h"
#include "Process.h"
#include "Processor.h"
#include "I_O.h"
#include "Disk.h"
#include "Clock.h"

class OS
{
private:
	size_t _total_processes;
	Clock* _clock;
	int _terminated_processing_time;

	Processor* _processor;
	I_O* _IO;
	Disk* _disk;

	std::queue<Process*> _processes;
	std::vector<Process*> _ALL_PROCESSES;

	std::queue<Process*> _HQ;
	std::queue<Process*> _LQ;
	std::queue<Process*> _DQ;

	std::queue<Process*> _terminated;

private:
	bool _readInput(std::vector<ProcessDescription>& process_list);
	void _createProcesses(std::queue<Process*>& processes, std::vector<Process*>& all_processes, std::vector<ProcessDescription>& pd);
	int _totalProcessingTime();
	void _placeLabels();
	void _removeTerminated();
	bool _endOfProcesses();

private:
	void _pushNewProcessesToHQ();
	void _checkForEmptyCores();
	void _checkCoreProcesses();
	void _checkForEmptyDisk();
	void _checkIOProcesses();
	void _checkDiskProcess();

private:
	void _print();
	void _printCurrentTime();
	void _printNumOfBusyCores();
	void _printAvgOfBusyCores();
	void _printQueue(std::string title, std::queue<Process*> qList);
	void _printProcessTable();

public:
	OS();
	~OS();
	
	bool setUp();
	void run();
};

#endif
