//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:39
#include "LocalIncludeFile.h"
struct MSG_IMAGE * MsgImage;
void InitMsgImage(void)
{
    memset((char *)MsgImage,'0',sizeof(struct MSG_IMAGE));
}

struct MSG_IMAGE *GetMsgImage(void)
{
    return  MsgImage;
}
void SetImageMsgID(char* InputID)
{
    strncpy(MsgImage->ID,InputID,sizeof(MsgImage->ID));
}
void SetImageMsgNetWork(char* InputNetWork)
{
    strncpy(MsgImage->NetWork,InputNetWork,sizeof(MsgImage->NetWork));
}
void SetImageMsgPlaza(char* InputPlaza)
{
    strncpy(MsgImage->Plaza,InputPlaza,sizeof(MsgImage->Plaza));
}
void SetImageMsgYear(char* InputYear)
{
    strncpy(MsgImage->Year,InputYear,sizeof(MsgImage->Year));
}
void SetImageMsgDay(char* InputDay)
{
    strncpy(MsgImage->Day,InputDay,sizeof(MsgImage->Day));
}
void SetImageMsgHour(char* InputHour)
{
    strncpy(MsgImage->Hour,InputHour,sizeof(MsgImage->Hour));
}
void SetImageMsgYMD(char* InputYMD)
{
    strncpy(MsgImage->YMD,InputYMD,sizeof(MsgImage->YMD));
}
void SetImageMsgCPHM(char* InputCPHM)
{
    //strncpy(MsgImage->CPHM,InputCPHM,sizeof(MsgImage->CPHM));
	char temp[sizeof(MsgImage->CPHM)+1];
	strncpy(MsgImage->CPHM,PadLeft('@',InputCPHM,temp,sizeof(MsgImage->CPHM)),sizeof(MsgImage->CPHM));   
}
void SetImageMsgTime(char* InputTime)
{
    strncpy(MsgImage->Time,InputTime,sizeof(MsgImage->Time));
}
void SetImageMsgLaneType(char InputLaneType)
{
    MsgImage->LaneType=InputLaneType;
}
void SetImageMsgLaneName(char* InputLaneName)
{
    strncpy(MsgImage->LaneName,InputLaneName,sizeof(MsgImage->LaneName));
}
void SetImageMsgTrans(char* InputTrans)
{
    strncpy(MsgImage->Trans,InputTrans,sizeof(MsgImage->Trans));
}
void SetImageMsgSubTrans(char InputSubTrans)
{
    MsgImage->SubTrans=InputSubTrans;
}
void SetImageMsgEntryNetwork(char* InputEntryNetwork)
{
    strncpy(MsgImage->EntryNetwork,InputEntryNetwork,sizeof(MsgImage->EntryNetwork));
}
void SetImageMsgEntryPlaza(char* InputEntryPlaza)
{
    strncpy(MsgImage->EntryPlaza,InputEntryPlaza,sizeof(MsgImage->EntryPlaza));
}
void SetImageMsgType(char *InputType)
{
    strncpy(MsgImage->Type,InputType,3);
}
void SetImageMsgClass(char InputClass)
{
    MsgImage->Class=InputClass;
}
void SetImageMsgStatus(char InputStatus)
{
    MsgImage->Status=InputStatus;
}
void SetImageMsgCollector(char* InputCollector)
{
    strncpy(MsgImage->Collector,InputCollector,sizeof(MsgImage->Collector));
}
void SetImageMsgTollFare(char* InputTollFare)
{
    strncpy(MsgImage->TollFare,InputTollFare,sizeof(MsgImage->TollFare));
	MsgImage->TollFare[3]= ' ';

}
void SetImageMsgPictureNum(int InputPictureNum)
{
    sprintf(MsgImage->PictureNum,"%010d",InputPictureNum);
}
void SetImageMsgMARK(char InputMARK)
{
    MsgImage->MARK=InputMARK;
}


