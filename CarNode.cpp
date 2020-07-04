#include "CarNode.h"
#include <cstring>

CarNode::~CarNode()
{
}

int CarNode::GetcarNum()
{
	return carNumber;
}

char * CarNode::GetcarOwner()
{
	return name;
}

char CarNode::Getstate()
{
	return state;
}

CarNode * CarNode::GetLeft()
{
	return pLeft;
}

CarNode * CarNode::GetRight()
{
	return pRight;
}

CarNode * CarNode::GetNext()
{
	return pNext;
}

void CarNode::SetcarNum(int carNum)
{
	carNumber = carNum;
}
void CarNode::SetcarOwner(char * carOwner)
{
	name = carOwner;
}
void CarNode::Setstate(char carstate)
{
	state = carstate;
}

void CarNode::SetLeft(CarNode * node)
{
	pLeft = node;
}

void CarNode::SetRight(CarNode * node)
{
	pRight = node;
}

void CarNode::SetNext(CarNode * node)
{
	pNext = node;
}