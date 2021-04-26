//    Final Project COMP 310
//    Your Name: Daisong Pan
//    Your McGill ID:  260783611
//
//    DISK_driver_problem2.h
//
# define MAX_CLOSEDFILES_EXAM 20

struct SAVEDFILE{
	char *filename;
	char str[80];
} savedfile[MAX_CLOSEDFILES_EXAM];

int close_helper(int id, int aft);