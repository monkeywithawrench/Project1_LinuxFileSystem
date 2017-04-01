/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: BinaryTree.c
 * Assignment Number: 1
 * Date Due: Jan 31, 2016
 * 
 *  Created on: Jan 26, 2015
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 *
 * About this file:
 * this file provides an API used for creating and managing binary trees
 ***************************************************************/

#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>




/**
 * newTree
 * malloc's a new tree struct and returns a StructP pointer to it.
 * Remember, this pointer must be type-casted by the program utilizing the ADT
 * @return TreeP pointer to the new tree
 */
TreeP newTree()
{
	TreeP tree;
	tree = /*(TreeP)*/malloc(sizeof(Tree));
	if(tree == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Tree Malloc failed!");
		return(tree);
	}
	NodeP node = newNode();
	tree->root = tree->curDir = node;
	return(tree);
}


/**
 * newNode
 * malloc's a new node struct and returns a NodeP pointer to it.
 * Remember, this pointer must be type-casted by the program utilizing the ADT
 * @return NodeP pointer to new node
 */
NodeP newNode()
{
	NodeP node = malloc(sizeof(Node));
	if(node == NULL)	//Checks malloc success.
	{
		fprintf(stderr, "ERROR! Node Malloc failed!");
		return(node);
	}
	node->parent = node->left = node->right = NULL;
	return(node);
}


/**
 * getInfo
 * Returns a void pointer to the info for the tree node passed to it.
 * Remember, this pointer must be type-casted by the program utilizing the ADT
 * @param {NodeP} node - pointer to the node to get the info of
 * @return void* void pointer to node's info data
 */
void *getInfo(NodeP node)
{
	return(node->info);
}


/**
 * setInfo
 * Sets the info of the node passed to the void info pointer passed.
 * @param {NodeP} node - pointer to the node to set the info of
 * @param {void*} info - the info to set the info pointer in the node to
 */
void setInfo(NodeP node, void *info)
{
	node->info = info;
	return;
}


/**
 * getLeft
 * returns a NodeP pointer to the left child node of the NodeP passed.
 * @param {NodeP} node - the node to get the left child of
 * @return NodeP the left child of the node
 */
NodeP getLeft(NodeP node)
{
	return(node->left);
}


/**
 * getRight
 * returns a NodeP pointer to the right child node of the NodeP passed.
 * @param {NodeP} node - the node to get the right child of
 * @return NodeP the right child of the node
 */
NodeP getRight(NodeP node)
{
	return(node->right);
}


/**
 * getParent
 * returns a NodeP pointer to the parent node of the NodeP passed.
 * @param {NodeP} node - the node to get the parent of
 * @return NodeP the parent of the node
 */
NodeP getParent(NodeP node)
{
	return(node->parent);
}


/**
 * setLeft
 * sets the left pointer of the first NodeP to the second NodeP passed.
 * @param {NodeP} node - the node to set the child of
 * @param {NodeP} node - the left child node
 */
void setLeft(NodeP node, NodeP node2)
{
	node->left = node2;
	return;
}


/**
 * setRight
 * sets the right pointer of the first NodeP to the second NodeP passed.
 * @param {NodeP} node - the node to set the child of
 * @param {NodeP} node - the right child node
 */
void setRight(NodeP node, NodeP node2)
{
	node->right = node2;
	return;
}


/**
 * setParent
 * sets the parent pointer of the first NodeP to the second NodeP passed.
 * @param {NodeP} node - the node to set the parent of
 * @param {NodeP} node - the parent node
 */
void setParent(NodeP node, NodeP node2)
{
	node->parent = node2;
	return;
}


