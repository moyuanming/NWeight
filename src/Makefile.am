noinst_PROGRAMS=emrc_main  Sync Uploader ClearAndArchiveData AutoTest
#lib_LTLIBRARIES=libRHY_UI_800_600.so libRHY_640_480 
#lib_LTLIBRARIES=libemrc_logc.la libemrc_billstyle.la libemrc_s303billstyle.la libemrc_communication.la
#libemrc_billstyle_la_LIBADD=-lemrc_logc
#libemrc_s303billstyle_la_LIBADD=-lemrc_logc
#libemrc_communication_la_LIBADD=-lemrc_logc
#emrc_main_LDADD= -lemrc_logc -lemrc_billstyle -lemrc_communication
#RemoteView_LDADD= -lemrc_logc -lemrc_billstyle -lemrc_communication
#Sync_LDADD=-lemrc_logc
#Sync_LDADD=-lemrc_logc
INCLUDES = \
-I$(top_srcdir)/src \
-I$(top_srcdir)/src/include \
-I$(top_srcdir)/src/logc/include \
-I$(top_srcdir)/src/ui/include \
-I$(top_srcdir)/src/dev/include \
-I$(top_srcdir)/src/dev/Weight/include \
-I$(top_srcdir)/src/global/include  \
-I$(top_srcdir)/src/systemcontext/include \
-I$(top_srcdir)/src/workflow/include \
-I$(top_srcdir)/src/uiInterface/include \
-I$(top_srcdir)/src/sysconfig/include \
-I$(top_srcdir)/src/communication/include \
-I$(top_srcdir)/src/dev/include \
-I$(top_srcdir)/src/dev/Print/include \
-I$(top_srcdir)/src/parameter/include \
-I$(top_srcdir)/src/messageBody/include \
-I$(top_srcdir)/src/SQLite/include \
-I$(top_srcdir)/src/ui/include \
-I$(top_srcdir)/src/ui/640_480/include \
-I$(top_srcdir)/src/ui/800_600/include \
-I$(top_srcdir)/src/RemoteControl/include \
-I$(top_srcdir)/src/SetConifgFile/include
COMMON_SUBDIRS = \
parameter/ParameterTable.c \
sysconfig/ParameterFileList.c \
global/global.c  \
global/common_ic_methods.c \
global/FileOperator.c \
global/mac.c \
global/3des.c \
global/imf.c \
sysconfig/CommunctionConfig.c \
sysconfig/LanConfig.c  \
sysconfig/TTYConfig.c \
sysconfig/AppFunctionConfig.c \
systemcontext/systemContext.c  \
systemcontext/LaneContext.c  \
systemcontext/SwitchContext.c  \
systemcontext/UserContext.c  \
systemcontext/DeviceContext.c  \
systemcontext/FileContext.c  \
systemcontext/CarInfoContext.c  \
systemcontext/MethodPayContext.c \
systemcontext/FareCalculation.c \
systemcontext/Image.c \
systemcontext/CardContext.c \
systemcontext/WeightContext.c \
systemcontext/FareContext.c \
sysconfig/IcKey.c \
SQLite/EmrcDBOperator.c \
messageBody/ExitBS.c  \
messageBody/ExitEI.c  \
messageBody/ExitES.c  \
messageBody/ExitHt.c  \
messageBody/ExitTR.c  \
messageBody/ExitVI.c  \
messageBody/MsgAK.c  \
messageBody/MsgEI.c  \
messageBody/MsgEM.c  \
messageBody/MsgGR.c  \
messageBody/MsgOF.c  \
messageBody/MsgInfo.c \
messageBody/LaneInfo.c  \
SetConifgFile/SetConfigWorkState.c \
workflow/init.c \
workflow/setWorkState.c \
workflow/workstate_main.c \
workflow/workstate_ic.c \
workflow/workstate_test.c \
workflow/workstate_peccancy.c \
workflow/wf_printer.c \
workflow/wf_ic.c \
workflow/wf_ioboard.c \
workflow/workstate_Login_Logout.c \
workflow/workstate_Month_Abate.c \
workflow/workstate_QianKuan.c \
workflow/workstate_simulate_first.c \
workflow/workstate_simulate_second.c \
workflow/workstate_Urgent.c \
workflow/workstate_Driver.c \
workflow/workstate_Lstdnyc.c \
workflow/workstate_WeightMenu.c \
global/list.c \
global/carlist.c \
global/serial.c \
dev/Weight/wds_protocol.c \
dev/Weight/wds_thread.c \
dev/Weight/Weight_InterFace.c \
dev/Com/Com.c\
ui/ui.c \
ui/640_480/From_640_480.c \
ui/800_600/From_800_600.c \
ui/UI_InterFace.c \
dev/device.c \
dev/MemSyncFile.c \
dev/VideoCaptureImage.c \
dev/IO_BaseIO_State.c \
dev/i_dev_ic.c  \
dev/i_dev_ioboard.c \
dev/TFI/i_dev_led.c  \
dev/TFI/i_dev_TFI_KK.c \
dev/TFI/i_dev_TFI_303.c \
dev/TFI/i_dev_TFI_HN.c \
dev/Print/i_dev_printer.c \
dev/Print/i_dev_KK_printer.c \
dev/Print/i_dev_TWD_printer.c \
dev/Print/i_dev_S303_printer.c \
dev/i_dev_vdm.c  \
dev/i_dev_keyboard.c \
dev/MIF_Interface.c \
parameter/ParameterCollect.c \
parameter/ParameterYPKList.c \
parameter/ParameterYHRateDescription.c \
parameter/ParameterFareList.c \
parameter/ParameterYHKList.c \
parameter/parameterCarKind.c \
parameter/FreeCarList.c \
parameter/SVRCardList.c \
parameter/ConstantTable.c \
messageBody/MsgRevsion.c  \
messageBody/SendMsg.c 


