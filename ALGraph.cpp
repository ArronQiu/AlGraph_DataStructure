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
	int _nIniGraphMartrix = 0; //用于初始化邻接表元素
	for (_nIniGraphMartrix = 0; _nIniGraphMartrix<nTotalNumOfNode; _nIniGraphMartrix++)
	{
		pGraph->pALGraphHead[_nIniGraphMartrix].nVertex = _nIniGraphMartrix;
		pGraph->ppDistance[_nIniGraphMartrix] = new OtherNode[nTotalNumOfNode];
		pGraph->ppPrevID[_nIniGraphMartrix] = new int[nTotalNumOfNode];
	}

	/*其实此处不一定需要这些“记录变量”，但个人习惯如此，感觉这样在循环内显得更简洁*/
	float fLongtitudeOut;	//记录起点经纬度
	float fLatitudeOut;
	float fLongtitudeIn;	//记录终点经纬度
	float fLatitudeIn;
	bool bIsOneWay;
	int nIdOut;	//记录起点ID
	int nIdIn;	//记录终点ID
	int numOfThisVertex = 0;	//这是第几个顶点
	Node *pNodeMove = pNodeHead->pNext; //创建两个在Node和Road里运动的指针
	Road *pRoadMove = pRoadHead->pNext;
	Node *pNodeMoveForPointY = pNodeMove;	//为了匹配终点，并初始化为表头
	EdgeNode *pEdge;	//边表

	while (pRoadMove != NULL) //根据路网的起终点，匹配对应的顶点
	{
		
		fLongtitudeOut = pRoadMove->fLongtitudeOut;
		fLatitudeOut = pRoadMove->fLatitudeOut;
		fLongtitudeIn = pRoadMove->fLongtitudeIn;
		fLatitudeIn = pRoadMove->fLatitudeIn;
		bIsOneWay = pRoadMove->bIsOneWay;

		while (pNodeMove != NULL)	//先匹配起点，再搜索终点
									/*如果某个点只做终点，无法match也需要输出*/
		{
			if ((fLongtitudeOut == pNodeMove->fLongitude) && (fLatitudeOut == pNodeMove->fLatitude))	//找到顶点
			{
				nIdOut = pNodeMove->nFID;
				if (pGraph->pALGraphHead[nIdOut].nVertex != nIdOut) //如果未曾被赋值
				{
					pGraph->pALGraphHead[nIdOut].nVertex = nIdOut; //顶点表起点
					pRoadMove->nIDBegin = nIdOut; //记录这条边的起点
					pGraph->pALGraphHead[nIdOut].fLatitude = fLatitudeOut;	//记录经纬度
					pGraph->pALGraphHead[nIdOut].fLongtitude = fLongtitudeOut;
				}

				/*在Node中寻找对应的邻接点*/
				while (pNodeMoveForPointY != NULL)
				{
					if ((fLongtitudeIn == pNodeMoveForPointY->fLongitude) && (fLatitudeIn == pNodeMoveForPointY->fLatitude))
					{
						nIdIn = pNodeMoveForPointY->nFID;
						pEdge = new EdgeNode;
						pEdge->nAdjv = nIdIn; //记录点号
						pEdge->fLength = pRoadMove->fLength;	//记录长度
						pEdge->bIsOneWay = bIsOneWay;	//记录单双向
						pEdge->fLatitude = fLatitudeIn;	//记录经纬度
						pEdge->fLongtitude = fLongtitudeIn;
						pEdge->pNext = pGraph->pALGraphHead[nIdOut].pFirstEdge;	//插入表头(1)
						pGraph->pALGraphHead[nIdOut].pFirstEdge = pEdge; //插入表头(2)
						pRoadMove->nIDEnd = nIdIn; ////记录这条边的终点
						break;
					}
					pNodeMoveForPointY = pNodeMoveForPointY->pNext;
				}
				if (bIsOneWay == false) //双向，需要在另外一方添加结点EdgeNode
				{
					int _nTempID; //起终点倒转
					_nTempID = nIdIn;
					nIdIn = nIdOut;
					nIdOut = _nTempID;

					pGraph->pALGraphHead[nIdOut].nVertex = nIdOut;
					if (pGraph->pALGraphHead[nIdOut].pFirstEdge == NULL)//若某结点只连接一条双向road，且作为In点，则需在此对其进行初始化(判断一次比重复赋值快)
					{
						pGraph->pALGraphHead[nIdOut].fLatitude = fLatitudeIn;	
						pGraph->pALGraphHead[nIdOut].fLongtitude = fLongtitudeIn;
					}
					pEdge = new EdgeNode;
					pEdge->nAdjv = nIdIn; //记录点号
					pEdge->fLength = pRoadMove->fLength;//记录长度
					pEdge->fLatitude = fLatitudeOut;	//记录经纬度
					pEdge->fLongtitude = fLongtitudeOut;
					pEdge->pNext = pGraph->pALGraphHead[nIdOut].pFirstEdge; //插入表头
					pGraph->pALGraphHead[nIdOut].pFirstEdge = pEdge; //插入表头2
					//双向，则此处不用更新终点

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
	/*由于第3题需要反复更新边介数，所以不在此对Graph动态矩阵成员初始化，而是放进Dijkstra里*/
}

void OutputALGraph(ALGraph * pGraph, int nTotalNumOfNode)
{
	EdgeNode *pGraphMove = pGraph->pALGraphHead[0].pFirstEdge;
	int numInpALGraphHead = 0; //是顶点表第几个顶点
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
	int nVertex = 0; //用于释放空间
	/*释放顶点表和边表*/
	for (nVertex = 0; nVertex < pGraph->n; nVertex++)
	{
		//cout << "Vertex"<<pGraph->pALGraphHead[nVertex].nVertex<<" :  ";
		//释放边表
		DeleteEdgeList(pGraph->pALGraphHead[nVertex].pFirstEdge); 
		//cout << "Des." << endl;
		pGraph->pALGraphHead[nVertex].pFirstEdge = NULL;
	}
	//释放顶点表
	delete[]pGraph->pALGraphHead; 

	/*释放D[]和P[]*/
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
	if (pHead!=NULL) //该顶点边表不为空
	{
		EdgeNode *pMoveNext = pHead->pNext;
		while (pMoveNext != NULL)
		{
			//cout << pMove->nAdjv << "  ";
			delete pMove;
			pMove = pMoveNext;
			pMoveNext = pMoveNext->pNext;
		}
		delete pMove; //最后一个
	}
	
}

void Dijkstra(ALGraph *pGraph, int nTotalNumOfNode)//,int nTotalNumOfRoad,Road *pRoad)
{
	/*初始化Graph的动态矩阵成员：Distance 和 Path，用于构建最短路径*/
	int i, j;
	for (i = 0; i < nTotalNumOfNode; i++)
		for (j = 0; j < nTotalNumOfNode; j++)
		{
			//pGraph->ppDistance[i][i]
			pGraph->ppDistance[i][j].fLength = INFINITY;
			pGraph->ppDistance[i][j].nID = j;
			pGraph->ppPrevID[i][j] = -1;	//每个顶点都无父节点
		}
	int nThisVertex = 0;
	int nIniVisit = 0;
	
	//按行，依次对D和P矩阵的各行进行处理，得到N个点到N个点的总距离，并通过一个方法显示路径
	for (nThisVertex = 0; nThisVertex < nTotalNumOfNode; nThisVertex++)	/*主循环*/
	{
		/*部分批注是为了输出其计算过程*/
		//cout << "This is Vertex " << nThisVertex << endl;
		int *pnFinal = new int[nTotalNumOfNode]; //是否找到最短路径

		for (nIniVisit = 0; nIniVisit < nTotalNumOfNode; nIniVisit++)
		{
			pnFinal[nIniVisit] = 0;	//都未找到最短路径
			/*是否需要遍历边表以初始化D和P中直接与ThisVertex连接的顶点*/
			/*不需要，因为每次主循环下的第一次遍历可以实现*/
		}

		LinkQueue  *Q = new LinkQueue;	//申请一个队列，并在队列内找到集合V中的最短距离
		InitQueue(Q);
		pGraph->ppDistance[nThisVertex][nThisVertex].fLength = 0;	//每个顶点到自己的距离是0
		EnQueue(Q, pGraph->ppDistance[nThisVertex][nThisVertex]); //入队参与排序
		QueueNode *pQMove = Q->front->pNext;	//仅用作Debug时输出Queue内元素

		while (!Empty(Q))
		{
			/*查看Q内元素*/
			/*cout << endl<< endl << "In Queue: ";
			pQMove = Q->front->pNext;
			while (pQMove != NULL)
			{
				cout << pQMove->nID<<"( "<<pQMove->fLength << " )  "; pQMove = pQMove->pNext;
			}*/

			QueueNode *cd = Q->front->pNext; //创建一个指针，指向队列的第一个元素
			int nIdOfFirstQNode = cd->nID;	//T集内离ThisVertex距离最小的结点ID，相当于w，每次从它出发去更新其他结点
			if (pnFinal[nIdOfFirstQNode])
				continue;
			pnFinal[nIdOfFirstQNode] = 1;	//该点已经找到了最短路径
			DeQueue(Q); //T集更新
			
			int nIDSonNode = nIdOfFirstQNode; //边的终点
			int nIDFatherNode = pGraph->ppPrevID[nThisVertex][nIDSonNode]; //边的起点，溯源时变动
			EdgeNode *pEdgeMove = pGraph->pALGraphHead[nIDFatherNode].pFirstEdge;	//搜索边起点的边表

			/*边介数计算*/
			/*先直接++最近的这条边*/
			if (nIDFatherNode != -1)	//非thisVertex的第一次运算
			{
				while (pEdgeMove)
				{
					if (pEdgeMove->nAdjv == nIDSonNode)	//找到边的终点
					{
						pEdgeMove->nBetweenness++; break;
					}
					pEdgeMove = pEdgeMove->pNext;
				}
				nIDSonNode = nIDFatherNode;	//溯源，更新子节点
				nIDFatherNode = pGraph->ppPrevID[nThisVertex][nIDFatherNode];	//溯源，更新父节点
				pEdgeMove = pGraph->pALGraphHead[nIDFatherNode].pFirstEdge;		//逐个顶点搜索
			}
			/*再溯源*/
			while (nIDFatherNode != -1)	//还没找到源点（源点的父节点被初始化为-1，见CreateGraph()）
			{
				while (pEdgeMove)
				{
					if (pEdgeMove->nAdjv == nIDSonNode)
					{
						pEdgeMove->nBetweenness++; break;
					}
					pEdgeMove = pEdgeMove->pNext;
				}
				nIDSonNode = nIDFatherNode;	//溯源，更新子节点
				nIDFatherNode = pGraph->ppPrevID[nThisVertex][nIDFatherNode];	//溯源，更新父节点
				pEdgeMove = pGraph->pALGraphHead[nIDFatherNode].pFirstEdge;		//逐个顶点搜索
			}
			/*边介数更新结束*/

			/*更新从w出发的邻接点*/
			pEdgeMove = pGraph->pALGraphHead[nIdOfFirstQNode].pFirstEdge;

			//EdgeNode *pEdgeMove = pGraph->pALGraphHead[nIdOfFirstQNode].pFirstEdge; //为了检查而输出时
			/*if(pEdgeMove!=NULL)
				cout << "\nVertex "<<nIdOfFirstQNode<<"---Start from Vertex " << pEdgeMove->nAdjv << endl;*/

			while (pEdgeMove)
			{
				int nTempVertex = pEdgeMove->nAdjv;
				float fTempLength = pEdgeMove->fLength;
				if (!pnFinal[nTempVertex] && //未找到最短路径，属于V-S集
					(pGraph->ppDistance[nThisVertex][nTempVertex].fLength > pGraph->ppDistance[nThisVertex][nIdOfFirstQNode].fLength + fTempLength))
					//某结点temp距离，> 从This出发到w + 从w出发到temp距离
				{
					//cout << "Vertex " << nTempVertex << ", ";
					pGraph->ppDistance[nThisVertex][nTempVertex].fLength = pGraph->ppDistance[nThisVertex][nIdOfFirstQNode].fLength + fTempLength;
					pGraph->ppPrevID[nThisVertex][nTempVertex] = nIdOfFirstQNode;
					EnQueue(Q, pGraph->ppDistance[nThisVertex][nTempVertex]); //跟新了temp，让temp入队
				}
				pEdgeMove = pEdgeMove->pNext;
			}
			//cout << "changed.";
		}
		//释放队列内节点所占空间
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

/*最繁杂，对N对N个点查询其最短路径，遇到一个经过的点，就查询对应的路，并++它和它的父节点那段路*/

int SearchForBetweennessOfOneRoad_OnGraph(ALGraph *pGraph, int nIDBegin, int nIDEnd)
{
	/*先看这两个点是否直接相连*/
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
//	/*在这里，需要在计算最短路径时，每经过一条边，该边的边介数++*/
//	/*1. 识别该边：在求最短路径时看NodeID，则可通过索引法查找对应的Road？*/
//	/*能否对Road进行IDBegin的排序和分块索引？*//*不改变RoadID ? RoadID不重要吧*/
//}


/*对第3题的想法的记录*/
/*1. 删除边介数最高的边*/
/*1.1. 一开始对所有边就边介数进行分块排序？但重新计算后是否会很大地影响边介数呢？若不会，排序有效？有影响大，不如只计算不排序，并查找最大值？*/
/*1.2. 删除边？[现有架构]的话，识别出最大处后，让一个指针从顶点遍历到最大处前节点，指向变换后，delete掉，得到一幅新图*/
/*1.3. 得到新图后，重新调用边介数运算函数，重复上述过程*/
/*2. 什么时候标记节点(包括顶点)的Community Belong？*/
/*2.1. 当连接该点的边的边介数 < [阈值]，或符合[下降比例]时？*/
/*2.2. 再通过一个函数，计算某个节点出发能与之相连的节点，标记为同一个社区；若某节点已被标记过，则下一个*/

/*社区识别，传统GN算法*/
/*
1. 计算所有边介数
2. 移除边介数最高的边
3. 重新计算所有边介数
4. 回到第2步直到所有边被移除	//相当于到最基础最底层的社区成员
5. 循环后需要标记边所属社区
*/

/*下列函数未实验，仅为草稿*/
/*输入顶点及邻接点位置，“删除”该边*/
/*比起删除该边，找不到节点，不如让这个节点的距离变成INFINITY*/
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
	/*记录被删除的层次*/
	

	/*pEdgeMove = pEdgePosHighBet->pNext;
	delete[]pEdgePosHighBet;
	pEdgePosHighBet = NULL;*/
}

//void QuickSort_Betweenness()
/*简单查找边介数最高的路，并删除*/
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
	nIDRoadTwoNode[1] = pEdgePosHighBet->nAdjv;	//记录两端
	DeleteCommunityRoad(pGraph,nPosVertexHighBet, pEdgePosHighBet);	//删除路网
	nIDRoadTwoNode[0] = nPosVertexHighBet;	//记录两端
	return nIDRoadTwoNode;
}

void CommunityIdentify(ALGraph *pGraph)
{
	int *pnIDRoadTwoNode;
	int nLevelOfBetweenness; //记录被删除时所属层次，认为，若所属层次在一定范围内的，为统一社区
	//问题：如何用上一层的划分区分这一层呢？
	//考虑使用树状结构，将每次删去的节点存放进一个树里面？
	while (1)	//条件？
	{
		pnIDRoadTwoNode = DeleteHighestBetweenness( pGraph);
		Dijkstra(pGraph, pGraph->n - 1);	//重新计算边介数
		cout << "Road between " << pnIDRoadTwoNode[0] << " and " << pnIDRoadTwoNode[1] << " deleted." << endl;
	}
}