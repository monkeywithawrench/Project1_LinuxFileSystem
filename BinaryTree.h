/*************************************************************** 
 * Student Name: Jeff Morton
 * File Name: BinaryTree.h
 * Assignment Number: 1
 * Date Due: Jan 31, 2016
 * 
 *  Created on: Jan 26, 2015
 *      Author: Jeff Morton (jhm14@students.uwf.edu)
 *
 * About this file:
 * this file provides an interface used for creating and managing binary trees
 ***************************************************************/

#ifndef LINUXFS_P1_BINARYTREE_H_
#define LINUXFS_P1_BINARYTREE_H_



typedef struct Node *NodeP;
typedef struct Node
{
	NodeP parent, left, right;
	void *info;
} Node;




typedef struct Tree
{
	NodeP root, curDir;
}Tree, *TreeP;



/**
 * newTree
 * malloc's a new tree struct and returns a StructP pointer to it.
 * Remember, this pointer must be type-casted by the program utilizing the ADT
 * @return TreeP pointer to the new tree
 */
TreeP newTree();


/**
 * newNode
 * malloc's a new node struct and returns a NodeP pointer to it.
 * Remember, this pointer must be type-casted by the program utilizing the ADT
 * @return NodeP pointer to new node
 */
NodeP newNode();


/**
 * getInfo
 * Returns a void pointer to the info for the tree node passed to it.
 * Remember, this pointer must be type-casted by the program utilizing the ADT
 * @param {NodeP} node - pointer to the node to get the info of
 * @return void* void pointer to node's info data
 */
void *getInfo(NodeP);


/**
 * setInfo
 * Sets the info of the node passed to the void info pointer passed.
 * @param {NodeP} node - pointer to the node to set the info of
 * @param {void*} info - the info to set the info pointer in the node to
 */
void setInfo(NodeP, void *);


/**
 * getLeft
 * returns a NodeP pointer to the left child node of the NodeP passed.
 * @param {NodeP} node - the node to get the left child of
 * @return NodeP the left child of the node
 */
NodeP getLeft(NodeP);


/**
 * getRight
 * returns a NodeP pointer to the right child node of the NodeP passed.
 * @param {NodeP} node - the node to get the right child of
 * @return NodeP the right child of the node
 */
NodeP getRight(NodeP);


/**
 * getParent
 * returns a NodeP pointer to the parent node of the NodeP passed.
 * @param {NodeP} node - the node to get the parent of
 * @return NodeP the parent of the node
 */
NodeP getParent(NodeP);


/**
 * setLeft
 * sets the left pointer of the first NodeP to the second NodeP passed.
 * @param {NodeP} node - the node to set the child of
 * @param {NodeP} node - the left child node
 */
void setLeft(NodeP, NodeP);


/**
 * setRight
 * sets the right pointer of the first NodeP to the second NodeP passed.
 * @param {NodeP} node - the node to set the child of
 * @param {NodeP} node - the right child node
 */
void setRight(NodeP, NodeP);


/**
 * setParent
 * sets the parent pointer of the first NodeP to the second NodeP passed.
 * @param {NodeP} node - the node to set the parent of
 * @param {NodeP} node - the parent node
 */
void setParent(NodeP, NodeP);






#endif /* LINUXFS_P1_BINARYTREE_H_ */
