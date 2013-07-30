#include "LocalIncludeFile.h"
#include <dlfcn.h>


#ifndef PCMACHINE

/***** VideoSaveToJPG_RHY ************
filename ：文件名
quality  ：JPG质量 0-100（越大越好）
***************************************/
extern int VideoSaveToJPG_RHY(char* jpgfilename,int quality);

/***** Video_Init_RHY ******************
视频初始化 设置视频窗口的位置和大小
注意： 不是任何高度和宽度都可以的
*****************************************/
extern int Video_Init_RHY(int left,int top,int width,int height);

/***** Video_Close_RHY ******************
关闭视频窗口
*****************************************/
extern int Video_Close_RHY(void);
/***** SetVideo_Win_RHY ******************
设置视频窗口的位置和大小
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
unsigned long  (*libcapsetpos)(int w,int h,int x,int y); 

void Create_camera (void )
{
	if (EnabledVideo() == 1 ||  EnabledVideo() == 2)
	{
		echoic("Video_Init_RHY");
		Video_Init_RHY(OFFSIZE_X,OFFSIZE_Y,352,288);
	} else  if (EnabledVideo() == 3)
	{
		echoic("Create_camera_libcapvide");
		Create_camera_libcapvide();
	}
	else 
	{
		echo_ct("Video Mode Error Or not use! 1 or 2 will use Video_Init_RHY ,3 will use lib for video   %d",EnabledVideo() );
	}
}

int www = 352;
int hhh = 288;
int xxx = 4;
int yyy = 308;
void Create_camera_libcapvide(void )
{
	int ret=0;
	char * error;
	//使用动态库方式加载视频  modify by DZ @20101110
	if ( ( dllhandle_cap = dlopen( "liblane.cap.v4l.so", RTLD_LAZY ) ) != 0 ) 
	{ 
		libcapsetpos= dlsym( dllhandle_cap, "capsetpos" ); 
		if ((error = dlerror()) != NULL)  {
			/*echoic("dlerror=%s\n", error);*/
			ret = -1;
		}
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
		libcapvideosource=dlsym( dllhandle_cap, "capvideosource" ); 
		if ((error = dlerror()) != NULL)  {
			//echoic("dlerror=%s\n", error);
			ret = -1;
		}
		 libcapsetpos(www,hhh,xxx ,yyy);
		ret = (*libcapvideoopen)(); 
		echoic("%d",ret);
	}
	else
	{
		 echoic("dlopen error:%s\n",dlerror());
	}
}
void SaveJpg ( char * file_name , int width , int height , int bpp )
{
	if (EnabledVideo() == 1)
	{
		VideoSaveToJPG_RHY(file_name,quality);
	}
	else if (EnabledVideo() == 2)
	{
		char ReadLen = 0;
		char buf[5];
		static char Cap_First_Flag=1;
		static int pipe_fd=-1,pipe_read_fd=-1;
		if (Cap_First_Flag)
		{
			pipe_fd = open("/dev/shm/VideoFifo", O_WRONLY);
			pipe_read_fd = open("/dev/shm/VideoRead", O_RDONLY);
			Cap_First_Flag = 0;
		}
		if (pipe_fd== -1)
		{
			perror("pipe_fd");

		}
		else 
		{
			write(pipe_fd,file_name,strlen(file_name)+1);
			do
			{
				ReadLen+=read(pipe_read_fd,buf,3);
			}while (ReadLen<3);
		}
	}
	else if (EnabledVideo() == 3)
	{
		SaveJpg_libcapcaptureone(file_name, 352, 288, 16);
	}
	else 
	{
		echoic("not use any method to save jpg ");
	}
}

void SaveJpg_libcapcaptureone( char * file_name , int width , int height , int bpp )
{
	echoic("ImageName:<%s>",file_name);
     (*libcapcaptureone)(file_name);
}




