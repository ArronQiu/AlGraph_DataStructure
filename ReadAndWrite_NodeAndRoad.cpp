#include "ReadAndWrite_NodeAndRoad.h"
#include "ALGraph.h"
#include <string>
#include <fstream>
#include <stdlib.h>

/*直接传Road文件的话，边介数算法得重写*/
/*用ALGraph的话，顶点表和边表都需要存放经纬度信息，边表还要加个bIsOneWay*/
/*通过遍历ALGraph，写出.csv*/
int WriteRoad(ALGraph *pGraph)
{
	/*尚未解决的问题：to_string时精度损失*/
	
	ofstream outfile;
	outfile.open("E:\\Data Structure\\BigWork\\data\\RoadWithBetweenness.csv", ios::out);
	int nThisVertex = 0;
	int nID=0;
	float fLongtitude = 0.0;
	float fLatitude = 0.0;
	EdgeNode *pEdgeMove;
	outfile << "FID" << ',' << "oneway" << ',' << "length(m)" << ',' << "begingID,beginX,beginY,endID,endX,endY" << endl;
	while (!outfile.eof())
	{
		pEdgeMove = pGraph->pALGraphHead[nThisVertex].pFirstEdge;
		
		while (pEdgeMove!=NULL)
		{
			
			if (pGraph->pALGraphHead[nThisVertex].pFirstEdge->bIsOneWay == true)	//单向边
			{
				outfile << nID << ',';
				outfile << 1 << ',';
			outfile << pEdgeMove->fLength << ',';
			outfile << pGraph->pALGraphHead[nThisVertex].nVertex << ',';
			outfile << to_string(pGraph->pALGraphHead[nThisVertex].fLongtitude) << ',';
			outfile << to_string(pGraph->pALGraphHead[nThisVertex].fLatitude) << ',';
			outfile << pEdgeMove->nAdjv << ',';
			outfile << to_string(pEdgeMove->fLongtitude) << ',';
			outfile << to_string(pEdgeMove->fLatitude) << ',';
			outfile << pEdgeMove->nBetweenness << endl; //该行输入结束
				
			}
			else if (nThisVertex < pEdgeMove->nAdjv)	//首次遇到这条双向边
			{
				outfile << nID << ',';
				outfile << 0 << ',';
				outfile << pEdgeMove->fLength << ',';
				outfile << pGraph->pALGraphHead[nThisVertex].nVertex << ',';
				outfile << to_string(pGraph->pALGraphHead[nThisVertex].fLongtitude) << ',';
				outfile << to_string(pGraph->pALGraphHead[nThisVertex].fLatitude) << ',';
				outfile << pEdgeMove->nAdjv << ',';
				outfile << to_string(pEdgeMove->fLongtitude) << ',';
				outfile << to_string(pEdgeMove->fLatitude) << ',';
				outfile << pEdgeMove->nBetweenness << endl; //该行输入结束
			}
			//若非首次遇到这条双向边，则说明该边已经输出过
				pEdgeMove = pEdgeMove->pNext;
				nID++;
		}
		
		//cout << "The roads out from " << nThisVertex << " haved been output." << endl;
		nThisVertex++;	//该顶点的边输出完毕
		if (nThisVertex > pGraph->n-1) break;	//最后一个顶点的边输出完毕，此处与n比较要-1，以为序号从0开始

		/*问题：双向道路重复输出*/
	}
	cout << "含边介数信息的路网文件已输出." << endl;
	outfile.close();
	return nID-1;	/*返回最后一条边的序号*/
}

