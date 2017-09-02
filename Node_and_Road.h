#pragma once
struct Node
{
	~Node();
	int nFID;
	float fLatitude;
	float fLongitude;
	int nJointCount;
	Node *pNext;
};

struct Road
{
	~Road();
	int nFID;
	bool bIsOneWay;
	float fLength;
	float fLongtitudeOut;
	float fLatitudeOut;
	float fLongtitudeIn;
	float fLatitudeIn;
	int nBetweenness; //�߽�������Dijsktra����ʱ��ֵ��
	int nIDBegin;	//���ڲ�ѯ��Ӧ�Ķ���
	int nIDEnd;		//���ڲ�ѯ��Ӧ���յ�
	Road *pNext;
};

void DeleteRoad(Road *pHead);
void DeleteNode(Node *pHead);