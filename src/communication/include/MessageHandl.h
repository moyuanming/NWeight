#ifndef _MessageHandl_H_
#define _MessageHandl_H_
#include "MessageDef.h"
char *GetCurrentMessage(void);
int DeleteSendedMessageFromMessageQueue(char *strMsgIndex);
char *GetRegMessage(void);
void CheckMessageBCC(void);
#endif


