#ifndef __MethodPayContext_H__
#define __MethodPayContext_H__
//交款方式
//	E 未付款(违章时)
//	D欠款
//	1现金
//	2 SVC
//	3公务
//	4月票
//	5信用卡
//	6军警
//	7绿色通道
//	8标准集装箱
//	9标准罐车
//	T 车队

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

