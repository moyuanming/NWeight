#include "LocalIncludeFile.h"
/*

EMRCDB 结构
table name:TB_Message
int ID 自增列
char * MessageBody 存放消息内容的字段
int mark 消息状态字段

create table TB_Message (
ID integer primary key,
MessageBody text,
MessageTime Text,
Mark int );
create table TB_LOG (
ID integer primary key,
LOG text,
MessageTime Text,
Mark int );
CREATE INDEX IDIndex on TB_Message (ID);
CREATE INDEX Mark_Index on TB_Message (Mark);
CREATE INDEX MarkTime_Index on TB_Message (Mark,MessageTime);
*/
#define  MSG_SEND 1
#define  MSG_BCCERROR 2
static volatile sem_t OperatorSyncDB;
sqlite3 *db;
void DB_Init()
{
	sqlite3_open(FILENAME_EMRC_MSG_DB, &db);
	sem_post((sem_t *)&OperatorSyncDB);
}
static int DB_EXECSQL(char * Sql)
{
	char *zErr;
	int rc;
	sem_wait((sem_t *)&OperatorSyncDB);
	rc = sqlite3_exec(db, Sql, NULL, NULL, &zErr);
	if(SQLITE_OK!=rc)
	{
		LogCDbLog("ErrNo:[%d]Errmessage：[%s]",rc,zErr);
	}
	sem_post((sem_t *)&OperatorSyncDB);
	return rc;
}
int DB_ID_Index = 0;
long  DB_MSGID_Current;
char  DB_MessageTemp[MAXMSGBODYLENGTH +6 ] = {0};

long Get_DB_MSGID_Current()
{
	return DB_MSGID_Current;
}
int callback(void* data, int ncols, char** values, char** headers)
{
	if(NULL !=values )
	{
		memset(DB_MessageTemp,0x00,MAXMSGBODYLENGTH +6);
		DB_MSGID_Current = atol(values[0]);
		strcpy(DB_MessageTemp,values[1]);
	}
	return 0;
}
char * DB_GetMesssageFromDB()
{
	char *zErr;
	int rc;
	char *sql;
	char *ret;
	sem_wait((sem_t *)&OperatorSyncDB);
	DB_MSGID_Current = -1;
	sql = "select * from TB_message where mark = '0' order by ID limit 1;";
	rc = sqlite3_exec(db, sql, callback, NULL, &zErr);
	if(SQLITE_OK!=rc)
	{
		LogCDbLog("ErrNo:[%d]Errmessage：[%s]",rc,zErr);
		ret = NULL;
	}
	else
	{
		if (-1==DB_MSGID_Current)
		{
			ret = NULL;
		}
		else
		{
			ret = DB_MessageTemp;
		}
	}
	sem_post((sem_t *)&OperatorSyncDB);
	return ret;
}
int DB_AddMessage(char * Messagebody)
{
	int rc;
	char *sql;
	
	sql = sqlite3_mprintf("insert into TB_message (MessageBody,Mark,MessageTime ) values('%q',0,datetime('now'))", Messagebody);
	do 
	{
		rc =DB_EXECSQL(sql);
		usleep(1000);
	} while (SQLITE_OK!=rc);

	sqlite3_free(sql);
	return rc;
}
int DB_AddLog(char * Logbody,int ErrNo)
{
	int rc;
	char *sql;
	sql = sqlite3_mprintf("insert into TB_LOG (LOG,Mark,MessageTime ) values('%q',%d,datetime('now'))",ErrNo, Logbody);
	rc =DB_EXECSQL(sql);
	sqlite3_free(sql);
	return rc;
}

static int DB_UpdateMark(int Mark,long ID)

{
	int rc;
	char  *sql;
	sql = sqlite3_mprintf("update TB_message Set Mark = %d where ID = %d ", Mark,ID);
	rc =DB_EXECSQL(sql);
	sqlite3_free(sql);
	return rc;
}
int DB_SetMessageSend( long ID)
{
	return DB_UpdateMark(MSG_SEND,ID);
}
int DB_SetBCCError( long ID)
{
	return DB_UpdateMark(MSG_BCCERROR,ID);
}

int DB_DelteOldMessage(int Savedays)
{
	int rc;
	char  *sql;
	sql = sqlite3_mprintf("delete From TB_message  where  Mark = 1 and MessageTime < datetime('now','-%d day'); ", Savedays);
	rc =DB_EXECSQL(sql);
	sqlite3_free(sql);
	return rc;
}

