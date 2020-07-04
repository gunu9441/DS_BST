#include "Queue.h"
#include <cstring>


Queue::Queue()
{
	pHead = NULL;
	flog.open("log.txt",ios::app);
}


Queue::~Queue()//Destructor
{
	flog.close();
}

void Queue::Push(CarNode * node)//Add the node.
{
	if (pHead != NULL)
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
	else
	{
		CarNode *newHead = new CarNode;
		newHead->SetcarNum(node->GetcarNum());
		newHead->SetcarOwner(node->GetcarOwner());
		newHead->Setstate(node->Getstate());
		pHead = newHead;
	}
}

void Queue::Pop()//delete the node.
{
	CarNode* currentNode = new CarNode;
	currentNode = pHead;
	pHead = pHead->GetNext();
	delete currentNode;
}

CarNode* Queue::Search(int car_num)//Search
{
	CarNode* currentNode = pHead;
	while (currentNode&&currentNode->GetcarNum() != car_num)
	{
		currentNode = currentNode->GetNext();
	}
	return currentNode;
}

bool Queue::Print()//Print
{
	CarNode* currentNode = pHead;
	if (pHead == NULL)
		return false;
	flog << "======= PRINT =======" << endl;
	while (currentNode)
	{
		flog << currentNode->GetcarNum() << " " << currentNode->GetcarOwner() << " " << currentNode->Getstate() << endl;
		currentNode = currentNode->GetNext();
	}
	flog << "===================" << endl << endl;
	return true;
}

bool Queue::Save()//Save
{
	if (pHead == NULL)
		return false;
	fcomplete_list.open("complete_list_car.txt", ios::app);
	while (1)
	{
		fcomplete_list << pHead->GetcarNum() << "	" << pHead->GetcarOwner() << "	" << pHead->Getstate() << endl;
		Pop();
		if (pHead == NULL)
			break;
	}
	return true;
}
