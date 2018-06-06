#ifndef _LOOKUPTABLE
#define _LOOKUPTABLE
#define ROWMAX 20
#define COLMAX 20
#define DATASIZE  ROWMAX*COLMAX
extern float RowScale[ROWMAX];
extern float ColumnScale[COLMAX];
extern float TableData[ROWMAX][COLMAX];
extern int RowNum;		//Actual row numember user inputs
extern int ColNum;		//Actual column numember user inputs
float LookupTable(float rowdata,float columndata);
#endif /*_LOOKUPTABLE_*/


