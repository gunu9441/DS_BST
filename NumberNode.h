#pragma once
#include "CarBST.h"
#include <cstring>

class NumberNode
{
private:
	int number;
	CarBST * bst;
	NumberNode * pLeft;			// BST Left Pointer
	NumberNode * pRight;		// BST Right Pointer

public:
	NumberNode()
	{
		number = NULL;
		bst = new CarBST;
		pLeft = NULL;
		pRight = NULL;
	}
	NumberNode(int num)
	{
		number = num;
		bst = new CarBST;
		pLeft = NULL;
		pRight = NULL;
	}
	~NumberNode();

	int			GetNumber();						// Get Number
	CarBST *		GetBST();						// Get Car BST
	NumberNode *	GetLeft();						// Get BST Left Pointer
	NumberNode *	GetRight();						// Get BST Right Pointer

	void			SetNumber(int num);				// Set Alphabet
	void			SetLeft(NumberNode * node);		// Set BST Left Pointer
	void			SetRight(NumberNode * node);	// Set BST Right Pointer
	void 			SetBST(CarBST * node);			// Set Car BST
};

