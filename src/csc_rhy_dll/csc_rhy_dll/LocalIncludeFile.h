#ifndef __LocalIncludeFile_H__
#define __LocalIncludeFile_H__


#define  DEBUGAUTO

#include "linux_include.h"
   

/*----includeĿ¼�е�.h�ļ�  ----*/
 
 

//fuxl add 2010-07-14 for cpu card
#include "IcKey.h"
#include "3des.h"
#include "mac.h"
#include "i_dev_ic.h"
#include "dal_imf.h"
#include "MIF_Interface.h"
  
/*-------------------------*/



//����ʱ��� ������Ͼ͹رգ�
//#define MYHDEBUG
	#ifdef MYHDEBUG
		#define echo(_Format_,args...)			LogC("EmrcLaneApp", LOG_DEBUG ,__FILE__, __LINE__ ,_Format_, ## args)	//print_emrc("MYH:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args) 
 
	#else
		#define echo(fmt, args...)  
	#endif
 
//#define dddd
	#ifdef dddd
		#define echo1(fmt, args...)	print_emrc("ECHO1:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args) 
	#else
		#define echo1(fmt, args...) 
	#endif
#endif
