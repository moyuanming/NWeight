#ifndef _ParameterFileList_H_
#define _ParameterFileList_H_

struct ParameterFileList
{
    char  COLLECT[50];
    char  FARELIST[50];
    char  YHKLIST[50];
    char  YPKLIST[50];
    char  YHRATE[50];
	char  CARKIND_CONF[50];
	char  SVRCARDLIST[50];
	char  JOUCODE[50];
	char  CONSTANT[50];
};
struct ParameterFileList *GetParameterFileList(void);
void LoadGetParameterFileList(void);
#endif

