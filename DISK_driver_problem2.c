//    Final Project COMP 310
//    Your Name:Daisong Pan
//    Your McGill ID: 260783611
//
//    You need to fill in this file for the second problem
//

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"
#include "DISK_driver_problem4.h"
#include <string.h>
#include <stdlib.h>

int close_helper(int id, int aft){
	active_file_table[aft] = NULL;
	active_file_table_owners[aft] = -1;
	
	openedfile[id].filename = NULL;
	openedfile[id].cellID = -1;
	openedfile[id].fatID = -1;
	strcpy(openedfile[id].str, "");
	openedfile[id].occupy = 2;
	//free(buffer);
	return 0;
}