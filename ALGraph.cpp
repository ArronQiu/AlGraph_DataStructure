#include "ALGraph.h"
#include "Queue.h"
#include <iostream>
#include "Node_and_Road.h"
using namespace std;
#define INFINITY 100000

void CreateALGraph(ALGraph * pGraph, Node *pNodeHead, Road *pRoadHead, int nTotalNumOfNode, int nTotalNumOfRoad)
{
	pGraph->n = nTotalNumOfNode;
	pGraph->e = nTotalNumOfRoad;
	pGraph->pALGraphHead = new VertexNode[nTotalNumOfNode];
	pGraph->ppDistance = new  OtherNode *[nTotalNumOfNode];
	pGraph->ppPrevID = new int *[nTotalNumOfNode];
	int _nIniGraphMartrix = 0; //���ڳ�ʼ���ڽӱ�Ԫ��
	for (_nIniGraphMartrix = 0; _nIniGraphMartrix<nTotalNumOfNode; _nIniGraphMartrix++)
	{
		pGraph->pALGraphHead[_nIniGraphMartrix].nVertex = _nIniGraphMartrix;
		pGraph->ppDistance[_nIniGraphMartrix] = new OtherNode[nTotalNumOfNode];
		pGraph->ppPrevID[_nIniGraphMartrix] = new int[nTotalNumOfNode];
	}

	/*��ʵ�˴���һ����Ҫ��Щ����¼��������������ϰ����ˣ��о�������ѭ�����Եø����*/
	float fLongtitudeOut;	//��¼��㾭γ��
	float fLatitudeOut;
	float fLongtitudeIn;	//��¼�յ㾭γ��
	float fLatitudeIn;
	bool bIsOneWay;
	int nIdOut;	//��¼���ID
	int nIdIn;	//��¼�յ�ID
	int numOfThisVertex = 0;	//���ǵڼ�������
	Node *pNodeMove = pNodeHead->pNext; //����������Node��Road���˶���ָ��
	Road *pRoadMove = pRoadHead->pNext;
	Node *pNodeMoveForPointY = pNodeMove;	//Ϊ��ƥ���յ㣬����ʼ��Ϊ��ͷ
	EdgeNode *pEdge;	//�߱�

	while (pRoadMove != NULL) //����·�������յ㣬ƥ���Ӧ�Ķ���
	{
		
		fLongtitudeOut = pRoadMove->fLongtitudeOut;
		fLatitudeOut = pRoadMove->fLatitudeOut;
		fLongtitudeIn = pRoadMove->fLongtitudeIn;
		fLatitudeIn = pRoadMove->fLatitudeIn;
		bIsOneWay = pRoadMove->bIsOneWay;

		while (pNodeMove != NULL)	//��ƥ����㣬�������յ�
									/*���ĳ����ֻ���յ㣬�޷�matchҲ��Ҫ���*/
		{
			if ((fLongtitudeOut == pNodeMove->fLongitude) && (fLatitudeOut == pNodeMove->fLatitude))	//�ҵ�����
			{
				nIdOut = pNodeMove->nFID;
				if (pGraph->pALGraphHead[nIdOut].nVertex != nIdOut) //���δ������ֵ
				{
					pGraph->pALGraphHead[nIdOut].nVertex = nIdOut; //��������
					pRoadMove->nIDBegin = nIdOut; //��¼�����ߵ����
					pGraph->pALGraphHead[nIdOut].fLatitude = fLatitudeOut;	//��¼��γ��
					pGraph->pALGraphHead[nIdOut].fLongtitude = fLongtitudeOut;
				}

				/*��Node��Ѱ�Ҷ�Ӧ���ڽӵ�*/
				while (pNodeMoveForPointY != NULL)
				{
					if ((fLongtitudeIn == pNodeMoveForPointY->fLongitude) && (fLatitudeIn == pNodeMoveForPointY->fLatitude))
					{
						nIdIn = pNodeMoveForPointY->nFID;
						pEdge = new EdgeNode;
						pEdge->nAdjv = nIdIn; //��¼���
						pEdge->fLength = pRoadMove->fLength;	//��¼����
						pEdge->bIsOneWay = bIsOneWay;	//��¼��˫��
						pEdge->fLatitude = fLatitudeIn;	//��¼��γ��
						pEdge->fLongtitude = fLongtitudeIn;
						pEdge->pNext = pGraph->pALGraphHead[nIdOut].pFirstEdge;	//�����ͷ(1)
						pGraph->pALGraphHead[nIdOut].pFirstEdge = pEdge; //�����ͷ(2)
						pRoadMove->nIDEnd = nIdIn; ////��¼�����ߵ��յ�
						break;
					}
					pNodeMoveForPointY = pNodeMoveForPointY->pNext;
				}
				if (bIsOneWay == false) //˫����Ҫ������һ����ӽ��EdgeNode
				{
					int _nTempID; //���յ㵹ת
					_nTempID = nIdIn;
					nIdIn = nIdOut;
					nIdOut = _nTempID;

					pGraph->pALGraphHead[nIdOut].nVertex = nIdOut;
					if (pGraph->pALGraphHead[nIdOut].pFirstEdge == NULL)//��ĳ���ֻ����һ��˫��road������ΪIn�㣬�����ڴ˶�����г�ʼ��(�ж�һ�α��ظ���ֵ��)
					{
						pGraph->pALGraphHead[nIdOut].fLatitude = fLatitudeIn;	
						pGraph->pALGraphHead[nIdOut].fLongtitude = fLongtitudeIn;
					}
					pEdge = new EdgeNode;
					pEdge->nAdjv = nIdIn; //��¼���
					pEdge->fLength = pRoadMove->fLength;//��¼����
					pEdge->fLatitude = fLatitudeOut;	//��¼��γ��
					pEdge->fLongtitude = fLongtitudeOut;
					pEdge->pNext = pGraph->pALGraphHead[nIdOut].pFirstEdge; //�����ͷ
					pGraph->pALGraphHead[nIdOut].pFirstEdge = pEdge; //�����ͷ2
					//˫����˴����ø����յ�

				}
				break;
			}
			else
				pNodeMove = pNodeMove->pNext;
		}
		pNodeMove = pNodeHead->pNext;
		pNodeMoveForPointY = pNodeMove->pNext;
		pRoadMove = pRoadMove->pNext;
	}
	/*���ڵ�3����Ҫ�������±߽��������Բ��ڴ˶�Graph��̬�����Ա��ʼ�������ǷŽ�Dijkstra��*/
}

