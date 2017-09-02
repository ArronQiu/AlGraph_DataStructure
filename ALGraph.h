#pragma once
#include <iostream>
#include <stdio.h>
#include "Node_and_Road.h"
#include "Queue.h"

using namespace std;

typedef struct GraphNode //�߱���
{
	int nAdjv;		//�ڽӵ���
	float fLength = 0;			//�൱��Ȩ��weight;
	int nBetweenness = 0;	//��������䶥��ıߵı߽���
	float fLatitude;
	float fLongtitude;
	bool bIsOneWay;
	struct GraphNode *pNext;	//ָ����һ���ڽӵ��ָ����
}EdgeNode;

typedef int VertexType;	//������FID��ʾ

typedef struct Vnode	//�������
{
	VertexType nVertex;		//������
	float fLatitude;
	float fLongtitude;
	EdgeNode *pFirstEdge=NULL;	//ָ���һ���ڽӱߵ�ָ����,���߱�ͷָ��
								//���Գ�ʼ��ΪNULL?
}VertexNode;

struct OtherNode //���D[]
{
	int nID;
	float fLength;
};

struct ALGraph
{
	VertexNode *pALGraphHead; //�����
	OtherNode **ppDistance; //��¼�������̾���
	int **ppPrevID; //��¼���·��������
	int n, e;			//�������ͱ���
};

void CreateALGraph(ALGraph *pGhead, Node *pNodeHead, Road *pRoadHead,int nTotalNumOfNode, int nTotalNumOfRoad);
void OutputALGraph(ALGraph *pGhead, int nTotalNumOfNode);
void DeleteALGraph(ALGraph *pGraph);
void DeleteEdgeList(EdgeNode *pHead);
void Dijkstra(ALGraph *G, int nTotalNumOfNode); //, int nTotalNumOfRoad, Road *pRoad);
void SearchForDistanceAndPath(ALGraph *Graph, int Vertex1, int Vertex2);
int SearchForBetweennessOfOneRoad_OnGraph(ALGraph *pGraph, int nIDBegin, int nIDEnd);