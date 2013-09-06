#include "LocalIncludeFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dlfcn.h>
#include "i_dev_VPR_HK.h"
int (*pDVR_Open)(void);
void (*pDVR_Close)(void);
void (*pClearCPHM)(void);
char * (*pGetCPHM)(char *);
void   *CPSB_handle = 0x00;
int VPR_HK_isInit = 0;
int VPR_HK_UnLoad(void)
{
	if(CPSB_handle)
	{
		VPR_HK_isInit = 0;
		DVR_Close();
		echoic("close libHCDVR.so");
		dlclose( CPSB_handle );
	}
	return VPR_HK_isInit;
}
int VPR_HK_Load(void)
{
	echoic("load libHCDVR.so");
    CPSB_handle = dlopen( "libHCDVR.so", RTLD_LAZY );
	if(CPSB_handle)
	{
		pDVR_Open    = dlsym( CPSB_handle, "DVR_Open" );
		if(pDVR_Open)
		{
			echoic("load func DVR_Open");
		}
		else
		{
			echoic("load func DVR_Open error");
		}
		
		pDVR_Close    = dlsym( CPSB_handle, "DVR_Close" );
		if(pDVR_Close)
		{
			echoic("load func DVR_Close");
		}
		else
		{
			echoic("load func DVR_Close error");
		}

		pGetCPHM    = dlsym( CPSB_handle, "GetCPHM" );
		if(pGetCPHM)
		{
			echoic("load func GetCPHM");
		}
		else
		{
			echoic("load func GetCPHM error");
		}
		pClearCPHM    = dlsym( CPSB_handle, "ClearCPHM" );
		if(pClearCPHM)
		{
			echoic("load func ClearCPHM");
		}
		else
		{
			echoic("load func ClearCPHM error");
		}
		VPR_HK_isInit = 1;
	    DVR_Open();
	}
	else
	{
		CPSB_UnLoad();
	}
	return 0;
}
 int VPR_HK_Open(void)
 {
	 if(VPR_HK_isInit&&pDVR_Open)
	 {
		 pDVR_Open();
		 return 0;
	 }
	 return 1;
 }
 void VPR_HK_Close(void)
 {
	 if(VPR_HK_isInit&&pDVR_Close)
	 {
		 pDVR_Close();
	 }
 }
 void VPR_HK_ClearCPHM(void)
 {
	 if(VPR_HK_isInit&&pClearCPHM)
	 {
		 pClearCPHM();
	 }
 }
 char * VPR_HK_GetCPHM(char *cp)
 {
	 if(VPR_HK_isInit&&pGetCPHM)
	 {
		 return pGetCPHM(cp);
	 }
	 return "Î´Ê¶±ð";
 }