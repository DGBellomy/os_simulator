/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Process holds a queue of Events (I called Actions) that it is to execute.
 *		It also holds information about itself such as start time, total core time,
 *		and its current state.
 */

#ifndef Process_H
#define Process_H

#include <queue>
#include <string>

enum State { Running, Ready, Busy, Terminated };
enum ActionType { CORE, IO, DISK, END };


struct Action {
	ActionType actionType;
	int time;
};



class Process
{
private:
	int _start_time;
	int _label;
	int _total_current_core_time;
	std::queue<Action*> _action_list;
	State _current_state;

public:
	Process(int action_value);
	~Process();

	void addAction(ActionType action, int action_value);
	int getTotalCoreTime();
	int getStartTime();
	void setLabel(int label);
	int getLabel();
	ActionType getCurrentAction();
	std::string getCurrentActionString();
	State getCurrentState();
	std::string getCurrentStateString();
	void setCurrentState(State state);
	int getCurrentActionTime();
	void updateCurrentCoreTime(int update);
	void deleteCurrentAction();
};

#endif
