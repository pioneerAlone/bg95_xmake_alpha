/*
 *Copyright :

 *Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.

 *Quectel Wireless Solutions Proprietary and Confidential.
 */
#ifndef __QAPI_QUECTEL_H__
#define __QAPI_QUECTEL_H__

#include "tx_api.h"
#include "qapi_status.h"
#include "qapi_txm_base.h"
#include "qapi_adc_types.h"
#include "qapi_dss.h"
#include "qapi_fs_types.h"
#include "qapi_i2c_master.h"
#include "qapi_timer.h"

/********************* Quectel OEM error number Definitions **********************/
typedef enum{
	QAPI_QT_ERR_OK = 0x1000,
	QAPI_QT_ERR_NORMAL_FAIL,
	QAPI_QT_ERR_INVALID_PARAM,
	QAPI_QT_ERR_OPERATE_FAILED,
	QAPI_QT_ERR_NO_MEM,
	QAPI_QT_ERR_PORT_ID,
	QAPI_QT_ERR_STREAM_ID,
	QAPI_QT_ERR_LOC_STOPPED,
	QAPI_QT_ERR_LOC_STARTED,
	QAPI_QT_ERR_GEOFENCE_ID_NOT_EXIST,
	QAPI_QT_ERR_FOTA_INVALID_PKG,
	QAPI_QT_ERR_FOTA_NOT_IN_DOWNLOADING,
	
	/* Reserved for FTP */
    QAPI_QT_ERR_FTP_ERR_HDL,            /* ftp client handle is null or invalid */
    QAPI_QT_ERR_FTP_OCCUPIED,           /* ftp client already startup */
    QAPI_QT_ERR_FTP_OPEN_CTRL_CON_FAIL, /* ftp connect failed */
    QAPI_QT_ERR_FTP_OPEN_DATA_CON_FAIL, 
    QAPI_QT_ERR_FTP_CLOSED_BY_PEER,
    QAPI_QT_ERR_FTP_NOT_ALLOWED,
    QAPI_QT_ERR_FTP_ERR_RESP,
    QAPI_QT_ERR_FTP_NO_SESS,
    QAPI_QT_ERR_FTP_NO_FILE,
    QAPI_QT_ERR_FTP_READ_FILE,
    QAPI_QT_ERR_FTP_SEND_DATA,

    QAPI_QT_ERR_OPER_NOT_SUPPORT,           /*Operation not supported*/
    QAPI_QT_ERR_GNSS_SUB_BUSY,              /*GNSS subsystem busy.*/
    QAPI_QT_ERR_FUNC_NOT_EN,                /* Function not enable */
    QAPI_QT_ERR_TIME_INFO_ERR,              /*Time info error*/
    QAPI_QT_ERR_GNSS_XTRA_NOT_ENABLE,       /*   XTRA not enable*/
    QAPI_QT_ERR_GNSS_XTRA_FILE_OPEN_ERR,    /*XTRA file open failed.*/
    QAPI_QT_ERR_GNSS_NO_TIME,               /*Not get time now*/
    QAPI_QT_ERR_GNSS_XTRA_FILE_NOT_EXIST,   /*XTRA file is not exist*/
    QAPI_QT_ERR_GNSS_XTRA_ON_DOWNLOADING,   /*xtra downloading */
    QAPI_QT_ERR_GNSS_XTRA_DATA_VALID,       /*xtra data is valid*/
    QAPI_QT_ERR_GNSS_IS_ACTIVE,             /*GNSS is working*/
    QAPI_QT_ERR_GNSS_TIME_INJECT_ERR,       /*Time info error*/
    QAPI_QT_ERR_GNSS_XTRA_DATA_INVALID,     /*xtra data is bad*/
    QAPI_QT_ERR_GNSS_UNKNOWN_ERR,           /*	Unknown*/
  
    QAPI_QT_ERR_API_NOT_SUPPORT = 0x1FFE,
    QAPI_QT_ERR_IVNALID_QT_API = 0x1FFF,
	/*  end  */
	QAPI_QT_ERR_END = 0x2000
}QAPI_QT_ERR_NUM;


/********************* Quectel OEM Definitions **********************/

/********************* Definitions of FOTA **********************/
#define QAPI_DSS_CALL_INFO_USERNAME_MAX_LEN  127  /**< Maxiumum length of the username. */
#define QAPI_DSS_CALL_INFO_PASSWORD_MAX_LEN  127  /**< Maxiumum length of the password. */
#define QAPI_DSS_CALL_INFO_APN_MAX_LEN       150  /**< Maxiumum length of the APN. */

#define APP_FOTA_APN_LEN	  		(QAPI_DSS_CALL_INFO_APN_MAX_LEN + 1)
#define APP_FOTA_APN_USER_LEN 		(QAPI_DSS_CALL_INFO_USERNAME_MAX_LEN + 1)
#define APP_FOTA_APN_PASS_LEN 		(QAPI_DSS_CALL_INFO_PASSWORD_MAX_LEN + 1)

typedef enum
{
  QAPI_FOTA_DSS_IP_VERSION_NON_IP = 0,	/**< IP version Non IP. */
  QAPI_FOTA_DSS_IP_VERSION_4,			/**< IP version v4. */
  QAPI_FOTA_DSS_IP_VERSION_6,			/**< IP version v6. */
  QAPI_FOTA_DSS_IP_VERSION_4_6			/**< IP version v4v6. */
} qapi_QT_FOTA_Pdn_Type_e;

typedef struct
{
	qapi_QT_FOTA_Pdn_Type_e iptype;
	char apn[APP_FOTA_APN_LEN];
	char user[APP_FOTA_APN_USER_LEN];
	char pass[APP_FOTA_APN_PASS_LEN];
} qapi_QT_FOTA_APN_Struct_t;

typedef enum
{
    QAPI_FOTA_PACKAGE_CORRECT = 0,              /* check pass*/
    QAPI_FOTA_PACKAGE_NOT_EXIST = 505,          /*package not exist*/
    QAPI_FOTA_PACKAGE_DAMAGED = 506,            /*package damaged*/
    QAPI_FOTA_PACKAGE_VERSION_MISMATCH = 511,   /*package version mismatch*/
} qapi_QT_FOTA_Package_Check_Result_e;

typedef void(*qapi_QT_FOTA_DL_CB_t)(int error_id);
typedef void(*qapi_QT_FOTA_DL_Process_CB_t)(int percent);

/******************** System Definitions **********************/
typedef enum
{
	QAPI_FATAL_ERR_RESET = 0,
	QAPI_FATAL_ERR_SAHARA = 1,
	QAPI_FATAL_ERR_MAX
}qapi_QT_FATAL_ERR_Mode_e;

/* --- GNSS Configuration--- */
typedef enum
{
	QUEC_GPS_FMT,
	QUEC_GPS_NMEA,
	QUEC_GLO_NMEA,
	QUEC_GAL_NMEA,
	QUEC_BEIDOU_NMEA,
	QUEC_GPS_AUTO,
	QUEC_GNSS_SELECT,
	QUEC_QZSS_NMEA,
	QUEC_GPS_PRIORITY,
	QUEC_GPS_XTRA,
	QUEC_GPS_XTRA_FIEL_SIZE,
	QUEC_GPS_XTRA_TIME,
	QUEC_GPS_XTRA_APN,
	QUEC_GPS_XTRA_TEST_MODE,
	QUEC_GPS_XTRA_AUTO_DL_CTRL,	
	QUEC_GNSS_MAX
}qapi_QT_GNSS_Config_e;

typedef enum
{
    QAPI_QT_GPS_XTRA_AUTO_DL_DISABLE = 0,    /**< XTRA Auto download Disable. */
    QAPI_QT_GPS_XTRA_AUTO_DL_ENABLE  = 1,    /**< XTRA Auto download Enable.  */
    QAPI_QT_GPS_XTRA_AUTO_DL_Mode_MAX
}qapi_QT_XTRA_AUTO_DL_Mode_e;

typedef enum
{
	QUEC_ERR_OK,
	QUEC_ERR_NORMAL_FAIL,
	QUEC_ERR_INVALID_PARAM,
	QUEC_ERR_XTRA_FILE_NO_EXIST,
	QUEC_ERR_XTRA_SYNC_TIME_FAILED,
}qapi_QT_GPS_ERR_ID_e;

typedef enum
{
    QAPI_GPS_XTRA_TEST_MODE_DISABLE = 0,    /**< XTRA Test mode Disable. */
    QAPI_GPS_XTRA_TEST_MODE_ENABLE  = 1,    /**< XTRA Test mode Enable.  */
    QAPI_GPS_XTRA_TEST_MODE_MAX
}qapi_QT_XTRA_Test_Mode_e;

typedef enum
{
    QAPI_GPS_XTRA_IP_TYPE_V4 = 0,	        /**< IP type 4. */
    QAPI_GPS_XTRA_IP_TYPE_V6 = 1,			/**< IP type 6. */
    QAPI_GPS_XTRA_IP_TYPE_MAX
}qapi_QT_GPS_XTRA_IP_Type_e;
    
typedef enum
{
    QAPI_GPS_XTRA_FILE_ONE_DAY   = 1,    /**< XTRA file validity period is 1 day. */
    QAPI_GPS_XTRA_FILE_THREE_DAY = 3,    /**< XTRA file validity period is 3 day. */
    QAPI_GPS_XTRA_FILE_SEVEN_DAY = 7,    /**< XTRA file validity period is 7 day. */
}qapi_QT_XTRA_File_Validity_Period_e;

typedef enum
{
    QAPI_GPS_COLD_START = 0,    /**< GPS cold start. */
    QAPI_GPS_HOT_START  = 1,    /**< GPS hot  start. */
    QAPI_GPS_WARM_START = 2,    /**< GPS warm start. */
    QAPI_GPS_START_MODE_MAX
}qapi_QT_GPS_Start_Mode_e;

typedef struct
{
	uint8 priority;
	union
	{
		uint8 save_flag;
		uint8 loaded_tech;
	}qapi_QT_Save_Loaded_u;
}qapi_QT_GPS_LTE_Priority_t;

typedef struct
{
    uint16_t nYear;
    uint8_t nMonth;
    uint8_t nDay;
    uint8_t nHour;
    uint8_t nMin;
    uint8_t nSec;
	uint16_t used_time;
}qapi_QT_XTRA_Info_t;

typedef struct
{
    uint16_t nYear;
    uint8_t nMonth;
    uint8_t nDay;
    uint8_t nHour;
    uint8_t nMin;
    uint8_t nSec;
	uint16_t unc_time;
}qapi_QT_XTRA_Time_t;

typedef struct
{
    uint16_t nYear;
    uint8_t nMonth;
    uint8_t nDay;
    uint8_t nHour;
    uint8_t nMin;
    uint8_t nSec;
    uint16 duration_time;
}qapi_QT_XTRA_Time_Data_t;

#define QAPI_QT_GPS_XTRA_APN_LEN              80  /**< Maxiumum length of the XTRA APN. */

typedef struct
{
    char    apn[QAPI_QT_GPS_XTRA_APN_LEN];
    uint32  ip_type;
}qapi_QT_APN_t;


typedef enum
{
	QAPI_GPS_JAM_NOMING_CALLBCK = 0, 			//no callback
 	QAPI_GPS_JAMMING_PERIO_CALLBACK = 1,		//Trigger callback periodically in 1s
 	QAPI_GPS_JAMMING_CHANGE_CALLBACK =2			//Trigger when the interference status change
}qapi_QT_GPS_Jamming_Mode_e;

/*
@func
  qapi_QT_GPS_Jamming_CB_t
@brief
  Notification of jamming status
@param[out]
  jamming_state  uint8_t jamming status
    		   0: without jamming
    		   1: exist jamming
  gpsdata  uint32_t,gps Noise Level (RNL)

*/

typedef void(*qapi_QT_GPS_Jamming_CB_t)(uint8_t jamming_status,uint32_t gpsdata);

/******************** System Definitions *********************/
typedef enum
{
	QT_FILE_CHECK_MD5,
	
	QT_FILE_CHECK_MAX
}qapi_QT_Get_File_Hash_e;

/*used to select airplane mode detection.*/
typedef enum
{
	QT_AIRPLANE_CTRL_DISABLE,
	QT_AIRPLANE_CTRL_ENABLE,
	QT_AIRPLANE_CTRL_MAX
}qapi_QT_Airplane_CTRL_Mode_e;

/*used to set sleep mode.*/
typedef enum
{
	QT_QSCLK_IS_DISABLE,
	QT_QSCLK_IS_ENABLE,
	QT_QSCLK_ENABLE_MAX
}qapi_QT_QSCLK_Mode_e;

/*used to set main uart AT function mode.*/
typedef enum
{
	QT_MAIN_UART_DISABLE,
	QT_MAIN_UART_ENABLE,
	QT_MAIN_UART_MAX
}qapi_QT_Main_UART_Mode_e;

/*Dynamically configure the NETLIGHT pin output mode*/
typedef enum
{
	QT_SET_LIGHT_PIN_MODEM_MODE,
	QT_SET_LIGHT_PIN_MINIPCIE_MODE,
	QT_SET_LIGHT_PIN_CUSTOMIZATION_MODE = 3,
	QT_SET_LIGHT_PIN_MAX
}qapi_QT_LED_Mode_e;

/*Get USB events */
typedef enum 
{
	QT_USB_EVENT_DEVICE_CONNECT = 0,
	QT_USB_EVENT_DEVICE_SUSPENDDISCONNECT,
	QT_USB_EVENT_DEVICE_SUSPEND,
	QT_USB_EVENT_DEVICE_RESUME,
	QT_USB_EVENT_DEVICE_RESUME_COMPLETE,
	QT_USB_EVENT_DEVICE_REMOTE_WAKEUP,
	QT_USB_EVENT_DEVICE_CONFIGURED,
	QT_USB_EVENT_DEVICE_UNCONFIGURED,
	QT_USB_EVENT_DEVICE_RESET,
	QT_USB_EVENT_DEVICE_SPEED_CHANGE,
	QT_USB_EVENT_DEVICE_MAX
}qapi_QT_USB_Event_e;

/* --- ATC Pipe --- */
typedef enum
{
	QAPI_PORT_OK = 0,
	QAPI_PORT_ERROR,
	QAPI_PORT_INV_ARG,
	QAPI_PORT_ERROR_SIO,
	QAPI_PORT_OPEN_FAILURE,
	QAPI_PORT_MAX
} qapi_QT_AT_Port_Status_e;

typedef enum
{
	QAPI_AT_PORT_0 = 0,
	QAPI_AT_PORT_1,
	QAPI_AT_PORT_MAX
}qapi_QT_AT_Port_e;

typedef struct
{
	char   data[2048];
	int    len;
} qapi_QT_AT_Pipe_Data_t; 

typedef struct {
 uint16  bkp_valid;    
 uint32  bkp_times;   
 uint32  restore_times;  
 uint32  crash[10];    
 uint32  bkp_page_cnt;     
 uint32  aefs_bkp_badblk_num;
 uint32  modem_bkp_badblk_num; 
}qapi_QT_EFS_Backup_Info_t;

typedef enum
{
    QAPI_QT_APP_EFS_BACKUP=0,
    QAPI_QT_MODEM_EFS_BACKUP,
}qapi_QT_EFS_Backup_Partition_Type_e;

typedef signed short int2;

typedef int2	qapi_QT_AT_Stream_ID_t;
/*
@func
  qapi_QT_AT_Resp_Func_CB_t
@brief
  A callback funtion to register when open internal ATC pipe.
@param[out]
  data	- Pointer, to store the data retured from modem side, like AT command executed result or raw data.
*/
typedef void  (*qapi_QT_AT_Resp_Func_CB_t)(qapi_QT_AT_Pipe_Data_t *data);	//response callback

/*
@func
  qapi_QT_MP_AP_Interaction_CB
@brief
  A callback funtion to register into kernel to monitor MP running status
@param [out]
  void
*/
typedef void (*qapi_QT_MP_AP_Interaction_CB)(uint16);	//response callback

/********************* USB Definitions********************/
typedef enum 
{
  QT_USB_DIAG_NMEA_COMP=0,
  QT_USB_SER3_COMP
} qapi_QT_USB_Mode_Type_e;

typedef struct
{
	char   data[2048];
} qapi_QT_USB_Data_t; 

typedef void (* qapi_NMEA_App_Rx_Cb_t) (uint8 * rx_buf,uint16 len);

/******************** URC Definitions *********************/
typedef struct 
 {
	 char	data[2048];
	 int	len;
 } qapi_QT_Report_URC_Data_t; 

 typedef void (*qapi_QT_URC_Report_CB)(qapi_QT_Report_URC_Data_t *user_data);
 typedef void *qapi_QT_Flash_FOTA_t;

