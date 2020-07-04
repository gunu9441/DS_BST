#pragma once
#include "CarNode.h"
#include<fstream>
#include <cstring>

class LinkedList
{
private:
	ofstream flog;
	ofstream ftotal_list;

public:
	CarNode * pHead;

	LinkedList();
	~LinkedList();

	void Insert(CarNode * node);	//LOAD, ADD
	CarNode* Search(int car_num);		//SEARCH
	bool Print();	//PRINT
	bool Save();	//SAVE
	bool Delete(int Carnum);
	CarNode* Move();
};
