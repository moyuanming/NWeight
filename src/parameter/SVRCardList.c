//By GER.Cmd.buildgcc   CreateDate:2009-3-10 11:14:06
#include "LocalIncludeFile.h"

struct MSG_SVRCARDLIST     SVRListRecord[MAXPAEAMRECORDS];
struct PARAM_HEAD	SVRListHead ;

struct MSG_JOUDESC   JOUDESCListRecord[MAXPAEAMRECORDS];
struct PARAM_HEAD    JOUListHead;
//ic�����
int  ParseRecordSVRList(char *RecordStr,int Rowindex)
{	
	strncpy((char *)&SVRListRecord[Rowindex],RecordStr,sizeof(struct MSG_SVRCARDLIST));	
	return 0;
}

int LoadSVRListRecord(int IsFirst)
{	
	int ret=0;
	ret= LoadRecord(PARASVRCARDLIST_FILE,&SVRListHead,LENGHT_MSG_SVRCARDLIST,ParseRecordSVRList,FRAE,IsFirst);	
	strncpy(GetMsgRevision()->SVRCARDLIST,SVRListHead.VerNo,2);	

	return ret;
}

int  ParseRecordJOUList(char *RecordStr,int Rowindex)
{	
	strncpy((char *)&JOUDESCListRecord[Rowindex],RecordStr,sizeof(struct MSG_JOUDESC));	
	return 0;
}

int LoadJOUListRecord(int IsFirst)
{	
	int ret=0;
	ret= LoadRecord(PARAJOUCODE_FILE,&JOUListHead,LENGHT_MSG_JOUDESC,ParseRecordJOUList,FRAE,IsFirst);	
	strncpy(GetMsgRevision()->JOUCODE,JOUListHead.VerNo,2);	

	return ret;
}

struct MSG_SVRCARDLIST *  FindCardInParamList(char *cardnumber )
{
	int rowscount;
	int i ;
	rowscount=atoi(SUBSTRING(SVRListHead.Recordcount));
	for (i=0;i<rowscount;i++)
	{
		//	echoic("%s   %s %d \n",SVRListRecord[i].SvrID,cardnumber,i);
		if (0==strncmp(SVRListRecord[i].SvrID,cardnumber,10))
		{
		
			return &SVRListRecord[i];
		}
	}
	return NULL;
}
int GetIsCardDateLimit(struct MSG_SVRCARDLIST * _SVRList)
{
	int i =0;
	echoic("%d",DiffCurrentDataTime(SUBSTRING(_SVRList->DisEnableDate)));
	int dise;
	int enable;
	dise=DiffCurrentDataTime(SUBSTRING(_SVRList->DisEnableDate));
	enable=DiffCurrentDataTime(SUBSTRING(_SVRList->EnableDate));
	if (dise>=0)
	{
		i =1;
	}
	if (enable<0)
	{
		i=2;
	}
	echoic("����ʱ��%d  ����ʱ��%d   ����ֵ%d",dise,enable,i);
	return i;
}
BOOL  CanPayForThisCarType( struct MSG_SVRCARDLIST * _SVRList, char * _cartype  )
{
	BOOL OK=FALSE;
	int re;
	int  cartypescount;
	 
	cartypescount=atoi(SUBSTRING(_SVRList->SVCUsedTypeCount));
	re= strncmp((char*)&_SVRList->CarType[(atoi(_cartype)-1)*2],"01",2);
	echoic("CanPayForThisCarType ʹ�ó�����:%d",cartypescount);
	echoic("CanPayForThisCarType  ��Ӧ���Ϳ��ñ�ʶ��%s %s �ȽϽ��:%d"
		   ,substring((char*)&_SVRList->CarType[(atoi(_cartype)-1)*2],2)
		   ,SUBSTRING(_SVRList->CarType)
		   ,re);
	if (re==0)
	{
		OK=TRUE;
	}
	return OK ;
}

BOOL Get_CardContext_InJouRouter(char * joucode)
{
	int rowscount ;
	int i;
	BOOL result=F;
	rowscount=atoi(SUBSTRING(JOUListHead.Recordcount));
	for (i=0;i<rowscount;i++)
	{
      if (0==strncmp(SUBSTRING(  JOUDESCListRecord[i].JouCode),joucode,sizeof(JOUDESCListRecord[i].JouCode)))
	  {
		  if (0==strncmp(SUBSTRING(JOUDESCListRecord[i].BeginSiteNetNo),GetLanConfigNetNo(),2))
		  {
				if (0==strncmp(SUBSTRING(JOUDESCListRecord[i].BeginSitePlaza),"00",2) 
					 ||  0==strncmp(SUBSTRING(JOUDESCListRecord[i].BeginSitePlaza), GetLanConfigPlazaNo(),2) 
					)
				{
					result=T;
				}
		  }//�Ƚ�·����
	  }//�Ƚ�·�̱���
	}//for ѭ��
	echoic("·���ź�վ���� %s%s  �ó̴���:%s",GetLanConfigNetNo(), GetLanConfigPlazaNo(),joucode);
	return result ;
}


//end_SVRCardList