/************************** SMS Definitions *******************************/
typedef enum {
  WMS_MESSAGE_TAG_TYPE_ENUM_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  WMS_TAG_TYPE_MT_READ_V01 = 0x00, 
  WMS_TAG_TYPE_MT_NOT_READ_V01 = 0x01, 
  WMS_TAG_TYPE_MO_SENT_V01 = 0x02, 
  WMS_TAG_TYPE_MO_NOT_SENT_V01 = 0x03, 
  WMS_MESSAGE_TAG_TYPE_ENUM_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}wms_message_tag_type_enum_v01;

typedef wms_message_tag_type_enum_v01 qapi_QT_SMS_Status_e;

#define WMS_MESSAGE_LENGTH_MAX_V01 281
#define WMS_ADDRESS_DIGIT_MAX_V01 21

typedef struct{
  uint32_t data_len;
  uint8_t data[WMS_MESSAGE_LENGTH_MAX_V01];
  uint8_t sender_num[WMS_ADDRESS_DIGIT_MAX_V01];    
}qapi_QT_SMS_Message_Info_t;


typedef struct{
//time_t time;
qapi_QT_SMS_Status_e status;
qapi_QT_SMS_Message_Info_t sms_info;
}qapi_QT_SMS_Message_Rcvd_t;

typedef struct {
char        address[20];
char        message[256];
} qapi_QT_SMS_Message_Content_t;

typedef struct {
  uint8_t number;
  uint8_t type;    /* 0x00-WMS_TAG_NONE; 
                      0x01-WMS_TAG_MT_READ;    0x03-WMS_TAG_MT_NOT_READ;     0x05-WMS_TAG_MO_SENT;     0x07-WMS_TAG_MO_NOT_SENT;
                      0x0D-WMS_TAG_MO_SENT_ST_NOT_RECEIVED;     0x15-WMS_TAG_MO_SENT_ST_NOT_STORED;     0x1D-WMS_TAG_MO_SENT_ST_STORED*/
}qapi_QT_SMS_Message_Index_t;

typedef struct {
  uint8_t sum;
  qapi_QT_SMS_Message_Index_t indices[255];
}qapi_QT_SMS_Message_List_t;  

typedef struct {
//uint8 fo; //no need to set this parameter
uint8 vp;
uint8 pid;
uint8 dcs;
} qapi_QT_SMS_Para_t;

typedef enum {
QT_WMS_MEMORY_STORE_ME=0,
QT_WMS_MEMORY_STORE_MT=1,
QT_WMS_MEMORY_STORE_SM=2,
QT_WMS_MEMORY_STORE_SR=3,
QT_WMS_MEMORY_STORE_MAX
} qapi_QT_SMS_Mem_e;

typedef struct {
qapi_QT_SMS_Mem_e mem1;
qapi_QT_SMS_Mem_e mem2;
qapi_QT_SMS_Mem_e mem3;
} qapi_QT_SMS_CPMS_Set_t;

typedef struct {
uint8        used_num;
uint8        max_num;
} qapi_QT_SMS_Message_Store_t;

typedef enum {
  ALPHA_IRA = 0,        /* International Reference Alphabet T.50 */
  ALPHA_GSM,            /* GSM 7 bit alphabet, not packed to 7 bits
                          (will not contain @ (0x00); might have got mapped to 
                           0xe6 at the ATCOP parser ) */
  ALPHA_UCS2,           /* UCS2 Unicode, rep'd by "4 hex character"-tuplets */
  ALPHA_HEX,            /* HEX, rep'd by "2 hex character"-tuplets */
  ALPHA_8BIT,           /* Octets, of 0-255 value */
  ALPHA_PBM_8BIT,       /* PBM's 8 bit alphabet */
  ALPHA_GSM_WITH_AT,    /* GSM 7 bit alphabet, which contains @ (0x00)
                           This character set should be used when 
                           dsatutil_convert_chset has to be called for sending the
                           converted string to modules other than ATCOP. 
                           the output might contain GSM7 bit @ (0x00) so, str_len on 
                           output string might return a wrong value. Output_len has to be 
                           calculated from the input string only.
                           This is for internal use with in ATCOP. This character
                           set is exactly the same as ALPHA_GSM above */
  ALPHA_PBM_UCS2,       /* The 2 byte representation of UCS2 for PBM */
  ALPHA_GSM_UCS2,       /* Special GSM encoding of UCS2 as specified in 
                           GSM TS 11.11 Annex B */
  ALPHA_MAX
} qapi_QT_Chset_Type_e;

typedef enum {
QT_UNKNOW_NUMBER=0,
QT_INTERNATIONAL_NUMBER=1,
QT_NATIONAL_NUMBER=2,
QT_NUMBER_TYPE_MAX
} qapi_QT_SMS_CSCA_Type_e;

typedef enum {
  QT_RESULT_SUCCESS_V01 = 0, 
  QT_RESULT_FAILURE_V01 = 1, 
}qapi_QT_SMS_Message_Send_Result_e;

typedef struct {

  /*  Result Code */
  qapi_QT_SMS_Message_Send_Result_e result;

  /*  Message ID */
  uint16_t message_id;
  /**<   WMS message ID. */
}qapi_QT_SMS_Message_Send_State_t;
typedef void (*qapi_QT_SMS_Message_Send_State_CB_t)(qapi_QT_SMS_Message_Send_State_t state);

/************************** NETWORK Definitions *******************************/
#define QT_DS_PROFILE_MAX_APN_STRING_LEN (101)
#define QT_DS_PROFILE_MAX_USERNAME_LEN (128)
#define QT_DS_PROFILE_MAX_PASSWORD_LEN (128)

typedef enum {
	QT_NW_CFUN_MIN_FUNC = 0,  
	QT_NW_CFUN_FUNN_FUNC = 1,
	QT_NW_CFUN_SHUT_DOWN = 2,
	QT_NW_CFUN_RESET = 3,
	QT_NW_CFUN_FTM = 4,

	QT_NW_CFUN_MAX
} qapi_QT_NW_CFUN_MODE_e;

typedef enum {
	QT_NW_PREF_GSM = 0,
	QT_NW_PREF_CATM = 1,
	QT_NW_PREF_GSM_CATM = 2,
	QT_NW_PREF_CATNB = 3,
	QT_NW_PREF_GSM_CATNB = 4,
	QT_NW_PREF_CATM_CATNB = 5,
	QT_NW_PREF_GSM_CATM_CATNB = 6,
	QT_NW_PREF_RAT_MAX
}qapi_QT_NW_RAT_PREF_e;

typedef enum {
	QT_NW_PREF_SCAN_CATM_CATNB_GSM = 0,
	QT_NW_PREF_SCAN_CATM_GSM_CATNB = 1,
	QT_NW_PREF_SCAN_CATNB_CATM_GSM = 2,
	QT_NW_PREF_SCAN_CATNB_GSM_CATM = 3,
	QT_NW_PREF_SCAN_GSM_CATM_CATNB = 4,
	QT_NW_PREF_SCAN_GSM_CATNB_CATM = 5,
	QT_NW_PREF_RAT_SCAN_ORDER_MAX
}qapi_QT_NW_RAT_SCAN_ORDER_e;

typedef enum {
	QT_NW_PREF_CS_ONLY = 0,
	QT_NW_PREF_PS_ONLY = 1,
	QT_NW_PREF_CS_PS = 2,
	QT_NW_PREF_SRV_DOMAIN_MAX
} qapi_QT_NW_SRV_DOMAIN_PREF_e;

typedef enum {
	QT_NW_GSM_BAND_EGSM = 0,
	QT_NW_GSM_BAND_PGSM = 1,
	QT_NW_GSM_BAND_PCS_1900 = 2,
	QT_NW_GSM_BAND_DCS_1800 = 3,
	QT_NW_GSM_BAND_CELL_850 = 4,
	QT_NW_GSM_BAND_MAX
}qapi_QT_GSM_BAND_e;

typedef enum
{
	QT_NW_DS_PROFILE_PDP_IPV4 = 0,
	QT_NW_DS_PROFILE_PDP_IPV6 = 1,
	QT_NW_DS_PROFILE_PDP_IPV4V6 = 2,
	QT_NW_DS_PROFILE_PDP_MAX
}qapi_QT_NW_DS_PROFILE_PDP_TYPE_e;

typedef enum {
	QT_NW_DS_PROFILE_AUTH_NONE = 0,
	QT_NW_DS_PROFILE_AUTH_PAP = 1,
	QT_NW_DS_PROFILE_AUTH_CHAP = 2,
	QT_NW_DS_PROFILE_AUTH_PAP_CHAP = 3,
	QT_NW_DS_PROFILE_AUTH_TYPE_MAX
}qapi_QT_NW_DS_PROFILE_AUTH_TYPE_e;

typedef enum
{
	QT_NW_TYPE_LAPI_DISABLE = 0,   /*Forced to disable*/
	QT_NW_TYPE_LAPI_ENABLE = 1,   /*Forced to enable*/
	QT_NW_TYPE_LAPI_AUTO = 2,       /*LAPI functionality is determined by SIM/EFS*/

	QT_NW_TYPE_LAPI_MODE_MAX = QT_NW_TYPE_LAPI_AUTO,
}qapi_QT_NW_Lapi_Type_Cfg_e;

typedef enum
{
	QT_NW_TYPE_LAPI_OFF,
	QT_NW_TYPE_LAPI_ON,

	QT_NW_TYPE_LAPI_SWITCH_MAX = QT_NW_TYPE_LAPI_ON,
}qapi_QT_NW_Lapi_Switch_Cfg_e;

typedef struct {
	unsigned char gsm_band;
	unsigned long long catm_band_low;
	unsigned long long nb_band_low;
}qapi_QT_NW_Band_Params_t;

typedef enum {
	QT_NW_EMTC = 0,
	QT_NW_NB_IOT = 1,
	QT_NW_GSM = 2,   /*GSM not support eDRX and PSM*/
}qapi_QT_NW_RAT_e;

typedef struct {
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	signed short time_zone;
}qapi_QT_Real_Time_Cfg_Params_t;

typedef struct {
	unsigned short arfcn;
	unsigned short mcc;
	unsigned short mnc;
	unsigned short lac;
	unsigned long cell_id;
	qapi_QT_GSM_BAND_e band;
	unsigned char bsic;
	unsigned char rxlev;
	unsigned short drx;
	int c1;
	int c2;
}qapi_QT_NW_GSM_Meas_Info_t;

typedef struct {
	unsigned long earfcn;
	unsigned short mcc;
	unsigned short mnc;
	unsigned short tac;
	unsigned long cell_id;
	unsigned char freq_band;
	unsigned short pci;
	signed short rsrp;
	signed short rsrq;
	signed short rssi;
	signed short sinr;
	unsigned short mnc_len;
}qapi_QT_NW_LTE_Meas_Info_t;

typedef struct {
	qapi_QT_NW_DS_PROFILE_PDP_TYPE_e pdp_type;
	qapi_QT_NW_DS_PROFILE_AUTH_TYPE_e auth_type;
	unsigned char apn[QT_DS_PROFILE_MAX_APN_STRING_LEN + 1];
	unsigned char user_name[QT_DS_PROFILE_MAX_USERNAME_LEN + 1];
	unsigned char pass_word[QT_DS_PROFILE_MAX_PASSWORD_LEN + 1];
}qapi_QT_NW_DS_Profile_PDP_Context_t;

typedef struct {
	unsigned char req_psm_enable;
	unsigned long req_active_timer_value;
	unsigned long req_periodic_tau_timer_value;
}qapi_QT_NW_Req_PSM_Cfg_t;

typedef struct {
	unsigned char alloc_psm_enabled;
	unsigned long alloc_active_timer_value;
	unsigned long alloc_periodic_tau_timer_value;
}qapi_QT_NW_Alloc_PSM_Cfg_t;

typedef struct {
	unsigned char req_edrx_enable;
	qapi_QT_NW_RAT_e rat_mode;
	unsigned char req_ptw_cycle;
	unsigned char req_edrx_cycle;
}qapi_QT_NW_Req_eDRX_Cfg_t;

typedef struct {
	unsigned char alloc_edrx_enable;
	unsigned char alloc_ptw_cycle;
	unsigned char alloc_edrx_cycle;
	unsigned char req_ptw_cycle;
	unsigned char req_edrx_cycle;
}qapi_QT_NW_Alloc_eDRX_Cfg_t;

typedef struct
{
	qapi_QT_NW_Lapi_Type_Cfg_e lapi_mode;
	qapi_QT_NW_Lapi_Switch_Cfg_e lapi_enable;
}qapi_QT_NW_Lapi_Config_Profile_t;								 	
							 
typedef enum
{
	QT_NW_Jamming_Detection_Mode_Disable = 0,
	QT_NW_Jamming_Detection_Mode_Enable = 1,
	QT_NW_Jamming_Detection_Mode_MAX
}qapi_QT_NW_Jamming_Detection_Mode_e;

typedef enum
{
	QT_JAMDET_NOJAMMING = 0,
	QT_JAMDET_JAMMED    = 1,
	QT_JAMDET_MAX
}qapi_QT_NW_Jamming_State_e;

typedef void (*qapi_QT_NW_Jamming_State_CB_t)(const qapi_QT_NW_Jamming_State_e state);

typedef struct
{
	int8_t urc;
	int8_t period;
	int8_t mnl;
	int8_t minch;
	int8_t rsrp;
	int8_t rsrq;
	int8_t rssi;
	int8_t totalrssi;
	int8_t shakeperiod;
	int8_t servenable;
}qapi_QT_NW_Jamming_Detection_CFG_t;

#define QUECTEL_NW_GSM_NEIGHBOURCELL_NUM_MAX 6
#define QUECTEL_NW_LTE_NEIGHBOURCELL_NUM_MAX 8

typedef enum{
QT_NW_RRC_STATE_REPORT_MODE_DISABLE = 0,
QT_NW_RRC_STATE_REPORT_MODE_ENABLE = 1,
QT_NW_RRC_STATE_REPORT_MODE_MAX
}qapi_QT_NW_RRC_State_Report_Mode_e;

typedef enum{
QT_NW_RRC_STATE_IDLE = 0,
QT_NW_RRC_STATE_CONNECTED = 1,
QT_NW_RRC_STATE_MAX
}qapi_QT_NW_RRC_State_e;

typedef void (*qapi_QT_NW_RRC_State_CB_t)(const qapi_QT_NW_RRC_State_e rrc_state);

typedef struct{
	uint8_t  nw_cell_valid;
	uint32_t  nw_mcc;
	uint32_t  nw_mnc;
	uint16_t  nw_lac;
	uint32_t  nw_cell_id;
	uint8_t   nw_bsic;
	uint16_t  nw_arfcn;
	int16_t   nw_rxlev;
	uint8_t   nw_c1;
	uint8_t   nw_c2; 
	uint32_t 	nw_c31;
	uint32_t 	nw_c32;
} qapi_QT_NW_GSM_Neighbourcell_t;

typedef struct {
	uint8_t gsm_neighbourcell_num;
	qapi_QT_NW_GSM_Neighbourcell_t gsm_info[QUECTEL_NW_GSM_NEIGHBOURCELL_NUM_MAX];
}qapi_QT_NW_GSM_Neighbourcell_Info_t;

typedef struct{
	uint32_t nw_earfcn;
	uint16_t nw_pci;
	int16_t nw_rsrp;
	int16_t nw_rsrq;
	int16_t nw_rssi;
	int16_t nw_sinr; 
	uint8_t nw_is_idle;	
	int16_t nw_srxlev;   
	uint8_t nw_cell_resel_priority;
	uint8_t nw_s_non_intra_search;
	uint8_t nw_thresh_serving_low;
	uint8_t nw_s_intra_search;	
}qapi_QT_NW_LTE_Neighbourcell_t;

typedef struct {
	uint8_t nw_rat;
	uint8_t lte_neighbourcell_num;
	qapi_QT_NW_LTE_Neighbourcell_t lte_info[QUECTEL_NW_LTE_NEIGHBOURCELL_NUM_MAX];
}qapi_QT_NW_LTE_Neighbourcell_Info_t;

typedef enum
{
	qapi_QT_timetick_usec = 1,
	qapi_QT_timetick_msec,
	qapi_QT_timetick_sec,
	qapi_QT_timetick_max
}qapi_QT_Timetick_Unit_e;

typedef enum
{
	qapi_QT_URC_Port_USBMODEM,    /* USB MODEM port */
	qapi_QT_URC_Port_UART,         /* MAIN UART port */
	qapi_QT_URC_Port_DAM,           /* DAM port */
	qapi_QT_URC_Port_Max
}qapi_QT_URC_Port_e;

typedef enum
{
    QAPI_SECBOOT_STATUS_GET_FAILED = -1,
	QAPI_SECBOOT_STATUS_NOT_ENABLED = 0,
	QAPI_SECBOOT_STATUS_ENABLED = 1,
	QAPI_SECBOOT_STATUS_END
}qapi_QT_SecBoot_Status_e;
/*********************** IIC Interface Definitions*************************/
#define QT_QAPI_I2CM_PORT_01		QAPI_I2CM_INSTANCE_001_E    //IIC1
#define QT_QAPI_SPIM_PORT_01        QAPI_SPIM_INSTANCE_2_E      //SPI1
#define QT_QAPI_SPIM_PORT_02        QAPI_SPIM_INSTANCE_4_E      //SPI2

