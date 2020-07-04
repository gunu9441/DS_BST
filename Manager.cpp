#include "Manager.h"
#include <cstring>


Manager::Manager()
{
	ll = new LinkedList;//Linked_List
	bst = new NumberBST;//Binary_Search_Tree
	queue = new Queue;//Queue
	flog.open("log.txt", ios::app);//flog is used by Manager run and Manager ADD.
}


Manager::~Manager()//destructor
{
}

void Manager::run(const char * command)
{
	ifstream fin;//Open ifstream
	int IsWork;
	fin.open(command);//Open command.

	char *cmd = new char[40];

	NumberNode* a = new NumberNode(7);//Making NumberBST.
	bst->Insert(a);
	NumberNode* b = new NumberNode(3);
	bst->Insert(b);
	NumberNode* c = new NumberNode(9);
	bst->Insert(c);
	NumberNode* d = new NumberNode(1);
	bst->Insert(d);
	NumberNode* e = new NumberNode(5);
	bst->Insert(e);
	NumberNode* f = new NumberNode(8);
	bst->Insert(f);
	NumberNode* g = new NumberNode(0);
	bst->Insert(g);
	NumberNode* h = new NumberNode(2);
	bst->Insert(h);
	NumberNode* i = new NumberNode(4);
	bst->Insert(i);
	NumberNode* j = new NumberNode(6);
	bst->Insert(j);

	while (!fin.eof())//Until meet file's end.
	{
		fin.getline(cmd, 40);
		char * tmp = strtok(cmd, " ");

		if (strcmp(tmp, "LOAD") == 0)//LOAD
		{
			if (LOAD())
				printSuccessCode("LOAD");
			else printErrorCode(100);
		}

		else if (strcmp(tmp, "ADD") == 0)//ADD
		{
			if (ADD())
				printSuccessCode("ADD");

			else printErrorCode(200);
		}

		else if (strcmp(tmp, "MOVE") == 0)//MOVE
		{
			tmp = strtok(NULL, " ");
			if (atoi(tmp) > 100 || atoi(tmp) < 1)//Exception Handling.
				printErrorCode(300);
			else
			{
				IsWork = MOVE(atoi(tmp));
				if (IsWork == true)
					printSuccessCode("MOVE");
				else printErrorCode(300);
			}
		}

		else if (strcmp(tmp, "SAVE") == 0)//SAVE
		{
			if (SAVE())
				printSuccessCode("SAVE");
			else printErrorCode(400);
		}

		else if (strcmp(tmp, "SEARCH") == 0)//SEARCH
		{
			tmp = strtok(NULL, " ");
			if (SEARCH(atoi(tmp)))
				continue;
			else printErrorCode(500);
		}

		else if (strcmp(tmp, "PRINT") == 0)//PRINT
		{
			char* tmp_n;//Second parameter of EVENT_LIST and COMPLETE_LIST
			tmp = strtok(NULL, " ");

			if (!strcmp(tmp, "EVENT_LIST"))
			{
				tmp_n = strtok(NULL, " ");
				IsWork = PRINT(tmp, tmp_n);
			}
			else//TOTAL_LIST and COMPLETE_LIST
				IsWork = PRINT(tmp);

			if (IsWork != true)
				printErrorCode(600);
		}

		else if (strcmp(tmp, "COMPLETE") == 0)//COMPLETE
		{
			tmp = strtok(NULL, " ");
			if (COMPLETE(atoi(tmp)))
				continue;
			else printErrorCode(700);
		}
		else//EXIT
		{
			EXIT();
			printSuccessCode("EXIT");
			break;
		}
	}
	fin.close();
	flog.close();
	return;
}


void Manager::printErrorCode(int n) {				//ERROR CODE PRINT 
	flog << "========ERROR=======" << endl;
	flog << n << endl;
	flog << "====================" << endl << endl;
}

void Manager::printSuccessCode(const char * cmdname) {//SUCCESS CODE PRINT 
	flog << "========" << cmdname << "========" << endl;
	flog << "Success" << endl;
	flog << "====================" << endl << endl;
}

