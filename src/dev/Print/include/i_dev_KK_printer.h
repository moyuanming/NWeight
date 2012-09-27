#ifndef __I_DEV_KK_Printer_H__
#define __I_DEV_KK_Printer_H__
#include "LocalIncludeFile.h"


void I_DEV_KK_Printer_PrintBill(struct BILLPARAM *var_billparam);
void I_DEV_KK_Printer_Close(void);
BOOL I_DEV_KK_Printer_TestStatus(void);
void I_DEV_KK_Printer_PrintTestBill(void);
#endif

