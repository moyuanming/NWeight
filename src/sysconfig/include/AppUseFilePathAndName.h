// ***************************************************************
//  AppUseFilePathAndName   version:  1.0   ·  date: 12/09/2007
//  -------------------------------------------------------------
//  车道程序使用的配置文件临时文件存储位置与路径！
//  -------------------------------------------------------------
//  Copyright (C) 2007 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************


#define PROHEADPATH  "/EMRCV4/"
#ifndef _AppUseFilePathAndName_H_
#define _AppUseFilePathAndName_H_
#define PARAACCESSLEVE_FILE                 GetParameterFileList()->ACCESLVL
#define PARABLACKCARDOPPCARTER_FILE         GetParameterFileList()->OPPCARTE
#define PARABLACKCARDOPPABONNR_FILE         GetParameterFileList()->OPPABONN
#define PARABLACKCARDLSTORANGR_FILE         GetParameterFileList()->LSTORANG

#define PARAFARERECORD_FILE                 GetParameterFileList()->TARI
#define PARAJOURNEYRECORD_FILE              GetParameterFileList()->TRAJ
#define PARAJOURNEYSERVICE_FILE             GetParameterFileList()->JOUSERVI
#define PARASERVICELIST_FILE                GetParameterFileList()->LSTSERVI
#define PARASTAFF_FILE                      GetParameterFileList()->LSTPERSO
#define PARABLACKPLATEOPPLAQUE_FILE         GetParameterFileList()->OPPLAQUE


#define PARAYHKLIST_FILE            GetParameterFileList()->YHKLIST //优惠卡表
#define PARACOLLECT_FILE            GetParameterFileList()->COLLECT //工号表
#define PARAFARELIST_FILE           GetParameterFileList()->FARELIST //费额表
#define PARAYHRATE_FILE             GetParameterFileList()->YHRATE //优惠率
#define PARAYPKLIST_FILE            GetParameterFileList()->YPKLIST //手输式月票卡表
#define PARACARKINDLIST_FILE        GetParameterFileList()->CARKIND_CONF  //车种表
#define PARAJOUCODE_FILE            GetParameterFileList()->JOUCODE //旅程代码表
#define PARASVRCARDLIST_FILE        GetParameterFileList()->SVRCARDLIST //ic卡参数表
#define PARACONSTANT_FILE                   GetParameterFileList()->CONSTANT //计重常量表
#define PARFREECARLIST_FILE				PROHEADPATH"PARAMETER/OfficeInfo.TXT"
#define CONFAPLAZARECORD_FILE               GetParameterFileList()->TOLLSYSTEM
#define FILEPATH_PARAMETER                  PROHEADPATH"PARAMETER/"
#define FILEPATH_PARAMETER_UPDATE           PROHEADPATH"PARAMETER/UPDATE"
#define FILEPATH_PARAMETER_ACTUAL           PROHEADPATH"PARAMETER/ACTUAL"
#define FILEPATH_PARAMETER_ERROR            PROHEADPATH"PARAMETER/ERROR"
#define FILEPATH_PARAMETER_FUTURE           PROHEADPATH"PARAMETER/FUTURE"
#define ICKEY_FILE							PROHEADPATH"PARAMETER/ICKEY"
#define FILEPATH_FTP_PARAMETER              "LDCPARAM"
#define FILEPATH_CONFIG                     PROHEADPATH"CONFIG/"
#define APPFUNCTIONFILENAMEFILE             PROHEADPATH"CONFIG/AppFunction.ini"
#define CONFCOMMUNCTION_FILE                PROHEADPATH"CONFIG/CommunctionConfig.ini"
#define FILENAME_PARAMETER_FILE_LIST        PROHEADPATH"CONFIG/ParameterFileList.ini"
#define LANECONFIGFILENAME_FILE             PROHEADPATH"CONFIG/Config.ini"
#define LANECONFIGFILENAME_FILE             PROHEADPATH"CONFIG/Config.ini"
#define LANEOLDCONFIG_FILE            		PROHEADPATH"CONFIG/BaseConfig.ini"
#define TTYCONFIG_FILE            			PROHEADPATH"CONFIG/TTYCONFIG.ini"

