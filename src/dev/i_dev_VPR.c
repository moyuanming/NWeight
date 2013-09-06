#include "LocalIncludeFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dlfcn.h>
#include  "i_dev_VPR_HK.h"
#include "i_dev_VPR_HW.h"
BOOL  CPSB_isInit = F ;
int CPSB_UnLoad(void)
{
	if(!CPSB_isInit)
	{
		CPSB_isInit = T;
		if (0 == strcmp("HK", GetVPRDLL()))
		{
			CPSB_isInit=VPR_HK_UnLoad();
		}
		else if (0 == strcmp("HW", GetVPRDLL()))
		{

		}

	}
	return CPSB_isInit;
}
int CPSB_Load(void)
{
	int r=0;
	if (0 == strcmp("HK", GetVPRDLL()))
	{
	  r =	VPR_HK_Load();
	}

	return r;
}
int DVR_Open(void)
{
	int r=0;
	if (0 == strcmp("HK", GetVPRDLL()))
	{
		r= VPR_HK_Open();
	}
	return  r ;
}
void DVR_Close(void)
{
	 	if (0 == strcmp("HK", GetVPRDLL()))
	{
		VPR_HK_Close();
		}
}
void ClearCPHM(void)
{
	 	 	if (0 == strcmp("HK", GetVPRDLL()))
	{
		 VPR_HK_ClearCPHM();
		}
}
char * GetCPHM(char *cp)
{
	if (0 == strcmp("HK", GetVPRDLL()))
	{
		return VPR_HK_GetCPHM(cp);
	}
	return "Î´Ê¶±ð";

}