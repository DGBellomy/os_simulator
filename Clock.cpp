/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Clock class implementation file.
 */

#include "Clock.h"



Clock::Clock()
{
	_ticks_per_milsec = CLOCKS_PER_SEC / 1000;
	_current_time = 0;
	setClock();
}


Clock::~Clock()
{
}



void Clock::setClock()
{
	_clock = clock();
}


int Clock::getTime()
{
	return _current_time;
}


void Clock::updateClock()
{
	_ticks = clock() - _clock;
	_current_time += (float)_ticks / _ticks_per_milsec;
	setClock();
}