void OutputALGraph(ALGraph * pGraph, int nTotalNumOfNode)
{
	EdgeNode *pGraphMove = pGraph->pALGraphHead[0].pFirstEdge;
	int numInpALGraphHead = 0; //�Ƕ����ڼ�������
	while (numInpALGraphHead<nTotalNumOfNode)
	{
		int numMove = 1;
		if (pGraph->pALGraphHead[numInpALGraphHead].nVertex)
			cout << "It's Vertex No." << pGraph->pALGraphHead[numInpALGraphHead].nVertex <<
			" with Lat "<< pGraph->pALGraphHead[numInpALGraphHead].fLatitude<<
			" and Lon "<< pGraph->pALGraphHead[numInpALGraphHead].fLongtitude<< endl;
		while (pGraphMove != NULL)
		{
			cout << "It's Road No." << numMove << " is connected to EdgeNode " << pGraphMove->nAdjv<<
				" with Lat " << pGraphMove->fLatitude <<
				" and Lon " << pGraphMove->fLongtitude<<
				" with Length: " << pGraphMove->fLength << endl;
			pGraphMove = pGraphMove->pNext;
			numMove++;
		}
		numInpALGraphHead++;
		pGraphMove = pGraph->pALGraphHead[numInpALGraphHead].pFirstEdge;
		cout << endl << endl;
	}
}

