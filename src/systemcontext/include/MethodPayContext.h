#ifndef __MethodPayContext_H__
#define __MethodPayContext_H__
//���ʽ
//	E δ����(Υ��ʱ)
//	DǷ��
//	1�ֽ�
//	2 SVC
//	3����
//	4��Ʊ
//	5���ÿ�
//	6����
//	7��ɫͨ��
//	8��׼��װ��
//	9��׼�޳�
//	T ����

#define MP_NotPay		'E'
#define MP_QIAN_KUAN	'D'
#define MP_XIAN_JIN		'1'
#define MP_SVC			'2'
#define MP_OFFICE		'3'
#define MP_MONTH		'4'
#define MP_CREDIT		'5'
#define MP_POLICE		'6'
#define MP_LVSETD		'7' 
#define MP_JI_ZHUANG_XIANG '8'
#define MP_GUAN_CHE		'9'
#define MP_TEAM			'T'
char * GetMethodPayText(char Index);

#endif

