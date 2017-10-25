#ifndef __SP_CONN_PARA__
#define __SP_CONN_PARA__

#include "meta.h"

typedef struct
{
    int                    com_port;
    META_COMM_BAUDRATE     baudrate[12];       /**< [META] META stage baudrate polling array, it must end with META_BAUD_END. */
    BOOT_META_ARG          boot_meta_arg;      /**< [BootROM] please refer to brom.h */
    unsigned int           ms_connect_timeout; /**< [META] META stage sync timeout value (after BootROM negotiation pass) */
    unsigned int           usb_enable: 1;      /**< [META] Connect target with UART or USB, 0: UART 1: USB others:reserved */
    unsigned int           InMetaMode: 1;      /**< [META] Decide that need boot META or not 0:need boot META 1:already in meta mode */
    META_MODE_TRACE_PARA_T trace_para;         /**< [META] META mode trace parameters */
    bool                   usb_auto_detec;     /**< [META] USB auto detection selection */
    bool                   secure_boot;        /**< [META] Selection of secure boot */
} SP_Conn_Para;

typedef struct
{
    SP_Conn_Para input_para;
    SP_BOOT_ARG_S* sp_boot_arg;
    int* boot_stop;
} SP_Conn_Input;

typedef struct
{
    bool b_shutdown;
    bool b_backup;
} SP_Disconn_Input;

#endif