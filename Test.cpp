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
	cout << "本实验内容为：有向图构建、最短路径查询及边介数查询." << endl;
	cout << "请问是否已调整读入文件的位置？ (1表示是，其他表示否): ";
	int nContinue = 0;
	cin >> nContinue;
	if (nContinue != 1)
	{
		cout << "请调整读入文件的位置！" << endl;
		return 0;
	}
	/*读入Node文件*/
	Node *pNodeHead = new Node;	//标记表头
	int nTotalNumOfNode = ReadAndCreateNode(pNodeHead);

	/*读入Road文件*/
	Road *pRoadHead = new Road;	//标记表头
	int nTotalNumOfRoad = ReadAndCreateRoad(pRoadHead);

	/*建立邻接表*/
	ALGraph Graph;	//建立结构体ALGraph
	ALGraph *pGraph = &Graph;	//用指针传递Graph的位置
	clock_t start0, finish0;
	double totaltime0;
	start0 = clock();	//开始计时
	CreateALGraph(pGraph, pNodeHead, pRoadHead, nTotalNumOfNode, nTotalNumOfRoad);
	finish0 = clock();	//结束计时
	totaltime0 = (double)(finish0 - start0) / CLOCKS_PER_SEC*1000.0;
	cout << "1. 有向图建立完毕. " << "运行时间为 " << totaltime0 << " ms." << endl << endl;
	/*图建立完毕*/
	
	/*释放Node和Road空间*/
	DeleteNode(pNodeHead);
	DeleteRoad(pRoadHead);
	
	/*遍历全图并输出*/
	//OutputALGraph(pGraph, nTotalNumOfNode);

	/*最短路径及边介数*/
	cout << "2. 最短路径、边介数计算." << endl;
	clock_t start, finish;
	double totaltime;
	start = clock();	//开始计时
	Dijkstra(pGraph, nTotalNumOfNode);// nTotalNumOfRoad, pRoadHead);	//核心算法
	finish = clock();	//结束计时
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC*1000.0;
	cout << "计算完毕，运行时间为 " << totaltime << " ms." << endl << endl;
	/*算法结束，输出时间为24s±，可查询任意两点间最短路径*/


	/*循环查询最短路径*/
	cout << "3. 查询两个节点的最短路径.\n请输入节点序号.\n";
	int Vertex1 = 0, Vertex2 = 0;
	int nKeepSearching = 1;
	while (nKeepSearching == 1)
	{
		cout << "节点 1: "; cin >> Vertex1;
		cout << "节点 2: "; cin >> Vertex2;
		if (Vertex1 == Vertex2) 
			cout << "节点序号相同!";
		else
		{
			clock_t start, finish;
			double totaltime;
			start = clock();	//开始计时

			/*查询最短路径*/
			SearchForDistanceAndPath(pGraph, Vertex1, Vertex2);
			
			finish = clock();	//结束计时
			totaltime = (double)(finish - start) / CLOCKS_PER_SEC*1000.0;
			cout << "查询运行时间为 " << totaltime << " ms." << endl << endl;
		}
		cout << "\n是否继续查询?\n1表示是，其他表示否： ";
		cin >> nKeepSearching;
	}

	/*循环查询边介数*/
	int nBegin = 0, nEnd = 0;
	int nKeepSearching_Betweenness = 1;
	int nBetweenness = 0;
	while (nKeepSearching_Betweenness==1)
	{
		cout << "\n4. 查询某条边的边介数.\n请输入起始点: ";
		cin >> nBegin;
		cout << "请输入终止点: "; cin >> nEnd;

		clock_t start, finish;
		double totaltime;
		start = clock();	//开始计时

		/*查询边介数*/
		nBetweenness = SearchForBetweennessOfOneRoad_OnGraph(pGraph, nBegin, nEnd);

		finish = clock();	//结束计时
		totaltime = (double)(finish - start) / CLOCKS_PER_SEC*1000.0;
		cout << "查询运行时间为 " << totaltime << " ms." << endl << endl;

		if (nBetweenness == -1)
		{cout << "这两个点没有直接相连！" << endl
			<< "是否继续查询？1表示是，其他表示否：" << endl;
		cin >> nKeepSearching_Betweenness;
	}
		else
		{
			cout << "边介数为: " << nBetweenness << endl
				<< "是否继续查询？1表示是，其他表示否：" << endl;
			cin >> nKeepSearching_Betweenness;
		}
	}
	cout << "\n5. 输出含边介数信息的路网文件.\n是否已调整输出路径？ 1表示是，其他为否：";
	cin >> nContinue;
	if (nContinue != 1)
		return 0;
	clock_t start5, finish5;
	double totaltime5;
	start5 = clock();	//开始计时

	/*输出带有边介数的边表信息*/
	int nIDLastRoad = WriteRoad(pGraph);

	finish5 = clock();	//结束计时
	totaltime5 = (double)(finish5 - start5) / CLOCKS_PER_SEC*1000.0;
	cout << "输出用时为 " << totaltime5 << " ms." << endl << endl;
	//cout << "共有"<<nIDLastRoad<<"条边"<<endl;
	
	/*第3题，社区识别*/

	/*最后，释放有向图的空间*/
	clock_t start6, finish6;
	double totaltime6;
	start6 = clock();	//开始计时
	
	DeleteALGraph(pGraph);
	
	finish6 = clock();	//结束计时
	totaltime6 = (double)(finish6 - start6) / CLOCKS_PER_SEC*1000.0;
	cout << "释放空间用时 " << totaltime6 << " ms." << endl << endl;

		return 0;
	
}