/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Clock keeps track of time in milliseconds.
 */

#ifndef Clock_H
#define Clock_H

#include <ctime>

class Clock
{
private:
	float _current_time;
	float _ticks_per_milsec;
	clock_t _clock;
	clock_t _ticks;

public:
	Clock();
	~Clock();

	void setClock();
	int getTime();
	void updateClock();
};

#endif
