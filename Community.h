#pragma once
#include "ALGraph.h"
class Community
{
public:
	double dCalModularity(ALGraph *pGraph); //计算模块度,参考《基于加权边介数的Web社区发现方法_胡桓》
	float **ppfNodeMatrix;
	float fTre;
	float *pfA;
	//eij表示网络中连接社区中的节点i与社区j中节点的边在所有边中所占的比例
	//ai = Σ(i) eij 表示与第i个社区中的节点相连的边在所有边中所占的比例
	//Tre = sum(eii)给出了网络中连接某一个社区内部各节点的边在所有边的数目中所占的比例
private:
	double Modulartiy; // = Σ(i) (eii-ai^2)
};