libemrc_logc_la_SOURCE=		global/common_main.c logc/LogC.c
#libemrc_billstyle_la_SOURCE=		dev/Print/i_dev_printer.c 
#libemrc_s303billstyle_la_SOURCE=	dev/s303_printer.c 
libemrc_communication_la_SOURCE=	communication/MessageBuild.c \
					communication/EmrcSocket.c \
					communication/MessageHandl.c \
					communication/RecvMessageDataHandl.c \
					communication/Emrc_Udp.c \
					communication/Udp.c 
emrc_main_SOURCES           = $(COMMON_SUBDIRS) $(libemrc_logc_la_SOURCE)  \
			      $(libemrc_communication_la_SOURCE) workflow/st_main.c 
			     
#RemoteView_SOURCES	    = $(COMMON_SUBDIRS) $(libemrc_logc_la_SOURCE) $(libemrc_billstyle_la_SOURCE) \
#			       $(libemrc_communication_la_SOURCE) RemoteControl/RemoteView.c \
#			       RemoteControl/RemoteControl.c  RemoteControl/UdpBase.c
#LsFile_SOURCES			=  SubProgarm/LsFile.c
Sync_SOURCES           = $(libemrc_logc_la_SOURCE) SubProgarm/Sync.c \
			 		sysconfig/ParameterFileList.c \
					sysconfig/CommunctionConfig.c \
					communication/Emrc_Udp.c 
Uploader_SOURCES  = $(libemrc_logc_la_SOURCE) SubProgarm/Uploader.c \
		                             sysconfig/ParameterFileList.c \
					       sysconfig/CommunctionConfig.c


ClearAndArchiveData_SOURCES = $(libemrc_logc_la_SOURCE) SubProgarm/ClearAndArchiveData.c \
			     sysconfig/ParameterFileList.c 

AutoTest_SOURCES = $(libemrc_logc_la_SOURCE) communication/Emrc_Udp.c  \
			     Test/AutoRunWorkFlow.c 