void Manager::printSearchCode(CarNode* car)//PRINT SEARCH CODE
{
	flog<< "=======SEARCH======" << endl;
	flog << car->GetcarNum() << "	" << car->GetcarOwner() << "	" << car->Getstate() << endl;
	flog << "===================" << endl << endl;
}
bool Manager::LOAD()//LOAD
{
	ifstream total_load, event_load, complete_load;

	total_load.open("total_list_car.txt",ios::in);//open 3 input stream.
	event_load.open("event_list_car.txt",ios::in);
	complete_load.open("complete_list_car.txt",ios::in);

	CarNode* a=ll->pHead;//Check the file that has already existed.
	int b = bst->getCnt();
	CarNode* c = queue->pHead;

	if (total_load)//If total_load open.
	{
		char *token = new char[50];
		int car_num;
		char* user_name = new char[5];
		char* det = new char[5];

		while (!total_load.eof())
		{
			char* Info = new char[100];//save one sentence.
			CarNode* newcar = new CarNode;
			total_load.getline(Info, 100);

			token = strtok(Info, "	");

			if (token == NULL)//Handling NULL pointer.
				break;

			car_num = atoi(token);		//Car number

			token = strtok(NULL, "	");	//Owner
			user_name = token;

			token = strtok(NULL, "	");
			det = token;				//Car accident

			newcar->SetcarNum(car_num);
			newcar->SetcarOwner(user_name);
			newcar->Setstate(det[0]);
			if (SEARCH_ADD(car_num) == false)
				ll->Insert(newcar);
			else
				continue;
		}
		total_load.close();
		remove("total_list_car.txt");
	}
	if (event_load)//If event_load open.
	{
		char *token = new char[50];
		int car_num;
		char* user_name = new char[5];
		char* det = new char[5];

		while (!event_load.eof())
		{
			char* Info = new char[100];//save one sentence.
			CarNode* newcar = new CarNode();
			event_load.getline(Info, 100);

			token = strtok(Info, "	");

			if (token == NULL)//Handling NULL pointer.
				break;

			car_num = atoi(token);		//Car number

			token = strtok(NULL, "	"); 
			user_name = token;			//Owner

			token = strtok(NULL, "	");
			det = token;				//Car accident

			newcar->SetcarNum(car_num);	//Making new car node.
			newcar->SetcarOwner(user_name);
			newcar->Setstate(det[0]);
			if (SEARCH_ADD(car_num) == false)
			{
				bst->Search(car_num)->GetBST()->Insert(newcar);
				bst->setCnt(bst->getCnt() + 1);//nodeCnt++
			}
			else
				continue;
		}
		event_load.close();
		remove("event_list_car.txt");
	}
	if (complete_load)
	{
		char *token = new char[50];
		int car_num;
		char* user_name = new char[5];
		char* det = new char[5];

		while (!complete_load.eof())
		{
			char* Info = new char[100];//save one sentence.
			CarNode* newcar = new CarNode;
			complete_load.getline(Info, 100);

			token = strtok(Info, "	");

			if (token == NULL)			//Exception Handling - NULL pointer.
				break;

			car_num = atoi(token);

			token = strtok(NULL, "	");
			user_name = token;

			token = strtok(NULL, "	");
			det = token;

			newcar->SetcarNum(car_num);
			newcar->SetcarOwner(user_name);
			newcar->Setstate(det[0]);
			if (SEARCH_ADD(car_num) == false)
				queue->Push(newcar);
			else
				continue;
		}
		complete_load.close();
		remove("complete_list_car.txt");
	}

	if (a != NULL || c != NULL || b != 0)	//if there is any list that has already existed, impelement this.
		return false;

	if (ll->pHead == NULL || bst->getCnt() == 0 || queue->pHead == NULL)// if there is any node that does not has root, return false.
		return false;

	else
		return true;
}

