#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"lookuptable.h"

float RowScale[ROWMAX] = {0};
float ColumnScale[COLMAX] = {0};
float TableData[ROWMAX][COLMAX] = {{0,0}};
int RowNum = 0;		//Actual row numember user inputs
int ColNum = 0;		//Actual column numember user inputs
//float *RowScale;
//float *ColumnScale;
//float **TableData;
int indexOfRow(float rowdata);
int indexOfColumn(float columndata);
/**************************************************************************************************/
float LookupTable(float rowdata,float columndata)
{
    float result = 0;
	float temp[4];       //store 4 block-surrouding data whose indexes are (i,j),(i+1,j),(i,j+1),(i+1,j+),respectively.
	float percent[4];   //store 4 percentage value according to the differences between inputed row/column data and Row/Column Scale
	int rowth = indexOfRow(rowdata);
	int columnth = indexOfColumn(columndata);
	if(rowth>=0 && columnth>=0)
	{
	   temp[0] = TableData[rowth][columnth];
	   temp[1] = TableData[rowth+1][columnth];
	   temp[2] = TableData[rowth][columnth+1];
	   temp[3] = TableData[rowth+1][columnth+1];

	   percent[0] = (rowdata-RowScale[rowth])/(RowScale[rowth+1]-RowScale[rowth]);
	   percent[1] = (RowScale[rowth+1]-rowdata)/(RowScale[rowth+1]-RowScale[rowth]);
	   percent[2] = (columndata-ColumnScale[columnth])/(ColumnScale[columnth+1]-ColumnScale[columnth]);
	   percent[3] = (ColumnScale[columnth+1]-columndata)/(ColumnScale[columnth+1]-ColumnScale[columnth]);

	   result = percent[0]*percent[2]*temp[0] + percent[1]*percent[2]*temp[1] + percent[0]*percent[3]*temp[2] + percent[1]*percent[3]*temp[3];
	}
	return	result;
}

void FillTableData(int rownum,int colnum,float* rowScale,float* columnScale,float** tableData)
{
   	int i,j;
     
	RowNum = rownum;
    ColNum = colnum;
	
	for(i=0;i<rownum;i++)
	{
	   RowScale[i] = rowScale[i];
	}
	for(j=0;j<colnum;j++)
	{
	   ColumnScale[j] = columnScale[j];
	}
	for(i=0;i<rownum;i++)
	{
	   for(j=0;j<colnum;j++)
	   {
	    TableData[i][j] = tableData[i][j];
	   }
	}
}
/**********************************************************************************************/
int indexOfRow(float rowdata)
{
   // if( A[i] <= rowdata < A[i+1])  return i;
   int i = 0;
   if(rowdata < RowScale[RowNum-1] && rowdata >= RowScale[0])
   {
      for(i=0;i<RowNum-1;i++)
      {
         if(rowdata >= RowScale[i] && rowdata < RowScale[i+1])
	       return i;
	  }
   }
   return -1;
}

int indexOfColumn(float columndata)
{
 // if( B[j] <= columndata < B[j+1])  return j;
   int i = 0;
   if(columndata < ColumnScale[ColNum-1] && columndata >= ColumnScale[0])
   {
      for(i=0;i<ColNum-1;i++)
      {
         if(columndata >= ColumnScale[i] && columndata < ColumnScale[i+1])
	       return i;
	  }
   }
   return -1;
}


