#include "readCSVFile.h"

int GetTotalLineCount(FILE *fp)
{
	int i = 0;
	char strLine[MAX_LINE_SIZE];
	fseek(fp, 0, SEEK_SET);						//fpָ��ָ��ͷ
	while (fgets(strLine, MAX_LINE_SIZE, fp))	//fgets������һ����Line��
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
		i = strlen(strLine)/ 2;		//��˴�ΪCSV�Զ���","Ϊ�ָ��������Գ���2
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	return i;
}

//ͨ��ָ����䶯̬�ռ�
int AssignSpaceForData(int inumdata)
{
	pnCsvData = NULL;
	pnCsvData = (int *)malloc(sizeof(int)*inumdata);
	if (pnCsvData == NULL)
		return 0;
	memset(pnCsvData, 0, sizeof(int)*inumdata);	//�����ٵĶ�̬�ռ��ʼ��Ϊ0
	return 1;
}

//�ͷŶ�̬�����ڴ�
void FreeCsvData()
{
	free(pnCsvData);
	pnCsvData = NULL;
}

//[�ؼ�]��CSV�ļ�
int ReadCsvData(char * csvFilePath)
{
	FILE *fCsv;
	char *ptr;
	char strLine[MAX_LINE_SIZE];
	int i;
	int j;
	//�������ݣ�����ɾ��
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
		char *_buf;	//Ϊ��strtok_s�ָ�󲿷ֵĴ���
		for (i = 0; i < nNumRow; i++)
		{
			j = 0;
			if (fgets(strLine, MAX_LINE_SIZE, fCsv))
			{
				//strtok_s��ԭ��
				//char *strtok_s( char *strToken, const char *strDelimit, char **buf);
				ptr = strtok_s(strLine, ",", &_buf);
	
				while (ptr != NULL)
				{
					pnCsvData[i*nNumCol + j] = *ptr;
					j++;
					ptr = strtok(NULL, ",");                //�����ļ��ж�ȡ�ĵ�ǰ��ʣ���ַ����飬��ȡ�ַ���,��ǰ����ֽ�
				}
			}
		}
		// �ر��ļ�
		fclose(fCsv);
	}
	return 1;
}

//ͨ������̨��ʾ��ȡ��csv����
void  ShowCsvData()
{
	int i;
	int j;
	for (i = 0; i < nNumRow; i++)
	{
		printf("Line %i :", i + 1);    //���ÿ�е��к� Line :
		for (j = 0; j < nNumCol; j++)
		{
			printf("%i", pnCsvData[i*nNumCol + j]);  // ��ӡCSV����
		}
		printf("\n");                           //�������
	}
}
	