// ***************************************************************
//  ClearAndArchiveData   version:  1.0   ·  date: 01/07/2008
//  -------------------------------------------------------------
//  清理与存档数据
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
* 清理过期的数据
*****************************************************************************************/
static void ClaerFile(const char *InputPath,char *InputFileName)
{
	char _sysCommand_[200];
	ClearFileCommand(_sysCommand_,InputPath,InputFileName);
	echoic("ClearAndArchive Exec System :%s",_sysCommand_);
	if (0==system(_sysCommand_))
	{
		echoic("ClearAndArchive 删除%s下的日期为%s的旧文件 ",InputPath,InputFileName);
	}
}

/****************************************************************************************
* 扫描目录 查看日期 将符合条件的文件进行处理 一次只处理一批
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
			DateStart = strstr(CurrentDataName,"20");//从年开始获取年的字符串
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
* 载入配置文件
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
* 上传图片 开一个线程 1秒钟做一次
* 清理文件 与处理文件 30分钟做一次！
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