void DeleteALGraph(ALGraph *pGraph)
{
	int nVertex = 0; //�����ͷſռ�
	/*�ͷŶ����ͱ߱�*/
	for (nVertex = 0; nVertex < pGraph->n; nVertex++)
	{
		//cout << "Vertex"<<pGraph->pALGraphHead[nVertex].nVertex<<" :  ";
		//�ͷű߱�
		DeleteEdgeList(pGraph->pALGraphHead[nVertex].pFirstEdge); 
		//cout << "Des." << endl;
		pGraph->pALGraphHead[nVertex].pFirstEdge = NULL;
	}
	//�ͷŶ����
	delete[]pGraph->pALGraphHead; 

	/*�ͷ�D[]��P[]*/
	for (nVertex = 0; nVertex < pGraph->n; nVertex++)
	{
		//cout << "D[]:"<<pGraph->ppDistance[nVertex]->nID << endl;
		delete[]pGraph->ppDistance[nVertex];
		pGraph->ppDistance[nVertex] = NULL;
	}
	delete[]pGraph->ppDistance;
	pGraph->ppDistance = NULL;

	for (nVertex = 0; nVertex < pGraph->n; nVertex++)
	{
		//cout << "P[]:" << pGraph->ppPrevID[nVertex] << endl;;
		delete[]pGraph->ppPrevID[nVertex];
		pGraph->ppPrevID[nVertex] = NULL;
	}
	pGraph->ppPrevID = NULL;

}

void DeleteEdgeList(EdgeNode *pHead)
{
	EdgeNode *pMove = pHead;
	if (pHead!=NULL) //�ö���߱�Ϊ��
	{
		EdgeNode *pMoveNext = pHead->pNext;
		while (pMoveNext != NULL)
		{
			//cout << pMove->nAdjv << "  ";
			delete pMove;
			pMove = pMoveNext;
			pMoveNext = pMoveNext->pNext;
		}
		delete pMove; //���һ��
	}
	
}

