#ifndef __I_DEV_S303_Printer_H__
#define __I_DEV_S303_Printer_H__

void I_DEV_S303_Printer_PrintBill(struct BILLPARAM *var_billparam);
void I_DEV_S303_Printer_Close(void);
BOOL I_DEV_S303_Printer_TestStatus(void);
void I_DEV_S303_Printer_PrintTestBill(void);
#endif