typedef struct 
{
    uint32 fota_wd_switch;
    uint32 fota_wd_pin_num;
    uint32 fota_wd_feed_interval;
}qapi_QT_FOTA_WD_CFG_t;   

typedef struct
{
   uint32_t  set_time;  /*!<The RTC alarm time to set, in seconds*/
   uint32_t  remain_time; /*!< Time remaining to RTC alarm, in seconds*/
} qapi_QT_RTC_Alarm_Time_Type_t;

/**------------- Quectel ThreadX APIs Struct Start -------------**/
typedef struct
{
    CHAR *name;
    UINT name_len; 
    UINT state;
    ULONG run_count;
    UINT priority;
    UINT preemption_threshold;
    ULONG time_slice;
    TX_THREAD *next_thread;
    TX_THREAD *next_suspended_thread;
}qapi_QT_Thread_Info_t;

typedef struct
{
    CHAR *name;
    UINT name_len; 
    ULONG available_bytes;
    ULONG fragments;
    TX_THREAD *first_suspended;
    ULONG suspended_count;
    TX_BYTE_POOL *next_pool;
}qapi_QT_Byte_Pool_Info_t;

typedef struct
{
    CHAR *name;
    UINT name_len;
    ULONG current_flags;
    TX_THREAD *first_suspended;
    ULONG suspended_count;
    TX_EVENT_FLAGS_GROUP *next_group;
}qapi_QT_Event_Flags_Info_t;

typedef struct
{
    CHAR *name;
    UINT name_len;
    ULONG enqueued;
    ULONG available_storage;
    TX_THREAD *first_suspended;
    ULONG suspended_count;
    TX_QUEUE *next_queue;
}qapi_QT_Queue_Info_t;   

typedef struct
{
    CHAR *name;
    UINT name_len;
    ULONG current_value;
    TX_THREAD *first_suspended;
    ULONG suspended_count;
    TX_SEMAPHORE *next_semaphore;
}qapi_QT_Semaphore_Info_t;  

typedef struct
{
    CHAR *name;
    UINT name_len;
    ULONG count;
    TX_THREAD *owner;
    TX_THREAD *first_suspended;
    ULONG suspended_count;
    TX_MUTEX *next_mutex;
}qapi_QT_Mutex_Info_t;  

typedef enum
{
	QAPI_QT_DAM_CRASH_DUMP_MODE = 0,
	QAPI_QT_DAM_CRASH_UNLOAD_MODE = 1,
	QAPI_QT_DAM_CRASH_MODE_MAX = 2
}qapi_QT_DAM_Crash_Mode_e;
    
#ifndef QURT_THREAD_ATTR_NAME_MAXLEN
#define QURT_THREAD_ATTR_NAME_MAXLEN    20
#endif
typedef struct
{
	uint32_t sp_info;
	uint32_t lr_info;
	uint32_t pc_info;
	uint32_t fault_addr_info;
    char     thread_name[QURT_THREAD_ATTR_NAME_MAXLEN];
}qapi_QT_DAM_Crash_Info_t;

typedef struct 
 {
  uint32 stack_sp_ptr;
  uint32 stack_start_ptr;
  uint32 stack_end_ptr;
 } qapi_QT_Stack_Info_t;
/**------------- Quectel ThreadX APIs Struct End -------------**/
  
/********************* Quectel OEM ID Definitions **********************/
/* @Note: Each new OEM ID needs to be defined in this enum */
typedef enum
{
#include "qapi_quectel_id_enum.h"
} TXM_OEM_API_ID_DEFINES_E;

/********************* Quectel OEM QAPI Functions **********************/
#ifdef  QAPI_TXM_MODULE  
static __inline void  atc_pipe_cb_uspace_dispatcher(UINT cb_id,
                                                             void *app_cb,
                                                             UINT cb_param1,
                                                             UINT cb_param2,
                                                             UINT cb_param3,
                                                             UINT cb_param4,
                                                             UINT cb_param5,
                                                             UINT cb_param6,
                                                             UINT cb_param7,
                                                             UINT cb_param8)
{
    void (*pfn_app_cb1)(qapi_QT_AT_Pipe_Data_t *);
    if(cb_id == ATC_PIPE_PORT0_CB || cb_id == ATC_PIPE_PORT1_CB || cb_id == ATC_PIPE_PORT2_CB || cb_id == ATC_PIPE_PORT3_CB)
    {
        pfn_app_cb1 = (void (*)(qapi_QT_AT_Pipe_Data_t * ))app_cb;
        (pfn_app_cb1)((qapi_QT_AT_Pipe_Data_t*)cb_param1);
    }	
}

static int atc_usb_cb_uspace_dispatcher(UINT cb_id,
void *app_cb,
UINT cb_param1,
UINT cb_param2,
UINT cb_param3,
UINT cb_param4,
UINT cb_param5,
UINT cb_param6,
UINT cb_param7,
UINT cb_param8)
{
	    void (*pfn_app_cb1) (uint8 *,uint16);

        if(cb_id == ATC_USB_PORT_CB) // custom cb-type1
        {
                pfn_app_cb1 = (void (*)(uint8*, uint16 ))app_cb;
                (pfn_app_cb1)((uint8 *)cb_param1, (uint16)cb_param2);

        }
		return 0;
}

static int atc_report_urc_cb_uspace_dispatcher(UINT cb_id,
void *app_cb,
UINT cb_param1,
UINT cb_param2,
UINT cb_param3,
UINT cb_param4,
UINT cb_param5,
UINT cb_param6,
UINT cb_param7,
UINT cb_param8)
{
	void (*pfn_app_cb1)(qapi_QT_Report_URC_Data_t *);

	pfn_app_cb1 = (void (*)(qapi_QT_Report_URC_Data_t * ))app_cb;
	(pfn_app_cb1)((qapi_QT_Report_URC_Data_t*)cb_param1);
	return 0;
}

static __inline void  qapi_FOTA_dl_start_cb_uspace_dispatcher(UINT cb_id,
void *app_cb,
UINT cb_param1,
UINT cb_param2,
UINT cb_param3,
UINT cb_param4,
UINT cb_param5,
UINT cb_param6,
UINT cb_param7,
UINT cb_param8)
{
	void (*pfn_app_cb1)(int);
	if(cb_id == FOTA_DL_RESP_CB)
	{
		pfn_app_cb1 = (void (*)(int))app_cb;
   		(pfn_app_cb1)((int )cb_param1);
	}
}

static __inline void  qapi_FOTA_dl_process_cb_uspace_dispatcher(UINT cb_id,
void *app_cb,
UINT cb_param1,
UINT cb_param2,
UINT cb_param3,
UINT cb_param4,
UINT cb_param5,
UINT cb_param6,
UINT cb_param7,
UINT cb_param8)
{
	void (*pfn_app_cb1)(int);
	if(cb_id == FOTA_DL_PROCESS_RESP_CB)
	{
		pfn_app_cb1 = (void (*)(int))app_cb;
   		(pfn_app_cb1)((int )cb_param1);
	}
}

static __inline void  qapi_MP_AP_WD_uspace_dispatcher(UINT cb_id,
void *app_cb,
UINT cb_param1,
UINT cb_param2,
UINT cb_param3,
UINT cb_param4,
UINT cb_param5,
UINT cb_param6,
UINT cb_param7,
UINT cb_param8)
{
	void (*qt_mp_ap_cb)(uint16);
	
	if(cb_id == ATC_MP_AP_WD_CB)
	{
        qt_mp_ap_cb = (void (*)(uint16))app_cb;
        (qt_mp_ap_cb)((uint16)cb_param1);
	}
}

static __inline void  qapi_GPS_Jamming_satae_uspace_dispatcher(UINT cb_id,
void *app_cb,
UINT cb_param1,
UINT cb_param2,
UINT cb_param3,
UINT cb_param4,
UINT cb_param5,
UINT cb_param6,
UINT cb_param7,
UINT cb_param8)
{
	void (*qt_gps_jamming_state_cb1)(uint8,uint32);
	if(cb_id == GNSS_GPS_JAMMING_CB)
	{
		qt_gps_jamming_state_cb1 = (void (*)(uint8,uint32))app_cb;
   		(qt_gps_jamming_state_cb1)((uint8)cb_param1,(uint32)cb_param2);
	}
}

static __inline void  qapi_nw_jamdet_state_cb_uspace_dispatcher(UINT cb_id,
                                                             void *app_cb,
                                                             UINT cb_param1,
                                                             UINT cb_param2,
                                                             UINT cb_param3,
                                                             UINT cb_param4,
                                                             UINT cb_param5,
                                                             UINT cb_param6,
                                                             UINT cb_param7,
                                                             UINT cb_param8)
{
	void (*pfn_app_cb1)(int);
	if(cb_id == JAMDET_STATE_CB)
	{
		pfn_app_cb1 = (void (*)(int))app_cb;
   		(pfn_app_cb1)((int)cb_param1);
	}
}

static __inline void  qapi_sms_messgae_send_state_cb_uspace_dispatcher(UINT cb_id,
                                                             void *app_cb,
                                                             UINT cb_param1,
                                                             UINT cb_param2,
                                                             UINT cb_param3,
                                                             UINT cb_param4,
                                                             UINT cb_param5,
                                                             UINT cb_param6,
                                                             UINT cb_param7,
                                                             UINT cb_param8)
{
	void (*pfn_app_cb1)(int);
	if(cb_id == SMS_SEND_STATE_CB)
	{
		pfn_app_cb1 = (void (*)(int))app_cb;
   		(pfn_app_cb1)((int)cb_param1);
	}
}

static __inline void  qapi_nw_rrc_state_cb_uspace_dispatcher(UINT cb_id,
                                                             void *app_cb,
                                                             UINT cb_param1,
                                                             UINT cb_param2,
                                                             UINT cb_param3,
                                                             UINT cb_param4,
                                                             UINT cb_param5,
                                                             UINT cb_param6,
                                                             UINT cb_param7,
                                                             UINT cb_param8)
{
	void (*pfn_app_cb1)(int);
	if(cb_id == RRC_STATE_CB)
	{
		pfn_app_cb1 = (void (*)(int))app_cb;
   		(pfn_app_cb1)((int)cb_param1);
	}
}

#define qapi_QT_Reset_Device()  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_RESET_DEVICE, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Shutdown_Device()  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_SHUTDOWN_DEVICE, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Sahara_Mode_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_SAHARA_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Sahara_Mode_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_SAHARA_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_USB_Sio_Open()  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_NMEA_SIO_OPEN, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_USB_Sio_Close()  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_NMEA_SIO_CLOSE, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_USB_Sio_Transmit(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_NMEA_SIO_SEND, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_USB_Sio_Register(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NMEA_SIO_REGISTER, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)atc_usb_cb_uspace_dispatcher, (ULONG)0, (ULONG)0)
#define qapi_QT_MP_FW_Ver_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_MP_FW_VER_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_AP_FW_Ver_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_AP_FW_VER_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_IMEI_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_IMEI_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_MP_Core_Info_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_MP_CORE_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_AP_Core_Info_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_AP_CORE_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_APPS_OS_Version_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_APPS_OS_VERSION_GET,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_UART_TX_Transmit_State_Get(a,b)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_UART_TX_SEND_STATE_GET,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Manufacturer_Info_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_MANU_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Random_Data_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_PRNG_DATA_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Get_USB_Event(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SYS_GET_USB_EVENT, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Switch_USB_Composition(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SWITCH_USB_COMPOSITION, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Get_USB_Composition(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_GET_USB_COMPOSITION, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SPIM_MultiCS_Set(a,b)      (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SPIM_MULTICS_SET,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SPIM_MultiCS_Get(a,b)      (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SPIM_MULTICS_GET,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Chip_Serial_Num_Get(a)	   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_CHIP_SERIAL_NUM_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Phone_Func_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_PHONE_FUNC_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Phone_Func_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_PHONE_FUNC_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Real_Time_Clock_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_REAL_TIME_CLOCK_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Real_Time_Clock_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_REAL_TIME_CLOCK_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Band_Pref_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_BAND_PREF_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Band_Pref_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_BAND_PREF_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Rat_Pref_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_RAT_PREF_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Rat_Pref_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_RAT_PREF_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Rat_Scan_Pre_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_RAT_SCAN_PREF_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Rat_Scan_Pre_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_RAT_SCAN_PREF_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Srv_Domain_Pref_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_SRV_DOMAIN_PREF_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Srv_Domain_Pref_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_SRV_DOMAIN_PREF_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_PDP_Cfg_Set(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_PDP_CFG_SET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_PDP_Cfg_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_PDP_CFG_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_GSM_Meas_Info_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_GSM_MEAS_INFO_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_LTE_Meas_Info_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_LTE_MEAS_INFO_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_PSM_Cfg_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_PSM_CFG_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_PSM_Cfg_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_PSM_CFG_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_eDRX_Cfg_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_EDRX_CFG_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_eDRX_Cfg_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_EDRX_CFG_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Extend_Band_Pref_Set(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_EXTEND_BAND_PREF_SET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Extend_Band_Pref_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_EXTEND_BAND_PREF_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Lapi_Cfg_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_LAPI_CFG_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Lapi_Cfg_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_LAPI_CFG_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_NAS_Cfg_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_NAS_CFG_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_NAS_Cfg_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_NAS_CFG_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_NCC_Cfg_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_NCC_CFG_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_NCC_Cfg_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_NCC_CFG_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_FGI_Cfg_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_FGI_CFG_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_FGI_Cfg_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_FGI_CFG_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Time_Report_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_TIME_REPORT_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Time_Report_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_TIME_REPORT_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Auto_Time_Update_Set(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_TIME_UPDATE_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Auto_Time_Update_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_TIME_UPDATE_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Jamming_Detection_Mode_Set(a,b)            ((UINT)(_txm_module_system_call4)(TXM_OEM_API_QT_NW_JAMDET_MODE_SET,(ULONG)a, (ULONG)b, (ULONG)0,(ULONG)qapi_nw_jamdet_state_cb_uspace_dispatcher))
#define qapi_QT_NW_Jamming_Detection_Mode_Get(a,b)            ((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_NW_JAMDET_MODE_GET,(ULONG)a, (ULONG)b, (ULONG)0))
#define qapi_QT_NW_Jamming_Detection_CFG_Set(a)            ((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_NW_JAMDET_CFG_SET,(ULONG)a, (ULONG)0, (ULONG)0))
#define qapi_QT_NW_Jamming_Detection_CFG_Get(a)            ((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_NW_JAMDET_CFG_GET,(ULONG)a, (ULONG)0, (ULONG)0))
#define qapi_QT_NW_RRC_State_Set(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_RRC_STATE_SET,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)qapi_nw_rrc_state_cb_uspace_dispatcher, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_RRC_State_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_RRC_STATE_GET,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_Camped_Network_RAT_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_CAMPED_NETWORK_RAT_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_GSM_NeighbourCell_Info_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_GSM_NEIGHBOURCELL_INFO_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_NW_LTE_NeighbourCell_Info_Get(a)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_NW_LTE_NEIGHBOURCELL_INFO_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)

#define qapi_QT_SIM_RDY_Check(a)    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SIM_RDY_Check, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SIM_IMSI_Get(a)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SIM_IMSI_Get, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SIM_CCID_Get(a)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SIM_CCID_Get, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SIM_MSISDN_Get(a)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SIM_MSISDN_Get, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Message_Send(a)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_SEND, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Message_Read(a,b)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_READ, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Message_Delete(a)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_DELETE, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Get_Service_Ready_Status(a) (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_READY, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Message_List(a)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_LIST, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Para_Set(a)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_PARA_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Para_Get(a)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_PARA_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_CPMS_Set(a)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_CPMS_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_CPMS_Get(a)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_CPMS_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Chset_Set(a)    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_CSCS_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Chset_Get(a)    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_CSCS_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Rcvd_Num(a)        (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_RCVD_Num_GET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Message_Status_Get(a,b)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_STATUS_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_CSCA_Set(a,b)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_CSCA_SET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_CSCA_Get(a,b)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SMS_CSCA_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_PDU_Message_Send(a)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_PDU_SMS_SEND, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_PDU_Message_Read(a,b)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_PDU_SMS_READ, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_SMS_Message_Send_CB_Set(a)  ((UINT)(_txm_module_system_call4)(TXM_OEM_API_QT_SMS_SEND_CB_SET,(ULONG)a, (ULONG)0, (ULONG)0,(ULONG)qapi_sms_messgae_send_state_cb_uspace_dispatcher))
#define qapi_QT_QSCLK_Enable_Get(a)			(UINT)_txm_module_system_call6(TXM_OEM_API_QT_QSCLK_ENABLE_GET,  (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0,(ULONG)0)
#define qapi_QT_QSCLK_Enable_Set(a)			(UINT)_txm_module_system_call6(TXM_OEM_API_QT_QSCLK_ENABLE_SET,(ULONG)a,(ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Main_UART_Enable_Get(a)  	(UINT)_txm_module_system_call6(TXM_OEM_API_QT_MAIN_UART_ENABLE_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Main_UART_Enable_Set(a)		(UINT)_txm_module_system_call6(TXM_OEM_API_QT_MAIN_UART_ENABLE_SET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_LED_Mode_Get(a,b,c)  	    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_LED_MODE_CTRL_GET,(ULONG)a, (ULONG)b, (ULONG)c, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_LED_Mode_Set(a,b,c)		    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_LED_MODE_CTRL_SET,(ULONG)a, (ULONG)b, (ULONG)c, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Airplane_CTRL_Set(a)  		(UINT)_txm_module_system_call6(TXM_OEM_API_QT_AIRPLANE_CTRL_SET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Airplane_CTRL_Get(a,b)		(UINT)_txm_module_system_call6(TXM_OEM_API_QT_AIRPLANE_CTRL_GET,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Reg_URC_CB_Hdlr(a,b)        (UINT)_txm_module_system_call6(TXM_OEM_API_QT_REPORT_URC_CB_CON,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)atc_report_urc_cb_uspace_dispatcher, (ULONG)0, (ULONG)0)
#define qapi_QT_Get_File_Hash(a,b,c)        (UINT)_txm_module_system_call6(TXM_OEM_API_QT_CACULATE_ENCRY_BINARY,(ULONG)a, (ULONG)b, (ULONG)c, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_URC_Port_Set(a)              (UINT)_txm_module_system_call6(TXM_OEM_API_QT_URC_PORT_SET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_URC_Port_Get(a)              (UINT)_txm_module_system_call6(TXM_OEM_API_QT_URC_PORT_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)

