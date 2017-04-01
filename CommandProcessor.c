/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: CommandProcessor.c
 * Assignment Number: 1
 * Date Due: Jan 31, 2016
 * 
 *  Created on: Feb 1, 2015
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 *
 * About this file:
 * this file provides an API to handle the core functionality of all of the commands the filesystem supports
 ***************************************************************/

#include "CommandProcessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "BinaryTree.h" //NOTE: This is included in "CommandProcessor.h"!!!!!
//#include "Commands.h"





//Utilities:
/**
 * doesFileExist
 * Recursively checks the current working directory for conflicting/duplicate file names
 * Returns TRUE if duplicate name is found, FALSE if there is no duplicate file name.
 * @param {char *} name - the name of the file/folder to search for
 * @param {NodeP} node - the first node to check in the directory
 * @return int returns TRUE if file exists, otherwise FALSE
 */
int doesFileExist(char *name, NodeP node);

/**
 * printParents
 * prints out the parent directories of the node passed (prints file location)
 * @params {NodeP} node - the node to print the parents of
 */
void printParents(NodeP node);

/**
 * insertNode
 * inserts the node into the directory, organized alphabetically
 * @params {NodeP} nodeSRC - the node to insert
 * @params {NodeP} nodeFS - specifies the directory to insert source node into
 */
void insertNode(NodeP nodeSRC, NodeP nodeFS);

/**
 * findNode
 * Recursively checks the current working directory for for the node specified
 * Returns NodeP if file/folder is found, NULL if not found
 * @param {char *} name - the name of the file/folder to search for
 * @param {NodeP} node - the first node to check in the directory
 */
NodeP findNode(char *name, NodeP node);

/**
 * clone
 * Recursively clones the node passed as well as all children and returns a pointer to the node
 * @params {NodeP} nodeSRC - the source node to clone
 * @params {TreeP} tree - a pointer to the file system tree
 * @return NodeP the duplicate node with children created
 */
NodeP clone(NodeP nodeSRC, TreeP tree);

/**
 * recursiveFree
 * Recursively frees memory of the node passed, all children, and the info for the node and children
 * @param {NodeP} node - the node free memory of
 * @return NodeP the remains of what was the node pointer. This is always NULL.
 */
NodeP recursiveFree(NodeP node);

/**
 * postOrderSearch
 * performs a post-order traversal of the file system for a file/folder with the name passed
 * @params {NodeP} node - the node to start the search at
 * @params {TreeP} tree - a pointer to the file system tree
 * @param {char *} name - the name of the file/folder to search for
 * @return NodeP the pointer to the first node found with the name specified. NULL if not found.
 */
NodeP postOrderSearch(NodeP node, TreeP tree, char *name);


/**
 * newCommand()
 * makes a new Command struct and returns a pointer do it.
 * This is used to store command args.
 * @return CommandP a pointer to the new command struct
 */
CommandP newCommand()
{
	CommandP command;
	command = /*(CommandP)*/malloc(sizeof(Command));
	if(command == NULL)		//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Command Malloc failed!");
		return(NULL);
	}
	int i = 0;
	while(i<=3) // malloc's the 3 arg string pointers in command->args.
	{
		command->args[i] = /*(char *)*/malloc(sizeof(char)*(MAX_ARG_LEN +1));
		if(command->args[i] == NULL)
		{
			fprintf(stderr, "ERROR! Arg Malloc failed!");
			return(NULL);
		}
		i++;
	}
	return(command);
}



/**
 * newInfo()
 * makes a new Info struct and returns a pointer do it.
 * This is used to store file/folder info.
 * @return InfoP a pointer to the new info struct
 */
InfoP newInfo()
{
	InfoP info = malloc(sizeof(Info));
	if(info == NULL)		//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Info Malloc failed!");
		return(NULL);
	}
	//info->type=0;
	return(info);
}


/**
 * getCommand
 * takes command input from the user, processes and stores the
 * command args in arg1, arg2, and arg3 in the CommandP passed.
 * @param {CommandP} command - the command to store the user's command in
 * @return CommandP the command with user data
 */
