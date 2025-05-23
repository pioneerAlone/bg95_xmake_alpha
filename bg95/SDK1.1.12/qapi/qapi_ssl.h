/*=======================================================================
 Copyright (c) 2017-2021  Qualcomm Technologies, Inc.  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
 ======================================================================*/

/*
!! IMPORTANT NOTE: "DATA SERVICES" VERSION CATEGORY.
*/

/**
 * @file qapi_ssl.h
 *
 * @brief This file describes the QAPIs used for transport layer
 *        security (TLS) and Datagram stransport layer security
 *        (DTLS).
 *
 * @details TLS and DTLS are used to provide security and data
 * integrity between two peers communicating over TCP or UDP.
 * After a TCP/UDP connection is established, the two peers use
 * a handshake mechanism to establish the keys used for
 * encryption/decryption and data verification. Once the
 * handshake is successful, data can be transmitted/received
 * over the TLS/DTLS connection.
 *
 */
#ifndef _QAPI_SSL_H_
#define _QAPI_SSL_H_

#include <stdint.h>
#include <qapi_net_status.h>

#include "qapi_data_txm_base.h"

/* SSL QAPI REQUEST ID DEFINES */

#define  TXM_QAPI_NET_SSL_OBJ_NEW                    TXM_QAPI_NET_SSL_BASE + 1
#define  TXM_QAPI_NET_SSL_CON_NEW                    TXM_QAPI_NET_SSL_BASE + 2
#define  TXM_QAPI_NET_SSL_CONFIGURE                  TXM_QAPI_NET_SSL_BASE + 3
#define  TXM_QAPI_NET_SSL_CERT_DELETE                TXM_QAPI_NET_SSL_BASE + 4
#define  TXM_QAPI_NET_SSL_CERT_STORE                 TXM_QAPI_NET_SSL_BASE + 5
#define  TXM_QAPI_NET_SSL_CERT_LOAD                  TXM_QAPI_NET_SSL_BASE + 6
#define  TXM_QAPI_NET_SSL_CERT_LIST                  TXM_QAPI_NET_SSL_BASE + 7
#define  TXM_QAPI_NET_SSL_FD_SET                     TXM_QAPI_NET_SSL_BASE + 8
#define  TXM_QAPI_NET_SSL_ACCEPT                     TXM_QAPI_NET_SSL_BASE + 9
#define  TXM_QAPI_NET_SSL_CONNECT                    TXM_QAPI_NET_SSL_BASE + 10
#define  TXM_QAPI_NET_SSL_SHUTDOWN                   TXM_QAPI_NET_SSL_BASE + 11
#define  TXM_QAPI_NET_SSL_OBJ_FREE                   TXM_QAPI_NET_SSL_BASE + 12
#define  TXM_QAPI_NET_SSL_READ                       TXM_QAPI_NET_SSL_BASE + 13
#define  TXM_QAPI_NET_SSL_WRITE                      TXM_QAPI_NET_SSL_BASE + 14
#define  TXM_QAPI_NET_SSL_CERT_CONVERT_AND_STORE     TXM_QAPI_NET_SSL_BASE + 15
#define  TXM_QAPI_NET_SSL_CERT_LOAD_GET_IDENTIFIER   TXM_QAPI_NET_SSL_BASE + 16
#define  TXM_QAPI_NET_SSL_CERT_FILE_EXISTS           TXM_QAPI_NET_SSL_BASE + 17
#define  TXM_QAPI_NET_SSL_SET_EXTENDED_CONFIG        TXM_QAPI_NET_SSL_BASE + 18

/** @addtogroup qapi_net_ssl_datatypes
@{ */

/** Maximum number of characters in a certificate or CA list name. */
#define QAPI_NET_SSL_MAX_CERT_NAME_LEN (64)

/** Maximum number of characters in a domain name for the
 *  certificates. */
#define QAPI_NET_SSL_MAX_DOMAIN_NAME_LEN (64)

/** Maximum number of file names returned in the qapi_Net_SSL_Cert_List() API. */
#define QAPI_NET_SSL_MAX_NUM_CERTS (10)

/** Maximum number of cipher suites that can be configured. */
#define QAPI_NET_SSL_CIPHERSUITE_LIST_DEPTH 8

/** Invalid handle. */
#define QAPI_NET_SSL_INVALID_HANDLE (0)

/*
 * SSL protocol version, to be used with qapi_Net_SSL_Configure.
 * SSL 3.0 is deprecated.
 */

/** Unknown SSL protocol version. */
#define QAPI_NET_SSL_PROTOCOL_UNKNOWN                  0x00

/** TLS version 1.0. */
#define QAPI_NET_SSL_PROTOCOL_TLS_1_0                  0x31

/** TLS version 1.1. */
#define QAPI_NET_SSL_PROTOCOL_TLS_1_1                  0x32

/** TLS version 1.2. */
#define QAPI_NET_SSL_PROTOCOL_TLS_1_2                  0x33

/** DTLS version 1.0. */
#define QAPI_NET_SSL_PROTOCOL_DTLS_1_0                 0xEF

/** DTLS version 1.2. */
#define QAPI_NET_SSL_PROTOCOL_DTLS_1_2                 0xED

/*
 * SSL cipher suites. To be used with qapi_Net_SSL_Configure
 */