void Dijkstra(ALGraph *pGraph, int nTotalNumOfNode)//,int nTotalNumOfRoad,Road *pRoad)
{
	/*��ʼ��Graph�Ķ�̬�����Ա��Distance �� Path�����ڹ������·��*/
	int i, j;
	for (i = 0; i < nTotalNumOfNode; i++)
		for (j = 0; j < nTotalNumOfNode; j++)
		{
			//pGraph->ppDistance[i][i]
			pGraph->ppDistance[i][j].fLength = INFINITY;
			pGraph->ppDistance[i][j].nID = j;
			pGraph->ppPrevID[i][j] = -1;	//ÿ�����㶼�޸��ڵ�
		}
	int nThisVertex = 0;
	int nIniVisit = 0;
	
	//���У����ζ�D��P����ĸ��н��д����õ�N���㵽N������ܾ��룬��ͨ��һ��������ʾ·��
	for (nThisVertex = 0; nThisVertex < nTotalNumOfNode; nThisVertex++)	/*��ѭ��*/
	{
		/*������ע��Ϊ�������������*/
		//cout << "This is Vertex " << nThisVertex << endl;
		int *pnFinal = new int[nTotalNumOfNode]; //�Ƿ��ҵ����·��

		for (nIniVisit = 0; nIniVisit < nTotalNumOfNode; nIniVisit++)
		{
			pnFinal[nIniVisit] = 0;	//��δ�ҵ����·��
			/*�Ƿ���Ҫ�����߱��Գ�ʼ��D��P��ֱ����ThisVertex���ӵĶ���*/
			/*����Ҫ����Ϊÿ����ѭ���µĵ�һ�α�������ʵ��*/
		}

		LinkQueue  *Q = new LinkQueue;	//����һ�����У����ڶ������ҵ�����V�е���̾���
		InitQueue(Q);
		pGraph->ppDistance[nThisVertex][nThisVertex].fLength = 0;	//ÿ�����㵽�Լ��ľ�����0
		EnQueue(Q, pGraph->ppDistance[nThisVertex][nThisVertex]); //��Ӳ�������
		QueueNode *pQMove = Q->front->pNext;	//������Debugʱ���Queue��Ԫ��

		while (!Empty(Q))
		{
			/*�鿴Q��Ԫ��*/
			/*cout << endl<< endl << "In Queue: ";
			pQMove = Q->front->pNext;
			while (pQMove != NULL)
			{
				cout << pQMove->nID<<"( "<<pQMove->fLength << " )  "; pQMove = pQMove->pNext;
			}*/

			QueueNode *cd = Q->front->pNext; //����һ��ָ�룬ָ����еĵ�һ��Ԫ��
			int nIdOfFirstQNode = cd->nID;	//T������ThisVertex������С�Ľ��ID���൱��w��ÿ�δ�������ȥ�����������
			if (pnFinal[nIdOfFirstQNode])
				continue;
			pnFinal[nIdOfFirstQNode] = 1;	//�õ��Ѿ��ҵ������·��
			DeQueue(Q); //T������
			
			int nIDSonNode = nIdOfFirstQNode; //�ߵ��յ�
			int nIDFatherNode = pGraph->ppPrevID[nThisVertex][nIDSonNode]; //�ߵ���㣬��Դʱ�䶯
			EdgeNode *pEdgeMove = pGraph->pALGraphHead[nIDFatherNode].pFirstEdge;	//���������ı߱�

			/*�߽�������*/
			/*��ֱ��++�����������*/
			if (nIDFatherNode != -1)	//��thisVertex�ĵ�һ������
			{
				while (pEdgeMove)
				{
					if (pEdgeMove->nAdjv == nIDSonNode)	//�ҵ��ߵ��յ�
					{
						pEdgeMove->nBetweenness++; break;
					}
					pEdgeMove = pEdgeMove->pNext;
				}
				nIDSonNode = nIDFatherNode;	//��Դ�������ӽڵ�
				nIDFatherNode = pGraph->ppPrevID[nThisVertex][nIDFatherNode];	//��Դ�����¸��ڵ�
				pEdgeMove = pGraph->pALGraphHead[nIDFatherNode].pFirstEdge;		//�����������
			}
			/*����Դ*/
			while (nIDFatherNode != -1)	//��û�ҵ�Դ�㣨Դ��ĸ��ڵ㱻��ʼ��Ϊ-1����CreateGraph()��
			{
				while (pEdgeMove)
				{
					if (pEdgeMove->nAdjv == nIDSonNode)
					{
						pEdgeMove->nBetweenness++; break;
					}
					pEdgeMove = pEdgeMove->pNext;
				}
				nIDSonNode = nIDFatherNode;	//��Դ�������ӽڵ�
				nIDFatherNode = pGraph->ppPrevID[nThisVertex][nIDFatherNode];	//��Դ�����¸��ڵ�
				pEdgeMove = pGraph->pALGraphHead[nIDFatherNode].pFirstEdge;		//�����������
			}
			/*�߽������½���*/

			/*���´�w�������ڽӵ�*/
			pEdgeMove = pGraph->pALGraphHead[nIdOfFirstQNode].pFirstEdge;

			//EdgeNode *pEdgeMove = pGraph->pALGraphHead[nIdOfFirstQNode].pFirstEdge; //Ϊ�˼������ʱ
			/*if(pEdgeMove!=NULL)
				cout << "\nVertex "<<nIdOfFirstQNode<<"---Start from Vertex " << pEdgeMove->nAdjv << endl;*/

			while (pEdgeMove)
			{
				int nTempVertex = pEdgeMove->nAdjv;
				float fTempLength = pEdgeMove->fLength;
				if (!pnFinal[nTempVertex] && //δ�ҵ����·��������V-S��
					(pGraph->ppDistance[nThisVertex][nTempVertex].fLength > pGraph->ppDistance[nThisVertex][nIdOfFirstQNode].fLength + fTempLength))
					//ĳ���temp���룬> ��This������w + ��w������temp����
				{
					//cout << "Vertex " << nTempVertex << ", ";
					pGraph->ppDistance[nThisVertex][nTempVertex].fLength = pGraph->ppDistance[nThisVertex][nIdOfFirstQNode].fLength + fTempLength;
					pGraph->ppPrevID[nThisVertex][nTempVertex] = nIdOfFirstQNode;
					EnQueue(Q, pGraph->ppDistance[nThisVertex][nTempVertex]); //������temp����temp���
				}
				pEdgeMove = pEdgeMove->pNext;
			}
			//cout << "changed.";
		}
		//�ͷŶ����ڽڵ���ռ�ռ�
		DeleteQueue(Q);
		delete Q;
		delete[]pnFinal;
		Q = NULL; pnFinal = NULL;
	}
}

