//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#ifndef _ExitTR_H_
#define _ExitTR_H_
struct MSG_EXITTR
{
      char tranNo[4];
      char subtranNo;
      char FareTblVer[2];
      char CanopyStatus;
      char entrynetwork[2];
      char EntryPlaza[2];
      char EntryDateTime[14];
      char EntryLane[3];
      char EntryCollector[6];
      char EntrySignal[32];
      char ICCard_Type;
      char EntryClass;
      char ExitClass;
      char EntryType;
      char EntrySubType;
      char ExitType[3];
      char ExitSubType;
      char EntryDirection;
      char ExitDirection;
      char Receipt;
      char ReceiptNo[8];
      char Method_Pay;
      char Actual_pay[10];
      char TollFare[10];
      char ServiceCard[32];
      char NoOfficeCard;
      char SVCOldBalance[6];
      char SVCBalance[6];
      char DiscountRate[10];
      char Violation;
      char PassageLoopError;
      char PresenceLoopError;
      char DisputeType;
      char ICCardStatus;
      char TransSpecial;
      char ICBox[4];
      char ICCardNum[32];
      char Override;
      char ArrearTicketNo[8];
      char ExitSignal[32];
      char MARK;
	  char IsPostil[10];
	  char WeightCarClass;
	  char DetectTime[14];
	  char FWeightTotal[53];
	  char FAxleCount[10];
	  char FFareBase[10];
	  char WeightTollFare[53];
	  char WeightLimit[10];
	  char WeightLimitTollFare[53];
	  char OverloadWeight[10];
	  char OverLoadWeightRate[53];
	  char OverloadFare[53];
	  char Speed[10];
	  char Acceleration[10];
	  char FlagOverWeight[10];
	  char FlagDisCount[10];
	  char DetectWeightTotal[53];
	  char RateFareWeight[10];
	  char DetectAxleCount[10];
	  char DetectAxleGorup1[53];
	  char WheelTypeOfGorup1;
	  char DetectAxleGorup2[53];
	  char WheelTypeOfGorup2;
	  char DetectAxleGorup3[53];
	  char WheelTypeOfGorup3;
	  char DetectAxleGorup4[53];
	  char WheelTypeOfGorup4;
	  char DetectAxleCount5[53];
	  char WheelTypeOfGorup5;
	  char DetectAxleGorup6[53];
	  char WheelTypeOfGorup6;
	  char DetectAxleGorup7[53];
	  char WheelTypeOfGorup7;
	  char DetectAxleGorup8[53];
	  char WheelTypeOfGorup8;
	  char DetectAxleGorup9[53];
	  char WheelTypeOfGorup9;
	  char DetectAxleGorup10[53];
	  char WheelTypeOfGorup10;
	  char DetectAxleGorup11[53];
	  char WheelTypeOfGorup11;
	  char DetectAxleGorup12[53];
	  char WheelTypeOfGorup12;
	  char DetectAxleGorup13[53];
	  char WheelTypeOfGorup13;
	  char DetectAxleCount14[53];
	  char WheelTypeOfGorup14;
	  char DetectAxleCount15[53];
	  char WheelTypeOfGorup15;
	  char DetectAxleGorupOther[10];
};//endstructExitTR