/** TLS PSK with RC4 128 SHA. */
#define QAPI_NET_TLS_PSK_WITH_RC4_128_SHA                   0x008A
/** TLS PSK with 3DES EDE CBC SHA. */
#define QAPI_NET_TLS_PSK_WITH_3DES_EDE_CBC_SHA              0x008B
/** TLS PSK with AES 128 CBC SHA. */
#define QAPI_NET_TLS_PSK_WITH_AES_128_CBC_SHA               0x008C
/** TLS PSK with AES 256 CBC SHA. */
#define QAPI_NET_TLS_PSK_WITH_AES_256_CBC_SHA               0x008D
/** TLS PSK with AES_128 GCM SHA256. */
#define QAPI_NET_TLS_PSK_WITH_AES_128_GCM_SHA256            0x00A8
/** TLS PSK with AES 256 GCM SHA384. */
#define QAPI_NET_TLS_PSK_WITH_AES_256_GCM_SHA384            0x00A9
/** TLS PSK with AES 128 CBC SHA256. */
#define QAPI_NET_TLS_PSK_WITH_AES_128_CBC_SHA256            0x00AE
/** TLS PSK with AES 256 CBC SHA384. */
#define QAPI_NET_TLS_PSK_WITH_AES_256_CBC_SHA384            0x00AF
/** TLS PSK with AES 128 CCM-8. */
#define QAPI_NET_TLS_PSK_WITH_AES_128_CCM_8                 0xC0A8
/** Cipher TLS RSA with AES 128 CBC SHA. */
#define QAPI_NET_TLS_RSA_WITH_AES_128_CBC_SHA               0x002F
/** Cipher TLS DHE RSA with AES 128 CBC SHA. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_128_CBC_SHA           0x0033
/** Cipher TLS RSA with AES 256 CBC SHA. */
#define QAPI_NET_TLS_RSA_WITH_AES_256_CBC_SHA               0x0035
/** Cipher TLS DHE RSA with AES 256 CBC SHA. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_256_CBC_SHA           0x0039
/** Cipher TLS RSA with AES 128 CBC SHA256. */
#define QAPI_NET_TLS_RSA_WITH_AES_128_CBC_SHA256            0x003C
/** Cipher TLS RSA with AES 256 CBC SHA256. */
#define QAPI_NET_TLS_RSA_WITH_AES_256_CBC_SHA256            0x003D
/** Cipher TLS DHE RSA with AES 128 CBC SHA256. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256        0x0067
/** Cipher TLS DHE RSA with AES 256 CBC SHA256. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256        0x006B
/** Cipher TLS RSA with AES 128 GCM SHA256. */
#define QAPI_NET_TLS_RSA_WITH_AES_128_GCM_SHA256            0x009C
/** Cipher TLS RSA with AES 256 GCM SHA384. */
#define QAPI_NET_TLS_RSA_WITH_AES_256_GCM_SHA384            0x009D
/** Cipher TLS DHE RSA with AES 128 GCM SHA256. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256        0x009E
/** Cipher TLS DHE RSA with AES 256 GCM SHA384. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384        0x009F
/** Cipher TLS ECDH ECDSA with AES 128 CBC SHA. */
#define QAPI_NET_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA        0xC004
/** Cipher TLS ECDH ECDSA with AES 256 CBC SHA. */
#define QAPI_NET_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA        0xC005
/** Cipher TLS ECDHE ECDSA with AES 128 CBC SHA. */
#define QAPI_NET_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA       0xC009
/** Cipher TLS ECDHE ECDSA with AES 256 CBC SHA. */
#define QAPI_NET_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA       0xC00A
/** Cipher TLS ECDH RSA with AES 128 CBC SHA. */
#define QAPI_NET_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA          0xC00E
/** Cipher TLS ECDH RSA with AES 256 CBC SHA. */
#define QAPI_NET_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA          0xC00F
/** Cipher TLS ECDHE RSA with AES 128 CBC SHA. */
#define QAPI_NET_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA         0xC013
/** Cipher TLS ECDHE RSA with AES 256 CBC SHA. */
#define QAPI_NET_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA         0xC014
/** Cipher TLS ECDHE ECDSA with AES 128 CBC SHA256. */
#define QAPI_NET_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256    0xC023
/** Cipher TLS ECDHE ECDSA with AES 256 CBC SHA384. */
#define QAPI_NET_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384    0xC024
/** Cipher TLS ECDH ECDSA with AES 128 CBC SHA256. */
#define QAPI_NET_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256     0xC025
/** Cipher TLS ECDH ECDSA with AES 256 CBC SHA384. */
#define QAPI_NET_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384     0xC026
/** Cipher TLS ECDHE RSA with AES 128 CBC SHA256. */
#define QAPI_NET_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256      0xC027
/** Cipher TLS ECDHE RSA with AES 256 CBC SHA384. */
#define QAPI_NET_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384      0xC028
/** Cipher TLS ECDH RSA with AES 128 CBC SHA256. */
#define QAPI_NET_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256       0xC029
/** Cipher TLS ECDH RSA with AES 256 CBC SHA384. */
#define QAPI_NET_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384       0xC02A
/** Cipher TLS ECDHE ECDSA with AES 128 GCM SHA256. */
#define QAPI_NET_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256    0xC02B
/** Cipher TLS ECDHE ECDSA with AES 256 GCM SHA384. */
#define QAPI_NET_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384    0xC02C
/** Cipher TLS ECDH ECDSA with AES 128 GCM SHA256. */
#define QAPI_NET_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256     0xC02D
/** Cipher TLS ECDH ECDSA with AES 256 GCM SHA384. */
#define QAPI_NET_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384     0xC02E
/** Cipher TLS ECDHE RSA with AES 128 GCM SHA256. */
#define QAPI_NET_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256      0xC02F
/** Cipher TLS ECDHE RSA with AES 256 GCM SHA384. */
#define QAPI_NET_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384      0xC030
/** Cipher TLS ECDH RSA with AES 128 GCM SHA256. */
#define QAPI_NET_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256       0xC031
/** Cipher TLS ECDH RSA with AES 256 GCM SHA384. */
#define QAPI_NET_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384       0xC032
/** Cipher TLS ECDHE ECDSA With AES 128 CCM8. */
#define QAPI_NET_TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8         0xC0AE
/** Cipher TLS RSA with AES 128 CCM. */
#define QAPI_NET_TLS_RSA_WITH_AES_128_CCM                   0xC09C
/** Cipher TLS RSA with AES 256 CCM. */
#define QAPI_NET_TLS_RSA_WITH_AES_256_CCM                   0xC09D
/** Cipher TLS DHE RSA with AES 128 CCM. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_128_CCM               0xC09E
/** Cipher TLS DHE RSA with AES 256 CCM. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_256_CCM               0xC09F
/** Cipher TLS RSA with AES 128 CCM 8. */
#define QAPI_NET_TLS_RSA_WITH_AES_128_CCM_8                 0xC0A0
/** Cipher TLS RSA with AES 256 CCM 8. */
#define QAPI_NET_TLS_RSA_WITH_AES_256_CCM_8                 0xC0A1
/** Cipher TLS DHE RSA with AES 128 CCM 8. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_128_CCM_8             0xC0A2
/** Cipher TLS DHE RSA with AES 256 CCM 8. */
#define QAPI_NET_TLS_DHE_RSA_WITH_AES_256_CCM_8             0xC0A3
/** Cipher TLS ECDHE RSA with CHACHA20 POLY1305 SHA256. */
#define QAPI_NET_TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256   0xCC13
/** Cipher TLS ECDHE ECDSA with CHACHA20 POLY1305 SHA256. */
#define QAPI_NET_TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256 0xCC14
/** Cipher TLS DHE RSA with CHACHA20 POLY1305 SHA256. */
#define QAPI_NET_TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256     0xCC15

