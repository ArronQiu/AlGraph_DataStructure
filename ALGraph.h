#pragma once
#include <iostream>
#include <stdio.h>
#include "Node_and_Road.h"
#include "Queue.h"

using namespace std;

typedef struct GraphNode //边表结点
{
	int nAdjv;		//邻接点域
	float fLength = 0;			//相当于权重weight;
	int nBetweenness = 0;	//连接其和其顶点的边的边介数
	float fLatitude;
	float fLongtitude;
	bool bIsOneWay;
	struct GraphNode *pNext;	//指向下一个邻接点的指针域
}EdgeNode;

typedef int VertexType;	//顶点用FID表示

typedef struct Vnode	//顶点表结点
{
	VertexType nVertex;		//顶点域
	float fLatitude;
	float fLongtitude;
	EdgeNode *pFirstEdge=NULL;	//指向第一条邻接边的指针域,即边表头指针
								//可以初始化为NULL?
}VertexNode;

struct OtherNode //组成D[]
{
	int nID;
	float fLength;
};

struct ALGraph
{
	VertexNode *pALGraphHead; //顶点表
	OtherNode **ppDistance; //记录顶点间最短距离
	int **ppPrevID; //记录最短路径父顶点
	int n, e;			//顶点数和边数
};

void CreateALGraph(ALGraph *pGhead, Node *pNodeHead, Road *pRoadHead,int nTotalNumOfNode, int nTotalNumOfRoad);
void OutputALGraph(ALGraph *pGhead, int nTotalNumOfNode);
void DeleteALGraph(ALGraph *pGraph);
void DeleteEdgeList(EdgeNode *pHead);
void Dijkstra(ALGraph *G, int nTotalNumOfNode); //, int nTotalNumOfRoad, Road *pRoad);
void SearchForDistanceAndPath(ALGraph *Graph, int Vertex1, int Vertex2);
int SearchForBetweennessOfOneRoad_OnGraph(ALGraph *pGraph, int nIDBegin, int nIDEnd);