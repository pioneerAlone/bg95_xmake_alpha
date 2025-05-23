/*=======================================================================
 Copyright (c) 2017-2019  Qualcomm Technologies, Inc.  All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
 ======================================================================*/

/*===========================================================================

						EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when         who     what, where, why
----------   ---     ---------------------------------------------------------
2018-06-04   akashy  Updated copyright for 2018
2017-04-24   leo     (Tech Comm) Edited/added Doxygen comments and markup.
2017-02-22   akashy  Initial Version.

===========================================================================*/

#ifndef QAPI_USB_H
#define QAPI_USB_H
/**
 * @file qapi_usb.h
 *
 * @brief  Contains QAPI USB driver definitions.
 *
 * @addtogroup qapi_usb
 * @{
 *
 * These USB APIs enable clients to open a USB channel to allow data transfers
 * between the client and the device without a specific packet format.
 *
 * @code
 *
 *
 *  * The code snippet below demonstrates use of this interface. The example
 *  * below opens a USB channel and then the write API helps the client send
 *  * data over USB. The Read API enables clients to get data over USB.
 *  * The client must define a callback function that is called whenever
 *  * there is data for the client, and then the client can call the Read
 *  * function.
 *  *
 *  * Clients can register a disconnect callback if they wish to be notified
 *  * whenever USB is disconnected.
 *
 *   void* Buffer;
 *   uint16 Max_Size;
 *   void* Data_Ptr;
 *   uint16 Len;
 *   void Callback_func(void);
 *   void disconnect_cb(void);
 *
 *   // To open a USB channel
 *   status = qapi_USB_Open();
 *   if (status != QAPI_OK) { ... }
 *
 *   // To read data over USB; buffer to get data and max size it can take
 *   status = qapi_USB_Read(&Buffer, Max_Size);
 *   if (status != QAPI_OK) { ... }
 *
 *   // To send data over USB; pointer to data and length of data
 *   status = qapi_USB_Write(Data_Ptr, Len);
 *   if (status != QAPI_OK) { ... }
 *
 *   // To register a client callback for getting notified about available data
 *   // for client
 *   status = qapi_USB_Ioctl(QAPI_USB_RX_CB_REG_E, (void*)Callback_func);
 *   if (status != QAPI_OK) { ... }
 *
 *   // To register disconnect callback
 *   status = qapi_USB_Ioctl(QAPI_USB_DISCONNECT_CB_REG_E, (void*)disconnect_cb);
 *   if (status != QAPI_OK) { ... }
 *
 * @endcode
 *
 * @}
 */

#include "qapi_usb_types.h"
                                                                                                                           
/*============================================================================
                USER_Mode_DEFS
============================================================================*/

                 /* Driver ID defines */

#define  TXM_QAPI_USB_OPEN              (TXM_QAPI_USB_BASE)
#define  TXM_QAPI_USB_READ              (TXM_QAPI_USB_BASE + 1)
#define  TXM_QAPI_USB_WRITE             (TXM_QAPI_USB_BASE + 2)
#define  TXM_QAPI_USB_IOCTL             (TXM_QAPI_USB_BASE + 3)

#define TXM_QAPI_USB_RX_CB              (CUSTOM_CB_QAPI_USB_BASE)
#define TXM_QAPI_USB_DISC_CB            (CUSTOM_CB_QAPI_USB_BASE + 1)


UINT qapi_USB_Handler(UINT id, UINT a, UINT b, UINT c, UINT d, UINT e,
						UINT f, UINT g, UINT h, UINT i, UINT j, UINT k, UINT l);

#ifdef  QAPI_TXM_MODULE

//Quectel Added, add static to avoid redefinition
static int qapi_USB_user_cb_dispatcher(UINT cb_id, void *app_cb,
                                     UINT cb_param1, UINT cb_param2,
                                     UINT cb_param3, UINT cb_param4,
                                     UINT cb_param5, UINT cb_param6,
                                     UINT cb_param7, UINT cb_param8)
{
  void (*pfn_app_cb1) (void);
  void (*pfn_app_cb2) (void);

  if(cb_id == TXM_QAPI_USB_RX_CB) // app_rx_cb
  {
      pfn_app_cb1 = (void (*)(void))app_cb;
      (pfn_app_cb1)();
  }
  else if(cb_id == TXM_QAPI_USB_DISC_CB) // app_disconnect_cb
  {
      pfn_app_cb2 = (void (*)(void))app_cb;
      (pfn_app_cb2)();
  }

  return 0;
}


                /* API Definitions */
