//    Final Project COMP 310
//    Your Name: Daisong Pan
//    Your McGill ID: 260783611
//
//    DISK_driver_problem1.h
//


# define MAX_OPENFILES_EXAM 20
# define MAX_BLOCKS 10

struct OPENEDFILE{
	char *filename;
	int cellID;
	int fatID;
	char str[80];
	int occupy;
	int offset;
}openedfile[MAX_OPENFILES_EXAM];


void initOpenedFile();
int openFileExam(char *name, int id);
int addToOpen(char *name, int id, int FAT);
int write_helper(char *parsedCommand[]);
char* read_helper(int id);