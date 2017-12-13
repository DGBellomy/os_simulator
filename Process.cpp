/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Process implementation file.
 */

#include "Process.h"

Process::Process(int action_value): _start_time(action_value) {
	_total_current_core_time = 0;
	_current_state = Ready;
}


Process::~Process() {
	while (!_action_list.empty()) {
		deleteCurrentAction();
	}
}


void Process::addAction(ActionType action, int action_value) {
	Action* pAction = new Action;
	pAction->time = action_value;
	pAction->actionType = action;

	_action_list.push(pAction);
}


int Process::getTotalCoreTime() {
	return _total_current_core_time;
}


int Process::getStartTime() {
	return _start_time;
}


void Process::setLabel(int label)
{
	_label = label;
}


int Process::getLabel()
{
	return _label;
}


ActionType Process::getCurrentAction() {
	return _action_list.front()->actionType;
}


std::string Process::getCurrentActionString() {
	if (!_action_list.empty())
	{
		ActionType current_action = _action_list.front()->actionType;

		if (current_action == CORE)
			return "CORE";
		else if (current_action == DISK)
			return "DISK";
		else if (current_action == END)
			return "END";
		else
			return "IO";
	}
	else
	{
		return "TERMINATED";
	}
}


State Process::getCurrentState()
{
	return _current_state;
}


std::string Process::getCurrentStateString()
{
	if (_current_state == Busy)
	{
		return "WAITING";
	}
	else if (_current_state == Ready)
	{
		return "READY";
	}
	else if (_current_state == Running)
	{
		return "RUNNING";
	}
	else // _current_state == Terminated
	{
		return "TERMINATED";
	}
}


void Process::setCurrentState(State state)
{
	_current_state = state;
}


int Process::getCurrentActionTime() {
	return _action_list.front()->time;
}


void Process::updateCurrentCoreTime(int update) {
	_total_current_core_time += update;
}


void Process::deleteCurrentAction() {
	Action* temp = _action_list.front();
	_action_list.pop();
	delete temp;
}
