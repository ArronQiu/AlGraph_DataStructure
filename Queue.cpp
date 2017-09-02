#include "Queue.h"
#include "ALGraph.h"
#include <iostream>
using namespace std;

int InitQueue(struct LinkQueue *Q) //初始化有头结点front的队列，通过front,第一个有元素节点和rear实现快速排序，达到优先队列的目的（即“有序”）
{
	Q->front = Q->rear = new QueueNode;
	if (!Q->front) return -1;
	Q->front->pNext = NULL;
	return 1;
}

void EnQueue(struct LinkQueue *Q, struct OtherNode Distance)
{
	/*若队列内已有同ID的节点，即该节点曾更新过距离，则需要删除过去的*/
	QueueNode *pQMove_ToDeleteTheSameIDNode = Q->front->pNext;
	QueueNode *pQMove_Prev = Q->front;
	while (pQMove_ToDeleteTheSameIDNode)
	{
		if (pQMove_ToDeleteTheSameIDNode->nID == Distance.nID)
		{
			pQMove_Prev->pNext = pQMove_ToDeleteTheSameIDNode->pNext;
			delete (pQMove_ToDeleteTheSameIDNode);
			break;
		}
		pQMove_Prev = pQMove_Prev->pNext;
		pQMove_ToDeleteTheSameIDNode = pQMove_ToDeleteTheSameIDNode->pNext;
	}
	QueueNode *pNewNode = new QueueNode; //建立一个新的队列节点
	pNewNode->nID = Distance.nID;
	pNewNode->fLength = Distance.fLength;

	/*因为入队前队列有序，所以仅需逐个比较fLength即可找到插入的位置*/
	QueueNode *pQMove;	//寻找p的插入位置
	pQMove = Q->front->pNext;
	pQMove_Prev = Q->front;
	/*【可优化为折半查找】，时间复杂度变为O(log_2_N)*/
	while (pQMove != NULL)
	{
		if (pNewNode->fLength > pQMove->fLength)
		{
			pQMove = pQMove->pNext;
			pQMove_Prev = pQMove_Prev->pNext;
		}
		else
			break;
	}
	pQMove_Prev->pNext = pNewNode; //插入
	pNewNode->pNext = pQMove;

	//确保排序后rear指向末尾
	
	Q->rear = pNewNode;
	pQMove = pNewNode->pNext;
	while (pQMove != NULL)
	{
		Q->rear = Q->rear->pNext;
		pQMove = pQMove->pNext;
	}
}

void DeQueue(struct LinkQueue *Q)
{
	// 若队列不空，则删除 Q 的队头元素
	if (Q->front == Q->rear) return; //队列为空，直接退出
	QueueNode *p = Q->front->pNext;
	Q->front->pNext = p->pNext;
	if (Q->rear == p) Q->rear = Q->front;   //若队头是队尾，则删除后将rear指向头结点
	delete (p);
}

bool Empty(struct LinkQueue *Q)
{
	if (Q->front == Q->rear)
		return 1;
	else
		return 0;
}

void DeleteQueue(LinkQueue *Q)
{
	
	//能否直接 delete []Q ??
	//delete[]Q;
	QueueNode *pMove = Q->front;
	QueueNode *pMoveNext = Q->front->pNext;
	while (pMoveNext != NULL)
	{
		//cout << pMove->nID <<"QNode des."<< endl;
		delete pMove;
		pMove = pMoveNext;
		pMoveNext = pMoveNext->pNext;
	}
	delete pMove; //最后一个
	pMove = NULL;
}

QueueNode::~QueueNode()
{
	//cout << this->nID<<" Queue Node des." << endl;
}
