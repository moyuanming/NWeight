#include "LocalIncludeFile.h"
#include "i_dev_VPR_HW.h"
int VPR_HW_isInit = 0;
int VPR_HW_UnLoad(void)
{
	 
	return VPR_HW_isInit;
}
int VPR_HW_Load(void)
{
	 
	return 0;
}
 int VPR_HW_Open(void)
 {
	 
	 return 1;
 }
 void VPR_HW_Close(void)
 {
	 if(VPR_HW_isInit )
	 {
		 
	 }
 }
 void VPR_HW_ClearCPHM(void)
 {
	 if(VPR_HW_isInit )
	 {
		 
	 }
 }
 char * VPR_HW_GetCPHM(char *cp)
 {
	 if(VPR_HW_isInit )
	 {
		 
	 }
	 return "Î´Ê¶±ð";
 }