/** @} */ /* end_addtogroup qapi_net_ssl_datatypes */

/*
 * Please refer to qapi_net_status.h for SSL QAPI return values.
 * See qapi_status.h for common error codes.
 */

/**
 * SSL identifier type.
 */
typedef enum
{
  QAPI_NET_SSL_ID_CN = 1,
  /**< Subject common name; refer to RFC6125, Section 1.8. */

  QAPI_NET_SSL_ID_ALT_DNS = 2,
  /**< Subject alternate name entry of type dNSName; refer to RFC6125, Section 1.8. */

  QAPI_NET_SSL_ID_SRV = 3,
  /**< Service type name. */

  QAPI_NET_SSL_ID_ALT_URI = 4,
  /**< Subject alternate name entry of type URI; refer to RFC6125, Section 1.8. */

} qapi_Net_SSL_Identifier_Type_t;

/** @addtogroup qapi_net_ssl_datatypes
@{ */

/**
 * Structure to specify the certificate verification policy.
 */
typedef struct /** @cond */__qapi_Net_SSL_Verify_Policy_s/** @endcond */ {
    uint8_t domain ;
    /**< TRUE to verify certificate commonName against the peer's domain name. */

    uint8_t time_Validity ;
    /**< TRUE to verify certificate time validity. */

    uint8_t send_Alert ;
    /**< TRUE to immediately send a fatal alert on detection of an untrusted certificate. */

    char match_Name[QAPI_NET_SSL_MAX_CERT_NAME_LEN];
    /**< Name to match against the common name or altDNSNames of the certificate. See
         #QAPI_NET_SSL_MAX_CERT_NAME_LEN. */
}  qapi_Net_SSL_Verify_Policy_t;

/**
 * Structure to get the identifier from the certificate.
 */
typedef struct /** @cond */__qapi_Net_SSL_Identifier_s/** @endcond */ {
    qapi_Net_SSL_Identifier_Type_t identifier_Type;
    /**< Type of identifier to extract from the certificate. */

    char identifier_Name[QAPI_NET_SSL_MAX_DOMAIN_NAME_LEN];
    /**< Name (altDNSNames, altURIs, or common name of the certificate. See
         #QAPI_NET_SSL_MAX_CERT_NAME_LEN. */
}  qapi_Net_SSL_Identifier_t;

/**
 * Structure to configure an SSL connection.
 */
typedef  struct /** @cond */__qapi_Net_SSL_Config_s/** @endcond */ {
    uint16_t protocol ;
    /**< Protocol to use. See QAPI_NET_SSL_PROTOCOL_*. */

    uint16_t cipher[QAPI_NET_SSL_CIPHERSUITE_LIST_DEPTH] ;
    /**< Cipher to use. See SSL cipher suites QAPI_NET_TLS* and
         #QAPI_NET_SSL_CIPHERSUITE_LIST_DEPTH. */

    qapi_Net_SSL_Verify_Policy_t verify ;
    /**< Certificate verification policy. */

    uint16_t max_Frag_Len;
    /**< Maximum fragment length in bytes. */

    uint16_t max_Frag_Len_Neg_Disable;
    /**< Whether maximum fragment length negotiation is allowed. See RFC 6066. */

    uint16_t sni_Name_Size;
    /**< Length of the SNI server name. */

    char *sni_Name;
    /**< Server name for SNI. */

}  qapi_Net_SSL_Config_t;

/**
 * Structure to get a list of certificates stored in nonvolatile memory.
 */
