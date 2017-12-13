/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		This structure was created to hold information of each line in the text file.
 *		I did this to separate the reading of the file from the creating of the processes.
 *		This is an intermediate step place holder.
 */

#ifndef ProcessDescription_H
#define ProcessDescription_H

#include <string>

struct ProcessDescription
{
	std::string action;
	int action_value;
};

#endif
