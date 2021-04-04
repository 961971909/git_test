/*! @file
********************************************************************************
<PRE>
模块�?      : 硬件驱动模块
文件�?      : drvI2C.h
相关文件     :
文件实现功能 : I2C总线驱动
作�?        : <--->
版本         : 1.0
--------------------------------------------------------------------------------
备注         :
--------------------------------------------------------------------------------
修改记录 :
�?�?       版本   修改�?        修改内容
2010/10/05   1.0    <xxxx>         创建
</PRE>
********************************************************************************

  * 版权所�?c) YYYY, <xxx>, 保留所有权�?

*******************************************************************************/

#ifndef _RN8302B_H
#define _RN8302B_H

/* Includes ------------------------------------------------------------------*/
#include "Macro.h"
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define RO                                      0x00
#define RW                                      0x01
#define bank0                                   0x00
#define bank1                                   0x01
#define bank2                                   0x02
#define bank3                                   0x03
#define bank4                                   0x04
#define WRENABLE                                0xE5
#define WRDISABLE                               0xDC
#define SAMPTEMPCLR                             0x10                // 50Hz采样，缓冲区清零
#define CLREMMIFH                               0xFF                // 清采样缓冲中断标�?
#define CLREMMIFL                               0xFF
#define SAMPSTART                               0x20
#define SOFTRST                                 0xFA
#define EMMOD                                   0xA2                // EMM模式
#define SLPMOD                                  0x18
#define NVM1MOD                                 0xE1
#define NVM2MOD                                 0x5C
#define CHANNELEN                               0xFF
#define ADCGAINVAL                              0x00                //ADC 通道增益设定。电压通道1倍增益�?
//#define HF6400                            0x031F                        //6400常数
#define EGYRDMODVAL                             0x40                //视在电能读取后清零�?
#define LNWIREMODE                              0x00        //三相四线接线模式�?
#define LLWIREMODE                              0x33        //三相三线接线模式�?
#define GAIN_1                                  0x00
//#define GAIN_2                                  0x01
//#define GAIN_4                                  0x10
//#define GAIN_8                                  0x11
#define CALIB_UIE                               0xb0
#define CALIB_ANGLE                             0xe8        //??
#define CALIB_IOFFSET                           0x1f        // 电流offset 校正
#define CALIB_SECTION_I                         0xa0        //设置电流分段
#define CALIB_AnoPwm                            0xc0        //设置模拟#量校�?
#define CALIB_SetPwm							0xc1
#define CALIB_SET_DEFAULT                       0xf9
#define CALIB_SET_ZERO                          0x04
#define CALIB_WRITEDATA                         0x05
//#define HFCONST1                                      0x39
//#define HFCONST0                                      0x07                        //测试常数
//#define HFCONST1                                      0xCE


// 一次侧采样数据
__packed typedef struct
{
    // 单位:0.01V
    float U;          // 电压
    // 单位:0.01V
    float UH;         // 谐波电压
    // 单位:0.01V
    float LineU;      // 线电�?
    // 单位:0.0001A
    float I;          // 电流
    // 单位:0.0001A
    float IH;         // 谐波电流
    float FI;         // 
    // 单位:0.00001kW=0.1w
    float P;          // 有功功率
    // 单位:0.00001kvar
    float Q;          // 无功功率
    // 单位:0.00001kVA
    float S;          // 视在功率
    // 单位:0.001
    float PF;         // 功率因数
    // 单位:0.1
    float U_Phase;    // 电压相角
    // 单位:0.1
    float I_Phase;    // 电流相角
    // 单位:0.1
    float THDU;       // 谐波畸变�?
    // 单位:0.1
    float THDI;       // 谐波畸变�?
}POWER_Real2_ValStruct;

__packed typedef struct
{
    POWER_Real2_ValStruct Real2_Val[PH_TH];

    float Pt;
    float Qt;
    float St;
    float PFTA;
    float Uavr;
    float ULavr;
    float Iavr;
    float Usum;
    float ULsum;
    float Isum;
    float PosEPT;
    float PosEQT;
    float EPT;
    float EQT;
    float Freq;
}POWER2_ValStruct;


