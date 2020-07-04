#include "NumberNode.h"
#include <cstring>

NumberNode::~NumberNode()
{
}

int NumberNode::GetNumber()
{
	return number;
}
CarBST * NumberNode::GetBST()
{
	return bst;
}
NumberNode * NumberNode::GetLeft()
{
	return pLeft;
}
NumberNode *NumberNode::GetRight()
{
	return pRight;
}
void NumberNode::SetNumber(int num)
{
	number = num;
}
void NumberNode::SetLeft(NumberNode * node)
{
	pLeft = node;
}
void NumberNode::SetRight(NumberNode * node)
{
	pRight = node;
}
void NumberNode::SetBST(CarBST * node)
{
	bst = node;
}