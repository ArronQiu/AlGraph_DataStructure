#pragma once
#include"ALGraph.h"
struct QueueNode
{
	~QueueNode();
	int nID;
	float fLength;
	struct QueueNode *pNext;
};

struct LinkQueue
{
	QueueNode *rear;
	QueueNode *front;
};

/*º¯ÊýÉùÃ÷*/
int InitQueue(struct LinkQueue *Q);
void EnQueue(struct LinkQueue *Q, struct OtherNode Distance);
void DeQueue(struct LinkQueue *Q);
bool Empty(struct LinkQueue *Q);
void DeleteQueue(LinkQueue *pHead);