#define  LENGHT_MSG_EXITTR 1580
void InitMsgExitTR(void);
struct MSG_EXITTR *GetMsgExitTR(void);
void SetExitTRMsgtranNo(char * InputTranNo);
void SetExitTRMsgsubtranNo(char InputsubtranNo);
void SetExitTRMsgFareTblVer(char* InputFareTblVer);
void SetExitTRMsgCanopyStatus(int InputCanopyStatus);
void SetExitTRMsgentrynetwork(char* Inputentrynetwork);
void SetExitTRMsgEntryPlaza(char* InputEntryPlaza);
void SetExitTRMsgEntryDateTime(char* InputEntryDateTime);
void SetExitTRMsgEntryLane(char* InputEntryLane);
void SetExitTRMsgEntryCollector(char* InputEntryCollector);
void SetExitTRMsgEntrySignal(char* InputEntrySignal);
void SetExitTRMsgICCard_Type(char InputICCard_Type);
void SetExitTRMsgEntryClass(char InputEntryClass);
void SetExitTRMsgExitClass(char InputExitClass);
void SetExitTRMsgEntryType(char InputEntryType);
void SetExitTRMsgEntrySubType(char InputEntrySubType);
void SetExitTRMsgExitType(char *InputExitType);
void SetExitTRMsgExitSubType(char InputExitSubType);
void SetExitTRMsgEntryDirection(char InputEntryDirection);
void SetExitTRMsgExitDirection(char InputExitDirection);
void SetExitTRMsgReceipt(char InputReceipt);
void SetExitTRMsgReceiptNo(char* InputReceiptNo);
void SetExitTRMsgMethod_Pay(char InputMethod_Pay);
void SetExitTRMsgActual_pay(int InputActual_pay);
void SetExitTRMsgTollFare(int InputTollFare);
void SetExitTRMsgServiceCard(char* InputServiceCard);
void SetExitTRMsgNoOfficeCard(char InputNoOfficeCard);
void SetExitTRMsgSVCOldBalance(char* InputSVCOldBalance);
void SetExitTRMsgSVCBalance(char* InputSVCBalance);
void SetExitTRMsgDiscountRate(int InputDiscountRate);
void SetExitTRMsgViolation(char InputViolation);
void SetExitTRMsgPassageLoopError(char InputPassageLoopError);
void SetExitTRMsgPresenceLoopError(char InputPresenceLoopError);
void SetExitTRMsgDisputeType(char InputDisputeType);
void SetExitTRMsgICCardStatus(char InputICCardStatus);
void SetExitTRMsgTransSpecial(char InputTransSpecial);
void SetExitTRMsgICBox(char* InputICBox);
void SetExitTRMsgICCardNum(char* InputICCardNum);
void SetExitTRMsgOverride(char InputOverride);
void SetExitTRMsgArrearTicketNo(char* InputArrearTicketNo);
void SetExitTRMsgExitSignal(char* InputExitSignal);
void SetExitTRMsgMARK(char InputMARK);

void SetExitTRMsgIsPostil(int InputIsPostil);
void SetExitTRMsgWeightCarClass(char InputWeightCarClass);
void SetExitTRMsgDetectTime(char*  InputDetectTime);
void SetExitTRMsgFWeightTotal(float  InputFWeightTotal);
void SetExitTRMsgFAxleCount(int InputFAxleCount);
void SetExitTRMsgFFareBase(int InputFFareBase);
void SetExitTRMsgWeightTollFare(float  InputWeightTollFare);
void SetExitTRMsgWeightLimit(int InputWeightLimit);
void SetExitTRMsgWeightLimitTollFare(float  InputWeightLimitTollFare);
void SetExitTRMsgOverloadWeight(int InputOverloadWeight);
void SetExitTRMsgOverLoadWeightRate(float  InputOverLoadWeightRate);
void SetExitTRMsgOverloadFare(float  InputOverloadFare);
void SetExitTRMsgSpeed(int InputSpeed);
void SetExitTRMsgAcceleration(int InputAcceleration);
void SetExitTRMsgFlagOverWeight(int InputFlagOverWeight);
void SetExitTRMsgFlagDisCount(int InputFlagDisCount);
void SetExitTRMsgDetectWeightTotal(float  InputDetectWeightTotal);
void SetExitTRMsgRateFareWeight(int InputRateFareWeight);
void SetExitTRMsgDetectAxleCount(int InputDetectAxleCount);
void SetExitTRMsgDetectAxleGorup(float InputDetectAxleGorup1,int index);
void SetExitTRMsgDetectAxleGorupOther(int InputDetectAxleGorupOther);


#endif //define t_tablename

