#include "NumberBST.h"
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

NumberBST::NumberBST()//Constructor
{
	root = NULL;
	nodeCnt = 0;
	flog.open("log.txt", ios::app);
}

NumberBST::~NumberBST()//Destructor
{
}

void NumberBST::Insert(NumberNode * node)//Insert
{
	NumberNode *p = root, *pp = NULL;
	while (p)//Moving P
	{
		pp = p;
		if (node->GetNumber() < p->GetNumber())
			p = p->GetLeft();
		else if (node->GetNumber() > p->GetNumber())
			p = p->GetRight();
		else
			return;
	}
	p = new NumberNode;
	p = node;
	if (root != NULL)//if root is not Null.
		if (node->GetNumber() < pp->GetNumber())
			pp->SetLeft(p);
		else
			pp->SetRight(p);
	else
		root = p;//or not
}

NumberNode*	NumberBST::Search(int num)//Search
{
	NumberNode* currentNode = root;
	while (currentNode && currentNode->GetNumber() != num / 1000)
	{
		if (currentNode->GetNumber() > num / 1000)
			currentNode = currentNode->GetLeft();
		else
			currentNode = currentNode->GetRight();
	}
	return currentNode;
}

bool NumberBST::Print(char * print_type)//Print
{
	if (!strcmp(print_type, "R_PRE"))//Recursive preorder
	{
		flog << "======= PRINT =======" << endl;
		Re_Preorder(root);
		flog << "===================" << endl << endl;
	}
	else if (!strcmp(print_type, "I_PRE"))//Iterative preorder
	{
		flog << "======= PRINT =======" << endl;
		stack<NumberNode *> s;
		s.push(root);
		while (s.empty() == false)
		{
			NumberNode* node = s.top();
			node->GetBST()->Print("I_PRE");
			s.pop();

			if (node->GetRight())
				s.push(node->GetRight());
			if (node->GetLeft())
				s.push(node->GetLeft());
		}
		flog << "===================" << endl << endl;
	}
	else if (!strcmp(print_type, "R_IN"))//Recursive inorder
	{
		flog << "======= PRINT =======" << endl;
		Re_Inorder(root);
		flog << "===================" << endl << endl;
	}

	else if (!strcmp(print_type, "I_IN"))//Iterative inorder
	{
		flog << "======= PRINT =======" << endl;
		stack<NumberNode*> s;
		NumberNode* currentNode = root;
		while (1)
		{
			while (currentNode)
			{
				s.push(currentNode);
				currentNode = currentNode->GetLeft();
			}
			if (s.empty())break;
			currentNode = s.top();
			s.pop();
			currentNode->GetBST()->Print("I_IN");

			currentNode = currentNode->GetRight();
		}
		flog << "===================" << endl << endl;
	}
	else if (!strcmp(print_type, "R_POST"))//Recursive postorder
	{
		flog << "======= PRINT =======" << endl;
		Re_Postorder(root);
		flog << "===================" << endl << endl;
	}
	else if (!strcmp(print_type, "I_POST"))//Iterative postorder
	{
		flog << "======= PRINT =======" << endl;
		stack<NumberNode*> child;
		stack<NumberNode*> parent;

		child.push(root);

		while (!child.empty())
		{
			NumberNode *curr = child.top();
			parent.push(curr);
			child.pop();
			if (curr->GetLeft())
				child.push(curr->GetLeft());
			if (curr->GetRight())
				child.push(curr->GetRight());
		}
		while (!parent.empty()) {
			parent.top()->GetBST()->Print("I_POST");
			parent.pop();
		}
		flog << "===================" << endl << endl;
	}
	else if (!strcmp(print_type, "I_LEVEL"))//Iterative level order
	{
		flog << "======= PRINT =======" << endl;
		queue<NumberNode*> q;
		NumberNode* currentNode = root;

		while (currentNode)
		{
			currentNode->GetBST()->Print("I_LEVEL");
			if (currentNode->GetLeft())
				q.push(currentNode->GetLeft());
			if (currentNode->GetRight())
				q.push(currentNode->GetRight());
			if (q.empty()) break;
			currentNode = q.front();
			q.pop();
		}
		flog << "===================" << endl << endl;
	}
	else
		return false;

	return true;
}

bool NumberBST::Save()
{
	int IsWork;
	if (getCnt() == 0)
		return false;
	else
	{
		save_Preorder(root);
		return true;
	}
}

void NumberBST::Re_Inorder(NumberNode *node)//Recursive inorder
{
	if (node)
	{
		Re_Inorder(node->GetLeft());
		node->GetBST()->Re_Inorder(node->GetBST()->root);
		Re_Inorder(node->GetRight());
	}
}

void NumberBST::Re_Preorder(NumberNode *node)//Recursive preorder
{
	if (node)
	{
		node->GetBST()->Re_Preorder(node->GetBST()->root);
		Re_Preorder(node->GetLeft());
		Re_Preorder(node->GetRight());
	}
}

void NumberBST::Re_Postorder(NumberNode *node)//Recursive postorder
{
	if (node)
	{
		Re_Postorder(node->GetLeft());
		Re_Postorder(node->GetRight());
		node->GetBST()->Re_Postorder(node->GetBST()->root);
	}
}

void NumberBST::save_Preorder(NumberNode *node)//Save
{
	if (node)
	{
		node->GetBST()->save_Preorder(node->GetBST()->root);
		save_Preorder(node->GetLeft());
		save_Preorder(node->GetRight());
	}
}

int	NumberBST::getCnt()//return nodCnt
{
	return nodeCnt;
}

void NumberBST::setCnt(int cnt)
{
	nodeCnt = cnt;
}

CarBST* NumberBST::Move(CarNode* node)
{
	return Search(node->GetcarNum())->GetBST();
}