typedef struct __qapi_Net_SSL_Cert_List_s {
    char name[QAPI_NET_SSL_MAX_NUM_CERTS][QAPI_NET_SSL_MAX_CERT_NAME_LEN];
    /**< Certificate name. See #QAPI_NET_SSL_MAX_NUM_CERTS and
         #QAPI_NET_SSL_MAX_CERT_NAME_LEN. */
} qapi_Net_SSL_Cert_List_t;

/**
 * SSL object role.
 */
typedef enum
{
  QAPI_NET_SSL_SERVER_E = 1,
  /**< Server role. Not supported. */

  QAPI_NET_SSL_CLIENT_E = 2
  /**< Client role. */
} qapi_Net_SSL_Role_t;

/**
 * SSL protocol.
 */
typedef enum
{
  QAPI_NET_SSL_TLS_E  = 1,
  /**< TLS protocol. */

  QAPI_NET_SSL_DTLS_E = 2,
  /**< DTLS protocol. */
} qapi_Net_SSL_Protocol_t;

/**
 * SSL certificate type.
 */
typedef enum
{
  QAPI_NET_SSL_CERTIFICATE_E = 1,
  /**< Certificate type. */

  QAPI_NET_SSL_CA_LIST_E = 2,
  /**< CA list type. */

  QAPI_NET_SSL_PSK_TABLE_E = 3,
  /**< PSK key table type. */

  QAPI_NET_SSL_DI_CERT_E = 4
  /**< Domain-issued certificate type. */

} qapi_Net_SSL_Cert_Type_t;


/** Maximum certificate authority list entries allowed for conversion to binary format. */
#define QAPI_NET_SSL_MAX_CA_LIST 10

/**
 * SSL client certificate info for conversion and storage.
 */
typedef struct __qapi_Net_SSL_CERT_s
{
    uint8_t *cert_Buf;
    /**< Client certificate buffer. */
    uint32_t cert_Size;
    /**< Client certificate buffer size. */
    uint8_t *key_Buf;
    /**< Private key buffer. */
    uint32_t key_Size;
    /**< Private key buffer size. */
    uint8_t *pass_Key;
    /**< Password phrase. */
} qapi_Net_SSL_CERT_t;

/**
 * SSL certificate authority list information.
 */
typedef struct __qapi_NET_SSL_CA_Info_s
{
    uint8_t *ca_Buf;
    /**< Certificate authority list buffer. */
    uint32_t ca_Size;
    /**< Certificate authority list buffer size. */
} qapi_NET_SSL_CA_Info_t;

/**
  * SSL certificate authority information for conversion and storage.
  */
typedef struct __qapi_Net_SSL_CA_List_s
{
    uint32_t ca_Cnt;
    /**< Certificate authority list count. */
    qapi_NET_SSL_CA_Info_t *ca_Info[QAPI_NET_SSL_MAX_CA_LIST];
    /**< Certificate authority list info. */
} qapi_Net_SSL_CA_List_t;

/**
  * SSL PSK table information for conversion and storage.
  */
typedef struct __qapi_Net_SSL_PSK_Table_s
{
    uint32_t psk_Size;
    /**< PSK table buffer size. */
    uint8_t *psk_Buf;
    /**< PSK table buffer. */
} qapi_Net_SSL_PSK_Table_t;

/**
  * SSL domain-issued certificate information for conversion and storage.
  */
typedef struct __qapi_Net_SSL_DI_Cert_s
{
    uint32_t di_Cert_Size;
    /**< Domain-issued certificate buffer size. */
    uint8_t *di_Cert_Buf;
    /**< Domain-issued certificate buffer. */
} qapi_Net_SSL_DI_Cert_t;

/**
  * SSL general certification information for conversion and
  * storage for client certificates, CA lists, and PSK tables.
  */
typedef struct __qapi_Net_SSL_Cert_Info_s
{
    qapi_Net_SSL_Cert_Type_t cert_Type;	/**< Certification type. */
    union
    {
       qapi_Net_SSL_CERT_t cert;		  /**< Certificate. */
       qapi_Net_SSL_CA_List_t ca_List;	  /**< CA list. */
       qapi_Net_SSL_PSK_Table_t psk_Tbl;  /**< PSK table. */
       qapi_Net_SSL_DI_Cert_t di_cert;    /**< Domain-issued certificate. */
    } info;								  /**< Certificate information. */
} /** @cond */qapi_Net_SSL_Cert_Info_t/** @endcond */;

/** @} */ /* end_addtogroup qapi_net_ssl_datatypes */

/** @addtogroup qapi_net_ssl_typedefs
@{ */

/**
 * Handle to an SSL object.
 *
 * This is obtained from a call to qapi_Net_SSL_Obj_New(). The handle is
 * freed with a call to qapi_Net_SSL_Obj_Free().
 */
typedef uint32_t qapi_Net_SSL_Obj_Hdl_t;

/**
 * Handle to an SSL connection.
 *
 * This is obtained from a call to qapi_Net_SSL_Con_New(). The handle is
 * freed with a call to qapi_Net_SSL_Shutdown().
 */
typedef uint32_t qapi_Net_SSL_Con_Hdl_t;

/**
 * Internal certificate format. The certificate is in a binary
 * format optimized for speed and size. The *.bin foramt
 * certificate can be created using the command line tool
 * [SharkSslParseCert].
 *
 * @usage
 * SharkSslParseCert \<cert file\> \<privkey file\> [-p
 * \<passkey\>] [-b \<binary output file\>]
 */
typedef const void * qapi_Net_SSL_Cert_t;

/**
 * Internal DI certificate format. The certificate is in a binary
 * format optimized for speed and size.
 */
typedef const void * qapi_Net_SSL_DICERT_t;

