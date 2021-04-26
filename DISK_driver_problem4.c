//    Final Project COMP 310
//    Your Name:
//    Your McGill ID: 
//
//    You need to fill in this file for the fourth random problem



//	  Fill in the name of the command that you are implementing here 
//    ------------------>COMMAND NAME<-----------------------------

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "DISK_driver_problem2.h"
#include "DISK_driver_problem3.h"
#include "DISK_driver_problem4.h"

#include <string.h>
#include <stdlib.h>



char *pipe_helper(int id, char *var){
	int i = 0;
	for(; i <MAX_OPENFILES_EXAM; i++){
		if ((openedfile[i].cellID == id && id != 0) ||(openedfile[i].cellID == id && openedfile[i].filename != NULL)){
			break;
		}
	}
	if(i >= MAX_OPENFILES_EXAM){
		printf("Error: you have to open the file first.\n");
		return NULL;
	}
	printf("something wrong down here");
	char* forReturn = malloc(100);
	strcat(forReturn, read_helper(i));
	if(forReturn == NULL){
		printf("Error, cannot read file\n");
		return NULL;
	}
	char *buffer = malloc(strlen(forReturn) * 4);
	for(int i = 0; i < strlen(forReturn);i++){
		buffer[i] = forReturn[i];
	}
	
	return forReturn;

}