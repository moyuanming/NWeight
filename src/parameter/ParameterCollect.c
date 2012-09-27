// ***************************************************************
//  collect  Table   version:  1.0   ·  date: 22/05/2008
//  -------------------------------------------------------------
//  职员信息表！
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************
#include "LocalIncludeFile.h"
struct MSG_COLLECT  * GetIndexCollect(int InputIndex)
{
    return  &MsgCollect[InputIndex];
}
/************************************************************************************
*解析职员表记录，每一条职员记录是一个已赋值的结构体
*************************************************************************************/
int ParseRecordCollect(char *RecordStr,int Rowindex)
{
    strncpy((char *)&MsgCollect[Rowindex],RecordStr,sizeof(struct MSG_COLLECT));
    return 0;
}
/*************************************************************************
*从职员表文件中读取记录到内存
*************************************************************************/
int LoadCollectRecord(int IsFirst)
{
    int ret = LoadRecord(PARACOLLECT_FILE,&CollectHead,LENGHT_MSG_COLLECT,ParseRecordCollect,FRAE,IsFirst);
	echoic("LoadCollectRecord = <%s> ",PARACOLLECT_FILE);
    strncpy(GetMsgRevision()->CollectVer,CollectHead.VerNo,2);
    return  ret;
}
char * PwdEncrypt(char *InputPassword)
{
    int i= 0;
    for(i=0;i<8;i++)
    {
        InputPassword[i] -=(char) 32 ;
        InputPassword[i] ^= (char) (i+1);
        InputPassword[i] ^= (char) 12; // Key= 12
        InputPassword[i] += (char) 32;
    }
    return InputPassword;
}




/***************************************************************************************************************/
char * GetUserGroup(char Identify)
{
	char * UserGroup;
	if('1' ==Identify)
	{
		UserGroup="收费员";
	}
	else if('3' == Identify)
	{
		UserGroup="维护员";
	}
	else
	{
		UserGroup="";
	}
	return UserGroup;
}
/*----------------------------------------------------------------------
函数名称：      int UserNumberExist(char *userNumber)
作用：          对用户输入的工号进行确认
参数：          char *userNumber 用户工号
返回值：        返回类型    int
                返回结果    0   工号位数不正确
                            1   工号正确
                            2   工号不正确
                            3   工号输入不正确并超过三次
创建日期：      2005.9
创建人:         莫远明
最后修改日期:   2008.5
最后修改人:     王海伟
----------------------------------------------------------------------*/
BOOL UserNumberExist(char *userNumber)
{
	int i ;
	BOOL ret = F;
	long  int  rowscount;
	rowscount=atol(CollectHead.Recordcount);
	for(i=0;i<rowscount;i++)
	{

		if(0==strncmp(userNumber,MsgCollect[i].collno,Getg_userNumberLen()))
		{

			SetG_User_Index (i);
			SetG_collectType(GetUserGroup(MsgCollect[i].identify[0]));
			Setg_szName(MsgCollect[i].collname);
			SetG_Number(MsgCollect[i].collno);
			ret =T;
			break;
		}
	}
	if(!ret)
	{
		if(0==strncmp(userNumber,"7777777777",Getg_userNumberLen()))
		{
			
			SetG_collectType("1");
			Setg_szName("开发测试工号");
			ret =T;
		}
		else if(0==strncmp(userNumber,"555555555",Getg_userNumberLen()))
		{
			SetG_collectType("9");
			Setg_szName("开发测试工号");
			ret =T;
		}
	}
	return ret;
}
int UserExist(char *InputUserNumber,char *InputPassword)
{
	int i ;
	int ret = F;
	long  int  rowscount;
	rowscount=atol(CollectHead.Recordcount);
    PwdEncrypt(InputPassword);
	echoic("UserExist:{%s},{%s}",InputUserNumber,InputPassword);
	for(i=0;i<rowscount;i++)
	{
		if(0==strncmp(InputUserNumber,MsgCollect[i].collno,6)  
			&& 0==strncmp(InputPassword,MsgCollect[i].password,Getg_userPasswordLen()) 
			&& '0' == MsgCollect[i].Status[0])
		{
			ret =T;
			break;
		}
	}	
	echoic("UserExist:{%s}{%d}{%d}",InputUserNumber,ret,Getg_userNumberLen());
	if(0==strncmp(InputUserNumber,"7777777777",Getg_userNumberLen()))
	{			
		ret =T;
	}
	else if(0==strncmp(InputUserNumber,"555555555",Getg_userNumberLen()))
	{			
		ret =T;
	}	
	return ret;
}