void SearchForDistanceAndPath(ALGraph *pGraph, int Vertex1, int Vertex2)
{
	int PositionInPath = Vertex2;
	if (pGraph->ppDistance[Vertex1][Vertex2].fLength == INFINITY)
	{

		cout << "They are not linked to each other." << endl;
	}
	else
	{
		cout << endl<< Vertex1 << " and " << Vertex2 << endl;
		cout << "The Distance is: " << pGraph->ppDistance[Vertex1][Vertex2].fLength << endl;
		cout << "The Path is: " << Vertex2;
		while (1)
		{
			//nHowManyArcInThisPath++;
			cout << " <- ";
			cout << pGraph->ppPrevID[Vertex1][PositionInPath];
			PositionInPath = pGraph->ppPrevID[Vertex1][PositionInPath];
			
			if (pGraph->ppPrevID[Vertex1][PositionInPath] == -1)
				break;
		}
		cout << endl;
	}
	
}

/*��ӣ���N��N�����ѯ�����·��������һ�������ĵ㣬�Ͳ�ѯ��Ӧ��·����++�������ĸ��ڵ��Ƕ�·*/

int SearchForBetweennessOfOneRoad_OnGraph(ALGraph *pGraph, int nIDBegin, int nIDEnd)
{
	/*�ȿ����������Ƿ�ֱ������*/
	EdgeNode *pEdgeMove = pGraph->pALGraphHead[nIDBegin].pFirstEdge;
	while (pEdgeMove)
	{
		if (pEdgeMove->nAdjv == nIDEnd)
			break;
		else
			pEdgeMove = pEdgeMove->pNext;
	}
	if (pEdgeMove == NULL)
	{
		return -1;
	}
	else
	{
		return pEdgeMove->nBetweenness;
	}


}
//
//int SearchForBetweennessOfOneRoad_OnRoad(ALGraph *pGraph, Road *pRoadHead,int nIDBegin, int nIDEnd)
//{
//	/*�������Ҫ�ڼ������·��ʱ��ÿ����һ���ߣ��ñߵı߽���++*/
//	/*1. ʶ��ñߣ��������·��ʱ��NodeID�����ͨ�����������Ҷ�Ӧ��Road��*/
//	/*�ܷ��Road����IDBegin������ͷֿ�������*//*���ı�RoadID ? RoadID����Ҫ��*/
//}


/*�Ե�3����뷨�ļ�¼*/
/*1. ɾ���߽�����ߵı�*/
/*1.1. һ��ʼ�����б߾ͱ߽������зֿ����򣿵����¼�����Ƿ��ܴ��Ӱ��߽����أ������ᣬ������Ч����Ӱ��󣬲���ֻ���㲻���򣬲��������ֵ��*/
/*1.2. ɾ���ߣ�[���мܹ�]�Ļ���ʶ�����󴦺���һ��ָ��Ӷ�����������ǰ�ڵ㣬ָ��任��delete�����õ�һ����ͼ*/
/*1.3. �õ���ͼ�����µ��ñ߽������㺯�����ظ���������*/
/*2. ʲôʱ���ǽڵ�(��������)��Community Belong��*/
/*2.1. �����Ӹõ�ıߵı߽��� < [��ֵ]�������[�½�����]ʱ��*/
/*2.2. ��ͨ��һ������������ĳ���ڵ��������֮�����Ľڵ㣬���Ϊͬһ����������ĳ�ڵ��ѱ���ǹ�������һ��*/

