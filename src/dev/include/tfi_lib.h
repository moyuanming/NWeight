#ifndef		_TFI_LIB_H_
#define		_TFI_LIB_H_


/***** LedTfi_init ************
金额显示器初始化
***************************************/
int LedTfi_init(char* DevName);

/***** LedTfi_GongHao ************
显示工号 最大长度8
***************************************/
int LedTfi_GongHao(char* GongHao);

/***** LedTfi_XingJi ************
显示星级 XingJi 范围 0x00~0x10，例如：9= 4星半
***************************************/
int LedTfi_XingJi(unsigned char XingJi);

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
int LedTfi_BMP(void);

/***** LedTfi_Clean ************
清屏
***************************************/
int LedTfi_Clean(void);

/***** LedTfi_DownLoadBMP ************
下载图片  图片的大小 = 128的倍数
***************************************/
int LedTfi_DownLoadBMP(unsigned char* ldBMP,unsigned int len);


/***** AudioVolume ************
音量大小
***************************************/
int SetTFIVolume(unsigned char Volume);


/********** AudioBrig ************
亮度
***************************************/
int SetTFIBrig(unsigned char Brig);


/***** AudioVolume ************
播放音频 
num = 播放多少个文件
file = 文件名,每个文件长度4 + 0x00
注:如果播放2个文件,file = 文件名1 + 0x00 + 文件名2 +0x00
***************************************/
int PlayAudio(unsigned char *file, unsigned char num);



/***** LedTfi_Line16 ************
16号字行显示
***************************************/
int LedTfi_Line16(unsigned char line,unsigned char *buf);

/***** LedTfi_Line32 ************
32号字行显示
***************************************/
int LedTfi_Line32(unsigned char line,unsigned char *buf);


/***** TFI_Output ************
继电器输出
***************************************/
int TFI_Output(unsigned char channel,unsigned char OnOff);


#endif

