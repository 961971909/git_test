/*! @file
********************************************************************************
<PRE>
模块名       : 485通讯处理任务模块
文件名       : taskRS232.h
相关文件     :
文件实现功能 : 通讯处理
作者         : < 、>
版本         : 1.0
--------------------------------------------------------------------------------
备注         :
--------------------------------------------------------------------------------
修改记录 :
日 期        版本   修改人         修改内容
2017/03/22   1.0    < 、>           创建
</PRE>
********************************************************************************

  * 版权所有(c) YYYY, <xxx>, 保留所有权利

*******************************************************************************/


#ifndef _TASKRS232_H
#define _TASKRS232_H


/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
#define ADDR_ALL                0xEE
#define ADDR_PC                 0xEF
#define RTU_ADDR_ALL            0xFA
#define RTU_ADDR_PC             0xFE
#define RX_SUBCOM_LEN           64
#define TX_SUBCOM_LEN           128

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/*------ 校表 ------*/
typedef struct
{
    u8 Start1;               // 帧起始符
    u8 Addr1;                // 发送方地址
    u8 Addr2;                // 接收方地址
    u8 Start2;               // 帧起始符
    u8 CtrlCode;             // 控制码
    u16 Len;                 // 数据长度
    u8 Cmd;                  // 命令码
    u8 Data[TX_SUBCOM_LEN];  // 数据域
    u8 CS;                   // 校验
}MSSendPackStruct;

// 接收数据结构
typedef struct
{
    u8 Start1;               // 帧起始符
    u8 Addr1;                // 发送方地址
    u8 Addr2;                // 接收方地址
    u8 Start2;               // 帧起始符
    u8 CtrlCode;             // 控制码
    u16 Len;                 // 数据长度
    u8 Cmd;                  // 命令码
    u8 Data[RX_SUBCOM_LEN];  // 数据地址
    u8 byCS;                 // 校验
}MSRecvPackStruct;

/*------ rtu ------*/
typedef struct
{
    u8 RTU_Addr;                 // 仪表地址
    u8 RTU_Func;                 // 功能码
    u16 RTU_DsAddr;              // 起始地址
    u16 RTU_DsData;               // 字节长度 动作值
    u16 RTU_DsNum;
    u8 RTU_DataNum;              //
    u8 RTU_DataLen;              //
    u8 RTU_Data;
    u8 Data[TX_SUBCOM_LEN];     // 数据域
    u16 RtuCRC;                 // 校验
}RtuSendPackStruct;

// 接收数据结构
typedef struct
{
    u8 RR_Addr;                 // 仪表地址
    u8 RR_Func;                 // 功能码
    u16 RR_DsAddr;              // 起始地址
    u16 RR_DsNum;               // 字节长度 动作值
    u8 RR_DataNum;              //
    u8 RR_DataLen;              //
    u8 RR_Data;
    u8 Data[RX_SUBCOM_LEN];  // 数据地址
    u16 RR_CRC;                 // 校验
}RtuRecvPackStruct;

typedef struct
{
    u8 Cmd;
    u8 Phase;
    u8 Data[64];
}AdjustMsgStruct;


/* Exported functions ------------------------------------------------------- */
void Task_RS232_init(void);
void Task_RS232_Function(void);
BOOL vMSRS232_RxProtocol(void);
void vModeBus_Query_Primary_HarmI(void);

#endif /* _TASKRS232_H */

//===========================================================================
// No more.
//===========================================================================