/**---------------- ATC Pipe QAPIs Begin --------------**/
#define qapi_QT_Apps_AT_Port_Open(a, b, c, d)	((UINT)(_txm_module_system_call5)(TXM_OEM_API_AT_PORT_OPEN,(ULONG)a, (ULONG)b, (ULONG)c, (ULONG)d,(ULONG)atc_pipe_cb_uspace_dispatcher))
#define qapi_QT_Apps_Send_AT(a, b)				((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_AT_SEND,(ULONG)a, (ULONG)b, (ULONG)0))
#define qapi_QT_Apps_Send_AT_HexByte(a, b)		((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_AT_SEND_HEXBYTE,(ULONG)a, (ULONG)b, (ULONG)0))
#define qapi_QT_Apps_Send_AT_General(a, b, c)	((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_AT_SEND_GENERAL,(ULONG)a, (ULONG)b, (ULONG)c))
#define qapi_QT_Apps_AT_Port_Close(a)			((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_AT_PORT_CLOSE,(ULONG)a, (ULONG)0, (ULONG)0))
/**---------------- ATC Pipe QAPIs End --------------**/

#define qapi_QT_Register_Wdog(a,b)				((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_REG_WDOG,(ULONG)a, (ULONG)b, (ULONG)0))
#define qapi_QT_Kick_Wdog(a)					((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_KICK_WDOG,(ULONG)a, (ULONG)0, (ULONG)0))
#define qapi_QT_Stop_Wdog(a)					((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_STOP_WDOG,(ULONG)a, (ULONG)0, (ULONG)0))
#define qapi_QT_USB_Switch_Set(a)				((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_USB_SWITCH_SET,(ULONG)a, (ULONG)0,(ULONG)0))
#define qapi_QT_USB_Switch_Get(a)				((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_USB_SWITCH_GET,(ULONG)a, (ULONG)0,(ULONG)0))
#define qapi_QT_USB_Mode_Set(a)					((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_USB_MODE_SET,(ULONG)a, (ULONG)0, (ULONG)0))
#define qapi_QT_Startup_Type_Get(a)  			((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_START_UP_TYPE_GET,(ULONG)a, (ULONG)0,(ULONG)0))
#define qapi_QT_EFS_Backup(a)					((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_EFS_BACKUP,(ULONG)a, (ULONG)0, (ULONG)0))
#define qapi_QT_EFS_Backup_Info_Get(a,b)  	    ((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_EFS_BACKUP_INFO_GET,(ULONG)a, (ULONG)b,(ULONG)0))
#define qapi_QT_RTC_Alarm_Time_Get(a)    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_RTC_ALARM_TIME_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_RTC_Alarm_Time_Set(a)    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_RTC_ALARM_TIME_SET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)

/**---------------- GNSS QAPIs Begin --------------**/
#define qapi_QT_GNSS_Config_Get(a,b,c)  		(UINT)_txm_module_system_call6(TXM_OEM_API_GNSS_CONFIG_GET, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_GNSS_Config_Set(a,b,c)  		(UINT)_txm_module_system_call6(TXM_OEM_API_GNSS_CONFIG_SET, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_GPS_XTRA_Info_Get(a,b)			(UINT)_txm_module_system_call6(TXM_OEM_API_GPS_XTRA_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_GPS_Delete_Assistance_Data(a)	(UINT)_txm_module_system_call6(TXM_OEM_API_GPS_DELETE_ASSISTANCE_DATA, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_GPS_Query_XTRA_Data(a)		    (UINT)_txm_module_system_call6(TXM_OEM_API_GPS_QUERY_XTRA_DATA, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_GPS_Inject_XTRA_Data(a)			(UINT)_txm_module_system_call6(TXM_OEM_API_GPS_INJECT_XTRA_DATA, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_GPS_XTRA_Download()             (UINT)_txm_module_system_call6(TXM_OEM_API_GPS_XTRA_DOWNLOAD, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_GPS_Jamming_Detection(a,b)      (UINT)_txm_module_system_call6(TXM_OEM_API_GPS_JAMMING_DETECTION, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)qapi_GPS_Jamming_satae_uspace_dispatcher, (ULONG)0, (ULONG)0)
/**---------------- GNSS QAPIs End --------------**/

/**---------------- FOTA QAPIs Begin --------------**/
#define qapi_QT_FOTA_Download_Start(a,b)     ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_DL_START, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)qapi_FOTA_dl_start_cb_uspace_dispatcher, (ULONG)0, (ULONG)0)) 
#define qapi_QT_Remove_FOTA_Package()        ((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_FOTA_REMOVE_PACKAGE,(ULONG)0, (ULONG)0, (ULONG)0)) 
#define qapi_QT_FOTA_Update_Start()		     ((UINT)(_txm_module_system_call5)(TXM_OEM_API_QT_FOTA_UPDATE_START,(ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_FOTA_Get_Package_Info(a,b)   ((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_FOTA_GET_PACKAGE_INFO,(ULONG)a, (ULONG)b, (ULONG)0))
#define qapi_QT_FOTA_Download_Cancel()       ((UINT)(_txm_module_kernel_call_dispatcher)(TXM_OEM_API_QT_FOTA_DL_CANCEL,(ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_FOTA_APN_Set(a)				 ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_APN_SET, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)) 
#define qapi_QT_FOTA_DL_Process(a)			 ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_DL_PROCESS, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)qapi_FOTA_dl_process_cb_uspace_dispatcher, (ULONG)0, (ULONG)0))
#define qapi_QT_Check_FOTA_Package(a)         ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_CHECK_PACKAGE,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
/**---------------- FOTA QAPIs End --------------**/

/**---------------- TIME QAPIs Begin --------------**/
#define qapi_QT_Julian_Convert_To_Sec(a,b)			 ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_JULIAN_CONVERT_SEC, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Sec_Convert_To_Julian(a,b)			 ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_SEC_CONVERT_JULIAN, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Get_Timetick(a)                      ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_GET_TIMETICK, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Time_To_Tick(a,b,c)                  ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_TIME_TO_TICK, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Tick_To_Time(a,b,c)                  ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_TICK_TO_TIME, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Tick_To_Time_V2(a,b,c)               ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_TICK_TO_TIME_V2, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)0, (ULONG)0, (ULONG)0))
/**---------------- TIME QAPIs End --------------**/

/**---------------- FOTA Start ----------------**/
#define qapi_QT_Open_FOTA_Partition(a)			         ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_OPEN_PARTITION, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Close_FOTA_Partition(a)			         ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_CLOSE_PARTITION, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Get_FOTA_Partition_Size(a,b)             ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_GET_PARTITION_SIZE, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Erase_FOTA_Partition(a)                  ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_ERASE_PARTITION, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_Malloc_For_FOTA_Partition_Write(a,b)  ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_MALLOC_MEMORY, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_FOTA_Partiton_Write_Data(a,b,c,d)            ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_PARTITION_WRITE, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)d, (ULONG)0, (ULONG)0))
#define qapi_QT_FOTA_Partiton_Read_Data(a,b,c,d)             ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_FOTA_PARTITION_READ, (ULONG)a, (ULONG)b, (ULONG)c, (ULONG)d, (ULONG)0, (ULONG)0))

/**---------------- DAM CFG Start ----------------**/
#define qapi_QT_DAM_CFG_Partition_Read(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_DAM_CFG_PARTITION_READ,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_DAM_CFG_Partition_Write(a,b) (UINT)_txm_module_system_call6(TXM_OEM_API_QT_DAM_CFG_PARTITION_WRITE,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_DAM_CFG_Partition_Erase()    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_DAM_CFG_PARTITION_ERASE,(ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)

#define qapi_QT_Get_SecBoot_Status(a)    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_GET_SECBOOT_STATUS,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Get_Rand(a)              ((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_GET_RANDOM, (ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))
#define qapi_QT_FOTA_WD_CFG_Get(a)    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_FOTA_WD_CFG_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_FOTA_WD_CFG_Set(a)    (UINT)_txm_module_system_call6(TXM_OEM_API_QT_FOTA_WD_CFG_SET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)

#define qapi_QT_MP_AP_Interaction_Reg(a,b) 	((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_MP_AP_INTERACTION,(ULONG)a, (ULONG)b, (ULONG)0,(ULONG)qapi_MP_AP_WD_uspace_dispatcher, (ULONG)0, (ULONG)0))
#define qapi_QT_PMIC_WD_Kick()				((UINT)(_txm_module_system_call6)(TXM_OEM_API_QT_PMIC_WD,(ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0))

/*-----------------ThreadX APIs Begin------------------*/
#define qapi_QT_Thread_Info_Get(a,b)        (UINT)_txm_module_system_call6(TXM_OEM_API_QT_THREAD_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Byte_Pool_Info_get(a,b)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_BYTE_POOL_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Event_Flags_Info_Get(a,b)   (UINT)_txm_module_system_call6(TXM_OEM_API_QT_EVENT_FLAGS_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Queue_Info_Get(a,b)         (UINT)_txm_module_system_call6(TXM_OEM_API_QT_QUEUE_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Semaphore_Info_Get(a,b)     (UINT)_txm_module_system_call6(TXM_OEM_API_QT_SEMAPHORE_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Mutex_Info_Get(a,b)         (UINT)_txm_module_system_call6(TXM_OEM_API_QT_MUTEX_INFO_GET, (ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_DAM_Crash_Mode_Set(a)		(UINT)_txm_module_system_call6(TXM_OEM_API_QT_DAM_CRASH_MODE_SET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_DAM_Crash_Mode_Get(a)		(UINT)_txm_module_system_call6(TXM_OEM_API_QT_DAM_CRASH_MODE_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_DAM_Crash_Info_Get(a)		(UINT)_txm_module_system_call6(TXM_OEM_API_QT_DAM_CRASH_INFO_GET,(ULONG)a, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_DAM_Crash_Info_Delete()		(UINT)_txm_module_system_call6(TXM_OEM_API_QT_DAM_CRASH_INFO_DELETE,(ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
#define qapi_QT_Thread_Stack_Info_Get(a,b)  (UINT)_txm_module_system_call6(TXM_OEM_API_QT_THREAD_STACK_INFO_GET,(ULONG)a, (ULONG)b, (ULONG)0, (ULONG)0, (ULONG)0, (ULONG)0)
/*-----------------ThreadX APIs End------------------*/
#else
/*
@func
  qapi_QT_Reset_Device
@brief
  reset module. 
@param
  null.
*/
qapi_Status_t qapi_QT_Reset_Device(void);


/*
@func
  qapi_QT_Shutdown_Device
@brief
  Shutdown module.
@param
  null.
*/
qapi_Status_t qapi_QT_Shutdown_Device(void);


/*
@func
  qapi_QT_Sahara_Mode_Get
@brief
  Get the NV Item value of Sahara mode setting.
@param[out]
  mode - Configure options.
    QAPI_FATAL_ERR_RESET -- Reset mode.
    QAPI_FATAL_ERR_SAHARA -- Sahara DUMP mode.
*/
qapi_Status_t qapi_QT_Sahara_Mode_Get(qapi_QT_FATAL_ERR_Mode_e* mode);


/*
@func
  qapi_QT_Sahara_Mode_Set
@brief
  Enable or disable module enter sahara dump mode when module crash.
  It will take effect after the module restarted.
@param[in]
  mode - Configure options.
    QAPI_FATAL_ERR_RESET -- Reset mode.
    QAPI_FATAL_ERR_SAHARA -- Sahara DUMP mode.
*/
qapi_Status_t qapi_QT_Sahara_Mode_Set(qapi_QT_FATAL_ERR_Mode_e mode);


/*
@func
  qapi_QT_USB_Sio_Open
@brief
  Open NMEA USB port for output user application log.
@param
  null
*/
qapi_Status_t qapi_QT_USB_Sio_Open(void);


/*
@func
  qapi_QT_USB_Sio_Close
@brief
  Close NMEA USB port.
@param
  null
*/
qapi_Status_t qapi_QT_USB_Sio_Close(void);


/*
@func
  qapi_QT_USB_Sio_Transmit
@brief
  Output user application log.
@param [in]
  log - Pointer, point to the buffer which store the user application log.
  len - length of log
*/
qapi_Status_t qapi_QT_USB_Sio_Transmit(char* log, int len);

/*
@func
  qapi_QT_USB_Sio_Register
@brief
  Register callback function for USB NMEA port 
@param [in]
  param - callback function for USB NMEA port
  buf - Callback buf user space address,The type must use qapi_QT_USB_Data_t*, and the buf size is 2048 
*/
qapi_Status_t qapi_QT_USB_Sio_Register(void * param,qapi_QT_USB_Data_t* buf);

/*
@func
  qapi_QT_Get_USB_Composition
@brief
  This function is used to get USB composition.
@param[out]
  mode: Pointer, USB composition mode.
  0: QT_USB_DIAG_NMEA_COMP ,DIAG and NMEA composition USB
  1:     HSU_USB_SER3_COMP ,SER3 composition USB
*/
qapi_Status_t qapi_QT_Get_USB_Composition( qapi_QT_USB_Mode_Type_e* mode);

/**
@func
 qapi_QT_Switch_USB_Composition

@brief  switch USB composition.

@param[in] mode     QT_USB_DIAG_NMEA_COMP :DIAG and NMEA composition USB
					QT_USB_NMEA_COMP      :SER3 composition USB            
@return
QUEC_ERR_OK on success, a -ve error code on failure. \n
QAPI_QT_ERR_NORMAL_FAIL  -- The write nv failure.
*/
qapi_Status_t qapi_QT_Switch_USB_Composition(qapi_QT_USB_Mode_Type_e mode);

/*
@func
  qapi_QT_MP_FW_Ver_Get
@brief
  Get module MP firmware version number.
@param [in]
  version - pointer, to store the MP firmware number.
  len - pointer, the length of version string.
*/
qapi_Status_t qapi_QT_MP_FW_Ver_Get(char* version, uint16* len);


/*
@func
  qapi_QT_AP_FW_Ver_Get
@brief
  Get module AP firmware version number.
@param [in]
  version - pointer, to store the AP firmware number.
  len - pointer, the length of version string.
*/
qapi_Status_t qapi_QT_AP_FW_Ver_Get(char* version, uint16* len);


/*
@func
  qapi_QT_IMEI_Get
@brief
  Get module IMEI number.
@param [in]
  imei - pointer, to store the IMEI number.
  len - pointer, the length of imei string.
*/
qapi_Status_t qapi_QT_IMEI_Get(char* imei, uint16* len);


/*
@func
  qapi_QT_MP_Core_Info_Get
@brief
  Get module MP Core information.
@param [in]
  info - pointer, to store the MP Core information.
        It is recommended to apply for 64 bytes.
  len - pointer, the length of info string.
*/
qapi_Status_t qapi_QT_MP_Core_Info_Get(char* info, uint16* len);


/*
@func
  qapi_QT_AP_Core_Info_Get
@brief
  Get module AP Core information.
@param [in]
  info - pointer, to store the AP Core information.
         It is recommended to apply for 64 bytes.
  len - pointer, the length of info string.
*/
qapi_Status_t qapi_QT_AP_Core_Info_Get(char* info, uint16* len);


/*
@func
  qapi_QT_Manufacturer_Info_Get
@brief
  Get module AP Core information.
@param [in]
  info - pointer, to store the Manufacturer Core information. Here will rerutn "Quectel".
  len - pointer, the length of info string.
*/
qapi_Status_t qapi_QT_Manufacturer_Info_Get(char* info, uint16* len);