#define qapi_USB_Open()\
	((qapi_USB_Status_t) (_txm_module_system_call12)(TXM_QAPI_USB_OPEN,\
	(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
	(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_USB_Read(Buffer, Max_Size)\
	((qapi_USB_Status_t) (_txm_module_system_call12)(TXM_QAPI_USB_READ,\
	(ULONG) Buffer, (ULONG) Max_Size, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
	(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_USB_Write(Data_Ptr, Len)\
	((qapi_USB_Status_t) (_txm_module_system_call12)(TXM_QAPI_USB_WRITE,\
	(ULONG) Data_Ptr, (ULONG) Len, (ULONG) 0, (ULONG) 0, (ULONG) 0,\
	(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#define qapi_USB_Ioctl(Cmd, Param)\
	((qapi_USB_Status_t) (_txm_module_system_call12)(TXM_QAPI_USB_IOCTL,\
	(ULONG) Cmd, (ULONG) Param, (ULONG) qapi_USB_user_cb_dispatcher, (ULONG) 0, (ULONG) 0,\
	(ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))


#elif defined QAPI_TXM_SOURCE_CODE

/*============================================================================
                KERNEL_Mode_DEFS
============================================================================*/

/** @addtogroup qapi_usb
@{ */

/*============================================================================
                qapi_USB_Open
============================================================================*/
/**
 *  Opens a ser3 channel for pure data transfer through USB.
 * 
 * @details This channel enables a data transfer path for clients without any
 * protocol.
 *
 * @return
 * QAPI_OK on success, a -ve error code on failure. \n
 * QAPI_ERR__ALREADY_DONE -- The ser3 channel is already open.
 */
qapi_USB_Status_t qapi_USB_Open(void);
                              
/*============================================================================
                qapi_USB_Read
============================================================================*/
/**
 *   Reads USB data.
 *
 *  @details This function is to be called after USB sends a callback that the
 *  PC has sent data. It can also be called without receiving the callback,
 *  but data might not be available with the USB.
 *
 *  @param[out] Buffer   Buffer to where the data is to be copied.
 *
 *  @param[in] Max_Size  Maximum size of the data that the client can take.
 *
 *  @return
 *  QAPI_OK on success, a -ve error code  on failure. \n
 *  QAPI_ERR_NO_DATA -- No data is available.
 */
qapi_USB_Status_t qapi_USB_Read(void ** Buffer, 
                               uint16_t Max_Size);

/*============================================================================
                qapi_USB_Write
============================================================================*/
/**
 *   Sends data over USB.
 *
 *  @details The client must send a data pointer and the length of the data
 *           it wishes to send over the channel.
 *
 *  @param[in] Data_Ptr  Pointer to the data that the client wishes to send.
 *
 *  @param[in] Len       Length of the data to be sent.
 *
 *  @return
 *  QAPI_OK on success, a -ve error code on failure.
 */
qapi_USB_Status_t qapi_USB_Write(void * Data_Ptr, 
                               uint16_t Len);
                             
/*============================================================================
                qapi_USB_Ioctl
============================================================================*/
/**
 *    IOCTL for registering the client Rx callback.
 *
 *  @details This IOCTL is made generic so that it may later be used for some
 *  other purposes.
 *
 *  @param[in] Cmd    Determines for what the IOCTL is called.
 *                    Currently, only the purpose stated above is valid.
 *
 *  @param[in] Param  Can change based on the command passed.
 *                    For currently used commands, it is a function pointer.
 *
 *  @return
 *  QAPI_OK on success, a -ve error code on failure. \n
 *  QAPI_ERR_INVALID_PARAM -- The command received is not supported.
 */
qapi_USB_Status_t qapi_USB_Ioctl(qapi_USB_Ioctl_Cmd_t Cmd,
							   void * Param);

/** @} */ /* end_addtogroup qapi_usb */


#else   

  #error "No QAPI flags defined"

#endif


#endif /** QAPI_USB_H */