/**
 * Internal CA list format. The CA list is in a binary format
 * optimized for speed and size. The list can be created
 * using the command line tool [SharkSSLParseCAList].
 *
 * @usage
 * SharkSSLParseCAList [-b \<binary output file\>]
 *     \<certfile\> [certfile...]
 *     where certfile is a .PEM file containing
 *     one or more certificates
 *
 *
 */
typedef const void * qapi_Net_SSL_CAList_t;

/**
 * Internal psk_table format.PSK table is in an optimized binary format.
 * The table can be created by using the command line tool
 * [SharkSslParsePSKTable]. Set the PSK file
 * format before using the tool. \n
 * Identity_1: psk_key1 \n
 * Identity_2: psk_key2
 *
 * @usage
 * SharkSslParsePSKTable \<PSK file\> [-b \<binary output
 * file\>]
 *
 */
typedef const void * qapi_Net_SSL_PSKTable_t;

/**
  * extended config items for ssl connection
  */
typedef enum
{
  QAPI_NET_SSL_EXTENDED_CONFIG_SESSION_NAME         = 0,
  /**< Session Name prefix used to store TLS/DTLS session. */

  QAPI_NET_SSL_EXTENDED_CONFIG_SESSION_LIFETIME     = 1,
  /**< Session Lifetime.\n
   * data type is uint32(seconds), value range [0, 86400], default is 86400(24hours). */

  QAPI_NET_SSL_EXTENDED_CONFIG_CONNECTION_TIMEOUT   = 2,
  /**< Connection timeout.\n
   * data type is uint32(seconds), value range [1, 60], default is 60
   * for TLS,  the value is the connection time out value,
   * for DTLS, the value is the max-retransmit-timer(retransmit logic: 1s, 2s, 4s,...max-retansmit-timer). */

  QAPI_NET_SSL_EXTENDED_CONFIG_DISABLE_CLOSE_NOTIFY = 3,
  /**< Disable Close-Notify when shutdown TLS/DTLS connection.
   * data type is uint32, value range [0, 1],
   * 1: disable close-notify
   * 0: enable  close-notify (default value). */

  QAPI_NET_SSL_EXTENDED_CONFIG_DTLS_HANDLE_ALERT_WITH_EPOCH_0 = 8,
  /**< Option to accept or discard an alert with epoch=0 after handshake process completed
   * Per RFC spec, SSL should discard packets with epoch=0 after handshake,
   * but in some special network environment, DTLS session may be lost and server cannot fill correct epoch and sequence number,
   * then server sends alert with epoch=0 to notify session is down and client need to do re-handshake.
   * Note: there is DoS risk to enable this option.
   * Data type is uint8, value range [0, 1].  \n
   * 1: SSL accept the alert packet with epoch=0, as normal alert.  \n
   * 0: SSL discard the alert packet with epoch=0. */
  QAPI_NET_SSL_EXTENDED_CONFIG_RFC_COMPATIBLE_SECURE_RENEGOTIATION_FEATURE = 10,
  /**< Option to configure compatibility of secure renegotiation feature.
   * Per RFC5746, client can either continue handshake if server does not support
   * secure renegotiation, or abort the handshake with alert if client wish to ensure
   * renegotiation attacks are impossible.
   *
   * For TLS1.3, which is not support renegotiation at all, this option is meaningful for
   * fallback scenario.
   *
   * Data type is uint8, value range [0, 1].  \n
   * 1: not compatible with server that not support secure renegotiation \n
   * 0: compatible with server that not support secure renegotiation. */

  QAPI_NET_SSL_EXTENDED_CONFIG_ENABLE_RENEG_EXTENSION = 11,
  /**< To enable use of Renegotiation_Info extension in stead of SCSV.
   * Per RFC5746, client can either include SCSV or empty Renegotiaton_Info extension
   * to indicate support of secure renegotiation. By default we will include SCSV.
   *
   * Data type is uint8, value range [0, 1].  \n
   * 1: use Renegotiation_Info extension in ClientHello \n
   * 0: use SCSV in ClientHello*/

  QAPI_NET_SSL_EXTENDED_CONFIG_MAX

}qapi_Net_SSL_Extended_Config_Options_t;

#ifdef  QAPI_TXM_MODULE     // USER_MODE_DEFS

#define qapi_Net_SSL_Obj_New(a)                     ((UINT) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_OBJ_NEW      , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Con_New(a,b)                   ((UINT) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CON_NEW      , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Configure(a,b)                 ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CONFIGURE    , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Cert_delete(a,b)               ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CERT_DELETE  , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Cert_Store(a,b,c,d)            ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CERT_STORE   , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Cert_Load(a,b,c)               ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CERT_LOAD    , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Cert_List(a,b)                 ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CERT_LIST    , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Fd_Set(a,b)                    ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_FD_SET       , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Accept(a)                      ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_ACCEPT       , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Connect(a)                     ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CONNECT      , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Shutdown(a)                    ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_SHUTDOWN     , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Obj_Free(a)                    ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_OBJ_FREE     , (ULONG) a, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Read(a,b,c)                    ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_READ         , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Write(a,b,c)                   ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_WRITE        , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Cert_Convert_And_Store(a,b)    ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CERT_CONVERT_AND_STORE  , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Cert_Load_Get_Identifier(a,b,c) ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CERT_LOAD_GET_IDENTIFIER    , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Cert_File_Exists(a,b)          ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_CERT_FILE_EXISTS    , (ULONG) a, (ULONG) b, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))
#define qapi_Net_SSL_Set_Extended_Config_Option(a,b,c,d)  ((int32_t) (_txm_module_system_call12)(TXM_QAPI_NET_SSL_SET_EXTENDED_CONFIG    , (ULONG) a, (ULONG) b, (ULONG) c, (ULONG) d, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0, (ULONG) 0))

