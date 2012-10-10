#ifndef		_TFI_LIB_H_
#define		_TFI_LIB_H_




/***** LedTfi_init ************
金额显示器初始化
***************************************/
int LedTfi_init(char* DevName);// /dev/COM1

/***** LedTfi_GongHao ************
显示工号 最大长度8
***************************************/
int LedTfi_GongHao(char* GongHao); // kong ge 

/***** LedTfi_XingJi ************
显示星级 XingJi 范围 0x01~0xA，例如：9= 4星半
***************************************/
int LedTfi_XingJi(unsigned char XingJi); // 0

/***** LedTfi_CheXing ************
显示星级 CheXing 范围 0x00~0x09，
***************************************/
int LedTfi_CheXing(unsigned char CheXing); 

/***** LedTfi_JinE ************
显示收费金额 最大长度6
***************************************/
int LedTfi_JinE(char* JinE);


/***** LedTfi_BMP ************
显示下载的图片 （结束时使用）
***************************************/
int LedTfi_BMP(void); // 清屏 只清 车型金额 


/***** LedTfi_Clean ************
清屏
***************************************/
int LedTfi_Clean(void);

/***** LedTfi_DownLoadBMP ************
下载图片  图片的大小 = 1024 字节
***************************************/
int LedTfi_DownLoadBMP(unsigned char* BMP);

/***** AudioVolume ************
音量大小 0~31
***************************************/
int AudioVolume(unsigned char Volume);


/***** AudioVolume ************
播放音频 dir=目录序号 file=文件序号
dir = 0x00~0x15
file = 0x00~0xc8
***************************************/
int PlayAudio(unsigned char dir,unsigned char file);

#endif