CommandP getCommand(CommandP command){
	char string[MAX_CMD_LEN];
	fprintf(stdout,"$ ");
	fgets(string, MAX_CMD_LEN, stdin);//gets command from user
	char *sp;
	if(string[0]=='\n' || string[0]=='\0')
	{
		fprintf(stdout, "Invalid command, please enter a new command.\n");
		return(command);
	}
	//sp = strtok(string, "\n");
	/*
	if(sp[0]=='\n' || sp[0]=='\0')
	{
		fprintf(stdout, "Invalid command, please enter a new command.\n");
		return(command);
	}
	*/
	command->argCount = 0;
	for(sp = strtok(string, " \n"); sp != NULL; sp = strtok(NULL," \n")) //tokenizes the string from the user into args.
	{
		if(command->argCount < 3 ) // stop if max # of args has been reached.
		{
			strcpy(command->args[command->argCount], sp);
			command->argCount++;
		}
	}
	return(command);
}


/**
 * takes command input from commands.txt, processes and stores the
 * command args in arg1, arg2, and arg3 in the CommandP passed.
 * @param {CommandP} command - the command to store the user's command in
 * @param {FILE *} inFile - the file pointer from which to read commands from
 * @return CommandP the command with user data
 */
CommandP readCommand(CommandP command, FILE *inFile){
	char string[MAX_CMD_LEN];
	fprintf(stdout,"$ ");
	if( fgets(string, MAX_CMD_LEN, inFile) == NULL)//gets command from user. Checks for EOF or other error
	{
		fprintf(stderr, "EOF was reached or an error occurred while reading command. User didn't specify bye command.\n");
		fclose(inFile);
		exit(0);
	}
	fprintf(stdout, "%s", string);
	char *sp;
	if(string[0]=='\n' || string[0]=='\0')
	{
		fprintf(stdout, "Invalid command, please enter a new command.\n");
		return(command);
	}
	//sp = strtok(string, "\n");
	/*
	if(sp[0]=='\n' || sp[0]=='\0')
	{
		fprintf(stdout, "Invalid command, please enter a new command.\n");
		return(command);
	}
	*/
	command->argCount = 0;
	for(sp = strtok(string, " \n"); sp != NULL; sp = strtok(NULL," \n")) //tokenizes the string from the user into args.
	{
		if(command->argCount < 3 ) // stop if max # of args has been reached.
		{
			strcpy(command->args[command->argCount], sp);
			command->argCount++;
		}
	}
	return(command);
}





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
 * processCommand
 * Processes the CommandP passed and calls the appropriate functions to handle it.
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 * @param {FILE *} inFile - the file pointer from which commands might be read. Needs this in case it needs to be closed.
 */
void processCommand(CommandP command, TreeP tree, FILE *inFile)
{
	if(!strcmp(command->args[0], "ls"))
		ls(command, tree);

	else if(!strcmp(command->args[0], "mkdir"))
		mkdir(command, tree);

	else if(!strcmp(command->args[0], "cd"))
		cd(command, tree);

	else if(!strcmp(command->args[0], "pwd"))
		pwd(command, tree);

	else if(!strcmp(command->args[0], "addf"))
		addf(command, tree);

	else if(!strcmp(command->args[0], "mv"))
		mv(command, tree);

	else if(!strcmp(command->args[0], "cp"))
		cp(command, tree);

	else if(!strcmp(command->args[0], "rm"))
		rm(command, tree);

	else if(!strcmp(command->args[0], "whereis"))
		whereis(command, tree);

	else if(!strcmp(command->args[0], "bye"))
		bye(inFile);

	else
		fprintf(stdout, "Error, not a valid command.\n");


	return;
}