// 二次侧采样数�?
__packed typedef struct
{
    // 单位:0.01V
    int U;              // 相电�?
    // 单位:0.01V
    int UH;             // 谐波电压
    // 单位:0.01V
    int LineU;          // 线电�?
    // 单位:0.0001A
    int I;              // 相电�?
    // 单位:0.0001A
    int IH;             // 谐波电流
    // 单位:0.00001kW=0.1w
    int P;              // 有功功率
    // 单位:0.00001kvar
    int Q;              // 无功功率
    // 单位:0.00001kVA
    int S;              // 视在功率
    // 单位:0.001
    int PF;             // 功率因数
    // 单位:0.1
    int U_Phase;        // 电压相角
    // 单位:0.1
    int I_Phase;        // 电流相角
    // 单位:0.1
    int THDU;           // 谐波畸变�?
    // 单位:0.1
    int THDI;           // 谐波畸变�?
}POWER_Real22_ValStruct;

__packed typedef struct
{
    POWER_Real22_ValStruct Real22_Val[PH_TH];

    int Pt;
    int Qt;
    int St;
    int PFTA;
    int Uavr;
    int ULavr;
    int Iavr;
    int Usum;
    int ULsum;
    int Isum;
    int Io;
    int Pavr;
    int Qavr;
    int Savr;
    int U_Imb;
    int I_Imb;
    int PosEPT;
    int PosEQT;
    int EPT;
    int EQT;
    int Freq;
    int UTHavr;
    int ITHavr;
}POWER22_ValStruct;


// 交流采样数据(读取数据�?
__packed typedef struct
{
    //单位:0.01V
    u16 U;          //二次侧电�?AC
    //单位:0.0001A
    u32 I;          //二次侧电�?B
    //单位:0.00001kW=0.1w
    s32 P;          //二次侧有功功�?A/B/C/�?
    //单位:0.00001kvar
    s32 Q;          //二次侧无功功�?A/B/C/�?
    //单位:0.00001kVA
    u32 S;          //二次侧视在功�?
    //单位:0.001
    u16 PF;         //功率因数�?
}POWER_Read_ValStruct;

// 校表可读
__packed typedef struct
{
    POWER_Read_ValStruct Real_Read_Val[PH_TH];

}POWER2_Read_ValStruct;


typedef struct
{
    unsigned char bank;
    unsigned char addr;
    unsigned char bytenum;
    unsigned char rw;
    unsigned int  data;
} RegStructure;

