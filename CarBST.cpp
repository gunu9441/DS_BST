#include "CarBST.h"
#include <stack>
#include <queue>
#include <cstring>

CarBST::CarBST()//Instructor
{
	root = NULL;
	flog.open("log.txt",ios::app);
}


CarBST::~CarBST()//destructor
{
}

void CarBST::Insert(CarNode * node)//Insert
{
	if(root == NULL)
	{
		CarNode *newHead = new CarNode;
		newHead->SetcarNum(node->GetcarNum());//making new node.
		newHead->SetcarOwner(node->GetcarOwner());
		newHead->Setstate(node->Getstate());
		root = newHead;
	}
	else
	{
	CarNode* p = root;
	CarNode *pp = NULL;
	while (p)//Moving p
	{
		pp = p;
		if (node->GetcarNum() < p->GetcarNum())
			p = p->GetLeft();
		else if (node->GetcarNum() > p->GetcarNum())
			p = p->GetRight();
		else
		{
		}
	}
	p = new CarNode;
	p->SetcarNum(node->GetcarNum());
	p->SetcarOwner(node->GetcarOwner());
	p->Setstate(node->Getstate());
	if (node->GetcarNum() < pp->GetcarNum())//Place the node into the correct place.
		pp->SetLeft(p);
	else
		pp->SetRight(p);
	}
}
CarNode* CarBST::Delete(int num)
{
	CarNode *p = root, *q = 0;
	while (p&&num != p->GetcarNum())//p must be deleted.
	{
		q = p;
		if (num < p->GetcarNum())
			p = p->GetLeft();
		else
			p = p->GetRight();
	}
	if (p == 0) return NULL;//not found

	if (p->GetLeft() == 0 && p->GetRight() == 0)//leaf node
	{
		if (q == 0) root = 0;//only root is existed.
		else if (q->GetLeft() == p)
			q->SetLeft(NULL);
		else q->SetRight(NULL);
		return p;
	}

	if (p->GetLeft() == 0)//has only rightChild
	{
		if (q == 0) root = p->GetRight();
		else if (q->GetLeft() == p)
			q->SetLeft(p->GetRight());
		else
			q->SetRight(p->GetRight());
		return p;
	}

	if (p->GetRight() == 0)//has only leftChild
	{
		if (q == 0) root = p->GetLeft();
		else if (q->GetLeft() == p)
			q->SetLeft(p->GetLeft());
		else q->SetRight(p->GetLeft());
		return p;
	}

	CarNode *prevprev = p, *prev = p->GetLeft(), *curr = p->GetLeft()->GetRight();//has leftChild and rightChild. the biggest node in the left subtree.
	while (curr) {
		prevprev = prev;
		prev = curr;
		curr = curr->GetRight();
	}
	p->SetcarNum(prev->GetcarNum());
	if (prevprev == p) prevprev->SetLeft(prev->GetLeft());
	else prevprev->SetRight(prev->GetLeft());
	return prev;
}
CarNode* CarBST::Search(int num)//Search
{
	CarNode* currentNode = root;
	while (currentNode && currentNode->GetcarNum() != num)
	{
		if (currentNode->GetcarNum() > num)
			currentNode = currentNode->GetLeft();
		else
			currentNode = currentNode->GetRight();
	}
	return currentNode;
}
void CarBST::Print(const char * print_type)//Print
{
	if (!strcmp(print_type, "I_PRE"))//Iterative Preorder
	{
		if (root == NULL)
			return;

		stack<CarNode *> s;
		s.push(root);
		while (s.empty() == false)
		{
			CarNode* currentNode = s.top();
			flog << currentNode->GetcarNum() << " " << currentNode->GetcarOwner() << " " << currentNode->Getstate() << endl;//Output
			s.pop();

			if (currentNode->GetRight())
				s.push(currentNode->GetRight());
			if (currentNode->GetLeft())
				s.push(currentNode->GetLeft());
		}
	}

	else if (!strcmp(print_type, "I_IN"))//Iterative Inorder
	{
		stack<CarNode*> s;
		CarNode* currentNode = root;
		while (1)//loop
		{
			while (currentNode)
			{
				s.push(currentNode);
				currentNode = currentNode->GetLeft();
			}
			if (s.empty()) break;
			currentNode = s.top();
			s.pop();
			flog << currentNode->GetcarNum() << " " << currentNode->GetcarOwner() << " " << currentNode->Getstate() << endl;//Output

			currentNode = currentNode->GetRight();
		}
		return;
	}

	else if (!strcmp(print_type, "I_POST"))//Iterative Postorder
	{
		stack<CarNode*> child;
		stack<CarNode*> parent;

		if (root == NULL)
			return;

		child.push(root);

		while (!child.empty())
		{
			CarNode* curr = child.top();
			parent.push(curr);
			child.pop();
			if (curr->GetLeft())
				child.push(curr->GetLeft());
			if (curr->GetRight())
				child.push(curr->GetRight());
		}
		while (!parent.empty()) {
			flog << parent.top()->GetcarNum() << " " << parent.top()->GetcarOwner() << " " << parent.top()->Getstate() << endl;//Output
			parent.pop();
		}
	}
	else if (!strcmp(print_type, "I_LEVEL"))//Iterative Levelorder
	{
		queue<CarNode*> q;
		CarNode* currentNode = root;

		while (currentNode)
		{
			flog << currentNode->GetcarNum() << " " << currentNode->GetcarOwner() << " " << currentNode->Getstate() << endl;//Output
			if (currentNode->GetLeft())
				q.push(currentNode->GetLeft());
			if (currentNode->GetRight())
				q.push(currentNode->GetRight());
			if (q.empty()) break;
			currentNode = q.front();
			q.pop();
		}
	}
	else
		return;
}

void CarBST::Re_Inorder(CarNode* node)//Recursive_Inorder
{
	if (node)
	{
		Re_Inorder(node->GetLeft());
		flog << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
		Re_Inorder(node->GetRight());
	}
}
void CarBST::Re_Preorder(CarNode* node)//Recursive_preorder
{
	if (node)
	{
		flog << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
		Re_Preorder(node->GetLeft());
		Re_Preorder(node->GetRight());
	}
}
void CarBST::Re_Postorder(CarNode* node)//Recursive_postorder
{
	if (node)
	{
		Re_Postorder(node->GetLeft());
		Re_Postorder(node->GetRight());
		flog << node->GetcarNum() << " " << node->GetcarOwner() << " " << node->Getstate() << endl;
	}
}

void CarBST::save_Preorder(CarNode* node)//Save
{
	if(node==root)
		fevent_list.open("event_list_car.txt",ios::app);//Open ouput stream.
	if (node)
	{
		fevent_list << node->GetcarNum() << "	" << node->GetcarOwner() << "	" << node->Getstate() << endl;
		save_Preorder(node->GetLeft());
		save_Preorder(node->GetRight());
	}
}