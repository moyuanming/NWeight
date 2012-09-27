#ifndef _ICKEY_
#define _ICKEY_

struct ICKEY
{
	char EXTERNAL_AUTHENTICATE_KEY[33];
	char WRITE_KEY[33];
};
char *Get_EXTERNAL_AUTHENTICATE_KEY(void);
char *Get_WRITE_KEY(void);
void LoadLanKey(void);
char *Get_KEYVER (void);
#endif 

