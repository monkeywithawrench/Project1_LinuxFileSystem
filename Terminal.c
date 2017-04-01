/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: Terminal.c
 * Assignment Number: 
 * Date Due: Jan 31, 2016
 * 
 *  Created on: Feb 1, 2015
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 *
 * About this file:
 * this file is merely responsible for calling a few functions to set up the program and repeatedly call to get input
 ***************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryTree.h"
#include "CommandProcessor.h"


/**
 * main
 * The main function of the entire program. Literally does nothing.
 * @return int returns an integer exit code.
 */
int main()
{
	TreeP tree = newTree();
	CommandP command = newCommand();
	InfoP info = newInfo();
	setInfo(tree->curDir, info);
	strcpy(info->name, "root");
	FILE *inFile = fopen("commands.txt","r");
	if( inFile == NULL )
	{
		fprintf(stderr, "file \"commands.txt\" could not be open!!! Program exiting!\n");
		return(0);
	}

	fprintf(stdout, "Welcome, user.\n");

	while(1)
	{
		//command= getCommand(command);
		command= readCommand(command, inFile);
		processCommand(command, tree, inFile);
	}

	fclose(inFile); //note: infile may be closed before this point by CommandProcessor
	return(0);
}
