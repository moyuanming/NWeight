// ***************************************************************
//  ClearAndArchiveData   version:  1.0   ��  date: 01/07/2008
//  -------------------------------------------------------------
//  ������浵����
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "LocalIncludeFile.h"
#define ArchiveFileCommand(_sysCommand_, _PATH_,_FileDate_) sprintf(_sysCommand_," tar cz %s%s > %sArchive/%s.tar.gz; rm -f %s%s %c",_PATH_,_FileDate_,_PATH_,_FileDate_,_PATH_,_FileDate_,0x00)
#define ClearFileCommand(_sysCommand_, _PATH_,_FileDate_) sprintf(_sysCommand_," rm -f %s%s %c",_PATH_,_FileDate_,0x00)
#define FTPPUTCOMMANDUPLOAD(_sysCommand_, _r_file_  ,_l_file_) sprintf(_sysCommand_,"ftpput -u %s -p %s %s LDCIMAGE\\\\%s %s %c",GetFtpUserName(),GetFtpPwd(),GetFtpServerIP(),_r_file_,_l_file_,0x00  )

static int LogArchiveDays   =1;
static int SendArchiveDays  =1;
static int RecvArchiveDays  =1;
static int LogClearDays         =10;
static int SendClearDays        =10;
static int RecvClearDays        =10;
int main(void);
/****************************************************************************************
* ������ڵ�����
*****************************************************************************************/
static void ClaerFile(const char *InputPath,char *InputFileName)
{
	char _sysCommand_[200];
	ClearFileCommand(_sysCommand_,InputPath,InputFileName);
	echoic("ClearAndArchive Exec System :%s",_sysCommand_);
	if (0==system(_sysCommand_))
	{
		echoic("ClearAndArchive ɾ��%s�µ�����Ϊ%s�ľ��ļ� ",InputPath,InputFileName);
	}
}
/****************************************************************************************
* �浵����
* ��������ʹ��tarѹ����洢��ָ��Ŀ¼��
*****************************************************************************************/
static void ArchiveFile(const char *InputPath,char *InputFileName)
{
	char _sysCommand_[200];
	ArchiveFileCommand(_sysCommand_,InputPath,InputFileName);
	echoic("ClearAndArchive   Exec System :%s",_sysCommand_);
	if (0==system(_sysCommand_))
	{
		echoic("ClearAndArchive ��%s�µ�����Ϊ%s�ľ��ļ�ѹ���鵵��%sArchive",InputPath,InputFileName,InputPath);
	}
}
/****************************************************************************************
* ɨ��Ŀ¼ �鿴���� �������������ļ����д��� һ��ֻ����һ��
*****************************************************************************************/
static int ScanDir( const char *InputPath,const char *InputFileType,const int Days,void (*HandFile)(const char *InputPath,char *InputFileName))
{
	DIR * DataDir;
	char *CurrentDataName;
	struct dirent * ptr;
	char *DateStart;
	DataDir   = opendir(InputPath);
	if (DataDir <0)
	{
		return 0;
	}
	ptr = readdir(DataDir);
	while (NULL != ptr)
	{
		CurrentDataName = (char *)ptr->d_name;
		echoic("CurrentDataName:[%s],InputFileType:[%s],DateStart:[%s,%s]",CurrentDataName,InputFileType,strstr(CurrentDataName,"20"),GetTimeAddTime(DATETIME_FORMAT_YYYY_MM_DD,0-Days,ADDTIME_TYPE_DAY));
		if ( NULL != strstr(CurrentDataName,InputFileType) )
		{
			DateStart = strstr(CurrentDataName,"20");//���꿪ʼ��ȡ����ַ���
			echoic("DateStart:[%s],GetTimeAddTime:[%s]",DateStart,GetTimeAddTime(DATETIME_FORMAT_YYYY_MM_DD,0-Days,ADDTIME_TYPE_DAY));

			if ( NULL != DateStart &&
				 strncmp(DateStart,GetTimeAddTime(DATETIME_FORMAT_YYYY_MM_DD,0-Days,ADDTIME_TYPE_DAY),10) <0)
			{
				echoic("asdfsad  %d",Days );
				HandFile(InputPath,CurrentDataName) ;
				usleep(1000);
			}
		}
		ptr = readdir(DataDir);
	}
	closedir(DataDir);
	return 1;
}
/****************************************************************************************
* ���������ļ�
*****************************************************************************************/
static void LoadClearAndArchiveConfig(void)
{
	LoadIniFile(LANECONFIGFILENAME_FILE);   echo_everyline("--");
	/*fprintf(stderr,"readItemInIniFile= %s",readItemInIniFile("NetNo"));	echo_everyline("--");*/
	LogArchiveDays = atoi(readItemInIniFile("LogArchiveDays")); echo_everyline("--");
	SendArchiveDays = atoi(readItemInIniFile("SendArchiveDays"));   echo_everyline("--");
	RecvArchiveDays = atoi(readItemInIniFile("RecvArchiveDays"));   echo_everyline("--");
	LogClearDays = atoi(readItemInIniFile("LogClearDays")); echo_everyline("--");
	SendClearDays = atoi(readItemInIniFile("SendClearDays"));   echo_everyline("--");
	RecvClearDays = atoi(readItemInIniFile("RecvClearDays"));   echo_everyline("--");
}
/****************************************************************************************
* �ϴ�ͼƬ ��һ���߳� 1������һ��
* �����ļ� �봦���ļ� 30������һ�Σ�
*****************************************************************************************/
int main(void)
{
	LoadClearAndArchiveConfig();    echo_everyline("--");
	//LoadCommunctionConfig();    echo_everyline("--");
	while (1)
	{
		//ScanDir(FILENAME_LOG_FILE_PATH,".Log",LogArchiveDays,ArchiveFile);  echo_everyline("--");
		//sleep(30);   echo_everyline("--");
		//ScanDir(FILENAME_SEND_MSG_BACKUP_FILE_Archive,".DAT",SendArchiveDays,ArchiveFile);  echo_everyline("--");
		//sleep(1);
		//ScanDir(FILENAME_SEND_MSG_BACKUP_FILE_Archive,".ARC",SendClearDays,ClaerFile);   echo_everyline("--");
		//sleep(1);   echo_everyline("--");
		ScanDir(FILENAME_LOG_FILE_PATH,".Log",LogClearDays,ClaerFile);   echo_everyline("--");
		sleep(3600*12);   echo_everyline("--");
	}
	return 1;
}