#else

int32_t qapi_SSL_Handler(UINT id, UINT a1, UINT a2, UINT a3, UINT a4, UINT a5, UINT a6, UINT a7, UINT a8, UINT a9, UINT a10, UINT a11, UINT a12);

/** @} */ /* end_addtogroup qapi_net_ssl_typedefs */


/** @ingroup qapi_create_ssl_object
 * Creates a new SSL object (client).
 *
 * @param[in] role Client role. Server is not supported.
 *
 * @return
 * SSL object handle on success. \n
 * QAPI_NET_SSL_HDL_NULL on error (out of memory).
 *
 * @dependencies
 * This function must be called before using any other SSL function.
 */
qapi_Net_SSL_Obj_Hdl_t qapi_Net_SSL_Obj_New(qapi_Net_SSL_Role_t role);

/** @ingroup qapi_create_conn_handle
 * Creates an SSL connection handle for an SSL object.
 *
 * @param[in] hdl  SSL object handle.
 * @param[in] prot Protocol to be used for this connection.
 *
 * @return
 * SSL connection handle on success. \n
 * QAPI_NET_SSL_HDL_NULL on error (out of memory).
 */
qapi_Net_SSL_Con_Hdl_t qapi_Net_SSL_Con_New(qapi_Net_SSL_Obj_Hdl_t hdl, qapi_Net_SSL_Protocol_t prot);

/** @ingroup qapi_config_ssl_conn
 * Configures an SSL connection regarding protocol and cipher, certificate
 * validation criteria, maximum fragment length, and disable fragment length
 * negotiation.
 *
 * The SSL protocol and up to 8 ciphers can be configured in the client context.
 *
 * The SSL_VERIFY_POLICY verify structure (and matchName) specify how the
 * SSL certificate will be verified during the SSL handshake:
 * - If verify.domain = 1, the certificate domain name will be
 *   checked against matchName
 * - If verify.timeValidity = 1, the certificate will be checked
 *   for expiration.
 * - The certificate itself is always checked against the CAList. If a
 *   CAList is not present in the SSL context, the certificate is implicitly
 *   trusted.
 * - If verify.sendAlert = 1, an SSL alert is sent if the certificate fails
 *   any of the tests. An error is also returned to the application, which
 *   subsequently closes the connection. If verify.sendAlert = 0, an error is
 *   returned by SSL_connect(), and it is up to the application to decide
 *   what to do.
 *
 * In SSL, a smaller fragment length helps in efficient memory utilization and
 * to minimize latency. In Client mode, a maximum fragment length of 1 KB is
 * negotiated during handshake using TLS extensions. If the peer server does not
 * support the extension, the default maximum size of 16 KB is used.
 *
 * SSL_configure provides two fields, max_frag_len and
 * max_frag_len_neg_disable, to override the above behavior.
 * max_frag_len_neg_disable applies only in Client mode.
 *
 * If set max_frag_len as 0, defautl configuration will be applied
 * Default configuration is:
 *   max_frag_len = 1024
 *   max_frag_len_neg_disable = 0
 *
 * If negotiation is allowed (i.e, max_frag_len_neg_disable = 0), max_frag_len
 * must be set to one of these four values, according to RFC 6066:
 * - 1 -- 512
 * - 2 -- 1024
 * - 3 -- 2048
 * - 4 -- 4096
 * Other values are not permitted.
 *
 * max_frag_len is applicable in Client or Server mode. Server mode does not
 * support a maximum fragment length TLS extension.
 *
 * There can be scenarios where the peer does not support the maximum fragment length
 * TLS extension, but the maximum fragment length is inferred. In that case,
 * the user may choose to configure max_frag_len and set max_frag_len_neg_disable to
 * 1 to disable negotiation and still get the benefits of a smaller fragment
 * length. When negotiation is disabled, any value < 16 KB can be configured for
 * max_frag_len. When value >= 16KB, the max_frag_len is set to 16384. Then the above
 * limitations do not apply.
 *
 * An error is returned and the connection is closed if any incoming record exceeds
 * max_frag_len.
 *
 * @param[in] ssl Connection handle.
 * @param[in] cfg Configuration parameters.
 *
 * @return
 * QAPI_OK on success. \n
 * QAPI_ERR_INVALID_PARAM_SSL if an error occurred (configuration is invalid).
 */
qapi_Status_t qapi_Net_SSL_Configure(qapi_Net_SSL_Con_Hdl_t ssl, qapi_Net_SSL_Config_t *cfg);

/** @ingroup qapi_delete_ssl_cert
 * Deletes an encrypted certificate or CA list, or a PSK table from
 * nonvolatile memory.
 *
 * @param[in] name Name of the certificate, CA list, or PSK table.
 *                 The maximum length of the name allowed is QAPI_NET_SSL_MAX_CERT_NAME_LE,
 *                 including the NULL character.
 * @param[in] type Type of data (certificate or CA list) to store.
 *                 Could be either QAPI_NET_SSL_CERTIFICATE_E,
 *                 QAPI_NET_SSL_CA_LIST_E, or QAPI_NET_SSL_PSK_TABLE_E.
 *
 * @return
 * 0 on success. \n
 * Negative value on error (see SslErrors).
 */
qapi_Status_t qapi_Net_SSL_Cert_delete(char *name, qapi_Net_SSL_Cert_Type_t type);

