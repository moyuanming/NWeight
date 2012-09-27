//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "LocalIncludeFile.h"
struct MSG_YHRATEDESCRIPTION    YHRateDescriptionRecord[MAXPAEAMRECORDS];

struct PARAM_HEAD	YHRateDescriptionHead ;

/************************************************************************************************************
*描述表中的每一条记录是一个已赋值的结构体，描述表文件对应结构体数组
************************************************************************************************************/
int  ParseRecordYHRateDescription(char *RecordStr,int Rowindex)
{	
	strncpy((char *)&YHRateDescriptionRecord[Rowindex],RecordStr,sizeof(struct MSG_YHRATEDESCRIPTION));	
	return 0;
}


/************************************************************************************************************
*加载描述表文件到内存
************************************************************************************************************/
int LoadYHRateDescriptionRecord(int IsFirst)
{	
	int ret;
	ret = LoadRecord(PARAYHRATE_FILE,&YHRateDescriptionHead,YHRateDescriptionSTRLENGTH,ParseRecordYHRateDescription,FRAE,IsFirst);	
	strncpy(GetMsgRevision()->YHRateDescriptionVer,YHRateDescriptionHead.VerNo,2);	
	return ret;
}

	char   date[23];
/************************************************************************************************************
*对应优惠编号的优惠政策 的生效时间
************************************************************************************************************/
char   *GetEffectDateTime(char *InputYHcode)
{	
    int i ;
    long int  rowscount;
    memset(date,0x00,23);	
    rowscount=atol(YHRateDescriptionHead.Recordcount);	
    for (i=0;i<rowscount;i++)
    {	
        if (0==strncmp(InputYHcode,YHRateDescriptionRecord[i].YHCode,3))
        {	
            strncpy(date,YHRateDescriptionRecord[i].EffectDateTime,sizeof(YHRateDescriptionRecord[i].EffectDateTime));	
            return  date;
        }
    }
    return  "";
}



//char  *GetAdjustMode(char *InputExitNetwork,char *InputxitPlaza,char *InputYHcode){	}
/************************************************************************************************************
*获取调整模式
************************************************************************************************************/
int  GetAdjustMode(char *InputYHcode)
{	
	int i ;
	int  rowscount;
	char  mode[5];
	int  AdjustMode;
	memset(mode,'\0',sizeof(mode));	
	rowscount=atol(YHRateDescriptionHead.Recordcount);	
	for(i=0;i<rowscount;i++)
	{	
		if (0==strncmp(InputYHcode,YHRateDescriptionRecord[i].YHCode,3))
		{	
			  strncpy(mode,YHRateDescriptionRecord[i].AdjustMode,sizeof(YHRateDescriptionRecord[i].AdjustMode));	
			  AdjustMode=atoi(mode);	
			  return AdjustMode;
		}
	}
	return 0;
}

/************************************************************************************************************
*获取进位模式
************************************************************************************************************/
int  GetCarryMode(char *InputYHcode)
{	
	int i ;
    long int  rowscount;
    char  mode[3];
    int  CarryMode;
    memset(mode,'\0',sizeof(mode));	
    rowscount=atol(YHRateDescriptionHead.Recordcount);	
    for(i=0;i<rowscount;i++)
    {	
        if(0==strncmp(InputYHcode,YHRateDescriptionRecord[i].YHCode,3))
        {	
            strncpy(mode,YHRateDescriptionRecord[i].CarryMode,sizeof(YHRateDescriptionRecord[i].CarryMode));	
            CarryMode=atoi(mode);	
            return CarryMode;
        }
    }
    return  0;
}

/************************************************************************************************************
*获取优惠率
************************************************************************************************************/
int  GetYHRate(char *InputYHcode)
{	
	int i ;
	long int  rowscount;
	char  Rate[4];
	char Reacordc[6];
	float YHRate;
	memset(Rate,'\0',sizeof(Rate));	
	strncpy(Reacordc,YHRateDescriptionHead.Recordcount,sizeof(YHRateDescriptionHead.Recordcount));	
	rowscount=atol(Reacordc);	
	memset(Rate,0x00,3);	
	for(i=0;i<rowscount;i++)
		{	
			if (0==strncmp(InputYHcode,YHRateDescriptionRecord[i].YHCode,3))
				{	
							strncpy(Rate,YHRateDescriptionRecord[i].YHRate,sizeof(YHRateDescriptionRecord[i].YHRate));	
							YHRate=atoi(Rate);								
							return YHRate;
				}
	  }

	return 0;
}




/*********************************************************************************************
*传入优惠前的金额，经过算法运算后返优惠后的金额Fact_Money
***********************************************************************************************/

int GetFactMoney(int Input,int YHL ,int adjustmod,int carrymod)
{	
	int A;
	int B;
	int Ret;
	if (YHL>0)
	{
		adjustmod*=10;
		adjustmod = adjustmod==0? 1000:adjustmod;
		A=(Input*YHL)/adjustmod;
		B=(Input*YHL)%adjustmod;	
		if(0==B || 3==carrymod)
		{	
			Ret= (A*adjustmod)/100;
	
		}
		else
		{	
			if(2==carrymod || B>=(adjustmod/2) )
			{	
				Ret=(A*adjustmod+adjustmod)/100;
			}
			else
			{	
				Ret= (A*adjustmod)/100;
			}
	
		}
		return Ret<(adjustmod/100)? adjustmod/100 :Ret;
	}
	else
	{
		return 0;
	}



}
//int  GetFactMoney(float  receivemoney,char *YHCode)
//{	
//		float  A;
//		int 	B;
//		int 	C;
//		int 	D;
//		float 	E;
//		int Fact_Money;
//		float  YHRate;
//		int  adjustmode;
//		int  carrymode;
//		Fact_Money=0;
//		YHRate=GetYHRate(YHCode);	
//		adjustmode=GetAdjustMode(YHCode);	
//		carrymode=GetCarryMode(YHCode);	
//	    A=receivemoney*YHRate;
//		B=(int)(A*10);	
//		C=B/adjustmode;
//		D=B%adjustmode;
//		E=((float)D/adjustmode)*10;
//		if(1==carrymode)
//		{	
//			if(E>=5.0)
//			{	
//				Fact_Money=C*adjustmode+adjustmode;
//			}
//			else
//			{	
//				Fact_Money=C*adjustmode;
//			}
//		}
//		else if (2==carrymode)
//		{	
//			if(E!=0)
//			{	
//				Fact_Money=C*adjustmode+adjustmode;
//			}
//			else
//			{	
//				Fact_Money=C*adjustmode;
//			}
//		}
//		else if(3==carrymode)
//		{	
//			Fact_Money=C*adjustmode;
//		}
//
//		 Fact_Money=Fact_Money /10; //计算出的结果单位是角，除以10转换成元，如果有零点几元的情况看怎么处理，等待沟通！！
//		return Fact_Money;
//
//}
//
//
//
