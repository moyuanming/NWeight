#ifndef __LOCALINCLUDE_H__
#define __LOCALINCLUDE_H__
 
#define MAXSYSINI 4096
#include "linux_include.h"
#include "global.h"
#include "Udp.h"
#include "common_ic_methods.h"
#include "MessageDef.h"
#include "AppUseFilePathAndName.h"
#include "CommunctionConfig.h"
#include "LanConfig.h"
#include "AppFunctionConfig.h"
#include "MessageHandl.h"
#include "EmrcSocket.h"
#include "init.h"
#include "setWorkState.h"
#include "i_dev_keyboard.h" 
#include "workState.h"
#include "wf_printer.h"
#include "MessageBuild.h"
#include "st_main.h"
#include "LogC.h"
#include "MessageBuild.h"
#include "SendMsg.h"
#include "RecvMessageDataHandl.h"
#include "SwitchContext.h"
#include "ExitBS.h"
#include "ExitEI.h"
#include "ExitES.h"
#include "ExitHt.h"
#include "ExitTR.h"
#include "ExitVI.h"
#include "MsgAK.h"
#include "MsgEI.h"
#include "MsgEM.h"
#include "MsgGR.h"
#include "MsgOF.h"
#include "Image.h"
#include "CarInfoContext.h"
#include "DeviceContext.h"
#include "FileContext.h"
#include "LaneContext.h"
#include "SwitchContext.h"
#include "UserContext.h"
#include "ParameterTable.h"
#include "MemSyncFile.h"
#include "ParameterFileList.h"
#include "ParameterCollect.h"
#include "MsgRevsion.h"
#include "ParameterYPKList.h"
#include "ParameterYHKList.h"
#include "ParameterFareList.h"
#include "ParameterTable.h"
#include "ParameterYHRateDescription.h"
#include "LaneInfo.h"
#include "MsgInfo.h"
#include "systemContext.h"
#include "parameterCarKind.h"
#include "MessageBuild.h"
#include "i_dev_ioboard.h"
#include "i_dev_IO_SAT.h"
#include "MIF_Interface.h"
#include "device.h"
#include "SVRCardList.h"
#include "CardContext.h"
#include "UdpBase.h"
#include "Emrc_Udp.h"
#include "common_main.h"
#include "VideoCaptureImage.h"
#include "workstate_Lstdnyc.h"
#include "i_dev_TFI_KK.h"
#include "i_dev_TFI_303.h"
#include "i_dev_TFI_HN.h"
#include "i_dev_VDM_SAT.h"
#include "i_dev_vdm.h"
#include "EmrcDBOperator.h"
#include "UI_InterFace.h"
#include "UI_Macro.h"
#include "ui.h"
#include "MethodPayContext.h"
#include "SetConfigWorkState.h"
#include "serial.h"
#include "list.h"
#include "carlist.h"
#include "wds_thread.h"
#include "FreeCarList.h"
#include "i_dev_KK_printer.h"
#include "i_dev_S303_printer.h"
#include "i_dev_TWD_printer.h"
#include "ConstantTable.h"
#include "FareCalculation.h"
#include "FareContext.h"
#include "WeightContext.h"
#include "Weight_InterFace.h"
#include "TTYConfig.h"
#include "wds_protocol.h"
#include "TrafficStat.h"
#include "i_dev_VPR_HK.h"
#include "From_800_600.h"
#define FTPSYNCCOMMAND(_sysCommand_,  _l_file_, _r_file_  ) sprintf(_sysCommand_,"ftpget  %s  %s %s\\\\%s  %c",GetParamFtpServerIP(),_l_file_ ,FILEPATH_FTP_PARAMETER,_r_file_,0x00 )
#define echo_ci(fmt, args...)    fprintf(stderr,"ץ��[%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo1(fmt, args...)	  //printf("ECHO:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo_cj(fmt, args...)    fprintf(stderr,"���졢����[%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo(fmt, args...)	  //printf("ECHO:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echoic(fmt, args...)     fprintf(stderr,"echoic:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo_ct(fmt, args...)     fprintf(stderr,"echo_ct:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echocad(fmt, args...)	   //printf("ECHO:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo_everyline(fmt, args...)	//   printf("ECHO:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echocad(fmt, args...)	    //printf("ECHO:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echoprint(fmt, args...)	  // printf("ECHO:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo_wds(fmt, args...)	  // fprintf(stderr,"WDS:::: [%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo_debug_WDS_Dll(fmt, args...)	   //fprintf(stderr,"debug++[%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo_debug(fmt, args...)	   //fprintf(stderr,"debug++[%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#define echo_debugESCOUNT(fmt, args...)	   //fprintf(stderr,"debug++[%s:%d]: " fmt "\n", __FILE__, __LINE__ , ## args)
#endif

