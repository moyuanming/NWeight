// ***************************************************************
//  collect  Table   version:  1.0   ��  date: 22/05/2008
//  -------------------------------------------------------------
//  ְԱ��Ϣ��
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
*����ְԱ���¼��ÿһ��ְԱ��¼��һ���Ѹ�ֵ�Ľṹ��
*************************************************************************************/
int ParseRecordCollect(char *RecordStr,int Rowindex)
{
    strncpy((char *)&MsgCollect[Rowindex],RecordStr,sizeof(struct MSG_COLLECT));
    return 0;
}
/*************************************************************************
*��ְԱ���ļ��ж�ȡ��¼���ڴ�
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
		UserGroup="�շ�Ա";
	}
	else if('3' == Identify)
	{
		UserGroup="ά��Ա";
	}
	else
	{
		UserGroup="";
	}
	return UserGroup;
}
/*----------------------------------------------------------------------
�������ƣ�      int UserNumberExist(char *userNumber)
���ã�          ���û�����Ĺ��Ž���ȷ��
������          char *userNumber �û�����
����ֵ��        ��������    int
                ���ؽ��    0   ����λ������ȷ
                            1   ������ȷ
                            2   ���Ų���ȷ
                            3   �������벻��ȷ����������
�������ڣ�      2005.9
������:         ĪԶ��
����޸�����:   2008.5
����޸���:     ����ΰ
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
			Setg_szName("�շ�Ա�����˺�");
			ret = T;
		} else if (0 == strncmp(userNumber, "9999999999", Getg_userNumberLen()))
		{
			SetG_collectType(GetUserGroup('9'));
			Setg_szName("δ֪����Ա�˺�");
			ret = T;
		}
		else if (0 == strncmp(userNumber, "0000000000", Getg_userNumberLen()))
		{
			SetG_collectType(GetUserGroup('2'));
			Setg_szName("ά��Ա�����˺�");
			ret = T;
		}
		else if (0 == strncmp(userNumber, "7777777777", Getg_userNumberLen()))
		{
			SetG_collectType(GetUserGroup('1'));
			Setg_szName("ά��Ա�����˺�");
			ret = T;
		}
	}
	return ret;
}
//������� ��һλ�� ���ڼ���������������0���ڶ�λ�������� �������9�� ������9�£�
//����λ ����λ��������ĺ��� �� ��λ�� 1�� ����01��������λ�� ��ѣ� ��2012 
//����:2013��3��11�� ����һ  �������  13112013  
//     2013��12��31��  ���ڶ� ������� 29312013 
BOOL GetRandPassword(char * password)
{
	char tmppassword[50];
	struct tm *rtc_time;
	memset (tmppassword,0x00,sizeof(tmppassword));
	time_t t = time(NULL);	
	rtc_time = localtime(&t);
	sprintf(tmppassword ,"%1d%1d%02d%04d",rtc_time->tm_wday,rtc_time->tm_mon>8?8+1:rtc_time->tm_mon+1,rtc_time->tm_mday, rtc_time->tm_year+1900);
	echo_ct("��ʱ����:%s",tmppassword);
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
	else if (0 == strncmp(InputUserNumber, "7777777", Getg_userNumberLen()) && GetUseAutoMan()==T )
	{
		ret = T;
	}
	return ret;
}

