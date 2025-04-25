#ifndef QAPI_TXM_BASE_H
#define QAPI_TXM_BASE_H 

/**
  @file qapi_txm_base.h 

 EXTERNALIZED FUNCTIONS
  none

 INITIALIZATION AND SEQUENCING REQUIREMENTS
  none

 Copyright (c) 2017-2020  by Qualcomm Technologies, Inc.  All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 ======================================================================*/
/*======================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *   
 *   This file contains QAPI/ThreadX modules Driver ID mappings
 *
 *
 * when         who     what, where, why
 * ----------   ---     ------------------------------------------------
 * 2017-01-20   c_sbegum  Add Header file, with initial QAPI TXM defines
 ======================================================================*/
 

#ifdef __cplusplus
extern "C" {
#endif

#include "txm_module.h"

/* this is used when no extra arguments need to be passed through kernel dispatcher*/
#define QAPI_NULL_EXTRA_ARG	0x4E415247

/* Callback ID which is currently unused for most of the TX CBs is
 being used to pass custom arguments to existing TXM function */
#define CB_CONFIG_ID_QC	0x51434342	// ASCII equivallent to QC CB

#define  TXM_QAPI_ID_START                        TXM_APPLICATION_REQUEST_ID_BASE
// this can be discussed for a proper name
#define  TXM_QAPI_ID_END                          TXM_QAPI_ID_START + TXM_QAPI_MAX_NUM_IDS

// *NOT TO BE CHANGED* or else it may impact system functionality
// API ID base and limit definitions for OEM APIs
#define  TXM_QC_OEM_API_BASE		TXM_APPLICATION_REQUEST_ID_BASE + 0x10000
#define  TXM_QC_OEM_API_MAX_IDS		0x10000
#define  TXM_QC_OEM_API_END			TXM_QC_OEM_API_BASE + TXM_QC_OEM_API_MAX_IDS
// OEM API ID base and limit definition ends

/*** DO NOT MODIFY anything above this line ***/

#define  TXM_QAPI_MAX_NUM_IDS                     (TXM_QAPI_LOCATION_NUM_IDS + \
                                                   TXM_QAPI_QCCI_NUM_IDS + \
                                                   TXM_QAPI_DIAG_NUM_IDS + \
                                                   TXM_QAPI_TIMERS_NUM_IDS + \
                                                   TXM_QAPI_FS_NUM_IDS + \
                                                   TXM_QAPI_TLMM_NUM_IDS + \
                                                   TXM_QAPI_PWM_NUM_IDS + \
                                                   TXM_QAPI_GPIO_INT_NUM_IDS + \
                                                   TXM_QAPI_ADC_NUM_IDS + \
                                                   TXM_QAPI_TSENS_NUM_IDS + \
                                                   TXM_QAPI_DATA_SERVICES_NUM_IDS + \
                                                   TXM_QAPI_BUSES_NUM_IDS + \
                                                   TXM_QAPI_FTL_NUM_IDS + \
                                                   TXM_QAPI_USB_NUM_IDS + \
                                                   TXM_QAPI_RIL_NUM_IDS + \
                                                   TXM_QAPI_PM_RTC_NUM_IDS + \
												   TXM_QAPI_PM_VBATT_NUM_IDS + \
                                                   TXM_QURT_TIMETICK_NUM_IDS + \
                                                   TXM_QAPI_QSEECOM_NUM_IDS + \
                                                   TXM_QAPI_QTEE_INVOKE_NUM_IDS + \
                                                   TXM_QAPI_QWESD_NUM_IDS + \
                                                   CUSTOM_CB_QAPI_EXAMPLE_BASE_num_IDs) // To be removed - TBR

#define  TXM_QAPI_LOCATION_BASE                   TXM_QAPI_ID_START
#define  TXM_QAPI_LOCATION_NUM_IDS                50

