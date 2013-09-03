#include "LocalIncludeFile.h"

char KeyBoard_KeyMap[MAXSYSINI];
struct KeyMap
{
	int DefaultKey;
	int DefineKey;
	char KeyName[20];
};
struct KeyMap KeyMapArray[100];

int  KeyTran(int keyvalue)
{
	int key=0;
	int i =0;
	key=keyvalue;
	for ( i=0;i<100;i++)
	{
		//echoic("DefineKey<%d><%d>",KeyMapArray[i].DefineKey,keyvalue);
		if (KeyMapArray[i].DefineKey==keyvalue)
		{
			key=KeyMapArray[i].DefaultKey;
			break;
		}
	}
	return key;
}
int KeyChangCode(int nKey)
{	
	if (nKey == 11)
	{	
		nKey = 48;
	}
	else
	{	
		nKey = nKey + 47;
	}
	return nKey;
}

int  KeyNameTran(char *KeyName)
{
	int key=0;
	int i =0;
	for ( i=0;i<100;i++)
	{
		if (0==strcmp(KeyMapArray[i].KeyName,KeyName))
		{
			key=KeyMapArray[i].DefaultKey;
			break;
		}
	}
	return key;
}
void InitKeyBoard_KeyMap(void)
{
	int i = 0;
	for(i=0;i<100;i++)
	{
		memset(KeyMapArray[i].KeyName,0x00,20);
	}
	LoadKeyBoardFile();

	KeyMapArray[0].DefaultKey=VK_0;
	strcpy(KeyMapArray[0].KeyName,"VK_0");

	KeyMapArray[1].DefaultKey=VK_1;
	strcpy(KeyMapArray[1].KeyName,"VK_1");

	KeyMapArray[2].DefaultKey=VK_2;
	strcpy(KeyMapArray[2].KeyName,"VK_2");

	KeyMapArray[3].DefaultKey =VK_3;
	strcpy(KeyMapArray[3].KeyName,"VK_3");

	KeyMapArray[4].DefaultKey =VK_4;
	strcpy(KeyMapArray[4].KeyName,"VK_4");

	KeyMapArray[5].DefaultKey=VK_5;
	strcpy(KeyMapArray[5].KeyName,"VK_5");


	KeyMapArray[6].DefaultKey =VK_6;
	strcpy(KeyMapArray[6].KeyName,"VK_6");

	KeyMapArray[7].DefaultKey=VK_7;
	strcpy(KeyMapArray[7].KeyName,"VK_7");

	KeyMapArray[8].DefaultKey=VK_8;
	strcpy(KeyMapArray[8].KeyName,"VK_8");

	KeyMapArray[9].DefaultKey=VK_9;
	strcpy(KeyMapArray[9].KeyName,"VK_9");

	KeyMapArray[10].DefaultKey=VK_CANCEL;
	strcpy(KeyMapArray[10].KeyName,"VK_CANCEL");

	KeyMapArray[11].DefaultKey=VK_YOUHUICARD;
	strcpy(KeyMapArray[11].KeyName,"VK_YOUHUICARD");

	KeyMapArray[12].DefaultKey=VK_MOUNTHCARD;
	strcpy(KeyMapArray[12].KeyName,"VK_MOUNTHCARD");

	KeyMapArray[13].DefaultKey=VK_QIANKUAN;
	strcpy(KeyMapArray[13].KeyName,"VK_QIANKUAN");

	KeyMapArray[14].DefaultKey=VK_LVSETONGDAO;
	strcpy(KeyMapArray[14].KeyName,"VK_LVSETONGDAO");


	KeyMapArray[15].DefaultKey=VK_RETURN;
	strcpy(KeyMapArray[15].KeyName,"VK_RETURN");


	KeyMapArray[16].DefaultKey=VK_WEIZHANG;
	strcpy(KeyMapArray[16].KeyName,"VK_WEIZHANG");


	KeyMapArray[17].DefaultKey=VK_JUNCHE;
	strcpy(KeyMapArray[17].KeyName,"VK_JUNCHE");


	KeyMapArray[18].DefaultKey=VK_GONGWU;
	strcpy(KeyMapArray[18].KeyName,"VK_GONGWU");


	KeyMapArray[19].DefaultKey=VK_BEIYONG;
	strcpy(KeyMapArray[19].KeyName,"VK_BEIYONG");

	KeyMapArray[20].DefaultKey=VK_LONGYONG;
	strcpy(KeyMapArray[20].KeyName,"VK_LONGYONG");

	KeyMapArray[21].DefaultKey=VK_SHANGBAN;
	strcpy(KeyMapArray[21].KeyName,"VK_SHANGBAN");

	KeyMapArray[22].DefaultKey=VK_XIABAN;
	strcpy(KeyMapArray[22].KeyName,"VK_XIABAN");

	KeyMapArray[23].DefaultKey=VK_CLOSE_YPD;
	strcpy(KeyMapArray[23].KeyName,"VK_CLOSE_YPD");

	KeyMapArray[24].DefaultKey=VK_OPEN_YPD;
	strcpy(KeyMapArray[24].KeyName,"VK_OPEN_YPD");

	KeyMapArray[25].DefaultKey=VK_OPEN;
	strcpy(KeyMapArray[25].KeyName,"VK_OPEN");

	KeyMapArray[26].DefaultKey=VK_CLOSE;
	strcpy(KeyMapArray[26].KeyName,"VK_CLOSE");

	KeyMapArray[27].DefaultKey=VK_MONI;
	strcpy(KeyMapArray[27].KeyName,"VK_MONI");

	KeyMapArray[28].DefaultKey=VK_CHEDUI_G;
	strcpy(KeyMapArray[28].KeyName,"VK_CHEDUI_G");

	//KeyMapArray[29].DefaultKey=VK_CHEDUI_R;
	//strcpy(KeyMapArray[29].KeyName,"VK_CHEDUI_R");

	KeyMapArray[30].DefaultKey=VK_URGENT;
	strcpy(KeyMapArray[30].KeyName,"VK_URGENT");

	KeyMapArray[31].DefaultKey=VK_LEFT;
	strcpy(KeyMapArray[31].KeyName,"VK_LEFT");

	KeyMapArray[33].DefaultKey=VK_RIGHT;
	strcpy(KeyMapArray[33].KeyName,"VK_RIGHT");

	KeyMapArray[34].DefaultKey=VK_UP;
	strcpy(KeyMapArray[34].KeyName,"VK_UP");

	KeyMapArray[35].DefaultKey=VK_DOWN;
	strcpy(KeyMapArray[35].KeyName,"VK_DOWN");

	/*KeyMapArray[36].DefaultKey=VK_LANGAN;
	strcpy(KeyMapArray[36].KeyName,"VK_LANGAN");*/


	KeyMapArray[36].DefaultKey=VK_System;
	strcpy(KeyMapArray[36].KeyName,"VK_System");




	KeyMapArray[37].DefaultKey=VK_00;
	strcpy(KeyMapArray[37].KeyName,"VK_00");
	KeyMapArray[38].DefaultKey=VK_CardBox;
	strcpy(KeyMapArray[38].KeyName,"VK_CardBox");
	KeyMapArray[39].DefaultKey=VK_HappyDay;
	strcpy(KeyMapArray[39].KeyName,"VK_HappyDay");
	KeyMapArray[40].DefaultKey=VK_TranCard;
	strcpy(KeyMapArray[40].KeyName,"VK_TranCard");
	KeyMapArray[41].DefaultKey=VK_SVC;
	strcpy(KeyMapArray[41].KeyName,"VK_SVC");
	KeyMapArray[42].DefaultKey=VK_JZK;
	strcpy(KeyMapArray[42].KeyName,"VK_JZK");


	KeyMapArray[43].DefaultKey=VK_BEIYONG2;
	strcpy(KeyMapArray[43].KeyName,"VK_BEIYONG2");
	KeyMapArray[44].DefaultKey=VK_BEIYONG3;
	strcpy(KeyMapArray[44].KeyName,"VK_BEIYONG3");
	KeyMapArray[45].DefaultKey=VK_Weight;
	strcpy(KeyMapArray[45].KeyName,"VK_Weight");
	KeyMapArray[46].DefaultKey=VK_TRUCK;
	strcpy(KeyMapArray[46].KeyName,"VK_TRUCK");
	for(i=0;i<100;i++)
	{
		//echoic("Keyname<%s><%d>",KeyMapArray[i].KeyName,GetKeyMapValue(KeyMapArray[i].KeyName));
		KeyMapArray[i].DefineKey =GetKeyMapValue(KeyMapArray[i].KeyName);
	}
}
int LoadKeyBoardFile(void)
{
	int ret=-1;
	char tmp[100];
	memset(tmp,0x00,100);
	sprintf(tmp,"%s%s",FILEPATH_PARAMETER,GetKeyMap());
	ret=LoadFile(tmp,KeyBoard_KeyMap,MAXSYSINI);
	//echoic("%s",tmp);
	return ret;

}
/****************************************************************************************
 * 在装载的Ini字符串中读取指定内容的值
 *****************************************************************************************/
char _KeyMap[100];
int  GetKeyMapValue(char *ItemName)
{
	char *ini_addr_ptr;
	int len;
	int keyreturn =0;
	//echoic("%s",ItemName);
	memset(_KeyMap,0x00,sizeof(_KeyMap));
	ini_addr_ptr = strstr(KeyBoard_KeyMap,ItemName);
	 if (ini_addr_ptr!=NULL)
	 {
		ini_addr_ptr = strchr(ini_addr_ptr,'<')+1;
		len=strchr(ini_addr_ptr,'>')-ini_addr_ptr;
		strncpy(_KeyMap,ini_addr_ptr,len);
		_KeyMap[len] = 0x00;
		keyreturn=atoi(_KeyMap);
	 }
	 else
	 {
		 keyreturn=0;
	 }
	return keyreturn;
}