/**
 * ls
 * lists all files and directories in the current directory, indicating which (file or directory) it is
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void ls(CommandP command, TreeP tree)
{
	//fprintf(stdout, "Command: ls\n");
	if(command->argCount != 1) //ls has no args
	{
		fprintf(stderr, "Invalid number of arguments. ls has no args.\n");
		return;
	}

	NodeP node = getLeft(tree->curDir); //starting node
	while(node != NULL)
	{
		InfoP info = (InfoP)getInfo(node);
		fprintf(stdout, "  %c %s\n", info->type, info->name);
		node = getRight(node);
	}
	//fprintf(stdout,"\n");
	return;
}

/**
 * mkdir
 * creates a new directory if it does not already exist
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void mkdir(CommandP command, TreeP tree)
{
	//fprintf(stdout, "Command: mkdir\n");
	//listArgs(command);
	if(command->argCount != 2) //mkdir has 1 arg
	{
		fprintf(stderr, "Invalid number of arguments. mkdir has 1 arg.\n");
		return;
	}
	if(getLeft(tree->curDir) !=NULL)
		if(doesFileExist(command->args[1], getLeft(tree->curDir)))
		{
			fprintf(stdout, "File or folder already exists with the name passed, no action taken.\n");
			return;
		}
	fprintf(stdout,"%s\n", command->args[1]);

	//if name is valid:
	NodeP node = newNode();
	setParent(node, tree->curDir);
	setLeft(node, NULL);
	setRight(node, NULL);

	InfoP info = newInfo();
	info->type = 'D';
	strcpy(info->name, command->args[1]); //copies the name from the command to the directory node info
	setInfo(node, info);


	if(getLeft(tree->curDir) == NULL) //if directory is empty, no sort needed to insert.
	{
		setLeft(tree->curDir, node);
		return;
	}
	int comp = strcmp( info->name, ( (InfoP)getInfo(getLeft(tree->curDir)) )->name );
	if(comp<0) // this section inserts the new node at the beginning of the directory if it's the lowest.
	{
		NodeP temp = getLeft(tree->curDir);
		setLeft(tree->curDir, node);
		setRight(node, temp);
		return;
	}

	// If both initial insertion attempts failed, then call insert.
	insertNode(node, getLeft(tree->curDir) );

	//fprintf(stdout,"\n");
	return;
}

/**
 * cd
 * changes into specified directory if it exists or the parent directory
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void cd(CommandP command, TreeP tree)
{
	//fprintf(stdout, "Command: cd\n");
	//listArgs(command);
	if(command->argCount != 2) //cd has 1 arg
	{
		fprintf(stderr, "Invalid number of arguments. cd has 1 arg.\n");
		return;
	}

	if(!strcmp(command->args[1], ".."))
	{
		if(getParent(tree->curDir) == NULL)
		{
			command->argCount=1;
			pwd(command, tree);
			return;
		}
		tree->curDir = getParent(tree->curDir);
		command->argCount=1;
		pwd(command, tree);
		return;
	}


	if(getLeft(tree->curDir) == NULL)
	{
		fprintf(stdout, "%s not located in %s\n", command->args[1], ((InfoP)getInfo(tree->curDir))->name);
		return;
	}
	NodeP node = findNode(command->args[1], getLeft(tree->curDir));
	if( node  != NULL && ((((InfoP)getInfo(node))->type) == 'D') )
	{
		tree->curDir = node;
		command->argCount=1;
		pwd(command, tree);
	}
	else
	{
		fprintf(stdout, "%s not located in %s or is a file\n", command->args[1], ((InfoP)getInfo(tree->curDir))->name);
	}

	return;
}

/**
 * pwd
 * specifies the current directory as: <yourname>/root/nextdir/etc/
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void pwd(CommandP command, TreeP tree)
{
	//fprintf(stdout, "Command: pwd\n");
	//listArgs(command);
	if(command->argCount != 1) //pwd has 0 args
	{
		fprintf(stderr, "Invalid number of arguments. pwd has 0 args.\n");
		return;
	}
	fprintf(stdout, "morton/");
	if(getParent(tree->curDir) == NULL)
		fprintf(stdout, "root/");
	else
	{
		//fprintf(stdout, "%s/", ((InfoP)getInfo(tree->curDir))->name);
		printParents(tree->curDir);
	}
	fprintf(stdout,"\n");
	return;
}

/**
 * addf
 * adds a file to the current directory
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void addf(CommandP command, TreeP tree)
{
	//fprintf(stdout, "Command: addf\n");
	//listArgs(command);
	if(command->argCount != 2) //addf has 1 arg
	{
		fprintf(stderr, "Invalid number of arguments. addf has 1 arg.\n");
		return;
	}


	if(getLeft(tree->curDir) !=NULL)
		if(doesFileExist(command->args[1], getLeft(tree->curDir)))
		{
			fprintf(stdout, "File or folder already exists with the name passed, no action taken.\n");
			return;
		}

	//if name is valid:
	NodeP node = newNode();
	setParent(node, tree->curDir);
	setLeft(node, NULL);
	setRight(node, NULL);

	InfoP info = newInfo();
	info->type = 'F';
	strcpy(info->name, command->args[1]); //copies the name from the command to the directory node info
	setInfo(node, info);


	if(getLeft(tree->curDir) == NULL) //if directory is empty, no sort needed to insert.
	{
		setLeft(tree->curDir, node);
		return;
	}
	int comp = strcmp( info->name, ( (InfoP)getInfo(getLeft(tree->curDir)) )->name );
	if(comp<0) // this section inserts the new node at the beginning of the directory if it's the lowest.
	{
		NodeP temp = getLeft(tree->curDir);
		setLeft(tree->curDir, node);
		setRight(node, temp);
		return;
	}

	// If both initial insertion attempts failed, then call insert.
	insertNode(node, getLeft(tree->curDir) );

	//fprintf(stdout,"\n");
	return;
}

/**
 * mv
 * change the name of the file or directory to the new name
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void mv(CommandP command, TreeP tree)
{
	if(command->argCount != 3) //mv has 2 args
	{
		fprintf(stderr, "Invalid number of arguments. mv has 2 args.\n");
		return;
	}


	NodeP node = findNode(command->args[1], getLeft(tree->curDir));
	if( node  != NULL )
	{

		strcpy( ((InfoP)getInfo(node))->name, command->args[2] );
	}
	else
	{
		fprintf(stdout, "%s not found\n", command->args[1]);
	}
	return;
}

/**
 * cp
 * copy file or folder to the new name
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void cp(CommandP command, TreeP tree)
{
	//fprintf(stdout, "Command: cp\n");
	//listArgs(command);
	if(command->argCount != 3) //Check to see if correct number of arguments. cp has 2 args
	{
		fprintf(stderr, "Invalid number of arguments. cp has 2 args.\n");
		return;
	}
	NodeP node = findNode(command->args[1], getLeft(tree->curDir)); //see if node exists
	if(node == NULL)
	{
		fprintf(stderr, "File or folder could not be found\n");
		return;
	}
	//check to see if file. if so, copy is easy.
	InfoP info = getInfo(node);
	if(info->type == 'F')
	{
		strcpy(command->args[1],command->args[2]);
		command->argCount = 2;
		addf(command, tree);
		fprintf(stdout,"\n");
		return;
	}
	//check to see if directory. if so, more work needs to be done.
	else if (info->type == 'D')
	{
		//make a clone function :)
		strcpy(command->args[1],command->args[2]);
		command->argCount = 2;
		mkdir(command, tree); //directory itself has now been copied
		NodeP parent = tree->curDir; //prep work for cloning the files and directories in the directory
		NodeP node2 = findNode(command->args[1], getLeft(tree->curDir)); //confirm that new directory was created
		if(node == NULL)
		{
			fprintf(stdout,"ERROR: Dir not cloned in cp function!\n");
			return;
		}
		tree->curDir = node2;
		//setRight(node2, clone(getRight(node), tree)); //this would be completely unnecessary, would just make a 2nd copy.
		setLeft(node2, clone(getLeft(node), tree) ); //recursively clone files and directories
		tree->curDir = parent; //clean up the pwd
		fprintf(stdout,"\n");
		return;
	}

	fprintf(stdout,"\n");
	return;
}

/**
 * rm
 * locate and remove the file or directory
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void rm(CommandP command, TreeP tree)
{
	//fprintf(stdout, "Command: rm\n");
	//listArgs(command);
	if(command->argCount != 2) //rm has 1 arg. Check proper arg count.
	{
		fprintf(stderr, "Invalid number of arguments. rm has 1 arg.\n");
		return;
	}
	NodeP node = findNode(command->args[1], getLeft(tree->curDir)); //see if the file or folder specified exists
	if(node == NULL)
	{
		fprintf(stderr, "File or folder could not be found\n");
		return;
	}
	NodeP rightNode = getRight(node); //save the right child, we'll need it.
	setRight(node, NULL); //set the right pointer to null so the rest of the nodes in the dir aren't removed
				//when recursiveFree() is run

	// STOP. need to PROPERLY find the previous node in the list next.
	int found = 0; //boolean.

	//gonna try something here. gonna look for the parent node of our target node by comparing pointer addresses!
	NodeP temp = getLeft(tree->curDir); //check to see if first node in directory is null. if so, this was the one deleted
	if(temp == NULL)
	{
		fprintf(stderr, "SOMETHING WENT HORRIBLY WRONG!!!\n");
		return;
	}
	if(temp == node)
	{
		found = 1; //we found it! :D
		setLeft(tree->curDir, rightNode); //we found where node was deleted, now set pointer to tempRight.
	}
	NodeP tempRight;
	while(!found)
	{
		tempRight = getRight(temp);
		if(tempRight == NULL) //given that we got this far in the function(confirming that the node does exist),
				//this should NEVER return true...
		{
			fprintf(stderr, "SOMETHING WENT HORRIBLY WRONG!!! tempRight=NULL!\n");
			return;
		}
		if(tempRight == node) //if true, temp is parent of the target node
		{
			found = 1; //WE FOUND IT!
			setRight(temp, rightNode); //set the right pointer of temp to the right child of the target node.
		}
		else
			temp = tempRight; //go to the next node and try again
	}
	node = recursiveFree(node);//since the above loop ended, we know the files in the parent directory have been prepared
	//fprintf(stdout,"\n");
	return;
}

/**
 * whereis
 * show path to first occurrence of file or directory if it exists
 * @param {CommandP} command - the command to get parsed command from
 * @param {TreeP} tree - a pointer to the file system
 */
