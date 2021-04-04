/*! @file
********************************************************************************
<PRE>
ģ����       : 485ͨѶ��������ģ��
�ļ���       : taskRS232.h
����ļ�     :
�ļ�ʵ�ֹ��� : ͨѶ����
����         : < ��>
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         :
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2017/03/22   1.0    < ��>           ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

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
/*------ У�� ------*/
typedef struct
{
    u8 Start1;               // ֡��ʼ��
    u8 Addr1;                // ���ͷ���ַ
    u8 Addr2;                // ���շ���ַ
    u8 Start2;               // ֡��ʼ��
    u8 CtrlCode;             // ������
    u16 Len;                 // ���ݳ���
    u8 Cmd;                  // ������
    u8 Data[TX_SUBCOM_LEN];  // ������
    u8 CS;                   // У��
}MSSendPackStruct;

// �������ݽṹ
typedef struct
{
    u8 Start1;               // ֡��ʼ��
    u8 Addr1;                // ���ͷ���ַ
    u8 Addr2;                // ���շ���ַ
    u8 Start2;               // ֡��ʼ��
    u8 CtrlCode;             // ������
    u16 Len;                 // ���ݳ���
    u8 Cmd;                  // ������
    u8 Data[RX_SUBCOM_LEN];  // ���ݵ�ַ
    u8 byCS;                 // У��
}MSRecvPackStruct;

/*------ rtu ------*/
typedef struct
{
    u8 RTU_Addr;                 // �Ǳ��ַ
    u8 RTU_Func;                 // ������
    u16 RTU_DsAddr;              // ��ʼ��ַ
    u16 RTU_DsData;               // �ֽڳ��� ����ֵ
    u16 RTU_DsNum;
    u8 RTU_DataNum;              //
    u8 RTU_DataLen;              //
    u8 RTU_Data;
    u8 Data[TX_SUBCOM_LEN];     // ������
    u16 RtuCRC;                 // У��
}RtuSendPackStruct;

// �������ݽṹ
typedef struct
{
    u8 RR_Addr;                 // �Ǳ��ַ
    u8 RR_Func;                 // ������
    u16 RR_DsAddr;              // ��ʼ��ַ
    u16 RR_DsNum;               // �ֽڳ��� ����ֵ
    u8 RR_DataNum;              //
    u8 RR_DataLen;              //
    u8 RR_Data;
    u8 Data[RX_SUBCOM_LEN];  // ���ݵ�ַ
    u16 RR_CRC;                 // У��
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


