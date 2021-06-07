#pragma once
#include "431Box.h"

struct COM_PORTMODE;


struct CMPHY_Relay
{
	unsigned __int8 InputChannel;
	unsigned __int8 OutputChannel;
	unsigned __int8 CANH;
	char CANL;
	unsigned __int8 CommType;
	char LogicType;
	char LevelType;
	unsigned __int8 LLine;
	unsigned __int8 Dts;
	unsigned __int8 field_9;
	unsigned __int8 field_A;
	unsigned __int8 field_B;

};




struct  CanTxMsg
{
	int StdId;
	int ExtId;
	char IDE;
	char RTR;
	char DLC;
	char Data[8];
};
typedef CanTxMsg CanRxMsg;


struct SC_CML_ISO15765
{
	volatile unsigned __int8 m_chState;
	volatile int m_nMScount;
	CanTxMsg m_chHoldDig;
	CanTxMsg m_TXM;
	CanRxMsg m_RXM;
	unsigned __int8 m_PakMode;
};



struct SC_CML_ISO14230
{
	int m_nFrameTime;
	int m_nBtyetime;
	int m_Maxwaittime;
	unsigned __int8 m_MsTime;
	char UnknowByte;
	char field_E;
	char field_F;
};


struct __declspec(align(2)) SET_LINK_KEEP
{
	unsigned __int8 linkType;
	unsigned int IdleTime;
	unsigned __int8 rightState;
	unsigned int timeCount;
	unsigned __int8 idleSendLen;
	unsigned __int8 idleRecvLen;
	unsigned __int8 dataBuf[50];
	unsigned __int8 chCount;
	unsigned __int8 linkState;
	char field_46;
};


struct SC_UserPak
{
	unsigned int PakCmdID;
	unsigned int PakLenth;
	unsigned __int8 *Pakdata;
};





typedef struct  SC_CML_KWP1281
{
	volatile unsigned __int8 m_chState;
	volatile int m_nMScount;
	int m_nFrameTime;
	int m_nBtyetime;
	int m_Idletime;
	int m_ReserveTime;
	int m_Maxwaittime;
	char m_chTemp[128];
	unsigned __int8 *m_Senddata;
	char m_chHoldDig[10];
	unsigned __int8 m_chHoldDataLen;
	unsigned __int8 m_LinkFG;
	unsigned __int8 m_Framecount;
	unsigned __int8 m_Reverse;
	volatile unsigned __int8 m_chCount;
	unsigned __int8 m_Lenth;
	unsigned __int8 m_SendFinishFlag;
	unsigned __int8 m_PakMode;
}SC_CML_KWP1281;

typedef struct  SC_PAKRECV
{
	unsigned int PakLenth;
	unsigned __int8 *PakdataAddr;
}SC_PAKRECV;


typedef struct SC_CMLISO15765ENTERFRAME
{
	unsigned __int8 dataLenth;
	unsigned char data[31];
}SC_CMLISO15765ENTERFRAME;


typedef struct SC_CMLISO15765para
{
	char CanPort;
	unsigned __int8 FilterNum;
	__int16 field_2;
	unsigned int ECUID[8];
	int Mask;
	char field_28;
}SC_CMLISO15765para;


typedef struct CAN_CONFIGPARA
{
	unsigned __int8 Badurate;
	char Mode;
	char field_2;
	char field_3;
	int *pMask;
	unsigned int *ECUID;
	unsigned __int8 FilterNum;
	char field_D[19];
	char field_20[4];
	char field_24;
	char field_25;
}CAN_CONFIGPARA;


typedef struct  SC_PAKSEND
{
	unsigned int PakLenth;
	unsigned __int8 *PakdataAddr;
}SC_PAKSEND ;




typedef struct data_info
{
	unsigned __int8 number;
	unsigned __int8 timers;
	unsigned __int8 length_pos;
	unsigned __int8 length;
	unsigned __int8 data[20];
}data_info;





void CMPHY_Relay_Init_sub_8030B62(CMPHY_Relay *SC_RelayState);
void CMPHY_Relay_Reset_sub_8030B88();
void GPIOWrite_sub_803092C();
void GPIO_WriteBit_PIN_sub_8030DBC(char a1, char a2);



