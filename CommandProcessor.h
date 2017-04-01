/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: CommandProcessor.h
 * Assignment Number: 1
 * Date Due: Jan 31, 2016
 * 
 *  Created on: Feb 1, 2015
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 *
 * About this file:
 * this file provides an interface to handle the core functionality of all of the commands the filesystem supports
 ***************************************************************/

#ifndef LINUXFS_P1_COMMANDPROCESSOR_H_
#define LINUXFS_P1_COMMANDPROCESSOR_H_

#include "BinaryTree.h" //used to access the TreeP data type in BinaryTree.h
#include <stdio.h>


#define MAX_ARG_LEN 100 //max # of chars of any given command argument

/**
 * /sets the max size of a command based on the MAX_ARG_LEN. The +6 comes from:
 * +2 for each of the 3 args to include space or newline chars;
 */
#define MAX_CMD_LEN MAX_ARG_LEN*3 + 6

#define TRUE 1
#define FALSE 0


typedef struct Command *CommandP;
typedef struct Command
{
	char *args[3];
	int argCount; // number of arguments in the current command.
}Command;//, *CommandP;


typedef struct Info
{
	char name[MAX_ARG_LEN+1];
	char type;
}Info, *InfoP;


/* these are all utility functions */
/**
 * listArgs
 * lists the arguments of the current command
 * @param {CommandP} command - the command to list the arguments of
 */
void listArgs(CommandP command); //lists all the args of the current command


/**
 * newCommand()
 * makes a new Command struct and returns a pointer do it.
 * This is used to store command args.
 * @return CommandP a pointer to the new command struct
 */
CommandP newCommand();


/**
 * newInfo()
 * makes a new Info struct and returns a pointer do it.
 * This is used to store file/folder info.
 * @return InfoP a pointer to the new info struct
 */
InfoP newInfo();


/**
 * getCommand
 * takes command input from the user, processes and stores the
 * command args in arg1, arg2, and arg3 in the CommandP passed.
 * @param {CommandP} command - the command to store the user's command in
 * @return CommandP the command with user data
 */
CommandP getCommand(CommandP command);


/**
 * takes command input from commands.txt, processes and stores the
 * command args in arg1, arg2, and arg3 in the CommandP passed.
 * @param {CommandP} command - the command to store the user's command in
 * @param {FILE *} inFile - the file pointer from which to read commands from
 * @return CommandP the command with user data
 */
CommandP readCommand(CommandP command, FILE *inFile);



/**
 * processCommand
 * Processes the CommandP passed and calls the appropriate functions to handle it.
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 * @param {FILE *} inFile - the file pointer from which commands might be read. Needs this in case it needs to be closed.
 */
void processCommand(CommandP command, TreeP tree, FILE *inFile);



/** Functions:
	ls              // lists all files and directories in the current directory, indicating which (file or directory) it is
	mkdir <dirname> // creates a new directory if it does not already exist
	cd <dirname>    // changes into specified directory if it exists
	cd ..           // changes to the parent directory
	pwd             // specifies the current directory as: <yourname>/root/nextdir/etc/
	addf <filename> // adds a file to the current directory
	mv <fname1> <fname2> // change the name of the file or directory to the new name
	cp <fname1> <fname2> // copy file or folder to the new name
	rm <filename>   // locate and remove the file or directory
	bye             // ends the session
	whereis <filename>   // show path to first occurrence of file or directory if it exists
 */

/**
 * ls
 * lists all files and directories in the current directory, indicating which (file or directory) it is
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void ls(CommandP command, TreeP tree);

/**
 * mkdir
 * creates a new directory if it does not already exist
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void mkdir(CommandP command, TreeP tree);

/**
 * cd
 * changes into specified directory if it exists or the parent directory
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void cd(CommandP command, TreeP tree);

/**
 * pwd
 * specifies the current directory as: <yourname>/root/nextdir/etc/
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void pwd(CommandP command, TreeP tree);

/**
 * addf
 * adds a file to the current directory
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void addf(CommandP command, TreeP tree);

/**
 * mv
 * change the name of the file or directory to the new name
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void mv(CommandP command, TreeP tree);

/**
 * cp
 * copy file or folder to the new name
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void cp(CommandP command, TreeP tree);

/**
 * rm
 * locate and remove the file or directory
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void rm(CommandP command, TreeP tree);

/**
 * whereis
 * show path to first occurrence of file or directory if it exists
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void whereis(CommandP command, TreeP tree);

/**
 * bye
 * exits the program and closes the input file
 * @param {FILE *} inFile - the input file to close
 */
void bye(FILE *inFile);










#endif /* LINUXFS_P1_COMMANDPROCESSOR_H_ */
