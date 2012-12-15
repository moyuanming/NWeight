#ifndef _AppFunctionConfig_H_
#define _AppFunctionConfig_H_


#define FUNENABLEDWEIGHT	EnabledWeight()
#define FUNENABLEDPRINTER	EnabledPrinter()
#define FUNENABLEDTFT		EnabledTFI()
#define FUNENABLEDVDM		EnabledVDM()
#define FUNENABLEDSCS		EnabledCICM()
#define FUNENABLEDLPR		EnabledLPR()
#define FUNENABLEDOPC		EnabledOPC()
int EnabledCPSB(void);//是否启用车牌识别
int EnabledWeight(void);	//是否启用计重
int EnabledPrinter(void);	//是否启用打印机
int EnabledTFI(void);		//是否启用费额显示器
int EnabledVDM(void);		//是否启用字符叠加
int EnabledCICM(void);		//是否启用读卡器
int EnabledLPR(void);		//车牌识别
int EnabledOPC(void);		//光栅隔离器
BOOL GetEnableIC(void);//是否启用IC卡功能
int EnabledIOBoard(void); //是否启用IO板的功能
void LoadAppFunction(void);//
BOOL EnabledCallTCS(void);//是否启用呼叫TCS功能
BOOL EnabledVideo(void);// 是否启用新视频
char *GetTFIDLL(void);
int GetDisPlay_Resolution(void);
char *GetPrintDLL(void);

#endif	

