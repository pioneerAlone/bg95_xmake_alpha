/*
 *Copyright :

 *Copyright (c) 2021, Quectel Wireless Solutions Co., Ltd. All rights reserved.

 *Quectel Wireless Solutions Proprietary and Confidential.
 */
/******************************************************************************

            quectel_uart_apis.h

******************************************************************************/

/******************************************************************************/
#ifndef __QUECTEL_UART_APIS_H__
#define __QUECTEL_UART_APIS_H__

#include "qapi_uart.h"

/**************************************************************************
*                                 DEFINE
***************************************************************************/
typedef struct{
	qapi_UART_Handle_t  hdlr;
	qapi_UART_Port_Id_e port_id;
	char *tx_buff;
	uint32_t tx_len;
	char *rx_buff;
	uint32_t rx_len;
	uint32_t baudrate;
}QT_UART_CONF_PARA;

#define QT_QAPI_UART_PORT_01		QAPI_UART_PORT_001_E
#define QT_QAPI_UART_PORT_02		QAPI_UART_PORT_003_E
#define QT_QAPI_UART_PORT_03		QAPI_UART_PORT_002_E
#define QT_QAPI_UART_PORT_04		QAPI_UART_PORT_004_E  /* main UART ID. Main UART port can be used for QuecOpen only after disabling AT command communication, 
                                                             that is, after setting QT_MAIN_UART_ENABLE mode by qapi_QT_Main_UART_Enable_Set() and restarting the module */

#define QT_UART_ECHO_ENABLE
/**************************************************************************
*                           FUNCTION DECLARATION
***************************************************************************/
void uart_init(QT_UART_CONF_PARA *uart_conf);
void uart_print(QT_UART_CONF_PARA *uart_conf, char *buff, uint16_t len);
void uart_recv(QT_UART_CONF_PARA *uart_conf);
void qt_uart_dbg(qapi_UART_Handle_t uart_hdlr, const char* fmt, ...);

#endif /* __QUECTEL_UART_APIS_H__ */

