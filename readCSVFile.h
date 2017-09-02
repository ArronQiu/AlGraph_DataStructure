#pragma once
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 65535

int *pnCsvData;
int nNumData;
int nNumRow;
int nNumCol;

int GetTotalLineCount(FILE* fp);
int GetTotalColCount(FILE *fp);
int AssignSpaceForData(int inumdata);
void FreeCsvData();
void ShowCsvData();