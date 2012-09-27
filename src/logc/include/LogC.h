#ifndef __LogC_H__
#define __LogC_H__



#define LOG_DEBUG "Debug"
#define LOG_ERROR "Error"
#define LOG_INFOR "Infor"
#define LOG_WARNI "Warni"


struct LogConfing
{
	int EnableDebug;
	int EnableError;
	int EnableInfor;
	int EnableWarni;
	int IsPrint;
};


void postLogcSync(void);
void LogC(char *ModName,char *LogType ,char *File,int LineNumber ,char *Format,...);
char *StrToHexStr(char * Strbuffer,int strlen);

#define MYMDPRINTF(fmt, args...)	printf("CARD DEGUG  [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define LogCWorkFlow(_LogType_ ,_Format_,args...)			//LogC("WorkFlow",		_LogType_ ,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCSystemContext(_LogType_ ,_Format_,args...)		//LogC("SystemContext",	_LogType_ ,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCSysconfig(_LogType_ ,_Format_,args...)			//LogC("Sysconfig",		_LogType_ ,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCParameter(_LogType_ ,_Format_,args...)			//LogC("EmrcLaneApp",		_LogType_ ,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCDev(_LogType_ ,_Format_,args...)				LogC("Dev",				_LogType_ ,"", 0 ,_Format_, ## args)
#define LogCCommunication(_LogType_ ,_Format_,args...)		//LogC("Communication",	_LogType_ ,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCGenera(_LOG_,_LogType_ ,_Format_,args...)		// LogC(_LOG_,	_LogType_ ,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCAppLog(_Format_,args...)					//LogC("EmrcLaneApp",LOG_INFOR,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCAppLogDebug(_Format_,args...)					LogC("EmrcLaneApp",LOG_DEBUG,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCAppLogWdsMonitorThread(_Format_,args...)	//					LogC("EmrcLaneApp",LOG_INFOR,__FILE__, __LINE__ ,_Format_, ## args)
#define LogCDbLog(_Format_,args...)					LogC("Emrc_Db_Log",LOG_DEBUG,__FILE__, __LINE__ ,_Format_, ## args)
//void OperatorLogC();
#endif

