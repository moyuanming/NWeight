#include "LocalIncludeFile.h"

/******************************************************************************************************
*服务器通讯状态
******************************************************************************************************/
int DevCStatePlazaServerState = 0;
int DevCStatePlazeServerSendFlag = 1;
void SetDevCStatePlazaServerState(int InputDevCStatePlazaServerState)
{	
	if(DevCStatePlazaServerState != InputDevCStatePlazaServerState )
	{	
		DevCStatePlazeServerSendFlag = 1;
		DevCStatePlazaServerState = InputDevCStatePlazaServerState;
		//ShowDevCStatePlazaServerState();	
	}
}
void ShowDevCStatePlazaServerState()
{	
    if (!DevCStatePlazaServerState)
    {		
        //SendMsgEI(MSGEI_SERVER_CONNECTED,MSGEI_STATUS_MSGINFO,"服务器通信恢复");	
		//SendTCOMsg( MSGTCO_NETWORK,"1");	
       // show_Help("服务器通信恢复");	
		
			
    }
    //else
    //{	
    //   //SendMsgEI(MSGEI_SERVER_DISCONNECT,MSGEI_STATUS_MSGINFO,"服务器通信故障");	
		
    //    //show_Help("服务器通信故障");	
    //}
}
int GetDevCStatePlazaServerState()
{	
	return DevCStatePlazaServerState;
}




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

//把U盘上的数据导出到U盘
void  DataExporter(void)
{	
    char *result;
    char *result_usb0;
    char *result_umount;
    char *result_mount;
    char *result_check1;
    char *result_check2;
    char *result_check3;
    if( 1==GetDevCStatePlazaServerState())
    {	
        UI_Show_Help_Info("和服务器通讯正常，不允许导出数据......\n按【取消】键取消。");	
        return;
    }
    UI_Show_Info("检查是否存在可移动存储设备......");	
    result=DoSysCmd("cat /proc/scsi/scsi");	
    if(0==strcmp(result,"Attached devices: none\n"))
    {	
        UI_Show_Info("对不起，没有发现任何设备！");	
        return;
    }
    result_usb0=DoSysCmd("cat /proc/scsi/usb-storage-0/0");	
    if(NULL==strstr(result_usb0 ,"Attached: Yes"))
    {	
        UI_Show_Info("对不起，设备未连接!");	
        return;
    }
    UI_Show_Info("存在可移动存储设备，正在尝试挂载...... ");	
    result_umount=   DoSysCmd("umount "FILENAME_USBDIR );	
    result_mount=DoSysCmd("mount  -t vfat  /dev/scsi/host0/bus0/target0/lun0/part1 "FILENAME_USBDIR);	
    if( NULL!=strstr(result_mount ,"failed:"))
    {	
        result_check1=DoSysCmd("mount");	
        if(NULL!=strstr(result_check1,"/dev/scsi/host0/bus0/target0/lun0/part1 on "FILENAME_USBDIR))
        {	
            UI_Show_Info("对不起，未能挂载可移动存储设备！");	
            return;
        }
    }
    UI_Show_Info("成功挂载可移动存储设备，正在准备复制文件..... ");	
    result_check2=DoSysCmd("ls "FILENAME_USBDIR""FILENAME_ARCATUSB);	
    if( NULL!=strstr(result_check2,"No such file or directory"))
    {	
        if( NULL!=strstr(DoSysCmd("mkdir "FILENAME_USBDIR""FILENAME_ARCATUSB),"mkdir:"))
        {	
            UI_Show_Info("对不起，创建目录时遇到问题!");	
            return;
        }
    }
    result_check3=DoSysCmd("ls "FILENAME_USBDIR""FILENAME_ARCATUSB);	
    if(strlen(result_check3)>1 )
    {	
        if( NULL!=strstr(result_check3,"No such file or directory"))
        {	
            UI_Show_Info("对不起，目录创建失败！");	
            return;
        }
        else
        {	
            UI_Show_Info("对不起,您可移动设备的目录【"FILENAME_ARCATUSB"】非空！");	
            return;
        }
    }
    UI_Show_Info("正在复制文件..... ");	
    if( NULL!=strstr(DoSysCmd("cp "FILENAME_SEND_MSG_BACKUP_FILE_Archive"* "FILENAME_USBDIR""FILENAME_ARCATUSB ),"cp:"))
    {	
        UI_Show_Info("对不起，复制文件时遇到问题!");	
        return;
    }
    UI_Show_Info("正在清理文件..... ");	
    if( NULL!=strstr(DoSysCmd("rm  "FILENAME_SEND_MSG_BACKUP_FILE_Archive"* "),"rm:"))
    {	
        UI_Show_Info("对不起，移除文件时遇到问题！");	
        return;
    }
    UI_Show_Info("文件复制完成！请拔出您的可移动存储设备！按【取消】键退出！");	
}



