#ifndef __MsgRevsion_H__
#define __MsgRevsion_H__

#define LEN_MSG_REVISION  16
struct MSG_REVISION 
{
	char CollectVer[2];
	char FareListVer[2];
	char YHKListVer[2];
	char YHRateDescriptionVer[2];
	char YPKListVer[2];
	char JOUCODE[2];
	char SVRCARDLIST[2];
	char FREECARLIST[2];
	char ConstVer[2];
};
struct MSG_REVISION *GetMsgRevision(void);
void InitMsgRevision(void);

#endif

