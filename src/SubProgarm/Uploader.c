// ***************************************************************
//  Uploader ����ͼƬ�ϴ�
// ***************************************************************

#include "LocalIncludeFile.h"
 
#define FTPPUTCOMMANDUPLOAD(_sysCommand_, _r_file_  ,_l_file_) sprintf(_sysCommand_,"ftpput -u %s -p %s %s LDCIMAGE\\\\%s %s %c",GetFtpUserName(),GetFtpPwd(),GetFtpServerIP(),_r_file_,_l_file_,0x00  )
#define MOVEIMGE(_sysCommand_,_l_file_) sprintf(_sysCommand_,"mv %s %s",_l_file_,FILENAME_SAVE_ImageArchive)
#define RMIMGE(_sysCommand_,_l_file_) sprintf(_sysCommand_,"rm %s ",_l_file_)
char ret[3024];
char *DoSysCmd(char * cmdline)
{	
    FILE *fp;
    char line[32];
    char cmdtmp[256];
    memset(cmdtmp,0x00,sizeof(cmdtmp)); 
    sprintf(cmdtmp,"%s  2>&1",cmdline); 
    memset(ret,0x00,sizeof(ret));   
    fp = popen(cmdtmp, "r");    
    while( fgets( line, sizeof(line), fp))
    {	
        sprintf(ret ,"%s%s",ret,line);	
    }
    pclose(fp);	
    return ret;
}
 
 
 
/****************************************************************************************
* �ϴ�ͼƬ��������
*****************************************************************************************/
int UploadImg(void)
{   
	DIR * PictureDir;
	char FtpCommandStr[300];
	char FullImageName[100];
	struct dirent * ptr;
	char * result;
	PictureDir   = opendir(FILENAME_SAVE_ImageUPLOAD);
	if (PictureDir <0)
	{
		return 0;
	}
	ptr = readdir(PictureDir);
	while (NULL != ptr)
	{
		if (NULL != strstr((char *)ptr->d_name,".IMG"))
		{
			memset(FtpCommandStr,0x00,sizeof(FtpCommandStr));
			memset(FullImageName,0x00,sizeof(FullImageName));
			sprintf(FullImageName,"%s%s%c",FILENAME_SAVE_ImageUPLOAD,(char *)ptr->d_name,0x00);
			FTPPUTCOMMANDUPLOAD(FtpCommandStr,(char *)ptr->d_name,FullImageName);
			//echoic("ִ��FTP����:%s",FtpCommandStr);
			result=DoSysCmd(FtpCommandStr);
			//echoic(" ���ؽ��Ϊ:%s",result);
			if (result==NULL || strlen(  result)==0 )
			{
				char cmds[100];
				//RMIMGE(cmds);
				RMIMGE(cmds,FullImageName);
				result=DoSysCmd(cmds);
				//echoic("  ִ������:%s",cmds);
				//echoic("���ؽ��Ϊ:%s",result);
				if (result==NULL || strlen(  result)==0 )
				{
					//echoic("  ɾ���ļ�:%s",FullImageName);
					remove(FullImageName);
				}
				else
				{
					//echoic("�������쳣");
				}
			}
			else
			{
					//echoic("FTP��������쳣");
			}
		}
		ptr = readdir(PictureDir);
	}
	closedir(PictureDir);
	return 1;
}
//end_Image
 
/****************************************************************************************
* �ϴ�ͼƬ ��һ���߳� 1������һ��
* �����ļ� �봦���ļ� 30������һ�Σ�
*****************************************************************************************/
int main(void)
{   
	LoadIniFile(LANECONFIGFILENAME_FILE);
	LoadCommunctionConfig();
	while (1)
	{
		UploadImg();
		sleep(1);
	}
	return 1;
}
