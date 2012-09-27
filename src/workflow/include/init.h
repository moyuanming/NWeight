#ifndef __INIT_H__
#define __INIT_H__

struct sys_ini_t sys_ini;
void init(void);
void InitLog(void);
void DevInit(void);
void I_DEV_LED_Init(void);
void I_DEV_Printer_Init(void);
void system_close(void);
void I_DEV_Printer_Close(void);
void read_sys_ini_file(void);
char* GetCSCCOM(void);
char * GetWeightCOMStr(void);
void writelog(int logfd,char *syslog);
void readItemInsysConfigFile(char *SystemFile,char *ItemName ,char *ItemValue);
void ReadLeanNumber(void);
struct sys_ini_t  *GetSysConfig(void);
  
#endif
