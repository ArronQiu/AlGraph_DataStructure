#pragma once
#include "ALGraph.h"
class Community
{
public:
	double dCalModularity(ALGraph *pGraph); //����ģ���,�ο������ڼ�Ȩ�߽�����Web�������ַ���_������
	float **ppfNodeMatrix;
	float fTre;
	float *pfA;
	//eij��ʾ���������������еĽڵ�i������j�нڵ�ı������б�����ռ�ı���
	//ai = ��(i) eij ��ʾ���i�������еĽڵ������ı������б�����ռ�ı���
	//Tre = sum(eii)����������������ĳһ�������ڲ����ڵ�ı������бߵ���Ŀ����ռ�ı���
private:
	double Modulartiy; // = ��(i) (eii-ai^2)
};