/*
@func
  qapi_QT_Random_Data_Get
@brief
  Gets the hardware random number
@param [in]
  prng_size - get the length of random Number.Parameters range of the support:1,2,4...512 
@param [out]
  prng_data - Stores the generated random Number,the size of the data returned depends on prng_size
*/
qapi_Status_t qapi_QT_Random_Data_Get(uint16 prng_size, uint8* prng_data);


/*
@func
  qapi_QT_Get_USB_Event
@brief
  Get USB events : 
    0 : DEVICE CONNECT
    1 : DEVICE DISCONNECT
    2 : DEVICE SUSPEND
    3 : DEVICE RESUME
    4 : DEVICE RESUME COMPLETED
    5 : DEVICE REMOTE WAKEUP
    6 : DEVICE CONFIGURED
    7 : DEVICE UNCONFIGURED
    8 : DEVICE RESET
    9 : DEVICE SPEED CHANGE
@param[in]
  usb_evt - pointer, store the USB Event.
*/
qapi_Status_t qapi_QT_Get_USB_Event(qapi_QT_USB_Event_e* usb_evt);

/*
@func
  qapi_QT_Apps_AT_Port_Open
@brief
  Open Apps AT command port and register a callback. 
@param [in]
  port_id - Port ID of ATC pipe. A specified port for AT command execution.
  cb - Callback function address. Function pointer passed to the kernel.
  data - allocate user space for the carried parameter of cb.
@param [out]
  stream_id - Pointer. Stream ID corresponding to the port of the ATC pipe.
*/
qapi_Status_t qapi_QT_Apps_AT_Port_Open(qapi_QT_AT_Port_e port_id, qapi_QT_AT_Stream_ID_t *stream_id, qapi_QT_AT_Resp_Func_CB_t cb, qapi_QT_AT_Pipe_Data_t *data);

/*
@func
  qapi_QT_Apps_Send_AT
@brief
  Send AT command in specifial stream port id. 
@param [in]
  stream_id - The stream ID returned by qapi_QT_Apps_AT_Port_Open().
  command_name - Pointer. The name of the AT command to be sent.
*/
qapi_Status_t qapi_QT_Apps_Send_AT(qapi_QT_AT_Stream_ID_t stream_id, const char *command_name);

/*
@func
  qapi_QT_Apps_Send_AT_HexByte
@brief
  Send string in specifial stream port id with Hex format.
@param [in]
  stream_id - The stream ID returned by qapi_QT_Apps_AT_Port_Open().
  hex_str - Pointer. The name of the hex format AT command to be sent.
*/
qapi_Status_t qapi_QT_Apps_Send_AT_HexByte(qapi_QT_AT_Stream_ID_t stream_id, const char *hex_str);

/*
@func
  qapi_QT_Apps_Send_AT_General
@brief
  Send typeless data in secifial stream port id. Caller can tranmit any type of data through stream port. And
  response will be notified in callback which registed in qapi_QT_Apps_AT_Port_Open(). 
@param [in]
  stream_id - The stream ID returned by qapi_QT_Apps_AT_Port_Open().
  trans_data - Pointer. Untyped data sent.
  trans_len - Length of the data sent.
*/
qapi_Status_t qapi_QT_Apps_Send_AT_General(qapi_QT_AT_Stream_ID_t stream_id, void *trans_data, uint32 trans_len);

/*
@func
  qapi_QT_Apps_AT_Port_Close
@brief
  Close AT command port with stream port id. 
@param [in]
  stream_id - The stream ID returned by qapi_QT_Apps_AT_Port_Open().
*/
void qapi_QT_Apps_AT_Port_Close(qapi_QT_AT_Stream_ID_t stream_id);

/*
@func
  qapi_QT_Register_dog
@brief
  Provides a dynamic method of registering watchdog services for application tasks.
@param [in]
  time - starvation detection threshhold in milliseconds.
@param [out]
  dog_id - used for qapi_QT_Kick_Wdog().
*/
qapi_Status_t qapi_QT_Register_Wdog( uint32 time,uint32 *dog_id);

/*
@func
  qapi_QT_kick_watchdog
@brief
  Report to the Watchdog task, so that it can tell that the monitored task is still functioning properly. 
@param [in]  
  id - dog id returned by qapi_QT_Register_Wdog().
*/
qapi_Status_t qapi_QT_Kick_Wdog(uint32 id);

/*
@func
  qapi_QT_stop_watchdog
@brief
  Used to enbale or disable all watchdogs
@param [in]
  mode - enable or disable watchdog
       1  disable all watchdog
       0  enable all watchdog    
*/
qapi_Status_t qapi_QT_Stop_Wdog(boolean mode);

/*
@func
  qapi_QT_USB_Switch_Set
@brief
  Set a global flag to prevent changing USB mode setting by the AT command AT+QCFGEXT="disusb".
@param [in]
  mode - Enable or disable configuration of USB functions by the AT command
       1  Enable configuration of USB functions by the AT command
       0  Disable configuration of USB functions by the AT command     
*/
qapi_Status_t qapi_QT_USB_Switch_Set(boolean mode);

/*
@func
  qapi_QT_USB_Switch_Get
@brief
  Get the configuration by qapi_QT_USB_Switch_Set().
@param [out]
  mode - The current global flag of preventing changing USB mode.
*/
qapi_Status_t qapi_QT_USB_Switch_Get(uint8* mode);

/*
@func
  qapi_QT_USB_Mode_Set
@brief
  Set the SW usb on/off
@param [in]
  mode - enable or disable the usb.
       1  disable the usb
       0  able the usb   
*/
qapi_Status_t qapi_QT_USB_Mode_Set(boolean mode);

/*
@func
  qapi_QT_Startup_Type_Get
@brief
  Gets the Module startup reason type
@param [out]
  val - Return the value of Module startup reason type.
*/
qapi_Status_t qapi_QT_Startup_Type_Get(uint16 *val);

/*
@func
  qapi_QT_GNSS_Config_Get
@brief
  Get GNSS configruations.
@param [in]
  nmea_type_val - enumeration,
		QUEC_GPS_FMT - Configure NMEA Sentences Protocol Standards
			*quec_gnss_cfg = 0:The output NMEA Sentences conforms to Qualcomm's standards.
			*quec_gnss_cfg = 1:The output NMEA Sentences conforms to NMEA 0183 Version 4.10.
		
		QUEC_GPS_NMEA_TYPE - Configure Output Type of GPS NMEA Sentences.
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GGA.
			*quec_gnss_cfg = 00000010b:Open   RMC.
			*quec_gnss_cfg = 00000100b:Open   GSV.
			*quec_gnss_cfg = 00001000b:Open   GSA.
			*quec_gnss_cfg = 00010000b:Open   VTG.
			*quec_gnss_cfg = 00011111b:Open   all the five types above.

		QUEC_GLO_NMEA - Configure Output Type of GLONASS NMEA Sentences.
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GSV.
			*quec_gnss_cfg = 00000010b:Open   GSA.
			*quec_gnss_cfg = 00000011b:Open   all the two types above.
			
		QUEC_GAL_NMEA - Configure Output Type of Galileo NMEA Sentences.
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GSV.
			*quec_gnss_cfg = 00000010b:Open   GSA.
			*quec_gnss_cfg = 00000011b:Open   all the two types above.
			
		QUEC_BEIDOU_NMEA - Configure Output Type of BeiDou NMEA Sentences .
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GSA.
			*quec_gnss_cfg = 00000010b:Open   GSV.
			*quec_gnss_cfg = 00000011b:Open   all the two types above.
		
		QUEC_QZSS_NMEA - Configure Output Type of QZSS NMEA Sentences .
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GSA.
			
		QUEC_GPS_AUTO - Enable/Disable GNSS to Run Automatically.
			*quec_gnss_cfg = 0:Disable GNSS to run automatically.
			*quec_gnss_cfg = 1:Enable GNSS to run automatically.

		QUEC_GNSS_SELECT - Configure Supported GNSS Constellation.
			*quec_gnss_cfg = 1:GPS ON/GLONASS ON/BeiDou OFF/Galileo OFF/QZSS OFF.
			*quec_gnss_cfg = 2:GPS ON/GLONASS OFF/BeiDou ON/Galileo OFF/QZSS OFF.
			*quec_gnss_cfg = 3:GPS ON/GLONASS OFF/BeiDou OFF/Galileo ON/QZSS OFF.
			*quec_gnss_cfg = 4:GPS ON/GLONASS OFF/BeiDou OFF/Galileo OFF/QZSS ON.
			*quec_gnss_cfg = 5:The constellation is selected based on MCC of camped network.
			
		QUEC_GPS_PRIORITY - Get GNSS and LTE priority.
		    The value of *quec_gnss_cfg refers to qapi_QT_GPS_LTE_Priority_t:
			priority  	0 	GNSS is in high priority 
						1	LTE is in high priority
			loaded_tech	0	Neither GPS nor LTE
						1	LTE Pending
						2	GPS Pending
						3	LTE Loaded
						4	GPS Loaded

		QUEC_GPS_XTRA - Enable gpsOneXTRA Assistance Function.
			*quec_gnss_cfg = 0:Disable gpsOneXTRA Assistance.
			*quec_gnss_cfg = 1:Enable gpsOneXTRA Assistance.

		QUEC_GPS_XTRA_FIEL_SIZE - Select Which XTRA File to be Downloaded.
		    The value of *quec_gnss_cfg refers to qapi_QT_XTRA_File_Validity_Period_e:
			*quec_gnss_cfg = 1:Download the XTRA file which term of validity is 1 day.
			*quec_gnss_cfg = 3:Download the XTRA file which term of validity is 3 day.
			*quec_gnss_cfg = 7:Download the XTRA file which term of validity is 7 day.
			
		QUEC_GPS_XTRA_TIME - The module will auto sync time from network by NITZ. 
								Customer can use qapi_QT_GNSS_Config_Get(QUEC_GPS_XTRA_TIME...) to query the synchronized time.
							    If there is a network state, the time acquired by this interface is the network time.
							    Before using it, customers must enable gpsOneXTRA Assistance function via qapi_QT_GNSS_Config_Set(QUEC_GPS_XTRA...) function.
		    The value of *quec_gnss_cfg refers to qapi_QT_XTRA_Time_t:
			nYear - Current UTC/GPS time
		    nMonth		
		    nDay		
		    nHour		
		    nMin		
		    nSec		
			unc_time - This parameter is invalid.
			
        QUEC_GPS_XTRA_APN - Configure XTRA APN
		    The value of *quec_gnss_cfg refers to qapi_QT_APN_t:
            apn - Access point name. Support up to QAPI_QT_GPS_XTRA_APN_LEN bytes of data.
            ip_type - IP family type refers to qapi_QT_GPS_XTRA_IP_Type_e.
                0: IPv4
                1: IPv6
  
        QUEC_GPS_XTRA_TEST_MODE - Enable/Disable XTRA Test Mode.This function is used for testing cold start with XTRA. Do not enable it in commercial use
		    The value of *quec_gnss_cfg refers to qapi_QT_XTRA_Test_Mode_e:
            *quec_gnss_cfg = 0:Disable XTRA test mode.
            *quec_gnss_cfg = 1:Enable XTRA test mode. The XTRA file download times is unlimited.

        QUEC_GPS_XTRA_AUTO_DL_CTRL - Enable/Disable auto download xtra file.When enable gpsOneXTRA Assistance Function and auto down xtra function, invoke 
                                qapi_Loc_Start_Tracking() will download xtra file automatically when the Xtra file does not exist or is expired.You can 
                                set it 0 to disable auto download.And the Mode value is stored in NV.The download status can be seen in qapi_Location_Meta_Data_Engine_Status_t.
                                Default:1
            *quec_gnss_cfg = QAPI_QT_GPS_XTRA_AUTO_DL_DISABLE:Disable auto download xtra.Refer to qapi_QT_XTRA_AUTO_DL_Mode_e.
	        *quec_gnss_cfg = QAPI_QT_GPS_XTRA_AUTO_DL_ENABLE:Enable auto download xtra.           

  quec_gnss_cfg_size - The size of quec_gnss_cfg
  @param [out]
  quec_gnss_cfg - pointer to get gnss config.
*/
qapi_Status_t qapi_QT_GNSS_Config_Get(qapi_QT_GNSS_Config_e nmea_type_val,void *quec_gnss_cfg,uint32 quec_gnss_cfg_size);

/*
@func
  qapi_QT_GNSS_Config_Set
@brief
  Set gnss config.
@param [in]
  nmea_type_val - enumeration,
		QUEC_GPS_FMT - Configure NMEA Sentences Protocol Standards
			*quec_gnss_cfg = 0:The output NMEA Sentences conforms to Qualcomm's standards.
			*quec_gnss_cfg = 1:The output NMEA Sentences conforms to NMEA 0183 Version 4.10.
		
		QUEC_GPS_NMEA - Configure Output Type of GPS NMEA Sentences.
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GGA.
			*quec_gnss_cfg = 00000010b:Open   RMC.
			*quec_gnss_cfg = 00000100b:Open   GSV.
			*quec_gnss_cfg = 00001000b:Open   GSA.
			*quec_gnss_cfg = 00010000b:Open   VTG.
			*quec_gnss_cfg = 00011111b:Open   all the five types above.

		QUEC_GLO_NMEA - Configure Output Type of GLONASS NMEA Sentences.
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GSV.
			*quec_gnss_cfg = 00000010b:Open   GSA.
			*quec_gnss_cfg = 00000011b:Open   all the two types above.
			
		QUEC_GAL_NMEA - Configure Output Type of Galileo NMEA Sentences.
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GSV.
			*quec_gnss_cfg = 00000010b:Open   GSA.
			*quec_gnss_cfg = 00000011b:Open   all the two types above.
			
		QUEC_BEIDOU_NMEA - Configure Output Type of BeiDou NMEA Sentences .
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GSA.
			*quec_gnss_cfg = 00000010b:Open   GSV.
			*quec_gnss_cfg = 00000011b:Open   all the two types above.

		QUEC_QZSS_NMEA - Configure Output Type of QZSS NMEA Sentences .
			*quec_gnss_cfg = 00000000b:Close the output of nmea statements.
			*quec_gnss_cfg = 00000001b:Open   GSA.
		
		QUEC_GPS_AUTO - Enable/Disable GNSS to Run Automatically.
			*quec_gnss_cfg = 0:Disable GNSS to run automatically.
			*quec_gnss_cfg = 1:Enable GNSS to run automatically.

		QUEC_GNSS_SELECT - Configure Supported GNSS Constellation.
			*quec_gnss_cfg = 1:GPS ON/GLONASS ON/BeiDou OFF/Galileo OFF/QZSS OFF.
			*quec_gnss_cfg = 2:GPS ON/GLONASS OFF/BeiDou ON/Galileo OFF/QZSS OFF.
			*quec_gnss_cfg = 3:GPS ON/GLONASS OFF/BeiDou OFF/Galileo ON/QZSS OFF.
			*quec_gnss_cfg = 4:GPS ON/GLONASS OFF/BeiDou OFF/Galileo OFF/QZSS ON.
			*quec_gnss_cfg = 5:The constellation is selected based on MCC of camped network.
			
		QUEC_GPS_PRIORITY - Set GNSS and LTE priority.This parameter is effective immediately.
		    The value of *quec_gnss_cfg refers to qapi_QT_GPS_LTE_Priority_t:
			priority  	0:GNSS is in high priority 
						1:LTE is in high priority
			save_flag 	0:priority is not saved to NVRAM
						1:priority is saved to NVRAM

		QUEC_GPS_XTRA - Enable gpsOneXTRA Assistance Function.
			*quec_gnss_cfg = 0:Disable gpsOneXTRA Assistance.
			*quec_gnss_cfg = 1:Enable gpsOneXTRA Assistance.

		QUEC_GPS_XTRA_FIEL_SIZE - Select Which XTRA File to be Downloaded.
		    The value of *quec_gnss_cfg refers to qapi_QT_XTRA_File_Validity_Period_e:
			*quec_gnss_cfg = 1:Download the XTRA file which term of validity is 1 day.
			*quec_gnss_cfg = 3:Download the XTRA file which term of validity is 3 day.
			*quec_gnss_cfg = 7:Download the XTRA file which term of validity is 7 day.
			
		QUEC_GPS_XTRA_TIME - Inject gpsOneXTRA Time.
								The function only need to inject time when you call qapi_QT_GNSS_Config_Get (QUEC_GPS_XTRA_TIME ...) without getting the time.
								Before using it, customers must enable gpsOneXTRA Assistance function via qapi_QT_GNSS_Config_Set(QUEC_GPS_XTRA...) function.
		    The value of *quec_gnss_cfg refers to qapi_QT_XTRA_Time_t:
			nYear - Current UTC/GPS time
		    nMonth		
		    nDay		
		    nHour		
		    nMin		
		    nSec		
			unc_time - This parameter refers to the error value between the actual time and the set time.

        QUEC_GPS_XTRA_APN - Configure XTRA APN
		    The value of *quec_gnss_cfg refers to qapi_QT_APN_t:
            apn - Access point name. Support up to QAPI_QT_GPS_XTRA_APN_LEN bytes of data.
            ip_type - IP family type refers to qapi_QT_GPS_XTRA_IP_Type_e.
                0: IPv4
                1: IPv6
      
        QUEC_GPS_XTRA_TEST_MODE - Enable/Disable XTRA Test Mode.This function is used for testing cold start with XTRA. Do not enable it in commercial use
		    The value of *quec_gnss_cfg refers to qapi_QT_XTRA_Test_Mode_e:
            *quec_gnss_cfg = 0:Disable XTRA test mode.
            *quec_gnss_cfg = 1:Enable XTRA test mode. The XTRA file download times is unlimited.

        QUEC_GPS_XTRA_AUTO_DL_CTRL - Enable/Disable auto download xtra file.When enable gpsOneXTRA Assistance Function and auto down xtra function, invoke 
                                qapi_Loc_Start_Tracking() will download xtra file automatically when the Xtra file does not exist or is expired.You can 
                                set it 0 to disable auto download.And the Mode value is stored in NV.The download status can be seen in qapi_Location_Meta_Data_Engine_Status_t.
                                Default:1
            *quec_gnss_cfg = QAPI_QT_GPS_XTRA_AUTO_DL_DISABLE:Disable auto download xtra.Refer to qapi_QT_XTRA_AUTO_DL_Mode_e.
	        *quec_gnss_cfg = QAPI_QT_GPS_XTRA_AUTO_DL_ENABLE:Enable auto download xtra.          

  quec_gnss_cfg - pointer to set gnss config
  quec_gnss_cfg_size - The size of quec_gnss_cfg.
*/
qapi_Status_t qapi_QT_GNSS_Config_Set(qapi_QT_GNSS_Config_e nmea_type_val, void* quec_gnss_cfg,uint32 quec_gnss_cfg_size);