/*����ʶ�𣬴�ͳGN�㷨*/
/*
1. �������б߽���
2. �Ƴ��߽�����ߵı�
3. ���¼������б߽���
4. �ص���2��ֱ�����б߱��Ƴ�	//�൱�ڵ��������ײ��������Ա
5. ѭ������Ҫ��Ǳ���������
*/

/*���к���δʵ�飬��Ϊ�ݸ�*/
/*���붥�㼰�ڽӵ�λ�ã���ɾ�����ñ�*/
/*����ɾ���ñߣ��Ҳ����ڵ㣬����������ڵ�ľ�����INFINITY*/
void DeleteCommunityRoad(ALGraph *pGraph,int nVertex, EdgeNode * pEdgePosHighBet)
{

	EdgeNode *pEdgeMove = pGraph->pALGraphHead[nVertex].pFirstEdge;
	while (pEdgeMove!=NULL)
	{
		if (pEdgeMove->pNext == pEdgePosHighBet)
			break;
		else pEdgeMove = pEdgeMove->pNext;
	}
	pEdgeMove->fLength = INFINITY;
	/*��¼��ɾ���Ĳ��*/
	

	/*pEdgeMove = pEdgePosHighBet->pNext;
	delete[]pEdgePosHighBet;
	pEdgePosHighBet = NULL;*/
}

//void QuickSort_Betweenness()
/*�򵥲��ұ߽�����ߵ�·����ɾ��*/
int * DeleteHighestBetweenness(ALGraph *pGraph)
{
	int nIDRoadTwoNode[2] = { 0 };
	int nVertex = 0;
	int nHighestBetweenness = 0;
	EdgeNode *pEdgeMove = NULL;
	EdgeNode *pEdgePosHighBet = NULL;
	int nPosVertexHighBet;
	while (nVertex < pGraph->n - 1)
	{
		pEdgeMove = pGraph->pALGraphHead[nVertex].pFirstEdge;
		while (pEdgeMove != NULL)
		{
			if (nHighestBetweenness < pEdgeMove->nBetweenness)
			{
				nHighestBetweenness = pEdgeMove->nBetweenness;
				pEdgePosHighBet = pEdgeMove;
				nPosVertexHighBet = nVertex;
			}
			pEdgeMove = pEdgeMove->pNext;
		}
		nVertex++;
	}
	//return pEdgePosHighBet;
	nIDRoadTwoNode[1] = pEdgePosHighBet->nAdjv;	//��¼����
	DeleteCommunityRoad(pGraph,nPosVertexHighBet, pEdgePosHighBet);	//ɾ��·��
	nIDRoadTwoNode[0] = nPosVertexHighBet;	//��¼����
	return nIDRoadTwoNode;
}

void CommunityIdentify(ALGraph *pGraph)
{
	int *pnIDRoadTwoNode;
	int nLevelOfBetweenness; //��¼��ɾ��ʱ������Σ���Ϊ�������������һ����Χ�ڵģ�Ϊͳһ����
	//���⣺�������һ��Ļ���������һ���أ�
	//����ʹ����״�ṹ����ÿ��ɾȥ�Ľڵ��Ž�һ�������棿
	while (1)	//������
	{
		pnIDRoadTwoNode = DeleteHighestBetweenness( pGraph);
		Dijkstra(pGraph, pGraph->n - 1);	//���¼���߽���
		cout << "Road between " << pnIDRoadTwoNode[0] << " and " << pnIDRoadTwoNode[1] << " deleted." << endl;
	}
}