void whereis(CommandP command, TreeP tree)
{
	//fprintf(stdout, "Command: whereis\n");
	//listArgs(command);
	if(command->argCount != 2) //whereis has 1 arg
	{
		fprintf(stderr, "Invalid number of arguments. whereis has 1 arg.\n");
		return;
	}
	NodeP node = postOrderSearch(tree->root, tree, command->args[1]);
	if(node == NULL)
	{
		fprintf(stdout, "File or folder could not be found.\n");
		return;
	}
	fprintf(stdout, "morton/");
	printParents(getParent(node));
	fprintf(stdout, "%s", ((InfoP)getInfo(node))->name);
	fprintf(stdout,"\n");
	return;
}

/**
 * bye
 * exits the program and closes the input file
 * @param {FILE *} inFile - the input file to close
 */
void bye(FILE *inFile)
{
	fprintf(stdout, "\nProgram exiting.\n");
	fclose(inFile);
	exit(0);
}


/* these are all utility functions */
/**
 * listArgs
 * lists the arguments of the current command
 * @param {CommandP} command - the command to list the arguments of
 */
void listArgs(CommandP command) //lists all the args of the current command
{
	fprintf(stdout, "Arg1: %s, Arg2: %s, Arg3: %s.\n", command->args[0], command->args[1], command->args[2]);
	fprintf(stdout, "Arg count: %i\n", command->argCount);
	return;
}


