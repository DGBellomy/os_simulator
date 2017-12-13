/*
 * Author:	Devin Garrett Bellomy
 * Course:	COSC 3360
 * ID:		1128654
 * File Description:
 *		Creates an OS object, sets up the OS by reading the redirected file and creating Processes
 *		from the information in the text file, and then runs the OS until all Processes have
 *		terminated.
 */

#include "OS.h"

int main(int argc, char* argv[]) {

	OS op_sys;

	if (!op_sys.setUp())
		return 1;

	op_sys.run();

	return 0;
}