bool Manager::ADD()//Add information in car.txt
{
	ifstream add_car;
	add_car.open("car.txt");

	char *token = new char[50];
	int car_num;
	char *user_name = new char[5];
	char* det = new char[5];

	if (!add_car)
		return false;

	while (!add_car.eof())
	{
		char* Info = new char[100];//save one sentence.
		CarNode* newcar = new CarNode;
		add_car.getline(Info, 100);

		token = strtok(Info, "	");

		if (token == NULL)//Handling NULL pointer.
			break;

		car_num = atoi(token);

		token = strtok(NULL, "	");
		user_name = token;

		token = strtok(NULL, "	");
		det = token;

		newcar->SetcarNum(car_num);
		newcar->SetcarOwner(user_name);
		newcar->Setstate(det[0]);
		if (SEARCH_ADD(car_num) == false)
			ll->Insert(newcar);
		else
			continue;
	}
	return true;
}

bool Manager::MOVE(int move_limit)
{
	int loop, det;
	int total_node = move_limit+bst->getCnt();
	int bst_node = bst->getCnt();

	if (total_node > 100)
		return false;

	for (det = 0; det < move_limit;det++)
	{
		CarNode* a = ll->Move();
		if (a == NULL)
			break;
	}

	if (det != move_limit)//move_limit and the number of nodes that has car accident is not same.
		return false;

	for (loop = 0;loop < move_limit;loop++)
	{
		CarNode* a = ll->Move();
		if (a == NULL)//there are not any 'N' node.
			break;
		CarBST* b = bst->Move(a);
		bst->setCnt(bst->getCnt() + 1);//bst nodeCnt increased.
		b->Insert(a);
		ll->Delete(a->GetcarNum());
	}
	if (bst_node == bst->getCnt())//moving node is not existed.
		return false;
	else
		return true;
}

bool Manager::SAVE()
{
	int IsWork_ll, IsWork_bst, IsWork_queue;
	IsWork_ll = ll->Save();
	IsWork_bst = bst->Save();
	IsWork_queue = queue->Save();

	if (!IsWork_ll&&!IsWork_bst&&!IsWork_queue)//3 IsWork are false.
		return false;
	else
		return true;
}

bool Manager::SEARCH(int car_num)
{
	NumberNode* found_num;
	CarNode* det = ll->Search(car_num);
	if (det != NULL)//Linked_List
		printSearchCode(det);
	else//not found
	{
		found_num = bst->Search(car_num);
		det = found_num->GetBST()->Search(car_num);
		if (det != NULL)//BST
			printSearchCode(det);
		else
		{
			det = queue->Search(car_num);
			if (det != NULL)//Queue
				printSearchCode(det);
			else
				return false;
		}

	}
	return true;
}

bool Manager::SEARCH_ADD(int car_num)
{
	NumberNode* found_num;
	CarNode* det = ll->Search(car_num);
	if (det == NULL)//Linked_List
	{
		found_num = bst->Search(car_num);
		det = found_num->GetBST()->Search(car_num);
		if (det == NULL)//BST
		{
			det = queue->Search(car_num);
			if (det == NULL)//Queue
				return false;//Cannot found.
		}
	}
	return true;//found.
}
bool Manager::PRINT(char* token)
{
	int IsWork = 0;

	if (strcmp(token, "TOTAL_LIST") == 0)//TOTAL_LIST
		IsWork = ll->Print();
	else//COMPLETE_LIST
		IsWork = queue->Print();

	if (IsWork == true)
		return true;
	else
		return false;
}
bool Manager::PRINT(char* token,char* token_n)//COMPLETE
{
	int IsWork = 0;
	if (bst->getCnt() == 0)//There is not any bst_node.	
		return false;

	if (strcmp(token, "EVENT_LIST") == 0)
		IsWork = bst->Print(token_n);
	
	if (IsWork == true)
		return true;
	else
		return false;
}

bool Manager::COMPLETE(int car_num)//COMPLETE
{
	CarNode* complete_car = bst->Search(car_num)->GetBST()->Search(car_num);
	if (complete_car == NULL)
		return false;
	else
	{
		flog << "======= PRINT =======" << endl;
		bst->Search(car_num)->GetBST()->Delete(car_num);
		complete_car->Setstate('C');
		queue->Push(complete_car);
		bst->setCnt(bst->getCnt() - 1);
		flog << complete_car->GetcarNum() << "	" << complete_car->GetcarOwner() << "	" << complete_car->Getstate() << endl;
		flog << "==================" << endl << endl;
		return true;
	}
}

void Manager::EXIT()
{
	return;
}