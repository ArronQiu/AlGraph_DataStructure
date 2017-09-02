#include "ReadAndWrite_NodeAndRoad.h"
#include "ALGraph.h"
#include <string>
#include <fstream>
#include <stdlib.h>

/*ֱ�Ӵ�Road�ļ��Ļ����߽����㷨����д*/
/*��ALGraph�Ļ��������ͱ߱���Ҫ��ž�γ����Ϣ���߱�Ҫ�Ӹ�bIsOneWay*/
/*ͨ������ALGraph��д��.csv*/
int WriteRoad(ALGraph *pGraph)
{
	/*��δ��������⣺to_stringʱ������ʧ*/
	
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
			
			if (pGraph->pALGraphHead[nThisVertex].pFirstEdge->bIsOneWay == true)	//�����
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
			outfile << pEdgeMove->nBetweenness << endl; //�����������
				
			}
			else if (nThisVertex < pEdgeMove->nAdjv)	//�״���������˫���
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
				outfile << pEdgeMove->nBetweenness << endl; //�����������
			}
			//�����״���������˫��ߣ���˵���ñ��Ѿ������
				pEdgeMove = pEdgeMove->pNext;
				nID++;
		}
		
		//cout << "The roads out from " << nThisVertex << " haved been output." << endl;
		nThisVertex++;	//�ö���ı�������
		if (nThisVertex > pGraph->n-1) break;	//���һ������ı������ϣ��˴���n�Ƚ�Ҫ-1����Ϊ��Ŵ�0��ʼ

		/*���⣺˫���·�ظ����*/
	}
	cout << "���߽�����Ϣ��·���ļ������." << endl;
	outfile.close();
	return nID-1;	/*�������һ���ߵ����*/
}

int ReadAndCreateNode(Node * pNodeHead)
{
	Node *pNodeMove = new Node;	//�����ƶ���new��ָ��
	pNodeHead->pNext = pNodeMove;	//��������
	char *buf;
	int nTotalNumOfNode = 0;	//�ܹ��ж��ٸ��ڵ�

	ifstream infile;
	infile.open("E:\\Data Structure\\BigWork\\data\\node1.csv");

	/*����Node�ļ�*/
	//�ȶ����ͷ����
	char cFirstLine[60];	//���ÿһ�е��ַ�
	infile.getline(cFirstLine, 50);	//�����һ��
									//cout << "The Node includes this infomation:\t";

	while (!infile.eof())
	{
		nTotalNumOfNode++;	//��¼�������

		char **_ppEachField = new char *[5];	//����һ����άָ�룬�ֱ��Ų�ͬ�ֶε����ݣ���ʼ��Ϊ��

		char _cReadEachLine[60];
		infile.getline(_cReadEachLine, 50); //���ÿһ�е��ַ�
		_ppEachField[0] = strtok_s(_cReadEachLine, ",", &buf); //�ָ��ַ�������¼�׸�Ԫ��

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

		/*�ͷ��ڴ�*/
		//����_ppEachField[i]��bufʵ��ָ����Ǿ�̬�ռ䣬����Ҳ�����ֶ�delete
		delete[]_ppEachField;
		_ppEachField = NULL;
	}
	infile.close();
	pNodeMove = pNodeHead->pNext;	//�ص���ͷ
	
	return nTotalNumOfNode;
}

int ReadAndCreateRoad(Road * pRoadHead)
{
	Road *pRoadMove = new Road;	//�����ƶ���new��ָ��
	pRoadHead->pNext = pRoadMove;	//��������
	int nTotalNumOfRoad = 0; //�ܹ��ж�������Arc
	ifstream infile_Road;
	infile_Road.open("E:\\Data Structure\\BigWork\\data\\road1.csv");
	char *buf_Road;

	//�ȶ����ͷ����
	char cFirstLine_Road[100];	//���ÿһ�е��ַ�
	infile_Road.getline(cFirstLine_Road, 100);

	//cout << "The Road includes this infomation:\t";
	int nforBool; //��0��1��ͨ���ж�����bool�͸�ֵ

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

		/*�ͷ��ڴ�*/
		//����_ppEachField[i]��bufʵ��ָ����Ǿ�̬�ռ䣬����Ҳ�����ֶ�delete
		delete[]_ppEachField;
		_ppEachField = NULL;
	}
	infile_Road.close();
	pRoadMove = pRoadHead->pNext;	//�ص���ͷ
	return nTotalNumOfRoad;
}