/******************************************************************************************************
* 生成新的抓拍图片文件名
******************************************************************************************************/
char CapImgNameFullPath[100];
char CapImgName[50];
int CapImgIndex=0;
char *CreateCapImgName(void)
{
    CapImgName[0]='I';
    memcpy(&CapImgName[1],GetTime(DATETIME_FORMAT_YYYYMMDDHHMMSS),14);
    memcpy(&CapImgName[15],GetLanConfigLaneNo(),3);
    CapImgIndex++;
    if(CapImgIndex>9999)
    {
        CapImgIndex = 0;
    }
    sprintf(CapImgNameFullPath,"%s%s%04d%c",FILENAME_SAVE_ImageUPLOAD,CapImgName,CapImgIndex,0x00);
    return CapImgNameFullPath;
}
static sem_t CaptureImg_Sync;
void InitImgSync(void)
{
	sem_init((sem_t *)&CaptureImg_Sync,0,0);
}
void PostImgSync(void)
{
	sem_post((sem_t *)&CaptureImg_Sync);
}

char TempCapImgNameFullPath[100];
int CaptureImg(char imageid)
{
   
	static int pipe_fd=-1,pipe_read_fd=-1;
	char buf[5];
	static char Cap_First_Flag=1;
	char ReadLen=0;
	sem_wait((sem_t *)&CaptureImg_Sync);
	sprintf(TempCapImgNameFullPath,"%s%c%s%c",FILENAME_SAVE_ImageTEMP,imageid,"TEMP.JPG",0x00);
	if (EnabledVideo())
	{
		SaveJpg(TempCapImgNameFullPath,352, 288, 16);
	}
	else
	{
		if (Cap_First_Flag)
		{
			pipe_fd = open("/dev/shm/VideoFifo", O_WRONLY);
			pipe_read_fd = open("/dev/shm/VideoRead", O_RDONLY);
			Cap_First_Flag=0;
		}
		if (pipe_fd== -1)
		{
			perror("pipe_fd");
			//echo("CAPTURE ERROE  \n");
			return -1;
		}

		write(pipe_fd,TempCapImgNameFullPath,strlen(TempCapImgNameFullPath)+1);
		do
		{
			ReadLen+=read(pipe_read_fd,buf,3);
		}while (ReadLen<3);
	}
	
	PostImgSync();
	return 0;
}
void LoadImageHeader(void)
{
        MsgImage=  GetSyncImageHeader();
}
struct MSG_IMAGE *GetSyncImageHeader(void)
{
	struct MSG_IMAGE *SyncmFile;
	int FilePointer;
	if(!FileExists(FILENAME_SAVE_ImageHeader))
	{
		CreateMsgFile(FILENAME_SAVE_ImageHeader,sizeof(struct MSG_IMAGE));
	}
	FilePointer = open(FILENAME_SAVE_ImageHeader,O_RDWR);
	SyncmFile = (struct MSG_IMAGE *)mmap(0,sizeof(struct MSG_IMAGE),PROT_READ|PROT_WRITE, MAP_SHARED, FilePointer, 0);
	return SyncmFile;
}
void BuildImageFiles(char * msghead,     struct MSG_EXITTR*exittr)
{
	struct MSG_HEAD  mh ;
	char desImage1[100];
	char desImage2[100];
	char temp[50];
	memset(desImage1,0x00,sizeof(desImage1));
	memset(desImage2,0x00,sizeof(desImage2));
	memset(&mh,' ',sizeof(struct MSG_HEAD));
    memcpy(&mh,msghead,sizeof(struct MSG_HEAD));    
    SetImageMsgClass(exittr->ExitClass);
    SetImageMsgCollector(mh.Collector );
    SetImageMsgDay(mh.Day );
    SetImageMsgHour (mh.Hour );
    SetImageMsgLaneName(mh.LaneNo );
    SetImageMsgLaneType(mh.LaneType);
    SetImageMsgMARK('0');
    SetImageMsgNetWork(mh.NetNo);
    SetImageMsgPictureNum(2);
    SetImageMsgPlaza(mh.PlazaNo);
    SetImageMsgStatus('1');
    SetImageMsgTime(mh.YYYYMMDDHHMMSS);
    SetImageMsgTollFare(exittr->EntryLane);
	SetImageMsgSubTrans(exittr->subtranNo);
    SetImageMsgTrans(exittr->tranNo);
    SetImageMsgYear(mh.Year );
	SetImageMsgType(exittr->ExitType);
	
	SetImageMsgYMD(mh.YYYYMMDD);
	//09年7月13日对Image添加了票据号和支付方法、争议类型。
	strncpy( GetMsgImage()->ReceiptNo,exittr->ReceiptNo,sizeof(GetMsgImage()->ReceiptNo));
	//增加车牌号码
	SetImageMsgCPHM(GetCPHM(temp));
	GetMsgImage()->Method_Pay=exittr->Method_Pay;
	GetMsgImage()->DisputeType=exittr->DisputeType;
    CreateCapImgName();
    if(msync((void *)&MsgImage, sizeof(struct MSG_IMAGE), MS_SYNC)<0)
    {
        LogCAppLog("Msync Faile!");
    }
	echoic(" sizeof(struct MSG_IMAGE  %d", sizeof(struct MSG_IMAGE));
		echoic("MsgImage  %s", substring((char*)GetMsgImage(),sizeof(struct MSG_IMAGE) ));
	sprintf(desImage1,"%s_1.IMG",CapImgNameFullPath);
	sprintf(desImage2,"%s_2.IMG",CapImgNameFullPath);
	StructAndFile(MsgImage, FILENAME_SAVE_ImageTEMP"1TEMP.JPG",GetFileSize(FILENAME_SAVE_ImageTEMP"1TEMP.JPG"), desImage1);
	StructAndFile(MsgImage, FILENAME_SAVE_ImageTEMP"2TEMP.JPG",GetFileSize( FILENAME_SAVE_ImageTEMP"2TEMP.JPG"), desImage2);
}
char TCOImage[50];
char * BuildTCOImage(char msgtype ,char *msg)
{
	struct MSG_HEAD  * mh;
	char   msgx[300];
	char desImage3[100];
	char  cnum[12];
	char tran[10];
	memset(msgx,0x00,sizeof(msgx));
	memset(cnum,0x00,sizeof(cnum));
	memset(tran,0x00,sizeof(tran));
	memset(desImage3,' ',sizeof(desImage3));
	mh=GetMsgHead();
	InitMsgMSG_TCOIMAGE();
	SetMSG_TCOIMAGEMsgCollector(SUBSTRING(mh->Collector));
	SetMSG_TCOIMAGEMsgDateTime(SUBSTRING(mh->YYYYMMDDHHMMSS));
	SetMSG_TCOIMAGEMsgKind(' ' );
	SetMSG_TCOIMAGEMsgLaneName(SUBSTRING(mh->LaneNo));
	SetMSG_TCOIMAGEMsgLaneType(mh->LaneType);
	SetMSG_TCOIMAGEMsgStatus(' ');
	sprintf(msgx,"%-250s",msg);
	strncpy(GetMsgMSG_TCOIMAGE()->MsgInfo,msgx,sizeof(GetMsgMSG_TCOIMAGE()->MsgInfo));
	SetMSG_TCOIMAGEMsgMsgType(msgtype);
	SetMSG_TCOIMAGEMsgNetWork(SUBSTRING(mh->NetNo));
	SetMSG_TCOIMAGEMsgPlaza(SUBSTRING(mh->PlazaNo));
	SetMSG_TCOIMAGEMsgStatus('0');
	sprintf(cnum,"%10s",GetCardContext_CardNumber());
	SetMSG_TCOIMAGEMsgSVRCard(cnum);
	sprintf(tran,"%4d",g_TranNo);
	strncpy(GetMsgMSG_TCOIMAGE()->Trans,tran,sizeof(GetMsgMSG_TCOIMAGE()->Trans));
	CaptureImg('3');
	CreateCapImgName();
	sprintf(desImage3,"%s_3.IMGTCO",CapImgNameFullPath);
	strcpy(TCOImage,(char *)&desImage3[strlen(FILENAME_SAVE_ImageUPLOAD)]);
	StructAndFileTCOIMG(GetMsgMSG_TCOIMAGE(), FILENAME_SAVE_ImageTEMP"3TEMP.JPG",GetFileSize(FILENAME_SAVE_ImageTEMP"3TEMP.JPG"), desImage3);
	return TCOImage;
}
int GetFileSize(char *FileName)
{
	struct stat buf;
	int fd;
	int FileLength=0;
	fd= open(FileName,O_RDONLY);
	if(fd<0)
	{
		return 0;
	}
	fstat(fd,&buf);
	FileLength = buf.st_size;
	close(fd);
	return FileLength;
}
int StructAndFile(struct MSG_IMAGE *CapImageHeader,char *SourFileName,int SourFileLength ,char *DesFileName)
{
	FILE *Sourfp,*DesFp;
	char Buf[1000000];
	int ret=0;

	DesFp = fopen(DesFileName, "wt+");
	if(DesFp==NULL)
	{

		return -1;
	}
	fwrite((char *)CapImageHeader, sizeof(struct MSG_IMAGE), 1, DesFp);
	if(SourFileLength>0)
	{
		Sourfp = fopen(SourFileName, "rb");
	}
	else
	{
		SourFileLength = GetFileSize("res/error.JPG");
		Sourfp = fopen("res/error.JPG", "rb");
	}
	if(Sourfp==NULL)
	{
		fclose(DesFp);
		return -1;
	}
	if( fread(Buf,SourFileLength,1,Sourfp) )
	{
		//echo("RUN");
		fwrite(Buf,SourFileLength,1,DesFp)	;
		ret =1;
	}
	else
	{
		ret= -1;
	}
	fclose(Sourfp);
	fclose(DesFp);
	//echo("RUN %d",ret);
	return ret;
}