/**
 * printParents
 * prints out the parent directories of the node passed (prints file location)
 * @params {NodeP} node - the node to print the parents of
 */
void printParents(NodeP node)
{
	if(getParent(node) != NULL)
		printParents(getParent(node));
	else
	{
		fprintf(stdout, "root/");
		return;
	}
	fprintf(stdout, "%s/", ((InfoP)getInfo(node))->name );
	return;
}


/**
 * doesFileExist
 * Recursively checks the current working directory for conflicting/duplicate file names
 * Returns TRUE if duplicate name is found, FALSE if there is no duplicate file name.
 * @param {char *} name - the name of the file/folder to search for
 * @param {NodeP} node - the first node to check in the directory
 * @return int returns TRUE if file exists, otherwise FALSE
 */
int doesFileExist(char *name, NodeP node)
{
	//NodeP temp = getRight(tree->curDir);
	if( !strcmp(name, ((InfoP)node->info)->name) )
		return(TRUE);
	else if(getRight(node)!=NULL)
		return(doesFileExist(name, getRight(node)) );
	else
		return(FALSE);
}


/**
 * insertNode
 * inserts the node into the directory, organized alphabetically
 * @params {NodeP} nodeSRC - the node to insert
 * @params {NodeP} nodeFS - specifies the directory to insert source node into
 */
