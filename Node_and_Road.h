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
	int nBetweenness; //边介数，在Dijsktra运算时赋值？
	int nIDBegin;	//用于查询对应的顶点
	int nIDEnd;		//用于查询对应的终点
	Road *pNext;
};

void DeleteRoad(Road *pHead);
void DeleteNode(Node *pHead);