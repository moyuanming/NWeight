//By GER.Cmd.buildgcc   CreateDate:2008-4-28 16:08:40
#include "LocalIncludeFile.h"
struct MSG_EXITTR MsgExitTR;
void InitMsgExitTR(void)
{	
	memset((char *)&MsgExitTR,'0',sizeof(struct MSG_EXITTR));	
}
struct MSG_EXITTR *GetMsgExitTR(void)
{	
	return (struct MSG_EXITTR  *)&MsgExitTR;
}
void SetExitTRMsgtranNo(char * InputTranNo)
{	
    strncpy(MsgExitTR.tranNo,InputTranNo,sizeof(MsgExitTR.tranNo));	
}
void SetExitTRMsgsubtranNo(char InputsubtranNo)
{	
	MsgExitTR.subtranNo=InputsubtranNo;
}
void SetExitTRMsgFareTblVer(char* InputFareTblVer)
{	
    strncpy(MsgExitTR.FareTblVer,InputFareTblVer,sizeof(MsgExitTR.FareTblVer));	
}
/*************************************************************************************
* 顶棚灯状态
**************************************************************************************/
void SetExitTRMsgCanopyStatus(int InputCanopyStatus)
{	
    char temp[1];
    if(InputCanopyStatus==1)
	{	
		temp[0]='G';
	}
	else
	{	
		temp[0]='R';
	}
    MsgExitTR.CanopyStatus=temp[0];
}
/*************************************************************************************
* 入口路网号
**************************************************************************************/
void SetExitTRMsgentrynetwork(char* Inputentrynetwork)
{	
    strncpy(MsgExitTR.entrynetwork,Inputentrynetwork,sizeof(MsgExitTR.entrynetwork));	
}
/*************************************************************************************
* 入口站号
**************************************************************************************/
void SetExitTRMsgEntryPlaza(char* InputEntryPlaza)
{	
    strncpy(MsgExitTR.EntryPlaza,InputEntryPlaza,sizeof(MsgExitTR.EntryPlaza));	
}
void SetExitTRMsgEntryDateTime(char* InputEntryDateTime)
{	
    strncpy(MsgExitTR.EntryDateTime,InputEntryDateTime,sizeof(MsgExitTR.EntryDateTime));	
}
/*************************************************************************************
* 入口车道号
**************************************************************************************/
void SetExitTRMsgEntryLane(char* InputEntryLane)
{	
    strncpy(MsgExitTR.EntryLane,InputEntryLane,sizeof(MsgExitTR.EntryLane));	
}
void SetExitTRMsgEntryCollector(char* InputEntryCollector)
{	
    strncpy(MsgExitTR.EntryCollector,InputEntryCollector,sizeof(MsgExitTR.EntryCollector));	
}
void SetExitTRMsgEntrySignal(char* InputEntrySignal)
{	
    strncpy(MsgExitTR.EntrySignal,InputEntrySignal,sizeof(MsgExitTR.EntrySignal));	
}
void SetExitTRMsgICCard_Type(char InputICCard_Type)
{	
	MsgExitTR.ICCard_Type=InputICCard_Type;
}
void SetExitTRMsgEntryClass(char InputEntryClass)
{	
	MsgExitTR.EntryClass=InputEntryClass;
}
/*************************************************************************************
* 出口车种
**************************************************************************************/
void SetExitTRMsgExitClass(char InputExitClass)
{	
	MsgExitTR.ExitClass=InputExitClass;
}
void SetExitTRMsgEntryType(char InputEntryType)
{	
	MsgExitTR.EntryType=InputEntryType;
}
void SetExitTRMsgEntrySubType(char InputEntrySubType)
{	
	MsgExitTR.EntrySubType=InputEntrySubType;
}
/*************************************************************************************
* 出口车型
**************************************************************************************/
void SetExitTRMsgExitType(char *InputExitType)
{	
	//strncpy(MsgExitTR.ExitType,InputExitType,3);
	sprintf(MsgExitTR.ExitType,"%3s",InputExitType);
}
void SetExitTRMsgExitSubType(char InputExitSubType)
{	
MsgExitTR.ExitSubType=InputExitSubType;
}
/*************************************************************************************
* 入口方向 X：任意方向
**************************************************************************************/
void SetExitTRMsgEntryDirection(char InputEntryDirection)
{	
	MsgExitTR.EntryDirection=InputEntryDirection;
}
void SetExitTRMsgExitDirection(char InputExitDirection)
{	
	MsgExitTR.ExitDirection=InputExitDirection;
}
void SetExitTRMsgReceipt(char InputReceipt)
{	
	MsgExitTR.Receipt=InputReceipt;
}
void SetExitTRMsgReceiptNo(char* InputReceiptNo)
{	
    strncpy(MsgExitTR.ReceiptNo,InputReceiptNo,sizeof(MsgExitTR.ReceiptNo));	
}
/*************************************************************************************
* 缴款方式
**************************************************************************************/
void SetExitTRMsgMethod_Pay(char InputMethod_Pay)
{	
	MsgExitTR.Method_Pay=InputMethod_Pay;
}
/*************************************************************************************
* 实际缴纳的通行费金额
**************************************************************************************/
void SetExitTRMsgActual_pay(int InputActual_pay)
{	
    sprintf(MsgExitTR.Actual_pay,"%010d",InputActual_pay);	
}
/*************************************************************************************
* 应缴纳的通行费金额
**************************************************************************************/
void SetExitTRMsgTollFare(int InputTollFare)
{	
    sprintf(MsgExitTR.TollFare,"%010d",InputTollFare);	
}
/*************************************************************************************
* 卡号
**************************************************************************************/
void SetExitTRMsgServiceCard(char* InputServiceCard)
{   
	char p='@' ;
	char temp[sizeof(MsgExitTR.ServiceCard)+1];
	echoic("使用的卡号:::%s",InputServiceCard);
	if (InputServiceCard==NULL ||  strlen(InputServiceCard)<=0)
	{
		p='0';
	}
	echoic("填空字符:::%c",p );
	strncpy(MsgExitTR.ServiceCard,PadLeft(p,InputServiceCard,temp,sizeof(MsgExitTR.ServiceCard)),sizeof(MsgExitTR.ServiceCard));    
}
/*************************************************************************************
* 卡号
**************************************************************************************/
void SetExitTRMsgNoOfficeCard(char InputNoOfficeCard)
{	
	MsgExitTR.NoOfficeCard=InputNoOfficeCard;
}
void SetExitTRMsgSVCOldBalance(char* InputSVCOldBalance)
{	
    strncpy(MsgExitTR.SVCOldBalance,InputSVCOldBalance,sizeof(MsgExitTR.SVCOldBalance));	
}
void SetExitTRMsgSVCBalance(char* InputSVCBalance)
{	
    strncpy(MsgExitTR.SVCBalance,InputSVCBalance,sizeof(MsgExitTR.SVCBalance));	
}
/*************************************************************************************
* 优惠率
**************************************************************************************/
void SetExitTRMsgDiscountRate(int InputDiscountRate)
{	
    sprintf(MsgExitTR.DiscountRate,"%010d",InputDiscountRate);	
}
/*************************************************************************************
* 违章情况
**************************************************************************************/
void SetExitTRMsgViolation(char InputViolation)
{	
MsgExitTR.Violation=InputViolation;
}
void SetExitTRMsgPassageLoopError(char InputPassageLoopError)
{	
MsgExitTR.PassageLoopError=InputPassageLoopError;
}
void SetExitTRMsgPresenceLoopError(char InputPresenceLoopError)
{	
MsgExitTR.PresenceLoopError=InputPresenceLoopError;
}
void SetExitTRMsgDisputeType(char InputDisputeType)
{	
MsgExitTR.DisputeType=InputDisputeType;
}
void SetExitTRMsgICCardStatus(char InputICCardStatus)
{	
MsgExitTR.ICCardStatus=InputICCardStatus;
}
void SetExitTRMsgTransSpecial(char InputTransSpecial)
{	
MsgExitTR.TransSpecial=InputTransSpecial;
}
void SetExitTRMsgICBox(char* InputICBox)
{	
    strncpy(MsgExitTR.ICBox,InputICBox,sizeof(MsgExitTR.ICBox));	
}
void SetExitTRMsgICCardNum(char* InputICCardNum)
{	
    strncpy(MsgExitTR.ICCardNum,InputICCardNum,sizeof(MsgExitTR.ICCardNum));	
}
void SetExitTRMsgOverride(char InputOverride)
{	
MsgExitTR.Override=InputOverride;
}
void SetExitTRMsgArrearTicketNo(char* InputArrearTicketNo)
{	
    strncpy(MsgExitTR.ArrearTicketNo,InputArrearTicketNo,sizeof(MsgExitTR.ArrearTicketNo));	
}
void SetExitTRMsgExitSignal(char* InputExitSignal)
{	
    strncpy(MsgExitTR.ExitSignal,InputExitSignal,sizeof(MsgExitTR.ExitSignal));	
}
void SetExitTRMsgMARK(char InputMARK)
{	
	MsgExitTR.MARK=InputMARK;
}