void insertNode(NodeP nodeSRC, NodeP nodeFS)
{
	//nodeFS is the current node that will potentially come before the inserted node
	NodeP next = getRight(nodeFS);
	if(next == NULL)
	{
		setRight(nodeFS, nodeSRC);
		return;
	}

	int comp = strcmp( ((InfoP)getInfo(nodeSRC))->name, ((InfoP)getInfo(next))->name );

	if(comp < 0)
	{
		setRight(nodeFS, nodeSRC);
		setRight(nodeSRC, next);
		return;
	}
	//if it makes it this far, call again.
	insertNode(nodeSRC, next);
	return;
}


/**
 * findNode
 * Recursively checks the current working directory for for the node specified
 * Returns NodeP if file/folder is found, NULL if not found
 * @param {char *} name - the name of the file/folder to search for
 * @param {NodeP} node - the first node to check in the directory
 */
NodeP findNode(char *name, NodeP node)
{
	if( !strcmp(name, ((InfoP)node->info)->name) )
		return(node);
	else if(getRight(node)!=NULL)
		return(findNode(name, getRight(node)) );
	else
		return(NULL);
}


/**
 * clone
 * Recursively clones the node passed as well as all children and returns a pointer to the node
 * @params {NodeP} nodeSRC - the source node to clone
 * @params {TreeP} tree - a pointer to the file system tree
 * @return NodeP the duplicate node with children created
 */
NodeP clone(NodeP nodeSRC, TreeP tree)
{
	if( nodeSRC == NULL)
		return( NULL );
	InfoP info = getInfo(nodeSRC);
	InfoP new_Info = newInfo();
	NodeP nodeNEW = newNode();
	strcpy(new_Info->name, info->name);
	new_Info->type = info->type;
	setInfo(nodeNEW, new_Info);
	setParent(nodeNEW, tree->curDir);
	setRight(nodeNEW, clone(getRight(nodeSRC), tree));
	if( getLeft(nodeSRC) != NULL)
	{
		NodeP parent = tree->curDir;
		tree->curDir = nodeNEW;
		setLeft(nodeNEW, clone(getLeft(nodeSRC), tree));
		tree->curDir = parent;

	}
	else
	{
		setLeft(nodeNEW, NULL);
	}
	return (nodeNEW);

}


/**
 * recursiveFree
 * Recursively frees memory of the node passed, all children, and the info for the node and children
 * @param {NodeP} node - the node free memory of
 * @return NodeP the remains of what was the node pointer. This is always NULL.
 */
NodeP recursiveFree(NodeP node)
{
	if(node == NULL) //if already at end of pointer tree, no action needed.
		return(node);
	free(getInfo(node));
	setInfo(node, NULL);
	setLeft(node, recursiveFree( getLeft(node) ));
	setRight(node, recursiveFree( getRight(node) ));
	free(node);
	return(NULL);
}


/**
 * postOrderSearch
 * performs a post-order traversal of the file system for a file/folder with the name passed
 * @params {NodeP} node - the node to start the search at
 * @params {TreeP} tree - a pointer to the file system tree
 * @param {char *} name - the name of the file/folder to search for
 * @return NodeP the pointer to the first node found with the name specified. NULL if not found.
 */
NodeP postOrderSearch(NodeP node, TreeP tree, char *name)
{
	if(node == NULL)
		return(NULL);
	if( !strcmp(name, ((InfoP)node->info)->name) )
		return(node);
	NodeP temp = postOrderSearch(getRight(node), tree, name);
	if(temp != NULL)
		return(temp);
	temp = postOrderSearch(getLeft(node), tree, name);
	if(temp != NULL)
		return(temp);
	return(NULL);
}




