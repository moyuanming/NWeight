#ifndef __PRINTER_H__
#define __PRINTER_H__
void printBill(struct BILLPARAM *printNode);
void I_Dev_Printer_PrintBill(struct BILLPARAM *var_billparam);
BOOL postPrinter(BOOL newNillNumber);
void createBillNumber(void);
void TestprintBill(void);
void I_DEV_Printer_PrintTestBill(void);
void ReadBillNumber(void);
void writeBillNumber(void);
BOOL GetCanTestPrinter(void );
#endif