//------------------------------------------------------------------------------
// Funtion: 设置回复给上位机的数据包
// Input  : data - 回复给上位机的数据
//          Ans - 回复给上位机的数据包
//          dataLenth - 数据包的长度
// Output : ans - 回复到上位机的数据
// Return : 无
// Info   :
//------------------------------------------------------------------------------
void PutDataToAns_sub_802BCBC(unsigned char * data, unsigned char * Ans, int dataLenth);
void SetGPIOGPIO_Mode_IN_sub_8031E6C(char a1);
void Delay_802EF34(int a1);
void ComClose_sub_80B1D06_sub_802FA28(char COM_ECUPORT);
void CMPHY_Relay_Set_sub_8030B94(CMPHY_Relay *SC_RelayState);
void SetCmmst462DVal_sub_802F1D8(char result);
void Givebyte_2000C64CVal_sub_80308BE(unsigned __int8 a1, char a2);
int ComOpen_sub_80B1AEC_802F7DE(char COM_ECUPORT, COM_PORTMODE *SC_com_portMode);
void SetGPIOTIM_sub_802F0D4(unsigned __int8 a1);
void IOCTRLSelect_sub_8030606(unsigned __int8 IoIndex, unsigned __int8 IoMode);
void IOCTRLSet_sub_8030658(char IOCtrl, int DelayMs);
void GPIO_PinAFConfigsub_802F062();
void TimerRelease_sub_802EF76(char index);
void SetPWMLink_sub_802C398();
void PWM_Init_sub_8032164();
BOOL PWM_Send_sub_803216E(unsigned __int8 *SendBuf, unsigned __int8 framesize, char Flag, unsigned __int8 *Addrress);
int PWM_Receive_sub_8032208(unsigned __int8 *Ans, unsigned __int8 a2, unsigned int *firstms, unsigned int a4, char a5, int a6, ...);
int VPW_Send_sub_8051862(unsigned __int8 *a1, unsigned __int8 FrameSize);
int VPW_Receive_sub_8051896(unsigned __int8 *a1, int a2, int *firstms, int a4);
void VPW_Init_sub_8051858();
int sub_80243CE(int Argc, unsigned __int8 *ArgvData, unsigned __int8 *Ans);
BOOL CanSendMsg_sub_802B874(unsigned __int8 *CmdHeaderBuf, char HeaderLen, _BYTE *CmdDataBuf);
unsigned int ReadOneFrameFromCANBuf_Ext_sub_802B550(unsigned __int8 *RcvData, char a2, unsigned __int8 *specialdata, unsigned __int8 a4, __int16 a5);
int CANUnPacket_sub_802B30C(unsigned __int8 *Buff, CanRxMsg RxMsg);
int ReceiveOneKwpFrameFromECUHasMode_sub_802C940(char recmode, unsigned __int8 *RecvBuf, unsigned int *Size, __int16 OverTime);
int GetKwpFrameBusyFlag_sub_802CAF8(unsigned __int8 *a1, unsigned __int8 *a2);
BOOL SetCanRx_sub_802D8C0(unsigned __int8 *a1);
int sub_802B6E8(unsigned __int8 *a1, int Len, unsigned __int8 *Ans, int DelayCnt);
void sub_803B704(unsigned __int8 *a1, unsigned __int8 *a2);
void sub_803B790(unsigned __int8 *a1, unsigned __int8 *a2);
void sub_803B878(unsigned __int8 *a1, unsigned __int8 *a2);
int SetTIM_sub_802F58C(__int16 a1);
unsigned int sub_802B3A6(unsigned __int8 *CmdHeadBuf, char a2, unsigned __int8 *CmdDataBuf, int a4, __int16 TimeOut, char Mode);
BOOL sub_8031CA0(CanRxMsg *RcPak, __int16 TimeOut, int a3);

