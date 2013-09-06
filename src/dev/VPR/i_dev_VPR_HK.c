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
int CPSB_isInit = 0;
int CPSB_UnLoad(void)
{
	if(CPSB_handle)
	{
		CPSB_isInit = 0;
		DVR_Close();
		echoic("close libHCDVR.so");
		dlclose( CPSB_handle );
	}
	return CPSB_isInit;
}
int CPSB_Load(void)
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
		CPSB_isInit = 1;
	    DVR_Open();
	}
	else
	{
		CPSB_UnLoad();
	}
	return 0;
}
 int DVR_Open(void)
 {
	 if(CPSB_isInit&&pDVR_Open)
	 {
		 pDVR_Open();
		 return 0;
	 }
	 return 1;
 }
 void DVR_Close(void)
 {
	 if(CPSB_isInit&&pDVR_Close)
	 {
		 pDVR_Close();
	 }
 }
 void ClearCPHM(void)
 {
	 if(CPSB_isInit&&pClearCPHM)
	 {
		 pClearCPHM();
	 }
 }
 char * GetCPHM(char *cp)
 {
	 if(CPSB_isInit&&pGetCPHM)
	 {
		 return pGetCPHM(cp);
	 }
	 return "Î´Ê¶±ð";
 }