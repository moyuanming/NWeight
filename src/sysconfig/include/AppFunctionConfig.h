#ifndef _AppFunctionConfig_H_
#define _AppFunctionConfig_H_


#define FUNENABLEDWEIGHT	EnabledWeight()
#define FUNENABLEDPRINTER	EnabledPrinter()
#define FUNENABLEDTFT		EnabledTFI()
#define FUNENABLEDVDM		EnabledVDM()
#define FUNENABLEDSCS		EnabledCICM()
#define FUNENABLEDLPR		EnabledLPR()
#define FUNENABLEDOPC		EnabledOPC()
int EnabledCPSB(void);//�Ƿ����ó���ʶ��
int EnabledWeight(void);	//�Ƿ����ü���
int EnabledPrinter(void);	//�Ƿ����ô�ӡ��
int EnabledTFI(void);		//�Ƿ����÷Ѷ���ʾ��
int EnabledVDM(void);		//�Ƿ������ַ�����
int EnabledCICM(void);		//�Ƿ����ö�����
int EnabledLPR(void);		//����ʶ��
int EnabledOPC(void);		//��դ������
BOOL GetEnableIC(void);//�Ƿ�����IC������
int EnabledIOBoard(void); //�Ƿ�����IO��Ĺ���
void LoadAppFunction(void);//
BOOL EnabledCallTCS(void);//�Ƿ����ú���TCS����
BOOL EnabledVideo(void);// �Ƿ���������Ƶ
char *GetTFIDLL(void);
int GetDisPlay_Resolution(void);
char *GetPrintDLL(void);
char * GetICReader(void);
char * GetVDMDLL(void);
char * GetIOBoardDLL(void);
char * GetVPRDLL(void);
#endif	