int sub_802E2F6(unsigned __int8 *receive_buff, _DWORD *RcvLen, __int16 WaitTime);
unsigned int sub_803AC10(int a1, unsigned __int8 *a2, unsigned __int8 a3, int a4);
int sub_803AA2C(int a1, unsigned __int8 *a2, unsigned __int8 a3);
int sub_802E5B4(_DWORD *a1);
int sub_802E490(_DWORD *a1, unsigned __int16 a2);
int sub_802E78E(_DWORD *a1);
int sub_802E864(unsigned int *a1);
int sub_802EB50(unsigned __int8 *a1, unsigned __int16 a2);
int sub_802EA12(unsigned __int16 *a1, unsigned int *a2);
BOOL SetCan_sub_802B9DE(unsigned __int8 *CmdHeaderBuf, char HeaderLen, _BYTE *CmdDataBuf);
int sub_802E6B4(unsigned int *a14);
int sub_802EC18(unsigned __int8 *AnsBuf, _DWORD *RecvSize, __int16 OverTime, _BYTE *SpeciData);
void TimerStop_sub_802EF10(char a1);
void Copysub_802FB50(void *a1, void *a2, int Len);
void setCanbusLinkDataToken_sub_802BEB4();
int TimerConfig_sub_802EDAE(char TimeIndex, unsigned __int8 a2);
void TimerInterruptFuntionLoad_sub_802EF66(unsigned __int8 Index, int FunAddr);
void TIM_sub_802EEEC(char a1);
void SC_CML_ISO15765_Time_sub_802DFC8();
int CANRecv_sub_8031D7C(CanRxMsg *a1, __int16 DelayCnt);
BOOL SetCanFrame_sub_80319D8(CanRxMsg *CANTxMsg);
void SC_setlinkkeep_sub_802C1EC();
void ComSendByte_sub_802F1E0(unsigned int ArgvData);
int sub_802FA88();
void ComSend_sub_802F3A4(unsigned __int8 UsArtData, char Flag);
int ComByte_sub_802F6CC(unsigned __int8 *Rcv, __int16 Count);
void sendAddressToEcu_sub_802CF50(char ArgvData, unsigned int DelayMs);
void EnableLLine_1_sub_802C560();
unsigned int autoCheckBaudRate_sub_802CE7E(int DelayCnt);
void IOCTRLInit_sub_802C570();
void sendAddressToEcu_sub_802CC82(char a1);
void sendAddressToEcu_sub_802CD84(char fiveBpsAddr);
int SetRelayPara_sub_802BCD0(char a1, unsigned __int8 a2);
void SetTIMCLOCK_RCC_APB1PeriphClockCmd_sub_802ED88(int a1);
void SC_CML_KWP1281_Time_sub_802C5B0();
void ComReadSign_sub_802F614(int result);
void ComSendByteInIsr_sub_802F4BA(unsigned __int8 Framecount);
void ComInterruptFuntionLoad_sub_802F8A0(int FunAddr, unsigned __int8 a2);
void SC_CML_KWP1281_Comread_sub_802C860();
int sub_802F660();
void TIM_SetCounter_sub_802EF52(char a1);
void SC_CML_KWP1281_Comsend_sub_802C7DC();
void set_time0Stop_sub_802BB48();
int SC_CML_KWP1281_Recv_sub_802CBCC(SC_PAKRECV *pakRcv);
int SC_CML_KWP1281_Sendsub_802CB36(SC_PAKSEND *pakSend);
BOOL checkXOR_Parity_sub_802BD40(int a1, unsigned __int8 *dataPos);
int SetLinkData_2_sub_804C77E(int a1, unsigned __int8 *Argv, unsigned __int8 *Ans);
int GiveValToA1CANPack_sub_802BD62(unsigned __int8 *a1, unsigned __int8 a2);
void CAN_SetLink_sub_802E0D4();
BOOL SetCanFrame_sub_8031B58(CanRxMsg *CANTxMsg);
int CheckLLine_sub_802C580();
void GPIO_WriteBit_Delay_sub_803069E(char a1, char a2, unsigned int a3);
void SetSysTickLOAD_sub_8031144(unsigned int result);
void Delay_sub_8031194();
void Set2000C6BF_is_1_sub_8030D78();
void Set2000C6BF_is_1_sub_8030D70();
BOOL IOCTRLGet_sub_80306E2();
void KeepLinkFrameSet_sub_802BF9E();
void TImCANLinkSend_sub_802E040();
void SC_setlinkkeep_sub_802C444();
int GetSeries_Ver_sub_8040000(char a1, unsigned __int8 *SeriesBuf, unsigned __int16 SeriesLen);
int SysTick_Config_sub_80311BE();
uint32_t GetDelayTim_sub_803112E();
void GPIO_PINAFConfig_RCCSet_sub_802EFE0();
int AboutSysTicksub_8030788(char a1, unsigned int a2);
int Delay_WaitIoSetLow_sub_802E440(unsigned int *DelayAllTime, unsigned __int16 DelayCnt);
void AboutSysTicksub_803120C(unsigned int a1);
int Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(unsigned int *DelayTime, unsigned __int16 OnceTimes);
int Delay_WaitIoSetLow_sub_802E396(unsigned int *a1, unsigned __int16 OnceTimes);
int LowHighSet_sub_802E4E0(_DWORD *DelayTime);
int Delay_OpenPort_sub_802DE94(int DelayTime, int a2, char a3);
BOOL sub_802E980(_BYTE *RcvData);
BOOL JudgeHighAndLowCnt_sub_802E938(unsigned __int16 a1);
int CheckIoBusy_sub_802DF38(int a1, int a2, char a3);
int setCanbusNormalDataToken_sub_802DD42(unsigned __int8 *DataPos);
void SetCANFilter_sub_802D4D4(unsigned __int8 *dataPos);
int CANOpen_sub_8031530(char CANPort, CAN_CONFIGPARA *PHY_CAN_SetPara);
void SetCanBaudRate_sub_802D86C(unsigned __int8 *buff);
void SetCanCommunicatioIO_sub_802D810(unsigned __int8 *dataPos);
void sub_802DA40();
void KWP2000_Time_sub_802DABE();
void sub_802DC20(unsigned __int8 *a1);
BOOL sub_802D942(unsigned __int8 *a1);
BOOL SetCanFrame_sub_802DC44(unsigned __int8 *DataPos);
void SetCanMaskFilterID_sub_802D2AC(unsigned __int8 *DataPos, unsigned __int8 FilterNum);
void SetCanDataFrameReceiveMode_sub_802D744(unsigned __int8 *DataPos);
void Can_sub_803289A(char canport);
int SetCan_sub_80327A2(char CANPort, unsigned int CANID, unsigned int FilterID, char CANMode);
int sub_802D03C(_BYTE *a1);
int CalculateTimeOut_sub_802CC3E(unsigned int a1, unsigned int a2);