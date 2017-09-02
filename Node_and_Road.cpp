#include "Node_and_Road.h"
#include <iostream>
using namespace std;

Road::~Road()
{
	//cout << "Road des." << endl;
}

Node::~Node()
{
	//cout << "Node des." << endl;
}

void DeleteRoad(Road *pHead)
{
	Road *pMove=pHead;
	Road *pMoveNext = pHead->pNext;
	while (pMoveNext!=NULL)
	{
		delete pMove;
		pMove = pMoveNext;
		pMoveNext = pMoveNext->pNext;
	}
	delete pMove; //最后一个
}
void DeleteNode(Node *pHead)
{
	Node *pMove = pHead;
	Node *pMoveNext = pHead->pNext;
	while (pMoveNext != NULL)
	{
		delete pMove;
		pMove = pMoveNext;
		pMoveNext = pMoveNext->pNext;
	}
	delete pMove; //最后一个

}