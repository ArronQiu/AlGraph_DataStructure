#include "Community.h"

void Community::initialEM(int numOfCommunity)
{
	ppfEMatx = new float*[numOfCommunity];
	pfA = new float[numOfCommunity];
	//初始化EM

	/*求和Tre*/
	int i = 0, j = 0;
	for (i = 0; i < numOfCommunity; i++)
	{
		fTre = fTre + ppfEMatx[i][i];
	}
	for (i = 0; i < numOfCommunity; i++)
	{
		pfA[i] = 0;
		for (j = 0; j < numOfCommunity; j++)
		{
			pfA[i] = pfA[i] + ppfEMatx[i][j];
		}
	}
}