#define  TXM_QAPI_QCCI_BASE                       (TXM_QAPI_LOCATION_BASE + TXM_QAPI_LOCATION_NUM_IDS)
#define  TXM_QAPI_QCCI_NUM_IDS                    100

#define  TXM_QAPI_DIAG_BASE                       (TXM_QAPI_QCCI_BASE + TXM_QAPI_QCCI_NUM_IDS)
#define  TXM_QAPI_DIAG_NUM_IDS                    100

#define  TXM_QAPI_TIMERS_BASE                     (TXM_QAPI_DIAG_BASE + TXM_QAPI_DIAG_NUM_IDS)
#define  TXM_QAPI_TIMERS_NUM_IDS                  50

#define  TXM_QAPI_FS_BASE                         (TXM_QAPI_TIMERS_BASE + TXM_QAPI_TIMERS_NUM_IDS)
#define  TXM_QAPI_FS_NUM_IDS                      100

#define  TXM_QAPI_TLMM_BASE                       (TXM_QAPI_FS_BASE + TXM_QAPI_FS_NUM_IDS)
#define  TXM_QAPI_TLMM_NUM_IDS                    50

#define  TXM_QAPI_GPIO_INT_BASE                   (TXM_QAPI_TLMM_BASE + TXM_QAPI_TLMM_NUM_IDS)
#define  TXM_QAPI_GPIO_INT_NUM_IDS                50

#define  TXM_QAPI_ADC_BASE                        (TXM_QAPI_GPIO_INT_BASE + TXM_QAPI_GPIO_INT_NUM_IDS)
#define  TXM_QAPI_ADC_NUM_IDS                     50

#define  TXM_QAPI_TSENS_BASE                      (TXM_QAPI_ADC_BASE + TXM_QAPI_ADC_NUM_IDS)
#define  TXM_QAPI_TSENS_NUM_IDS                   50

#define  TXM_QAPI_DATA_SERVICES_BASE              (TXM_QAPI_TSENS_BASE + TXM_QAPI_TSENS_NUM_IDS)
#define  TXM_QAPI_DATA_SERVICES_NUM_IDS           300

#define  TXM_QAPI_BUSES_BASE                      (TXM_QAPI_DATA_SERVICES_BASE + TXM_QAPI_DATA_SERVICES_NUM_IDS)
#define  TXM_QAPI_BUSES_NUM_IDS                   100

#define  TXM_QAPI_FTL_BASE                        (TXM_QAPI_BUSES_BASE + TXM_QAPI_BUSES_NUM_IDS)
#define  TXM_QAPI_FTL_NUM_IDS                     25

#define  TXM_QAPI_USB_BASE                        (TXM_QAPI_FTL_BASE + TXM_QAPI_FTL_NUM_IDS)
#define  TXM_QAPI_USB_NUM_IDS                     25

#define  TXM_QAPI_RIL_BASE                        (TXM_QAPI_USB_BASE + TXM_QAPI_USB_NUM_IDS)
#define  TXM_QAPI_RIL_NUM_IDS                     50

#define  TXM_QAPI_PM_RTC_BASE                     (TXM_QAPI_RIL_BASE + TXM_QAPI_RIL_NUM_IDS)
#define  TXM_QAPI_PM_RTC_NUM_IDS                  10

#define  TXM_QAPI_PM_VBATT_BASE                   (TXM_QAPI_PM_RTC_BASE + TXM_QAPI_PM_RTC_NUM_IDS)
#define  TXM_QAPI_PM_VBATT_NUM_IDS                15

#define  TXM_QURT_TIMETICK_BASE                   (TXM_QAPI_PM_VBATT_BASE + TXM_QAPI_PM_VBATT_NUM_IDS)
#define  TXM_QURT_TIMETICK_NUM_IDS                10

#define  TXM_QAPI_QSEECOM_BASE                     (TXM_QURT_TIMETICK_BASE + TXM_QURT_TIMETICK_NUM_IDS)
#define  TXM_QAPI_QSEECOM_NUM_IDS                  20