/** @ingroup qapi_store_ssl_cert
 * Stores an internal certificate or CA list, or a PSK table in
 * nonvolatile memory in encrypted form.
 *
 * The certificate is in binary format optimized for speed and
 * size. The *.bin format certificate can be created using
 * the command line tool [SharkSslParseCert].
 *
 * The CA list is in binary format
 * optimized for speed and size. The list can be created
 * using the command line tool [SharkSSLParseCAList].
 *
 * The PSK table is in an optimized binary format.
 * The table can be created using the command line tool
 * [SharkSslParsePSKTable].
 * Set the table format before using the tool: \n
 * Identity_1: psk_key1 \n
 * Identity_2: psk_key2
 *
 *
 * @param[in] name Name of the certificate, CA list, or PSK
 *                 table. The maximum length of the name allowed
 *                 is QAPI_NET_SSL_MAX_CERT_NAME_LEN, including
 *                 the NULL character.
 * @param[in] type Type of data (certificate, CA list, or PSK table)
 *                 to store. Could be either QAPI_NET_SSL_CERTIFICATE_E,
 *                 QAPI_NET_SSL_CA_LIST_E, or QAPI_NET_SSL_PSK_TABLE_E.
 * @param[in] cert Address of the file containing the certificate in SSL
 *                 internal format (*.bin file).
 * @param[in] size Size of the certificate file.
 *
 * @return
 * 0 on success. \n
 * Negative value on error (see SslErrors).
 */
qapi_Status_t qapi_Net_SSL_Cert_Store(const char *name, qapi_Net_SSL_Cert_Type_t type, qapi_Net_SSL_Cert_t cert, uint32_t size);

/** @ingroup qapi_net_ssl_cert_convert_and_store
 * Converts certificates, CA lists from .PEM and PSK
 * tables to binary format and stores them in nonvolatile memory
 * in encrypted form. The certificate is in binary format optimized
 * for speed and size. Only one of these types can be converted and
 * stored at a time.
 *
 * The maximum number of CA lists that are supported for conversion and
 * storage in binary format is QAPI_NET_SSL_MAX_CA_LIST.
 *
 * The PSK table must be in the following format:
 * - Identity_1: psk_key1
 * - Identity_2: psk_key2
 *
 * @param[in] cert_info  Information pertaining to either the client certificate,
 *                       CA lists in .PEM format or PSK tables.
 * @param[in] cert_name  Name of the certificate, CA list, or PSK table that
 *                       the cert_info is to be stored under after the conversion.
 *
 * @return
 * 0 on success. \n
 * Negative value on error (see SslErrors).
 */
qapi_Status_t qapi_Net_SSL_Cert_Convert_And_Store(qapi_Net_SSL_Cert_Info_t *cert_info, const	uint8_t *cert_name);


/** @ingroup qapi_load_ssl_cert
 * Reads an encrypted certificate or CA list, or a PSK table from
 * nonvolatile memory, decrypts it, and then adds it to
 * the SSL object.
 *
 * - Certficate -- Loads a client certificate to the SSL
 * object.
 *
 * - Certificate Authority (CA) list -- Enables the SSL object to
 * perform certificate validation on the peer's certificate.
 * Only one CA list can be set, thus the CA list must include
 * all root certificates required for the Session
 *
 * - PSK table -- Holds a list of preshared keys (PSK) to load SSL
 * conext. Only one PSK table can be set, thus the PSK table
 * must include all PSK entries required for the
 * session.
 *
 * Certificates, CA lists, or a PSK table must be added before
 * the qapi_Net_SSL_Connect() or qapi_Net_SSL_Accept() APIs are
 * called.
 *
 * @param[in] hdl SSL object handle.
 * @param[in] type Type of data (certificate or CA list) to load.
 *                 Could be either QAPI_NET_SSL_CERTIFICATE_E,
 *                 QAPI_NET_SSL_CA_LIST_E, or QAPI_NET_SSL_PSK_TABLE_E.
 * @param[in] name Name of the file to load.
 *
 * @return
 * 0 on success. \n
 * Negative value on error (see SslErrors).
 */
qapi_Status_t qapi_Net_SSL_Cert_Load(qapi_Net_SSL_Obj_Hdl_t hdl, qapi_Net_SSL_Cert_Type_t type, const char *name);

/** @ingroup qapi_load_ssl_cert2
 * Reads an encrypted domain-issued certificate (RFC6698, mode 3) from
 * nonvolatile memory, decrypts it, and then adds it to
 * the SSL object and returns the identifier.
 *
 * Domain Issued Certficate: Load a DI certificate to the SSL
 * object.
 *
 * @param[in] hdl SSL object handle.
 * @param[out] identifier Type of certificate identifier.
 * @param[in] name Name of the file to load.
 *
 * @return
 * 0 on success, \n
 * Negative value on error (see SslErrors).
 */
qapi_Status_t qapi_Net_SSL_Cert_Load_Get_Identifier(qapi_Net_SSL_Obj_Hdl_t hdl, qapi_Net_SSL_Identifier_t *identifier, const char *name);

/** @ingroup qapi_get_cert_list
 * Gets a list of encrypted certificates or CA lists, or a PSK table stored
 * in nonvolatile memory.
 *
 * The structure #qapi_Net_SSL_Cert_List_t must be allocated by the
 * caller.
 *
 * @param[in] type Type of data (certificate or CA list) to store.
 *                 This can be either QAPI_NET_SSL_CERTIFICATE_E,
 *                 QAPI_NET_SSL_CA_LIST_E, or QAPI_NET_SSL_PSK_TABLE_E.
 * @param[in,out] list List of file names.
 *
 * @return
 * Number of files. \n
 * 0 on error.
 */
