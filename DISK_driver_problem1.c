//    Final Project COMP 310
//    Your Name: Daisong Pan
//    Your McGill ID: 260783611
//
//    You need to fill in this file for the first problem
//

#include "DISK_driver.h"
#include "DISK_driver_problem1.h"
#include "interpreter.h"

#include <string.h>
#include <stdlib.h>

#include "DISK_driver_problem2.h"

# define MAX_OPENEDFILES 20
# define MAX_BLOCKS 10

void initOpenedFile(){
	for (int i = 0; i < MAX_OPENEDFILES; i++){
		struct OPENEDFILE bf = openedfile[i];
		bf.filename = NULL;
		bf.cellID = -1;
		bf.fatID = -1;
		strcpy(bf.str, "");
		bf.occupy = 0;
		bf.offset = 0;
	}
	for (int j = 0; j < MAX_CLOSEDFILES_EXAM; j++){
		struct SAVEDFILE bf2 = savedfile[j];
		bf2.filename = NULL;
		strcpy(bf2.str, "");
	}
}
/*
non-negative index: FAT index
-1 failed to open file
-2 cell index number in use
*/
int openFileExam(char *name, int id){
	// version from openfile, with addition of cell id
	
	// Checking if there is a free block in the data section to create a new file
	if(currentPartition.last_free_block > currentPartition.total_blocks)
		return -3;
	
	// Lookup on the FAT
	int FATindex = 0;
	for (; FATindex < MAX_FILES; FATindex++)
		if (fat[FATindex].filename == NULL || strcmp(fat[FATindex].filename, name) == 0)
		break;
	
	//2. check if cell is taken
	if (active_file_table_owners[id] == FATindex){
		return FATindex;
	}
	else if(active_file_table_owners[id] != -1){
		//meaning the cell is taken
		printf("ERROR: Index number in use.");
		return -2;
	}
	//3. cell not taken, fat not added
	active_file_table[id]  = fopen(filename, "r+");
	active_file_table_owners[id] = FATindex;
	
	if(FATindex == MAX_FILES && fat[MAX_FILES -1].filename != NULL){
		// File DNE on the FAT and FAT is full
		fclose(active_file_table[id]);
		active_file_table[id] = NULL;
		active_file_table_owners[id] = -1;
		return -1;
	}
	else if(fat[FATindex].filename == NULL){
		// Make a new file
		fat[FATindex].filename = malloc(sizeof(500));
		strcpy(fat[FATindex].filename, name);
		fat[FATindex].current_location = 0;
		fat[FATindex].file_length = 0;
	}
	else{
		fat[FATindex].current_location = 0;
	}
	return FATindex;
}
// -1: no more space available 
int addToOpen(char *name, int id, int FAT){
	int i = 0;
	for (; i < MAX_OPENFILES_EXAM; i++){
		if(openedfile[i].filename == NULL || (openedfile[i].filename == name && openedfile[i].cellID == id)){
			break;
		}
	}
	if(i >= MAX_OPENFILES_EXAM){
		printf("ERROR, not enough space.");
		return -1;
	}
	int openedBefore = openedfile[i].occupy;
	openedfile[i].filename = name;
	openedfile[i].cellID = id;	
	openedfile[i].fatID = FAT;
	openedfile[i].occupy = 1;
	
	
	/*------------*/
	if(openedBefore == 2){
		int k = 0;
		int bool = 0;
		for (; k < MAX_CLOSEDFILES_EXAM; k++){
			bool = 0;
			if(savedfile[k].filename != NULL){
				for (int m = 0; m < strlen(name); m++){
					if( savedfile[k].filename[m] != name[m]){
						bool = 1;
					}
				}
				if(bool == 0){
					break;
				}
			}
			/*
			if(savedfile[k].filename == name){
				break;
			}*/
		}
		strcpy(openedfile[i].str, savedfile[k].str);
		
	}
	/*------------*/
	return 0;
}

int write_helper(char *parsedCommand[]){
	char str[80] = "";
	for (int i = 2; i < 100;i++){
		if(parsedCommand[i] == NULL){
			break;
		}
		strcat(str, parsedCommand[i]);
		strcat(str, " ");
	}
	int fileID = atoi(parsedCommand[1]);
	int j = 0;
	for (; j < MAX_OPENFILES_EXAM; j++){
		if(openedfile[j].cellID == fileID){
			strcpy(openedfile[j].str, str);
			break;
		}
	}
	if (j >= MAX_OPENFILES_EXAM){
		printf("ERROR, file does not exist.");
		return -1;
	}
	

	int k = 0;
	for(; k < MAX_CLOSEDFILES_EXAM;k++){
		if(savedfile[k].filename == openedfile[j].filename || savedfile[k].filename == NULL){
			break;
		}
	}
	if (k >= MAX_CLOSEDFILES_EXAM){
		printf("ERROR, unknown error");
		return -1;
	}
	
	
	savedfile[k].filename = openedfile[j].filename;
	strcpy(savedfile[k].str, openedfile[j].str);
	return j;	
}

/*
char* read_helper(int id){
	char *str = malloc(100);
	strcat(str, openedfile[id].str);
	return str;
}*/

char* read_helper(int id){
	char *str = malloc(100);
	strcat(str, &openedfile[id].str[openedfile[id].offset]);
	openedfile[id].offset = strlen(openedfile[id].str) -4;
	return str;
}