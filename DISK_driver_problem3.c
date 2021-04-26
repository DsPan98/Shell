//    Final Project COMP 310
//    Your Name: Daisong Pan	
//    Your McGill ID: 260783611
//
//    You need to fill in this file for the third problem
//

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"
#include "DISK_driver_problem3.h"

#include <string.h>
int seek_helper(int id, int offset){
	if(offset + openedfile[id].offset >= strlen(openedfile[id].str)){
		printf("ERROR: Out of bounds. Stopped at end of file.");
		openedfile[id].offset = strlen(openedfile[id].str) - 1;
		return 2;
	}
	else if(offset + openedfile[id].offset < 0){
		printf("ERROR: Out of bounds. Stopped at start of file.");
		openedfile[id].offset = 0;
		return 2;
	}
	openedfile[id].offset += offset;
	return 0;
}