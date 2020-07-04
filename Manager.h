#pragma once
#include "LinkedList.h"
#include "NumberBST.h"
#include "Queue.h"
#include<utility>
#include <cstring>


class Manager
{
public:
	LinkedList * ll;
	NumberBST * bst;
	Queue * queue;
	ofstream flog;

public:
	Manager();
	~Manager();

	void run(const char * command);
	bool LOAD();
	bool ADD();
	bool MOVE(int move_limit);
	bool SAVE();
	bool SEARCH(int car_num);
	bool SEARCH_ADD(int car_num);
	bool PRINT(char* token);
	bool PRINT(char* token, char* token_n);
	bool COMPLETE(int car_num);
	void EXIT();

	void printErrorCode(int n);
	void printSuccessCode(const char * cmdname);
	void printSearchCode(CarNode* car);

};