// rn8302b 配置
typedef struct
{
    RegStructure        Ua_wave;
    RegStructure        Ub_wave;
    RegStructure        Uc_wave;
    RegStructure        Ia_wave;
    RegStructure        Ib_wave;
    RegStructure        Ic_wave;
    RegStructure        In_wave;
    RegStructure        U[3];
    RegStructure        USum_vector;
    RegStructure        I[3];
    RegStructure        In;
    RegStructure        Reserved1;
    RegStructure        ISum_vector;
//    RegStructure        Ia_NVM1;
//    RegStructure        Ib_NVM1;
//    RegStructure        Ic_NVM1;
    RegStructure        P[3];
    RegStructure        Pt;
    RegStructure        Q[3];
    RegStructure        Qt;
    RegStructure        S[3];
    RegStructure        St;
    RegStructure        Pf[3];
    RegStructure        Pft;
//    RegStructure        PAfCnt;
//    RegStructure        PBfCnt;
//    RegStructure        PCfCnt;
//    RegStructure        PTfCnt;
//    RegStructure        QAfCnt;
//    RegStructure        QBfCnt;
//    RegStructure        QCfCnt;
//    RegStructure        QTfCnt;
//    RegStructure        SAfCnt;
//    RegStructure        SBfCnt;
//    RegStructure        SCfCnt;
//    RegStructure        STfCnt;
//    RegStructure        EPa;
//    RegStructure        EPb;
//    RegStructure        EPc;
    RegStructure        EPt;
//    RegStructure        PosEPa;
//    RegStructure        PosEPb;
//    RegStructure        PosEPc;
    RegStructure        PosEPt;
//    RegStructure        NegEPa;
//    RegStructure        NegEPb;
//    RegStructure        NegEPc;
    RegStructure        NegEPt;
//    RegStructure        EQa;
//    RegStructure        EQb;
//    RegStructure        EQc;
    RegStructure        EQt;
//    RegStructure        PosEQa;
//    RegStructure        PosEQb;
//    RegStructure        PosEQc;
    RegStructure        PosEQt;
//    RegStructure        NegEQa;
//    RegStructure        NegEQb;
//    RegStructure        NegEQc;
    RegStructure        NegEQt;
//    RegStructure        ESa;
//    RegStructure        ESb;
//    RegStructure        ESc;
//    RegStructure        ESt;
//    RegStructure        STV;
//    RegStructure        PfTV;
//    RegStructure            STFVCnt;
//    RegStructure        ESTV;
} Full_wave_data;
//???????????
typedef struct
{

    RegStructure        YU[3];
    RegStructure        YI[3];
    RegStructure        YIn;
    RegStructure        UFrequence;
    RegStructure        FU[3];
    RegStructure        FI[3];
    RegStructure        FPa;
    RegStructure        FPb;
    RegStructure        FPc;
    RegStructure        FPt;
    RegStructure        FQa;
    RegStructure        FQb;
    RegStructure        FQc;
    RegStructure        FQt;
    RegStructure        FSa;
    RegStructure        FSb;
    RegStructure        FSc;
    RegStructure        FSt;
    RegStructure        FPfa;
    RegStructure        FPfb;
    RegStructure        FPfc;
    RegStructure        FPft;
//    RegStructure        FPAFCnt;
//    RegStructure        FPBFCnt;
//    RegStructure        FPCFCnt;
//    RegStructure        FPTFCnt;
//    RegStructure        FQAFCnt;
//    RegStructure        FQBFCnt;
//    RegStructure        FQCFCnt;
//    RegStructure        FQTFCnt;
//    RegStructure        FSAFCnt;
//    RegStructure        FSBFCnt;
//    RegStructure        FSCFCnt;
//    RegStructure        FSTFCnt;
//    RegStructure        FEPa;
//    RegStructure        FEPb;
//    RegStructure        FEPc;
    RegStructure        FEPt;
//    RegStructure        PoSFEPa;
//    RegStructure        PoSFEPb;
//    RegStructure        PoSFEPc;
//    RegStructure        PoSFEPt;
//    RegStructure        NegFEPa;
//    RegStructure        NegFEPb;
//    RegStructure        NegFEPc;
//    RegStructure        NegFEPt;
//    RegStructure        FEQa;
//    RegStructure        FEQb;
//    RegStructure        FEQc;
    RegStructure        FEQt;
//    RegStructure        PoSFEQa;
//    RegStructure        PoSFEQb;
//    RegStructure        PoSFEQc;
//    RegStructure        PoSFEQt;
//    RegStructure        NegFEQa;
//    RegStructure        NegFEQb;
//    RegStructure        NegFEQc;
//    RegStructure        NegFEQt;
//    RegStructure        FESa;
//    RegStructure        FESb;
//    RegStructure        FESc;
//    RegStructure        FESt;
    RegStructure        HU[3];
    RegStructure        HI[3];
//    RegStructure        FSTV;
//    RegStructure        FPfTV;
//    RegStructure        FSTVFCnt;
//    RegStructure        FESTV;
} Fundamental_wave_data;

