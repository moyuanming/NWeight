#ifndef		_TFI_LIB_H_
#define		_TFI_LIB_H_


/***** LedTfi_init ************
�����ʾ����ʼ��
***************************************/
int LedTfi_init(char* DevName);

/***** LedTfi_GongHao ************
��ʾ���� ��󳤶�8
***************************************/
int LedTfi_GongHao(char* GongHao);

/***** LedTfi_XingJi ************
��ʾ�Ǽ� XingJi ��Χ 0x00~0x10�����磺9= 4�ǰ�
***************************************/
int LedTfi_XingJi(unsigned char XingJi);

/***** LedTfi_CheXing ************
��ʾ�Ǽ� CheXing ��Χ 0x00~0x09��
***************************************/
int LedTfi_CheXing(unsigned char CheXing);

/***** LedTfi_JinE ************
��ʾ�շѽ�� ��󳤶�6
***************************************/
int LedTfi_JinE(char* JinE);

/***** LedTfi_BMP ************
��ʾ���ص�ͼƬ ������ʱʹ�ã�
***************************************/
int LedTfi_BMP(void);

/***** LedTfi_Clean ************
����
***************************************/
int LedTfi_Clean(void);

/***** LedTfi_DownLoadBMP ************
����ͼƬ  ͼƬ�Ĵ�С = 128�ı���
***************************************/
int LedTfi_DownLoadBMP(unsigned char* ldBMP,unsigned int len);


/***** AudioVolume ************
������С
***************************************/
int SetTFIVolume(unsigned char Volume);


/********** AudioBrig ************
����
***************************************/
int SetTFIBrig(unsigned char Brig);


/***** AudioVolume ************
������Ƶ 
num = ���Ŷ��ٸ��ļ�
file = �ļ���,ÿ���ļ�����4 + 0x00
ע:�������2���ļ�,file = �ļ���1 + 0x00 + �ļ���2 +0x00
***************************************/
int PlayAudio(unsigned char *file, unsigned char num);



/***** LedTfi_Line16 ************
16��������ʾ
***************************************/
int LedTfi_Line16(unsigned char line,unsigned char *buf);

/***** LedTfi_Line32 ************
32��������ʾ
***************************************/
int LedTfi_Line32(unsigned char line,unsigned char *buf);


/***** TFI_Output ************
�̵������
***************************************/
int TFI_Output(unsigned char channel,unsigned char OnOff);


#endif

