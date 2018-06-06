#ifndef _LDDSPORTS_H
#define _LDDSPORTS_H

#define  DENUM		   3


//Setpoint
#define   SPHUM					0
#define   SPTEMP				1
#define   SETRECON				2



///// temp register

#define   WSTLEVEL				0
#define   SSTLEVEL				1
#define   RELEVEL				2
#define   DELEVEL1				3
#define   DELEVEL2				4
#define   DELEVEL3				5

#define   BUFLEVEL1				6
#define   BUFLEVEL2				7
#define   BUFLEVEL3				8

#define   CASETRANSFER			13
#define   CASEEMERGENCY			14




#define LOCALORREMOTE 0


///please adjust these para based on the system!!!!!1
#define RLA     18  // The low alarm level of regenerator tank
#define RHA1    40  //The first high alarm level of regenerator tank
#define RHA2    45  // The second high alarm level of regenerator tank
#define DLA     18  //The low alarm level of dehumidifier tank
#define DHA1    40  //The first high alarm level of dehumidifier tank
#define DHA2    45  //The second high alarm level of dehumidifier tank
#define DHA3    48  //The third high alarm level of dehumidifier tank
#define BLA     10  //The low alarm level of buffer tank
#define BHA1    100  //The first high alarm level of buffer tank
#define BHA2 	110  //The second high alarm level of buffer tank
#define BMA1 	30   //The first middle alarm level of buffer tank
#define BMA2 	90   //The second middle alarm level of buffer tank
#define WLA  	10   //The low alarm level of weak solution tank
#define WHA1 	100   //The first high alarm level of weak solution tank
#define WHA2 	110   //The second high alarm level of weak solution tank
#define SLA  	10   //The low alarm level of strong solution tank
#define SHA1 	100   //The first high alarm level of strong solution tank
#define SHA2  	110   //The second high alarm level of strong solution tank


#endif 