//????????
typedef struct
{
    RegStructure        HFConst1;
    RegStructure        HFConst2;
    RegStructure        IStart_PS;
    RegStructure        IStart_Q;
    RegStructure        LostVoltT;
    RegStructure        ZXOT;
    RegStructure        PRTH1L;   // ·???D�?y
    RegStructure        PRTH1H;
    RegStructure        PRTH2L;
    RegStructure        PRTH2H;
//    RegStructure        IRegion3L;
//    RegStructure        IRegion3H;
    RegStructure        PHSU[3];
    RegStructure        PHSI[3];
    RegStructure        PHSIN;
    RegStructure        GSU[3];
    RegStructure        GSI[3];
    RegStructure        GSIN;
//    RegStructure        DCOS_UA;
//    RegStructure        DCOS_UB;
//    RegStructure        DCOS_UC;
//    RegStructure        DCOS_IA;
//    RegStructure        DCOS_IB;
//    RegStructure        DCOS_IC;
//    RegStructure        DCOS_IN;
//    RegStructure        UA_OS;
//    RegStructure        UB_OS;
//    RegStructure        UC_OS;
    RegStructure        I_OS[3];
//    RegStructure        IN_OS;
//    RegStructure        GP[3];
//    RegStructure        GQ[3];
//    RegStructure        GS[3];
    RegStructure        P_PHSL[3];
    RegStructure        Q_PHSL[3];
//    RegStructure        PA_OS;
//    RegStructure        PB_OS;
//    RegStructure        PC_OS;
//    RegStructure        QA_OS;
//    RegStructure        QB_OS;
//    RegStructure        QC_OS;
//    RegStructure        FUA_OS;
//    RegStructure        FUB_OS;
//    RegStructure        FUC_OS;
//    RegStructure        FIA_OS;
//    RegStructure        FIB_OS;
//    RegStructure        FIC_OS;
//    RegStructure        GFPA;
//    RegStructure        GFPB;
//    RegStructure        GFPC;
//    RegStructure        GFQA;
//    RegStructure        GFQB;
//    RegStructure        GFQC;
//    RegStructure        GFSA;
//    RegStructure        GFSB;
//    RegStructure        GFSC;
//    RegStructure        FPA_PHS;
//    RegStructure        FPB_PHS;
//    RegStructure        FPC_PHS;
//    RegStructure        FQA_PHS;
//    RegStructure        FQB_PHS;
//    RegStructure        FQC_PHS;
//    RegStructure        FPA_OS;
//    RegStructure        FPB_OS;
//    RegStructure        FPC_OS;
//    RegStructure        FQA_OS;
//    RegStructure        FQB_OS;
//    RegStructure        FQC_OS;
//    RegStructure        SAGCFG;
//    RegStructure        OVLVL;
//    RegStructure        OILVL;
    RegStructure        CFCFG;
    RegStructure        EMUCFG;
    RegStructure        EMUCON;
    RegStructure        WSAVECON;
    RegStructure        EMMIE;
    RegStructure        EMMIF;
    RegStructure        PQSign;
    RegStructure        Noload;
    RegStructure        IRegionS;
    RegStructure        PHASES;
    RegStructure        CheckSum1;
//    RegStructure        NVM1CFG;
//    RegStructure        NVM1IF;
//    RegStructure        NVM2CFG;
//    RegStructure        NVM2CMPA;
//    RegStructure        NVM2CMPB;
//    RegStructure        NVM2CMPC;
//    RegStructure        NVM2IF;
    RegStructure        WREN;
    RegStructure        WMSW;
    RegStructure        SOFT_RST;
    RegStructure        ADCREG;
    RegStructure        MODSEL;
    RegStructure        SYSSR;
    RegStructure        CheckSum2 ;
    RegStructure        RData;
    RegStructure        WData;
    RegStructure        LRBufAddr;
    RegStructure        DeciceID;
    RegStructure        AUOTDC_EN;
    RegStructure        IN_WaveEN;
    RegStructure        PA_PHSM;
    RegStructure        PA_PHSH;
    RegStructure        PB_PHSM;
    RegStructure        PB_PHSH;
    RegStructure        PC_PHSM;
    RegStructure        PC_PHSH;
    RegStructure        QA_PHSM;
    RegStructure        QA_PHSH;
    RegStructure        QB_PHSM;
    RegStructure        QB_PHSH;
    RegStructure        QC_PHSM;
    RegStructure        QC_PHSH;
} Config_Stutas_REG;