#define  TXM_QAPI_QTEE_INVOKE_BASE                (TXM_QAPI_QSEECOM_BASE + TXM_QAPI_QSEECOM_NUM_IDS)
#define  TXM_QAPI_QTEE_INVOKE_NUM_IDS             10

#define  TXM_QAPI_QWESD_BASE                      (TXM_QAPI_QTEE_INVOKE_BASE + TXM_QAPI_QTEE_INVOKE_NUM_IDS)
#define  TXM_QAPI_QWESD_NUM_IDS                   30

#define  TXM_QAPI_PWM_BASE                        (TXM_QAPI_QWESD_BASE + TXM_QAPI_QWESD_NUM_IDS)
#define  TXM_QAPI_PWM_NUM_IDS                     50


// @@@@@@@@@@ Added to test custom cb notification fwk.To be removed later.
#define CUSTOM_CB_QAPI_EXAMPLE_BASE			(TXM_QAPI_PWM_BASE + TXM_QAPI_PWM_NUM_IDS)
#define CUSTOM_CB_QAPI_EXAMPLE_BASE_num_IDs	10
#define CUSTOM_CB_QAPI_EXAMPLE1			CUSTOM_CB_QAPI_EXAMPLE_BASE
#define CUSTOM_OEM_CB_QAPI_EXAMPLE2		CUSTOM_CB_QAPI_EXAMPLE_BASE + 1
#define CUSTOM_CB_QAPI_EXAMPLE3			CUSTOM_CB_QAPI_EXAMPLE_BASE + 2
#define CUSTOM_CB_QAPI_EXAMPLE4			CUSTOM_CB_QAPI_EXAMPLE_BASE + 3
// @@@@@@@@@@

/* Defines for QC custom callback base and limit ---- */
#define TXM_QC_CUSTOM_CALLBACK_ID_BASE		32
#define TXM_QC_CUSTOM_CALLBACK_ID_MAX	    2000 - 1 // Set the limit as 2000 for now

/* QC Custom callback IDs allocation ------- */
#define CUSTOM_CB_QAPI_LOCATION_BASE			  (TXM_QC_CUSTOM_CALLBACK_ID_BASE + CUSTOM_CB_QAPI_EXAMPLE_BASE_num_IDs)		
#define CUSTOM_CB_QAPI_LOCATION_NUM_IDS			  10

#define CUSTOM_CB_QAPI_GPIO_BASE				  (CUSTOM_CB_QAPI_LOCATION_BASE + CUSTOM_CB_QAPI_LOCATION_NUM_IDS)
#define CUSTOM_CB_QAPI_GPIO_INT_NUM_IDS			  5

#define CUSTOM_CB_QAPI_ADC_BASE				  	  (CUSTOM_CB_QAPI_GPIO_BASE + CUSTOM_CB_QAPI_GPIO_INT_NUM_IDS)
#define CUSTOM_CB_QAPI_ADC_NUM_IDS			      5

#define CUSTOM_CB_QAPI_TSENS_BASE				  (CUSTOM_CB_QAPI_ADC_BASE + CUSTOM_CB_QAPI_ADC_NUM_IDS)
#define CUSTOM_CB_QAPI_TSENS_NUM_IDS			  5

#define CUSTOM_CB_QAPI_USB_BASE				  	  (CUSTOM_CB_QAPI_TSENS_BASE + CUSTOM_CB_QAPI_TSENS_NUM_IDS)
#define CUSTOM_CB_QAPI_USB_NUM_IDS			  	  5

#define CUSTOM_CB_QAPI_DATA_SERVICES_BASE		  (CUSTOM_CB_QAPI_USB_BASE + CUSTOM_CB_QAPI_USB_NUM_IDS)
#define CUSTOM_CB_QAPI_DATA_SERVICES_NUM_IDS	  20