int StructAndFileTCOIMG(struct MSG_TCOIMAGE *CapImageHeader,char *SourFileName,int SourFileLength ,char *DesFileName)
{
	FILE *Sourfp,*DesFp;
	char Buf[1000000];
	int ret=0;

	DesFp = fopen(DesFileName, "wt+");
	if(DesFp==NULL)
	{

		return -1;
	}
	fwrite((char *)CapImageHeader, sizeof(struct MSG_TCOIMAGE), 1, DesFp);
	if(SourFileLength>0)
	{
		Sourfp = fopen(SourFileName, "rb");
	}
	else
	{
		SourFileLength = GetFileSize("res/error.JPG");
		Sourfp = fopen("res/error.JPG", "rb");
	}
	if(Sourfp==NULL)
	{
		fclose(DesFp);
		return -1;
	}
	if( fread(Buf,SourFileLength,1,Sourfp) )
	{
		//echo("RUN");
		fwrite(Buf,SourFileLength,1,DesFp)	;
		ret =1;
	}
	else
	{
		ret= -1;
	}
	fclose(Sourfp);
	fclose(DesFp);
	//echo("RUN %d",ret);
	return ret;
}

struct MSG_TCOIMAGE MsgMSG_TCOIMAGE;
void InitMsgMSG_TCOIMAGE(void)
{
memset((char *)&MsgMSG_TCOIMAGE,'0',sizeof(struct MSG_TCOIMAGE));
}
struct MSG_TCOIMAGE *GetMsgMSG_TCOIMAGE(void)
{
return (struct MSG_TCOIMAGE  *)&MsgMSG_TCOIMAGE;
}
void SetMSG_TCOIMAGEMsgNetWork(char* InputNetWork)
{
	strncpy(MsgMSG_TCOIMAGE.NetWork,InputNetWork,sizeof(MsgMSG_TCOIMAGE.NetWork));
}
void SetMSG_TCOIMAGEMsgPlaza(char* InputPlaza)
{
	strncpy(MsgMSG_TCOIMAGE.Plaza,InputPlaza,sizeof(MsgMSG_TCOIMAGE.Plaza));
}
void SetMSG_TCOIMAGEMsgDateTime(char* InputDateTime)
{
	strncpy(MsgMSG_TCOIMAGE.DateTime,InputDateTime,sizeof(MsgMSG_TCOIMAGE.DateTime));
}
void SetMSG_TCOIMAGEMsgLaneType(char InputLaneType)
{
MsgMSG_TCOIMAGE.LaneType=InputLaneType;
}
void SetMSG_TCOIMAGEMsgLaneName(char* InputLaneName)
{
	strncpy(MsgMSG_TCOIMAGE.LaneName,InputLaneName,sizeof(MsgMSG_TCOIMAGE.LaneName));
}
void SetMSG_TCOIMAGEMsgTrans(char* InputTrans)
{
	strncpy(MsgMSG_TCOIMAGE.Trans,InputTrans,sizeof(MsgMSG_TCOIMAGE.Trans));
}
void SetMSG_TCOIMAGEMsgSubTrans(char InputSubTrans)
{
MsgMSG_TCOIMAGE.SubTrans=InputSubTrans;
}
void SetMSG_TCOIMAGEMsgEntryNetwork(char* InputEntryNetwork)
{
	strncpy(MsgMSG_TCOIMAGE.EntryNetwork,InputEntryNetwork,sizeof(MsgMSG_TCOIMAGE.EntryNetwork));
}
void SetMSG_TCOIMAGEMsgEntryPlaza(char* InputEntryPlaza)
{
	strncpy(MsgMSG_TCOIMAGE.EntryPlaza,InputEntryPlaza,sizeof(MsgMSG_TCOIMAGE.EntryPlaza));
}
void SetMSG_TCOIMAGEMsgType(char InputType)
{
MsgMSG_TCOIMAGE.Type=InputType;
}
void SetMSG_TCOIMAGEMsgKind(char InputKind)
{
MsgMSG_TCOIMAGE.Kind=InputKind;
}
void SetMSG_TCOIMAGEMsgStatus(char InputStatus)
{
MsgMSG_TCOIMAGE.Status=InputStatus;
}
void SetMSG_TCOIMAGEMsgCollector(char* InputCollector)
{
	strncpy(MsgMSG_TCOIMAGE.Collector,InputCollector,sizeof(MsgMSG_TCOIMAGE.Collector));
}
void SetMSG_TCOIMAGEMsgTollFare(char* InputTollFare)
{
	strncpy(MsgMSG_TCOIMAGE.TollFare,InputTollFare,sizeof(MsgMSG_TCOIMAGE.TollFare));
}
void SetMSG_TCOIMAGEMsgSVRCard(char* InputSVRCard)
{
	strncpy(MsgMSG_TCOIMAGE.SVRCard,InputSVRCard,sizeof(MsgMSG_TCOIMAGE.SVRCard));
}
void SetMSG_TCOIMAGEMsgRev1(char* InputRev1)
{
	strncpy(MsgMSG_TCOIMAGE.Rev1,InputRev1,sizeof(MsgMSG_TCOIMAGE.Rev1));
}
void SetMSG_TCOIMAGEMsgMsgInfo(char* InputMsgInfo)
{
	strncpy(MsgMSG_TCOIMAGE.MsgInfo,InputMsgInfo,sizeof(MsgMSG_TCOIMAGE.MsgInfo));
}
void SetMSG_TCOIMAGEMsgMsgType(char InputMsgType)
{
MsgMSG_TCOIMAGE.MsgType=InputMsgType;
}
void SetMSG_TCOIMAGEMsgRev2(char* InputRev2)
{
	strncpy(MsgMSG_TCOIMAGE.Rev2,InputRev2,sizeof(MsgMSG_TCOIMAGE.Rev2));
}