qapi_Status_t qapi_Net_SSL_Cert_List(qapi_Net_SSL_Cert_Type_t type, qapi_Net_SSL_Cert_List_t *list);

/** @ingroup qapi_attach_socket_descriptor
 * Attaches a given socket descriptor to the SSL connection.
 *
 * The SSL connection inherits the behavior of the socket
 * descriptor (zero-copy/nonzero-copy, blocking/nonblocking, etc.).
 *
 * @param[in] ssl SSL connection handle.
 * @param[in] fd FD socket descriptor.
 *
 * @return
 * QAPI_OK on success. \n
 * QAPI_ERR_INVALID_PARAM_SSL on error.
 */
qapi_Status_t qapi_Net_SSL_Fd_Set(qapi_Net_SSL_Con_Hdl_t ssl, uint32_t fd);

/** @ingroup qapi_accept_ssl_conn
 * Accepts an incoming SSL connection from the client.
 *
 * This should be called only by a server SSL object. This will respond
 * to the incoming client Hello message and complete the SSL handshake.
 *
 * @param[in] ssl SSL connection handle.
 *
 * @return
 * QAPI_SSL_OK_HS on success. \n
 * QAPI_ERR_* on error.
 */
qapi_Status_t qapi_Net_SSL_Accept(qapi_Net_SSL_Con_Hdl_t ssl);

/** @ingroup qapi_init_ssl_handshake
 * Initiates an SSL handshake. Called only by a client SSL object.
 *
 * @param[in] ssl SSL connection handle.
 *
 * @return
 * QAPI_SSL_OK_HS on success. \n
 * QAPI_ERR_* on error.
 */
qapi_Status_t qapi_Net_SSL_Connect(qapi_Net_SSL_Con_Hdl_t ssl);

/** @ingroup qapi_close_ssl_conn
 * Closes an SSL connection.
 *
 * The connection handle will be freed in this API.
 * The socket must be closed explicitly after this call. See socket QAPIs.
 *
 * @param[in] ssl SSL connection handle.
 *
 * @return
 * QAPI_OK on success. \n
 * QAPI_ERR_INVALID_PARAM_SSL on error (invalid connection handle).
 */
qapi_Status_t qapi_Net_SSL_Shutdown(qapi_Net_SSL_Con_Hdl_t ssl);

/** @ingroup qapi_free_ssl_object
 * Frees the SSL object handle.
 *
 * @param[in] hdl SSL object handle.
 *
 * @return
 * QAPI_OK on success.
 *
 * @dependencies
 * All connections belonging to this handle must be closed before calling this
 * API.
 */
qapi_Status_t qapi_Net_SSL_Obj_Free(qapi_Net_SSL_Obj_Hdl_t hdl);

/** @ingroup qapi_read_ssl_data
 * Reads data received over the SSL connection.
 *
 * @param[in] hdl Connection handle.
 * @param[in,out] buf Buffer to hold received data. Must be allocated by the application.
 * @param[in] size Size of the buffer in bytes.
 *
 * @return
 * The number of bytes available in the buffer. \n
 * QAPI_ERR_* on error.
 *
 * @dependencies
 * The SSL handshake must be completed successfully before calling this API.
 * Depending on the underlying socket associated with the SSL connection, the
 * API will be blocking/nonblocking, etc. The select API can be
 * used to check if there is any data available.
 */
qapi_Status_t qapi_Net_SSL_Read(qapi_Net_SSL_Con_Hdl_t hdl, void *buf, uint32_t size);

/** @ingroup qapi_write_ssl_data
 * Sends data over the SSL connection.
 *
 * @param[in] hdl Connection handle.
 * @param[in] buf   Buffer with the data to be sent.
 * @param[in] size  Size of buf in bytes.
 *
 * @return
 * The number of bytes sent. \n
 * QAPI_ERR_* on error.
 *
 * @dependencies
 * The SSL handshake must be completed successfully before calling this API.
 * Depending on the underlying socket associated with the SSL connection, the
 * API will be blocking/nonblocking, etc.
 */
qapi_Status_t qapi_Net_SSL_Write(qapi_Net_SSL_Con_Hdl_t hdl, void *buf, uint32_t size);

/** @ingroup qapi_does_ssl_cert_file_exist
 * Given the certificate name and type, returns
 * whether the file exists in the encrypted location.
 *
 * @param[in] file_name   Certificate file name.
 * @param[in] type        Type of SSL certificate.
 *
 * @return
 * QAPI_OK on success. \n
 * QAPI_ERR_* on error.
 *
 */
qapi_Status_t qapi_Net_SSL_Cert_File_Exists(char *file_name, qapi_Net_SSL_Cert_Type_t type);

/**
 * @versiontable{2.0,2.45,
 * Data\_Services 1.2.0  &  Introduced. @tblendline
 * }
 * @ingroup qapi_Net_SSL_Set_Extended_Config_Option
 * Set extended config option for SSL connection
 *
 * @param[in] hdl    Connection Handle.
 * @param[in] option Extended option enum.
 * @param[in] val    variable pointer for the option.
 * @param[in] len    length of val.
 *
 * @return
 * QAPI_OK on success. \n
 * QAPI_ERR_* on error.
 *
 */
qapi_Status_t qapi_Net_SSL_Set_Extended_Config_Option
(
  qapi_Net_SSL_Con_Hdl_t                 hdl ,
  qapi_Net_SSL_Extended_Config_Options_t option,
  void * val , uint32_t len
);

#endif

#endif /* _QAPI_SSL_H_ */
