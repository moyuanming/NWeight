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
		
		if (0 == strncmp(userNumber, "8888888888", Getg_userNumberLen()))
		{
			SetG_collectType(GetUserGroup('1'));
			Setg_szName("收费员测试账号");
			ret = T;
		} else if (0 == strncmp(userNumber, "9999999999", Getg_userNumberLen()))
		{
			SetG_collectType(GetUserGroup('9'));
			Setg_szName("未知测试员账号");
			ret = T;
		}
		else if (0 == strncmp(userNumber, "0000000000", Getg_userNumberLen()))
		{
			SetG_collectType(GetUserGroup('2'));
			Setg_szName("维护员测试账号");
			ret = T;
		}
	}
	return ret;
}
//随机密码 第一位是 星期几的数字星期天是0，第二位是月数， 如果超过9月 ，则是9月，
//第三位 第四位是月里面的号数 ， 两位， 1号 就是01，后面四位是 年费， 如2012 
//举例:2013年3月11日 星期一  密码就是  13112013  
//     2013年12月31号  星期二 密码就是 29312013 
BOOL GetRandPassword(char * password)
{
	char tmppassword[50];
	struct tm *rtc_time;
	memset (tmppassword,0x00,sizeof(tmppassword));
	time_t t = time(NULL);	
	rtc_time = localtime(&t);
	sprintf(tmppassword ,"%1d%1d%02d%04d",rtc_time->tm_wday,rtc_time->tm_mon>8?8+1:rtc_time->tm_mon+1,rtc_time->tm_mday, rtc_time->tm_year+1900);
	echo_ct("临时密码:%s",tmppassword);
	return 	0 == strncmp(PwdEncrypt(password), tmppassword, Getg_userPasswordLen());
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
	 if (0 == strncmp(InputUserNumber, "8888888888", Getg_userNumberLen()) && GetRandPassword( InputPassword))
	{
		ret = T;
	} 
	else if (0 == strncmp(InputUserNumber, "9999999999", Getg_userNumberLen()) && GetRandPassword( InputPassword))
	{
		ret = T;
	}
	else if (0 == strncmp(InputUserNumber, "0000000000", Getg_userNumberLen()) && GetRandPassword( InputPassword) )
	{
		ret = T;
	}
	return ret;
}

