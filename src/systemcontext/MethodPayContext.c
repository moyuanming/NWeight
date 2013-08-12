#include "LocalIncludeFile.h"
//	E 未付款(违章时)
//	D欠款
//	1
//	2 SVC
//	3公务
//	4月票
//	5信用卡
//	6军警
//	7绿色通道
//	8标准集装箱
//	9标准罐车
//	T 车队

char * GetMethodPayText(char Index)
{
	char *ret = "";
	switch (Index)
	{
		case  CARKIND_SHOUFEI		:
			ret = "现金";
			break;
		case  CARKIND_WEIZHANG	:
			ret = "未付款";
			break;
		case  CARKIND_GONGWU	:
			ret = "公务卡";
			break;
		case CARKIND_LSTD:
		case CARKIND_JINCHE:
		case CARKIND_NONGYONG:
		case CARKIND_JUNCHE:
			ret = "减免";
			break;
		case  CARKIND_YPC		:
			ret = "月票卡";
			break;
		case  MP_CREDIT		:
			ret = "信用卡";
			break;
		case  CARKIND_YHC		:
			ret = "优惠卡";
			break;
		}
	return ret;

}

