#pragma once
#include "CarNode.h"
#include <queue>
#include <fstream>
#include <cstring>

class Queue
{
public: 		// public member funciton
	ofstream fcomplete_list;
	Queue();
	~Queue();

	CarNode * pHead;							// member variable
	ofstream flog;

	void		Push(CarNode * node);			// LOAD
	void		Pop();
	CarNode *	Search(int car_num);				// SEARCH
	bool		Print();						// PRINT
	bool		Save();
};