#define FILENAME_ASVE_EXITHT                PROHEADPATH"TEMP/ExitHT.TMP"
#define FILENAME_ASVE_NEWEXITHT             PROHEADPATH"TEMP/NEWExitHT.TMP"
#define FILENAME_ASVE_EXITES                PROHEADPATH"TEMP/ExitES.TMP"
#define FILENAME_ASVE_NEWEXITES             PROHEADPATH"TEMP/NEWExitES.TMP"
#define FILENAME_ASVE_EMRCFROM              PROHEADPATH"TEMP/EMRCFROM.TMP"
#define FILENAME_NO_SEND_MSG_FILE           PROHEADPATH"DATA/Send/"
#define FILENAME_SEND_MSG_BACKUP_FILE       PROHEADPATH"DATA/Send/Archive/"
#define FILENAME_CARDBOX                    PROHEADPATH"TEMP/CradBox.TMP"
#define FILENAME_SETTLEMENT_DATA_JOB_NO     PROHEADPATH"TEMP/SettlementDateAndJobNo.TMP"
#define FILENAME_SAVE_MEOJOB_FILE           PROHEADPATH"TEMP/JOBSUM.TMP"
#define FILENAME_SAVE_MEOJOB_FILE_REVEMOP   PROHEADPATH"TEMP/REVEMOP.TMP"
#define FILENAME_SAVE_MEOJOB_FILE_DISCOUNTMOP   PROHEADPATH"TEMP/DISCOUNTMOP.TMP"
#define FILENAME_SAVE_MEOJOB_FILE_OVERLOADMOP   PROHEADPATH"TEMP/OVERLOADMOP.TMP"
#define FILENAME_SAVE_TrafficDaily          PROHEADPATH"TEMP/TrafficDaily.TMP"
#define FILENAME_SAVE_TrafficHour           PROHEADPATH"TEMP/TrafficHour.TMP"
#define FILENAME_SAVE_WorkInfo              PROHEADPATH"TEMP/WorkInfo.TMP"
#define FILENAME_SAVE_ImageHeader           PROHEADPATH"TEMP/ImageHeader.TMP"
#define FILENAME_SAVE_ImageHeader           PROHEADPATH"TEMP/ImageHeader.TMP"
#define FILENAME_SAVE_ParameterVersion      PROHEADPATH"TEMP/PatameterVersion.TMP"
#define FILENAME_SAVE_ImageTEMP             PROHEADPATH"IMAGE/TEMP/"
#define FILENAME_SAVE_ImageUPLOAD           PROHEADPATH"IMAGE/UPLOAD/"
#define FILENAME_SAVE_ImageArchive           PROHEADPATH"IMAGE/Archive/"
#define FILENAME_LOG_FILE_PATH              PROHEADPATH"LOG/"
#define FILENAME_LOG_FILE_PATH_Archive      PROHEADPATH"LOG/Archive/"
#define FILENAME_SEND_MSG_BACKUP_FILE_Archive       PROHEADPATH"DATA/Send/Archive/"
#define FILENAME_SAVE_TEMP     PROHEADPATH"TEMP/"
#define FILENAME_SAVE_BILLNUMBER     PROHEADPATH"TEMP/BillNumber.TMP"
//EMRC_DB
#define  FILENAME_EMRC_MSG_DB PROHEADPATH"DATA/EMRC_MSG_DB"
#define  FILENAME_EMRC_LOG_DB PROHEADPATH"LOG/EMRC_LOG_DB"
//USB挂载的目录
#define FILENAME_USBDIR  PROHEADPATH"USB/"
#define FILENAME_DISKQUEUE  PROHEADPATH"DATA/DiskQueue"
//USB上的导出数据的目标位置
#define FILENAME_ARCATUSB  "/EMRC-R2_EXPORTET_DATA/"

 
#endif




