#include "LocalIncludeFile.h"

/******************************************************************************************************
*������ͨѶ״̬
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
        //SendMsgEI(MSGEI_SERVER_CONNECTED,MSGEI_STATUS_MSGINFO,"������ͨ�Żָ�");	
		//SendTCOMsg( MSGTCO_NETWORK,"1");	
       // show_Help("������ͨ�Żָ�");	
		
			
    }
    //else
    //{	
    //   //SendMsgEI(MSGEI_SERVER_DISCONNECT,MSGEI_STATUS_MSGINFO,"������ͨ�Ź���");	
		
    //    //show_Help("������ͨ�Ź���");	
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

//��U���ϵ����ݵ�����U��
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
        UI_Show_Help_Info("�ͷ�����ͨѶ������������������......\n����ȡ������ȡ����");	
        return;
    }
    UI_Show_Info("����Ƿ���ڿ��ƶ��洢�豸......");	
    result=DoSysCmd("cat /proc/scsi/scsi");	
    if(0==strcmp(result,"Attached devices: none\n"))
    {	
        UI_Show_Info("�Բ���û�з����κ��豸��");	
        return;
    }
    result_usb0=DoSysCmd("cat /proc/scsi/usb-storage-0/0");	
    if(NULL==strstr(result_usb0 ,"Attached: Yes"))
    {	
        UI_Show_Info("�Բ����豸δ����!");	
        return;
    }
    UI_Show_Info("���ڿ��ƶ��洢�豸�����ڳ��Թ���...... ");	
    result_umount=   DoSysCmd("umount "FILENAME_USBDIR );	
    result_mount=DoSysCmd("mount  -t vfat  /dev/scsi/host0/bus0/target0/lun0/part1 "FILENAME_USBDIR);	
    if( NULL!=strstr(result_mount ,"failed:"))
    {	
        result_check1=DoSysCmd("mount");	
        if(NULL!=strstr(result_check1,"/dev/scsi/host0/bus0/target0/lun0/part1 on "FILENAME_USBDIR))
        {	
            UI_Show_Info("�Բ���δ�ܹ��ؿ��ƶ��洢�豸��");	
            return;
        }
    }
    UI_Show_Info("�ɹ����ؿ��ƶ��洢�豸������׼�������ļ�..... ");	
    result_check2=DoSysCmd("ls "FILENAME_USBDIR""FILENAME_ARCATUSB);	
    if( NULL!=strstr(result_check2,"No such file or directory"))
    {	
        if( NULL!=strstr(DoSysCmd("mkdir "FILENAME_USBDIR""FILENAME_ARCATUSB),"mkdir:"))
        {	
            UI_Show_Info("�Բ��𣬴���Ŀ¼ʱ��������!");	
            return;
        }
    }
    result_check3=DoSysCmd("ls "FILENAME_USBDIR""FILENAME_ARCATUSB);	
    if(strlen(result_check3)>1 )
    {	
        if( NULL!=strstr(result_check3,"No such file or directory"))
        {	
            UI_Show_Info("�Բ���Ŀ¼����ʧ�ܣ�");	
            return;
        }
        else
        {	
            UI_Show_Info("�Բ���,�����ƶ��豸��Ŀ¼��"FILENAME_ARCATUSB"���ǿգ�");	
            return;
        }
    }
    UI_Show_Info("���ڸ����ļ�..... ");	
    if( NULL!=strstr(DoSysCmd("cp "FILENAME_SEND_MSG_BACKUP_FILE_Archive"* "FILENAME_USBDIR""FILENAME_ARCATUSB ),"cp:"))
    {	
        UI_Show_Info("�Բ��𣬸����ļ�ʱ��������!");	
        return;
    }
    UI_Show_Info("���������ļ�..... ");	
    if( NULL!=strstr(DoSysCmd("rm  "FILENAME_SEND_MSG_BACKUP_FILE_Archive"* "),"rm:"))
    {	
        UI_Show_Info("�Բ����Ƴ��ļ�ʱ�������⣡");	
        return;
    }
    UI_Show_Info("�ļ�������ɣ���γ����Ŀ��ƶ��洢�豸������ȡ�������˳���");	
}



