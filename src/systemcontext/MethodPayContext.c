#include "LocalIncludeFile.h"
//	E δ����(Υ��ʱ)
//	DǷ��
//	1
//	2 SVC
//	3����
//	4��Ʊ
//	5���ÿ�
//	6����
//	7��ɫͨ��
//	8��׼��װ��
//	9��׼�޳�
//	T ����

char * GetMethodPayText(char Index)
{
	char *ret = "";
	switch (Index)
	{
		case  CARKIND_SHOUFEI		:
			ret = "�����";
			break;
		case  CARKIND_WEIZHANG	:
			ret = "δ����";
			break;
		case  CARKIND_GONGWU	:
			ret = "����";
			break;
		case CARKIND_LSTD:
		case CARKIND_JINCHE:
		case CARKIND_NONGYONG:
		case CARKIND_JUNCHE:
			ret = "����";
			break;
		case  CARKIND_YPC		:
			ret = "��Ʊ��";
			break;
		case  MP_CREDIT		:
			ret = "���ÿ�";
			break;
		case  CARKIND_YHC		:
			ret = "�Żݿ�";
			break;
		}
	return ret;

}

