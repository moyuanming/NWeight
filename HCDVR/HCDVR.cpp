//============================================================================
// Name        : CPSBTESTCPP.cpp
// Author      : leowoo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <semaphore.h>
#include "hcnetsdk.h"
#include "HCDVR.h"
using namespace std;
char cphm[MAX_LICENSE_LEN];
sem_t CPHM_Semt;
void SetCPHM(char * cp)
{
    sem_wait(&(CPHM_Semt));
    memcpy(cphm, cp, MAX_LICENSE_LEN);
    sem_post(&(CPHM_Semt));
}
char * GetCPHM(char *cp)
{
    sem_wait(&(CPHM_Semt));
    memcpy(cp, cphm, MAX_LICENSE_LEN);
    sem_post(&(CPHM_Semt));
    return cp;

}
void ClearCPHM(void)
{
    sem_wait(&(CPHM_Semt));
    //memset(cphm,0x00, MAX_LICENSE_LEN);
    *cphm = 0;
    sem_post(&(CPHM_Semt));
}
void CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer,
                              char *pAlarmInfo, DWORD dwBufLen, void* pUser)
{
    NET_DVR_PLATE_RESULT m_struResult;
    memcpy(&m_struResult, pAlarmInfo, sizeof(NET_DVR_PLATE_RESULT));
    switch (lCommand)
    {
        case COMM_UPLOAD_PLATE_RESULT:
        {
            SetCPHM(m_struResult.struPlateInfo.sLicense);
            cout << "车牌号:" << m_struResult.struPlateInfo.sLicense << endl;
        }
            break;
        default:
            break;
    }
}
LONG login()
{
    LONG lUserID = -1;
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    while (lUserID < 0)
    {
        lUserID = NET_DVR_Login_V30("192.0.0.64", 8000, "admin", "12345",
                                    &struDeviceInfo);
        cout << "test login" << endl;
        sleep(1);
    }
    cout << "test login ok" << endl;
    return lUserID;
}
LONG SetupAlarmChan(LONG lUserID)
{
    LONG lHandle = -1;
    NET_DVR_CloseAlarmChan_V30(0);
    cout << "test CloseAlarmChan" << endl;
    while (lHandle < 0)
    {
        lHandle = NET_DVR_SetupAlarmChan_V30(lUserID);
        cout << "test SetupAlarmChan" << endl;
        sleep(1);
    }
    NET_DVR_SetDVRMessageCallBack_V30(MessageCallback, NULL);
    cout << "test SetupAlarmChan ok" << endl;
    return lHandle;
}

LONG Reboot(LONG lUserID)
{
    //---------------------------------------
    // 注册设备
    lUserID = login();
    if (lUserID != 0)
    {
        while (!NET_DVR_RebootDVR(lUserID))
        {
            cout << "test RebootDVR" << endl;
            sleep(1);
        }
        NET_DVR_Logout(lUserID);
        cout << "test RebootDVR ok" << endl;
        sleep(10);
        lUserID = login();
    }
    return lUserID;
}

LONG DVR_lUserID;
LONG DVR_lHandle;
void * InitCP(void * nul)
{
    //---------------------------------------
    // 初始化
    memset(cphm, 0x00, sizeof(cphm));
    sem_init(&(CPHM_Semt), 0, 1);
    NET_DVR_Init();
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
    //---------------------------------------
    // 注册设备
    DVR_lUserID = Reboot(DVR_lUserID);
    //启用布防
    DVR_lHandle = SetupAlarmChan(DVR_lUserID);
    return 0;
}
static pthread_t ParamUThread;
int DVR_Open(void)
{
    int ret;
    pthread_attr_t new_attr;
    pthread_attr_init(&new_attr);
    pthread_attr_setdetachstate(&new_attr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&ParamUThread, &new_attr, InitCP, 0);
    pthread_attr_destroy(&new_attr);
    return ret;
}
void DVR_Close()
{
    NET_DVR_SetupAlarmChan_V30(DVR_lHandle);
    NET_DVR_Logout(DVR_lUserID);
    NET_DVR_Cleanup();
}
int main()
{
    DVR_Open();
    int i = 20;
    char temp[50];
    while (i--)
    {
        //GetCPH(cp);
        GetCPHM(temp);
        cout << "获取车牌号:" << temp << endl; // prints !!!Hello World!!!
        sleep(1);
    }
    DVR_Close();
    return 0;
}