#define CUSTOM_CB_QAPI_BUSES_BASE				  (CUSTOM_CB_QAPI_DATA_SERVICES_BASE + CUSTOM_CB_QAPI_DATA_SERVICES_NUM_IDS)
#define CUSTOM_CB_QAPI_BUSES_NUM_IDS			  10

#define CUSTOM_CB_QAPI_DIAG_BASE                  (CUSTOM_CB_QAPI_BUSES_BASE + CUSTOM_CB_QAPI_BUSES_NUM_IDS)
#define CUSTOM_CB_QAPI_DIAG_NUM_IDS               5

#define CUSTOM_CB_QAPI_RIL_BASE                   (CUSTOM_CB_QAPI_DIAG_BASE + CUSTOM_CB_QAPI_DIAG_NUM_IDS)
#define CUSTOM_CB_QAPI_RIL_NUM_IDS                5

#define CUSTOM_CB_QAPI_QWES_BASE                  (CUSTOM_CB_QAPI_RIL_BASE + CUSTOM_CB_QAPI_RIL_NUM_IDS)
#define CUSTOM_CB_QAPI_QWES_NUM_IDS               5

#define CUSTOM_CB_QAPI_LOCATION_EXT_BASE          (CUSTOM_CB_QAPI_QWES_BASE + CUSTOM_CB_QAPI_QWES_NUM_IDS)          
#define CUSTOM_CB_QAPI_LOCATION_EXT_NUM_IDS       5

/* QC Custom callback IDs allocation END ---- */

/* Defines for QC OEM custom callback base and limit ---- */
#define TXM_QC_OEM_CALLBACK_ID_BASE		10000
#define TXM_QC_OEM_CALLBACK_ID_MAX	    TXM_QC_OEM_CALLBACK_ID_BASE + 2000 - 1
/* QC OEM Custom callback IDs allocation END ---- */

/*Quectel modify*/
#define CUSTOM_CB_QAPI_RSERVED_NUM_IDS       	  28

/* Quectel's QAPIs callback IDs allocation  ------- */
#define CUSTOM_CB_QAPI_QUECTEL_API_BASE           (TXM_QC_OEM_CALLBACK_ID_BASE + CUSTOM_CB_QAPI_RSERVED_NUM_IDS)
#define CUSTOM_CB_QAPI_QUECTEL_API_NUM_IDS        50
/* Quectel's QAPIs callback IDs allocation END ------- */

/*Quectel callback id define*/
#define ATC_PIPE_PORT0_CB					(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 0)
#define ATC_PIPE_PORT1_CB					(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 1)
#define ATC_PIPE_PORT2_CB					(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 2)
#define ATC_PIPE_PORT3_CB					(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 3)
#define FOTA_DL_RESP_CB						(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 4)
#define FOTA_DL_PROCESS_RESP_CB				(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 5)
#define ATC_USB_PORT_CB						(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 6)
#define ATC_REPORT_URC_PORT_CB				(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 7)  
#define FTP_CUSTOM_SESS_CB					(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 8)
#define GNSS_GPS_JAMMING_CB					(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 9)
#define JAMDET_STATE_CB                     (CUSTOM_CB_QAPI_QUECTEL_API_BASE + 10)
#define SMS_SEND_STATE_CB                   (CUSTOM_CB_QAPI_QUECTEL_API_BASE + 11)
#define RRC_STATE_CB                    	(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 12)
#define ATC_MP_AP_WD_CB						(CUSTOM_CB_QAPI_QUECTEL_API_BASE + 13)

/* Function pointer typdef for custom callback user space dispatcher
   Function pointed to, by this function pointer is responsible to invoke
   actual user/app callback after doing required typecasting */
typedef UINT (* pFn_app_cb_dispatcher_t)(	UINT cb_type, void *app_cb, 
										UINT param1, UINT param2,
										UINT param3, UINT param4,
										UINT param5, UINT param6,
										UINT param7, UINT param8);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif /* QAPI_TXM_BASE_H */
