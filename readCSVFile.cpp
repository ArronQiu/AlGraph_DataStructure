#include "readCSVFile.h"

int GetTotalLineCount(FILE *fp)
{
	int i = 0;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);						//fp指针指向开头
	while (fgets(strLine, MAX_LINE_SIZE, fp))	//fgets函数，一共读Line次
		i++;
	fseek(fp, 0, SEEK_SET); 
	return i;
}

int GetTotalColCount(FILE *fp)
{
	int i = 0;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);
	if (fgets(strLine, MAX_LINE_SIZE, fp))
	{
		i = strlen(strLine)/ 2;		//因此处为CSV以逗号","为分隔符，所以除以2
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	return i;
}

//通过指针分配动态空间
int AssignSpaceForData(int inumdata)
{
	pnCsvData = NULL;
	pnCsvData = (int *)malloc(sizeof(int)*inumdata);
	if (pnCsvData == NULL)
		return 0;
	memset(pnCsvData, 0, sizeof(int)*inumdata);	//将开辟的动态空间初始化为0
	return 1;
}

//释放动态数据内存
void FreeCsvData()
{
	free(pnCsvData);
	pnCsvData = NULL;
}

//[关键]读CSV文件
int ReadCsvData(char * csvFilePath)
{
	FILE *fCsv;
	char *ptr;
	char strLine[MAX_LINE_SIZE];
	int i;
	int j;
	//已有数据，则先删除
	if (pnCsvData != NULL)
		FreeCsvData();
	if (fopen_s(&fCsv, csvFilePath, "r") != 0)
	{
		printf("Open file %s failed ", csvFilePath);
		return -1;
	}
	else
	{
		nNumRow = GetTotalLineCount(fCsv);
		nNumCol = GetTotalColCount(fCsv);
		nNumData = nNumRow*nNumCol;
		char *_buf;	//为了strtok_s分割后部分的储存
		for (i = 0; i < nNumRow; i++)
		{
			j = 0;
			if (fgets(strLine, MAX_LINE_SIZE, fCsv))
			{
				//strtok_s的原型
				//char *strtok_s( char *strToken, const char *strDelimit, char **buf);
				ptr = strtok_s(strLine, ",", &_buf);
	
				while (ptr != NULL)
				{
					pnCsvData[i*nNumCol + j] = *ptr;
					j++;
					ptr = strtok(NULL, ",");                //将从文件中读取的当前行剩余字符数组，读取字符‘,’前面的字节
				}
			}
		}
		// 关闭文件
		fclose(fCsv);
	}
	return 1;
}

//通过控制台显示读取的csv数据
void  ShowCsvData()
{
	int i;
	int j;
	for (i = 0; i < nNumRow; i++)
	{
		printf("Line %i :", i + 1);    //输出每行的行号 Line :
		for (j = 0; j < nNumCol; j++)
		{
			printf("%i", pnCsvData[i*nNumCol + j]);  // 打印CSV数据
		}
		printf("\n");                           //输出换行
	}
}
	