/*
@func
  qapi_QT_GPS_Xtra_Info_Get
@brief
  This function is used to get gps xtra information.
@param[out]
    quec_xtra_info: get gps xtra information
		nYear	   - Last XTRA data download time in UTC
		nMonth
		nDay
		nHour
		nMin
		nSec
		used_time  -Number of hours for which the current XTRA information is valid
	err_id : get error information
		QUEC_ERR_OK - no error
		QUEC_ERR_NORMAL_FAIL - Normal error
		QUEC_ERR_INVALID_PARAM - Invalid parameter
		QUEC_ERR_XTRA_FILE_NO_EXIST -XTRA file does not exist
		QUEC_ERR_XTRA_SYNC_TIME_FAILED -XTRA file download time analysis failed	
*/
qapi_Status_t qapi_QT_GPS_XTRA_Info_Get(qapi_QT_XTRA_Info_t *quec_xtra_info,qapi_QT_GPS_ERR_ID_e *err_id);

/*
@func
  qapi_QT_QSCLK_Enable_Set
@brief
  To control whether the module enters into sleep mode.The QAPI function is the same as the AT+QSCLK 
@param [in]
  mode - Enable or disable sleep mode
       1  enable sleep mode
       0  disable sleep mode 
*/
qapi_Status_t qapi_QT_QSCLK_Enable_Set(qapi_QT_QSCLK_Mode_e mode);

/*
@func
  qapi_QT_QSCLK_Enable_Get
@brief
  To get current status of sleep mode
@param [out]
   mode - Return current status of sleep mode, the value is the same as AT+QSCLK.
*/
qapi_Status_t qapi_QT_QSCLK_Enable_Get(qapi_QT_QSCLK_Mode_e* mode);

/*
@func
  qapi_QT_Main_UART_Enable_Set
@brief
  To enable or disable current mode of AT function on main UART. It takes effect after the module restart.
@param [in]
  mode - Enable or disable AT function on main UART, if disable, main UART will be changed to general UART.
       1  close main UART AT function
       0  open main UART AT function
*/
qapi_Status_t qapi_QT_Main_UART_Enable_Set(qapi_QT_Main_UART_Mode_e mode);

/*
@func
  qapi_QT_Main_UART_Enable_Get
@brief
  To get current mode of AT function on main UART.
@param [out]
  mode - Return current mode of AT function on main UART.
*/
qapi_Status_t qapi_QT_Main_UART_Enable_Get(qapi_QT_Main_UART_Mode_e* mode);

/*
@func
  qapi_QT_LED_Mode_Get
@brief
  Gets the current output mode and output level configuration of the NET_STATUS pin.
@param [out]
mode - Current output mode of NET_STATUS pin.
time_on - Current time of duration that the NETLIGHT pin output level is high.
time_off - Current time of duration that the NETLIGHT pin output level is low.
*/
qapi_Status_t qapi_QT_LED_Mode_Get(qapi_QT_LED_Mode_e* mode,uint32* time_on,uint32* time_off);

/*
@func
  qapi_QT_LED_Mode_Set
@brief
  Dynamically configures the output mode and output level of NET_STATUS pin.
@param [in]
  mode - NET_STATUS output mode to be set
       0  Set the NETLIGHT pin to be modem mode.
       1  Set the NETLIGHT pin to be minipcie mode. 
       3  Set the NETLIGHT pin to be customization mode.
  time_on - Time of duration that the NETLIGHT pin output level is high to be set.
  time_off - Time of duration that the NETLIGHT pin output level is low to be set.
*/
qapi_Status_t qapi_QT_LED_Mode_Set(qapi_QT_LED_Mode_e mode,uint32  time_on,uint32  time_off);

/*
@func
  qapi_QT_Airplane_CTRL_Set
@brief
  To used to enable or disable airplane mode detection.The QAPI function is same as the AT+QCFG="airplanecontrol"
  This function is not supported on BG600LM3.
@param [in]
 airplane_control_enable - enable/disable airplane mode detection.
        0  Disable airplane mode detection.
        1  Enable airplane mode detection.
*/
qapi_Status_t qapi_QT_Airplane_CTRL_Set(qapi_QT_Airplane_CTRL_Mode_e airplane_control_enable);

/*
@func
  qapi_QT_Airplane_CTRL_Get
@brief
  Gets the current configuration of airplane mode.
  This function is not supported on BG600LM3
@param [out]
  airplane_control_enable - The current configuration of airplane mode.
  airplane_control_status - The current airplane mode control status.
*/
qapi_Status_t qapi_QT_Airplane_CTRL_Get(qapi_QT_Airplane_CTRL_Mode_e* airplane_control_enable,uint8* airplane_control_status);

/*
@func
  qapi_QT_Reg_URC_CB_Hdlr
@brief
  To registered user space callback to receive URC messages
@param [in]
  cb - URC callback function defined in user space.
  buff - URC buffer defined in user space.
*/
qapi_Status_t qapi_QT_Reg_URC_CB_Hdlr(qapi_QT_URC_Report_CB cb,qapi_QT_Report_URC_Data_t *buff);

/*
@func
  qapi_QT_Get_File_Hash
@brief
  This function is used to encrypt file data to generate MD5/CRC.
@param [in]
  path - File path
  type - Encryption type
@param[out]
  output - Encrypted data
@return 
  QAPI_QT_ERR_OK  -- OK.
  Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Get_File_Hash(const char *path, qapi_QT_Get_File_Hash_e type, char *output);

/*
@func
  qapi_QT_Phone_Func_Set
@brief
  This function is used to set phone functionality
@param [in]
  fun - Used to set the module functionality. Please refer to the enumeration qapi_QT_NW_CFUN_MODE_e
*/
qapi_Status_t qapi_QT_Phone_Func_Set(qapi_QT_NW_CFUN_MODE_e* fun);

/*
@func
  qapi_QT_Phone_Func_Get
@brief
  This function is used to get current functionality configuration
@param [in]
  fun - Used to store the current functionality configuration
*/
qapi_Status_t qapi_QT_Phone_Func_Get(qapi_QT_NW_CFUN_MODE_e *fun);

/*
@func
  qapi_QT_Real_Time_Clock_Set
@brief
  This function is used to set real time of the module
@param [in]
  time - Used to store the time setting value.
*/
qapi_Status_t qapi_QT_Real_Time_Clock_Set(qapi_QT_Real_Time_Cfg_Params_t *time);

/*
@func
  qapi_QT_Real_Time_Clock_Get
@brief
  This function is used to get real time of the module.
@param [in]
  time - Used to store the time values get form modem. Same with AT+CCLK result..
*/
qapi_Status_t qapi_QT_Real_Time_Clock_Get(qapi_QT_Real_Time_Cfg_Params_t *time);

/*
@func
  qapi_QT_NW_Band_Pref_Set
@brief
  This function is used to set preferred band
@param [in]
  band_pref - Used to set the preferred band.
*/
qapi_Status_t qapi_QT_NW_Band_Pref_Set(qapi_QT_NW_Band_Params_t *band_pref);

/*
@func
  qapi_QT_NW_Band_Pref_Get
@brief
  This function is used to get preferred band
@param [out]
  band_pref - Used to store the preferred band.
*/
qapi_Status_t qapi_QT_NW_Band_Pref_Get(qapi_QT_NW_Band_Params_t *band_pref);

/*
@func
  qapi_QT_NW_Extend_Band_Pref_Set
@brief
  This function is used to get band of configuration (B65 ~ B128).
@param [in]
  catm_band - Used to store the CATM preferred band (B65 ~ B128)..
  nb_band - Used to store the NB preferred band (B65 ~ B128).
*/
qapi_Status_t qapi_QT_NW_Extend_Band_Pref_Set(uint64 *catm_band, uint64 *nb_band);

/*
@func
  qapi_QT_NW_Extend_Band_Pref_Get
@brief
  This function is used to config preferred band (B65 ~ B128)
@param [out]
  catm_band - Used to store the CATM preferred band (B65 ~ B128)..
  nb_band - Used to store the NB preferred band (B65 ~ B128).
*/
qapi_Status_t qapi_QT_NW_Extend_Band_Pref_Get(uint64 *catm_band, uint64 *nb_band);

/*
@func
  qapi_QT_NW_Rat_Pref_Set
@brief
  This function is used to set preferred RAT (Radio Access Technology).
@param [in]
  mode - Used to configure preferred RAT.
*/
qapi_Status_t qapi_QT_NW_Rat_Pref_Set(qapi_QT_NW_RAT_PREF_e *mode);

/*
@func
  qapi_QT_NW_Rat_Pref_Get
@brief
  This function is used to get preferred RAT (Radio Access Technology).
@param [out]
  mode - Used to store the current configuration of preferred RAT.
*/
qapi_Status_t qapi_QT_NW_Rat_Pref_Get(qapi_QT_NW_RAT_PREF_e *mode);

/*
@func
  qapi_QT_NW_Rat_Scan_Pre_Set
@brief
  This function is used to set configuration of preference of RAT scan.
@param [in]
  order - Used to configure the RAT scan preference.
*/
qapi_Status_t qapi_QT_NW_Rat_Scan_Pre_Set(qapi_QT_NW_RAT_SCAN_ORDER_e *order);

/*
@func
  qapi_QT_NW_Rat_Scan_Pre_Get
@brief
  This function is used to get configuration of preference of RAT scan.
@param [in]
  order - Used to store the current configuration of preference of RAT scan.
*/
qapi_Status_t qapi_QT_NW_Rat_Scan_Pre_Get(qapi_QT_NW_RAT_SCAN_ORDER_e *order);

/*
@func
  qapi_QT_NW_Srv_Domain_Pref_Set
@brief
  This function is used to set configuration of preferred service domain
@param [in]
  domain - Pointer. Used to configure the preferred service domain.
*/
qapi_Status_t qapi_QT_NW_Srv_Domain_Pref_Set(qapi_QT_NW_SRV_DOMAIN_PREF_e *domain);

/*
@func
  qapi_QT_NW_Srv_Domain_Pref_Get
@brief
  This function is used to get configuration of preferred service domain.
@param [out]
  domain - Used to store the current configuration of preferred service domain.
*/
qapi_Status_t qapi_QT_NW_Srv_Domain_Pref_Get(qapi_QT_NW_SRV_DOMAIN_PREF_e *domain);

/*
@func
  qapi_QT_NW_PDP_Cfg_Set
@brief
  This function is used to configure the specific PDP context. 
@param [in]
  pdp_context_number - Pointer. Indicate specific PDP context that needs to be configured.
  profile - Pointer. Used to configure the specific PDP context.
*/
qapi_Status_t qapi_QT_NW_PDP_Cfg_Set(uint8 *pdp_context_number, qapi_QT_NW_DS_Profile_PDP_Context_t *profile);

/*
@func
  qapi_QT_NW_PDP_Cfg_Get
@brief
  This function is used to get configuration of specific PDP context. 
@param [in]
  pdp_context_number - Pointer. Indicate the specific PDP context whose configuration is needed.
@param [out]
  profile - Pointer. Used to store the configuration of the specific PDP context.
*/
qapi_Status_t qapi_QT_NW_PDP_Cfg_Get(uint8 *pdp_context_number, qapi_QT_NW_DS_Profile_PDP_Context_t* profile);

/*
@func
  qapi_QT_NW_GSM_Meas_Info_Get
@brief
  This function is used to get information of measurement under GSM.
@param [out]
  meas_info - Pointer. Used to store information of measurement under GSM.
*/
qapi_Status_t qapi_QT_NW_GSM_Meas_Info_Get(qapi_QT_NW_GSM_Meas_Info_t* meas_info);

/*
@func
  qapi_QT_NW_LTE_Meas_Info_Get
@brief
  This function is used to get information of measurement under LTE. 
@param [out]
  meas_info - Pointer. Used to store information of measurement under LTE.
*/
qapi_Status_t qapi_QT_NW_LTE_Meas_Info_Get(qapi_QT_NW_LTE_Meas_Info_t* meas_info);

/*
@func
  qapi_QT_NW_PSM_Cfg_Set
@brief
  This function is used to set configuration of PSM of UE.
@param [in]
  psm_cfg - Pointer. Used to configure the parameter of PSM.
*/
qapi_Status_t qapi_QT_NW_PSM_Cfg_Set(qapi_QT_NW_Req_PSM_Cfg_t *psm_cfg);

/*
@func
  qapi_QT_NW_PSM_Cfg_Get
@brief
  This function is used to get network allocated parameters of PSM. 
@param [out]
  psm_cfg - Pointer. Used to store the parameters of PSM that allocated by network.
*/
qapi_Status_t qapi_QT_NW_PSM_Cfg_Get(qapi_QT_NW_Alloc_PSM_Cfg_t* psm_cfg);

/*
@func
  qapi_QT_NW_eDRX_Cfg_Set
@brief
  This function is used to set configuration of eDRX of UE. 
@param [in]
  edrx_cfg - Pointer. Used to configure eDRX of UE.
*/
qapi_Status_t qapi_QT_NW_eDRX_Cfg_Set(qapi_QT_NW_Req_eDRX_Cfg_t *edrx_cfg);

/*
@func
  qapi_QT_NW_eDRX_Cfg_Get
@brief
  This function is used to get network allocated parameters of eDRX. 
@param [in]
  rat_mode - Pointer. RAT that needs the eDRX parameters.
@param [out]
  edrx_cfg - Pointer. Store that network allocated parameters of eDRX.
*/
qapi_Status_t qapi_QT_NW_eDRX_Cfg_Get(qapi_QT_NW_RAT_e *rat_mode, qapi_QT_NW_Alloc_eDRX_Cfg_t* edrx_cfg);

/*
@func
  qapi_QT_NW_Lapi_Cfg_Set/qapi_QT_NW_Lapi_Cfg_Get
@brief
  Set/Get Lapi configuration. Reference AT+QCFG="lapiconf"
@param 
 	lapi_mode -
 	0: Forced to disable
 	1: Forced to enable
 	2: LAPI functionality is determined by SIM/EFS
	lapi_enable -
	0: OFF
	1: ON
*/
qapi_Status_t qapi_QT_NW_Lapi_Cfg_Set(qapi_QT_NW_Lapi_Config_Profile_t *lapi_cfg);
qapi_Status_t qapi_QT_NW_Lapi_Cfg_Get(qapi_QT_NW_Lapi_Config_Profile_t *lapi_cfg);

/*
@func
  qapi_QT_NW_NAS_Cfg_Set/qapi_QT_NW_NAS_Cfg_Get
@brief
  Set/Get NAS configuration. Reference AT+QCFG="nasconfig"
@param
 	nas_config_data - Range of values(0-7FFF)
*/
qapi_Status_t qapi_QT_NW_NAS_Cfg_Set(unsigned short* nas_config_data);
qapi_Status_t qapi_QT_NW_NAS_Cfg_Get(unsigned short* nas_config_data);

