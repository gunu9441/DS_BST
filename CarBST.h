#pragma once
#include "CarNode.h"
#include <iostream>
#include <fstream>// header file declare
#include <cstring>

using namespace std;
class CarBST
{
public:
	CarNode * root;
	ofstream flog;
	ofstream fevent_list;

public:
	CarBST();
	~CarBST();

	void		Insert(CarNode * node);			// LOAD, MOVE
	CarNode *	Delete(int num);				// COMPLETE
	CarNode *	Search(int num);				// ADD, COMPLETE, SEARCH
	void		Print(const char * print_type);		// PRINT
	void		Re_Inorder(CarNode* node);
	void		Re_Preorder(CarNode* node);
	void		Re_Postorder(CarNode* node);
	void		save_Preorder(CarNode* node);
};