#ifndef __SwitchContext_H__
#define __SwitchContext_H__


void Setg_bYuPeng(BOOL  value);
void Setg_bJiaoTong(BOOL   value);
void Setg_bYuPengOpened(BOOL  value);
int Getg_bYuPengOpened(void);
int Getg_bJiaoTong(void);
void Setg_bLanGan(BOOL    value);
int Getg_bLanGan(void);
void Setg_bZhuaPaiXianQuan(BOOL   value);
int Getg_bZhuaPaiXianQuan(void);
void Setg_bTongGuoXianQuan(BOOL   value);
int Getg_bTongGuoXianQuan(void);
void Setg_bPrint(BOOL   value);
int Getg_bPrint(void);
void Setg_Ring(BOOL   value);
int Getg_Ring(void);
void Setg_printfState(char  value);
int Getg_printfState(void);
void Setg_bCheDaoStatus(BOOL  value);
int Getg_bCheDaoStatus(void);
void Setg_bReLogin(BOOL   value);
int Getg_bReLogin(void);
void Setg_bWeiZhang(BOOL  value);
int Getg_bWeiZhang(void);
BOOL  Getg_bYuPeng(void);
#endif