struct RN_Coefficient
{
    unsigned short HFConst1;
    unsigned short HFConst2;
    unsigned short IStart_PS;
    unsigned short IStart_Q;
    unsigned short LostVoltT;
    unsigned short ZXOT;
    short GSUA;
    short GSUB;
    short GSUC;
    short GSIA;
    short GSIB;
    short GSIC;
    unsigned int PHSIA;
    unsigned int PHSIB;
    unsigned int PHSIC;
    unsigned int PA_PHSL;
    unsigned int PB_PHSL;
    unsigned int PC_PHSL;
};

/*
struct RN_AnalogData
{
    unsigned int    wDataUa;
    unsigned int    wDataUb;
    unsigned int    wDataUc;
    unsigned int    wDataIa;
    unsigned int    wDataIb;
    unsigned int    wDataIc;
    unsigned int    wDataIn;
    unsigned int    wDataPa;
    unsigned int    wDataPb;
    unsigned int    wDataPc;
    unsigned int    wDataQa;
    unsigned int    wDataQb;
    unsigned int    wDataQc;
    unsigned int    wDataSa;
    unsigned int    wDataSb;
    unsigned int    wDataSc;
    unsigned int    wDataPfa;
    unsigned int    wDataPfb;
    unsigned int    wDataPfc;
    unsigned int    wDataP;
    unsigned int    wDataQ;
    unsigned int    wDataS;
    unsigned int    wDataPF;
    unsigned int    wDataEPa;
    unsigned int    wDataEPb;
    unsigned int    wDataEPc;
    unsigned int    wDataEPt;
    unsigned int    wDataPosEPa;
    unsigned int    wDataPosEPb;
    unsigned int    wDataPosEPc;
    unsigned int    wDataPosEPt;
    unsigned int    wDataNegEPa;
    unsigned int    wDataNegEPb;
    unsigned int    wDataNegEPc;
    unsigned int    wDataNegEPt;
    unsigned int    wDataEQa;
    unsigned int    wDataEQb;
    unsigned int    wDataEQc;
    unsigned int    wDataEQt;
    unsigned int    wDataPosEQa;
    unsigned int    wDataPosEQb;
    unsigned int    wDataPosEQc;
    unsigned int    wDataPosEQt;
    unsigned int    wDataNegEQa;
    unsigned int    wDataNegEQb;
    unsigned int    wDataNegEQc;
    unsigned int    wDataNegEQt;
    unsigned int    wDataESa;
    unsigned int    wDataESb;
    unsigned int    wDataESc;
    unsigned int    wDataESt;
    unsigned int    wDataSTV;
    unsigned int    wDataPfTV;
    unsigned int    wDataESTV;
    unsigned int    wData3U0;
    unsigned int    wData3I0;
    unsigned int    wDataYUa;
    unsigned int    wDataYUb;
    unsigned int    wDataYUc;
    unsigned int    wDataYIa;
    unsigned int    wDataYIb;
    unsigned int    wDataYIc;
    unsigned int    wDataYIn;
    unsigned int    wDataF;
    unsigned int    wDataFUa;
    unsigned int    wDataFUb;
    unsigned int    wDataFUc;
    unsigned int    wDataFIa;
    unsigned int    wDataFIb;
    unsigned int    wDataFIc;
    unsigned int    wDataFPa;
    unsigned int    wDataFPb;
    unsigned int    wDataFPc;
    unsigned int    wDataFPt;
    unsigned int    wDataFQa;
    unsigned int    wDataFQb;
    unsigned int    wDataFQc;
    unsigned int    wDataFQt;
    unsigned int    wDataFSa;
    unsigned int    wDataFSb;
    unsigned int    wDataFSc;
    unsigned int    wDataFSt;
    unsigned int    wDataFPfa;
    unsigned int    wDataFPfb;
    unsigned int    wDataFPfc;
    unsigned int    wDataFPft;
    unsigned int    wDataFEPa;
    unsigned int    wDataFEPb;
    unsigned int    wDataFEPc;
    unsigned int    wDataFEPt;
    unsigned int    wDataPoSFEPa;
    unsigned int    wDataPoSFEPb;
    unsigned int    wDataPoSFEPc;
    unsigned int    wDataPoSFEPt;
    unsigned int    wDataNegFEPa;
    unsigned int    wDataNegFEPb;
    unsigned int    wDataNegFEPc;
    unsigned int    wDataNegFEPt;
    unsigned int    wDataFEQa;
    unsigned int    wDataFEQb;
    unsigned int    wDataFEQc;
    unsigned int    wDataFEQt;
    unsigned int    wDataPoSFEQa;
    unsigned int    wDataPoSFEQb;
    unsigned int    wDataPoSFEQc;
    unsigned int    wDataPoSFEQt;
    unsigned int    wDataNegFEQa;
    unsigned int    wDataNegFEQb;
    unsigned int    wDataNegFEQc;
    unsigned int    wDataNegFEQt;
    unsigned int    wDataFESa;
    unsigned int    wDataFESb;
    unsigned int    wDataFESc;
    unsigned int    wDataFESt;
    //????
    unsigned int    wDataHUa;
    unsigned int    wDataHUb;
    unsigned int    wDataHUc;
    unsigned int    wDataHIa;
    unsigned int    wDataHIb;
    unsigned int    wDataHIc;
    unsigned int    wDataFSTV;
    unsigned int    wDataFPfTV;
    unsigned int    wDataFESTV;
};*/

