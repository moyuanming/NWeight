#ifndef _EmrcDBOperator_H_
#define _EmrcDBOperator_H_

void DB_Init(void);
long Get_DB_MSGID_Current(void);
char * DB_GetMesssageFromDB(void);
int DB_AddMessage(char * Messagebody);
int DB_AddLog(char * Logbody,int rc);
int DB_SetMessageSend( long ID);
int DB_SetBCCError( long ID);
int DB_DelteOldMessage(int Savedays);
#endif