/*
@func
  qapi_QT_NW_NCC_Cfg_Set/qapi_QT_NW_NCC_Cfg_Get
@brief
  Set/Get NCC configuration. Reference AT+QCFG="nccconf"
@param
 	capability_value - Range of values (0-1FF)
*/
qapi_Status_t qapi_QT_NW_NCC_Cfg_Set(unsigned short* capability_value);
qapi_Status_t qapi_QT_NW_NCC_Cfg_Get(unsigned short* capability_value);

/*
@func
  qapi_QT_NW_FGI_Cfg_Set/qapi_QT_NW_FGI_Cfg_Get
@brief
  Set/Get FGI configuration. Reference AT+QCFG="fgiconfig"
@param
 	capability_value - Range of values (0-FFFFFFFF)
*/
qapi_Status_t qapi_QT_NW_FGI_Cfg_Set(unsigned int* fgi_value);
qapi_Status_t qapi_QT_NW_FGI_Cfg_Get(unsigned int* fgi_value);

/*
@func
  qapi_QT_SIM_RDY_Check
@brief
  To get the state of SIM card
@param [out]
  SIM_state - String indicate the state of SIM card
*/
qapi_Status_t qapi_QT_SIM_RDY_Check(char *SIM_state);

/*
@func
  qapi_QT_SIM_IMSI_Get
@brief
  To get the IMSI of SIM card
@param [out]
  IMSI - The IMSI of SIM card
*/
qapi_Status_t qapi_QT_SIM_IMSI_Get(char *IMSI);

/*
@func
  qapi_QT_SIM_CCID_Get
@brief
  To get the CCID of SIM card
@param [out]
  CCID- The CCID of SIM card
*/
qapi_Status_t qapi_QT_SIM_CCID_Get(char *CCID);

/*
@func
  qapi_QT_SIM_MSISDN_Get
@brief
  To get the MSISDN of SIM card
@param [out]
  MSISDN - The MSISDN of SIM card
*/
qapi_Status_t qapi_QT_SIM_MSISDN_Get(char *MSISDN);

/*
@func
  qapi_QT_SMS_Get_Service_Ready_Status
@brief
  To get the state of SMS service, the state must be ready before operate the SMS
@param [out]
  service_state - The service state of SMS
*/
qapi_Status_t qapi_QT_SMS_Get_Service_Ready_Status(uint16 *service_state);

/*
@func
  qapi_QT_SMS_Message_List
@brief
  To list all the SMS messages
@param [out]
  para - All the SMS messages
*/
qapi_Status_t qapi_QT_SMS_Message_List(qapi_QT_SMS_Message_List_t *para);

/*
@func
  qapi_QT_SMS_Message_Send
@brief
  To send a short message
@param [in]
  send_message - The address and content of SMS to be sent
*/
qapi_Status_t qapi_QT_SMS_Message_Send(qapi_QT_SMS_Message_Content_t *send_message);

/*
@func
  qapi_QT_SMS_Message_Read
@brief
  To read the content of specific SMS
@param [in]
  index - index of the SMS to be read
@param [out]
  msg_info - The content of the specific SMS tobe read
*/
qapi_Status_t qapi_QT_SMS_Message_Read(uint16 index, qapi_QT_SMS_Message_Rcvd_t *msg_info);

/*
@func
  qapi_QT_SMS_Message_Delete
@brief
  To delete the apecific SMS
@param [in]
  index - The index of SMS to be delete
*/
qapi_Status_t qapi_QT_SMS_Message_Delete(uint16 index);

/*
@func
  qapi_QT_SMS_Para_Set/qapi_QT_SMS_Para_Get
@brief
  To set/get the vp/pid/dcs of SMS
@param [in/out]
  sms_para - The vp/pid/dcs of SMS paramater
*/
qapi_Status_t qapi_QT_SMS_Para_Set(qapi_QT_SMS_Para_t *sms_para);
qapi_Status_t qapi_QT_SMS_Para_Get(qapi_QT_SMS_Para_t *sms_para);

/*
@func
  qapi_QT_SMS_CPMS_Set/qapi_QT_SMS_CPMS_Get
@brief
  To set/get the storage of SMS
@param [in]
  sms_cpms - the SMS storage to be set
@param [out]
  sms_cpms_info - the string indicate the storage of SMS
*/
qapi_Status_t qapi_QT_SMS_CPMS_Set(qapi_QT_SMS_CPMS_Set_t *sms_cpms);
qapi_Status_t qapi_QT_SMS_CPMS_Get(char *sms_cpms_info);

/*
@func
  qapi_QT_SMS_Chset_Set/qapi_QT_SMS_Chset_Get
@brief
  To set/get the charset of SMS
@param [in/out]
  cscs_val - The charset of SMS
*/
qapi_Status_t qapi_QT_SMS_Chset_Set(qapi_QT_Chset_Type_e cscs_val);
qapi_Status_t qapi_QT_SMS_Chset_Get(qapi_QT_Chset_Type_e *cscs_val);

/*
@func
  qapi_QT_SMS_Rcvd_Num
@brief
  To get number of received and total SMS
@param [out]
  msg_store_num - The received and totalSMS number
*/
qapi_Status_t qapi_QT_SMS_Rcvd_Num(qapi_QT_SMS_Message_Store_t *msg_store_num);

/*
@func
  qapi_QT_SMS_Message_Status_Get
@brief
  To get the state of specific SMS
@param [in]
  index - The index of specific SMS
@param [out]
  msg_status - The state of the specific SMS
*/
qapi_Status_t qapi_QT_SMS_Message_Status_Get(uint16 index, qapi_QT_SMS_Status_e *msg_status);

/*
@func
  qapi_QT_SMS_CSCA_Set
@brief
  To set the service center address
@param [in]
  sca - The service center address 
  sca_type - The type of service center address
*/
qapi_Status_t qapi_QT_SMS_CSCA_Set(char *sca, qapi_QT_SMS_CSCA_Type_e sca_type);

/*
@func
  qapi_QT_SMS_PDU_Message_Send
@brief
  Send SMS in PDU mode
@param [in]
  message_data - The content of SMS in PDU mode
*/
qapi_Status_t qapi_QT_SMS_PDU_Message_Send(uint8 *message_data);

/*
@func
  qapi_QT_SMS_PDU_Message_Read
@brief
  Read SMS in PDU mode
@param [in]
  index - index of SMS
@param [out]
  message_data - The content of SMS in PDU mode
*/
qapi_Status_t qapi_QT_SMS_PDU_Message_Read(uint8 index, uint8 *message_data);

/*
@func
  qapi_QT_SMS_CSCA_Get
@brief
  To get the service center address
@param [out]
  sca - The service center address 
  sca_type - The type of service center address
*/
qapi_Status_t qapi_QT_SMS_CSCA_Get(char *sca, qapi_QT_SMS_CSCA_Type_e *sca_type);

/*
@func
  qapi_QT_Remove_FOTA_Package
@brief
  Remove FOTA package.
@param
  null
*/
qapi_Status_t qapi_QT_Remove_FOTA_Package(void);

/*
@func
  qapi_QT_FOTA_Download_Start
@param [in]
  url - FOTA package path. for example: HTTP://220.180.239.212:8005/BG95_112A_119.zip. 
  response_cb - response callback, This callback will come when download failed or success.
@brief
  Start FOTA package download.
*/
qapi_Status_t qapi_QT_FOTA_Download_Start(char *url,qapi_QT_FOTA_DL_CB_t response_cb);

/*
@func
  qapi_QT_FOTA_Update_Start
@brief
  Start FOTA Update.
@param
  null
  Note:
    Before use this interface, the delta firmware should be uploded to the flash.
*/
qapi_Status_t qapi_QT_FOTA_Update_Start(void);

/*
@func
  qapi_QT_FOTA_Get_Package_Info
@brief
  Get the DFOTA Package Information.
@param [out]
  dwl_size - Pointer, size of the downloaded file.
  total_size - Pointer, total size of the package file .
*/
qapi_Status_t qapi_QT_FOTA_Get_Package_Info(uint32 *dwl_size, uint32 *total_size);

/*
@func
  qapi_QT_FOTA_Download_Cancel
@brief
  Cancel the current download process.
@param
  null
*/
qapi_Status_t qapi_QT_FOTA_Download_Cancel(void);

/*
@func
  qapi_QT_FOTA_APN_Set
@brief
  Config the APN infomation of FOTA.
@param [out]
	apn_value - APN  infomation
*/
qapi_Status_t qapi_QT_FOTA_APN_Set(qapi_QT_FOTA_APN_Struct_t *apn_value);

/*
@func
  qapi_QT_FOTA_DL_Process
@brief
  Show  fota download progress.
@param [in]
	cb - process callback This callback will come when downloading
*/
qapi_Status_t qapi_QT_FOTA_DL_Process(qapi_QT_FOTA_DL_Process_CB_t cb);

/*
@func
  qapi_QT_Check_FOTA_Package
@brief
  check the CRC value and base version of FOTA package.
@param [out]
  check_res - The check result,please refer to the qapi_QT_FOTA_Package_Check_Result_e for the details
@return One of the following error codes:
  QAPI_QT_ERR_OK  -- OK.
  Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Check_FOTA_Package(qapi_QT_FOTA_Package_Check_Result_e *check_res);

/*
@func
  qapi_QT_NW_Time_Report_Set
@brief
  	This function is used to set the time zone report of changed event.
  	If reporting is enabled, the MT returns the unsolicited result code
  	+CTZV: <tz> or +CTZE: <tz>,<dst>,<time> whenever the time zone is changed.
	The configuration is stored to NVRAM automatically.
@param [in]
  ctzr_value - Pointer, set the mode of the time zone report.
  		0	Disable time zone reporting of changed event
		1	Enable time zone reporting of changed event by unsolicited result code:+CTZV: <tz>
		2	Enable extended time zone reporting of changed event by unsolicited result code:+CTZE: <tz>,<dst>,<time>
*/
qapi_Status_t qapi_QT_NW_Time_Report_Set(uint8* ctzr_value);

/*
@func
  qapi_QT_NW_Time_Report_Get
@brief
  	This function is used to get the time zone report of changed event.
@param [out]
  ctzr_value - Pointer, get the mode of the time zone report.
*/
qapi_Status_t qapi_QT_NW_Time_Report_Get(uint8* ctzr_value);

/*
@func
  qapi_QT_NW_Auto_Time_Update_Set
@brief
  This function is used to set NITZ to enable and disable automatic time zone update.
  The configuration is automatically stored in NVRAM.
@param [in]
  ctzu_value - Pointer, set the mode of automatic time zone update.
  		0	Disable automatic time zone update via NITZ
  		1	Enable automatic time zone update via NITZ
*/
qapi_Status_t qapi_QT_NW_Auto_Time_Update_Set(uint8* ctzu_value);

/*
@func
  qapi_QT_NW_Auto_Time_Update_Get
@brief
  This function is used to get NITZ to enable and disable automatic time zone update.
@param [out]
  ctzu_value - Pointer, get the mode of automatic time zone update.
*/
qapi_Status_t qapi_QT_NW_Auto_Time_Update_Get(uint8* ctzu_value);

/*
@func
  qapi_julian_convert_to_sec
@brief
  This function is used to convert julian time to seconds.
@param [in]
  time_julian - Pointer, store the time in julian format.
@param [out]
  time_sec - converted time in second.
*/
qapi_Status_t qapi_QT_Julian_Convert_To_Sec(qapi_time_get_t *time_julian ,uint32 *time_sec);

/*
@func
  qapi_sec_convert_to_julian
@brief
  This function is used to convert seconds to julian time.
@param [in]
  time_sec - time in sencond.
@param [out]
  time_julian -converted time in julian format.
*/
qapi_Status_t qapi_QT_Sec_Convert_To_Julian(uint32 time_sec,qapi_time_get_t *time_julian);

/*
@func
   qapi_QT_GPS_Jamming_Detection
@brief
  Enable the reporting of jamming detection status
@param[in]
  jammode  qapi_QT_GPS_Jamming_Mode_e, Mode of triggering callback
    		   0: no callback
    		   1: Trigger callback periodically in 1s
    		   2: Trigger when the interference state changes
  jamming_callback  jamming status notification function,
		  typedef void(*qapi_QT_GPS_Jamming_CB_t)(uint8_t jamming_status,uint32_t gpsdata);
	
@param[out]
		QUEC_ERR_OK - no error
		Other error codes -- Failure
*/
qapi_Status_t  qapi_QT_GPS_Jamming_Detection(qapi_QT_GPS_Jamming_Mode_e jammode,qapi_QT_GPS_Jamming_CB_t jamming_callback);

/*
@func
  qapi_QT_Get_Timetick
@brief
  Get the value of timetick.
@param [out]
  timetick - Pointer to get the current time tick  .
@return
  QAPI_QT_ERR_OK  -- OK.
  Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Get_Timetick(unsigned long long *timetick);

/*
@func
  qapi_QT_Time_To_Tick
@brief
  Convert time to tick.
@param [in]
  time - time that need to be converted.
  unit - time unit.  
@param [out]
  tick - pointer that store the converted tick.   
@return
  QAPI_QT_ERR_OK  -- OK.
  Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Time_To_Tick(uint32 time,qapi_QT_Timetick_Unit_e unit, unsigned long long *tick);

/*
@func
  qapi_QT_Tick_To_Time
@brief
  Convert tick(32 bit) to time.
@param [in]
  tick - tick that need to be converted.
  unit - time unit.  
@param [out]
  time - pointer that store the converted time.   
@return
  QAPI_QT_ERR_OK  -- OK.
  Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Tick_To_Time(uint32 tick,qapi_QT_Timetick_Unit_e unit , uint32 *time);

/*
@func
  qapi_QT_Tick_To_Time_V2
@brief
  Convert tick(64 bit) to time.
@param [in]
  tick - tick that need to be converted.
  unit - time unit.  
@param [out]
  time - pointer that store the converted time.   
@return
  QAPI_QT_ERR_OK  -- OK.
  Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Tick_To_Time_V2(unsigned long long* tick,qapi_QT_Timetick_Unit_e unit , uint32 *time);

/*
@func
  qapi_QT_URC_Port_Set.
@brief
  Set the port reported by URC.
@param[in]
  port :Port where urc messages are reported.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_URC_Port_Set(qapi_QT_URC_Port_e port);

/*
@func
  qapi_QT_URC_Port_Get.
@brief
  Get the port information reported by URC.
@param[out]
  port :Pointer,port information where urc messages are reported.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_URC_Port_Get(qapi_QT_URC_Port_e* port);

/*
@func
  qapi_QT_GPS_Delete_Assistance_Data
@brief
  This function is used to delet assistance data so as to operate cold start, hot start and warm start of GNSS.
@param[in]
  gnss_startup_mode - The type of GNSS assistance data to be deleted.
       0:Delete all assistance data include XTRA data. Enforce cold start after starting GNSS.
       1:Do not delete any data. Perform hot start if the conditions are permitted after starting GNSS.
       2:Delete some related data. Perform warm start if the conditions are permitted after starting GNSS.
*/
qapi_Status_t qapi_QT_GPS_Delete_Assistance_Data(uint8_t gnss_startup_mode);

/*
@func
  qapi_QT_GPS_Query_XTRA_Data
@brief
  This function is used to query the status of XTRA file.
@param[out]
  xtra_time_data 
        nYear	    - Valid time of injected XTRA file. Unit: min.
		nMonth
		nDay
		nHour
		nMin
		nSec
		duration_time  -Starting time of the valid time of XTRA file.
*/
qapi_Status_t qapi_QT_GPS_Query_XTRA_Data(qapi_QT_XTRA_Time_Data_t* xtra_time_data);

/*
@func
  qapi_QT_GPS_Inject_XTRA_Data
@brief
  This function is used to Inject XTRA file.
@param[in]
    xtra_data - String type. Filename of the XTRA file, e.g. "UFS: xtra3gr.bin" or "EUFS:xtra3gr.bin".
				The XTRA file need to be downloaded by customer and save it to /ufs/ in AP or modem side.
*/
qapi_Status_t qapi_QT_GPS_Inject_XTRA_Data(char *xtra_data);

/*
@func
  qapi_QT_GPS_XTRA_Download
@brief
  This function is used to trigger XTRA File Downloading.
@param[out]
*/
qapi_Status_t qapi_QT_GPS_XTRA_Download(void);

