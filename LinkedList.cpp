#include "LinkedList.h"
#include <cstring>



LinkedList::LinkedList()//Instructor
{
	pHead = NULL;
	flog.open("log.txt", ios::app);
}


LinkedList::~LinkedList()//Destructor
{
}

void LinkedList::Insert(CarNode * node)//Insert
{
	if (pHead != NULL)//If pHead is exist
	{
		CarNode* currentNode = pHead;
		while (currentNode->GetNext() != NULL)//Move the temp;
			currentNode = currentNode->GetNext();
		CarNode* nextNode = new CarNode;
		nextNode->SetcarNum(node->GetcarNum());
		nextNode->SetcarOwner(node->GetcarOwner());
		nextNode->Setstate(node->Getstate());
		currentNode->SetNext(nextNode);
	}
	else//or not
	{
		CarNode *newHead = new CarNode;
		newHead->SetcarNum(node->GetcarNum());
		newHead->SetcarOwner(node->GetcarOwner());
		newHead->Setstate(node->Getstate());
		pHead = newHead;
	}
}

CarNode* LinkedList::Search(int car_num)//Search
{
	CarNode* currentNode = pHead;
	while (currentNode&&currentNode->GetcarNum() != car_num)
	{
		currentNode = currentNode->GetNext();
	}
	return currentNode;
}

bool LinkedList::Print()//Print
{
	CarNode* currentNode = pHead;
	if (pHead == NULL)
		return false;
	flog << "======= PRINT =======" << endl;//Output
	while (currentNode)
	{
		flog << currentNode->GetcarNum() << " " << currentNode->GetcarOwner() << " " << currentNode->Getstate() << endl;//Output
		currentNode = currentNode->GetNext();
	}
	flog << "===================" << endl << endl;//Output
	return true;
}

bool LinkedList::Save()
{
	ftotal_list.open("total_list_car.txt",ios::app);//Open the file.
	CarNode* currentNode = pHead;
	if (pHead == NULL)//Exception handling.
		return false;
	while (currentNode)
	{
		if (currentNode->GetcarNum() < 0)//Exception Handling.
			break;
		ftotal_list<< currentNode->GetcarNum() << "	" << currentNode->GetcarOwner() << "	" << currentNode->Getstate() << endl;//Output
		currentNode = currentNode->GetNext();
	}
	return true;
}

bool LinkedList::Delete(int Carnum)//Delete
{
	CarNode* currentNode = pHead;
	CarNode* prevNode = NULL;
	while (currentNode->GetcarNum() != Carnum)
	{
		prevNode = currentNode;
		currentNode = currentNode->GetNext();
	}
	if (prevNode == NULL)//Deleted node is pHead.
		pHead = currentNode->GetNext();
	else
		if(currentNode->GetNext()!=NULL)//node is sequantial after currentNode
			prevNode->SetNext(currentNode->GetNext());
	delete currentNode;
	return true;
}

CarNode* LinkedList::Move()//Move
{
	CarNode* currentNode = pHead;
	while (currentNode&&currentNode->Getstate() != 'Y')
	{
		currentNode = currentNode->GetNext();
		if (currentNode == NULL)
			return NULL;
		if (currentNode->GetcarNum() < 0)//Exception Handling.
			return NULL;
	}
	return currentNode;
}