/* Exported functions ------------------------------------------------------- */

extern int Phase_U[3];
extern int Phase_I[3];

extern POWER2_ValStruct vg_Power_Val;
extern POWER22_ValStruct vg_Power2_Val;
extern POWER2_Read_ValStruct vg_Read_Val;
extern u32 CheckSum;
extern u8 RN8302RDBUFF(u16 addr, u8 *pReadWaveData);
extern void bsp_InitRN8023(void);
extern void RN8032_Adjust(u8 Cmd, u8 Phase, u8 *pAdjustData);
void Task_Power_Function(void);
/*RN8302??????*/
extern void RN8032_Updata(void);

#define NUM_FFT 128 // Length of FFT to process
//#define PI 3.1415926

typedef struct
{
	float iRealArray[NUM_FFT];
	float iMageArray[NUM_FFT];
	u16	FU[3];			//---?ù2¨μ??1---NNN.N6
	u32	FI[4];			//---?ù2¨μ?á÷NNNN.NNNN
	float HarmonicpercentU[3][51];
	float HarmonicpercentI[3][51];			//---D32¨o?óD?ê--NNN.N6
	float HarmonicCurrent[3][32];
}sDl645FftHarmonicData_TypeDef;

typedef struct
{
    u8  Channel;					 // μ±?°2é?ùí¨μà
    u16  ReadAdress;				 // ?áè?μ??·
    u8  StarFlag;					 // ?aê???DDD32¨êy?Y·???
    u8  ADSPIBusy;					 // ??DDD32¨·????2ê±?μêy?Y2é?ù
    u16 DataCount;					 // μ±?°2é?ùμ?êy
    u16 ReadAddres;				 	 // 2é?ùμ?êy?Yμ??·
    u16	dwFreq;					 	 // 2é?ù?ü?úμ±?°?μ?ê
    u16 TimeOutStamp;				 // 2é?ù?óê±í?3?
    u8 InstantaneousData[384];      // μ±?°2é?ù128μ??2ê±êy?Y
}sADE_Instantaneous_TypeDef;

typedef enum
{
	UAChannel		= 0x00,
	UBChannel		= 0x01,
	UCChannel		= 0x02,
	IAChannel		= 0x03,
	IBChannel		= 0x04,
	ICChannel		= 0x05
}eADEChannelFlag_TypeDef;

extern BOOL FFTEnble;
extern sDl645FftHarmonicData_TypeDef HarmonicData;
extern void fnDl645Fft_Harmonic_Exec(void);
extern void fnDl645Fft_init(void);
extern void Int_FFT(s16 ReArray[], s16 ImArray[]);
extern void Bit_Reverse(s16 BR_Array[]);

#endif /* _DRVI2C_H */

//===========================================================================
// No more.
//===========================================================================