/*
@func
  qapi_QT_Open_FOTA_Partition.
@brief
  Open FOTA partition
@param[out]
   handle: This is the handle that will be passed to client for further usage   
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Open_FOTA_Partition(qapi_QT_Flash_FOTA_t* handle);

/*
@func
  qapi_QT_Close_FOTA_Partition.
@brief
  Close FOTA partition
@param[out]
   handle: handle of the partition to be closed   
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Close_FOTA_Partition (qapi_QT_Flash_FOTA_t* handle);

/*
@func
  qapi_QT_Get_FOTA_Partition_Size.
@brief
  Get FOTA partition size.
@param[in]
  handle: FLASH handle. the same handle returned from qapi_QT_Open_Fota_Partiton.
@param[out]
  size: FOTA partition size for saving delta package. Unit : byte
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Get_FOTA_Partition_Size(qapi_QT_Flash_FOTA_t handle, uint32* size);

/*
@func
  qapi_QT_Erase_FOTA_Partition.
@brief
  Erase entire FOTA partition.
@param[in]
  handle: FLASH handle. the same handle returned from qapi_QT_Open_Fota_Partiton.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Erase_FOTA_Partition(qapi_QT_Flash_FOTA_t handle);

/*
@func
  qapi_QT_Malloc_For_FOTA_Partition_Write.
@brief
  Malloc for  FOTA partition write .
@param[in]
  buff: buffer used for FOTA partition write. 
  size:The buffer size must be 256KB.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Malloc_For_FOTA_Partition_Write(uint8* buff, uint32 size);

/*
@func
  qapi_QT_FOTA_Partiton_Write_data
@brief
  Write delta package in FOTA partition. Only for saving FOTA package.
@param[in]
  handle: FLASH handle. the same handle returned from qapi_QT_Open_Fota_Partiton
  offset : the offset of write address, range: [0, FOTA_partition_size -1], FOTA_partition_size is got via qapi_QT_Get_Fota_Partition_Size 
  buff : write data buffer
  size : write data buffer size, suggest to be an integral multiple of 128KB
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_FOTA_Partiton_Write_Data(qapi_QT_Flash_FOTA_t handle, uint32 offset, uint8 *buff, uint32 size);

/*
@func
  qapi_QT_FOTA_Partiton_Read_Data.
@brief 
  Read  delta package in FOTA partition.
@param[in]
  handle: FLASH handle. the same handle returned from qapi_QT_Open_Fota_Partiton
  offset:  the offset of read address, range: [0, FOTA_partition_size -1], FOTA_partition_size is got via qapi_QT_Get_Fota_Partition_Size 
  buff : read data buffer
  size : read data buffer
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_FOTA_Partiton_Read_Data(qapi_QT_Flash_FOTA_t handle, uint32 offset, uint8 *buff, uint32 size);

/*
@func
  qapi_QT_JAMDET_Enable_Set
@brief
  Enable/disable Jamming detection
@param [in]
  jamdet_enable,  qapi_QT_NW_Jamming_Detection_Mode_e
  jamdet_cb,      bring back the jamming state
                  callback function, enable jamming dection will register the callback, disable jamming detection will deregister the callback
*/
qapi_Status_t qapi_QT_NW_Jamming_Detection_Mode_Set(qapi_QT_NW_Jamming_Detection_Mode_e jamdet_mode, qapi_QT_NW_Jamming_State_CB_t jamdet_cb);

/*
@func
  qapi_QT_JAMDET_Enable_Get
@brief
  Get the jamming detection status
@param [out]
  jamdet_enable,  qapi_QT_NW_Jamming_Detection_Mode_e
  jamstate,    string, jamming state
*/
qapi_Status_t qapi_QT_NW_Jamming_Detection_Mode_Get(qapi_QT_NW_Jamming_Detection_Mode_e *jamdet_mode, char *jamstate);

/*
@func
  qapi_QT_JAMDET_CFG_Set
@brief
  Set Jamming detection config
@param [in]
jamdet_cfg, Jamming detection config
*/
qapi_Status_t qapi_QT_NW_Jamming_Detection_CFG_Set(qapi_QT_NW_Jamming_Detection_CFG_t *jamdet_cfg);

/*
@func
  Get Jamming detection config
@brief
  Enable/disable Jamming detection
@param [out]
jamdet_cfg, Jamming detection config
*/
qapi_Status_t qapi_QT_NW_Jamming_Detection_CFG_Get(qapi_QT_NW_Jamming_Detection_CFG_t *jamdet_cfg);

/* 
@func
  qapi_QT_SPIM_MultiCS_Set
@brief
  This function is used to set multi cs gpio open enable.
@param [in]
[multi_cs]  cs bit value for setting, bit_n=1, enable cs_n, n=1/2/3
            bit1-cs1, pin GPIO_0, multiplex to DEBUG_TXD
            bit2-cs2, pin GPIO_1, multiplex to DEBUG_RXD
            bit3-cs3, pin GPIO_2, multiplex to I2C_SDA
[instance]  spi instance, only for QT_QAPI_SPIM_PORT_02
*/
qapi_Status_t qapi_QT_SPIM_MultiCS_Set(uint8 multi_cs, qapi_SPIM_Instance_t instance);

/* 
@func
  qapi_QT_SPIM_MultiCS_Get
@brief
  This function is used to get multi cs gpio open enable.
@param [in]
[instance]  spi instance, only for QT_QAPI_SPIM_PORT_02
@param [out]
[multi_cs]  cs bit value for setting, bit_n=1, enable cs_n, n=0/1/2/3
            bit1-cs1, pin GPIO_0, multiplex to DEBUG_TXD
            bit2-cs2, pin GPIO_1, multiplex to DEBUG_RXD
            bit3-cs3, pin GPIO_2, multiplex to I2C_SDA
*/
qapi_Status_t qapi_QT_SPIM_MultiCS_Get(uint8 *multi_cs, qapi_SPIM_Instance_t instance);

/*
@func
  qapi_QT_DAM_CFG_Partition_Write.
@brief
  Write data to DAM CFG partition.
@param[in]
  data :Need to be written to the flash buffer. 
@param[in]
  len :Length of data written. 
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_DAM_CFG_Partition_Write(void *data, int len);

/*
@func
  qapi_QT_DAM_CFG_Partition_Read.
@brief
  Read data from DAM CFG partition.
@param[out]
  data :Need to be read from the flash buffer. 
@param[in]
  len :Length of data read. 
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_DAM_CFG_Partition_Read(void *data, int len);

/*
@func
  qapi_QT_DAM_CFG_Partition_Erase.
@brief
  Eraser all data from DAM CFG partition.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_DAM_CFG_Partition_Erase(void);

/*
@func
  qapi_QT_Get_SecBoot_Status.
@brief
  Get the module secureboot enabled status.
@param[out]
  sec_status :Pointer,the module SecureBoot status.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Get_SecBoot_Status(qapi_QT_SecBoot_Status_e* sec_status);

/*
@func
  qapi_QT_Get_Rand
@brief
  Get a Random value .
@param[out]
  rand:Pointer , get a random value  .
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Get_Rand(uint32 *rand);

/* 
@func
  qapi_QT_SMS_Message_Send_CB_Set
@brief
  This function is used to get sms send state
@param [in]
[sms_send_state_cb]  sms send state callback
*/
qapi_Status_t qapi_QT_SMS_Message_Send_CB_Set(qapi_QT_SMS_Message_Send_State_CB_t sms_send_state_cb);

/*
@func
  qapi_QT_Chip_Serial_Num_Get
@brief
  Get the chip serial number by qapi_QT_Chip_Serial_Num_Get.
@param [out]
  Pointer, pointer to the chip serial number. 
*/
qapi_Status_t qapi_QT_Chip_Serial_Num_Get(uint32 *serial_num);

/*
@func
  qapi_QT_EFS_Backup
@brief
  Backup Modem or APP file system .
@param[in]
  efs_region: which file system backup.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_EFS_Backup(qapi_QT_EFS_Backup_Partition_Type_e efs_region);

/*
@func
  qapi_QT_EFS_Backup_Info_Get
@brief
  Get Modem or APP file system info.
@param[in]
  efs_region: which file system info get.
@param[out]
  info: Pointer, get file system info. 
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_EFS_Backup_Info_Get(qapi_QT_EFS_Backup_Partition_Type_e efs_region, qapi_QT_EFS_Backup_Info_t* info);

/*
@func
  qapi_QT_RTC_Alarm_Time_Get
@brief
  This function is used to get the scheduled startup time and the remain time of RTC alarm .
@param [out]
  [time_ptr]  ->set_time :    Get the time interval from now to the next start up of the schedule set by "qapi_QT_RTC_Alarm_time_Set".
              ->remain_time : After <remain_time>, the module will startup automatically. 
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.     
*/
qapi_Status_t qapi_QT_RTC_Alarm_Time_Get(qapi_QT_RTC_Alarm_Time_Type_t *time_ptr);

/*
@func
  qapi_QT_RTC_Alarm_Time_Set
@brief
  This function is used to set the time interval between now and the next startup plan.
@param [in]
  set_time  :set the time interval between now and the next scheduled startup,in seconds.   
            If <set_time > is 0, RTC alarm will be disabled.
  		    Note��	1. If the module is resetted before reaching the scheduled startup time that you set, RTC alarm will be disabled.
     				2. If the module is shutdown after reaching the scheduled startup time, it will startup immediately.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.            
*/
qapi_Status_t qapi_QT_RTC_Alarm_Time_Set(uint32_t *set_time);

/*
@func
  qapi_QT_APPS_OS_Version_Get
@brief
  This function is used to get the APPs OS kernel version. 
@param [out]
  ver_str : Pointer to buffer of string the APPS OS kernel version. 
@param [in]
  str_len : size of the buffer of string of APPS OS kernel version, not less than 64 bytes. 
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.            
*/
qapi_Status_t qapi_QT_APPS_OS_Version_Get(uint8_t *ver_str, uint8_t str_len);

/*
@func
  qapi_QT_UART_TX_Transmit_State_Get
@brief
  This function is used to query whether the data in UART_TX has been sent.
@param [in]
  id : UART port ID. 
@param [out]
  tx_status : Pointer to tx transmit state. 
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.            
*/
qapi_Status_t qapi_QT_UART_TX_Transmit_State_Get(qapi_UART_Port_Id_e id, uint8* tx_status);


/*
@func
  qapi_QT_FOTA_WD_CFG_Get.
@brief
  Get the configuration of fota watch dog.
@param[out]
  WD_info :Pointer,the configuration of fota watch dog.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_FOTA_WD_CFG_Get(qapi_QT_FOTA_WD_CFG_t *WD_info);

/*
@func
  qapi_QT_FOTA_WD_CFG_Set.
@brief
  Set the configuration fota watch dog.
@param[out]
  WD_info :Pointer,the configuration of fota watch dog.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_FOTA_WD_CFG_Set(qapi_QT_FOTA_WD_CFG_t* WD_info);

/*
@func
  qapi_QT_MP_AP_Interaction
@brief
  Register a callback to monitor MP running status, with specified timer period.
@param [in]
  duration  timer period
  cb		callback function
*/
qapi_Status_t qapi_QT_MP_AP_Interaction_Reg(uint32 duration, qapi_QT_MP_AP_Interaction_CB cb);

/*
@func
  qapi_QT_PMIC_WD_Kick
@brief
  Kick PMIC Watch Dog
@note
  The QAPI introduces the PMIC WD(watch dog) scheme, but it can't replace external WD;
  PMIC WD can make module automatically reboot when abnormal problems occur, such as modem MP or QuecOpen App crashed but the AP kernel doesn��t detect this problem;
  
  Based on PMIC internal timer, AP kernel setup an internal mechanism(PMIC WD) to monitor module status. 
  Within the module, communication is maintained between AP and MP to confirm the status of MP, 
  while communication is maintained between AP and QuecOpen App to monitor the running status of customer DAM application if this QAPI is called. 
  If any communication exception takes longer than expected, the module is considered to have an exception and PMIC WD will trigger a reset operation.
*/
qapi_Status_t qapi_QT_PMIC_WD_Kick(void);

/*
@func
  qapi_QT_Thread_Info_Get.
@brief
  Get information about the specified thread.
@param[in]
  thread_ptr: Pointer to thread handle.
  thread_info->name_len: Parameter name allocated space size.
@param[out]
  thread_info
    Other parameters.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Thread_Info_Get(TX_THREAD *thread_ptr, qapi_QT_Thread_Info_t *thread_info);

/*
@func
  qapi_QT_Byte_Pool_Info_get.
@brief
  Get information about the specified pool.
@param[in]
  pool_ptr: Pointer to byte pool handle.
  pool_info->name_len: Parameter name allocated space size.
@param[out]
  pool_info
    Other parameters.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Byte_Pool_Info_get(TX_BYTE_POOL *pool_ptr, qapi_QT_Byte_Pool_Info_t *pool_info);

/*
@func
  qapi_QT_Event_Flags_Info_Get.
@brief
  Get information about the specified event flags.
@param[in]
  group_ptr: Pointer to event flag group handle.
  event_flags_info->name_len:  Parameter name allocated space size.
@param[out]
  event_flags_info
    Other parameters.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Event_Flags_Info_Get(TX_EVENT_FLAGS_GROUP *group_ptr, qapi_QT_Event_Flags_Info_t *event_flags_info);

/*
@func
  qapi_QT_Queue_Info_Get.
@brief
  Get information about the specified queue.
@param[in]
  queue_ptr: Pointer to queue handle.
  queue_info->name_len: Parameter name allocated space size.
@param[out]
  queue_info
    Other parameters.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Queue_Info_Get(TX_QUEUE *queue_ptr, qapi_QT_Queue_Info_t *queue_info);

/*
@func
  qapi_QT_Semaphore_Info_Get.
@brief
  Get information about the specified semaphore.
@param[in]
  semaphore_ptr: Pointer to semaphore handle.
  semaphore_info->name_len: Parameter name allocated space size.
@param[out]
  semaphore_info
    Other parameters.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Semaphore_Info_Get(TX_SEMAPHORE *semaphore_ptr, qapi_QT_Semaphore_Info_t *semaphore_info);

/*
@func
  qapi_QT_Mutex_Info_Get.
@brief
  Get information about the specified mutex.
@param[in]
  mutex_ptr: Pointer to mutex handle.
  mutex_info->name_len: Parameter name allocated space size.
@param[out]
  mutex_info
    Other parameters.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Mutex_Info_Get(TX_MUTEX *mutex_ptr, qapi_QT_Mutex_Info_t *mutex_info);

/*
@func
  qapi_QT_DAM_Crash_Mode_Set.
@brief
  Set the DAM crash mode.
@param[in]
  crash_mode : Set the DAM crash mode.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_DAM_Crash_Mode_Set(qapi_QT_DAM_Crash_Mode_e crash_mode);

/*
@func
  qapi_QT_DAM_Crash_Mode_Get.
@brief
  Get the DAM crash mode.
@param[out]
  crash_mode : Pointer. Point to DAM crash mode.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_DAM_Crash_Mode_Get(qapi_QT_DAM_Crash_Mode_e *crash_mode);

/*
@func
  qapi_QT_DAM_Crash_Info_Get.
@brief
  Get the DAM crash information.
@param[out]
  crash_info : Structure pointer. Point to DAM crash information.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_DAM_Crash_Info_Get(qapi_QT_DAM_Crash_Info_t *crash_info);

/*
@func
  qapi_QT_DAM_Crash_Info_Delete.
@brief
  Delete the DAM crash information.
@param[out]
  None.
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_DAM_Crash_Info_Delete(void);

/*
@func
  qapi_QT_Thread_Stack_Info_Get
@brief
  Get the current stack information of the thread.
@param [in]
  thread_ptr: Handle to the query thread
@param [out]
  thread_stack_info: Thread stack information obtained 
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_Thread_Stack_Info_Get(TX_THREAD* thread_Ptr, qapi_QT_Stack_Info_t *thread_stack_info);

/*
@func
  qapi_QT_NW_RRC_State_Set.
@brief
  set  rrc state report enable or disable.
@param[out]
  rrc_report_mode   rrc_cb
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_NW_RRC_State_Set(qapi_QT_NW_RRC_State_Report_Mode_e rrc_report_mode, qapi_QT_NW_RRC_State_CB_t rrc_cb);
/*
@func
  qapi_QT_NW_RRC_State_Get.
@brief
  Get information about rrc state report config and current status.
@param[out]
  rrc_report_mode  rrc_state
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/

qapi_Status_t qapi_QT_NW_RRC_State_Get(qapi_QT_NW_RRC_State_Report_Mode_e* rrc_report_mode, qapi_QT_NW_RRC_State_e* rrc_state);


/*
@func
  qapi_QT_NW_Camped_Network_RAT_Get.
@brief
  Get information about camp network rat .
@param[out]
  camp_rat
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_NW_Camped_Network_RAT_Get(qapi_QT_NW_RAT_e *camped_rat);

/*
@func
  qapi_QT_NW_GSM_NeighbourCell_Info_Get.
@brief
  Get information about gsm neighbourcell info.
@param[out]
  gsm_neighbourcell_info
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_NW_GSM_NeighbourCell_Info_Get(qapi_QT_NW_GSM_Neighbourcell_Info_t *gsm_neighbourcell_info);

/*
@func
  qapi_QT_NW_LTE_NeighbourCell_Info_Get.
@brief
  Get information about lte neighbourcell info.
@param[out]
  lte_neighbourcell_info
@return One of the following error codes:
  		QAPI_QT_ERR_OK  -- OK.
  		Other error codes -- Failure.
*/
qapi_Status_t qapi_QT_NW_LTE_NeighbourCell_Info_Get(qapi_QT_NW_LTE_Neighbourcell_Info_t *lte_neighbourcell_info);

#endif /* QAPI_TXM_MODULE */

#endif /*__QAPI_QUECTEL_H__*/

