#pragma once
#include "NumberNode.h"
#include <iostream>
#include <fstream>
#include <cstring>


class NumberBST
{
private:
	NumberNode * root;
	int nodeCnt;
	ofstream flog;

public:
	NumberBST();
	~NumberBST();


	void		Insert(NumberNode * node);			// LOAD, MOVE
	NumberNode *	Search(int num);				// ADD, COMPLETE, SEARCH, DELETE
	bool		Print(char * print_type);			// PRINT
	bool		Save();								// SAVE
	void		Re_Inorder(NumberNode *node);
	void		Re_Preorder(NumberNode *node);
	void		Re_Postorder(NumberNode *node);
	void		save_Preorder(NumberNode *node);
	int			getCnt();
	void		setCnt(int cnt);
	CarBST* Move(CarNode* node);
};