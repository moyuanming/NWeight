#include "LocalIncludeFile.h"
#include <dlfcn.h>


#ifndef PCMACHINE

/***** VideoSaveToJPG_RHY ************
filename ���ļ���
quality  ��JPG���� 0-100��Խ��Խ�ã�
***************************************/
extern int VideoSaveToJPG_RHY(char* jpgfilename,int quality);

/***** Video_Init_RHY ******************
��Ƶ��ʼ�� ������Ƶ���ڵ�λ�úʹ�С
ע�⣺ �����κθ߶ȺͿ�ȶ����Ե�
*****************************************/
extern int Video_Init_RHY(int left,int top,int width,int height);

/***** Video_Close_RHY ******************
�ر���Ƶ����
*****************************************/
extern int Video_Close_RHY(void);
/***** SetVideo_Win_RHY ******************
������Ƶ���ڵ�λ�úʹ�С
*****************************************/
int SetVideo_Win_RHY(int left,int top,int width,int height);


static int quality = 70 ;

#define OFFSIZE_Y ((UI_DISPLAY_RESOLUTION) == (DISPPLAY_640_480) ? (55):(308))
#define OFFSIZE_X ((UI_DISPLAY_RESOLUTION) == (DISPPLAY_640_480) ? (282):(4))

#endif

void *dllhandle_cap; 
unsigned long  (*libcapvideoopen)(void); 
unsigned long  (*libcapcapmode)(int); 
unsigned long  (*libcapcaptureone)(char*); 
unsigned long  (*libcapcaptureonecommit)(char*,char*); 
unsigned long  (*libcapvideosource)(int); 
unsigned long  (*libcideoclose)(void); 
void Create_camera ( )
{
#ifdef PCMACHINE	
	int ret=0;
	char * error;

	echo_ci("ccd");
	//ʹ�ö�̬�ⷽʽ������Ƶ  modify by DZ @20101110
	if ( ( dllhandle_cap = dlopen( "liblane.cap.v4l.so", RTLD_LAZY ) ) != 0 ) 
	{ 
		echo_ci("ccd");
		/*echoic("dlopen ok.\n");*/
		libcapvideoopen= dlsym( dllhandle_cap, "capvideoopen" ); 
		if ((error = dlerror()) != NULL)  {
			/*echoic("dlerror=%s\n", error);*/
			ret = -1;
		}
		libcapcaptureone= dlsym( dllhandle_cap, "capcaptureone" ); 
		if ((error = dlerror()) != NULL)  {
			echoic("dlerror=%s\n", error);
			ret = -1;
		}
		libcapvideosource= dlsym( dllhandle_cap, "capvideosource" ); 
		if ((error = dlerror()) != NULL)  {
			//echoic("dlerror=%s\n", error);
			ret = -1;
		}
		echo_ci("ccd");
		ret = (*libcapvideoopen)(); 
	}
	else
	{
		echo_ci("ccd");
		//echoic("dlopen error:%s\n",dlerror());
	}
#else
echoic("Video_Init_RHY");
echo_ci("Video_Init_RHY");
	Video_Init_RHY(OFFSIZE_X,OFFSIZE_Y,352,288);
#endif
	return;
}
void SaveJpg ( char * file_name , int width , int height , int bpp )
{
#ifdef PCMACHINE
echo_ci("SaveJpg_PCMACHINE");
		//echoic("ImageName:<%s>",file_name);
	// (*libcapcaptureone)(file_name);
#else
echoic("SaveJpg");
echo_ci("SaveJpg_VideoSaveToJPG_RHY");
	VideoSaveToJPG_RHY(file_name,quality);
#endif
}