int ReadAndCreateNode(Node * pNodeHead)
{
	Node *pNodeMove = new Node;	//用于移动、new的指针
	pNodeHead->pNext = pNodeMove;	//连接起来
	char *buf;
	int nTotalNumOfNode = 0;	//总共有多少个节点

	ifstream infile;
	infile.open("E:\\Data Structure\\BigWork\\data\\node1.csv");

	/*读入Node文件*/
	//先读入表头各项
	char cFirstLine[60];	//存放每一行的字符
	infile.getline(cFirstLine, 50);	//读入第一行
									//cout << "The Node includes this infomation:\t";

	while (!infile.eof())
	{
		nTotalNumOfNode++;	//记录顶点个数

		char **_ppEachField = new char *[5];	//申请一个二维指针，分别存放不同字段的数据，初始化为空

		char _cReadEachLine[60];
		infile.getline(_cReadEachLine, 50); //存放每一行的字符
		_ppEachField[0] = strtok_s(_cReadEachLine, ",", &buf); //分割字符串，记录首个元素

		int _i = 0;
		while (_ppEachField[_i])
		{
			_i++;
			_ppEachField[_i] = strtok_s(NULL, ",", &buf);
		}
		_ppEachField[_i] = "\0";
		pNodeMove->nFID = atoi(_ppEachField[0]);
		pNodeMove->fLongitude = strtod(_ppEachField[1], NULL);
		pNodeMove->fLatitude = strtod(_ppEachField[2], NULL);
		pNodeMove->nJointCount = atoi(_ppEachField[3]);

		if (infile.eof()) break;
		pNodeMove->pNext = new Node;
		pNodeMove = pNodeMove->pNext;
		pNodeMove->pNext = NULL;

		/*释放内存*/
		//由于_ppEachField[i]和buf实际指向的是静态空间，无需也不能手动delete
		delete[]_ppEachField;
		_ppEachField = NULL;
	}
	infile.close();
	pNodeMove = pNodeHead->pNext;	//回到表头
	
	return nTotalNumOfNode;
}

int ReadAndCreateRoad(Road * pRoadHead)
{
	Road *pRoadMove = new Road;	//用于移动、new的指针
	pRoadHead->pNext = pRoadMove;	//连接起来
	int nTotalNumOfRoad = 0; //总共有多少条边Arc
	ifstream infile_Road;
	infile_Road.open("E:\\Data Structure\\BigWork\\data\\road1.csv");
	char *buf_Road;

	//先读入表头各项
	char cFirstLine_Road[100];	//存放每一行的字符
	infile_Road.getline(cFirstLine_Road, 100);

	//cout << "The Road includes this infomation:\t";
	int nforBool; //读0和1后通过判断语句给bool型赋值

	while (!infile_Road.eof())
	{
		nTotalNumOfRoad++;
		char **_ppEachField = new char *[8];

		char _cReadEachLine_Road[100];
		infile_Road.getline(_cReadEachLine_Road, 100);
		_ppEachField[0] = strtok_s(_cReadEachLine_Road, ",", &buf_Road);

		int _i = 0;
		while (_ppEachField[_i])
		{
			_i++;
			_ppEachField[_i] = strtok_s(NULL, ",", &buf_Road);
		}
		_ppEachField[_i] = "\0";
		pRoadMove->nFID = atoi(_ppEachField[0]);
		nforBool = atoi(_ppEachField[1]);
		if (nforBool == 1)
			pRoadMove->bIsOneWay = true;
		else
			pRoadMove->bIsOneWay = false;
		pRoadMove->fLength = strtod(_ppEachField[2], NULL);
		pRoadMove->fLongtitudeOut = strtod(_ppEachField[3], NULL);
		pRoadMove->fLatitudeOut = strtod(_ppEachField[4], NULL);
		pRoadMove->fLongtitudeIn = strtod(_ppEachField[5], NULL);
		pRoadMove->fLatitudeIn = strtod(_ppEachField[6], NULL);

		if (infile_Road.eof()) break;
		pRoadMove->pNext = new Road;
		pRoadMove = pRoadMove->pNext;
		pRoadMove->pNext = NULL;

		/*释放内存*/
		//由于_ppEachField[i]和buf实际指向的是静态空间，无需也不能手动delete
		delete[]_ppEachField;
		_ppEachField = NULL;
	}
	infile_Road.close();
	pRoadMove = pRoadHead->pNext;	//回到表头
	return nTotalNumOfRoad;
}
