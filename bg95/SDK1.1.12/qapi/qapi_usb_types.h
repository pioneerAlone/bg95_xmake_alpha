/*==================================================================================================
Copyright (c) 2016-2019 Qualcomm Technologies, Inc.
All Rights Reserved.  Confidential and Proprietary - Qualcomm Technologies, Inc.
==================================================================================================*/

 /*===========================================================================

						 EDIT HISTORY FOR MODULE

   This section contains comments describing changes made to the module.
   Notice that changes are listed in reverse chronological order.

 when         who   what, where, why
 ----------   ---   ---------------------------------------------------------
 2018-04-27   leo   (Tech Comm) Edited/added Doxygen comments and markup.
 2017-04-24   leo   (Tech Comm) Edited/added Doxygen comments and markup.
 2017-02-22   ak    Initial Version

 ===========================================================================*/

/**
 * @file qapi_usb_types.h
 *
 * @brief Type definitions for USB QAPIs.
 *
 */

#ifndef QAPI_USB_TYPES_H
#define QAPI_USB_TYPES_H

#include "qapi_txm_base.h"
#include "qapi_status.h"

/*==============================================================================
                              MACROS
=============================================================================*/

/* QAPI USB Macros */
 
/* Error Macros defined for QAPI errors */
 
#define ___QAPI_ERROR(x)  ((qapi_Status_t)(__QAPI_ERROR(QAPI_MOD_BSP_USB,  x)))

/* The action is already done. */
#define QAPI_ERR_ALREADY_DONE     ___QAPI_ERROR(1)

/* No data is available. */
#define QAPI_ERR_NO_DATA          ___QAPI_ERROR(2)

/** @addtogroup qapi_usb_types
@{ */

/*======================================================================
                          TYPEDEFS
 ======================================================================*/

typedef int32_t           qapi_USB_Status_t;

/** Client callback function type to be called when data is received for the client. */
typedef void (* qapi_USB_App_Rx_Cb_t) (void);

/** Client callback function type to provide a disconnect notification. */
typedef void (* qapi_USB_App_Disconnect_Cb_t) (void);

/** IOCTL command type. */
typedef enum {
  QAPI_USB_RX_CB_REG_E = 0,  /**< IOCTL command argument to register a client callback. */
  QAPI_USB_DISCONNECT_CB_REG_E   /**< Command argument to register a disconnect callback. */
} qapi_USB_Ioctl_Cmd_t;

/** @} */ /* end_addtogroup qapi_usb_types */

/*=============================================================================
                                   ENUMS
=============================================================================*/


/*============================================================================
                                  STRUCTURES
============================================================================*/


#endif /** QAPI_USB_TYPES_H*/


