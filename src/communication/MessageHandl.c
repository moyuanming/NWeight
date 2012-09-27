#include "LocalIncludeFile.h"

static int MsgIndex = 0;
/******************************************************************************************************
* 删除已发送消息从消息队列中 并将消息存放到已发送的文件中
******************************************************************************************************/
int  DeleteSendedMessageFromMessageQueue(char *strMsgIndex)
{
	char temp[5] ;
	int ret = 0;
	sprintf(temp,"%04d",MsgIndex);
	temp[4] = 0;
	if(0==strncmp(temp,strMsgIndex,4))
	{
		DB_SetMessageSend(Get_DB_MSGID_Current());
		MsgIndex++;
		if(10000<=MsgIndex)
		{
			MsgIndex = 0;
		}
		ret = 1;
	}
	return ret;
}
/******************************************************************************************************
* 获取注册消息
******************************************************************************************************/
static char RegMsg[9];

char *GetRegMessage(void)
{
	memset(RegMsg,0x00,9);
	strncpy(RegMsg,GetLanConfigNetNo(),2);
	strncpy(&RegMsg[2],GetLanConfigPlazaNo(),2);
	RegMsg[4] = GetLanConfigLaneType();
	strncpy(&RegMsg[5],GetLanConfigLaneNo(),3);

	return RegMsg;
}
/******************************************************************************************************
* 从消息队列中获取消息
******************************************************************************************************/
char MsgTemp[MAXMSGBODYLENGTH +6 ] = {0};
char *GetCurrentMessage()
{
	char *Message;
	Message = DB_GetMesssageFromDB();
	if(NULL!=Message)
	{
		memset(MsgTemp,0x00,MAXMSGBODYLENGTH +6);
		sprintf(MsgTemp,"%04d%s",MsgIndex,Message);
		echoic("MsgTemp=%s\n",MsgTemp);
		return MsgTemp;
	}
	else
	{
		return NULL;
	}
}

BOOL CheckBCC(char *Message)
{
	int i;
	char BCC = Message[0];
	int Len = strlen(Message);
	for( i = 1;i<Len -1;i++)
	{
		BCC ^= Message[i];
	}
	if( 0 == BCC)
	{
		BCC = '#';
	}
	//echodebug(" BCC=[%d],Message=[%d] \r\n \r\n Message = [%s]",BCC,Message[Len-1],Message);
	return BCC == Message[Len-1];
}

void CheckMessageBCC()
{
	char *Message;
	Message = GetCurrentMessage();
	if(!CheckBCC(Message))
	{
		DB_SetBCCError(Get_DB_MSGID_Current());
	}
}