void SetExitTRMsgIsPostil(int InputIsPostil)
{
	sprintf(MsgExitTR.IsPostil,"%010d",InputIsPostil);
}
void SetExitTRMsgWeightCarClass(char InputWeightCarClass)
{
	MsgExitTR.WeightCarClass=InputWeightCarClass;
	GetMsgImage()->WeightCarClass=InputWeightCarClass;
}
void SetExitTRMsgDetectTime(char* InputDetectTime)
{
	strncpy(MsgExitTR.DetectTime,InputDetectTime,sizeof(MsgExitTR.DetectTime));
}
void SetExitTRMsgFWeightTotal(float InputFWeightTotal)
{
	sprintf(MsgExitTR.FWeightTotal,"%053.2f",Rounding(InputFWeightTotal));
	sprintf(GetMsgImage()->FWeightTotal,"%053.2f",Rounding(InputFWeightTotal));
}
void SetExitTRMsgFAxleCount(int InputFAxleCount)
{
	sprintf(MsgExitTR.FAxleCount,"%010d",InputFAxleCount);
	sprintf(GetMsgImage()->FAxleCount,"%010d",InputFAxleCount);
}
void SetExitTRMsgFFareBase(int InputFFareBase)
{
	sprintf(MsgExitTR.FFareBase,"%010d",InputFFareBase);
	sprintf(GetMsgImage()->FFareBase,"%010d",InputFFareBase);
}
void SetExitTRMsgWeightTollFare(float InputWeightTollFare)
{
	sprintf(MsgExitTR.WeightTollFare,"%053.2f",Rounding(InputWeightTollFare));
	sprintf(GetMsgImage()->WeightTollFare,"%053.2f",Rounding(InputWeightTollFare));
}
void SetExitTRMsgWeightLimit(int InputWeightLimit)
{
	sprintf(MsgExitTR.WeightLimit,"%010d",InputWeightLimit);
	sprintf(GetMsgImage()->WeightLimit,"%010d",InputWeightLimit);
}
void SetExitTRMsgWeightLimitTollFare(float InputWeightLimitTollFare)
{
	sprintf(MsgExitTR.WeightLimitTollFare,"%053.2f",Rounding(InputWeightLimitTollFare));
	sprintf(GetMsgImage()->WeightLimitTollFare,"%053.2f",Rounding(InputWeightLimitTollFare));
}
void SetExitTRMsgOverloadWeight(int InputOverloadWeight)
{
	sprintf(MsgExitTR.OverloadWeight,"%010d",InputOverloadWeight);
	sprintf(GetMsgImage()->OverloadWeight,"%010d",InputOverloadWeight);
}
void SetExitTRMsgOverLoadWeightRate(float InputOverLoadWeightRate)
{
	sprintf(MsgExitTR.OverLoadWeightRate,"%053.2f",Rounding(InputOverLoadWeightRate));
	sprintf(GetMsgImage()->OverLoadWeightRate,"%053.2f",Rounding(InputOverLoadWeightRate));
}
void SetExitTRMsgOverloadFare(float InputOverloadFare)
{
	sprintf(MsgExitTR.OverloadFare,"%053.2f",Rounding(InputOverloadFare));
	sprintf(GetMsgImage()->OverloadFare,"%053.2f",Rounding(InputOverloadFare));
}
void SetExitTRMsgSpeed(int InputSpeed)
{
	sprintf(MsgExitTR.Speed,"%010d",InputSpeed);
	sprintf(GetMsgImage()->Speed,"%010d",InputSpeed);
}
void SetExitTRMsgAcceleration(int InputAcceleration)
{
	sprintf(MsgExitTR.Acceleration,"%010d",InputAcceleration);
	sprintf(GetMsgImage()->Acceleration,"%010d",InputAcceleration);
}
void SetExitTRMsgFlagOverWeight(int InputFlagOverWeight)
{
	sprintf(MsgExitTR.FlagOverWeight,"%010d",InputFlagOverWeight);
	sprintf(GetMsgImage()->FlagOverWeight,"%010d",InputFlagOverWeight);
}
void SetExitTRMsgFlagDisCount(int InputFlagDisCount)
{
	sprintf(MsgExitTR.FlagDisCount,"%010d",InputFlagDisCount);
	sprintf(GetMsgImage()->FlagDisCount,"%010d",InputFlagDisCount);
}
void SetExitTRMsgDetectWeightTotal(float InputDetectWeightTotal)
{
	sprintf(MsgExitTR.DetectWeightTotal,"%053.2f",(InputDetectWeightTotal));
	sprintf(GetMsgImage()->DetectWeightTotal,"%053.2f",(InputDetectWeightTotal));
}
void SetExitTRMsgDetectAxleCount(int InputDetectAxleCount)
{
	sprintf(MsgExitTR.DetectAxleCount,"%010d",InputDetectAxleCount);
	sprintf(GetMsgImage()->DetectAxleCount,"%010d",InputDetectAxleCount);
}
void SetExitTRMsgDetectAxleGorup1(float InputDetectAxleGorup1)
{
	sprintf(MsgExitTR.DetectAxleGorup1,"%053.2f",(InputDetectAxleGorup1));
}
void SetExitTRMsgDetectAxleGorup(float InputDetectAxleGorup1,int index)
{
	char *temp = (char *)MsgExitTR.DetectAxleGorup1+index*54;
	sprintf(temp,"%053.2f",Rounding(InputDetectAxleGorup1));
	temp +=53;
	temp[0] = 'X';
}
void SetExitTRMsgRateFareWeight(int InputRateFareWeight)
{
	sprintf(MsgExitTR.RateFareWeight,"%010d",InputRateFareWeight);
}
void SetExitTRMsgDetectAxleGorupOther(int InputDetectAxleGorupOther)
{
	sprintf(MsgExitTR.DetectAxleGorupOther,"%010d",InputDetectAxleGorupOther);
}

//end_ExitTR
