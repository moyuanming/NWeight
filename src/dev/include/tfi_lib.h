#ifndef		_TFI_LIB_H_
#define		_TFI_LIB_H_




/***** LedTfi_init ************
�����ʾ����ʼ��
***************************************/
int LedTfi_init(char* DevName);// /dev/COM1

/***** LedTfi_GongHao ************
��ʾ���� ��󳤶�8
***************************************/
int LedTfi_GongHao(char* GongHao); // kong ge 

/***** LedTfi_XingJi ************
��ʾ�Ǽ� XingJi ��Χ 0x01~0xA�����磺9= 4�ǰ�
***************************************/
int LedTfi_XingJi(unsigned char XingJi); // 0

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
int LedTfi_BMP(void); // ���� ֻ�� ���ͽ�� 


/***** LedTfi_Clean ************
����
***************************************/
int LedTfi_Clean(void);

/***** LedTfi_DownLoadBMP ************
����ͼƬ  ͼƬ�Ĵ�С = 1024 �ֽ�
***************************************/
int LedTfi_DownLoadBMP(unsigned char* BMP);

/***** AudioVolume ************
������С 0~31
***************************************/
int AudioVolume(unsigned char Volume);


/***** AudioVolume ************
������Ƶ dir=Ŀ¼��� file=�ļ����
dir = 0x00~0x15
file = 0x00~0xc8
***************************************/
int PlayAudio(unsigned char dir,unsigned char file);

#endif

