#include "Queue.h"
#include "ALGraph.h"
#include <iostream>
using namespace std;

int InitQueue(struct LinkQueue *Q) //��ʼ����ͷ���front�Ķ��У�ͨ��front,��һ����Ԫ�ؽڵ��rearʵ�ֿ������򣬴ﵽ���ȶ��е�Ŀ�ģ��������򡱣�
{
	Q->front = Q->rear = new QueueNode;
	if (!Q->front) return -1;
	Q->front->pNext = NULL;
	return 1;
}

void EnQueue(struct LinkQueue *Q, struct OtherNode Distance)
{
	/*������������ͬID�Ľڵ㣬���ýڵ������¹����룬����Ҫɾ����ȥ��*/
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
	QueueNode *pNewNode = new QueueNode; //����һ���µĶ��нڵ�
	pNewNode->nID = Distance.nID;
	pNewNode->fLength = Distance.fLength;

	/*��Ϊ���ǰ�����������Խ�������Ƚ�fLength�����ҵ������λ��*/
	QueueNode *pQMove;	//Ѱ��p�Ĳ���λ��
	pQMove = Q->front->pNext;
	pQMove_Prev = Q->front;
	/*�����Ż�Ϊ�۰���ҡ���ʱ�临�Ӷȱ�ΪO(log_2_N)*/
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
	pQMove_Prev->pNext = pNewNode; //����
	pNewNode->pNext = pQMove;

	//ȷ�������rearָ��ĩβ
	
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
	// �����в��գ���ɾ�� Q �Ķ�ͷԪ��
	if (Q->front == Q->rear) return; //����Ϊ�գ�ֱ���˳�
	QueueNode *p = Q->front->pNext;
	Q->front->pNext = p->pNext;
	if (Q->rear == p) Q->rear = Q->front;   //����ͷ�Ƕ�β����ɾ����rearָ��ͷ���
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
	
	//�ܷ�ֱ�� delete []Q ??
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
	delete pMove; //���һ��
	pMove = NULL;
}

QueueNode::~QueueNode()
{
	//cout << this->nID<<" Queue Node des." << endl;
}
