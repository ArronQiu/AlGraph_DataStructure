#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "Queue.h"
#include "ALGraph.h"
#include "Node_and_Road.h"
#include "ReadAndWrite_NodeAndRoad.h"

#define INFINITY 100000

using namespace std;

int main()
{
	cout << "��ʵ������Ϊ������ͼ���������·����ѯ���߽�����ѯ." << endl;
	cout << "�����Ƿ��ѵ��������ļ���λ�ã� (1��ʾ�ǣ�������ʾ��): ";
	int nContinue = 0;
	cin >> nContinue;
	if (nContinue != 1)
	{
		cout << "����������ļ���λ�ã�" << endl;
		return 0;
	}
	/*����Node�ļ�*/
	Node *pNodeHead = new Node;	//��Ǳ�ͷ
	int nTotalNumOfNode = ReadAndCreateNode(pNodeHead);

	/*����Road�ļ�*/
	Road *pRoadHead = new Road;	//��Ǳ�ͷ
	int nTotalNumOfRoad = ReadAndCreateRoad(pRoadHead);

	/*�����ڽӱ�*/
	ALGraph Graph;	//�����ṹ��ALGraph
	ALGraph *pGraph = &Graph;	//��ָ�봫��Graph��λ��
	clock_t start0, finish0;
	double totaltime0;
	start0 = clock();	//��ʼ��ʱ
	CreateALGraph(pGraph, pNodeHead, pRoadHead, nTotalNumOfNode, nTotalNumOfRoad);
	finish0 = clock();	//������ʱ
	totaltime0 = (double)(finish0 - start0) / CLOCKS_PER_SEC*1000.0;
	cout << "1. ����ͼ�������. " << "����ʱ��Ϊ " << totaltime0 << " ms." << endl << endl;
	/*ͼ�������*/
	
	/*�ͷ�Node��Road�ռ�*/
	DeleteNode(pNodeHead);
	DeleteRoad(pRoadHead);
	
	/*����ȫͼ�����*/
	//OutputALGraph(pGraph, nTotalNumOfNode);

	/*���·�����߽���*/
	cout << "2. ���·�����߽�������." << endl;
	clock_t start, finish;
	double totaltime;
	start = clock();	//��ʼ��ʱ
	Dijkstra(pGraph, nTotalNumOfNode);// nTotalNumOfRoad, pRoadHead);	//�����㷨
	finish = clock();	//������ʱ
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC*1000.0;
	cout << "������ϣ�����ʱ��Ϊ " << totaltime << " ms." << endl << endl;
	/*�㷨���������ʱ��Ϊ24s�����ɲ�ѯ������������·��*/


	/*ѭ����ѯ���·��*/
	cout << "3. ��ѯ�����ڵ�����·��.\n������ڵ����.\n";
	int Vertex1 = 0, Vertex2 = 0;
	int nKeepSearching = 1;
	while (nKeepSearching == 1)
	{
		cout << "�ڵ� 1: "; cin >> Vertex1;
		cout << "�ڵ� 2: "; cin >> Vertex2;
		if (Vertex1 == Vertex2) 
			cout << "�ڵ������ͬ!";
		else
		{
			clock_t start, finish;
			double totaltime;
			start = clock();	//��ʼ��ʱ

			/*��ѯ���·��*/
			SearchForDistanceAndPath(pGraph, Vertex1, Vertex2);
			
			finish = clock();	//������ʱ
			totaltime = (double)(finish - start) / CLOCKS_PER_SEC*1000.0;
			cout << "��ѯ����ʱ��Ϊ " << totaltime << " ms." << endl << endl;
		}
		cout << "\n�Ƿ������ѯ?\n1��ʾ�ǣ�������ʾ�� ";
		cin >> nKeepSearching;
	}

	/*ѭ����ѯ�߽���*/
	int nBegin = 0, nEnd = 0;
	int nKeepSearching_Betweenness = 1;
	int nBetweenness = 0;
	while (nKeepSearching_Betweenness==1)
	{
		cout << "\n4. ��ѯĳ���ߵı߽���.\n��������ʼ��: ";
		cin >> nBegin;
		cout << "��������ֹ��: "; cin >> nEnd;

		clock_t start, finish;
		double totaltime;
		start = clock();	//��ʼ��ʱ

		/*��ѯ�߽���*/
		nBetweenness = SearchForBetweennessOfOneRoad_OnGraph(pGraph, nBegin, nEnd);

		finish = clock();	//������ʱ
		totaltime = (double)(finish - start) / CLOCKS_PER_SEC*1000.0;
		cout << "��ѯ����ʱ��Ϊ " << totaltime << " ms." << endl << endl;

		if (nBetweenness == -1)
		{cout << "��������û��ֱ��������" << endl
			<< "�Ƿ������ѯ��1��ʾ�ǣ�������ʾ��" << endl;
		cin >> nKeepSearching_Betweenness;
	}
		else
		{
			cout << "�߽���Ϊ: " << nBetweenness << endl
				<< "�Ƿ������ѯ��1��ʾ�ǣ�������ʾ��" << endl;
			cin >> nKeepSearching_Betweenness;
		}
	}
	cout << "\n5. ������߽�����Ϣ��·���ļ�.\n�Ƿ��ѵ������·���� 1��ʾ�ǣ�����Ϊ��";
	cin >> nContinue;
	if (nContinue != 1)
		return 0;
	clock_t start5, finish5;
	double totaltime5;
	start5 = clock();	//��ʼ��ʱ

	/*������б߽����ı߱���Ϣ*/
	int nIDLastRoad = WriteRoad(pGraph);

	finish5 = clock();	//������ʱ
	totaltime5 = (double)(finish5 - start5) / CLOCKS_PER_SEC*1000.0;
	cout << "�����ʱΪ " << totaltime5 << " ms." << endl << endl;
	//cout << "����"<<nIDLastRoad<<"����"<<endl;
	
	/*��3�⣬����ʶ��*/

	/*����ͷ�����ͼ�Ŀռ�*/
	clock_t start6, finish6;
	double totaltime6;
	start6 = clock();	//��ʼ��ʱ
	
	DeleteALGraph(pGraph);
	
	finish6 = clock();	//������ʱ
	totaltime6 = (double)(finish6 - start6) / CLOCKS_PER_SEC*1000.0;
	cout << "�ͷſռ���ʱ " << totaltime6 << " ms." << endl << endl;

		return 0;
	
}