#include "stdafx.h"
#include "431Box.h"
#include "stm32F2xx.h"
#include "FUN_Base.h"
#include "SC_cmdfunc.h"

extern unsigned char szFNG_20004A08[4];
extern unsigned char szFOK_20004A04[4];
extern unsigned char szFBREAK_20004A0C[4];
extern unsigned char szFNOWAIT[4];
extern CMPHY_Relay SC_RelayState_200049DC;
extern SC_CML_ISO15765 SC_TagISO15765_2000C334;
extern SC_CML_ISO14230 SC_TagKWP2000_20004974;
extern SET_LINK_KEEP Keep_Link_200046C0;
extern unsigned __int8 timer_open_flag_2000C6B7;
extern COM_PORTMODE SC_com_portMode_20004964;
extern SC_CML_KWP1281 SC_TagKWP1281_200043E4;
extern unsigned char receive_buff_2000BF20[261];
extern char byte_2000C6BB;
extern unsigned __int8 SendPakdataPackData_2000BDF4[100];
extern char unk_2000C6BF; 
extern SC_CMLISO15765ENTERFRAME CanEnterFrame_2000C47C;
unsigned int position_804D764[10] = { 0xE1E1E1E1, 0xE5E4E3E2, 0xE9E8E7E6, 0xEDECEBEA, 0xD2D1EFEE
,0xD6D5D4D3, 0xDAD9D8D7, 0xDEDDDCDB, 0xB3B2B1DF, 0xB5B4 };
extern char ucCan30ConfigMode_2000C6BD;
extern unsigned char aV1168[8];
extern int dword_2000C668;
extern char unk_2000C6B9;
extern char kwp2000m_nBtyetime_2000C540;
extern char TimeOut_2000C530;
extern int dword_2000C538;
extern int FrameTime_2000C534;
extern int DelayTime_2000C53C;
GPIO_TypeDef GPIOB_BASE_40020400;
extern CAN_TypeDef CAN1_BASE_40006400;
extern CAN_TypeDef CAN2_BASE_40006800;
extern USART_TypeDef *USART1;
extern USART_TypeDef *USART2;
extern SC_CMLISO15765para CAN_SetPara_2000C2F0;
extern unsigned __int8 specialdata_2000C670[4];
extern CAN_CONFIGPARA PHY_CAN_SetPara_20004984;
extern unsigned __int8 CmdBuf_2000C554[20];
extern unsigned char ExitFlag_2000C6BA;//盒子退出接收上位机通讯标识

extern unsigned char*pGetDataFlag ;//串口数据中断过来会改变这个指针地址的值 是一个有数据过来的标识
extern unsigned __int8 BackPhoneBlueTH_20008E3C[256];//返回给上位机的数据

extern unsigned int DataGroupNum_2000C67C;//接收串口数据有几组 一串数据可能会被分成几次处理 以6x xx xx 6x xx 的这类数据
extern unsigned char BlueThBuf_200078C1[300];
extern unsigned char byte_2000B8E4[300];
extern char CheckSuccessFlag;
extern unsigned int dword_804F3EC[5];
extern char byte_2000C6BB;
extern pfnCmdLine g_sCmdTable_200040E4[3][0x30];

unsigned __int8 byte_803AFD0[8] = { 0x88, 0xC7, 0x60, 7, 0xC8, 0, 0, 0 };

unsigned __int8 byte_803AFD8[8] = { 0x88, 0xC7, 0x78, 7, 0xC8, 0, 0, 0 };

unsigned __int8 byte_803AFE0[8] = { 0x88, 0xC7, 0x58, 7, 0xC8, 0, 0, 0 };

unsigned __int8 byte_803AFE8[16] = { 0x88, 0xE7, 0x60, 7, 0xC8, 0x11, 2, 1, 0xFF, 0xFF, 0, 0xEF, 0, 0, 0, 0 };

unsigned int byte_803B290[16] = { 0x88, 0xE7, 0x60, 7, 0xC8, 0x13, 9, 9, 2, 0xFF, 0, 0xEF, 0, 0, 0, 0 };

unsigned char byte_802B14C[28] = { 0x18, 0, 1, 0, 4, 2, 0, 2, 0, 0, 9, 1, 2, 0, 7, 0x7A, 0x69, 0x79, 0x69, 0x6E, 0x67, 0x7A, 0x68, 0x75, 0, 0, 0, 0 };

unsigned __int8 byte_802B2DC[8] = { 6, 0x6E, 0x65, 0x77, 0x67, 0x78, 0x33, 0 };
unsigned char byte_2000C6BE;

// JV700 通讯IO 设置
// // Funtion: 设置通讯参数 200078C3 FF FF 0A 09 00 FF 01 DE C7 D8 CF BC AA 86 17 65 25 AE D7 8F
// // Input  : argc - 参数长度  
// //          argv - 参数缓冲区
// //          argv[0]:通讯逻辑，
// //          argv[1]:通讯电平
// //          argv[2]:输出脚
// //          argv[3]:输入脚
// //          argv[4]:L线使能开关
// //          argv[5]:DTS线脚位
// //          argv[6]:通讯类型：通讯类型K线，通讯类型双线CAN，通讯类型单线CAN，通讯类型 PWM，通讯类型 VPW
// // Output : ans - 回复到上位机的数据，正常返回FF 00, 异常返回FF 02
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : argv: 60,01,ff,ff,08,07,00,ff,00,91,
// //                      1) 2) 3) 4) 5) 6) 7)
// //          1) ECU 通信的电压逻辑，FF：正；00：负，他失败
// //          2) ECU 通信的工作电压，FF:12V；00：5V，其他失败
// //          3) 输出线，请参考X431 IO 脚定义
// //          4) 输入线，请参考X431 IO 脚定义
// //          5) L 线使能， FF：使能；00：不使能， 其他失败
// //          6) DTS 通讯线, 00：DTS IO8, 01: DTS IO4: 02: DTS IO11, FF 或其他
// //          7) 通迅类型设置, 00 K线, 01 双线CANBUS, 02 单线CANBUS, 03 PWM/VPW
// //          以下情况程序中直接退出：
// //          6 14 协议类型不是01()双线CAN)
// //          3 11 协议类型不是01()双线CAN)
// //          协议类型是 01，但是两个IO 相同 双线CAN
// //          协议类型是 02，但是两个IO 不相同 单线CAN
// //          不重复设置IO，与上次设置相同，退出
// //          ans: ff,00, 固定回 ff 00 表示成功
int ID6001Fun_SetIoParameter_1_sub_804BEA6(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	int v6; // r0
	int Commtype; // r0
				  // 60 01  Argv: FF FF 01 01 00 FF 00 58 69 E1 EB FB 8E A9 CD 14 3D 77 A2 B4
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	CMPHY_Relay_Reset_sub_8030B88();
	GPIO_WriteBit_PIN_sub_8030DBC(0, 1);
	if (Argv[2] == 0xA && Argv[3] == 9 && Argv[6] != 1 && Argv[6] != 0x21
		|| Argv[2] == Argv[3] && Argv[6] == 1
		|| Argv[2] != Argv[3] && Argv[6] == 2)
	{
		goto LABEL_65;
	}
	if (*Argv)
	{
		if (*Argv != 0xFF)
			goto LABEL_29;
		SC_RelayState_200049DC.LogicType = 1;       // ECU 通信的电压逻辑
	}
	else
	{
		SC_RelayState_200049DC.LogicType = 0;
	}
	if (Argv[1])
	{
		if (Argv[1] != 0xFF)
			goto LABEL_29;
		SC_RelayState_200049DC.LevelType = 0xC;     // 设置电压12
	}
	else
	{
		SC_RelayState_200049DC.LevelType = 5;
	}
	if (Argv[2] >= 0x10u)
		goto LABEL_29;
	SC_RelayState_200049DC.OutputChannel = Argv[2];// 输出线
	if (Argv[3] >= 0x10u)
		goto LABEL_29;
	SC_RelayState_200049DC.InputChannel = Argv[3];// 输入线
	if (Argv[4])
	{
		if (Argv[4] == 0xFF)
		{
			SC_RelayState_200049DC.LLine = 1;         // L 线使能
			goto LABEL_30;
		}
	LABEL_29:
		PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
		return 2;
	}
	SC_RelayState_200049DC.LLine = 0;
LABEL_30:
	if ((Argv[5] & 0xF0) == 0xF0)
	{
		IOCTRLSelect_sub_8030606(0x13u, 1u);
		IOCTRLSet_sub_8030658(1, 0);
	}
	else
	{
		if ((Argv[5] & 0xF0) != 0)
			return 2;
		IOCTRLSelect_sub_8030606(0x13u, 1u);
		IOCTRLSet_sub_8030658(0, 0);
	}
	v6 = Argv[5] & 0xF;
	if ((Argv[5] & 0xF) != 0)
	{
		switch (v6)                               // 设置DTS 也不知道什么是DTS
		{
		case 1:
			SC_RelayState_200049DC.Dts = 1;
			break;
		case 2:
			SC_RelayState_200049DC.Dts = 3;
			break;
		case 0xF:
			SC_RelayState_200049DC.Dts = 0;
			break;
		default:
			SC_RelayState_200049DC.Dts = 0;
			IOCTRLSelect_sub_8030606(0x13u, 1u);
			IOCTRLSet_sub_8030658(1, 0);
			PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
			return 2;
		}
	}
	else
	{
		SC_RelayState_200049DC.Dts = 2;
	}
	Commtype = Argv[6];
	if (Argv[6])
	{
		switch (Commtype)                         // 通讯类型设置
		{
		case 1:
			CAN_DeInit_sub_80348F4(&CAN1_BASE_40006400);
			CAN_DeInit_sub_80348F4(&CAN2_BASE_40006800);
			SC_RelayState_200049DC.CommType = Argv[6];
			SC_RelayState_200049DC.CANH = SC_RelayState_200049DC.InputChannel;
			SC_RelayState_200049DC.CANL = SC_RelayState_200049DC.OutputChannel;
			GPIO_WriteBit_PIN_sub_8030DBC(0x10, 0);
			GPIO_WriteBit_PIN_sub_8030DBC(3, 1);
			SetGPIOGPIO_Mode_IN_sub_8031E6C(0);
			Delay_802EF34(8);
			break;
		case 2:
			CAN_DeInit_sub_80348F4(&CAN2_BASE_40006800);
			SC_RelayState_200049DC.CommType = Argv[6];
			SC_RelayState_200049DC.CANH = SC_RelayState_200049DC.InputChannel;
			GPIO_WriteBit_PIN_sub_8030DBC(0x20, 0);
			SetGPIOGPIO_Mode_IN_sub_8031E6C(1);
			Delay_802EF34(8);
			break;
		case 0x20:
			SC_RelayState_200049DC.CommType = 0x20;
			GPIO_WriteBit_PIN_sub_8030DBC(0x20, 1);
			SetGPIOGPIO_Mode_IN_sub_8031E6C(2);
			Delay_802EF34(8);
			break;
		case 0x21:
			CAN_DeInit_sub_80348F4(&CAN1_BASE_40006400);
			CAN_DeInit_sub_80348F4(&CAN2_BASE_40006800);
			SC_RelayState_200049DC.CommType = 0x21;
			GPIO_WriteBit_PIN_sub_8030DBC(3, 0);
			GPIO_WriteBit_PIN_sub_8030DBC(0x10, 1);
			SetGPIOGPIO_Mode_IN_sub_8031E6C(3);
			Delay_802EF34(8);
			break;
		case 0x22:
			SC_RelayState_200049DC.CommType = 0x22;
			GPIO_WriteBit_PIN_sub_8030DBC(0x40, 1);
			GPIO_PinAFConfigsub_802F062();
			break;
		default:
			SC_RelayState_200049DC.CommType = 0;
			break;
		}
	}
	else
	{
		SC_RelayState_200049DC.CommType = Argv[6];
	}
	SC_TagISO15765_2000C334.m_chState = 0;
	SC_TagKWP2000_20004974.UnknowByte = 0;
	Keep_Link_200046C0.rightState = 5;
	if (timer_open_flag_2000C6B7 == 1)
	{
		timer_open_flag_2000C6B7 = 0;
		TimerRelease_sub_802EF76(0);
	}
	if (SC_RelayState_200049DC.CommType == 0x22)
		ComClose_sub_80B1D06_sub_802FA28(4);
	else
		ComClose_sub_80B1D06_sub_802FA28(1);
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	if (SC_RelayState_200049DC.CommType == 0x22)
		ComOpen_sub_80B1AEC_802F7DE(4, &SC_com_portMode_20004964);
	else
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
LABEL_65:
	PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
	return 2;
}




// // Funtion: 设置对ECU通讯串口波特率
// // Input  : argc - 参数长度
// //          argv - 参数缓冲区
// //          argv[0]:值非0：决定波特率是由argv[1]到argv[2]组成，
// //                  值为0：决定波特率是由argv[1]到argv[4]组成。
// //    在argv[0]为0时：
// //          argv[1]:波特率参数
// //          argv[2]:波特率参数
// //          argv[3]:波特率参数
// //          argv[4]:波特率参数
// //          argv[5]:字节校验方式
// //    在argv[0]为非0时：
// //          argv[1]:波特率参数
// //          argv[2]:波特率参数
// //          argv[3]:字节校验方式
// // Output : ans - 回复到上位机的数据，正常返回FF 00, 异常返回FF 02
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : argv: 60,02,00,00,25,80,
// //                      1) 2) 3) 4)
// //          1) 如果为 0 则波特率为：1)2)3)4) - 0x00002580
// //             如果不为 0 则波特率为：1)2)
// //             60,02,D7,50,00 - 0xD750
// //          send: ff,00, 固定回 ff 00 表示成功
int ID6002Fun_SetEcuBaudRate_1_sub_804C234(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	int Badurate; // r7 60 02 Argv: 00 01 C2 00 00  0001C200 = 115200 bps
				  //                00 00 E1 00 00  0000E100 = 57600
				  //                
	char v5; // r8
	unsigned int v6; // r0

	if (*Argv)
	{
		v5 = 2;
		Badurate = 576000u / (0x10000 - (Argv[1] + (*Argv << 8)));
	}
	else
	{
		Badurate = Argv[3] + (*Argv << 0x18) + (Argv[1] << 0x10) + (Argv[2] << 8);
		v5 = 4;
	}
	SC_com_portMode_20004964.BaudRate = Badurate;
	SC_com_portMode_20004964.WordLength = 0;
	SC_com_portMode_20004964.StopBits = 0;
	SC_com_portMode_20004964.Parity = 0;
	v6 = Argv[v5];
	if (Argv[v5])
	{
		if (v6 == 2)
		{
			SC_com_portMode_20004964.Parity = 0x400;
			SC_com_portMode_20004964.WordLength = 0x1000;
		}
		else if (v6 >= 2)
		{
			if (v6 != 4 && v6 >= 4)
			{
				PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
				return 1;
			}
			SC_com_portMode_20004964.Parity = 0x2000;
		}
		else
		{
			SC_com_portMode_20004964.Parity = 0x600;
			SC_com_portMode_20004964.WordLength = 0x1000;
		}
	}
	else
	{
		SC_com_portMode_20004964.Parity = 0;
	}
	SC_TagKWP2000_20004974.UnknowByte = 0;
	Keep_Link_200046C0.rightState = 5;
	if (SC_RelayState_200049DC.CommType == 0x22)
	{
		ComClose_sub_80B1D06_sub_802FA28(4);
		ComOpen_sub_80B1AEC_802F7DE(4, &SC_com_portMode_20004964);
	}
	else
	{
		ComClose_sub_80B1D06_sub_802FA28(1);
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	}
	PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
	return 2;
}




// // Funtion: 设置对ECU通讯时间参数
// // Input  : argc - 参数长度
// //          argv - 参数缓冲区
// //          argv[0]:设置字节间隔参数
// //          argv[1]:设置字节间隔参数
// //          argv[2]:设置帧间隔参数
// //          argv[3]:设置最大等待时间参数
// //          argv[4]:设置最大等待时间参数 hejm
// // Output : ans - 回复到上位机的数据，正常返回FF 00, 异常返回FF 02
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : argv: 60,03,00,1e,01,00,19
// //                      1) 2) 3) 4)
// //          1)2) 字节与字节间隔时间*10，精度0.1 毫秒. 0X001E表示3.0MS
// //          3) 数据包之间时间间隔,单位毫秒/10, 不能为0, 01-表示10MS
// //          4) 5 uint8_t：接收ECU 数据包最大等待时间/10，不能为0， 0X0019表示250MS
// //          send: ff,00, 固定回 ff 00 表示成功
int ID6003Fun_SetEcuCommTimeInterval_1_sub_804C39A(int a1, unsigned __int8 *argv, unsigned __int8 *Ans)
{
	unsigned __int8 i; // r7 60 03 Argv: 00 01 05 01 2C 00 00 00
					   //                00 1E 08 01 2C   012C=300
					   //                00 03 65 00 03 FC
	unsigned int v5; // r9
	int temp; // r8

	for (i = 0; i < 3u; ++i)
	{
		if (i)
		{
			if (i == 2)
			{
				temp = argv[4] + (argv[3] << 8);
				if (!temp)
				{
				LABEL_14:
					PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
					return 2;
				}
				SC_TagKWP2000_20004974.m_Maxwaittime = 0xA * temp;// temp = 0x012C = 300
			}
			else if (i < 2u)
			{
				if (!argv[2])
					goto LABEL_14;
				SC_TagKWP2000_20004974.m_nFrameTime = 0xA * argv[2];// 这里怎么看都觉得不太对
			}
		}
		else                                        // ==0的时候
		{
			SC_TagKWP2000_20004974.m_nBtyetime = *argv << 8;
			SC_TagKWP2000_20004974.m_nBtyetime += argv[1];// m_nMScount MS计数 不知道是什么
			SC_TagKWP2000_20004974.m_nBtyetime *= 0x64;
			v5 = SC_TagKWP2000_20004974.m_nBtyetime / 0x64;
			if (SC_TagKWP2000_20004974.m_nBtyetime / 0x64 % 0xAu >= 5)
				SC_TagKWP2000_20004974.m_MsTime = v5 / 0xA + 1;
			else
				SC_TagKWP2000_20004974.m_MsTime = v5 / 0xA;
			if (!SC_TagKWP2000_20004974.m_MsTime)
				SC_TagKWP2000_20004974.m_MsTime = 1;
		}
	}
	SC_TagKWP2000_20004974.UnknowByte = 0;        // 这字段不知道是什么意思
	Keep_Link_200046C0.rightState = 5;
	if (timer_open_flag_2000C6B7 == 1)
	{
		timer_open_flag_2000C6B7 = 0;
		TimerRelease_sub_802EF76(0);
	}
	PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
	return 2;
}



// // Funtion: 设置连路保持
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : argv: 60,04,06,80,98,f1,01,3e,48,06,64
// //                      1) 2) 3) 4) 5) 6) 7) 8) 9)
// //          1) 链路命令长度(若为0，则终止链路)
// //          2) 3) 4) 5) 6) 7) 链路数据包
// //          8) 未知或无意义
// //          9) 其值乘10 即：0x64*10=1000（ms）为链路间隔时间，若为0，则返回错误
// //          send: ff,00, 固定回 ff 00 表示成功
int ID6004Fun_SetLinkData_1_sub_804C4CA(int a1, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned int v5; // r8 60 04 00 67 00 03 
	unsigned __int8 dataLength; // r7
	int result; // r0

	v5 = 0;
	receive_buff_2000BF20[0x104] = 0;
	if (timer_open_flag_2000C6B7 == 1)
	{
		while (Keep_Link_200046C0.rightState != 5)
		{
			++v5;
			Delay_sub_802EF46(0x64u);
			if (v5 >= 0x2711)
			{
				Keep_Link_200046C0.rightState = 5;
				break;
			}
		}
		TimerStop_sub_802EF10(0);
	}
	else if (timer_open_flag_2000C6B7 == 3)
	{
		TimerStop_sub_802EF10(1);
	}
	Keep_Link_200046C0.idleSendLen = *Argv;
	Keep_Link_200046C0.linkState = 0;
	Keep_Link_200046C0.field_46 = 0;
	dataLength = Keep_Link_200046C0.idleSendLen;
	if (Keep_Link_200046C0.idleSendLen)
	{
		Copysub_802FB50(Keep_Link_200046C0.dataBuf, Argv + 1, Keep_Link_200046C0.idleSendLen);
		Keep_Link_200046C0.idleRecvLen = Argv[dataLength + 1];
		if (!Argv[dataLength + 2])
		{
		LABEL_17:
			PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
			return 2;
		}
		Keep_Link_200046C0.IdleTime = 0xA * Argv[dataLength + 2];
		Keep_Link_200046C0.linkType = 4;
		if (Argv[1] == 0x55 && Argv[2] == 0xAA)
		{
			Keep_Link_200046C0.linkType = 1;
			if ((Argv[6] & 0x80) == 0 && dataLength >= 0x12u || (Argv[6] & 0x80) != 0 && dataLength >= 0x14u)
				goto LABEL_17;
			setCanbusLinkDataToken_sub_802BEB4();
		}
		else if (Argv[1] == 0x55 && Argv[2] == 0xBB)
		{
			Copysub_802FB50(Keep_Link_200046C0.dataBuf, Argv + 3, dataLength);
			Keep_Link_200046C0.linkType = 6;
			Keep_Link_200046C0.idleSendLen -= 2;
		}
		else if (Argv[1] == 0x55 && Argv[2] == 0xCC)
		{
			Copysub_802FB50(Keep_Link_200046C0.dataBuf, Argv + 3, dataLength);
			Keep_Link_200046C0.linkType = 7;
			Keep_Link_200046C0.idleSendLen -= 2;
		}
		switch (Keep_Link_200046C0.linkType)
		{
		case 1u:
			SC_TagISO15765_2000C334.m_PakMode = 1;
			Keep_Link_200046C0.rightState = 5;
			TimerConfig_sub_802EDAE(0, 0xAu);
			TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_CML_ISO15765_Time_sub_802DFC8);
			TIM_sub_802EEEC(0);
			timer_open_flag_2000C6B7 = 1;
			break;
		case 4u:                                  // KEEPLINK_ACCESS
			TimerConfig_sub_802EDAE(0, SC_TagKWP2000_20004974.m_MsTime);
			Keep_Link_200046C0.rightState = 5;
			TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_setlinkkeep_sub_802C1EC);
			TIM_sub_802EEEC(0);
			timer_open_flag_2000C6B7 = 1;
			break;
		case 6u:
			TimerConfig_sub_802EDAE(1, SC_TagKWP2000_20004974.m_MsTime);// 这里是多的一个case 不知道作用是什么
			Keep_Link_200046C0.rightState = 5;
			if (Keep_Link_200046C0.IdleTime == 0x9CE)
				Keep_Link_200046C0.IdleTime = 0xFA0;
			TimerInterruptFuntionLoad_sub_802EF66(1, (int)SetPWMLink_sub_802C398);// PWM协议 可能是PWM的链路保持
			TIM_sub_802EEEC(1);
			timer_open_flag_2000C6B7 = 3;
			break;
		}
		PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
		result = 2;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
		{
			while (Keep_Link_200046C0.rightState != 5)
			{
				++v5;
				Delay_sub_802EF46(0x64u);
				if (v5 >= 0x2711)
				{
					Keep_Link_200046C0.rightState = 5;
					break;
				}
			}
		}
		SC_TagISO15765_2000C334.m_chState = 0;
		SC_TagKWP1281_200043E4.m_LinkFG = 0;
		Keep_Link_200046C0.linkType = 0;
		timer_open_flag_2000C6B7 = 0;
		PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
		result = 2;
	}
	return result;
}


// // Funtion: 地址码触发函数，用于发送地址码，通过55H计算波特率，接收KW1,KW2,
// //          发送KW2取反。常用于地址码ISO协议、地址码KWP协议、地址码单字节协议
// // Input  : argc - 参数长度
// //          argv - 参数
// //          argv[0]:地址码发送模式。值为1表示模式1，值为2表示模式2，值为3表示模式3
// //     模式1  发送5波特率地址码
// //          argv[1]:地址码值
// //          argv[2]:判断是否自动计算波特率。为0表示不自动计算，为0xFF表示自动计算波特率
// //          argv[3]:判断是否将KW2取反发回到ECU。为0表示不取反发回，为0xff表示取反发回
// //          argv[4]:如argv[3]非0，argv[4]为0表示必须要收到ECU发来的地址码取反字节，如argv[3]为0，argv[4]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[4]非0，则argv[4]表示要从ECU接受的数据的帧数
// //          argv[5]~arg[5+argv[4]-1]:如argv[4]为0，这些字节无意义,如argv[4]非0，这些字节分别表示接收的每一帧数据的长度
// //--------------------------------------------------
// //     模式2 发送设定的地址码或200bps地址码
// //          argv[1]:地址码值
// //          argv[2]:最高位为1表示需要计算地址码的波特率，并作为计算波特率的一个参数，否则表示地址码波特率为200.
// //          argv[3]:argv[2]最高位为1时，argv[3]为计算波特率的一个参数，argv[2]最高位不为1时，argv[3]无意义
// //          argv[4]:判断是否将KW2取反发回到ECU。为0表示不取反发回，为0xff表示取反发回
// //          argv[5]:如argv[4]非0，argv[5]为0表示必须要收到ECU发来的地址码取反字节，如argv[4]为0，argv[5]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[5]非0，则argv[5]表示要从ECU接受的数据的帧数
// //          argv[6]~arg[6+argv[5]-1]:如argv[4]为0，这些字节无意义,如argv[5]非0，这些字节分别表示接收的每一帧数据的长度
// //--------------------------------------------------
// //     模式3 发送200bps地址码
// //          argv[1]:地址码值
// //          argv[2]:判断是否自动计算波特率。为0表示不自动计算，为0xFF表示自动计算波特率
// //          argv[3]:判断是否将KW2取反发回到ECU。为0表示不取反发回，为0xff表示取反发回
// //          argv[4]:如argv[3]非0，argv[4]为0表示必须要收到ECU发来的地址码取反字节，如argv[3]为0，argv[4]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[4]非0，则argv[4]表示要从ECU接受的数据的帧数
// //          argv[5]~arg[5+argv[4]-1]:如argv[4]为0，这些字节无意义,如argv[4]非0，这些字节分别表示接收的每一帧数据的长度
// // Output : ans - 回复到上位机的数据:
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、如在ECU发完KW1,KW2后，还有帧数据接收，则，ans的内容为：接收总帧数 第一帧数据长度 第一帧数据
// //                   第二帧数据长度 第二帧数据......第n帧数据长度，第n帧数据(总帧数用两个字节表示)
// //                   如ans[] = {0x00,0x02,0x05,0x81,0x10,0xf1,0x81,0x03,0x06，0x82,0x10,0xf1,0x04,0x05,0x08c}
// //                4、如在ECU发完KW1,KW2后，无帧数据接收，则返回FF 00
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6005
int ID6005_Set5BpsParameter_1_sub_8022EB0(int argc, unsigned __int8 *argv, unsigned __int8 *Ans)
{
	unsigned int CaseNum; // r0
	unsigned int l; // r10
	int v8; // r9
	int v9; // r11
	unsigned int m; // r10
	char v11; // r0
	char v12; // r7
	unsigned int v13; // r8
	unsigned int n; // r10
	int v15; // r9
	unsigned int ii; // r10
	char Ret; // r0
	char Argv1Data; // r7
	unsigned int i; // r10
	int v20; // r9
	unsigned int j; // r10
	char v22; // r0
	unsigned __int8 k; // [sp+0h] [bp-30h] BYREF
	char v24[3]; // [sp+1h] [bp-2Fh] BYREF
	unsigned __int8 keyWord[44]; // [sp+4h] [bp-2Ch] BYREF

	*(_DWORD *)keyWord = 0;
	Delay_802EF34(5);
	TimerRelease_sub_802EF76(0);
	CaseNum = *argv;
	if (CaseNum == 1)
		goto LABEL_7;
	if (!*argv)
		goto LABEL_9;
	if (CaseNum == 3)
	{
		Argv1Data = argv[1];
		Delay_802EF34(0x1F4);
		if (argv[2])
		{
			if (argv[2] != 0xFF)
				goto LABEL_9;
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CF50(Argv1Data, 0xC8u);
			EnableLLine_1_sub_802C560();
			SC_com_portMode_20004964.BaudRate = 0;
			IOCTRLSelect_sub_8030606(0, 3u);
			SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
			if (!SC_com_portMode_20004964.BaudRate)
			{
				Delay_802EF34(0xFA0);
				IOCTRLSelect_sub_8030606(1u, 1u);
				IOCTRLSet_sub_8030658(1, 0x1F4);
				sendAddressToEcu_sub_802CF50(Argv1Data, 0xC8u);

				IOCTRLSelect_sub_8030606(0, 3u);
				SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
				if (!SC_com_portMode_20004964.BaudRate)
					goto LABEL_22;
			}
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		}
		else
		{
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CF50(Argv1Data, 0xC8u);
			IOCTRLInit_sub_802C570();
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
			{
				Delay_802EF34(0xFA0);

				IOCTRLSelect_sub_8030606(1u, 1u);
				sendAddressToEcu_sub_802CF50(Argv1Data, 0xC8u);
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
					goto LABEL_121;
			}
		}
		for (i = 0; i < 2; ++i)
		{
			if (!ComByte_sub_802F6CC(&keyWord[i], 0x1388))
				goto LABEL_121;
		}
		if (argv[3])
		{
			if (argv[3] != 0xFF)
				goto LABEL_117;
			Delay_802EF34(0x22);
			ComSendByte_sub_802F1E0((unsigned __int8)~keyWord[1]);
			if (!argv[4])
			{
				if (ComByte_sub_802F6CC(&k, 0x3E8))
					PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
				else
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
				return 2;
			}
		}
		else if (!argv[4])
		{
		LABEL_107:
			PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
			return 2;
		}
		*Ans = 0;
		v20 = 5;
		Ans[1] = argv[4];
		v9 = 2;
		for (j = 0; j < argv[4]; ++j)
		{
			if (!argv[v20])
				goto LABEL_117;
			Ans[v9++] = argv[v20];
			for (k = 0; k < (unsigned int)argv[v20]; ++k)
			{
				v22 = ComByte_sub_802F6CC(&Ans[v9++], 0x3E8);
				if (!v22)
					goto LABEL_121;
			}
			++v20;
		}
		return v9;
	}
	if (CaseNum >= 3)
	{
		if (CaseNum != 4)
			goto LABEL_9;
	LABEL_7:
		if (argv[2])
		{
			if (argv[2] != 0xFF)
			{
			LABEL_9:
				PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
				return 2;
			}
			Delay_802EF34(0x1F4);
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CC82(argv[1]);
			if (*argv == 1)
				IOCTRLInit_sub_802C570();
			SC_com_portMode_20004964.BaudRate = 0;
			IOCTRLSelect_sub_8030606(0, 3u);
			SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
			if (!SC_com_portMode_20004964.BaudRate)
			{
				Delay_802EF34(0xFA0);

				IOCTRLSelect_sub_8030606(1u, 1u);
				IOCTRLSet_sub_8030658(1, 0x1F4);
				sendAddressToEcu_sub_802CC82(argv[1]);
				IOCTRLSelect_sub_8030606(0, 3u);
				SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
				if (!SC_com_portMode_20004964.BaudRate)
				{
				LABEL_22:
					ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
					return 2;
				}
			}
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		}
		else
		{
			Delay_802EF34(0x1F4);
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CC82(argv[1]);
			if (*argv == 1)
				IOCTRLInit_sub_802C570();
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
			{
				Delay_802EF34(0xFA0);

				IOCTRLSelect_sub_8030606(1u, 1u);
				sendAddressToEcu_sub_802CC82(argv[1]);
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
					goto LABEL_121;
			}
		}
		for (l = 0; l < 2; ++l)
		{
			if (!ComByte_sub_802F6CC(&keyWord[l], 0x1388))
				goto LABEL_121;
		}
		if (!argv[3])
			goto LABEL_129;
		if (argv[3] == 0xFF)
		{
			Delay_802EF34(0x22);
			ComSendByte_sub_802F1E0((unsigned __int8)~keyWord[1]);
		}
		if (argv[4])
		{
		LABEL_129:
			if (!argv[4])
			{
				if (*argv != 1)
				{
					*Ans = 0;
					Ans[1] = 1;
					Ans[2] = 2;
					Ans[3] = keyWord[0];
					Ans[4] = keyWord[1];
					return 5;
				}
				goto LABEL_107;
			}
			*Ans = 0;
			v8 = 5;
			Ans[1] = argv[4];
			v9 = 2;
			for (m = 0; m < argv[4]; ++m)
			{
				if (!argv[v8])
					goto LABEL_117;
				if (argv[v8] == 0xFF)
				{
					if (!ComByte_sub_802F6CC(&argv[v8], 0x3E8))
						goto LABEL_121;
					Ans[v9++] = argv[v8] + 1;
				}
				Ans[v9++] = argv[v8];
				for (k = 0; k < (unsigned int)argv[v8]; ++k)
				{
					v11 = ComByte_sub_802F6CC(&Ans[v9++], 0x3E8);
					if (!v11)
						goto LABEL_121;
				}
				++v8;
			}
			return v9;
		}
		if (ComByte_sub_802F6CC((unsigned __int8 *)v24, 0x12C))
			PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
		else
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
		return 2;
	}
	v12 = argv[1];
	Delay_802EF34(0x1F4);

	IOCTRLSelect_sub_8030606(1u, 1u);
	if ((argv[2] & 0x80) != 0)
	{
		v13 = 0x8CA00u / (0x10000 - (argv[3] + (argv[2] << 8)));
		sendAddressToEcu_sub_802CF50(v12, v13);
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
		{
			Delay_802EF34(0xFA0);
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CF50(v12, v13);
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
			{
			LABEL_121:
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
				return 2;
			}
		}
	}
	else
	{
		sendAddressToEcu_sub_802CF50(v12, 0xC8u);
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
		{
			Delay_802EF34(0xFA0);
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CF50(v12, 0xC8u);
			IOCTRLInit_sub_802C570();
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
				goto LABEL_121;
		}
	}
	for (n = 0; n < 2; ++n)
	{
		if (!ComByte_sub_802F6CC(&keyWord[n], 0x1388))
			goto LABEL_121;
	}
	if (!argv[4])
	{
		if (!argv[5])
			goto LABEL_107;
		goto LABEL_77;
	}
	if (argv[4] != 0xFF)
	{
	LABEL_117:
		PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
		return 2;
	}
	Delay_802EF34(0x22);
	ComSendByte_sub_802F1E0((unsigned __int8)~keyWord[1]);
	if (argv[5])
	{
	LABEL_77:
		*Ans = 0;
		v15 = 6;
		Ans[1] = argv[5];
		v9 = 2;
		for (ii = 0; ii < argv[5]; ++ii)
		{
			if (!argv[v15])
				goto LABEL_117;
			Ans[v9++] = argv[v15];
			for (k = 0; k < (unsigned int)argv[v15]; ++k)
			{
				Ret = ComByte_sub_802F6CC(&Ans[v9++], 0x3E8);
				if (!Ret)
					goto LABEL_121;
			}
			++v15;
		}
		return v9;
	}
	if (ComByte_sub_802F6CC(&k, 0x1388))
		PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
	else
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
	return 2;
}



// Funtion: BOSCH地址码触发函数  bosch协议专用
// Input  : argc - 参数长度
//          argv - 指令参数缓冲区
//          argv[0]:确定在发送完地址码后是否禁能L线，为0表示禁能L线，非0表示不禁能L线
//          argv[1]:地址码值
// Output : ans - 回复到上位机的数据
//                1、指令格式异常返回 FF 01
//                2、下位机通信异常返回 FF 02
//                3、当KW2为0x8f时，返回00 00
//                4、当KW2非0x8f，并正常接收版本信息数据时，ans的格式为：总帧数 第一帧数据  第二帧数据......第N帧数据
//                如ans[] = {00,04,0f,01,f6,b0,36,42,39,30,36,30,33,32,41,20,20,03,17,03,f6,32,2e,30,4c,20,32,56,20,45,
//                           55,32,20,20,20,20,20,20,20,20,20,03,07,05,f6,35,32,31,36,03,08,07,f6,00,00,06,00,00,03}
// Return : 返回的ans缓冲区的有效数据长度
// Info   : 6006
int ID6006Fun_SetBosch_1_sub_80215FA(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned int Badurate = 0; // r7
	unsigned int i; // r8
	int result; // r0
	unsigned int j; // r8
	int dataLenth; // r9
	unsigned int k; // r8
	unsigned __int8 Keyword[4]; // [sp+0h] [bp-30h] BYREF
	SC_PAKRECV PakRecv; // [sp+4h] [bp-2Ch] BYREF
	SC_PAKSEND PakSend; // [sp+Ch] [bp-24h] BYREF

	*(_DWORD *)Keyword = 0;
	PakSend.PakdataAddr = SendPakdataPackData_2000BDF4;
	PakSend.PakLenth = 4;
	SendPakdataPackData_2000BDF4[0] = 3;
	SendPakdataPackData_2000BDF4[1] = 0;
	SendPakdataPackData_2000BDF4[2] = 9;
	SendPakdataPackData_2000BDF4[3] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	SC_TagKWP1281_200043E4.m_chHoldDig[0] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDig[1] = 0;
	SC_TagKWP1281_200043E4.m_chHoldDig[2] = 9;
	SC_TagKWP1281_200043E4.m_chHoldDig[3] = 3;
	PakRecv.PakdataAddr = receive_buff_2000BF20;
	TimerRelease_sub_802EF76(0);
	SC_TagKWP1281_200043E4.m_Idletime = 0x258;
	SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	SC_TagKWP1281_200043E4.m_SendFinishFlag = 1;
	SC_TagKWP1281_200043E4.m_LinkFG = 1;
	for (i = 0; i < 4; ++i)
	{
		EnableLLine_1_sub_802C560();
		IOCTRLSelect_sub_8030606(1u, 1u);
		if ((*Argv & 0x80) != 0)
		{
			sendAddressToEcu_sub_802CD84(Argv[1]);
			SetRelayPara_sub_802BCD0(0xD, 1u);
			SetRelayPara_sub_802BCD0(0xD, 2u);
			CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
			++i;
		}
		else if (i >= 2)
		{
			sendAddressToEcu_sub_802CD84(Argv[1]);
			SetRelayPara_sub_802BCD0(0, 8u);
			SetRelayPara_sub_802BCD0(0xD, 1u);
			SetRelayPara_sub_802BCD0(1, 2u);
			CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
		}
		else
		{
			Delay_802EF34(0x1F4);
			sendAddressToEcu_sub_802CD84(Argv[1]);
			IOCTRLInit_sub_802C570();
		}
		IOCTRLSelect_sub_8030606(0, 3u);
		Badurate = autoCheckBaudRate_sub_802CE7E(0x19);
		if (Badurate)
			break;
	}
	if (Badurate)
	{
		SC_com_portMode_20004964.BaudRate = Badurate;
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		for (j = 0; j < 2; ++j)
		{
			if (!ComByte_sub_802F6CC(&Keyword[j], 0x1388))
				goto LABEL_32;
		}
		Delay_802EF34(0x20);
		ComSendByte_sub_802F1E0((unsigned __int8)~Keyword[1]);
		*Ans = 0;
		Ans[1] = 0;
		dataLenth = 2;
		if (Keyword[1] == 0x8F)
		{
			ComByte_sub_802F6CC(&Keyword[2], 0x3E8);
		}
		else
		{
			SetTIMCLOCK_RCC_APB1PeriphClockCmd_sub_802ED88(Keyword[1]);
			SC_TagKWP1281_200043E4.m_nMScount = 0;
			SC_TagKWP1281_200043E4.m_chCount = 0;
			Keep_Link_200046C0.rightState = 2;
			TimerConfig_sub_802EDAE(0, 1u);
			if (Badurate >= 5000)
			{
				SC_TagKWP1281_200043E4.m_nBtyetime = 2;
				SC_TagKWP1281_200043E4.m_nFrameTime = 0x16;
				SC_TagKWP1281_200043E4.m_ReserveTime = 2;
			}
			else
			{
				SC_TagKWP1281_200043E4.m_nBtyetime = 6;
				SC_TagKWP1281_200043E4.m_nFrameTime = 0x1E;
				SC_TagKWP1281_200043E4.m_ReserveTime = 3;
			}
			SC_TagKWP1281_200043E4.m_LinkFG = 1;
			timer_open_flag_2000C6B7 = 1;
			TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_CML_KWP1281_Time_sub_802C5B0);
			ComInterruptFuntionLoad_sub_802F8A0((int)SC_CML_KWP1281_Comread_sub_802C860, 1u);
			ComInterruptFuntionLoad_sub_802F8A0((int)SC_CML_KWP1281_Comsend_sub_802C7DC, 0);
			TIM_sub_802EEEC(0);
			ComReadSign_sub_802F614(1);               // 接收回复
			if (!SC_CML_KWP1281_Recv_sub_802CBCC(&PakRecv))
			{
			LABEL_32:
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
				return 2;
			}
			while (PakRecv.PakdataAddr[2] != 9 && PakRecv.PakdataAddr[2] != 0xF7 && PakRecv.PakLenth >= 3)
			{
				++Ans[1];
				for (k = 0; k < PakRecv.PakLenth; ++k)
					Ans[dataLenth++] = PakRecv.PakdataAddr[k];
				if (!SC_CML_KWP1281_Sendsub_802CB36(&PakSend) || !SC_CML_KWP1281_Recv_sub_802CBCC(&PakRecv))
					goto LABEL_32;
			}
		}
		result = dataLenth;
	}
	else
	{
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
		result = 2;
	}
	return result;
}



// 
// //------------------------------------------------------------------------------
// // Funtion: 设置总线电平（高或低），多用于拉低拉高KWP协议
// // Input  : argc - 参数长度
// //          argv - 参数缓冲区
// //          argv[0]:值为0表示拉低电平，值为0xff表示拉高电平
// //          argv[1]:拉低或拉高电平的时间参数
// //          argv[2]:拉低或拉高电平的时间参数
// // Output : ans - 回复到上位机的数据，正常返回FF 00, 异常返回FF 02
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6007, 00,00,19,
// //------------------------------------------------------------------------------
int ID6007Fun_SetCommunicationLineVoltage_1_sub_804C946(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned __int8 temp_1; // r7
	int tt; // r2

	temp_1 = *Argv;

	IOCTRLSelect_sub_8030606(1u, 0);
	tt = Argv[2];
	if (temp_1)
	{
		if (temp_1 != 0xFF)
		{
			PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
			return 2;
		}
		IOCTRLSet_sub_8030658(1, tt + (Argv[1] << 8));
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	}
	else
	{
		IOCTRLSet_sub_8030658(0, tt + (Argv[1] << 8));
		SC_TagKWP2000_20004974.UnknowByte = 0;
	}
	PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
	return 2;
}



// // Funtion: BOSCH链路维持函数  bosch协议专用
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          此函数不需要参数
// // Output : ans - 回复到上位机的数据
// //                返回FF 00
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6008
int ID6008_SetBoschLink_1_Fun_sub_804CBC0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	SC_TagKWP1281_200043E4.m_Idletime = 600;
	SC_TagKWP1281_200043E4.m_chHoldDig[0] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDig[1] = 0;
	SC_TagKWP1281_200043E4.m_chHoldDig[2] = 9;
	SC_TagKWP1281_200043E4.m_chHoldDig[3] = 3;
	if (*argv)
	{
		if (*argv != 255)
		{
			PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
			return 2;
		}
		SC_TagKWP1281_200043E4.m_LinkFG = 1;
		SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	}
	else if (timer_open_flag_2000C6B7 == 1)
	{
		while (Keep_Link_200046C0.rightState != 5)
			;
		TimerStop_sub_802EF10(0);
	}
	Keep_Link_200046C0.rightState = 5;
	PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
	return 2;
}





// // Funtion: 类似于Set5BpsParameter   对ECU发来的关键字不取反发回
// // Input  : argc - 参数长度
// //          argv - 参数
// //          argv[0]:地址码
// // Output : ans - 回复到上位机的数据格式 总帧数 帧长度 帧数据
// //          ans[] = { 00 01 02 08 09}
// // Return : 返回ans的有效数据长度
// // Info   : 6009
int ID6009Fun_BoschFiat_1_sub_8024570(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int result; // r0
	unsigned __int8 v6[24]; // [sp+0h] [bp-18h] BYREF


	IOCTRLSelect_sub_8030606(1u, 1u);
	sendAddressToEcu_sub_802CC82(*argv);
	IOCTRLSelect_sub_8030606(0, 3u);
	IOCTRLInit_sub_802C570();
	SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
	if (SC_com_portMode_20004964.BaudRate
		|| (Delay_802EF34(0x9C40),
			IOCTRLSelect_sub_8030606(1u, 1u),
			sendAddressToEcu_sub_802CC82(*argv),
			IOCTRLSelect_sub_8030606(0, 3u),
			(SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28)) != 0))
	{
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		if (ComByte_sub_802F6CC(v6, 0x3E8)
			&& (*ans = 0, ++ans[1], ans[2] = 2, ans[3] = v6[0], ComByte_sub_802F6CC(v6, 0x7D0)))
		{
			ans[4] = v6[0];
			result = 5;
		}
		else
		{
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			result = 2;
		}
	}
	else
	{
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		result = 2;
	}
	return result;
}


// // Funtion: 发送地址码到ECU，返回六个字节，对第三个字节取返发回。
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:地址码发送模式
// //          argv[1]:地址码值
// //          argv[2]:判断是否自动计算波特率，为0表示使用已知波特率，为0xff表示自动计算波特率
// //          argv[3]:判断是否继续从ECU接受数据，为0表示不接收数据，为0xff表示继续接受数据
// //          argv[4]:指定从ECU接收的数据的总帧数
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、不接收ECU的帧数据，则返回FF 00
// //                4、当从ECU接受指定的帧数的数据时，但不接收五个关键字时，ans的格式为：总帧数(总帧数固定用两个字节表示) 第一帧长度 第一帧数据
// //                   第二帧长度 第二帧数据......第N帧长度 第N帧数据
// //                   如ans[] = {00,04,0f,0E,f6,b0,36,42,39,30,36,30,33,32,41,20,20,05,17,16,f6,32,2e,30,4c,20,32,56,20,45,
// //                              55,32,20,20,20,20,20,20,20,20,20,04,07,06,f6,35,32,31,36,19,08,07,f6,00,00,06,00,00,03}
// //                   当从ECU接受指定的帧数的数据时，且接收五个关键字时，ans的格式为：总帧数(总帧数固定用两个字节表示) 第一帧长度 第一帧数据
// //                   第二帧长度 第二帧数据......第N帧长度 第N帧数据
// //                   如ans[] = {00,05,05,01,02,03,04,05,0f,0E,f6,b0,36,42,39,30,36,30,33,32,41,20,20,05,17,16,f6,32,2e,30,4c,20,32,56,20,45,
// //                              55,32,20,20,20,20,20,20,20,20,20,04,07,06,f6,35,32,31,36,19,08,07,f6,00,00,06,00,00,03}
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 600a
// //-------------------------------------------------------------------
// // SetAddressFiat :发送地址码到ECU，返回六个字节，对第三个字节取返发回。
int ID600AFun_SetAddressFiat_1_sub_8024694(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v3 = 0; // r10
	unsigned int v6; // r0
	unsigned int l; // r9
	unsigned int v9; // r7
	unsigned int m; // r9
	unsigned int v11; // r8
	int v12; // r10
	unsigned int n; // r9
	unsigned int v14; // r7
	unsigned int ii; // r9
	unsigned int v16; // r8
	int v17; // r10
	unsigned int i; // r9
	unsigned int v19; // r7
	unsigned int j; // r9
	unsigned int v21; // r8
	int v22; // r10
	unsigned __int8 k; // [sp+0h] [bp-28h] BYREF
	unsigned __int8 Keyword[39]; // [sp+1h] [bp-27h] BYREF

	*ans = 0;
	ans[1] = 0;
	v6 = *argv;
	if (v6 == 1)                                // Argv[0] = 1,2,3,4...的各种情况判断
		goto LABEL_7;
	if (!*argv)
		goto LABEL_75;
	if (v6 != 3)
	{
		if (v6 >= 3)
		{
			if (v6 != 4)
				goto LABEL_75;
			if (argv[2])                            // argv[2] =0 ,0xFF的判断
			{
				if (argv[2] != 0xFF)
				{
				LABEL_75:                                       // Argv[0] =0
					PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
					return 2;
				}

				IOCTRLSelect_sub_8030606(1u, 1u);
				Delay_802EF34(0x1F4);
				sendAddressToEcu_sub_802CC82(argv[1]);
				SC_com_portMode_20004964.BaudRate = 0;

				IOCTRLSelect_sub_8030606(0, 3u);
				SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
				if (!SC_com_portMode_20004964.BaudRate)
				{
					Delay_802EF34(0xFA0);

					IOCTRLSelect_sub_8030606(1u, 1u);
					IOCTRLSet_sub_8030658(1, 0x1F4);
					sendAddressToEcu_sub_802CC82(argv[1]);

					IOCTRLSelect_sub_8030606(0, 3u);
					SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
					if (!SC_com_portMode_20004964.BaudRate)
						goto LABEL_84;
				}
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			LABEL_86:
				v3 = 3;
				for (i = 0; i < 5; ++i)
				{
					if (!ComByte_sub_802F6CC(Keyword, 0x7D0))
						goto LABEL_102;
					ans[v3++] = Keyword[0];
					if (i == 1)
						k = Keyword[0];
				}
				ans[1] = 1;
				ans[2] = 5;
				IOCTRLInit_sub_802C570();
				if (argv[3] == 0xFF)
				{
					Keyword[0] = 0;
					Delay_802EF34(0x14);
					ComSendByte_sub_802F1E0((unsigned __int8)~k);
					v19 = argv[4];
					if (!argv[4])
					{
					LABEL_94:
						PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
						return 2;
					}
					ans[1] += v19;
					for (j = 0; j < v19; ++j)
					{
						if (!ComByte_sub_802F6CC(Keyword, 0x1F4))
							goto LABEL_102;
						v21 = Keyword[0];
						ans[v3] = Keyword[0] + 1;
						v22 = v3 + 1;
						ans[v22] = Keyword[0];
						v3 = v22 + 1;
						for (k = 0; k < v21; ++k)
						{
							if (!ComByte_sub_802F6CC(Keyword, 0x12C))
								goto LABEL_102;
							ans[v3++] = Keyword[0];
						}
					}
					return v3;
				}
			LABEL_61:
				PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
				return 2;
			}
			IOCTRLSelect_sub_8030606(1u, 1u);
			Delay_802EF34(0x1F4);
			sendAddressToEcu_sub_802CC82(argv[1]);
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (ComByte_sub_802F6CC(&k, 0x9F6) && k == 0x55)
				goto LABEL_86;
			Delay_802EF34(0xFA0);

			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CC82(argv[1]);
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (ComByte_sub_802F6CC(&k, 2550))
			{
				if (k == 0x55)
					goto LABEL_86;
			}
		LABEL_102:
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			return 2;
		}
	LABEL_7:                                        // case Argv[0] ==1
		if (argv[2])
		{
			if (argv[2] != 0xFF)
				goto LABEL_75;

			IOCTRLSelect_sub_8030606(1u, 1u);
			Delay_802EF34(0x1F4);
			sendAddressToEcu_sub_802CC82(argv[1]);
			IOCTRLInit_sub_802C570();
			SC_com_portMode_20004964.BaudRate = 0;

			IOCTRLSelect_sub_8030606(0, 3u);
			SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
			if (!SC_com_portMode_20004964.BaudRate)
			{
				Delay_802EF34(0xFA0);

				IOCTRLSelect_sub_8030606(1u, 1u);
				IOCTRLSet_sub_8030658(1, 0x1F4);
				sendAddressToEcu_sub_802CC82(argv[1]);

				IOCTRLSelect_sub_8030606(0, 3u);
				SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
				if (!SC_com_portMode_20004964.BaudRate)
					goto LABEL_84;
			}
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		}
		else
		{
			IOCTRLSelect_sub_8030606(1u, 1u);
			Delay_802EF34(0x1F4);
			sendAddressToEcu_sub_802CC82(argv[1]);
			IOCTRLInit_sub_802C570();
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
			{
				Delay_802EF34(0xFA0);
				IOCTRLSelect_sub_8030606(1u, 1u);
				sendAddressToEcu_sub_802CC82(argv[1]);
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
					goto LABEL_102;
			}
		}
		for (l = 0; l < 5; ++l)
		{
			if (!ComByte_sub_802F6CC(Keyword, 0x7D0))
				goto LABEL_102;
			if (l == 1)
				k = Keyword[0];
		}
		if (!argv[3])
		{
			IOCTRLInit_sub_802C570();
			PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
			return 2;
		}
		if (argv[3] == 0xFF)
		{
			IOCTRLInit_sub_802C570();
			Delay_802EF34(0x14);
			k = 0xFF - k;
			ComSendByte_sub_802F1E0(k);
			Keyword[0] = 0;
			v9 = argv[4];
			if (!argv[4])
				goto LABEL_94;
			ans[1] = v9;
			v3 = 2;
			for (m = 0; m < v9; ++m)
			{
				if (!ComByte_sub_802F6CC(Keyword, 0x1F4))
					goto LABEL_102;
				v11 = Keyword[0];
				ans[v3] = Keyword[0] + 1;
				v12 = v3 + 1;
				ans[v12] = Keyword[0];
				v3 = v12 + 1;
				for (k = 0; k < v11; ++k)
				{
					if (!ComByte_sub_802F6CC(Keyword, 0x12C))
						goto LABEL_102;
					ans[v3++] = Keyword[0];
				}
			}
		}
		return v3;
	}
	if (argv[2])
	{
		if (argv[2] != 0xFF)
			goto LABEL_75;
		IOCTRLSelect_sub_8030606(1u, 1u);
		Delay_802EF34(0x1F4);
		sendAddressToEcu_sub_802CC82(argv[1]);
		IOCTRLInit_sub_802C570();
		SC_com_portMode_20004964.BaudRate = 0;
		IOCTRLSelect_sub_8030606(0, 3u);
		SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
		if (!SC_com_portMode_20004964.BaudRate)
		{
			Delay_802EF34(0xFA0);
			IOCTRLSelect_sub_8030606(1u, 1u);
			IOCTRLSet_sub_8030658(1, 0x1F4);
			sendAddressToEcu_sub_802CC82(argv[1]);
			IOCTRLSelect_sub_8030606(0, 3u);
			SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
			if (!SC_com_portMode_20004964.BaudRate)
			{
			LABEL_84:
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				return 2;
			}
		}
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	}
	else
	{
		IOCTRLSelect_sub_8030606(1u, 1u);
		Delay_802EF34(0x1F4);
		sendAddressToEcu_sub_802CC82(argv[1]);
		IOCTRLInit_sub_802C570();
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
		{
			Delay_802EF34(0xFA0);
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CC82(argv[1]);
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&k, 0x9F6) || k != 0x55)
				goto LABEL_102;
		}
	}
	v3 = 3;
	for (n = 0; n < 5; ++n)
	{
		if (!ComByte_sub_802F6CC(Keyword, 0x7D0))
			goto LABEL_102;
		ans[v3++] = Keyword[0];
		if (n == 1)
			k = Keyword[0];
	}
	ans[1] = 1;
	ans[2] = 5;
	IOCTRLInit_sub_802C570();
	if (argv[3] != 0xFF)
		goto LABEL_61;
	Keyword[0] = 0;
	Delay_802EF34(0x14);
	ComSendByte_sub_802F1E0((unsigned __int8)~k);
	v14 = argv[4];
	if (v14 < 2)
		goto LABEL_94;
	ans[1] += v14;
	for (ii = 1; ii < v14; ++ii)
	{
		if (!ComByte_sub_802F6CC(Keyword, 0x1F4))
			goto LABEL_102;
		v16 = Keyword[0];
		ans[v3] = Keyword[0] + 1;
		v17 = v3 + 1;
		ans[v17] = Keyword[0];
		v3 = v17 + 1;
		for (k = 0; k < v16; ++k)
		{
			if (!ComByte_sub_802F6CC(Keyword, 0x12C))
				goto LABEL_102;
			ans[v3++] = Keyword[0];
		}
	}
	return v3;
}



// 和982源码不一致
int ID600B_SetLinkNoAnswer_1_sub_804CA4C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 send_length; // r7
	int result; // r0

	if (timer_open_flag_2000C6B7 == 1)
		TimerStop_sub_802EF10(0);
	send_length = *argv;
	Keep_Link_200046C0.field_46 = 0;
	Keep_Link_200046C0.idleSendLen = send_length;
	Keep_Link_200046C0.linkState = 0;
	if (send_length)
	{
		Copysub_802FB50(Keep_Link_200046C0.dataBuf, argv + 1, send_length);
		Keep_Link_200046C0.idleRecvLen = argv[send_length + 1];
		if (!argv[send_length + 2])
		{
		LABEL_11:
			PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
			return 2;
		}
		Keep_Link_200046C0.IdleTime = 10 * argv[send_length + 2];
		Keep_Link_200046C0.linkType = 4;
		if (argv[1] == 0x55 && argv[2] == 0xAA)
		{
			Keep_Link_200046C0.linkType = 1;
			if ((argv[6] & 0x80) != 0 && send_length >= 0x14u || !checkXOR_Parity_sub_802BD40(argv[3] + 2, argv + 3))
				goto LABEL_11;
			setCanbusLinkDataToken_sub_802BEB4();
		}
		if (Keep_Link_200046C0.linkType == 1)
		{
			Keep_Link_200046C0.rightState = 5;
			SC_TagISO15765_2000C334.m_PakMode = 1;
			TimerConfig_sub_802EDAE(0, 0xAu);
			TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_CML_ISO15765_Time_sub_802DFC8);
			TIM_sub_802EEEC(0);
			timer_open_flag_2000C6B7 = 1;
		}
		else if (Keep_Link_200046C0.linkType == 4)
		{
			TimerConfig_sub_802EDAE(0, SC_TagKWP2000_20004974.m_MsTime);
			Keep_Link_200046C0.rightState = 5;
			TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_setlinkkeep_sub_802C1EC);
			TIM_sub_802EEEC(0);
			timer_open_flag_2000C6B7 = 1;
		}
		PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
		result = 2;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TimerStop_sub_802EF10(0);
		timer_open_flag_2000C6B7 = 0;
		Keep_Link_200046C0.linkType = 0;
		PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
		result = 2;
	}
	return result;
}

//设置canbus的链路保持
int ID600C_SetCANBusLinkData_1_sub_804C9BA(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	return ID6004Fun_SetLinkData_1_sub_804C4CA(argc, argv, ans);
}


// // Funtion: 设置CANBUS链路保持
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : recv: 60,0D,06,80,98,f1,01,3e,48,06,64
// //                      1) 2) 3) 4) 5) 6) 7) 8) 9)
// //          1) 链路命令长度(若为0，则终止链路)
// //          2) 3) 4) 5) 6) 7) 链路数据包
// //          8) 未知或无意义
// //          9) 其值乘10 即：0x64*10=1000（ms）为链路间隔时间，若为0，则返回错误
// //          send: ff,00, 固定回 ff 00 表示成功
int ID600DFun_SetCANBus2LinkData_1_sub_804C9CE(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v3; // r7

	if (argv[2] + (argv[1] << 8) == 0x55DD)
		v3 = SetLinkData_2_sub_804C77E(argc, argv, ans);          // 这个函数的功能
	else
		v3 = ID6004Fun_SetLinkData_1_sub_804C4CA(argc, argv, ans);
	return v3;
}




// 目前来看 好像除了返回ok 或则FNG 没有设置电平的作用
int ID600E_sub_804CA0C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int result; // r0

	if (!argv[1] || argv[1] == 255)
	{
		PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
		result = 2;
	}
	else
	{
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}




// // Funtion: LANDROVER ABS 地址码触发函数
// //  tool -> 地址码   ECU->  55H  KW1  KE2
// //  tool -> byte1    ECU->  0x42
// //  tool -> byte2    ECU->  byte3
// //  tool -> byte3    ECU->  byte4
// //  tool -> byte4    ECU->  byte5
// //  tool -> byte5    ECU->  byte6
// //  完成触发
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6011
// // Funtion: LANDROVER ABS 地址码触发函数
// //  tool -> 地址码   ECU->  55H  KW1  KE2
// //  tool -> byte1    ECU->  0x42
// //  tool -> byte2    ECU->  byte3
// //  tool -> byte3    ECU->  byte4
// //  tool -> byte4    ECU->  byte5
// //  tool -> byte5    ECU->  byte6
// //  完成触发
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6011
int ID6011_LandroverABSEnter_1_sub_802423C(int argc, unsigned __int8 *argv, unsigned __int8 *Ans)
{
	int result; // r0
	unsigned __int8 v6[24]; // [sp+0h] [bp-18h] BYREF

	IOCTRLSelect_sub_8030606(1u, 1u);
	sendAddressToEcu_sub_802CC82(*argv);          // 发送地址码
	IOCTRLInit_sub_802C570();
	ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	if (!ComByte_sub_802F6CC(v6, 0x9F6))        // 接收第一个字节
	{
		IOCTRLSelect_sub_8030606(1u, 1u);
		sendAddressToEcu_sub_802CC82(*argv);
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		if (!ComByte_sub_802F6CC(v6, 0x9F6))
			goto LABEL_14;
	}
	if (!ComByte_sub_802F6CC(v6, 0x3E8) || !ComByte_sub_802F6CC(v6, 0x7D0))// 接收第二 三个字节
		goto LABEL_14;
	if (argv[1])
	{
		Delay_802EF34(0x27);
		ComSendByte_sub_802F1E0(argv[2]);           // 发送第3个字节
		if (!ComByte_sub_802F6CC(v6, 0x320)
			|| v6[0] != 0x42
			|| (ComSendByte_sub_802F1E0(argv[3]), Delay_802EF34(2), !ComByte_sub_802F6CC(v6, 0x12C))// 发送第四个字节
			|| (ComSendByte_sub_802F1E0(v6[0]), !ComByte_sub_802F6CC(v6, 0x12C))
			|| (ComSendByte_sub_802F1E0(v6[0]), !ComByte_sub_802F6CC(v6, 0x12C)))
		{
		LABEL_14:
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
			return 2;
		}
		ComSendByte_sub_802F1E0(v6[0]);
		if (ComByte_sub_802F6CC(v6, 0x12C))
			PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
		else
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
		result = 2;
	}
	else
	{
		PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
		result = 2;
	}
	return result;
}




// // Funtion: BOSCH地址码触发函数  bosch协议专用
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:地址码值
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、当KW2为0x8f时，返回00 00
// //                4、当KW2非0x8f，并正常接收版本信息数据时，ans的格式为：总帧数 第一帧数据  第二帧数据......第N帧数据
// //                如ans[] = {00,04,0f,01,f6,b0,36,42,39,30,36,30,33,32,41,20,20,03,17,03,f6,32,2e,30,4c,20,32,56,20,45,
// //                           55,32,20,20,20,20,20,20,20,20,20,03,07,05,f6,35,32,31,36,03,08,07,f6,00,00,06,00,00,03}
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6014
int ID6014FunShangHuanBoschSystem_1_sub_8023FC4(int argc, unsigned __int8 *argv, unsigned __int8 *Ans)
{
	char flag_L_Line; // r9
	int result; // r0
	int dataLenth; // r8
	unsigned int i; // r7
	SC_PAKRECV PakRecv; // [sp+0h] [bp-30h] BYREF
	SC_PAKSEND PakSend; // [sp+8h] [bp-28h] BYREF
	unsigned __int8 v11[32]; // [sp+10h] [bp-20h] BYREF

	Delay_802EF34(0x32);
	PakSend.PakdataAddr = SendPakdataPackData_2000BDF4;
	PakSend.PakLenth = 4;
	SendPakdataPackData_2000BDF4[0] = 3;
	SendPakdataPackData_2000BDF4[1] = 0;
	SendPakdataPackData_2000BDF4[2] = 9;
	SendPakdataPackData_2000BDF4[3] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	SC_TagKWP1281_200043E4.m_chHoldDig[0] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDig[1] = 0;
	SC_TagKWP1281_200043E4.m_chHoldDig[2] = 9;
	SC_TagKWP1281_200043E4.m_chHoldDig[3] = 3;
	PakRecv.PakdataAddr = receive_buff_2000BF20;
	TimerRelease_sub_802EF76(0);
	flag_L_Line = CheckLLine_sub_802C580();
	SC_TagKWP1281_200043E4.m_Idletime = 0x258;
	SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	SC_TagKWP1281_200043E4.m_SendFinishFlag = 1;
	EnableLLine_1_sub_802C560();

	IOCTRLSelect_sub_8030606(1u, 1u);
	sendAddressToEcu_sub_802CC82(*argv);
	IOCTRLSelect_sub_8030606(0, 3u);
	SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x2A);
	ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	if (ComByte_sub_802F6CC(v11, 0x3E8) && ComByte_sub_802F6CC(v11, 0x7D0))
	{
		if (flag_L_Line == 1)
			EnableLLine_1_sub_802C560();
		else
			IOCTRLInit_sub_802C570();
		Delay_802EF34(0x14);
		ComSendByte_sub_802F1E0((unsigned __int8)~v11[0]);
		*Ans = 0;
		Ans[1] = 0;
		dataLenth = 2;
		SetTIMCLOCK_RCC_APB1PeriphClockCmd_sub_802ED88(2);
		SC_TagKWP1281_200043E4.m_nMScount = 0;
		SC_TagKWP1281_200043E4.m_chCount = 0;
		Keep_Link_200046C0.rightState = 2;
		if (SC_com_portMode_20004964.BaudRate >= 5000u)
		{
			TimerConfig_sub_802EDAE(0, 1u);
			SC_TagKWP1281_200043E4.m_nBtyetime = 2;
			SC_TagKWP1281_200043E4.m_nFrameTime = 0x16;
			SC_TagKWP1281_200043E4.m_ReserveTime = 2;
		}
		else
		{
			TimerConfig_sub_802EDAE(0, 1u);
			SC_TagKWP1281_200043E4.m_nBtyetime = 6;
			SC_TagKWP1281_200043E4.m_nFrameTime = 0x1E;
			SC_TagKWP1281_200043E4.m_ReserveTime = 3;
		}
		SC_TagKWP1281_200043E4.m_LinkFG = 1;
		timer_open_flag_2000C6B7 = 1;
		TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_CML_KWP1281_Time_sub_802C5B0);
		ComInterruptFuntionLoad_sub_802F8A0((int)SC_CML_KWP1281_Comread_sub_802C860, 1u);
		ComInterruptFuntionLoad_sub_802F8A0((int)SC_CML_KWP1281_Comsend_sub_802C7DC, 0);
		TIM_sub_802EEEC(0);
		ComReadSign_sub_802F614(1);
		if (SC_CML_KWP1281_Recv_sub_802CBCC(&PakRecv))
		{
			while (PakRecv.PakdataAddr[2] != 9 && PakRecv.PakdataAddr[2] != 0xF7 && PakRecv.PakLenth >= 3)
			{
				++Ans[1];
				for (i = 0; i < PakRecv.PakLenth; ++i)
					Ans[dataLenth++] = PakRecv.PakdataAddr[i];
				if (!SC_CML_KWP1281_Sendsub_802CB36(&PakSend) || !SC_CML_KWP1281_Recv_sub_802CBCC(&PakRecv))
					goto LABEL_21;
			}
			result = dataLenth;
		}
		else
		{
		LABEL_21:
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
			result = 2;
		}
	}
	else
	{
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
		result = 2;
	}
	return result;
}




// // Funtion: BOSCH地址码触发函数  bosch协议专用 接受五个关键字，对第二个关键字取反发回
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:地址码值
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 第一帧数据  第二帧数据......第N帧数据
// //                如ans[] = {00,04,0f,01,f6,b0,36,42,39,30,36,30,33,32,41,20,20,03,17,03,f6,32,2e,30,4c,20,32,56,20,45,
// //                           55,32,20,20,20,20,20,20,20,20,20,03,07,05,f6,35,32,31,36,03,08,07,f6,00,00,06,00,00,03}
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6015
int ID6015Fun_FiatBoschSystem_1_sub_80227CC(int argc, unsigned __int8 *argv, unsigned __int8 *Ans)
{
	char flag_L_Line; // r10
	unsigned __int8 v6; // r9
	int dataLenth; // r8
	unsigned int i; // r7
	int Ret; // r0
	unsigned __int8 v10[4]; // [sp+0h] [bp-38h] BYREF
	SC_PAKRECV PakRecv; // [sp+4h] [bp-34h] BYREF
	SC_PAKSEND PakSend; // [sp+Ch] [bp-2Ch] BYREF

	TimerRelease_sub_802EF76(0);
	flag_L_Line = CheckLLine_sub_802C580();
	SC_TagKWP1281_200043E4.m_Idletime = 0x258;
	SC_TagKWP1281_200043E4.m_SendFinishFlag = 1;
	SC_TagKWP1281_200043E4.m_LinkFG = 1;
	EnableLLine_1_sub_802C560();

	IOCTRLSelect_sub_8030606(1u, 1u);
	sendAddressToEcu_sub_802CC82(*argv);
	if (flag_L_Line == 1)
		EnableLLine_1_sub_802C560();
	else
		IOCTRLInit_sub_802C570();
	IOCTRLSet_sub_8030658(1, 0x14);
	IOCTRLSelect_sub_8030606(0, 3u);
	SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x19);
	ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	Delay_802EF34(0xA);
	if (!ComByte_sub_802F6CC(v10, 0x3E8))
		goto LABEL_25;
	Delay_802EF34(0xA);
	if (!ComByte_sub_802F6CC(v10, 0x3E8))
		goto LABEL_25;
	v6 = v10[0];
	Delay_802EF34(0xA);
	if (!ComByte_sub_802F6CC(v10, 0x3E8))
		goto LABEL_25;
	Delay_802EF34(0xA);
	if (!ComByte_sub_802F6CC(v10, 0x3E8))
		goto LABEL_25;
	Delay_802EF34(0xA);
	if (!ComByte_sub_802F6CC(v10, 0x3E8))
		goto LABEL_25;
	ComSendByte_sub_802F1E0((unsigned __int8)~v6);
	*Ans = 0;
	Ans[1] = 0;
	dataLenth = 2;
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	SC_TagKWP1281_200043E4.m_chCount = 0;
	Keep_Link_200046C0.rightState = 2;
	PakSend.PakdataAddr = SendPakdataPackData_2000BDF4;
	PakSend.PakLenth = 4;
	SendPakdataPackData_2000BDF4[0] = 3;
	SendPakdataPackData_2000BDF4[1] = 0;
	SendPakdataPackData_2000BDF4[2] = 9;
	SendPakdataPackData_2000BDF4[3] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	SC_TagKWP1281_200043E4.m_chHoldDig[0] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDig[1] = 0;
	SC_TagKWP1281_200043E4.m_chHoldDig[2] = 9;
	SC_TagKWP1281_200043E4.m_chHoldDig[3] = 3;
	PakRecv.PakdataAddr = receive_buff_2000BF20;
	SetTIMCLOCK_RCC_APB1PeriphClockCmd_sub_802ED88((int)receive_buff_2000BF20);
	if (SC_com_portMode_20004964.BaudRate >= 0x1388u)
	{
		TimerConfig_sub_802EDAE(0, 1u);
		SC_TagKWP1281_200043E4.m_nBtyetime = 2;
		SC_TagKWP1281_200043E4.m_nFrameTime = 0x16;
		SC_TagKWP1281_200043E4.m_ReserveTime = 2;
	}
	else
	{
		TimerConfig_sub_802EDAE(0, 1u);
		SC_TagKWP1281_200043E4.m_nBtyetime = 6;
		SC_TagKWP1281_200043E4.m_nFrameTime = 0x1E;
		SC_TagKWP1281_200043E4.m_ReserveTime = 3;
	}
	TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_CML_KWP1281_Time_sub_802C5B0);//  // 加载串口中断
	ComInterruptFuntionLoad_sub_802F8A0((int)SC_CML_KWP1281_Comread_sub_802C860, 1u);
	ComInterruptFuntionLoad_sub_802F8A0((int)SC_CML_KWP1281_Comsend_sub_802C7DC, 0);
	timer_open_flag_2000C6B7 = 1;
	TIM_sub_802EEEC(0);
	ComReadSign_sub_802F614(1);                   // 接收回复
	if (SC_CML_KWP1281_Recv_sub_802CBCC(&PakRecv))
	{
		while (PakRecv.PakdataAddr[2] != 9 && PakRecv.PakdataAddr[2] != 0xF7 && PakRecv.PakLenth >= 3)
		{
			++Ans[1];
			for (i = 0; i < PakRecv.PakLenth; ++i)
				Ans[dataLenth++] = PakRecv.PakdataAddr[i];
			if (!SC_CML_KWP1281_Sendsub_802CB36(&PakSend) || !SC_CML_KWP1281_Recv_sub_802CBCC(&PakRecv))
				goto LABEL_25;
		}
		Ret = dataLenth;
	}
	else
	{
	LABEL_25:
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
		Ret = 2;
	}
	return Ret;
}



int ID6016FunBenz38SelectLine_1_sub_804CC78(int argc, unsigned __int8 *argv, unsigned __int8 *Ans)
{
	unsigned __int8 connector_type; // r9
	char rxdflg; // r10
	int ii; // r11
	int result; // r0
	int ioadd; // r11
	char i; // r8
	char v11; // r7
	_BYTE PostionBuf[80]; // [sp+0h] [bp-50h] BYREF

	connector_type = 0x80;
	rxdflg = 0;
	memcpy(PostionBuf, position_804D764, 0x28u);
	IOCTRLSelect_sub_8030606(0x13u, 0);
	IOCTRLSet_sub_8030658(1, 1);
	IOCTRLSelect_sub_8030606(1u, 0);
	IOCTRLSet_sub_8030658(1, 1);
	IOCTRLSelect_sub_8030606(0, 2u);
	Set2000C6BF_is_1_sub_8030D78();
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	CMPHY_Relay_Reset_sub_8030B88();
	ii = (char)*argv;
	if (ii < 0x27)
	{
		SC_RelayState_200049DC.LogicType = 1;
		SC_RelayState_200049DC.LevelType = 0xC;
		SC_RelayState_200049DC.OutputChannel = 2;
		SC_RelayState_200049DC.InputChannel = 2;
		SC_RelayState_200049DC.Dts = 2;
		SC_RelayState_200049DC.CommType = 5;        //  //benz 38 里面没有CAN 协议ziyingzhu 2009-5-25 
		CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
		Set2000C6BF_is_1_sub_8030D70();
		Delay_802EF34(0xA);
		if (IOCTRLGet_sub_80306E2())
			rxdflg = 0xFF;
		Delay_802EF34(0xA);
		if (IOCTRLGet_sub_80306E2() || rxdflg)
		{
			if (!unk_2000C6BF)
			{
				unk_2000C6BF = 0;
				connector_type = 0x80;
				Set2000C6BF_is_1_sub_8030D78();
				SC_RelayState_200049DC.OutputChannel = 1;
				SC_RelayState_200049DC.InputChannel = 0xD;
				SC_RelayState_200049DC.LLine = 1;
				CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
				Set2000C6BF_is_1_sub_8030D70();
			}
		}
		else
		{
			unk_2000C6BF = 1;                         // 这个字段的意思没弄明白
			connector_type = 0x81;
			Set2000C6BF_is_1_sub_8030D78();
			SC_RelayState_200049DC.OutputChannel = 1;
			SC_RelayState_200049DC.InputChannel = 3;
			SC_RelayState_200049DC.LLine = 1;
			CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
			Set2000C6BF_is_1_sub_8030D70();
		}
		Delay_802EF34(0xA);
		ioadd = (char)PostionBuf[(char)(ii - 1)];
		for (i = 0; i < 8; ++i)
		{
			Delay_802EF34(2);
			GPIO_WriteBit_Delay_sub_803069E(0x13, 0, 0);
			v11 = ioadd & 0x80;
			ioadd *= 2;
			if (v11)
				GPIO_WriteBit_Delay_sub_803069E(1, 1, 0);
			else
				GPIO_WriteBit_Delay_sub_803069E(1, 0, 0);
			Delay_802EF34(5);
			GPIO_WriteBit_Delay_sub_803069E(0x13, 1, 0);
		}
		Delay_802EF34(2);
		GPIO_WriteBit_Delay_sub_803069E(1, 1, 0);
		Delay_802EF34(2);
		GPIO_WriteBit_Delay_sub_803069E(0x13, 1, 0);
		Delay_802EF34(0x1F4);
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		*Ans = 2;
		Ans[1] = 0xFF;
		Ans[2] = connector_type;
		result = 3;
	}
	else
	{
		*Ans = 0;
		Ans[1] = 2;
		result = 2;
	}
	return result;
}



// 982没有这个函数
int ID6017Fun_SetMitLinkKeep_sub_804CE88(int argc, unsigned __int8 *argv, unsigned __int8 *Ans)
{
	int dataLenth; // r8
	unsigned __int8 argvPos; // r10
	char v7; // r9
	unsigned __int8 v9; // r9
	unsigned __int8 i; // r7

	dataLenth = *argv;
	SC_TagISO15765_2000C334.m_PakMode = *argv;
	Keep_Link_200046C0.field_46 = 0;              // 这个字段也不知道是什么意思
	argvPos = 1;
	while ((_BYTE)dataLenth--)
	{
		v7 = argv[argvPos] + 2;
		argvPos += v7;
		if (!v7)
		{
			PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
			return 2;
		}
	}
	Keep_Link_200046C0.IdleTime = 10 * argv[argvPos];
	v9 = 1;
	for (i = 0; i < (unsigned int)*argv; ++i)
		v9 += argv[v9] + 2;
	Copysub_802FB50(Keep_Link_200046C0.dataBuf, argv + 2, (unsigned __int8)(v9 + 1));
	KeepLinkFrameSet_sub_802BF9E();
	Keep_Link_200046C0.rightState = 5;
	TimerConfig_sub_802EDAE(0, 0xAu);
	TimerInterruptFuntionLoad_sub_802EF66(0, (int)TImCANLinkSend_sub_802E040);
	TIM_sub_802EEEC(0);
	timer_open_flag_2000C6B7 = 1;
	PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
	return 2;
}




// 60 18 Argv:0D 55 AA 09 61 01 04 DE 20 40 30 00 00 E3 A0
//            0D 55 AA 09 61 01 04 DE 20 10 30 00 00 B3 94 
int ID6018_SetEnterFrameData_1_sub_8037060(int argc, unsigned __int8 *argv, unsigned __int8 *Ans)
{
	int result; // r0

	CanEnterFrame_2000C47C.dataLenth = *argv;
	if (CanEnterFrame_2000C47C.dataLenth)
	{
		if ((argv[6] & 0x80) != 0)
		{
			CanEnterFrame_2000C47C.data[30] = argv[12];
		}
		else if (argv[9] != 0x30 || argv[10] == 0x30)
		{
			CanEnterFrame_2000C47C.data[30] = argv[11];
		}
		else
		{
			CanEnterFrame_2000C47C.data[30] = argv[10];// CanEnterFrame_2000C47C.data  不太清除data的大小是否正确
		}
		memmove(CanEnterFrame_2000C47C.data, argv + 6, argv[3] - 2);// 复制命令的有效数据
		memmove(Ans, szFOK_20004A04, 4u);
		result = 2;
	}
	else
	{
		memmove(Ans, szFBREAK_20004A0C, 4u);
		result = 2;
	}
	return result;
}


// // Funtion: 设置接头与主机通讯波特率（无效果）
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : recv: 60,19,00,00,25,00
// //                      1) 2) 3) 4)
// //          1)2)3)4)  通讯波特率
// //          send: ff,00, 表示成功
int ID6019Fun_SetConnectorBaudRate_1_sub_804CF62(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	*ans = -1;
	ans[1] = 0;
	return 2;
}




// // Funtion: BOSCH地址码触发函数  bosch协议专用
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:发送地址码模式
// //     模式1
// //          argv[1]:地址码值
// //          argv[2]:是否使能L线标识，最高位为1则使能L线，否则禁能L线
// //          argv[3]:是否自动计算波特率，为0则使用设定的波特率，为0xff则自动计算波特率
// //          argv[4]:无意义
// //          argv[5]:KW2和KW2取反之间的时间延时参数，毫秒级
// //          argv[6]:判定是否KW2取反发回，为0则不取反发回，为0XFF则取反发回
// //          argv[7]:如argv[6]非0，argv[7]为0表示必须要收到ECU发来的地址码取反字节，如argv[6]为0，argv[7]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[7]非0，则argv[7]表示要从ECU接受的数据的帧数
// //          argv[8]~arg[8+argv[7]-1]:如argv[7]为0，这些字节无意义,如argv[7]非0，这些字节分别表示接收的每一帧数据的长度
// //     模式2
// //          argv[1]:地址码值
// //          argv[2]:是否使能L线标识，最高位为1则使能L线，否则禁能L线
// //          argv[3]:最高位为1表示需要计算地址码的波特率，并作为计算波特率的一个参数，否则表示地址码波特率为200.
// //          argv[4]:argv[3]最高位为1时，argv[4]为计算波特率的一个参数，argv[3]最高位不为1时，argv[4]无意义
// //          argv[5]:无意义
// //          argv[6]:KW2和KW2取反之间的时间延时参数，毫秒级
// //          argv[7]:判定是否KW2取反发回，为0则不取反发回，为0XFF则取反发回
// //          argv[8]:如argv[7]非0，argv[8]为0表示必须要收到ECU发来的地址码取反字节，如argv[7]为0，argv[8]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[8]非0，则argv【8]表示要从ECU接受的数据的帧数
// //          argv[9]~arg[9+argv[8]-1]:如argv[8]为0，这些字节无意义,如argv[8]非0，这些字节分别表示接收的每一帧数据的长度
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、当KW2为0x8f时，返回00 00
// //                4、当KW2非0x8f，并正常接收版本信息数据时，ans的格式为：总帧数 第一帧数据  第二帧数据......第N帧数据
// //                如ans[] = {00,04,0f,01,f6,b0,36,42,39,30,36,30,33,32,41,20,20,03,17,03,f6,32,2e,30,4c,20,32,56,20,45,
// //                           55,32,20,20,20,20,20,20,20,20,20,03,07,05,f6,35,32,31,36,03,08,07,f6,00,00,06,00,00,03}
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 601a
int ID601A_SendAddressCodeTimeAdjustable_1_sub_8021FE4(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int CaseArgv0Val; // r0
	unsigned int framenum; // r6
	int ansPostion; // r11
	int argvLen; // r7
	unsigned int i; // r10
	int frameLen; // r0 MAPDST
	int tAnsPos; // r11
	int tFrameLen; // r0
	unsigned int baudrate; // r9
	unsigned int j; // r10
	int v18; // r7
	unsigned int k; // r10
	char v20; // r0
	unsigned __int8 rcvbyte; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 RcvByte; // [sp+1h] [bp-2Fh] BYREF
	unsigned __int8 OBD_FID1; // [sp+2h] [bp-2Eh]
	unsigned __int8 keyWord[44]; // [sp+4h] [bp-2Ch] BYREF 这个大小总是感觉有点问题

	*(_DWORD *)&keyWord[4] = argc;
	rcvbyte = 0;
	*(_DWORD *)keyWord = 0;
	OBD_FID1 = argv[2];
	CaseArgv0Val = *argv;
	if (CaseArgv0Val == 1)
	{
		if (argv[3])
		{
			if (argv[3] != 0xFF)
			{
			LABEL_6:
				PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
				return 2;
			}
			Delay_802EF34(0x1F4);                     // 自动计算0x55波特率

			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CC82(argv[1]);
			IOCTRLInit_sub_802C570();
			if ((OBD_FID1 & 0x80) != 0)
				EnableLLine_1_sub_802C560();
			SC_com_portMode_20004964.BaudRate = 0;

			IOCTRLSelect_sub_8030606(0, 3u);
			SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
			if (!SC_com_portMode_20004964.BaudRate)
			{
				Delay_802EF34(0xFA0);

				IOCTRLSelect_sub_8030606(1u, 1u);
				IOCTRLSet_sub_8030658(1, 0x1F4);
				sendAddressToEcu_sub_802CC82(argv[1]);
				IOCTRLInit_sub_802C570();

				IOCTRLSelect_sub_8030606(0, 3u);
				SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
				if (!SC_com_portMode_20004964.BaudRate)
				{
					ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					return 2;
				}
			}
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		}
		else
		{
			Delay_802EF34(0x1F4);

			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CC82(argv[1]);
			IOCTRLInit_sub_802C570();
			if ((OBD_FID1 & 0x80) != 0)
				EnableLLine_1_sub_802C560();
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
			{
				Delay_802EF34(0xFA0);
				IOCTRLSelect_sub_8030606(1u, 1u);
				sendAddressToEcu_sub_802CC82(argv[1]);
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
					goto LABEL_78;
			}
		}
		RcvByte = 0;
		if (!ComByte_sub_802F6CC(&RcvByte, 0x3E8) || !ComByte_sub_802F6CC(&RcvByte, 0x7D0))
		{
		LABEL_78:
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			return 2;
		}
		IOCTRLSet_sub_8030658(1, 0x3E8 * argv[5]);
		if (argv[6])
		{
			if (argv[6] != 0xFF)
				goto LABEL_38;
			RcvByte = 0xFF - RcvByte;
			ComSendByte_sub_802F1E0(RcvByte);
			if (!argv[7])
			{
				if (ComByte_sub_802F6CC(&RcvByte, 0x12C))
				{
					PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
					IOCTRLInit_sub_802C570();
				}
				else
				{
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				}
				return 2;
			}
		}
		else if (!argv[7])
		{
			PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
			IOCTRLInit_sub_802C570();
			return 2;
		}
		framenum = argv[7];
		*ans = 0;
		ans[1] = framenum;
		ansPostion = 2;
		argvLen = 8;
		for (i = 0; i < framenum; ++i)
		{
			frameLen = argv[argvLen++];
			if (!frameLen)
				goto LABEL_38;
			ans[ansPostion] = frameLen;
			tAnsPos = ansPostion + 1;
			if (!ComByte_sub_802F6CC(&RcvByte, 0x3E8))
				goto LABEL_78;
			ans[tAnsPos] = RcvByte;
			ansPostion = tAnsPos + 1;
			--frameLen;
			while (1)
			{
				tFrameLen = frameLen--;
				if (!tFrameLen || !ComByte_sub_802F6CC(&RcvByte, 0x64))
					break;
				ans[ansPostion++] = RcvByte;
			}
		}
		return ansPostion;
	}
	if (CaseArgv0Val != 2)
		goto LABEL_6;
	if ((argv[3] & 0x80) != 0)
	{
		baudrate = 0x8CA00u / (0x10000 - (argv[4] + (argv[3] << 8)));

		IOCTRLSelect_sub_8030606(1u, 1u);
		sendAddressToEcu_sub_802CF50(argv[1], baudrate);
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
		{
			Delay_802EF34(0xFA0);
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CF50(argv[1], baudrate);
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
				goto LABEL_78;
		}
	}
	else
	{

		IOCTRLSelect_sub_8030606(1u, 1u);
		sendAddressToEcu_sub_802CF50(argv[1], 0xC8u);
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
		{
			Delay_802EF34(0xFA0);
			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CF50(argv[1], 0xC8u);
			IOCTRLInit_sub_802C570();
			if ((OBD_FID1 & 0x80) != 0)
				EnableLLine_1_sub_802C560();
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
				goto LABEL_78;
		}
	}
	for (j = 0; j < 2; ++j)
	{
		if (!ComByte_sub_802F6CC(&keyWord[j], 0x1388))
			goto LABEL_78;
	}
	if (!argv[7])
	{
		if (!argv[8])
			goto LABEL_78;
		goto LABEL_72;
	}
	if (argv[7] != 0xFF)
	{
	LABEL_38:
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		return 2;
	}
	Delay_802EF34(0x22);
	ComSendByte_sub_802F1E0((unsigned __int8)~keyWord[1]);
	if (argv[8])
	{
	LABEL_72:
		*ans = 0;
		ans[1] = argv[8];
		ansPostion = 2;
		v18 = 9;
		for (k = 0; k < argv[8]; ++k)
		{
			if (!argv[v18])
				goto LABEL_38;
			ans[ansPostion++] = argv[v18];
			for (rcvbyte = 0; rcvbyte < (unsigned int)argv[v18]; ++rcvbyte)
			{
				v20 = ComByte_sub_802F6CC(&ans[ansPostion++], 0x3E8);
				if (!v20)
					goto LABEL_78;
			}
			++v18;
		}
		return ansPostion;
	}
	if (ComByte_sub_802F6CC(&rcvbyte, 0x1388))
		PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
	else
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
	return 2;
}




int ID601B_SetBenzHMFLinkKeep_1_sub_804CF70(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v5; // r7

	set_time0Stop_sub_802BB48();
	Keep_Link_200046C0.field_46 = 0;
	Keep_Link_200046C0.linkState = 0;
	v5 = *argv;
	if (*argv)
	{
		Keep_Link_200046C0.idleSendLen = *argv;
		Copysub_802FB50(Keep_Link_200046C0.dataBuf, argv + 1, v5);
		Keep_Link_200046C0.IdleTime = 10 * argv[(unsigned __int8)(v5 + 2)];
		TimerConfig_sub_802EDAE(0, SC_TagKWP2000_20004974.m_MsTime);
		Keep_Link_200046C0.rightState = 5;
		TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_setlinkkeep_sub_802C444);
		timer_open_flag_2000C6B7 = 2;
		TIM_sub_802EEEC(0);
	}
	else
	{
		timer_open_flag_2000C6B7 = 0;
		Keep_Link_200046C0.idleSendLen = 0;
		Keep_Link_200046C0.IdleTime = 0;
	}
	PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
	return 2;
}



// // Funtion: 地址码触发函数，用于发送地址码，通过55H计算波特率，接收KW1,KW2,
// //          发送KW2取反。常用于地址码ISO协议、地址码KWP协议、地址码单字节协议
// // Input  : argc - 参数长度
// //          argv - 参数
// //          argv[0]:地址码发送模式。值为1表示模式1，值为2表示模式2，值为3表示模式3
// //          argv[1]:地址码值
// //          argv[2]:控制L线是否禁能
// //     模式1  发送5波特率地址码
// //          argv[3]:判断是否自动计算波特率。为0表示不自动计算，为0xFF表示自动计算波特率
// //          argv[4]:无意义
// //          argv[5]:KW2到KW2取反之间的时间延迟
// //          argv[6]:判断是否将KW2取反发回到ECU。为0表示不取反发回，为0xff表示取反发回
// //          argv[7]:如argv[6]非0，argv[7]为0表示必须要收到ECU发来的地址码取反字节，如argv[6]为0，argv[7]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[7]非0，则argv[7]表示要从ECU接受的数据的帧数
// //          argv[8]~arg[8+argv[7]-1]:如argv[7]为0，这些字节无意义,如argv[7]非0，这些字节分别表示接收的每一帧数据的长度
// //--------------------------------------------------
// //     模式2 发送设定的地址码或200bps地址码
// //          argv[3]:最高位为1表示需要计算地址码的波特率，并作为计算波特率的一个参数，否则表示地址码波特率为200.
// //          argv[4]:argv[3]最高位为1时，argv[4]为波特率计算参数，否则无意义
// //          argv[5]:无意义
// //          argv[6]:KW2到KW2取反之间的时间延迟
// //          argv[7]:判断是否将KW2取反发回到ECU。为0表示不取反发回，为0xff表示取反发回
// //          argv[8]:如argv[7]非0，argv[8]为0表示必须要收到ECU发来的地址码取反字节，如argv[7]为0，argv[8]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[7]非0，则argv[8]表示要从ECU接受的数据的帧数
// //          argv[9]~arg[9+argv[8]-1]:如argv[8]为0，这些字节无意义,如argv[8]非0，这些字节分别表示接收的每一帧数据的长度
// //--------------------------------------------------
// // Output : ans - 回复到上位机的数据:
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、如在ECU发完KW1,KW2后，还有帧数据接收，则，ans的内容为：接收总帧数 第一帧数据长度 第一帧数据
// //                   第二帧数据长度 第二帧数据......第n帧数据长度，第n帧数据(总帧数用两个字节表示)
// //                   如ans[] = {0x00,0x02,0x05,0x81,0x10,0xf1,0x81,0x03,0x06，0x82,0x10,0xf1,0x04,0x05,0x08c}
// //                4、如在ECU发完KW1,KW2后，无帧数据接收，则返回FF 00
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 601c
int ID601C_AddressCodeWayAdjustTime_benz_1_sub_802371C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int argvpos; // r11 MAPDST
	char addr_code; // r8
	int Argv0Val; // r0
	unsigned int v9; // r10
	int ArgvPosVal; // r0
	int v16; // r7
	int rcvlen; // r0 MAPDST
	unsigned __int8 AnsPos; // r9
	int rcvframenum; // r0 MAPDST
	unsigned __int8 rcvbyte; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 obdfid; // [sp+1h] [bp-2Fh]

	rcvbyte = 0;
	addr_code = argv[1];
	obdfid = argv[2];
	Argv0Val = *argv;
	if (Argv0Val == 1)
	{
		if (argv[3])
		{
			if (argv[3] != 0xFF)
			{
			LABEL_6:
				PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
				return 2;
			}

			IOCTRLSelect_sub_8030606(1u, 1u);
			IOCTRLSet_sub_8030658(1, 0x1F4);
			sendAddressToEcu_sub_802CF50(argv[1], 5u);
			if ((obdfid & 0x80) != 0)
				EnableLLine_1_sub_802C560();
			else
				IOCTRLInit_sub_802C570();
			IOCTRLSelect_sub_8030606(0, 3u);
			SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
			if (!SC_com_portMode_20004964.BaudRate)
			{
				Delay_802EF34(0xFA0);
				IOCTRLSelect_sub_8030606(1u, 1u);
				sendAddressToEcu_sub_802CF50(argv[1], 5u);
				IOCTRLSelect_sub_8030606(0, 3u);
				SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
				if (!SC_com_portMode_20004964.BaudRate)
				{
					ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					return 2;
				}
			}
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			argvpos = 4;
		}
		else
		{
			Delay_802EF34(0x1F4);

			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CC82(addr_code);
			if ((obdfid & 0x80) != 0)
				EnableLLine_1_sub_802C560();
			else
				IOCTRLInit_sub_802C570();
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
			{
				Delay_802EF34(0xFA0);
				IOCTRLSelect_sub_8030606(1u, 1u);
				IOCTRLSet_sub_8030658(1, 0x1F4);
				sendAddressToEcu_sub_802CC82(addr_code);
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
					goto LABEL_57;
			}
		}
	}
	else
	{
		if (Argv0Val != 2)
			goto LABEL_6;
		Delay_802EF34(0x1F4);
		if ((argv[3] & 0x80) != 0)
		{
			v9 = 0x8CA00u / (0x10000 - (argv[4] + (argv[3] << 8)));

			IOCTRLSelect_sub_8030606(1u, 1u);
			IOCTRLSet_sub_8030658(1, 0x1F4);
			sendAddressToEcu_sub_802CF50(addr_code, v9);
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
			{
				Delay_802EF34(0xFA0);
		
				IOCTRLSelect_sub_8030606(1u, 1u);
				sendAddressToEcu_sub_802CF50(addr_code, v9);
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
					goto LABEL_57;
			}
		}
		else
		{

			IOCTRLSelect_sub_8030606(1u, 1u);
			sendAddressToEcu_sub_802CF50(addr_code, 0xC8u);
			if ((obdfid & 0x80) != 0)
				EnableLLine_1_sub_802C560();
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(&rcvbyte, 2550) || rcvbyte != 0x55)
			{
				
				IOCTRLSelect_sub_8030606(1u, 1u);
				Delay_802EF34(0xFA0);
				IOCTRLSet_sub_8030658(1, 0x1F4);
				sendAddressToEcu_sub_802CF50(addr_code, 0xC8u);
				if ((obdfid & 0x80) != 0)
					EnableLLine_1_sub_802C560();
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(&rcvbyte, 0x9F6) || rcvbyte != 0x55)
					goto LABEL_57;
			}
		}
		argvpos = 5;
	}
	++argvpos;
	if (!ComByte_sub_802F6CC(&rcvbyte, 0x3E8) || !ComByte_sub_802F6CC(&rcvbyte, 0x7D0))
	{
	LABEL_57:
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		return 2;
	}
	Delay_802EF34(argv[argvpos++]);
	argvpos += 2;
	ArgvPosVal = argv[argvpos];
	if (!ArgvPosVal)
	{
		rcvlen = argv[argvpos++];
		v16 = rcvlen;
		if (!(_BYTE)rcvlen)
		{
			PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
			return 2;
		}
		goto LABEL_53;
	}
	if (ArgvPosVal != 0xFF)
		goto LABEL_44;
	ComSendByte_sub_802F1E0((unsigned __int8)~rcvbyte);
	rcvlen = argv[argvpos++];
	v16 = rcvlen;
	if ((_BYTE)rcvlen)
	{
	LABEL_53:
		*ans = 0;
		ans[1] = v16;
		AnsPos = 2;
	LABEL_54:
		rcvframenum = argv[argvpos++];
		if ((_BYTE)rcvframenum)
		{
			ans[AnsPos++] = rcvframenum;
			while (ComByte_sub_802F6CC(&rcvbyte, 0x12C))
			{
				ans[AnsPos++] = rcvbyte;
				if (!(_BYTE)--rcvframenum)
				{
					if ((_BYTE)--v16)
						goto LABEL_54;
					return AnsPos;
				}
			}
			goto LABEL_57;
		}
	LABEL_44:
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		return 2;
	}
	if (ComByte_sub_802F6CC(&rcvbyte, 0x12C))
		PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
	else
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
	return 2;
}





// // Funtion: 地址码触发函数，用于发送地址码，通过55H计算波特率，接收KW1,KW2,
// //          发送KW2取反。常用于地址码ISO协议、地址码KWP协议、地址码单字节协议
// // Input  : argc - 参数长度
// //          argv - 参数
// //          argv[0]:地址码发送模式。值为1表示模式1，值为2表示模式2，值为3表示模式3
// //          argv[1]:地址码值
// //     模式1  发送5波特率地址码
// //          argv[2]:判断是否自动计算波特率。为0表示不自动计算，为0xFF表示自动计算波特率
// //          argv[3]:判断是否将KW2取反发回到ECU。为0表示不取反发回，为0xff表示取反发回
// //          argv[4]:如argv[3]非0，argv[4]为0表示必须要收到ECU发来的地址码取反字节，如argv[3]为0，argv[4]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[3]非0，argv[4]非0，则argv[4]表示要从ECU接受的数据的帧数
// //          argv[5]~arg[5+argv[4]-1]:如argv[4]为0，这些字节无意义,如argv[4]非0，这些字节分别表示接收的每一帧数据的长度
// //--------------------------------------------------
// //     模式2 发送设定的地址码或200bps地址码
// //          argv[2]:最高位为1表示需要计算地址码的波特率，并作为计算波特率的一个参数，否则表示地址码波特率为200.
// //          argv[3]:argv[2]最高位为1时，argv[3]为波特率计算参数，否则无意义
// //          argv[4]:判断是否将KW2取反发回到ECU。为0表示不取反发回，为0xff表示取反发回
// //          argv[5]:如argv[4]非0，argv[5]为0表示必须要收到ECU发来的地址码取反字节，如argv[4]为0，argv[5]为0表示
// //                  发完地址码后不再进行任何收发动作，如argv[4]非0，则argv[5]表示要从ECU接受的数据的帧数
// //          argv[6]~arg[6+argv[5]-1]:如argv[5]为0，这些字节无意义,如argv[5]非0，这些字节分别表示接收的每一帧数据的长度
// //--------------------------------------------------
// // Output : ans - 回复到上位机的数据:
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、如在ECU发完KW1,KW2后，还有帧数据接收，则，ans的内容为：接收总帧数 第一帧数据长度 第一帧数据
// //                   第二帧数据长度 第二帧数据......第n帧数据长度，第n帧数据(总帧数用两个字节表示)
// //                   如ans[] = {0x00,0x02,0x05,0x81,0x10,0xf1,0x81,0x03,0x06，0x82,0x10,0xf1,0x04,0x05,0x08c}
// //                4、如在ECU发完KW1,KW2后，无帧数据接收，则返回FF 00
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 601d
int ID601D_AddressCodeCommunicationWay_Lline_1_sub_8023CF4(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r0
	int rcvframenum; // r7
	int argvLen; // r8
	int ansposition; // r10
	int rcvlen; // r0 MAPDST
	unsigned __int8 rcvbyte[40]; // [sp+0h] [bp-28h] BYREF

	v5 = *argv;
	if (v5 == 1)
	{

		IOCTRLSelect_sub_8030606(1u, 1u);
		Delay_802EF34(0x1F4);
		if (argv[2])
		{
			if (argv[2] != 0xFF)
			{
			LABEL_6:
				PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
				return 2;
			}
			sendAddressToEcu_sub_802CC82(argv[1]);

			IOCTRLSelect_sub_8030606(0, 3u);
			SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
		}
		else
		{
			sendAddressToEcu_sub_802CC82(argv[1]);
			ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
			if (!ComByte_sub_802F6CC(rcvbyte, 0x3E8))
				goto LABEL_36;
			if (rcvbyte[0] != 0x55)
			{
				Delay_802EF34(0xFA0);

				IOCTRLSelect_sub_8030606(1u, 1u);
				sendAddressToEcu_sub_802CC82(argv[1]);
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(rcvbyte, 0x3E8) || rcvbyte[0] != 0x55)
					goto LABEL_36;
			}
		}
	}
	else
	{
		if (v5 != 2)
			goto LABEL_6;

		IOCTRLSelect_sub_8030606(1u, 1u);
		Delay_802EF34(0x1F4);
		if ((argv[2] & 0x80) != 0)
			sendAddressToEcu_sub_802CF50(argv[1], 0x8CA00u / (0x10000 - (argv[3] + (argv[2] << 8))));
		else
			sendAddressToEcu_sub_802CF50(argv[1], 0xC8u);
		SC_com_portMode_20004964.BaudRate = autoCheckBaudRate_sub_802CE7E(0x28);
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	}
	if (!ComByte_sub_802F6CC(rcvbyte, 0x3E8) || !ComByte_sub_802F6CC(rcvbyte, 0x7D0))
	{
	LABEL_36:
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		return 2;
	}
	Delay_802EF34(0x23);
	if (!argv[3])
	{
		rcvframenum = argv[4];
		if (!argv[4])
		{
			PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
			IOCTRLInit_sub_802C570();
			return 2;
		}
		goto LABEL_32;
	}
	if (argv[3] != 0xFF)
	{
	LABEL_23:
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		return 2;
	}
	rcvbyte[0] = 0xFF - rcvbyte[0];
	ComSendByte_sub_802F1E0(rcvbyte[0]);
	rcvframenum = argv[4];
	if (argv[4])
	{
	LABEL_32:
		IOCTRLInit_sub_802C570();
		*ans = rcvframenum;
		argvLen = 5;
		ansposition = 2;
		ans[1] = rcvframenum;
	LABEL_33:
		rcvlen = argv[argvLen++];
		if (!rcvlen)
			goto LABEL_23;
		ans[ansposition++] = rcvlen;
		while (ComByte_sub_802F6CC(rcvbyte, 0x3E8))
		{
			ans[ansposition++] = rcvbyte[0];
			if (!--rcvlen)
			{
				if (--rcvframenum)
					goto LABEL_33;
				*ans = 0;
				return ansposition;
			}
		}
		goto LABEL_36;
	}
	if (ComByte_sub_802F6CC(rcvbyte, 0x12C))
	{
		PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
		IOCTRLInit_sub_802C570();
	}
	else
	{
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
	}
	return 2;
}



//直接返回 没有设置硬件这些信息
int ID601EFun_SelectMultiIoLine_sub_804D040(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	*ans = 0;
	ans[1] = 2;
	return 2;
}



// 设置流控制帧之类的函数 与982不一样 功能也不太明白
int ID601F_SetEnterFrameDataExt_1_sub_80370D6(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	ucCan30ConfigMode_2000C6BD = *argv;
	CanEnterFrame_2000C47C.dataLenth = argv[1];
	if ((argv[7] & 0x80) != 0)
	{
		CanEnterFrame_2000C47C.data[30] = argv[13];
	}
	else if (argv[10] != 0x30 || argv[11] == 0x30)
	{
		CanEnterFrame_2000C47C.data[30] = argv[12];
	}
	else
	{
		CanEnterFrame_2000C47C.data[30] = argv[11];
	}
	if (CanEnterFrame_2000C47C.dataLenth)
	{
		memmove(CanEnterFrame_2000C47C.data, argv + 7, argv[4]);
		memmove(ans, szFOK_20004A04, 4u);
	}
	else
	{
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
	}
	return 2;
}



// 处理获取的版本号 日期等信息
// Argv:6F
int ID6020Fun_GetBoxInfo_sub_804D04E(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 SeriesBuf[8]; // [sp+0h] [bp-40h] BYREF
	unsigned __int8 v6[24]; // [sp+8h] [bp-38h] BYREF
	unsigned __int8 v7[4]; // [sp+20h] [bp-20h] BYREF
	unsigned __int8 v8[4]; // [sp+24h] [bp-1Ch]
	int v9; // [sp+28h] [bp-18h]

	*(_DWORD *)v7 = 0;
	*(_DWORD *)v8 = 0;
	v9 = 0;
	memset(v6,0, 24u);
	GetSeries_Ver_sub_8040000(1, SeriesBuf, 8u);  // 获取V1.00.00字符串
	if (SeriesBuf[2] == 46)
	{
		v6[1] = SeriesBuf[1] - 48;
		v6[2] = SeriesBuf[4] + 10 * SeriesBuf[3] - 16;
	}
	else if (SeriesBuf[3] == 46)
	{
		v6[1] = SeriesBuf[2] + 10 * SeriesBuf[1] - 16;
		v6[2] = SeriesBuf[5] + 10 * SeriesBuf[4] - 16;
	}
	if (aV1168[2] == 46)
	{
		v6[3] = aV1168[1] - 48;
		v6[4] = aV1168[4] + 10 * aV1168[3] - 16;
	}
	else if (aV1168[3] == 46)
	{
		v6[3] = aV1168[2] + 10 * aV1168[1] - 16;
		v6[4] = aV1168[5] + 10 * aV1168[4] - 16;
	}
	GetSeries_Ver_sub_8040000(0, &v6[5], 0xCu);   // 得到 987591721700
	GetSeries_Ver_sub_8040000(2, v7, 8u);         // 得到20181024
	v6[17] = v7[2] - 48;
	v6[18] = v7[3] - 48;
	v6[19] = v8[0] - 48;
	v6[20] = v8[1] - 48;
	v6[21] = v8[2] - 48;
	v6[22] = v8[3] - 48;
	memmove(ans, v6, 0x17u);                      // ans得到00 01 00 0B 44 39 38 37 35 39 31 37 32 31 37 30 30 01 08 01 00 02 04
	return 23;                                    // 返回0x17
}


//直接返回数据
int ID6021_GetDownloadType_sub_804D1C0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	*ans = 0;
	ans[1] = 7;
	return 2;
}


//一些延时时间 的赋值
int ID6022_sub_804D1DC(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int v3; // r4
	unsigned int v4; // r5
	unsigned int v5; // r0

	v3 = *argv;
	if (v3 == 1)
	{
		TimeOut_2000C530 = argv[2] + (argv[1] << 8);
		FrameTime_2000C534 = argv[4] + (argv[3] << 8);
		dword_2000C538 = argv[6] + (argv[5] << 8);
		DelayTime_2000C53C = argv[8] + (argv[7] << 8);
		if (!TimeOut_2000C530 && !FrameTime_2000C534 && !dword_2000C538 && !DelayTime_2000C53C)
		{
			kwp2000m_nBtyetime_2000C540 = SC_TagKWP2000_20004974.m_nBtyetime;
			TimeOut_2000C530 = SC_TagKWP2000_20004974.m_Maxwaittime;
		}
		if (!TimeOut_2000C530)
		{
			if (SC_TagKWP2000_20004974.m_Maxwaittime >= 0x1F4)
				TimeOut_2000C530 = SC_TagKWP2000_20004974.m_Maxwaittime;
			else
				TimeOut_2000C530 = 0xBB8;
		}
	}
	else if (*argv && v3 != 3)
	{
		if (v3 < 3)
		{
			kwp2000m_nBtyetime_2000C540 = argv[2] + (argv[1] << 8);
			if (!kwp2000m_nBtyetime_2000C540)
			{
				kwp2000m_nBtyetime_2000C540 = SC_TagKWP2000_20004974.m_nBtyetime;
				TimeOut_2000C530 = SC_TagKWP2000_20004974.m_Maxwaittime;
			}
		}
		else if (v3 == 4)
		{
			v4 = argv[5] + (argv[3] << 0x10) + (argv[2] << 0x18) + (argv[4] << 8);
			unk_2000C6B9 = 1;
			*ans = 0xFF;
			ans[1] = 0;
			v5 = argv[1];
			if (argv[1])
			{
				if (v5 == 2)
				{
					SC_TagKWP2000_20004974.m_nFrameTime = v4 / 0xA;
				}
				else if (v5 >= 2)
				{
					if (v5 == 4)
					{
						SC_TagKWP2000_20004974.m_nFrameTime = v4 / 0xA;
					}
					else if (v5 >= 4)
					{
						if (v5 == 6)
						{
							dword_2000C668 = v4 / 0xA;
						}
						else if (v5 >= 6)
						{
							*ans = 0xFF;
							ans[1] = 2;
						}
						else
						{
							SC_TagKWP2000_20004974.m_nBtyetime = 0x64 * v4;
						}
					}
				}
				else
				{
					SC_TagKWP2000_20004974.m_Maxwaittime = v4 / 0xA;
				}
			}
			else
			{
				SC_TagKWP2000_20004974.m_nFrameTime = 10;
				SC_TagKWP2000_20004974.m_nBtyetime = 5000;
				SC_TagKWP2000_20004974.m_Maxwaittime = 500;
				SC_TagKWP2000_20004974.m_MsTime = 5;
				unk_2000C6B9 = 0;
				dword_2000C668 = 0;
			}
		}
	}
	*ans = 0xFF;
	ans[1] = 0;
	return 2;
}



// 982没找到对应的函数 
int ID6023_sub_802AB34(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	char v5; // r10
	char v6; // r9
	int result; // r0
	int v9; // r8
	unsigned int i; // r7
	SC_PAKRECV PakRecv; // [sp+0h] [bp-38h] BYREF
	SC_PAKSEND PakSend; // [sp+8h] [bp-30h] BYREF
	unsigned __int8 RcvByte; // [sp+10h] [bp-28h] BYREF

	v5 = 5;
	Delay_802EF34(0x32);
	PakSend.PakdataAddr = SendPakdataPackData_2000BDF4;
	PakSend.PakLenth = 4;
	SendPakdataPackData_2000BDF4[0] = 3;
	SendPakdataPackData_2000BDF4[1] = 0;
	SendPakdataPackData_2000BDF4[2] = 9;
	SendPakdataPackData_2000BDF4[3] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	SC_TagKWP1281_200043E4.m_chHoldDig[0] = 3;
	SC_TagKWP1281_200043E4.m_chHoldDig[1] = 0;
	SC_TagKWP1281_200043E4.m_chHoldDig[2] = 9;
	SC_TagKWP1281_200043E4.m_chHoldDig[3] = 3;
	PakRecv.PakdataAddr = receive_buff_2000BF20;
	TimerRelease_sub_802EF76(0);
	v6 = CheckLLine_sub_802C580();
	SC_TagKWP1281_200043E4.m_Idletime = 0x258;
	SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	SC_TagKWP1281_200043E4.m_SendFinishFlag = 1;
	EnableLLine_1_sub_802C560();

	IOCTRLSelect_sub_8030606(1u, 1u);
	sendAddressToEcu_sub_802CC82(*argv);
	ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	do
	{
		if (!v5--)
			break;
		if (!ComByte_sub_802F6CC(&RcvByte, 0x7D0))
			return 2;
	} while (RcvByte != 0x8A);
	if (!v5)
		return 2;
	if (v6 == 1)
		EnableLLine_1_sub_802C560();
	else
		IOCTRLInit_sub_802C570();
	Delay_802EF34(0x14);
	ComSendByte_sub_802F1E0((unsigned __int8)~RcvByte);
	*ans = 0;
	ans[1] = 0;
	v9 = 2;
	SetTIMCLOCK_RCC_APB1PeriphClockCmd_sub_802ED88(2);
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	SC_TagKWP1281_200043E4.m_chCount = 0;
	Keep_Link_200046C0.rightState = 2;
	if (SC_com_portMode_20004964.BaudRate >= 0x1388u)
	{
		TimerConfig_sub_802EDAE(0, 1u);
		SC_TagKWP1281_200043E4.m_nBtyetime = 2;
		SC_TagKWP1281_200043E4.m_nFrameTime = 0x16;
		SC_TagKWP1281_200043E4.m_ReserveTime = 2;
	}
	else
	{
		TimerConfig_sub_802EDAE(0, 1u);
		SC_TagKWP1281_200043E4.m_nBtyetime = 6;
		SC_TagKWP1281_200043E4.m_nFrameTime = 0x1E;
		SC_TagKWP1281_200043E4.m_ReserveTime = 3;
	}
	SC_TagKWP1281_200043E4.m_LinkFG = 1;
	timer_open_flag_2000C6B7 = 1;
	TimerInterruptFuntionLoad_sub_802EF66(0, (int)SC_CML_KWP1281_Time_sub_802C5B0);
	ComInterruptFuntionLoad_sub_802F8A0((int)SC_CML_KWP1281_Comread_sub_802C860, 1u);
	ComInterruptFuntionLoad_sub_802F8A0((int)SC_CML_KWP1281_Comsend_sub_802C7DC, 0);
	TIM_sub_802EEEC(0);
	ComReadSign_sub_802F614(1);
	if (SC_CML_KWP1281_Recv_sub_802CBCC(&PakRecv))
	{
		while (PakRecv.PakdataAddr[2] != 9 && PakRecv.PakdataAddr[2] != 0xF7 && PakRecv.PakLenth >= 3)
		{
			++ans[1];
			for (i = 0; i < PakRecv.PakLenth; ++i)
				ans[v9++] = PakRecv.PakdataAddr[i];
			if (!SC_CML_KWP1281_Sendsub_802CB36(&PakSend) || !SC_CML_KWP1281_Recv_sub_802CBCC(&PakRecv))
				goto LABEL_25;
		}
		result = v9;
	}
	else
	{
	LABEL_25:
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		result = 2;
	}
	return result;
}




// 这函数没看懂
int ID6024Fun_sub_802AD94(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int v4; // r7
	unsigned int v5; // r8
	uint32_t v6; // r9

	v4 = 0;
	v5 = 0;
	if (*argv)
	{
		if (*argv == 1)
		{
			IOCTRLSelect_sub_8030606(1u, 1u);
			IOCTRLSet_sub_8030658(0, 0x186A0);
			do
			{
				IOCTRLSet_sub_8030658(1, 0x7D0);
				IOCTRLSet_sub_8030658(0, 0x7D0);
				++v4;
			} while (v4 < 5);
			do
			{
				IOCTRLSet_sub_8030658(1, 0x514);
				IOCTRLSet_sub_8030658(0, 0x1F4);
				IOCTRLSet_sub_8030658(1, 0x1F4);
				IOCTRLSet_sub_8030658(0, 0x514);
				++v5;
			} while (v5 < 0x10);
			IOCTRLSet_sub_8030658(1, 0x1F4);
			IOCTRLSet_sub_8030658(0, 0x514);
			GPIO_WriteBit_80312F6(&GPIOB_BASE_40020400, 0x400, 1);
			IOCTRLSelect_sub_8030606(0, 3u);
			SetSysTickLOAD_sub_8031144(1200000u);
			while (SysTick_Config_sub_80311BE())
			{
				if (!IOCTRLGet_sub_80306E2())
				{
					v6 = GetDelayTim_sub_803112E();
					while (v6 - GetDelayTim_sub_803112E() <= 0x3E8)
						;
					if (!IOCTRLGet_sub_80306E2())
					{
						while (!IOCTRLGet_sub_80306E2())
							Delay_sub_802EF46(0x64u);
						PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
						return 2;
					}
				}
			}
		}
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
	}
	else
	{

		IOCTRLSelect_sub_8030606(1u, 1u);
		IOCTRLSet_sub_8030658(0, 0x186A0);
		do
		{
			IOCTRLSet_sub_8030658(1, 0x7D0);
			IOCTRLSet_sub_8030658(0, 0x7D0);
			++v4;
		} while (v4 < 5);
		do
		{
			IOCTRLSet_sub_8030658(1, 0x4B0);
			IOCTRLSet_sub_8030658(0, 0x258);
			IOCTRLSet_sub_8030658(1, 0x258);
			IOCTRLSet_sub_8030658(0, 0x4B0);
			++v5;
		} while (v5 < 0x10);
		GPIO_WriteBit_80312F6(&GPIOB_BASE_40020400, 0x400, 1);
		PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
	}
	return 2;
}


//设置寄存器 和IO引脚
int ID6025Fun_sub_804D64E(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	IOCTRLSelect_sub_8030606(0x16u, 0);
	if (*argv)
	{
		if (*argv != 255)
		{
			*ans = -1;
			ans[1] = 2;
			return 2;
		}
		IOCTRLSet_sub_8030658(0, 0);
	}
	else
	{
		CMPHY_Relay_Reset_sub_8030B88();
		IOCTRLSet_sub_8030658(1, 20);
	}
	*ans = -1;
	ans[1] = 0;
	return 2;
}

//设置寄存器 和IO引脚
int ID6026Fun_sub_804D69E(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v4; // r7

	v4 = *argv;
	if (v4 == 255)
	{
		IOCTRLSelect_sub_8030606(0x13u, 1u);
		IOCTRLSet_sub_8030658(1, 0);
	}
	else
	{
		if ((_BYTE)v4)
		{
			*ans = -1;
			ans[1] = 2;
			return 2;
		}
		IOCTRLSelect_sub_8030606(0x13u, 1u);
		IOCTRLSet_sub_8030658(0, 0);
	}
	*ans = -1;
	ans[1] = 0;
	return 2;
}

//直接返回 
int ID6027Fun_sub_804D1CE(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	*ans = 0;
	ans[1] = 2;
	return 2;
}

//用于校验版本的 蓝牙之间配对的 暂时估计不需要
int ID6028Fun_sub_804D78C(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	return 1;
}



//设置一些通讯时用到的值 
int ID602D_Fun_sub_804D6F2(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned __int8 v4; // r7

	v4 = *Argv;
	if (*Argv)
	{
		if (v4 == 1)
		{
			Set2000C6BF_is_1_sub_8030D78();
		}
		else if (v4 != 2)
		{
			if (v4 != 3)
			{
				*Ans = 0xFF;
				Ans[1] = 1;
				return 2;
			}
			CMPHY_Relay_Reset_sub_8030B88();
		}
	}
	else
	{
		Set2000C6BF_is_1_sub_8030D70();
	}
	*Ans = 0xFF;
	Ans[1] = 0;
	return 2;
}


//设置通讯的波特率 以及继电器 通讯类型
int ID602E_sub_804D3E0(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned __int8 v5; // r10
	unsigned __int8 v6; // r8
	unsigned __int8 v7; // r9
	unsigned __int8 v8; // r11
	int result; // r0
	unsigned __int8 v10; // r7
	unsigned __int8 v11[4]; // [sp+0h] [bp-38h] BYREF
	COM_PORTMODE SC_com_portMode; // [sp+4h] [bp-34h] BYREF

	v11[0] = 0;
	v5 = 0;
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	v6 = *Argv;
	SC_RelayState_200049DC.CommType = 0;
	v7 = Argv[1];
	SC_RelayState_200049DC.OutputChannel = v7;
	v8 = Argv[2];
	if (v8)
	{
		GPIO_PINAFConfig_RCCSet_sub_802EFE0();
		*(_QWORD *)&SC_com_portMode.BaudRate = 10400i64;
		*(_QWORD *)&SC_com_portMode.StopBits = 0i64;
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode);
		v10 = 3;
		while (v8)
		{
			v5 = Argv[v10++];
			SC_RelayState_200049DC.InputChannel = v5;
			SC_RelayState_200049DC.LevelType = 0xC;
			SC_RelayState_200049DC.LogicType = 1;
			CMPHY_Relay_Reset_sub_8030B88();
			CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
			ComSendByteInIsr_sub_802F4BA(0x55u);
			if (ComByte_sub_802F6CC(v11, 0xA))
			{
				if (v11[0] == 0x55)
				{
					*Ans = 0;
					Ans[1] = 1;
				}
				else
				{
					*Ans = 0;
					Ans[1] = 2;
				}
				break;
			}
			*Ans = 0;
			Ans[1] = 0;
			--v8;
		}
		Ans[2] = v6;
		Ans[3] = v5;
		Ans[4] = v7;
		Ans[5] = 0;
		Ans[6] = 0;
		result = 7;
	}
	else
	{
		*Ans = 0xFF;
		Ans[1] = 2;
		result = 2;
	}
	return result;
}




int ID602F_sub_804D4F8(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned __int8 v4; // r7
	int result; // r0

	v4 = *Argv;
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	CMPHY_Relay_Reset_sub_8030B88();
	switch (v4)
	{
	case 1u:
		SC_RelayState_200049DC.OutputChannel = 4;
		SC_RelayState_200049DC.InputChannel = 4;
		SC_RelayState_200049DC.Dts = 1;
		break;
	case 2u:
		SC_RelayState_200049DC.OutputChannel = 11;
		SC_RelayState_200049DC.InputChannel = 11;
		SC_RelayState_200049DC.Dts = 3;
		break;
	case 0xCu:
		SC_RelayState_200049DC.OutputChannel = 8;
		SC_RelayState_200049DC.InputChannel = 8;
		SC_RelayState_200049DC.Dts = 2;
		break;
	default:
		*Ans = -1;
		Ans[1] = 2;
		return 2;
	}
	SC_RelayState_200049DC.CommType = 0;
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	IOCTRLSelect_sub_8030606(0x13u, 0);
	IOCTRLSet_sub_8030658(1, 10);
	IOCTRLSet_sub_8030658(0, 10);
	IOCTRLSelect_sub_8030606(0, 3u);
	if (AboutSysTicksub_8030788(0, 1000000u))
	{
		IOCTRLSelect_sub_8030606(0x13u, 0);
		IOCTRLSet_sub_8030658(1, 10);
		IOCTRLSelect_sub_8030606(0, 3u);
		if (AboutSysTicksub_8030788(1, 1000000u))
		{
			IOCTRLSelect_sub_8030606(0x13u, 0);
			IOCTRLSet_sub_8030658(0, 10);
			IOCTRLSet_sub_8030658(1, 10);
			IOCTRLSet_sub_8030658(0, 10);
			IOCTRLSet_sub_8030658(1, 10);
			IOCTRLSet_sub_8030658(0, 10);
			IOCTRLSet_sub_8030658(1, 10);
			IOCTRLSet_sub_8030658(0, 10);
			IOCTRLSet_sub_8030658(1, 10);
			*Ans = 0;
			Ans[1] = 2;
		}
		else
		{
			*Ans = 0;
			Ans[1] = 0;
		}
		result = 2;
	}
	else
	{
		*Ans = 0;
		Ans[1] = 0;
		result = 2;
	}
	return result;
}


// IO设置
int ID6101_sub_80292C4(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned __int8 v3; // r5
	unsigned int v5; // r0
	char v6; // r8
	int v7; // r6
	char v8; // r10
	char v9; // r9
	unsigned __int8 v10; // r7
	int v11; // r7
	int v13; // r8
	int result; // r0
	int v16; // r7
	int v18; // r8
	char v20; // r11
	char v21; // r10
	char v22; // r9
	char v23; // r8
	int v24; // r6
	char v25; // r10
	char v26; // r9
	unsigned __int8 v27; // r7
	int v28; // r7
	int v30; // r8
	unsigned __int8 v32; // r10
	unsigned __int8 v33; // r0
	int v34; // r11
	int v36; // r10
	int v37; // r5
	unsigned __int8 v38; // r10
	char v39; // r8
	int v40; // r6
	char v41; // r10
	char v42; // r9
	unsigned __int8 v43; // r7
	int v44; // r8
	int v45; // r5
	unsigned __int8 v46; // r7
	char v47; // r8
	int v48; // r6
	char v49; // r10
	char v50; // r9
	unsigned __int8 v51; // r7
	int v52; // r7
	int v54; // r8
	int v56; // r7
	int v58; // r8
	unsigned int DelayTime; // [sp+0h] [bp-C0h] BYREF
	unsigned __int8 v61[4]; // [sp+4h] [bp-BCh] BYREF
	unsigned int v62; // [sp+8h] [bp-B8h]
	unsigned __int8 v63; // [sp+Ch] [bp-B4h]
	unsigned __int8 v64[132]; // [sp+10h] [bp-B0h] BYREF
	int v65; // [sp+94h] [bp-2Ch]
	unsigned __int8 *v66; // [sp+98h] [bp-28h]

	v65 = Argc;
	v66 = Argv;
	v5 = *Argv;
	if (!*Argv)
		goto LABEL_310;
	if (v5 == 2)
	{
		IOCTRLSelect_sub_8030606(0, 2u);
		IOCTRLSelect_sub_8030606(1u, 0);
		IOCTRLSet_sub_8030658(0, 0);
		Delay_802EF34(0x7D0);
		v11 = 0x64;
	LABEL_63:
		if (!(_BYTE)v11--)
		{
			*Ans = 0xFF;
			Ans[1] = 2;
			return 2;
		}
		v13 = 0x64;
		do
		{
			if (!(_BYTE)v13--)
				goto LABEL_63;
		} while (!Delay_WaitIoSetLow_sub_802E440(&DelayTime, 400u));// 返回1是低电平 0 是高电平 返回1低电平 直接退出while
		while (LowHighSet_sub_802E4E0(&DelayTime) == 1)
		{
			*Ans = 0;
			Ans[1] = BYTE1(DelayTime);
			Ans[2] = DelayTime;
			GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
		}
		*Ans = 0xFF;
		Ans[1] = 2;
		result = 2;
	}
	else
	{
		if (v5 < 2)
		{
			v6 = 0;
			if (Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
			{
				v7 = 0x14;
				do
				{
					if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
					if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
					if (DelayTime >= 0x7D0)
					{
						while (1)
						{
							while (1)
							{
								v8 = 0;
								v9 = 0;
								do
								{
									if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
									{
										*Ans = 0xFF;
										Ans[1] = 2;
										return 2;
									}
									if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
									{
										*Ans = 0xFF;
										Ans[1] = 2;
										return 2;
									}
									++v8;
								} while (DelayTime < 0x3E8);
								do
								{
									if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
									{
										*Ans = 0xFF;
										Ans[1] = 2;
										return 2;
									}
									if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
									{
										*Ans = 0xFF;
										Ans[1] = 2;
										return 2;
									}
									++v9;
								} while (DelayTime < 0x7D0);
								v10 = v9 + 0xA * v8;
								if (v6)
									break;
								v6 = 1;
								*Ans = 0;
								Ans[1] = 0;
								Ans[2] = v10;
								v3 = v9 + 0xA * v8;
								GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
							}
							if (v3 == v10)
								break;
							++v6;
							*Ans = 0;
							Ans[1] = 0;
							Ans[2] = v10;
							GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
						}
						v7 = 0;
					}
					else
					{
						--v7;
					}
				} while (v7);
				*Ans = 0;
				Ans[1] = 0;
				Ans[2] = 0;
				result = 3;
			}
			else
			{
				*Ans = 0xFF;
				Ans[1] = 2;
				result = 2;
			}
			return result;
		}
		if (v5 == 4)
		{
			IOCTRLSelect_sub_8030606(0, 2u);
			v63 = IOCTRLGet_sub_80306E2();
			*Ans = 0;
			Ans[1] = 0;
			Ans[2] = v63;
			GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
			goto LABEL_310;
		}
		if (v5 < 4)
		{
			IOCTRLSelect_sub_8030606(1u, 0);
			IOCTRLSet_sub_8030658(0, 0);
			Delay_802EF34(0x36B0);
			IOCTRLSet_sub_8030658(1, 0);
			*Ans = 0xFF;
			Ans[1] = 0;
			return 2;
		}
		if (v5 == 6)
		{
			Delay_802EF34(0x4B0);
			v16 = 0x64;
		LABEL_74:
			if (!(_BYTE)v16--)
			{
				*Ans = 0xFF;
				Ans[1] = 2;
				return 2;
			}
			v18 = 0x64;
			do
			{
				if (!(_BYTE)v18--)
					goto LABEL_74;
			} while (!Delay_WaitIoSetLow_sub_802E440(&DelayTime, 0x190u));
			while (LowHighSet_sub_802E4E0(&DelayTime) == 1)
			{
				*Ans = 0;
				Ans[1] = BYTE1(DelayTime);
				Ans[2] = DelayTime;
				GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
			}
			*Ans = 0xFF;
			Ans[1] = 2;
			result = 2;
		}
		else
		{
			if (v5 < 6)
			{
				IOCTRLSelect_sub_8030606(1u, 0);
				IOCTRLSet_sub_8030658(0, 0);
				Delay_802EF34(0x3E8);
				*Ans = 0xFF;
				Ans[1] = 0;
				return 2;
			}
			if (v5 == 8)
			{
				SC_RelayState_200049DC.Dts = 2;
				CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
				IOCTRLSelect_sub_8030606(0x13u, 1u);
				IOCTRLSet_sub_8030658(0, 0);
				Delay_802EF34(0x7D0);
				if (!Delay_WaitIoSetLow_sub_802E440(&DelayTime, 0xC8u))
				{
					*Ans = 0xFF;
					Ans[1] = 2;
					return 2;
				}
				if (SC_RelayState_200049DC.LogicType == 1)
				{
					Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 1u);
					if (DelayTime < 0x14)
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
				}
				else
				{
					Delay_WaitIoSetLow_sub_802E396(&DelayTime, 1u);
					if (DelayTime < 0x14)
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
				}
				v20 = 0;
				v21 = 0;
				v22 = 0;
				while (1)
				{
					while (1)
					{
						while (1)
						{
							do
							{
								if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x32u))
								{
									*Ans = 0xFF;
									Ans[1] = 2;
									return 2;
								}
								if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x32u))
								{
									*Ans = 0xFF;
									Ans[1] = 2;
									return 2;
								}
								++v22;
							} while (DelayTime < 0x5DC);
							v62 = DelayTime;
							Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x32u);
							if (DelayTime + v62 < 0x7D0)
								break;
							*Ans = 0;
							Ans[1] = 0;
							Ans[2] = 0xA;
							GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
						}
						do
						{
							if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x32u))
								return 2;
							if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x32u))
								return 2;
							++v21;
						} while (DelayTime < 0x5DC);
						v62 = DelayTime;
						Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x32u);
						if (DelayTime + v62 < 0x7D0)
							break;
						if (DelayTime + v62 >= 0x1388)
							goto LABEL_106;
						*Ans = 0;
						Ans[1] = 0;
						Ans[2] = v21 + 0xA * v22;
						GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
					}
					do
					{
						if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x32u))
							return 2;
						if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x32u))
							return 2;
						++v20;
					} while (DelayTime < 0x5DC);
					v62 = DelayTime;
					Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x32u);
					if (DelayTime + v62 >= 0x1388)
					{
					LABEL_106:
						*Ans = 0;
						Ans[1] = 0;
						Ans[2] = 0;
						GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
						return 0xFF;
					}
					*Ans = 0;
					Ans[1] = 0;
					Ans[2] = v20 + 0xA * v21 + 0x64 * v22;
					GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
				}
			}
			if (v5 < 8)
			{
				IOCTRLSelect_sub_8030606(1u, 0);
				IOCTRLSet_sub_8030658(1, 0);
				*Ans = 0xFF;
				Ans[1] = 2;
				return 2;
			}
			if (v5 == 0xA)
			{
				Delay_802EF34(0x4B0);
				v28 = 0x64;
			LABEL_143:
				if (!(_BYTE)v28--)
				{
					*Ans = 0xFF;
					Ans[1] = 2;
					return 2;
				}
				v30 = 0x64;
				do
				{
					if (!(_BYTE)v30--)
						goto LABEL_143;
				} while (!Delay_WaitIoSetLow_sub_802E440(&DelayTime, 0x190u));
				while (sub_802E6B4((unsigned int*)v61))
				{
					*Ans = 0;
					Ans[1] = v61[1];
					Ans[2] = v61[0];
					GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
				}
				while (LowHighSet_sub_802E4E0((unsigned int*)v61) == 1)
				{
					*Ans = 0;
					Ans[1] = v61[1];
					Ans[2] = v61[0];
					GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
				}
				*Ans = 0xFF;
				Ans[1] = 2;
				result = 2;
			}
			else
			{
				if (v5 < 0xA)
				{
					v23 = 0;
					if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
					v24 = 0x14;
					do
					{
						if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
						if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
						if (DelayTime >= 0x9C4)
						{
							while (1)
							{
								while (1)
								{
									v25 = 0;
									v26 = 0;
									do
									{
										if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x14u))
										{
											*Ans = 0xFF;
											Ans[1] = 2;
											return 2;
										}
										if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x14u))
										{
											*Ans = 0xFF;
											Ans[1] = 2;
											return 2;
										}
										++v25;
									} while (DelayTime < 0x3E8);
									do
									{
										if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x14u))
										{
											*Ans = 0xFF;
											Ans[1] = 2;
											return 2;
										}
										if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x14u))
										{
											*Ans = 0xFF;
											Ans[1] = 2;
											return 2;
										}
										++v26;
									} while (DelayTime < 0x9C4);
									v27 = v26 + 0xA * v25;
									if (v23)
										break;
									v23 = 1;
									*Ans = 0;
									Ans[1] = 0;
									Ans[2] = v27;
									v3 = v26 + 0xA * v25;
									GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
								}
								if (v3 == v27)
									break;
								++v23;
								*Ans = 0;
								Ans[1] = 0;
								Ans[2] = v27;
								GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
							}
							v24 = 0;
						}
						else
						{
							--v24;
						}
					} while (v24);
					memset(Ans, 0, 3);
					GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
					goto LABEL_310;
				}
				if (v5 == 0xC)
				{
					v63 = 2;
					LOBYTE(v37) = 0x14;
					while (1)
					{
						if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
							return 2;
						if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
							return 2;
						if (DelayTime >= 0x7D0)
							break;
						v37 = (unsigned __int8)(v37 - 1);
						if (!v37)
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
					}
					while (1)
					{
						v38 = 0;
						do
						{
							if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
							{
								*Ans = 0xFF;
								Ans[1] = 2;
								return 2;
							}
							if (DelayTime < 0x2EE)
								v38 *= 2;
							else
								v38 = (2 * v38) | 1;
							if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
							{
								*Ans = 0;
								Ans[1] = 0;
								Ans[2] = 0;
								GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
							}
						} while (DelayTime < 0x4E2);
						*Ans = 0;
						Ans[1] = 0;
						Ans[2] = v38;
						GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
					}
				}
				if (v5 < 0xC)
				{
					v32 = 0;
					v33 = sub_802EB50(v64, 0xFFu);
					v34 = v33;
					if (v33)
					{
						while ((_BYTE)v34--)
						{
							*Ans = 0;
							Ans[1] = v64[v32];
							v36 = (unsigned __int8)(v32 + 1);
							Ans[2] = v64[v36];
							v32 = v36 + 1;
							GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
							Delay_802EF34(0x32);
						}
						*Ans = 0xFF;
						Ans[1] = 2;
						result = 2;
					}
					else
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						result = 2;
					}
					return result;
				}
				if (v5 == 0xE)
				{
					IOCTRLSelect_sub_8030606(1u, 0);
					IOCTRLSet_sub_8030658(1, 0);
					AboutSysTicksub_803120C(0x5DCu);
					IOCTRLSet_sub_8030658(0, 0);
					AboutSysTicksub_803120C(0xBB8u);
					LOBYTE(v44) = 0;
					if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
					while (1)
					{
						if (!sub_802E490(&DelayTime, 0xC8u))
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
						if (!Delay_WaitIoSetLow_sub_802E440(&DelayTime, 0xC8u))
							break;
						if (DelayTime >= 0x5DC0)
						{
							while (sub_802E78E((unsigned int *)v61))
							{
								if (!(*(_DWORD *)v61 >> 8 << 0x18) && v61[0] == 0xA)
									goto LABEL_221;
							}
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
					}
					do
					{
						if (!sub_802E490(&DelayTime, 0xC8u))
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
						if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
					} while (DelayTime < 0xBB8);
				LABEL_221:
					if (!sub_802E864((unsigned int *)v61))
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
					v45 = *(_DWORD *)v61 >> 8;
					v46 = v61[0];
					if (*(unsigned __int16 *)v61 != 0xA)
					{
						while (1)
						{
							*Ans = 0;
							Ans[1] = v61[1];
							Ans[2] = v61[0];
							GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
							if (!sub_802E864((unsigned int *)v61))
								break;
							if (*(unsigned __int16 *)v61 == 0xA)
								goto LABEL_229;
						}
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
				LABEL_229:
					if (!sub_802E78E((unsigned int *)v61))
					{
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
					if (*(unsigned __int16 *)v61 != 0xA)
					{
						v64[0] = v61[1];
						v64[1] = v61[0];
						LOBYTE(v44) = 1;
						while (sub_802E78E((unsigned int *)v61))
						{
							if (*(unsigned __int16 *)v61 == 0xA)
								goto LABEL_238;
							v64[2 * (unsigned __int8)v44] = v61[1];
							v64[2 * (unsigned __int8)v44 + 1] = v61[0];
							LOBYTE(v44) = v44 + 1;
						}
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
					while (1)
					{
					LABEL_238:
						if (!sub_802E864((unsigned int *)v61))
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
						if (v61[1] == (unsigned __int8)v45 && v61[0] == v46)
							break;
						*Ans = 0;
						Ans[1] = v61[1];
						Ans[2] = v61[0];
						GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
					}
					while ((_BYTE)v44)
					{
						*Ans = 0;
						v44 = (unsigned __int8)(v44 - 1);
						Ans[1] = v64[2 * v44];
						Ans[2] = v64[2 * (unsigned __int8)v44 + 1];
						GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
						Delay_802EF34(0x64);
					}
				LABEL_288:
					*Ans = 0;
					Ans[1] = 0;
					Ans[2] = 0;
					GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
					goto LABEL_310;
				}
				if (v5 < 0xE)
				{
					v39 = 0;
					v40 = 0x28;
					if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 25u))
						return 2;
					if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 25u))
					{
						*Ans = 0;
						Ans[1] = 0;
						Ans[2] = 0;
						GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
					}
					while (1)
					{
						if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
							return 2;
						Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u);
						if (DelayTime >= 0xDAC)
						{
							while (1)
							{
								while (1)
								{
									v41 = 0;
									v42 = 0;
									do
									{
										if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 25u))
											return 2;
										if (DelayTime < 0x36B)
											goto LABEL_195;
										if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
											return 2;
										++v41;
									} while (DelayTime < 0x36B);
									if (DelayTime < 0xABE)
									{
										do
										{
											if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
												return 2;
										LABEL_195:
											if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
												return 2;
											++v42;
										} while (DelayTime < 0x9C4);
									}
									v43 = v42 + 0xA * v41;
									if (v39)
										break;
									v39 = 1;
									*Ans = 0;
									Ans[1] = 0;
									Ans[2] = v43;
									v3 = v42 + 0xA * v41;
									GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
								}
								if (v3 == v43)
									break;
								++v39;
								*Ans = 0;
								Ans[1] = 0;
								Ans[2] = v43;
								GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
							}
							*Ans = 0;
							Ans[1] = 0;
							Ans[2] = 0;
							GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
						}
						else
						{
							--v40;
						}
						if (!v40)
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
					}
				}
				if (v5 == 0x10)
				{
					Delay_802EF34(0x320);
					v47 = 0;
					if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
					{
						*Ans = 0;
						Ans[1] = 0;
						Ans[2] = 0;
						GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
					}
					v48 = 0x14;
					while (1)
					{
						if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							return 2;
						}
						if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
							break;
						if (DelayTime >= 0xBB8)
						{
							while (2)
							{
								while (2)
								{
									v49 = 0;
									v50 = 0;
									do
									{
										if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u))
										{
											*Ans = 0xFF;
											Ans[1] = 2;
											return 2;
										}
										if (DelayTime < 0x3E8)
										{
											do
											{
												++v50;
												if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
												{
													*Ans = 0xFF;
													Ans[1] = 2;
													return 2;
												}
												if (DelayTime >= 0xBB8)
													goto LABEL_282;
											} while (Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTime, 0x19u));
											*Ans = 0xFF;
											Ans[1] = 2;
											return 2;
										}
										++v49;
										if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
										{
											*Ans = 0xFF;
											Ans[1] = 2;
											return 2;
										}
									} while (DelayTime < 0xBB8);
								LABEL_282:
									v51 = v50 + 0xA * v49;
									if (!v47)
									{
										v47 = 1;
										*Ans = 0;
										Ans[1] = 0;
										Ans[2] = v51;
										v3 = v50 + 0xA * v49;
										GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
										continue;
									}
									break;
								}
								if (v3 != v51)
								{
									++v47;
									*Ans = 0;
									Ans[1] = 0;
									Ans[2] = v51;
									GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
									continue;
								}
								break;
							}
							v48 = 0;
						}
						else
						{
							--v48;
						}
						if (!v48)
							goto LABEL_288;
					}
					*Ans = 0xFF;
					Ans[1] = 2;
					result = 2;
				}
				else
				{
					if (v5 < 0x10)
					{
						IOCTRLSelect_sub_8030606(1u, 0);
						IOCTRLSet_sub_8030658(0, 0);
						Delay_802EF34(0xC8);
						if (Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
						{
							while (1)
							{
								if (!sub_802E490(&DelayTime, 0xC8u))
								{
									*Ans = 0xFF;
									Ans[1] = 2;
									return 2;
								}
								if (!Delay_WaitIoSetLow_sub_802E440(&DelayTime, 0xC8u))
									break;
								if (DelayTime >= 0x5DC0)
								{
								LABEL_256:
									IOCTRLSet_sub_8030658(1, 0);
									Delay_802EF34(0xC8);
									*Ans = 0xFF;
									Ans[1] = 0;
									return 2;
								}
							}
							while (1)
							{
								if (!sub_802E490(&DelayTime, 0xC8u))
								{
									*Ans = 0xFF;
									Ans[1] = 2;
									return 2;
								}
								if (!Delay_WaitIoSetLow_sub_802E396(&DelayTime, 0x19u))
									break;
								if (DelayTime >= 0xBB8)
									goto LABEL_256;
							}
							*Ans = 0xFF;
							Ans[1] = 2;
							result = 2;
						}
						else
						{
							*Ans = 0xFF;
							Ans[1] = 2;
							result = 2;
						}
						return result;
					}
					if (v5 == 0x12)
					{
						SC_RelayState_200049DC.Dts = 2;
						CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
						IOCTRLSelect_sub_8030606(0x13u, 1u);
						IOCTRLSet_sub_8030658(0, 0);
						Delay_802EF34(0x3E8);
						IOCTRLSet_sub_8030658(1, 0);
						Delay_802EF34(0x7D0);
						IOCTRLSet_sub_8030658(0, 0);
						Delay_802EF34(0x3E8);
						IOCTRLSet_sub_8030658(1, 0);
						Delay_802EF34(0x3E8);
						IOCTRLSet_sub_8030658(0, 0);
						Delay_802EF34(0x3E8);
						IOCTRLSet_sub_8030658(1, 0);
						Delay_802EF34(0x3E8);
						IOCTRLSet_sub_8030658(0, 0);
						Delay_802EF34(0x7D0);
						IOCTRLSet_sub_8030658(1, 0);
						*Ans = 0xFF;
						Ans[1] = 0;
						return 2;
					}
					if (v5 < 0x12)
					{
						Copysub_802FB50(Ans, byte_802B14C, 0x19);
						GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 0x1B);
					LABEL_310:
						*Ans = 0xFF;
						Ans[1] = 2;
						return 2;
					}
					if (v5 == 0x14)
					{
						Delay_802EF34(0x4B0);
						v56 = 0x64;
						while ((_BYTE)v56--)
						{
							v58 = 0x64;
							while ((_BYTE)v58--)
							{
								if (Delay_WaitIoSetLow_sub_802E440(&DelayTime, 0x190u))
								{
									while (sub_802E5B4((unsigned int*)v61) == 1)
									{
										*Ans = 0;
										Ans[1] = v61[1];
										Ans[2] = v61[0];
										GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
									}
									*Ans = 0xFF;
									Ans[1] = 0;
									return 2;
								}
							}
						}
						*Ans = 0xFF;
						Ans[1] = 0;
						result = 2;
					}
					else
					{
						if (v5 >= 0x14)
						{
							if (v5 == 0x15)
							{
								Copysub_802FB50(Ans, byte_802B2DC, 7);
								GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 9);
							}
							goto LABEL_310;
						}
						IOCTRLSelect_sub_8030606(0, 2u);
						IOCTRLSelect_sub_8030606(1u, 0);
						IOCTRLSet_sub_8030658(0, 0);
						Delay_802EF34(0x7D0);
						v52 = 0x64;
						while ((_BYTE)v52--)
						{
							v54 = 0x64;
							while ((_BYTE)v54--)
							{
								if (Delay_WaitIoSetLow_sub_802E440(&DelayTime, 0x190u))
								{
									while (sub_802E5B4((unsigned int*)v61) == 1)
									{
										*Ans = 0;
										Ans[1] = v61[1];
										Ans[2] = v61[0];
										GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, 5);
									}
									*Ans = 0xFF;
									Ans[1] = 0;
									return 2;
								}
							}
						}
						*Ans = 0xFF;
						Ans[1] = 0;
						result = 2;
					}
				}
			}
		}
	}
	return result;
}






int ID6102_sub_8024E98(int Argc, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned __int8 v4; // r6
	int AnsPos; // r11
	int v7; // r6
	char v9; // r6
	int v10; // r6
	int v12; // r11
	int v13; // r11
	int v14; // r6
	char v15; // r6
	int v16; // r7
	int v17; // r5
	int v19; // r5
	int i; // r11
	int v22; // r5
	int v24; // r5
	int v25; // r7
	int v28; // r7
	int v30; // r7
	int v32; // r7
	int v34; // r7
	int v36; // r10
	int v37; // r11
	int v38; // r11
	int v39; // r7
	int v41; // r7
	unsigned __int8 v43; // r8
	int v44; // r11
	char v45; // r8
	int v46; // r11
	char v47; // r8
	unsigned __int8 v48; // r6
	unsigned int j; // r9
	int v50; // r10
	unsigned int m; // r9
	int v53; // r10
	unsigned __int8 v55; // r6
	unsigned int k; // r9
	int v57; // r10
	unsigned __int8 v59; // r6
	unsigned int l; // r9
	int v61; // r10
	unsigned __int8 AnsByte; // [sp+0h] [bp-48h] BYREF
	char v63; // [sp+1h] [bp-47h]
	unsigned __int8 v64; // [sp+2h] [bp-46h]
	char v65; // [sp+3h] [bp-45h]
	int v66; // [sp+4h] [bp-44h]
	int v67; // [sp+8h] [bp-40h]
	int v68; // [sp+Ch] [bp-3Ch]
	int v69; // [sp+10h] [bp-38h]
	unsigned __int8 v70; // [sp+14h] [bp-34h]

	v4 = 0;
	v68 = 0;
	v67 = 0;
	v69 = 0;
	v66 = 0;
	set_time0Stop_sub_802BB48();
	v70 = *Argv;
	*Ans = 0;
	Ans[1] = 0;
	AnsPos = 3;
	if (v70 == 1)
	{
		if (Delay_OpenPort_sub_802DE94(0xFA0, 0x64, 1) == 1)
		{
			szFBREAK_20004A0C[0] = 0xFF;
			szFBREAK_20004A0C[1] = 2;
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
			return 2;
		}
		do
		{
			while (IOCTRLGet_sub_80306E2())
			{
				Delay_sub_802EF46(0x64u);
				if ((unsigned int)++v66 > 0x3E8)
				{
					v66 = 0;
					szFBREAK_20004A0C[0] = 0xFF;
					szFBREAK_20004A0C[1] = 2;
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
					return 2;
				}
			}
		} while (JudgeHighAndLowCnt_sub_802E938(4u));
		Delay_802EF34(0x6C);
		IOCTRLSelect_sub_8030606(0, 2u);
		v7 = 0xC;
		while ((_BYTE)v7--)
		{
			if (!sub_802E980(&AnsByte))
			{
				szFBREAK_20004A0C[0] = 0xFF;
				szFBREAK_20004A0C[1] = 2;
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
				return 2;
			}
			Ans[AnsPos++] = AnsByte;
		}
		Ans[1] = 1;
		Ans[2] = 0xC;
		goto LABEL_275;
	}
	if (v70)
	{
		if (v70 == 3)
		{
			v12 = 3;
			while (ComByte_sub_802F6CC(&AnsByte, 0x320))
			{
				if (AnsByte == 0x14)
				{
					Ans[v12++] = AnsByte;
					if (!ComByte_sub_802F6CC(&AnsByte, 0x320))
						return 2;
					if (AnsByte == 0xFC)
					{
						Ans[v12++] = AnsByte;
						if (!ComByte_sub_802F6CC(&AnsByte, 0x320))
							goto LABEL_272;
						if (AnsByte == 0xC)
						{
							Ans[v12] = AnsByte;
							v13 = v12 + 1;
							if (ComByte_sub_802F6CC(&AnsByte, 0x320))
							{
								Ans[v13] = AnsByte;
								AnsPos = v13 + 1;
								v14 = 0x10;
								while (ComByte_sub_802F6CC(&AnsByte, 0x12C))
								{
									Ans[AnsPos++] = AnsByte;
									if (!(_BYTE)--v14)
									{
										Ans[1] = 1;
										Ans[2] = AnsPos - 3;
										goto LABEL_275;
									}
								}
							}
							goto LABEL_272;
						}
					}
				}
			}
			goto LABEL_272;
		}
		if (v70 < 3u)
		{
			while (1)
			{
				v9 = 0;
				AnsPos = 3;
				if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
					goto LABEL_272;
				if (AnsByte == 0xFF)
				{
					Ans[3] = AnsByte;
					AnsPos = 4;
					v9 = 1;
					if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
						goto LABEL_272;
					if (!AnsByte)
					{
						Ans[4] = 0;
						AnsPos = 5;
						v9 = 2;
						if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
							goto LABEL_272;
						if (AnsByte == 0x2A)
						{
							Ans[5] = AnsByte;
							AnsPos = 6;
							v9 = 3;
							if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
								goto LABEL_272;
							if (AnsByte == 0x46)
							{
								Ans[6] = AnsByte;
								AnsPos = 7;
								v9 = 4;
								if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
									goto LABEL_272;
								if (!AnsByte)
								{
									Ans[7] = 0;
									AnsPos = 8;
									v9 = 5;
								}
							}
						}
					}
				}
				if (v9 == 5)
				{
					v10 = 0x29;
					while ((_BYTE)v10--)
					{
						if (!ComByte_sub_802F6CC(&AnsByte, 0x12C))
							goto LABEL_272;
						Ans[AnsPos++] = AnsByte;
					}
					*Ans = 0;
					Ans[1] = 1;
					Ans[2] = AnsPos - 3;
					goto LABEL_275;
				}
			}
		}
		if (v70 == 5)
			goto LABEL_179;
		if (v70 < 5u)
		{
			v15 = 9;
			while (ComByte_sub_802F6CC(&AnsByte, 0x1F4))
			{
				if ((AnsByte & 0x10) != 0)
					--v15;
				else
					v15 = 9;
				if (!v15)
				{
					v16 = 0x13;
					while (ComByte_sub_802F6CC(&AnsByte, 0x1F4))
					{
						AnsByte &= 0x10u;
						if (AnsByte)
						{
							v63 = 8;
							v17 = 0;
							while (v63--)
							{
								if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
									goto LABEL_272;
								v19 = 2 * v17;
								AnsByte &= 0x10u;
								if (AnsByte)
									v17 = v19 & 0xFE;
								else
									v17 = v19 | 1;
							}
							Ans[1] = v17;
							for (i = 2; (_BYTE)v16--; ++i)
							{
								if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
									goto LABEL_272;
								AnsByte &= 0x10u;
								if (!AnsByte)
									goto LABEL_272;
								v63 = 8;
								v22 = 0;
								while (v63--)
								{
									if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
										goto LABEL_272;
									v24 = 2 * v22;
									AnsByte &= 0x10u;
									if (AnsByte)
										v22 = v24 & 0xFE;
									else
										v22 = v24 | 1;
								}
								Ans[i] = v22;
							}
							Ans[1] = 1;
							return i;
						}
					}
					goto LABEL_272;
				}
			}
			goto LABEL_272;
		}
		if (v70 != 7)
		{
			if (v70 < 7u)
			{
				if (CheckIoBusy_sub_802DF38(0x64, 1, 1) == 1)
					goto LABEL_179;
				if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
				{
					Ans[3] = AnsByte;
					if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
					{
						Ans[4] = AnsByte;
						AnsPos = 5;
						v25 = AnsByte - 0x54;
						while ((_BYTE)v25--)
						{
							if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
								goto LABEL_272;
							Ans[AnsPos++] = AnsByte;
						}
						Ans[1] = 1;
						goto LABEL_275;
					}
				}
			}
			else if (v70 == 9)
			{
				if (CheckIoBusy_sub_802DF38(0x80, 3, 1) == 1)
					goto LABEL_179;
				if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
				{
					Ans[3] = AnsByte;
					AnsPos = 4;
					v34 = 0x7F;
					while ((_BYTE)v34--)
					{
						if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
							goto LABEL_272;
						Ans[AnsPos++] = AnsByte;
					}
					Ans[1] = 1;
					goto LABEL_275;
				}
			}
			else if (v70 < 9u)
			{
				if (CheckIoBusy_sub_802DF38(0x12C, 8, 1) == 1)
					goto LABEL_179;
				if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
				{
					Ans[3] = AnsByte;
					AnsPos = 4;
					v32 = AnsByte + 1;
					while ((_BYTE)v32--)
					{
						if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
							goto LABEL_272;
						Ans[AnsPos++] = AnsByte;
					}
					Ans[1] = 1;
					Ans[2] = AnsPos - 3;
					goto LABEL_275;
				}
			}
			else if (v70 == 0xB)
			{
				AnsPos = 3;
				Ans[2] = 0;
				v69 = 3;
				v36 = 0x32;
			LABEL_161:
				if (v36)
				{
					--v36;
					v37 = v69;
					while (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
					{
						if (AnsByte == 0xFF)
						{
							++Ans[2];
							Ans[v37] = AnsByte;
							v38 = v37 + 1;
							if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
								goto LABEL_272;
							Ans[v38] = AnsByte;
							AnsPos = v38 + 1;
							++Ans[2];
							if (!AnsByte)
								goto LABEL_176;
							v39 = AnsByte;
							while ((_BYTE)v39--)
							{
								if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
									goto LABEL_272;
								Ans[AnsPos++] = AnsByte;
								++Ans[2];
							}
							if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
								goto LABEL_272;
							if (AnsByte == 0xFF)
								goto LABEL_176;
							Ans[2] = 0;
							goto LABEL_161;
						}
					}
					goto LABEL_272;
				}
			LABEL_176:
				if (v36)
				{
					Ans[1] = 1;
					goto LABEL_275;
				}
			}
			else
			{
				if (v70 < 0xBu)
				{
					while (ComByte_sub_802F6CC(&AnsByte, 0x1F4))
					{
						if (AnsByte == 0xFF)
						{
							Ans[AnsPos++] = AnsByte;
							if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
								goto LABEL_272;
							if (!AnsByte)
							{
								Ans[AnsPos++] = 0;
								if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
									goto LABEL_272;
								if (AnsByte == 0x10)
								{
									Ans[AnsPos++] = AnsByte;
									if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
										goto LABEL_272;
									if (AnsByte == 0x63)
									{
										Ans[AnsPos++] = AnsByte;
										if (!ComByte_sub_802F6CC(&AnsByte, 0x1F4))
											goto LABEL_272;
										if (AnsByte == 0x47)
											Ans[AnsPos++] = AnsByte;
									}
								}
							}
						}
					}
					goto LABEL_272;
				}
				if (v70 == 0xD)
				{
					do
					{
						v65 = 0;
						if (CheckIoBusy_sub_802DF38(0x80, 4, 1) == 1)
							return 2;
						if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
						{
							v43 = AnsByte;
							Ans[AnsPos] = AnsByte;
							v44 = AnsPos + 1;
							if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
							{
								v45 = AnsByte + v43;
								Ans[v44] = AnsByte;
								v46 = v44 + 1;
								if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
								{
									v47 = AnsByte + v45;
									Ans[v46] = AnsByte;
									AnsPos = v46 + 1;
									v48 = AnsByte;
									for (j = 0; j < (unsigned int)v48 - 5; ++j)
									{
										if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
											goto LABEL_272;
										v47 += AnsByte;
										Ans[AnsPos++] = AnsByte;
									}
									if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
									{
										v65 += AnsByte;
										if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
											continue;
									}
								}
							}
						}
						goto LABEL_272;
					} while (v47 != v65);
					Ans[1] = 1;
					goto LABEL_275;
				}
				if (v70 >= 0xDu)
				{
					if (v70 == 0xF)
					{
						v53 = 0x19;
						while (v53--)
						{
							AnsPos = 3;
							Ans[2] = 0;
							if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
								goto LABEL_272;
							if (AnsByte == 0x20)
							{
								Ans[3] = AnsByte;
								++Ans[2];
								if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
									goto LABEL_272;
								Ans[4] = AnsByte;
								++Ans[2];
								if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
									goto LABEL_272;
								v55 = AnsByte;
								Ans[5] = AnsByte;
								AnsPos = 6;
								++Ans[2];
								while (Ans[2] < (unsigned int)v55)
								{
									if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
										goto LABEL_272;
									Ans[AnsPos++] = AnsByte;
									++Ans[2];
								}
								for (k = 3; k < AnsPos - 2; ++k)
									v68 += Ans[k];
								v67 += Ans[k];
								v67 += Ans[k + 1] << 8;
								if (v68 == v67)
									break;
							}
						}
						Ans[1] = 1;
					}
					else if (v70 >= 0xFu)
					{
						if (v70 == 0x11)
						{
							v61 = 9;
							v66 = 0;
							*Ans = 0;
							Ans[1] = 1;
							AnsPos = 3;
							while (v61)
							{
								if (v61 == 9)
								{
									if (!ComByte_sub_802F6CC(&AnsByte, 0xC8))
										goto LABEL_272;
									if (AnsByte == 0x37)
									{
										Ans[AnsPos++] = AnsByte;
										v61 = 8;
									}
									else if ((unsigned int)++v66 >= 0x65)
									{
										goto LABEL_272;
									}
								}
								else
								{
									if (!ComByte_sub_802F6CC(&AnsByte, 0x32))
										goto LABEL_272;
									Ans[AnsPos++] = AnsByte;
									--v61;
								}
							}
							Ans[2] = AnsPos - 3;
						}
						else if (v70 < 0x11u)
						{
							v57 = 0x19;
							while (v57--)
							{
								Ans[2] = 0;
								if (!ComByte_sub_802F6CC(&AnsByte, 0xBB8))
									goto LABEL_272;
								Ans[3] = AnsByte;
								AnsPos = 4;
								++Ans[2];
								v64 = AnsByte;
								if ((AnsByte & 0x80) != 0)
								{
									if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
										goto LABEL_272;
									if (AnsByte == 0xF1)
									{
										Ans[4] = AnsByte;
										AnsPos = 5;
										++Ans[2];
										if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
											goto LABEL_272;
										if (AnsByte == 0xC1)
										{
											Ans[5] = AnsByte;
											AnsPos = 6;
											++Ans[2];
											break;
										}
									}
								}
							}
							v59 = v64 & 0xF;
							for (l = 0; l < (unsigned int)v59 + 1; ++l)
							{
								if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
									goto LABEL_272;
								Ans[AnsPos++] = AnsByte;
								++Ans[2];
							}
							Ans[1] = 1;
						}
					}
					else
					{
						v50 = 0x19;
						while (v50--)
						{
							Ans[2] = 0;
							if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
								goto LABEL_272;
							Ans[3] = AnsByte;
							AnsPos = 4;
							++Ans[2];
							v64 = AnsByte;
							if (AnsByte == 0x80)
							{
								if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
									goto LABEL_272;
								if (AnsByte == 0xF2)
								{
									Ans[4] = AnsByte;
									AnsPos = 5;
									++Ans[2];
									if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
										goto LABEL_272;
									if (AnsByte == 0x50)
									{
										Ans[5] = AnsByte;
										AnsPos = 6;
										++Ans[2];
										break;
									}
								}
							}
							else if (v64 == 0x20)
							{
								if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
									goto LABEL_272;
								if (AnsByte == 0xB0)
								{
									Ans[4] = AnsByte;
									AnsPos = 5;
									++Ans[2];
									break;
								}
							}
						}
						if (!v50 || !ComByte_sub_802F6CC(&AnsByte, 0x3E8))
							goto LABEL_272;
						Ans[AnsPos++] = AnsByte;
						++Ans[2];
						if (v64 == 0x80)
							v4 = AnsByte;
						if (v64 == 0x20)
							v4 = AnsByte - 4;
						for (m = 0; m < (unsigned int)v4 + 1; ++m)
						{
							if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
								goto LABEL_272;
							Ans[AnsPos++] = AnsByte;
							++Ans[2];
						}
						Ans[1] = 1;
					}
					goto LABEL_275;
				}
				if (CheckIoBusy_sub_802DF38(0x80, 5, 1) == 1)
				{
				LABEL_179:
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
					return 2;
				}
				if (ComByte_sub_802F6CC(&AnsByte, 0x3E8))
				{
					Ans[3] = AnsByte;
					AnsPos = 4;
					v41 = AnsByte + 1;
					while ((_BYTE)v41--)
					{
						if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
							goto LABEL_272;
						Ans[AnsPos++] = AnsByte;
					}
					Ans[1] = 1;
					goto LABEL_275;
				}
			}
		LABEL_272:
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
			return 2;
		}
		if (CheckIoBusy_sub_802DF38(0x64, 1, 1) != 1)
		{
			v63 = 0xC8;
			while (v63--)
			{
				if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
					goto LABEL_272;
				if (AnsByte == 0x41)
					break;
				if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
					goto LABEL_272;
				v28 = AnsByte - 0x54;
				while ((_BYTE)v28--)
				{
					if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
						goto LABEL_272;
				}
			}
			Ans[3] = AnsByte;
			if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
				goto LABEL_272;
			Ans[4] = AnsByte;
			AnsPos = 5;
			v30 = AnsByte - 0x54;
			while ((_BYTE)v30--)
			{
				if (!ComByte_sub_802F6CC(&AnsByte, 0x3E8))
					goto LABEL_272;
				Ans[AnsPos++] = AnsByte;
			}
			Ans[1] = 1;
			goto LABEL_275;
		}
		goto LABEL_179;
	}
LABEL_275:
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return AnsPos;
}



// // Funtion: BOSCH地址码触发函数  bosch协议专用
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:一帧数据发送的次数
// //          argv[1]:待发送的命令的帧数
// //          argv[2]到指令末尾：发送的一帧数据的长度  发送的一帧的数据，一直下去直到指令末尾
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、成功则返回 FF 00
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6104 Only send data to ecu not receive anyone data from ecu
int ID6104FunOnlySendToEcu_1_sub_8023BB4(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	char CANCONNECTOR; // r10
	int sendtime; // r8
	int result; // r0
	unsigned __int8 argvpos; // r7
	int framenum; // r9
	unsigned __int8 sendlen; // r0 MAPDST

	CANCONNECTOR = 0;
	set_time0Stop_sub_802BB48();
	if (argv[3] == 0x55 && argv[4] == 0xAA)
		CANCONNECTOR = 1;
	sendtime = *argv;
	if ((_BYTE)sendtime)
	{
		while ((_BYTE)sendtime--)
		{
			argvpos = 2;
			framenum = argv[1];
			if (!(_BYTE)framenum)
			{
				PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return 2;
			}
			while ((_BYTE)framenum--)
			{
				sendlen = argv[argvpos++];
				if (!sendlen)
				{
					PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 2;
				}
				while (sendlen--)
				{
					if (CANCONNECTOR == 1)
					{
						setCanbusNormalDataToken_sub_802DD42(&argv[argvpos + 2]);
						argvpos += sendlen;
						break;
					}
					ComSendByte_sub_802F1E0(argv[argvpos++]);
					if (sendlen >= 2u)
						Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
				}
				Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
			}
		}
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
		result = 2;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}





// 他这个 第3个参数 传递的是盒子的序列号
// Ex A1: 0x00000010 
// A2:0x200078C3  内容是FF 01 0A 55 AA 06 60 01 00 01 FD 00 9B 00 03  FC 00 1E 01 01 2C
// A3:0x20008E3E 00 61 05 55 AA 01 00 01 35 39 31 37 32 31 37 30 30 01 08 01 00 02 04
int ID6105Funsub_805383C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int result; // r0 61 05 Argv: FF 01 07 55 AA 03 60 05 FF 99 00 03 FC 00 
				//                FF 01 08 55 AA 04 60 02 00 03 65 00 03 
				//                FF 01 07 55 AA 03 60 04 00 67 00 03 FC 80
				//                FF 01 0A 55 AA 06 60 01 00 01 C2 00 A4 00 03 FC 89 
				//                FF 01 04 44 04 00 40 00 02 00 97 
	int v5; // r9
	int v6; // r11
	unsigned __int8 v7; // r0 MAPDST
	int v8; // r11
	unsigned __int8 v9; // r6
	int v11; // r0
	int v12; // r6
	int v13; // r0
	int v14; // r11
	int v15; // r6
	unsigned int v16; // r7
	int v17; // r8
	unsigned int i; // r10
	unsigned int j; // r10
	unsigned __int8 v20; // r8
	unsigned int v21; // r7
	unsigned int k; // r10
	unsigned __int8 CmdByteData; // [sp+0h] [bp-38h] BYREF
	unsigned __int8 v24; // [sp+1h] [bp-37h]
	char v25; // [sp+2h] [bp-36h]
	unsigned __int8 v26; // [sp+3h] [bp-35h]
	unsigned __int8 *v27; // [sp+4h] [bp-34h]
	unsigned __int8 v28; // [sp+8h] [bp-30h]
	unsigned __int8 v29; // [sp+9h] [bp-2Fh]
	int v30; // [sp+Ch] [bp-2Ch]
	unsigned __int8 *BuleThData; // [sp+10h] [bp-28h]

	v30 = argc;
	BuleThData = argv;
	v24 = 0;
	v26 = 0;
	v25 = 0;
	v27 = receive_buff_2000BF20;
	if (argv[3] == 0xAA
		&& BuleThData[4] == 0x55
		&& SC_RelayState_200049DC.LLine == 1
		&& SC_RelayState_200049DC.InputChannel != 0xD)
	{
		SC_RelayState_200049DC.InputChannel = -1;
		SC_RelayState_200049DC.LLine = 2;
		CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	}
	if (!*BuleThData)
		ExitFlag_2000C6BA = 1;
	set_time0Stop_sub_802BB48();
	*ans = 0;
	if (BuleThData[3] == 0x55 && BuleThData[4] == 0xAA)
	{
		v25 = 1;
		if (!SC_RelayState_200049DC.CommType)
			SC_RelayState_200049DC.CommType = 1;
	}
	v28 = BuleThData[1];
	if (v28)
	{
		ans[1] = v28;
		v5 = 2;
		ans[2] = 0;
		v6 = 2;
		while (1)
		{
			v7 = BuleThData[v6];
			v8 = v6 + 1;
			v9 = v7;
			if (!v7)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
				return 2;
			}
			while (1)
			{
				if (!v7)
					goto LABEL_45;
				--v7;
				if (v25 == 1)
					break;
				ComSendByte_sub_802F1E0(BuleThData[v8++]);
				if (v7)
					Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			setCanbusNormalDataToken_sub_802DD42(&BuleThData[v8 + 2]);// ex:这里传出的参数的值为06 60 01 00 01 FD 00 9B 00 03 FC 00 1E 01 01 2C
			v8 += v9;
			if (BuleThData[6] == 0x60)
			{
				if ((unsigned int)BuleThData[7] - 1 <= 1// BuleThData[7] 命令的ID的第二个字节 比如 60 02的02
					|| (unsigned int)BuleThData[7] - 4 <= 3
					|| (unsigned int)BuleThData[7] - 10 <= 1)
				{
					ans[1] = 1;
					ans[2] = 5;
					ans[3] = 0x55;
					ans[4] = 0xAA;
					ans[5] = 1;
					ans[6] = 0;
					ans[7] = 1;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 8;
				}
			}
			else if (BuleThData[6] == 0x61)
			{
				if (BuleThData[7] == 3)
				{
					ans[1] = 1;
					ans[2] = 5;
					ans[3] = 0x55;
					ans[4] = 0xAA;
					ans[5] = 1;
					ans[6] = 0;
					ans[7] = 1;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 8;
				}
			}
			else if (BuleThData[6] == 0x62 && BuleThData[7] == 1)
			{
				ans[1] = 1;
				ans[2] = 5;
				ans[3] = 0x55;
				ans[4] = 0xAA;
				ans[5] = 1;
				ans[6] = 0;
				ans[7] = 1;
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return 8;
			}
		LABEL_45:
			v11 = BuleThData[v8];
			v6 = v8 + 1;
			v12 = v11;
			if ((_BYTE)v11)
				break;
			v13 = BuleThData[v6];
			v14 = v6 + 1;
			v15 = v13;
			if ((_BYTE)v13)
			{
				if (v25 != 1)
				{
					v16 = 0;
					v29 = BuleThData[v14];
					v6 = v14 + 1;
					do
					{
						if (!ComByte_sub_802F6CC(&CmdByteData, SC_TagKWP2000_20004974.m_Maxwaittime))
						{
							PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							return 2;
						}
						v27[v16++] = CmdByteData;
						--v15;
					} while ((_BYTE)v15);
					CmdByteData -= v29;
					CmdByteData -= v16;
					v17 = CmdByteData;
					if (!CmdByteData && v25 != 1)
					{
						ans[v5++] = v16;
						for (i = 0; i < v16; ++i)
							ans[v5++] = v27[i];
						goto LABEL_105;
					}
					while (ComByte_sub_802F6CC(&CmdByteData, 500))
					{
						v27[v16++] = CmdByteData;
						if (!(_BYTE)--v17)
						{
							ans[v5++] = v16;
							for (j = 0; j < v16; ++j)
								ans[v5++] = v27[j];
							goto LABEL_103;
						}
					}
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 2;
				}
				v6 = v14 + 1;
				v24 = sub_802D03C(&ans[v5 + 1]);
				ans[v5] = v24;
				v5 += v24 + 1;
				if (!v24)
				{
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 2;
				}
			}
			else
			{
				if (v25 != 1)
				{
					v20 = BuleThData[v14];
					v6 = v14 + 1;
					v21 = 0;
					do
					{
						if (!ComByte_sub_802F6CC(&CmdByteData, SC_TagKWP2000_20004974.m_Maxwaittime))
						{
							PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							return 2;
						}
						v27[v21++] = CmdByteData;
					} while (CmdByteData != v20);
					if (ComByte_sub_802F6CC(&CmdByteData, 500))
					{
						ans[v5++] = v21;
						for (k = 0; k < v21; ++k)
							ans[v5++] = v27[k];
						goto LABEL_103;
					}
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 2;
				}
				v6 = v14 + 1;
				v24 = sub_802D03C(&ans[v5 + 1]);
				ans[v5] = v24;
				v5 += v24 + 1;
				if (!v24)
				{
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 2;
				}
			}
		LABEL_103:
			if (++v26 < (unsigned int)v28)
				Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		LABEL_105:
			if (v26 >= (unsigned int)v28)
				goto LABEL_106;
		}
		if (v25 == 1)
		{
			v24 = sub_802D03C(&ans[v5 + 1]);
			ans[v5] = v24;
			v5 += v24 + 1;
			if (!v24)
			{
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return 2;
			}
		LABEL_106:
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			return v5;
		}
		ans[v5++] = v11;
		while (ComByte_sub_802F6CC(&CmdByteData, SC_TagKWP2000_20004974.m_Maxwaittime))
		{
			ans[v5++] = CmdByteData;
			if (!(_BYTE)--v12)
				goto LABEL_103;
		}
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = 2;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}




int ID6106_sub_8022594(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int SendLen; // r7
	int result; // r0
	int i; // r8
	unsigned __int8 v8; // r0
	int v9; // r8
	int v10; // r6
	int v11; // r8
	int v12; // r9
	int v13; // r0
	int v14; // r7
	int v15; // r0
	int v16; // r8
	int v17; // r11
	unsigned __int8 v18; // r10
	int v19; // r11
	int v20; // r9
	unsigned __int8 v21; // r11
	char v22; // r10
	unsigned __int8 KeyWord; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 v24; // [sp+1h] [bp-2Fh]
	int v25; // [sp+4h] [bp-2Ch]

	set_time0Stop_sub_802BB48();
	SendLen = *argv;
	if ((_BYTE)SendLen)
	{
		for (i = 1; ; ++i)
		{
			v8 = SendLen--;
			if (v8 < 2u)
				break;
			ComSendByte_sub_802F1E0(argv[i]);
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(argv[i]);
		v9 = i + 1;
		v10 = argv[v9];
		v11 = v9 + 1;
		*ans = 0;
		ans[1] = v10;
		v12 = 2;
		v25 = 0;
	LABEL_9:
		v13 = argv[v11++];
		v14 = v13;
		if ((_BYTE)v13)
		{
			ans[v12++] = v13;
			while (ComByte_sub_802F6CC(&KeyWord, 600))
			{
				ans[v12++] = KeyWord;
				if (!(_BYTE)--v14)
					goto LABEL_30;
			}
		}
		else
		{
			v15 = argv[v11];
			v16 = v11 + 1;
			if ((_BYTE)v15)
			{
				v25 = v12++;
				v17 = v15;
				v18 = 0;
				v24 = argv[v16];
				v11 = v16 + 1;
				while (ComByte_sub_802F6CC(&KeyWord, 600))
				{
					ans[v12++] = KeyWord;
					++v18;
					if (!(_BYTE)--v17)
					{
						KeyWord -= v24;
						KeyWord -= v18;
						v19 = KeyWord;
						while (ComByte_sub_802F6CC(&KeyWord, 600))
						{
							ans[v12++] = KeyWord;
							++v18;
							if (!(_BYTE)--v19)
							{
								ans[v25] = v18;
								goto LABEL_30;
							}
						}
						break;
					}
				}
			}
			else
			{
				v25 = v12;
				v20 = v12 + 1;
				v21 = argv[v16];
				v11 = v16 + 1;
				v22 = 0;
				while (ComByte_sub_802F6CC(&KeyWord, 600))
				{
					ans[v20++] = KeyWord;
					++v22;
					if (v21 == KeyWord)
					{
						if (!ComByte_sub_802F6CC(&KeyWord, 600))
							break;
						ans[v20] = KeyWord;
						v12 = v20 + 1;
						ans[v25] = v22 + 1;
					LABEL_30:
						if (!(_BYTE)--v10)
						{
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							return v12;
						}
						goto LABEL_9;
					}
				}
			}
		}
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		result = 2;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}



// //函数名称:int ISO_SendDataToEcuGetMultiFrameAnswer()
// // Input  : argc - 参数长度
// //          argv - 0xlen,0x内容,最大等待时间
// // Output : ans  - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6107
// //1.发送给上位机的数据格式是: 0x00 ,0x00, 0xlen 一帧长度 一帧内容.......
// //                            -    ----------   ---------------------
// //                            |        |                 |记录的是实际的内容。
// //                            |        |帧数记录。
// //                            |数据标志位，（0xff表示的是设置）。
// //2.argv的缓冲区的数据格式：
// //  长度　+ 内容 + 最大等待时间 //0x03 0x01,0x02,0x03,
// //3.实现的功能:ISO_9141协议的接受和发送。
// //             主要实现的是：发送并接受,直到没有接受数据为止。
// //4,协议举例:
// //   req:68 6a f1 be 81
// //   ans:48 6b c0 fe 00 01 72
int ID6107_ISO_SendDataToEcuGetMultiFrameAnswer_1_sub_8026F6E(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	__int16 v3; // r8
	unsigned int v5; // r10
	unsigned __int8 *t2Ans; // r11
	unsigned int result; // r0
	unsigned int i; // r4
	size_t ii; // r4
	size_t v10; // r10
	unsigned int SendLen; // [sp+0h] [bp-38h]
	unsigned int v12; // [sp+4h] [bp-34h]
	int time; // [sp+8h] [bp-30h]

	v3 = 0;
	v5 = 0;
	t2Ans = ans + 2;
	SendLen = *argv;
	time = 10 * CalculateTimeOut_sub_802CC3E(argv[SendLen + 1], 0xAu);
	if (argc < 0)
	{
		memset(t2Ans, 0, 4);
		*ans = -1;
		ans[1] = 2;
		return 2;
	}
	v12 = Keep_Link_200046C0.IdleTime / SC_TagKWP2000_20004974.m_MsTime;
	set_time0Stop_sub_802BB48();
	for (i = 0; i < SendLen; ++i)
	{
		ComSendByte_sub_802F1E0(argv[i + 1]);
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	ii = 1;
	do
	{
		while (1)
		{
			if (!ComByte_sub_802F6CC(&receive_buff_2000BF20[ii], time))
			{
				receive_buff_2000BF20[0] = ii - 1;
				memmove(t2Ans, receive_buff_2000BF20, ii);
				v10 = ii + v5;
				if (v3)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = 0;
					ans[1] = v3;
					result = v10 + 2;
				}
				else
				{
					Keep_Link_200046C0.timeCount = v12;
					*ans = -1;
					ans[1] = 2;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					result = 2;
				}
				return result;
			}
			if (receive_buff_2000BF20[ii] != 0x6B || receive_buff_2000BF20[ii - 1] != 0x48)
				break;
			if (v3)
			{
				receive_buff_2000BF20[0] = ii - 2;
				memmove(t2Ans, receive_buff_2000BF20, ii - 1);
				v5 += ii - 1;
				t2Ans += ii - 1;
				++v3;
				memmove(&receive_buff_2000BF20[1], &receive_buff_2000BF20[ii - 1], 2u);
				ii = 3;
				goto LABEL_21;
			}
			++ii;
			v3 = 1;
		}
		++ii;
	LABEL_21:
		;
	} while (v5 <= 0xE10);
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	*ans = 0;
	ans[1] = v3;
	return v5 + 2;
}



// // Funtion: KWP协议发多帧收多帧，对于发送的每一帧都有一帧的应答.
// // Input  : argc - 参数长度
// //          argv - 发送次数+发送帧数+发送第一帧的长度+发送帧的内容……
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6109
// //1.发送给上位机的数据格式是: 0x00 ,0x00, 0xlen 一帧长度 一帧内容 。。。。。。
// //                            -    ----------   ---------------------
// //                            |        |                 |记录的是实际的内容。
// //                            |        |帧数记录。
// //                            |数据标志位，（0xff表示的是设置）。
// //2.argv的缓冲区的数据格式：
// //  发送次数 +  发送帧数 + 发送第一帧长度 + 发送第一帧内容
// //3.实现的功能是：发多帧收多帧，并且在发送的过程中是发一帧收一帧。
// //4.在函数中能够对0X7f,0x78进行处理。
// //5.函数例程:
// //req: 82 10 F1 21 01 A5
// //ans: 82 f1 10 61 01 cc
// //req: 80 10 F1 02 21 02 A6
// //ans: 80 f1 10 03 7f 02 78 ef
// //req: 00 02 21 01 24
// //ans: 00 02 61 01 64
// //req: 02 21 01 24
// //ans: 02 61 01 64
int ID6109FunKWPSendDataToEcuGetAnswer_1_sub_802606E(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int step; // r11 64 02 Argv: FF 01 06 82 40 F1 1A 80 4D
	int Ret; // r0
	unsigned int Count; // r0
	int frame_pos; // r6
	int receive_total_length; // r9
	unsigned __int8 receive_number; // r8
	unsigned __int8 *ans_head; // r10
	unsigned int i; // r11
	int frame_length; // r5
	unsigned int j; // r4
	unsigned int receive_len; // [sp+4h] [bp-44h] BYREF
	unsigned __int8 speci_data[2]; // [sp+Ch] [bp-3Ch] BYREF
	unsigned int v17; // [sp+10h] [bp-38h]
	int m_Maxwaittime; // [sp+14h] [bp-34h]

	v17 = argv[1];
	step = 0;
	receive_len = 0;
	*(_WORD *)speci_data = 0;
	if (!*argv)
		ExitFlag_2000C6BA = 1;                      // 这个字段不知道什么意思
	if (argc >= 0)
	{
		set_time0Stop_sub_802BB48();
		if (ComByte_sub_802F6CC(receive_buff_2000BF20, 0) == 1)
		{
			do
			{
				if (ComByte_sub_802F6CC(receive_buff_2000BF20, 5) != 1)
					break;
				Count = step++;                         // 这里是不是把串口里面残留的数据读出来
			} while (Count < 0x33);
		}
		frame_pos = 2;
		receive_total_length = 0;
		receive_number = 0;
		receive_len = 0;
		ans_head = ans + 2;
		m_Maxwaittime = SC_TagKWP2000_20004974.m_Maxwaittime;
		for (i = 0; i < v17; ++i)
		{
			frame_length = argv[frame_pos];
			for (j = 0; j < frame_length - 1; ++j)
			{
				ComSendByte_sub_802F1E0(argv[j + 1 + frame_pos]);
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			ComSendByte_sub_802F1E0(argv[j + 1 + frame_pos]);
			while (1)
			{
				if (!ReceiveOneKwpFrameFromECU_sub_802E188(
					&receive_buff_2000BF20[1],
					&receive_len,
					SC_TagKWP2000_20004974.m_Maxwaittime,
					speci_data)
					&& !receive_len)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					memset(ans_head, 0, 4);
					*ans = -1;
					ans[1] = 2;
					return 2;
				}
				if (speci_data[0] != 0x7F || speci_data[1] != 0x78)
					break;
				SC_TagKWP2000_20004974.m_Maxwaittime = 5000;
			}
			SC_TagKWP2000_20004974.m_Maxwaittime = m_Maxwaittime;
			receive_buff_2000BF20[0] = receive_len;
			memmove(ans_head, receive_buff_2000BF20, receive_len + 1);
			++receive_number;                         // 这里++ 接收帧数
			ans_head += receive_len + 1;
			frame_pos += frame_length + 1;
			receive_total_length += receive_len + 1;
			if (i != v17 - 1)
				Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		}
		*ans = 0;
		ans[1] = receive_number;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		Ret = receive_total_length + 2;
	}
	else
	{
		memset(ans + 2, 0, 4);
		*ans = -1;
		ans[1] = 2;
		Ret = 2;
	}
	return Ret;
}




// //函数名称:ReceiveOneKwpFrameFromECU
// //函数功能:从ECU获取一帧信息
// //函数的参数:buff接受缓冲区
// //          :size接受的总的长度
// //          :overtime接受时帧与帧之间的间隔，字节与字节之间的间隔
// //          :speci_data.0x7f,0x78所对应的字节内容
// //函数的返回值:true  成功
// //            false 失败
// //与LPC2368相比，这里的函数直接把0x7f,0x78直接
// //在这里实现的是接受一帧kwp指令，在指令中没有关闭和开启链路保持。
int ReceiveOneKwpFrameFromECU_sub_802E188(unsigned __int8 *buff, unsigned int *size, __int16 overtime, _BYTE *speci_data)
{
	int PakType; // r9
	int v10; // r8
	unsigned int l; // r10
	int v12; // r8
	unsigned int k; // r10
	int length; // r8
	unsigned int j; // r10
	int length1; // r8
	unsigned int i; // r10

	*size = 0;
	if (!ComByte_sub_802F6CC(buff, overtime))
		return 0;
	++*size;
	PakType = *buff & 0xC0;
	if (PakType == 0x40)
		return 0;
	if ((unsigned __int8)PakType < 0x80u || (*buff & 0x3F) != 0)
	{
		if ((unsigned __int8)PakType < 0x80u)
		{
			if ((*buff & 0x3F) != 0)                // 02 21 01 cs 这一类
			{
				length1 = *buff;
				for (i = 1; length1 + 1 >= i; ++i)
				{
					if (!ComByte_sub_802F6CC(&buff[i], overtime))
						return 0;
					++*size;
				}
				*speci_data = buff[1];
				speci_data[1] = buff[3];
			}
			else                                      // 00 02 21 sum 这一类的
			{
				length = 0;
				for (j = 1; length + 2 >= j; ++j)
				{
					if (!ComByte_sub_802F6CC(&buff[j], overtime))
						return 0;
					++*size;
					if (j == 1)
						length = buff[1];
				}
				*speci_data = buff[2];
				speci_data[1] = buff[4];
			}
		}
		else                                        // 81 C1 ... sum这一类的
		{
			v12 = *buff & 0x3F;
			for (k = 1; v12 + 3 >= k; ++k)
			{
				if (!ComByte_sub_802F6CC(&buff[k], overtime))
					return 0;
				++*size;
			}
			*speci_data = buff[3];
			speci_data[1] = buff[5];
		}
	}
	else                                          // >=0x80  头是80 C0 ... sum
	{
		v10 = 0;
		for (l = 1; v10 + 4 >= l; ++l)
		{
			if (!ComByte_sub_802F6CC(&buff[l], overtime))
				return 0;
			++*size;
			if (l == 3)
				v10 = buff[3];
		}
		*speci_data = buff[4];
		speci_data[1] = buff[6];
	}
	return 1;
}



// // Funtion: BOSCH发一帧收多帧函数  bosch协议专用
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:BOSCH命令的帧头
// //          argv[1]:BOSCH命令计数器
// //          argv[2]~ argv[argv[0] - 1]:BOSCH命令功能ID
// //          argv[argv[0]]:BOSCH命令结束字节03
// //          argv[argv[0]+1]:判定是否接收多帧，非1表示收多帧，为1表示收单帧
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、并正常接收版本信息数据时，ans的格式为：总帧数 第一帧数据  第二帧数据......第N帧数据
// //                如ans[] = {00,04,0f,01,f6,b0,36,42,39,30,36,30,33,32,41,20,20,03,17,03,f6,32,2e,30,4c,20,32,56,20,45,
// //                           55,32,20,20,20,20,20,20,20,20,20,03,07,05,f6,35,32,31,36,03,08,07,f6,00,00,06,00,00,03}
// // Return : 返回的ans缓冲区的有效数据长度
// // 0x610a
int ID610A_BoschSendDataToEcuGetMultiFrameAnswer_1_sub_8022C14(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int temp; // r7
	int dataLenth; // r8
	unsigned __int8 i; // r9
	unsigned __int8 j; // r9
	unsigned __int8 k; // r9
	unsigned __int8 l; // r9
	unsigned __int8 m; // r9
	SC_PAKSEND PakSend; // [sp+0h] [bp-30h] BYREF
	SC_PAKRECV PakRcv; // [sp+8h] [bp-28h] BYREF

	PakRcv.PakdataAddr = SendPakdataPackData_2000BDF4;
	PakSend.PakdataAddr = receive_buff_2000BF20;
	if (SC_TagKWP1281_200043E4.m_LinkFG == 1)
		SC_TagKWP1281_200043E4.m_chHoldDataLen = 0;
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	temp = *argv + 1;
	*ans = 0;
	ans[1] = 0;
	dataLenth = 2;
	while (Keep_Link_200046C0.rightState != 5)
	{
		if (SC_TagKWP1281_200043E4.m_nMScount >= 2501)
		{
			TimerStop_sub_802EF10(0);
			Keep_Link_200046C0.rightState = 5;
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			return 2;
		}
	}
	if (argv[temp] != 1)
	{
		PakSend.PakLenth = *argv + 1;
		for (i = 0; i < PakSend.PakLenth; ++i)
			PakSend.PakdataAddr[i] = argv[i];
		if (SC_CML_KWP1281_Sendsub_802CB36(&PakSend) && SC_CML_KWP1281_Recv_sub_802CBCC(&PakRcv))
		{
			++ans[1];
			for (j = 0; j < PakRcv.PakLenth; ++j)
				ans[dataLenth++] = PakRcv.PakdataAddr[j];
			PakSend.PakLenth = 4;
			*PakSend.PakdataAddr = 3;
			PakSend.PakdataAddr[1] = 0;
			PakSend.PakdataAddr[2] = 9;
			PakSend.PakdataAddr[3] = 3;
			while (SC_CML_KWP1281_Sendsub_802CB36(&PakSend) && SC_CML_KWP1281_Recv_sub_802CBCC(&PakRcv))
			{
				if (PakRcv.PakdataAddr[2] == 9 || PakRcv.PakdataAddr[2] == 0xF7 || PakRcv.PakLenth < 3)
					goto LABEL_37;
				++ans[1];
				for (k = 0; k < PakRcv.PakLenth; ++k)
					ans[dataLenth++] = PakRcv.PakdataAddr[k];
			}
		}
		goto LABEL_33;
	}
	PakSend.PakLenth = *argv + 1;
	for (l = 0; l < PakSend.PakLenth; ++l)
		PakSend.PakdataAddr[l] = argv[l];
	if (!SC_CML_KWP1281_Sendsub_802CB36(&PakSend) || !SC_CML_KWP1281_Recv_sub_802CBCC(&PakRcv))
	{
	LABEL_33:
		TimerStop_sub_802EF10(0);
		Keep_Link_200046C0.rightState = 5;
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		return 2;
	}
	++ans[1];
	for (m = 0; m < PakRcv.PakLenth; ++m)
		ans[dataLenth++] = PakRcv.PakdataAddr[m];
LABEL_37:
	if (SC_TagKWP1281_200043E4.m_LinkFG == 1)
		SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	return dataLenth;
}



// // Funtion: KWP协议发一帧收多帧
// // Input  : argc - 参数长度
// //          argv - 0xlen,0x内容,最大等待时间
// // Output : ans  - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 610b
// //1.发送给上位机的数据格式是: 0x00 ,0x00, 0xlen 一帧长度 一帧内容 。。。。。。
// //                            -    ----------   ---------------------
// //                            |        |                 |记录的是实际的内容。
// //                            |        |帧数记录。
// //                            |数据标志位，（0xff表示的是设置）。
// //2.argv的缓冲区的数据格式：
// //  发送次数 +  发送帧数 +  + 发送第一帧长度 + 发送第一帧内容
// //3.实现的功能是：发多帧收多帧，并且在发送的过程中是发一帧收一帧。
// //4.在函数中能够对0X7f,0x78进行处理。
// //5.函数例程：
// //req: 82 10 F1 21 03 A7
// //ans: 1n 82 f1 10 61 01 A6
// //ans: 1n 82 f1 10 61 02 A6
// //ans: 1n 82 f1 10 61 02 A6
// //ans:    82 f1 10 61 02 cc
// 
// // 这里只是发送一帧数据 hejm
// // 所以argv的缓冲区的数据格式是：
// // 帧长度 + 帧内容
int ID610B_KWPSendOneAndReceiveMultiFrame_1_sub_8026230(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 receive_number; // r8
	unsigned __int8 v5; // r9
	unsigned int receive_total_length; // r11
	unsigned __int8 *AnsHead; // r5
	unsigned int i; // r6
	__int16 overtime; // r7
	int result; // r0
	unsigned int size; // [sp+0h] [bp-38h] BYREF
	unsigned __int8 speci_data[2]; // [sp+4h] [bp-34h] BYREF
	int v14; // [sp+8h] [bp-30h]

	v14 = *argv;
	receive_number = 0;
	size = 0;
	*(_WORD *)speci_data = 0;
	v5 = 0;
	receive_total_length = 0;
	AnsHead = ans + 2;
	set_time0Stop_sub_802BB48();
	for (i = 0; i < v14 - 1; ++i)
	{
		ComSendByte_sub_802F1E0(argv[i + 1]);
		v5 += argv[i + 1];
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	ComSendByte_sub_802F1E0(v5);
	overtime = 10 * CalculateTimeOut_sub_802CC3E(argv[i + 2], 0xAu);
	while (ReceiveOneKwpFrameFromECU_sub_802E188(AnsHead + 1, &size, overtime, speci_data))
	{
		if (speci_data[0] == 0x7F && speci_data[1] == 120)
		{
			overtime = 5000;
		}
		else
		{
			overtime = 10 * CalculateTimeOut_sub_802CC3E(argv[i + 2], 0xAu);
			*AnsHead = size;
			AnsHead += size + 1;
			++receive_number;                         // 这里应该是接收的帧数++
			receive_total_length += size + 1;
			if (receive_total_length > 0xE10)
			{
				*ans = 0;
				ans[1] = receive_number;
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return receive_total_length + 2;
			}
		}
	}
	if (receive_number)
	{
		*ans = 0;
		ans[1] = receive_number;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = receive_total_length + 2;
	}
	else
	{
		*ans = -1;
		ans[1] = 2;
		result = 2;
	}
	return result;
}



int ID610C_PWM_SendDataToEcuGetAnswer_1_sub_8051266(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 framesize; // r6
	int framepos; // r8
	unsigned __int8 framenum; // r9 MAPDST
	int FrameID; // r11 MAPDST
	int framepos1; // r10
	unsigned __int8 v13; // r6
	unsigned __int8 v15; // r0
	unsigned __int8 Addrress[4]; // [sp+Ch] [bp-34h] BYREF
	unsigned int firstms[12]; // [sp+10h] [bp-30h] BYREF

	firstms[2] = argc;
	if (!*argv)
		ExitFlag_2000C6BA = 2;
	framesize = argv[2];
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	SC_RelayState_200049DC.CommType = 3;
	SC_RelayState_200049DC.LevelType = 12;
	CMPHY_Relay_Reset_sub_8030B88();
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	PWM_Init_sub_8032164();
	framepos = 3;
	framenum = argv[1];
	if (argv[3] == 0x61 && argv[4] == 0x6A)
	{
		FrameID = 0x416BF0;
	}
	else if (argv[3] == 0xC4)
	{
		FrameID = argv[4] + ((argv[5] + 0xC400) << 8);
	}
	else
	{
		FrameID = 0;
	}
	if (framenum == 1)                          // 发1收多
	{
		if (!PWM_Send_sub_803216E(argv + 3, framesize, 1, Addrress))
		{
			Delay_802EF34(1);
			PWM_Send_sub_803216E(argv + 3, framesize, 1, Addrress);
		}
		framenum = 0;
		Addrress[0] = argv[5];
		firstms[0] = 0;
		framenum = PWM_Receive_sub_8032208(ans + 3, 0xC8u, firstms, 0x1F4u, 1, FrameID, Addrress[0]);
		if (firstms[0] < 0x1F4)
		{
			ans[2] = framenum;
			framepos = framenum + 4;
			framenum = 1;
		}
		ans[1] = framenum;
		if (!framenum)
		{
			*ans = -1;
			ans[1] = 2;
			return 2;
		}
	}
	else                                          // 发多收多
	{
		framepos1 = 0;
		ans[1] = framenum;
		while (framenum)
		{
			v13 = argv[framepos1 + 2];
			if (!PWM_Send_sub_803216E(&argv[framepos1 + 3], v13, 1, Addrress))
			{
				Delay_802EF34(1);
				PWM_Send_sub_803216E(&argv[framepos1 + 3], v13, 1, Addrress);
			}
			framepos1 += v13 + 1;
			if (argv[3] == 0x61 && argv[4] == 0x6A)
			{
				FrameID = 0x416BF0;
			}
			else if (argv[3] == 196)
			{
				FrameID = argv[4] + ((argv[5] + 0xC400) << 8);
			}
			else
			{
				FrameID = 0;
			}
			Addrress[0] = argv[5];
			firstms[0] = 0;
			v15 = PWM_Receive_sub_8032208(&ans[framepos], 0xC8u, firstms, 0x1F4u, 1, FrameID, Addrress[0]);
			ans[framepos - 1] = v15;
			framepos += v15 + 1;
			if (!v15)
			{
				*ans = -1;
				ans[1] = 2;
				return 2;
			}
			--framenum;
		}
	}
	*ans = 0;
	return framepos - 1;
}



int ID610EFun_VpwSendOneAndReceiveOneFrame_1sub_8050F60(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 framesize; // r7
	int framepos; // r10
	int framenum; // r11
	unsigned __int8 v9; // r11
	unsigned __int8 v10; // r7
	int v11; // r9
	unsigned __int8 v12; // r7
	unsigned __int8 v13; // r8
	int firstms[10]; // [sp+0h] [bp-28h] BYREF

	if (!*argv)
		ExitFlag_2000C6BA = 2;
	framesize = argv[2];
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	SC_RelayState_200049DC.CommType = 4;
	SC_RelayState_200049DC.LevelType = 0xC;
	CMPHY_Relay_Reset_sub_8030B88();
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	VPW_Init_sub_8051858();
	firstms[0] = 0;
	framepos = 3;
	framenum = argv[1];
	if (framenum == 1)
	{
		if (!VPW_Send_sub_8051862(argv + 3, framesize))
		{
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		v9 = 0;
		v10 = VPW_Receive_sub_8051896(ans + 3, 0xC8, firstms, 0x12C);
		if (v10)
		{
			ans[2] = v10;
			framepos = v10 + 4;
			v9 = 1;
			firstms[0] = 0;
		}
		ans[1] = v9;
		if (!v9)
		{
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
	}
	else
	{
		v11 = 0;
		ans[1] = framenum;
		while ((_BYTE)framenum)
		{
			v12 = argv[v11 + 2];
			if (!VPW_Send_sub_8051862(&argv[v11 + 3], v12))
			{
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			v11 += v12 + 1;
			v13 = VPW_Receive_sub_8051896(&ans[framepos], 0xC8, firstms, 0x12C);
			if (!v13)
			{
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			ans[framepos - 1] = v13;
			framepos += v13 + 1;
			LOBYTE(framenum) = framenum - 1;
			Delay_802EF34(5);
		}
	}
	*ans = 0;
	return framepos - 1;
}




// // Funtion: BOSCH发多帧收多帧函数，在发多帧时，每发一帧，只收一帧  bosch协议专用
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:数据流开关
// //          argv[1]:待发送的数据的总帧数
// //          argv[2]~argv[n]:第一帧命令，第二帧命令......第N帧命令
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、并正常接收版本信息数据时，ans的格式为：总帧数 第一帧数据  第二帧数据......第N帧数据
// //                如ans[] = {00,04,0f,01,f6,b0,36,42,39,30,36,30,33,32,41,20,20,03,17,03,f6,32,2e,30,4c,20,32,56,20,45,
// //                           55,32,20,20,20,20,20,20,20,20,20,03,07,05,f6,35,32,31,36,03,08,07,f6,00,00,06,00,00,03}
// // Return : 返回的ans缓冲区的有效数据长度
// // info:0x610f 
int ID610F_BoschSendDataToEcuGetAnswer_1_sub_8022AB4(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int frameLen; // r7
	int argvPos; // r9
	int dataLenth; // r10
	unsigned __int8 i; // r8
	unsigned __int8 j; // r8
	SC_PAKSEND PackSend; // [sp+0h] [bp-30h] BYREF
	SC_PAKRECV PackRcv; // [sp+8h] [bp-28h] BYREF

	PackSend.PakLenth = argc;
	PackRcv.PakLenth = (unsigned int)ans;
	PackRcv.PakdataAddr = receive_buff_2000BF20;
	PackSend.PakdataAddr = SendPakdataPackData_2000BDF4;
	if (SC_TagKWP1281_200043E4.m_LinkFG == 1)
		SC_TagKWP1281_200043E4.m_chHoldDataLen = 0;
	if (!*argv)
		ExitFlag_2000C6BA = 2;
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	frameLen = argv[1];
	*ans = 0;
	argvPos = 2;
	ans[1] = frameLen;
	dataLenth = 2;
	while (Keep_Link_200046C0.rightState != 5)
	{
		if (SC_TagKWP1281_200043E4.m_nMScount >= 0x9C5)
		{
			TimerStop_sub_802EF10(0);
			Keep_Link_200046C0.rightState = 5;
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			return 2;
		}
	}
	while ((_BYTE)frameLen--)
	{
		PackSend.PakLenth = argv[argvPos] + 1;
		for (i = 0; i < PackSend.PakLenth; ++i)
			PackSend.PakdataAddr[i] = argv[argvPos++];
		if (!SC_CML_KWP1281_Sendsub_802CB36(&PackSend)
			|| !SC_CML_KWP1281_Recv_sub_802CBCC(&PackRcv))
		{
			TimerStop_sub_802EF10(0);
			Keep_Link_200046C0.rightState = 5;
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			return 2;
		}
		for (j = 0; j < PackRcv.PakLenth; ++j)
			ans[dataLenth++] = PackRcv.PakdataAddr[j];
	}
	Delay_802EF34(0x32);
	if (SC_TagKWP1281_200043E4.m_LinkFG == 1)
		SC_TagKWP1281_200043E4.m_chHoldDataLen = 4;
	return dataLenth;
}



// //函数名称:int ISO_SendDataToEcuGetAnswer()
// // Input  : argc - 参数长度
// //          argv - 0xlen,0x内容,最大等待时间
// // Output : ans  - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6110
// //1.发送给上位机的数据格式是: 0x00 ,0x00, 0xlen 一帧长度 一帧内容.......
// //                            -    ----------   ---------------------
// //                            |        |                 |记录的是实际的内容。
// //                            |        |帧数记录。
// //                            |数据标志位，（0xff表示的是设置）。
// //2.argv的缓冲区的数据格式：
// //  发送的次数 + 帧数 + 每帧的长度 + 每帧的内容 +长度　+ 内容
// //3.实现的功能:ISO_9141协议的接受和发送。
// //             主要实现的是：发多帧收多帧,对于发送的每一帧都有一帧的应答。
// //4,协议举例:
// //   req:68 6a f1 be 81
// //   ans:48 6b c0 fe 00 01 72
// //5.注意函数实现的功能和函数：IsoInitSendDataToEcuGetAnswer,IsoInitSendDataToEcuGetAnswer,
// //  IsoAddSendDataToEcuGetAnswer.组合使用的方式是一样的。
int ID6110_ISO_SendDataToEcuGetAnswer_1_sub_80270FE(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 receive_number; // r7
	int receive_total_length; // r8
	__int16 time; // r9
	int send_length_pos; // r5
	unsigned __int8 *ans_head; // r10
	int Ret; // r0
	unsigned int i; // r4
	unsigned int j; // r11
	int receive_len; // r11
	unsigned int v13; // [sp+8h] [bp-38h]
	unsigned int send_length; // [sp+Ch] [bp-34h]
	unsigned int timecnt; // [sp+10h] [bp-30h]

	receive_number = 0;
	receive_total_length = 0;
	time = 500;
	if (!*argv)
		ExitFlag_2000C6BA = 1;
	v13 = argv[1];
	send_length_pos = 2;
	ans_head = ans + 2;
	if (argc >= 0 && argv[1])
	{
		timecnt = Keep_Link_200046C0.IdleTime / SC_TagKWP2000_20004974.m_MsTime;
		set_time0Stop_sub_802BB48();
		for (i = 0; i < v13; ++i)
		{
			send_length = argv[send_length_pos];
			for (j = 0; j < send_length; ++j)
			{
				ComSendByte_sub_802F1E0(argv[j + 1 + send_length_pos]);
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			for (receive_len = 0; ; receive_len = 0)
			{
				while (ComByte_sub_802F6CC(&receive_buff_2000BF20[receive_len + 1], time))
				{
					++receive_len;
					time = 50;
					if (receive_len == 7
						&& receive_buff_2000BF20[4] == 0x7F
						&& (receive_buff_2000BF20[6] == 0x78 || receive_buff_2000BF20[6] == 0x23))
					{
						receive_len = 0;
						time = 5000;
					}
				}
				if (!receive_len)
				{
					Keep_Link_200046C0.timeCount = timecnt;
					*ans = -1;
					ans[1] = 2;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 2;
				}
				if (receive_buff_2000BF20[4] != 0x7F || receive_buff_2000BF20[6] != 0x78)
					break;
				time = 5000;
			}
			receive_buff_2000BF20[0] = receive_len;
			++receive_number;
			memmove(ans_head, receive_buff_2000BF20, receive_len + 1);
			ans_head += receive_len + 1;
			send_length_pos += send_length + 1;
			receive_total_length += receive_len + 1;
			if (i != v13 - 1)
				Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		}
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0;
		ans[1] = receive_number;
		Ret = receive_total_length + 2;
	}
	else
	{
		memset(ans_head, 0, 4);
		*ans = -1;
		ans[1] = 2;
		Ret = 2;
	}
	return Ret;
}


// // Funtion: send one frame to ecu and receive multiframe know nothing of frame
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:发往ECU的一帧数据的长度: len
// //          argv[1] ~ argv[len]:发往ECU的一帧数据
// //     后面的三个字节有合起来有三种情况
// //     case 1:
// //          argv[len + 1]: 非0表示从ECU接受一帧数据的长度
// //     case 2:
// //          argv[len + 1]为0，argv[len + 2]为0表示接受数据直到碰到指定的字节argv[len + 3]后，再接收一个字节。
// //     case 3:
// //          argv[len + 1]为0，argv[len + 2]非0表示以特定的规则从ECU接收数据，这个规则的关键字为argv[len + 3]
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 帧长度 帧数据
// //                如ans[] = {00,01,0f,01,f6,b0,36,42,39,30,36,30,33,32,41,20,20,03}
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6111
int ID6111_SendOneFrameDataToEcuGetAnyFrameAnswer_1_sub_8027594(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int len; // r7
	int i; // r9 MAPDST
	unsigned int v8; // r0
	int v10; // r9
	unsigned __int8 v11; // r0
	int ansLen; // r8
	int v13; // r0 MAPDST
	int v14; // r9
	unsigned __int8 kw1; // r10
	int v17; // r11
	int v18; // r10
	int v20; // r11
	unsigned __int8 rcvbyte[40]; // [sp+0h] [bp-28h] BYREF

	set_time0Stop_sub_802BB48();
	if (CheckIoBusy_sub_802DF38(0x80, 5, 1) == 1 && CheckIoBusy_sub_802DF38(0x80, 8, 1) == 1)
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
	LABEL_5:
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		return 2;
	}
	len = *argv;
	if (!*argv)
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		goto LABEL_5;
	}
	for (i = 1; ; ++i)
	{
		v8 = len--;
		if (v8 < 2)
			break;
		ComSendByte_sub_802F1E0(argv[i]);
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	v10 = i + 1;
	v11 = argv[i];
	argv[i] = v11 + 1;
	ComSendByte_sub_802F1E0(v11);
	*ans = 0;
	ans[1] = 1;
	ans[2] = 0;
	ansLen = 3;
	v13 = argv[v10];
	v14 = v10 + 1;
	if (v13)
	{
		ans[2] = v13;
		while (v13--)
		{
			if (!ComByte_sub_802F6CC(rcvbyte, 2000))
				goto LABEL_33;
			ans[ansLen++] = rcvbyte[0];
		}
		goto LABEL_35;
	}
	if (argv[v14])
	{
		v17 = argv[v14];
		v18 = argv[v14 + 1];
		while ((_BYTE)v17--)
		{
			if (!ComByte_sub_802F6CC(rcvbyte, 2000))
				goto LABEL_33;
			ans[ansLen++] = rcvbyte[0];
			++ans[2];
		}
		v20 = rcvbyte[0] - v18 - ans[2];
		while ((_BYTE)v20--)
		{
			if (!ComByte_sub_802F6CC(rcvbyte, 2000))
				goto LABEL_33;
			ans[ansLen++] = rcvbyte[0];
			++ans[2];
		}
	LABEL_35:
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		return ansLen;
	}
	kw1 = argv[v14 + 1];
	while (ComByte_sub_802F6CC(rcvbyte, 2000))
	{
		ans[ansLen++] = rcvbyte[0];
		++ans[2];
		if (rcvbyte[0] == kw1)
		{
			if (!ComByte_sub_802F6CC(rcvbyte, 2000))
				break;
			ans[ansLen++] = rcvbyte[0];
			++ans[2];
			goto LABEL_35;
		}
	}
LABEL_33:
	PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
	return 2;
}


// // Funtion: PWM协议发一收多
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6112 07,c4,10,f5,22,02,00,5b,03,2d,
int ID6112Fun_PwmSendOneAndReceiveMultiFrame_1_sub_8051460(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int framesize; // r7
	unsigned __int8 v6; // r10
	int FramePos; // r9
	int FrameID; // r11
	unsigned __int8 Framenum; // r8
	unsigned __int8 FrameSize; // r7
	int result; // r0
	unsigned __int8 Addrress[4]; // [sp+Ch] [bp-2Ch] BYREF
	unsigned int firstms; // [sp+10h] [bp-28h] BYREF

	framesize = *argv;
	v6 = argv[framesize + 1];
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	SC_RelayState_200049DC.CommType = 3;
	SC_RelayState_200049DC.LevelType = 12;
	CMPHY_Relay_Reset_sub_8030B88();
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	PWM_Init_sub_8032164();
	firstms = 0;
	FramePos = 3;
	if (argv[1] == 0x61 && argv[2] == 0x6A)
	{
		FrameID = 0x416BF0;
	}
	else if (argv[1] == 0xC4)
	{
		FrameID = argv[2] + ((argv[3] + 0xC400) << 8);
	}
	else
	{
		FrameID = 0;
	}
	if (!PWM_Send_sub_803216E(argv + 1, framesize, 1, Addrress))
	{
		Delay_802EF34(1);
		PWM_Send_sub_803216E(argv + 1, framesize, 1, Addrress);
	}
	Framenum = 0;
	Addrress[0] = argv[3];
	firstms = 0;
	while (Framenum < (unsigned int)v6)
	{
		FrameSize = PWM_Receive_sub_8032208(&ans[FramePos], 0xC8u, &firstms, 0x1F4u, 1, FrameID, Addrress[0]);
		if (firstms >= 0x1F4)
			break;
		ans[FramePos - 1] = FrameSize;
		FramePos += FrameSize + 1;
		++Framenum;
	}
	ans[1] = Framenum;
	if (Framenum)
	{
		*ans = 0;
		result = FramePos - 1;
	}
	else
	{
		*ans = -1;
		ans[1] = 2;
		result = 2;
	}
	return result;
}



// // Funtion:
// // Input  : argc - 参数长度
// //          argv - 数据格式
// //         (0x61 + 0x13 ) + 发送次数 + 帧数 + 发送长度 + 发送内容 .
// //         在链路层中发送次数和帧数默认的设置的是1
// // 实例   : 0x61 0x13 0x01 0x01 0x11 0x55 0xaa 0x0b 0X61 0X03 0x08 0xID1 0XID2 0X03
// //          0X21 0X01 0X02 0X00 0X00 0X00 0X00 0XXX
// // Output : ans - 这个函数只是进行数据的发送
// // Return : 0xff
// // Info   : 6113
// // 在使用这个函数的时候要注意的是：
// // 1.接受时间的确认。
// // 2.发送的帧数和发送的次数在链路层默认的是1.
int ID6113_CanbusOnlySendDataToEcu_1_sub_8028506(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 ii; // r10
	int send_length; // r7
	int result; // r0

	ii = 3;
	send_length = argv[2];
	if (*argv && argv[1] && argv[2])
	{
		set_time0Stop_sub_802BB48();
		while (send_length--)
		{
			ComSendByte_sub_802F1E0(argv[ii++]);
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 0;
		result = 2;
	}
	else
	{
		*ans = -1;
		ans[1] = 2;
		result = 2;
	}
	return result;
}



// // Input  : argc - 参数长度
// //          argv - 0xlen,0x内容,最大等待时间
// // Output : ans  - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6116
// //1.发送给上位机的数据格式是: 0x00 ,0x00, 0xlen 一帧长度 一帧内容.......
// //                            -    ----------   ---------------------
// //                            |        |                 |记录的是实际的内容。
// //                            |        |帧数记录。
// //                            |数据标志位，（0xff表示的是设置）。
// //2.argv的缓冲区的数据格式：
// //   长度 + 内容 　+ 接受的最大等待时间
// //3.实现的功能:ISO_9141协议的接受和发送。
// //             主要实现的是:发送一帧内容收多帧的情况
// //4,协议举例:
// //   req:68 6a f1 be 81
// //   ans:48 6b c0 fe 00 01 72
int ID6116FunFordIsoSendOneAndReceiveMultiFrame_1_sub_80277DC(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int16 SingleFrameCount; // r7
	unsigned int receive_total_length; // r9
	unsigned __int8 *ans_head; // r11
	__int16 time; // r10
	int result; // r0
	unsigned int i; // r4
	int receive_number; // r6
	unsigned int ii; // r4
	int send_length; // [sp+4h] [bp-34h]

	SingleFrameCount = 0;
	receive_total_length = 0;
	ans_head = ans + 2;
	send_length = *argv;
	time = 0xA * CalculateTimeOut_sub_802CC3E(argv[send_length + 1], 0xAu);
	if (argc >= 0)
	{
		set_time0Stop_sub_802BB48();
		for (i = 0; i < send_length - 1; ++i)
		{
			ComSendByte_sub_802F1E0(argv[i + 1]);
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(argv[i + 1]);
	LABEL_7:
		if (ComByte_sub_802F6CC(&receive_buff_2000BF20[1], time))
		{
			if (receive_total_length <= 0xE10)
			{
				receive_number = (receive_buff_2000BF20[1] >> 4) + 1;
				ii = 2u;
				receive_buff_2000BF20[0] = (receive_buff_2000BF20[1] >> 4) + 1;
				while (1)
				{
					if (!--receive_number)
					{
						++SingleFrameCount;
						memmove(ans_head, receive_buff_2000BF20, receive_buff_2000BF20[0] + 1);
						ans_head += receive_buff_2000BF20[0] + 1;
						receive_total_length += receive_buff_2000BF20[0];
						goto LABEL_7;
					}
					if (!ComByte_sub_802F6CC(&receive_buff_2000BF20[ii], time))
						break;
					++ii;
				}
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				result = 2;
			}
			else
			{
				*ans = 0;
				ans[1] = SingleFrameCount;
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				result = SingleFrameCount + receive_total_length + 2;
			}
		}
		else if (SingleFrameCount)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0;
			ans[1] = SingleFrameCount;
			result = SingleFrameCount + receive_total_length + 2;
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0xFF;
			ans[1] = 2;
			result = 2;
		}
	}
	else
	{
		memset(ans_head, 0, 4);
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}




// // Funtion: send one frame to ecu and receive multiframe know nothing of frame
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:数据流标志
// //          argv[1]:发送帧数
// //          argv[2]:接收帧数
// //          argv[3]:检测 08 55 a3开关, 如果为0，则检测
// //     根据帧数后面字节循环依次为：headid : 检验从ECU所收数据的帧头是否匹配
// //                                 busidletime: 检测总线空闲最大等待时间
// //                                 framelen；发送的一帧数据的长度len
// //                                 framedata:长度为len的一帧数据
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 帧长度 帧数据
// // Return : 返回的ans缓冲区的有效数据长度
int ID6117Fun_HoldenNormalRingLinkSendOneAndOneFrame_1_sub_8027970(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v5; // r9
	int sendnum; // r6
	int ansLen; // r7
	int argvPos; // r11 MAPDST
	int framelen; // r10
	int i; // r11
	unsigned __int8 tFrameLen; // r0
	int v15; // r10
	unsigned int j; // r8
	unsigned __int8 rcvbyte; // [sp+0h] [bp-38h] BYREF
	unsigned __int8 busidletime; // [sp+1h] [bp-37h]
	unsigned __int8 checkid_sw; // [sp+2h] [bp-36h]
	unsigned __int8 rcvnum; // [sp+3h] [bp-35h]
	unsigned __int8 *PRcv; // [sp+4h] [bp-34h]
	unsigned __int8 headid; // [sp+8h] [bp-30h]

	v5 = 0;
	PRcv = receive_buff_2000BF20;
	set_time0Stop_sub_802BB48();
	Delay_802EF34(0xA);
	if (!*argv)
		ExitFlag_2000C6BA = 1;
	sendnum = argv[1];                            // 发送帧数
	rcvnum = argv[2];                             // // 接收帧数
	checkid_sw = argv[3];                         // // 检测 08 55 a3开关, 如果为0，则检测
	*ans = 0;
	ans[1] = 0;
	ansLen = 2;
	argvPos = 4;
	do
	{
		if (!checkid_sw)
		{
			while (ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
			{
				if (rcvbyte == 8)
				{
					if (!ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
						goto LABEL_38;
					if (rcvbyte == 0x55)
					{
						if (!ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
							goto LABEL_38;
						if (rcvbyte == 0xA3)
							goto LABEL_13;
					}
				}
			}
			goto LABEL_38;
		}
	LABEL_13:
		headid = argv[argvPos];
		busidletime = argv[++argvPos];
		++argvPos;
		if (checkid_sw)
		{
			if (CheckIoBusy_sub_802DF38(0x80, busidletime, 1) == 1)
			{
				argvPos -= 2;
				goto LABEL_45;
			}
		}
		else
		{
			Delay_802EF34(busidletime);
		}
		framelen = argv[argvPos];
		for (i = argvPos + 1; ; ++i)
		{
			tFrameLen = framelen--;
			if (tFrameLen < 2u)
				break;
			ComSendByte_sub_802F1E0(argv[i]);
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(argv[i]);
		argvPos = i + 1;
		if (rcvnum--)
		{
			if (ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
			{
				if (rcvbyte == headid)
				{
					*PRcv = rcvbyte;
					if (ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
					{
						PRcv[1] = rcvbyte;
						v5 = 2;
						v15 = rcvbyte - 0x54;
						while (1)
						{
							if (!(_BYTE)v15--)
							{
								Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
								goto LABEL_41;
							}
							if (!ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
								break;
							PRcv[v5++] = rcvbyte;
						}
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
					}
					else if (timer_open_flag_2000C6B7 == 1)
					{
						TIM_sub_802EEEC(0);
					}
				}
				else if (timer_open_flag_2000C6B7 == 1)
				{
					TIM_sub_802EEEC(0);
				}
			}
			else if (timer_open_flag_2000C6B7 == 1)
			{
				TIM_sub_802EEEC(0);
			}
		LABEL_38:
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			return 2;
		}
	LABEL_41:
		++ans[1];
		ans[ansLen++] = v5;
		for (j = 0; j < v5; ++j)
			ans[ansLen++] = PRcv[j];
		v5 = 0;
	LABEL_45:
		--sendnum;
	} while ((_BYTE)sendnum);
	return ansLen;
}



// // Funtion:  6118+00/FF+FID（过滤的帧头ID）+CS说明：该模块属于只收模式的一种类型，上位机告诉要
// //                接受的以什么字节开头的数据帧; 数据第二个字节-54H是接收数据的长度。
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:数据流标志
// //          argv[1]:fid 指定所接受的数据帧以什么字节开头的
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 帧长度 帧数据
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6118
int ID6118FunHoldenOnlyKnowHeadOfFrame_1__sub_8027C20(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 fid; // r5
	int result; // r0
	unsigned int try_count; // r11
	unsigned __int8 temp; // r6
	unsigned __int8 framelen; // r8
	unsigned int i; // r9
	unsigned int v10; // r0
	int ansLen; // r10
	int len; // r7
	unsigned __int8 rcvbyte[4]; // [sp+0h] [bp-230h] BYREF
	unsigned __int8 tempbuff[512]; // [sp+4h] [bp-22Ch] BYREF

	memset(tempbuff,0, 0x200u);
	set_time0Stop_sub_802BB48();
	if (!*argv)
		ExitFlag_2000C6BA = 1;
	fid = argv[1];
	if (fid)
	{
		do
		{
			do
			{
				do
				{
					if (!ComByte_sub_802F6CC(rcvbyte, 0x3E8))
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						goto LABEL_59;
					}
				} while (rcvbyte[0] != 8);
				if (!ComByte_sub_802F6CC(rcvbyte, 0x12C))
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					goto LABEL_59;
				}
			} while (rcvbyte[0] != 0x55);
			if (!ComByte_sub_802F6CC(rcvbyte, 0x12C))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				goto LABEL_59;
			}
		} while (rcvbyte[0] != 0xA3);
		try_count = 0;
		while (1)
		{
			if (!ComByte_sub_802F6CC(rcvbyte, 0x3E8))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				goto LABEL_59;
			}
			temp = rcvbyte[0];
			tempbuff[0] = rcvbyte[0];
			if (rcvbyte[0] != fid)
				break;
		LABEL_49:
			if (temp == fid)
			{
				*ans = 0;
				ans[1] = 1;
				ans[3] = rcvbyte[0];
				++ans[2];
				if (ComByte_sub_802F6CC(rcvbyte, 0x1F4))
				{
					ans[4] = rcvbyte[0];
					ansLen = 5;
					++ans[2];
					len = rcvbyte[0] - 0x54;
					while (1)
					{
						if (!(_BYTE)len--)
							return ansLen;
						if (!ComByte_sub_802F6CC(rcvbyte, 0x1F4))
							break;
						ans[ansLen++] = rcvbyte[0];
						++ans[2];
					}
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
				}
				else if (timer_open_flag_2000C6B7 == 1)
				{
					TIM_sub_802EEEC(0);
				}
				goto LABEL_59;
			}
		}
		if (ComByte_sub_802F6CC(rcvbyte, 0x12C))
		{
			tempbuff[1] = rcvbyte[0];
			framelen = rcvbyte[0] - 0x54;
			for (i = 0; i < framelen; ++i)
			{
				if (!ComByte_sub_802F6CC(rcvbyte, 0x12C))
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					goto LABEL_59;
				}
				if (i < 3)
					tempbuff[i + 2] = rcvbyte[0];
			}
			if (tempbuff[0] != 8)
				goto LABEL_49;
			if (tempbuff[1] != 0x55)
				goto LABEL_49;
			if (tempbuff[2] != 0xAA)
				goto LABEL_49;
			v10 = try_count++;
			if (v10 < 2)
				goto LABEL_49;
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
		}
		else if (timer_open_flag_2000C6B7 == 1)
		{
			TIM_sub_802EEEC(0);
		}
	LABEL_59:
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		result = 2;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}




// // Funtion:  6119 针对SUBRU老协议的链路，其格式和6105的格式相同，其受数据的高电平的时间为12。
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:数据流开关标志
// //          argv[1]:指定从ECU接收数据的帧数
// //          argv[2]:发送往ECU的有效数据的长度
// //          argv[3]~argv[len + 2]:发送往ECU的有效数据
// //     后面的字节情况:
// //          case1: argv[len + 3]非0:表示从ECU接收固定长度的数据
// //          case2: argv[len + 3]为0，argv[len + 4]非0:argv[len + 4]和argv[len + 5]都为一种特殊接收数据的方式的关键字
// //          case3: argv[len + 3]为0，argv[len + 4]为0，另外一种特殊接收数据的方式
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 帧长度 帧数据
// // Return : 返回的ans缓冲区的有效数据长度
int ID6119_SubruOldProtocol_1_sub_8027EF8(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int framenum; // r6
	unsigned int len; // r10
	int argvPos; // r7 MAPDST
	int ansLen; // r9
	int temp; // r0 MAPDST
	int v12; // r8
	int v14; // r8
	unsigned __int8 len_1; // r10
	int v16; // r11
	char v17; // r10
	int v18; // r9
	unsigned __int8 rcvbyte; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 v20; // [sp+1h] [bp-2Fh]

	argvPos = 0;
	set_time0Stop_sub_802BB48();
	if (CheckIoBusy_sub_802DF38(0x1F4, 8, 1) == 1)
		goto LABEL_2;
	if (!*argv)
		ExitFlag_2000C6BA = 2;
	framenum = argv[1];
	if (!(_BYTE)framenum)
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
	LABEL_2:
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		return 2;
	}
	len = argv[2];
	if (!argv[2])
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		goto LABEL_2;
	}
	argvPos = 3;
	do
	{
		ComSendByte_sub_802F1E0(argv[argvPos++]);
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		--len;
	} while (len >= 2);
	ComSendByte_sub_802F1E0(argv[argvPos++]);
	*ans = 0;
	ans[1] = framenum;
	ansLen = 2;
LABEL_16:
	if (CheckIoBusy_sub_802DF38(0x1F4, 0xB, 1) != 1)
	{
		temp = argv[argvPos++];
		v12 = temp;
		if (temp)
		{
			ans[ansLen++] = temp;
			while (ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
			{
				ans[ansLen++] = rcvbyte;
				if (!--v12)
					goto LABEL_38;
			}
		}
		else
		{
			temp = argv[argvPos++];
			v14 = temp;
			if (temp)
			{
				argvPos = ansLen++;
				len_1 = 0;
				v20 = argv[argvPos++];
				while (ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
				{
					ans[ansLen++] = rcvbyte;
					++len_1;
					if (!--v14)
					{
						rcvbyte -= v20;
						rcvbyte -= len_1;
						v16 = rcvbyte;
						while (ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
						{
							ans[ansLen++] = rcvbyte;
							++len_1;
							if (!(_BYTE)--v16)
							{
								ans[argvPos] = len_1;
								goto LABEL_38;
							}
						}
						break;
					}
				}
			}
			else
			{
				v17 = 0;
				argvPos = ansLen;
				v18 = ansLen + 1;
				while (ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
				{
					ans[v18++] = rcvbyte;
					++v17;
					if (!rcvbyte)
					{
						if (!ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
							break;
						ans[v18] = rcvbyte;
						ansLen = v18 + 1;
						ans[argvPos] = v17 + 1;
					LABEL_38:
						if (!(_BYTE)--framenum)
						{
							Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							return ansLen;
						}
						goto LABEL_16;
					}
				}
			}
		}
	}
	PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
	return 2;
}



int ID611A_sub_8028184(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int result; // r0
	int FrameNum; // r6
	unsigned __int8 v7; // r7
	unsigned __int8 argvPos; // r10 MAPDST
	unsigned __int8 v9; // r11
	int FrameLenth; // r8
	int v12; // r10
	int v13; // r9
	unsigned __int8 rcvbyte; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 delayTime; // [sp+1h] [bp-2Fh]

	set_time0Stop_sub_802BB48();
	if (CheckIoBusy_sub_802DF38(500, 8, 1) == 1 || (FrameNum = argv[1], !(_BYTE)FrameNum))
	{
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	else
	{
		delayTime = argv[2];
		v7 = argv[3];
		argvPos = 4;
		*ans = 0;
		ans[1] = FrameNum;
		v9 = 2;
		while (1)
		{
			FrameLenth = argv[argvPos++];
			do
			{
				ComSendByte_sub_802F1E0(argv[argvPos++]);
				Delay_802EF34(v7);
				--FrameLenth;
			} while ((unsigned __int8)FrameLenth >= 2u);
			ComSendByte_sub_802F1E0(argv[argvPos]);
			v12 = (unsigned __int8)(argvPos + 1);
			LOBYTE(v13) = argv[v12];
			argvPos = v12 + 1;
			v13 = (unsigned __int8)v13;
			if ((_BYTE)v13)
				break;
			ans[v9++] = 0;
		LABEL_15:
			Delay_802EF34(delayTime);
			if (!(_BYTE)--FrameNum)
				return v9;
		}
		if (CheckIoBusy_sub_802DF38(500, 11, 1) != 1)
		{
			ans[v9++] = v13;
			while (ComByte_sub_802F6CC(&rcvbyte, 500))
			{
				ans[v9++] = rcvbyte;
				if (!(_BYTE)--v13)
					goto LABEL_15;
			}
		}
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		result = 2;
	}
	return result;
}




// // Funtion: VPW_Holden专用_发多帧收多帧
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : recv: 611B,05,c4,10,f5,13,c7,50
// //          send:
// //         改函数带有ID过滤功能。由于接收解码程序由中断程序完成，所以过滤处理
// //         必须在接收完成后，再将不符合要求的数据过滤掉，接收过程只统计有效帧
// //         数，过滤后帧数与统计有效帧数对比，必须相等，否则出错。
int ID611B_Fun_VPW_HDN_SendDataToEcuGetMultiFrameAnswer_1_sub_805166C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int result; // r0
	int frameSize; // r0
	int firstms; // [sp+0h] [bp-20h] BYREF

	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	SC_RelayState_200049DC.CommType = 3;
	SC_RelayState_200049DC.LevelType = 0xC;
	CMPHY_Relay_Reset_sub_8030B88();
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	VPW_Init_sub_8051858();
	if (VPW_Send_sub_8051862(argv + 1, *argv))
	{
		frameSize = VPW_Receive_sub_8051896(ans + 3, 0xC8, &firstms, 0x78);
		if (frameSize)
		{
			*ans = 0;
			ans[1] = 1;
			ans[2] = frameSize;
			result = frameSize + 3;
		}
		else
		{
			*ans = 0xFF;
			ans[1] = 2;
			result = 2;
		}
	}
	else
	{
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}




// // Funtion:  OPEL/SAAB 发一帧收多帧.
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:数据流开关标志
// //          argv[1]:检测总线是否空闲的时间参数
// //          argv[2]:发送往ECU的有效数据的长度 len
// //          argv[3]~argv[len + 2]:发送往ECU的有效数据
// //     后面的字节情况:
// //          case1: argv[len + 3]非0:表示从ECU接收固定长度的数据
// //          case2: argv[len + 3]为0，argv[len + 4]非0:argv[len + 4]和argv[len + 5]都为一种特殊接收数据的方式的关键字
// //          case3: argv[len + 3]为0，argv[len + 4]为0，另外一种特殊接收数据的方式
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 帧长度 帧数据
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 611c   注意，本函数也要求在PC有新指令下来之前，下位机必须与ECU反复通讯。此功能还未能实现
int ID611C_Fun_SendOneFrameDataToEcuGetAnyFrameAnswer_Check_1_sub_80282D0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int len; // r10 MAPDST
	int i; // r8 MAPDST
	int ansLen; // r9
	int temp; // r0 MAPDST
	int argvPos; // r8
	int v16; // r11
	unsigned __int8 len_1; // r10
	int R0; // r6
	char v19; // r10
	unsigned __int8 rcvbyte; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 busytime; // [sp+1h] [bp-2Fh]
	unsigned __int8 B; // [sp+2h] [bp-2Eh]

	set_time0Stop_sub_802BB48();
	busytime = argv[1];
	if (CheckIoBusy_sub_802DF38(1000, busytime, 1) == 1)
		goto LABEL_2;
	len = argv[2];
	if (!argv[2])
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
	LABEL_2:
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		return 2;
	}
	for (i = 3; (unsigned int)--len >= 2; ++i)
	{
		ComSendByte_sub_802F1E0(argv[i]);
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	ComSendByte_sub_802F1E0(argv[i++]);
	*ans = 0;
	ans[1] = 1;
	ansLen = 3;
	temp = argv[i++];
	if (temp)
	{
		ans[2] = temp;                              // 上位机接收的长度
		while (ComByte_sub_802F6CC(&rcvbyte, 500))
		{
			ans[ansLen++] = rcvbyte;
			if (!--temp)
				goto LABEL_31;
		}
	}
	else                                          // 自动判断长度
	{
		temp = argv[i];
		argvPos = i + 1;
		v16 = temp;
		if (temp)
		{
			len_1 = 0;
			B = argv[argvPos];
			while (ComByte_sub_802F6CC(&rcvbyte, 500))
			{
				ans[ansLen++] = rcvbyte;
				++len_1;
				if (!--v16)
				{
					rcvbyte -= B;
					rcvbyte -= len_1;
					R0 = rcvbyte;
					while (ComByte_sub_802F6CC(&rcvbyte, 500))
					{
						ans[ansLen++] = rcvbyte;
						++len_1;
						if (!(_BYTE)--R0)
						{
							ans[2] = len_1;
							goto LABEL_31;
						}
					}
					break;
				}
			}
		}
		else
		{
			v19 = 0;
			while (ComByte_sub_802F6CC(&rcvbyte, 500))
			{
				ans[ansLen++] = rcvbyte;
				++v19;
				if (!rcvbyte)
				{
					if (!ComByte_sub_802F6CC(&rcvbyte, 500))
						break;
					ans[ansLen++] = rcvbyte;
					ans[2] = v19 + 1;
				LABEL_31:
					Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
					return ansLen;
				}
			}
		}
	}
	PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
	return 2;
}



// // Funtion: VPW_Holden专用_发多帧收多帧
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : recv: 611B,05,c4,10,f5,13,c7,50
// //          send:
// //         改函数带有ID过滤功能。由于接收解码程序由中断程序完成，所以过滤处理
// //         必须在接收完成后，再将不符合要求的数据过滤掉，接收过程只统计有效帧
// //         数，过滤后帧数与统计有效帧数对比，必须相等，否则出错。
int ID611D_VPW_HDN_SendDataToEcuGetMultiFrameAnswer_1_sub_80516EA(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 send_framesize; // r7
	int ansPos; // r10
	int v7; // r11
	unsigned __int8 FrameNum; // r11
	unsigned __int8 framesize; // r7
	int v11; // r9
	unsigned __int8 send_framesize_1; // r7
	unsigned __int8 framesize_1; // r8
	int firstms; // [sp+0h] [bp-38h] BYREF
	CMPHY_Relay Relaybuf; // [sp+4h] [bp-34h] BYREF

	if (!*argv)
		ExitFlag_2000C6BA = 2;
	send_framesize = argv[2];
	CMPHY_Relay_Init_sub_8030B62(&Relaybuf);
	Relaybuf.CommType = 4;
	Relaybuf.LevelType = 0xC;
	CMPHY_Relay_Reset_sub_8030B88();
	CMPHY_Relay_Set_sub_8030B94(&Relaybuf);
	VPW_Init_sub_8051858();
	firstms = 0;
	ansPos = 3;
	v7 = argv[1];
	if (v7 == 1)
	{
		if (!VPW_Send_sub_8051862(argv + 3, send_framesize))
		{
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		FrameNum = 0;
		while ((unsigned int)firstms < 0xC8 && FrameNum < 0x14u)
		{
			framesize = VPW_Receive_sub_8051896(&ans[ansPos], 0xC8, &firstms, 0xC8);
			if (framesize)
			{
				ans[ansPos - 1] = framesize;
				ansPos += framesize + 1;
				++FrameNum;
				firstms = 0;
			}
		}
		ans[1] = FrameNum;
		if (!FrameNum)
		{
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
	}
	else
	{
		v11 = 0;
		ans[1] = v7;
		while ((_BYTE)v7)
		{
			send_framesize_1 = argv[v11 + 2];
			if (!VPW_Send_sub_8051862(&argv[v11 + 3], send_framesize_1))
			{
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			v11 += send_framesize_1 + 1;
			framesize_1 = VPW_Receive_sub_8051896(&ans[ansPos], 0xC8, &firstms, 0xC8);
			if (!framesize_1)
			{
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			ans[ansPos - 1] = framesize_1;
			ansPos += framesize_1 + 1;
			LOBYTE(v7) = v7 - 1;
		}
	}
	*ans = 0;
	return ansPos - 1;
}





// 和源码函数对应不上
int ID611E_sub_802A530(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v5; // r8
	int v6; // r10
	int k; // r11
	unsigned int v9; // r0
	int v10; // r10
	unsigned int v11; // r9
	unsigned int v12; // r0
	int v14; // r7
	int v15; // r7
	unsigned int v16; // r0
	unsigned __int8 v17; // r8
	int argvPos; // r10 MAPDST
	int i; // r11
	int SendLenth; // r0 MAPDST
	int v25; // r7
	unsigned __int8 v26; // r8
	int v27; // r10
	int v28; // r11
	int v30; // r0 MAPDST
	int v33; // r11
	unsigned __int8 j; // r6
	unsigned __int8 rcvbyte; // [sp+0h] [bp-38h] BYREF
	unsigned __int8 v36; // [sp+1h] [bp-37h]
	unsigned __int8 RecvByte; // [sp+2h] [bp-36h] BYREF
	unsigned __int8 v38; // [sp+3h] [bp-35h]
	unsigned __int8 v39; // [sp+4h] [bp-34h]
	unsigned __int8 v40; // [sp+5h] [bp-33h]
	unsigned __int8 v41; // [sp+6h] [bp-32h] BYREF
	unsigned __int8 v42; // [sp+7h] [bp-31h]
	unsigned __int8 Keyword[8]; // [sp+8h] [bp-30h] BYREF

	v36 = 0;
	RecvByte = 0;
	v41 = 0;
	v40 = 0;
	v42 = *argv;
	rcvbyte = 0;
	v38 = 0;
	v39 = 0;
	*(_DWORD *)Keyword = 0;
	set_time0Stop_sub_802BB48();
	switch (v42)
	{
	case 1u:
		argv[3] = 0;
		v36 = ID6011_LandroverABSEnter_1_sub_802423C(argc, argv + 2, ans);
		goto LABEL_104;
	case 0u:
	LABEL_103:
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		return 2;
	case 3u:
		v17 = argv[2];
		argvPos = 3;
		*ans = 0;
		ans[1] = v17;
		for (i = 2; ; ++i)
		{
			if (!v17--)
			{
				v36 = i;
				goto LABEL_104;
			}
			SendLenth = argv[argvPos++];
			if (!SendLenth)
				break;
			while ((unsigned int)--SendLenth >= 2)
			{
				ComSendByte_sub_802F1E0(argv[argvPos++]);
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			ComSendByte_sub_802F1E0(argv[argvPos++]);
			v25 = 0;
			do
			{
				if (!ComByte_sub_802F6CC(&rcvbyte, 0x5DC))
				{
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 2;
				}
				if (!v25)
				{
					if ((rcvbyte & 0x80) == 0)
					{
						PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						return 2;
					}
					if (rcvbyte < 0xC0u)
						v25 = rcvbyte - 0x80;
					else
						v25 = rcvbyte - 0xC0;
					ans[i++] = v25 + 1;
				}
				ans[i++] = rcvbyte;
				--v25;
			} while (v25);
			if (!ComByte_sub_802F6CC(&rcvbyte, 0x5DC))
			{
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return 2;
			}
			ans[i] = rcvbyte;
			if (v17)
				Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		}
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		goto LABEL_76;
	}
	if (v42 >= 3u)
	{
		if (v42 != 5)
		{
			if (v42 < 5u)
			{
				v36 = sub_80243CE(argc, argv + 2, ans); // 这个不知道是什么函数
			LABEL_104:
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return v36;
			}
			if (v42 == 6)
			{
				Delay_802EF34(0x1F4);
	
				IOCTRLSelect_sub_8030606(1u, 1u);
				sendAddressToEcu_sub_802CC82(argv[2]);
				v40 = ~argv[2];
				ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				if (!ComByte_sub_802F6CC(&RecvByte, 2550) || RecvByte != 0x55 && RecvByte != 0xAA)
				{
					Delay_802EF34(0xFA0);
					
					IOCTRLSelect_sub_8030606(1u, 1u);
					sendAddressToEcu_sub_802CC82(argv[2]);
					ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
					if (!ComByte_sub_802F6CC(&RecvByte, 0x9F6) || RecvByte != 0x55)
					{
						PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
						v36 = 2;
					}
				}
				for (j = 0; j < 2u; ++j)
				{
					if (!ComByte_sub_802F6CC(&Keyword[j], 0x1388))
					{
						PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
						v36 = 2;
					}
				}
				Delay_802EF34(0x23);
				ComSendByte_sub_802F1E0((unsigned __int8)~Keyword[1]);
				if (ComByte_sub_802F6CC(&v41, 0x12C))
				{
					if (v41 == v40)
						PutDataToAns_sub_802BCBC(szFOK_20004A04, ans, 4);
					else
						PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					v36 = 2;
				}
				else
				{
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					v36 = 2;
				}
				goto LABEL_104;
			}
			goto LABEL_103;
		}
		IOCTRLInit_sub_802C570();
		v38 = argv[2];
		v39 = argv[3];
		v26 = argv[4];
		v27 = 5;
		*ans = 0;
		ans[1] = v26;
		v28 = 2;
		while (1)
		{
			if (!v26--)
			{
				v36 = v28;
				goto LABEL_104;
			}
			v30 = argv[v27++];
			if (!v30)
				break;
			while (v30--)
			{
				ComSendByte_sub_802F1E0(0xFFu);
				Delay_802EF34(v38);
				ComSendByte_sub_802F1E0(argv[v27++]);
				if (!ComByte_sub_802F6CC(&rcvbyte, v39))
				{
					PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return 2;
				}
				ans[v28] = 1;
				v33 = v28 + 1;
				ans[v33] = rcvbyte;
				v28 = v33 + 1;
			}
			if (v26)
				Delay_802EF34(v38);
		}
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
	LABEL_76:
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		return 2;
	}
	v5 = argv[2];
	v6 = 3;
	*ans = 0;
	ans[1] = v5;
	for (k = 2; ; ++k)
	{
		if (!v5--)
		{
			v36 = k;
			goto LABEL_104;
		}
		v9 = argv[v6];
		v10 = v6 + 1;
		v11 = v9;
		if (!v9)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			goto LABEL_76;
		}
		while (1)
		{
			v12 = v11--;
			if (v12 < 2)
				break;
			ComSendByte_sub_802F1E0(argv[v10++]);
			if (!ComByte_sub_802F6CC(&rcvbyte, 0x1F4))
			{
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return 2;
			}
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(argv[v10]);
		v6 = v10 + 1;
		v14 = 0;
		do
		{
			if (!ComByte_sub_802F6CC(&rcvbyte, 0x5DC))
			{
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return 2;
			}
			if (!v14)
			{
				if ((rcvbyte & 0xF0) == 0x80)
					v15 = (rcvbyte & 0xF) + 2;
				else
					v15 = 2;
				ans[k++] = v15;
				v14 = v15 - 1;
			}
			ComSendByte_sub_802F1E0(rcvbyte);
			ans[k++] = rcvbyte;
			v16 = v14--;
		} while (v16 >= 2);
		if (!ComByte_sub_802F6CC(&rcvbyte, 0x5DC))
			break;
		ans[k] = rcvbyte;
		if (v5)
			Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
	}
	PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return 2;
}




int ID611F_HoldenCan20SendOneFrameReceiveDatas_1_sub_8037154(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int RecvLen; // r7
	unsigned __int8 *ansHead; // r9
	unsigned __int8 total_length; // r8
	int result; // r0
	unsigned __int8 specialdata[4]; // [sp+4h] [bp-54h] BYREF
	data_info RecvInfo; // [sp+8h] [bp-50h] BYREF
	data_info SendInfo; // [sp+20h] [bp-38h] BYREF

	*(_DWORD *)specialdata = 0;
	RecvLen = 0;
	set_time0Stop_sub_802BB48();
	ansHead = ans + 2;
	if (!*argv)
		ExitFlag_2000C6BA = 2;
	SendInfo.number = argv[1];
	RecvInfo.number = argv[2];
	SendInfo.length_pos = 3;
	total_length = 0;
	if (SendInfo.number)
	{
		memmove(SendInfo.data, &argv[SendInfo.length_pos + 3], 0xBu);
		Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		CanSendMsg_sub_802B874(SendInfo.data, 2, specialdata);
		SendInfo.length_pos += argv[SendInfo.length_pos] + 2;
		--SendInfo.number;
	}
	if (RecvInfo.number)
	{
		do
		{
			if (!RecvInfo.number)
				break;
			RecvInfo.length = ReadOneFrameFromCANBuf_Ext_sub_802B550(&RecvInfo.data[1], 2, specialdata, 3u, 0x1F4);
			if (!RecvInfo.length && !RecvLen)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			if (RecvInfo.length < 5u)
				break;
			RecvInfo.data[0] = RecvInfo.length + 1;
			memmove(ansHead, RecvInfo.data, RecvInfo.length + 1);
			ansHead += RecvInfo.length + 1;
			RecvLen += RecvInfo.length + 1;
			++total_length;
			--RecvInfo.number;
		} while (!SendInfo.number);
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0;
		ans[1] = total_length;
		Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		result = RecvLen + 2;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 0;
		result = 2;
	}
	return result;
}




// // Funtion: JAGUAR 专用 PWM 协议 发一帧数据到ECU 并接收应答(直到ECU 不发才结束)
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : recv: 61,20,01,f5,10,05,c4,10,f5,13,c7,50
int ID6120_JAGUARPWM_SendDataToEcuGetMultiFrameAnswer_1_sub_8051586(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 framesize; // r7
	int framepos; // r9
	int FrameID; // r10
	unsigned __int8 frameNum; // r8
	unsigned __int8 framesize_1; // r7
	int result; // r0
	unsigned __int8 Addrress[4]; // [sp+Ch] [bp-2Ch] BYREF
	unsigned int firstms; // [sp+10h] [bp-28h] BYREF

	framesize = argv[3];
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	SC_RelayState_200049DC.CommType = 3;
	SC_RelayState_200049DC.LevelType = 0xC;
	CMPHY_Relay_Reset_sub_8030B88();
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	PWM_Init_sub_8032164();
	firstms = 0;
	framepos = 3;
	FrameID = argv[2] + ((argv[1] + (*argv << 8)) << 8);
	if (!PWM_Send_sub_803216E(argv + 4, framesize, 1, Addrress))
	{
		Delay_802EF34(1);
		PWM_Send_sub_803216E(argv + 4, framesize, 1, Addrress);
	}
	frameNum = 0;
	Addrress[0] = argv[6];
	while (1)
	{
		framesize_1 = PWM_Receive_sub_8032208(&ans[framepos], 0xC8u, &firstms, 0x1F4u, 1, FrameID, Addrress[0]);
		if (firstms >= 0x78)
			break;
		ans[framepos - 1] = framesize_1;
		framepos += framesize_1 + 1;
		++frameNum;
	}
	ans[1] = frameNum;
	if (frameNum)
	{
		*ans = 0;
		result = framepos;
	}
	else
	{
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}



//wabco ABS send one frame to ecu and receive one frame,but each times read or send byte
int ID6121_WabcoAbsSendOneAndReicveOneFrame_1_sub_80218F0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 argvPos; // r7 MAPDST
	int sendframenum; // r8
	int Ret; // r0
	unsigned __int8 ansPos; // r11
	int sendlen; // r0 MAPDST
	int rcvlen; // r0 MAPDST
	unsigned __int8 v16; // r0
	unsigned __int8 v17; // r0
	unsigned __int8 v18[40]; // [sp+0h] [bp-28h] BYREF

	*ans = 0;
	set_time0Stop_sub_802BB48();
	argvPos = 1;
	sendframenum = *argv;
	if ((_BYTE)sendframenum)
	{
		ans[1] = sendframenum;
		ansPos = 2;
		while ((_BYTE)sendframenum--)
		{
			sendlen = argv[argvPos++];
			if (!(_BYTE)sendlen)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
			LABEL_10:
				PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
				return 2;
			}
			rcvlen = argv[argvPos++];
			if (!(_BYTE)rcvlen)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				goto LABEL_10;
			}
			ans[ansPos++] = rcvlen - 1;
			while (1)
			{
				v16 = sendlen--;
				if (v16 < 2u)
					break;
				ComSendByte_sub_802F1E0(argv[argvPos++]);
				if (!ComByte_sub_802F6CC(v18, 500))
					goto LABEL_25;
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			ComSendByte_sub_802F1E0(argv[argvPos++]);
			while (1)
			{
				v17 = rcvlen--;
				if (v17 < 2u)
					break;
				if (!ComByte_sub_802F6CC(v18, 1500))
					goto LABEL_25;
				ComSendByte_sub_802F1E0(v18[0]);
				ans[ansPos++] = v18[0];
			}
			if (!ComByte_sub_802F6CC(v18, 1500))
			{
			LABEL_25:
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				return 2;
			}
			Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		}
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		Ret = ansPos;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		Ret = 2;
	}
	return Ret;
}




// // Funtion: wabco ABS send one frame to ecu and receive Multi-frame,but each times read or send byte
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:发送到ECU的一帧数据的长度len
// //          argv[1] ~ argv[len]:发送到ECU的数据
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 帧长度 帧数据
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6122
int ID6122_WabcoAbsSendOneAndReicveMultiFrame_1_sub_8021A92(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v5; // r11
	int sendlen; // r9
	int result; // r0
	unsigned __int8 argvPos; // r7
	unsigned __int8 v9; // r0
	unsigned __int8 ansLen; // r8
	unsigned __int8 v11; // r10
	unsigned __int8 rcvbyte[40]; // [sp+0h] [bp-28h] BYREF

	v5 = 0;
	set_time0Stop_sub_802BB48();
	sendlen = *argv;
	if ((_BYTE)sendlen)
	{
		argvPos = 1;
		while (1)
		{
			v9 = sendlen--;
			if (v9 < 2u)
				break;
			ComSendByte_sub_802F1E0(argv[argvPos++]);
			if (!ComByte_sub_802F6CC(rcvbyte, 0x3E8))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
			LABEL_20:
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				return 2;
			}
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(argv[argvPos]);
		*ans = 0;
		ans[1] = 1;
		ansLen = 3;
		do
		{
			if (!ComByte_sub_802F6CC(rcvbyte, 0x9C4))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				goto LABEL_20;
			}
			ComSendByte_sub_802F1E0(rcvbyte[0]);
			ans[ansLen++] = rcvbyte[0];
			v11 = rcvbyte[0];
			++v5;
			if (!ComByte_sub_802F6CC(rcvbyte, 0x3E8))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				goto LABEL_20;
			}
		} while (v11 != 4);
		ans[2] = v5;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = ansLen;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}



// //    功  能：发一帧数据到ECU并接收一帧ECU的应答，一帧数据长度大于
// //            256字节.
// //    参  数：argc 发送数据长度
// //            argv     发送缓冲区指针,格式为:数据长度高位
// //                        （1BYTE）数据长度低位（1BYTE）, 数据内容,
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 帧长度 帧数据
// // Return : 返回的ans缓冲区的有效数据长度
// //    0x6126    用于长安铃木车型
int ID6126_OneToOne_SendLongDataToEcuGetLongAnswer_1_sub_8021DF8(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r7
	int argvPos; // r9
	int trcvlen; // r8
	int ansLen; // r10
	unsigned int RecvLen; // r8
	unsigned int sendframesize; // r8 MAPDST
	unsigned __int8 rcvbyte[40]; // [sp+0h] [bp-28h] BYREF

	set_time0Stop_sub_802BB48();
	v5 = *argv << 8;
	ComSendByte_sub_802F1E0(*argv);
	Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	sendframesize = argv[1] + v5;
	ComSendByte_sub_802F1E0(argv[1]);
	Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	if (sendframesize < 2)
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		return 2;
	}
	argvPos = 2;
	sendframesize -= 2;
	do
	{
		ComSendByte_sub_802F1E0(argv[argvPos++]);
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		--sendframesize;
	} while (sendframesize >= 2);
	ComSendByte_sub_802F1E0(argv[argvPos]);
	*ans = 0;
	ans[1] = 1;
	if (!ComByte_sub_802F6CC(rcvbyte, 0x12C))
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
	LABEL_24:
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		return 2;
	}
	ans[2] = rcvbyte[0];
	trcvlen = rcvbyte[0] << 8;
	if (!ComByte_sub_802F6CC(rcvbyte, 0x12C))
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		goto LABEL_24;
	}
	ans[3] = rcvbyte[0];
	ansLen = 4;
	RecvLen = rcvbyte[0] + trcvlen;
	if (RecvLen < 2)
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		goto LABEL_24;
	}
	sendframesize = RecvLen - 2;
	while (sendframesize--)
	{
		if (!ComByte_sub_802F6CC(rcvbyte, 0x12C))
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			goto LABEL_24;
		}
		ans[ansLen++] = rcvbyte[0];
	}
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return ansLen;
}




// // Funtion: VPW协议发多 收多
// // Input  : argc - 参数长度
// //          argv - 参数
// // Output : ans - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6127 ,ff,01,10,6c,f1,05,6c,25,f1,20,c5,6d,
// //          BUG  08 6C 10 F1 12 03 FF FF E6 ;Times: 1319601 us 
// //               0A 6C F1 10 52 03 00 02 00 00 79 ;Times: 17894 us 
// //               0A 6C F1 10 52 03 00 03 01 00 BA ;Times: 12541 us 
// //               09 6C F1 10 52 03 00 04 00 E9 ;Times: 11655 us 
// //               09 6C F1 10 52 03 00 05 48 5E ;Times: 12319 us 
// //               09 6C F1 10 52 03 00 06 80 57 ;Times: 12556 us 
// //               09 6C F1 10 52 03 00 07 91 CB ;Times: 13194 us 
// //               09 6C F1 10 52 03 00 0B 65 B7 ;Times: 11926 us 
// //               0A 6C F1 10 52 03 00 0C 00 00 70 ;Times: 13271 us 
// //               09 6C F1 10 52 03 00 0D 00 FF ;Times: 11696 us 
// //               08 6C 10 F1 12 03 FF FF E6 ;Times: 12086 us 
// //               0A 6C F1 10 52 03 00 10 09 0F CF ;Times: 7804 us 
// //      SendCmd: 55,aa,f0,f8,00,13,3f,27,01,61,27,ff,01,50,6c,f1,08,6c,10,f1,12,03,ff,ff,e6,05,
// //      ReceiveCmd: ff,02,
int ID6127_VpwSendMultiFrameAndReceiveMultiFrameKnownAckFrameNumber_1_sub_80510C0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 framenum; // r7 MAPDST
	unsigned int Allms; // r10
	int framepos; // r8
	int v8; // r9
	unsigned __int8 v9; // r6
	int v10; // r9
	int result; // r0
	unsigned __int8 framesize; // r6
	unsigned __int8 v14; // r11
	unsigned __int8 filt_id1; // [sp+0h] [bp-30h]
	unsigned __int8 filt_id2; // [sp+1h] [bp-2Fh]
	unsigned __int8 MaxRecv; // [sp+2h] [bp-2Eh]
	int firstms[11]; // [sp+4h] [bp-2Ch] BYREF

	firstms[1] = argc;
	if (!*argv)
		ExitFlag_2000C6BA = 2;
	if (SC_RelayState_200049DC.CommType != 4)
		CMPHY_Relay_Reset_sub_8030B88();
	CMPHY_Relay_Init_sub_8030B62(&SC_RelayState_200049DC);
	SC_RelayState_200049DC.CommType = 4;
	SC_RelayState_200049DC.LevelType = 0xC;
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	VPW_Init_sub_8051858();
	framenum = argv[1];
	MaxRecv = argv[2];
	filt_id1 = argv[3];
	filt_id2 = argv[4];
	Allms = 0;
	firstms[0] = 0;
	framepos = 3;
	v8 = 5;
	while (framenum)
	{
		v9 = argv[v8];
		v10 = v8 + 1;
		Delay_802EF34(0x14);
		if (!VPW_Send_sub_8051862(&argv[v10], v9))
		{
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		--framenum;
		v8 = v9 + v10;
	}
	framenum = 0;
	while (Allms < 1400 && framenum < (unsigned int)MaxRecv)
	{
		framesize = VPW_Receive_sub_8051896(&ans[framepos], 0xC8, firstms, 0x12C);
		if (framesize < 5u)
			v14 = 0;
		else
			v14 = ans[framepos + 3];
		if (framesize && ans[framepos] == filt_id1 && ans[framepos + 1] == filt_id2)
		{
			ans[framepos - 1] = framesize;
			framepos += framesize + 1;
			++framenum;
			Allms = 0x3E8;
		}
		else if (framesize && filt_id1 == 0x7F)
		{
			if (ans[framepos + 1] == filt_id2 || filt_id2 == 0x7F)
			{
				ans[framepos - 1] = framesize;
				framepos += framesize + 1;
				++framenum;
				Allms = 0x3E8;
			}
		}
		else
		{
			Allms += firstms[0];
		}
		if (v14 == 0x7F)
			Allms = 0;
	}
	ans[1] = framenum;
	if (framenum)
	{
		*ans = 0;
		result = framepos - 1;
	}
	else
	{
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}






// //函数名称:int OneToOne_SendOneByteToEcuGetAnswerLM()
// // Input  : argc - 参数长度
// //          argv - 0xlen,0x内容,最大等待时间
// // Output : ans  - 回复到上位机的数据
// // Return : 回复到上位机的数据长度
// // Info   : 6128
// //1.发送给上位机的数据格式是: 0x00 ,0x00, 0xlen 一帧长度 一帧内容.......
// //                            -    ----------   ---------------------
// //                            |        |                 |记录的是实际的内容。
// //                            |        |帧数记录。
// //                            |数据标志位，（0xff表示的是设置）。
// //2.argv的缓冲区的数据格式：
// //  发送的次数 + 帧数 + 每帧的长度 + 每帧的内容 +长度　+ 内容
// //3.实现的功能:ISO_9141协议的接受和发送。
// //             主要实现的是：发多帧收多帧,对于发送的每一帧都有一帧的应答。
// //4,协议举例:
// //   req:68 6a f1 be 81
// //   ans:48 6b c0 fe 00 01 72
// //5.注意函数实现的功能和函数：IsoInitSendDataToEcuGetAnswer,IsoInitSendDataToEcuGetAnswer,
// //  IsoAddSendDataToEcuGetAnswer.组合使用的方式是一样的。
int ID6128_OneToOne_SendOneByteToEcuGetAnswerLM_1_sub_80272B8(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int result; // r0
	int v6; // r7
	int argvPos; // r8
	int v9; // r9
	int v10; // r10
	int v11; // r7
	unsigned __int8 rcvbyte[40]; // [sp+0h] [bp-28h] BYREF

	if (*argv)
	{
		v6 = *argv - 1;
		argvPos = 1;
		set_time0Stop_sub_802BB48();
		while (v6--)
		{
			ComSendByte_sub_802F1E0(argv[argvPos++]);
			if (!ComByte_sub_802F6CC(rcvbyte, 1000))
			{
				*ans = -1;
				ans[1] = 2;
				return 2;
			}
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(argv[argvPos]);
		if (ComByte_sub_802F6CC(rcvbyte, 1000))
		{
			ans[1] = 1;
			if (ComByte_sub_802F6CC(rcvbyte, 1000))
			{
				ans[2] = rcvbyte[0];
				if (ComByte_sub_802F6CC(rcvbyte, 1000))
				{
					ans[3] = rcvbyte[0];
					v9 = 4;
					v10 = rcvbyte[0] + 1;
					v11 = rcvbyte[0] + 5;
					while (v10--)
					{
						if (!ComByte_sub_802F6CC(rcvbyte, 1000))
						{
							*ans = -1;
							ans[1] = 2;
							return 2;
						}
						ans[v9++] = rcvbyte[0];
					}
					*ans = 0;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					result = v11;
				}
				else
				{
					*ans = -1;
					ans[1] = 2;
					result = 2;
				}
			}
			else
			{
				*ans = -1;
				ans[1] = 2;
				result = 2;
			}
		}
		else
		{
			*ans = -1;
			ans[1] = 2;
			result = 2;
		}
	}
	else
	{
		*ans = -1;
		ans[1] = 2;
		result = 2;
	}
	return result;
}


// // Funtion: KWP通讯时，可过滤指定ID
// // Input  : argc - 参数长度
// //          argv - 指令参数缓冲区
// //          argv[0]:recmode
// //          argv[1]:发送一帧数数据的长度len
// //          argv[2]~argv[len+1]:发送往ECU的一帧有效数据
// //          argv[3]:目标地址
// //          argv[4]:源地址
// //          argv[len+2]:timebuff
// // Output : ans - 回复到上位机的数据
// //                1、指令格式异常返回 FF 01
// //                2、下位机通信异常返回 FF 02
// //                3、ans的格式为：总帧数 帧长度 帧数据
// // Return : 返回的ans缓冲区的有效数据长度
// // Info   : 6129 用于下线检测的指令，诊断中未使用
int ID6129_KWPSendOneAndReceiveMultiFrameHasFilter_1_sub_80273FA(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 recmode; // r8
	int argvPos; // r10
	int framelen; // r9
	int result; // r0
	int ansLen; // r11
	unsigned __int8 i; // r6
	unsigned __int8 v12; // [sp+0h] [bp-40h]
	unsigned __int8 v13; // [sp+2h] [bp-3Eh]
	unsigned int rcvframesize; // [sp+4h] [bp-3Ch] BYREF
	int waitingtime; // [sp+8h] [bp-38h]
	unsigned __int8 busyid[2]; // [sp+Ch] [bp-34h] BYREF
	int timebuff; // [sp+10h] [bp-30h]

	*(_WORD *)busyid = 0;
	timebuff = 0;
	waitingtime = 0;
	rcvframesize = 0;
	set_time0Stop_sub_802BB48();
	recmode = *argv;
	if (!*argv)
	{
		v13 = argv[3];
		v12 = argv[4];
	}
	argvPos = 2;
	framelen = argv[1];
	if ((_BYTE)framelen)
	{
		do
		{
			ComSendByte_sub_802F1E0(argv[argvPos++]);
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			--framelen;
		} while ((unsigned __int8)framelen >= 2u);
		ComSendByte_sub_802F1E0(argv[argvPos]);
		timebuff = 300;
		waitingtime = 300;
		*ans = 0;
		ans[1] = 0;
		ansLen = 2;
		while (ReceiveOneKwpFrameFromECUHasMode_sub_802C940(recmode, receive_buff_2000BF20, &rcvframesize, waitingtime))
		{
			if (recmode || v13 == receive_buff_2000BF20[2] && v12 == receive_buff_2000BF20[1])
			{
				GetKwpFrameBusyFlag_sub_802CAF8(receive_buff_2000BF20, busyid);
				if (busyid[0] == 0x7F && busyid[1] == 0x78)
				{
					waitingtime = 5000;                   // 遇到忙帧 等待时间加长
				}
				else
				{
					++ans[1];
					ans[ansLen++] = rcvframesize;
					for (i = 0; rcvframesize--; ++i)
						ans[ansLen++] = receive_buff_2000BF20[i];
				}
			}
		}
		if (ans[1])
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			result = ansLen;
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			result = 2;
		}
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}


//602A 省略了

int ID612B_sub_802A3BC(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 FrameNum; // r7
	unsigned __int8 Checkxor; // r8
	unsigned int total_length; // r9
	int v7; // r10
	unsigned __int8 *ansHead; // r11
	unsigned int i; // r5
	__int16 time; // r6
	int result; // r0
	unsigned __int8 v12; // r0
	unsigned __int8 v13; // [sp+0h] [bp-40h]
	unsigned __int8 specialdata[3]; // [sp+1h] [bp-3Fh] BYREF
	unsigned int RecvSize; // [sp+8h] [bp-38h] BYREF
	int v17; // [sp+Ch] [bp-34h]
	unsigned __int8 rcvbyte[8]; // [sp+10h] [bp-30h] BYREF

	v17 = *argv;
	FrameNum = 0;
	RecvSize = 0;
	*(_WORD *)&specialdata[1] = 0;
	Checkxor = 0;
	total_length = 0;
	v7 = 0;
	ansHead = ans + 2;
	*(_WORD *)specialdata = argv[2];
	v13 = argv[3];
	while (ComByte_sub_802F6CC(rcvbyte, 3))
		;
	set_time0Stop_sub_802BB48();
	for (i = 0; i < v17 - 1; ++i)
	{
		ComSendByte_sub_802F1E0(argv[i + 1]);
		Checkxor += argv[i + 1];
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	ComSendByte_sub_802F1E0(Checkxor);
	time = 0xA * CalculateTimeOut_sub_802CC3E(argv[i + 2], 0xAu);
	while (sub_802EC18(ansHead + 1, &RecvSize, time, &specialdata[1]))// 这函数 接收数据
	{
		if (specialdata[1] == 0x7F && specialdata[2] == 0x78)
		{
			time = 0x1388;
		}
		else
		{
			time = 0xA * CalculateTimeOut_sub_802CC3E(argv[i + 2], 0xAu);
			if (specialdata[0] == ansHead[3] && v13 == ansHead[2])
			{
				v7 = 0;
				*ansHead = RecvSize;
				ansHead += RecvSize + 1;
				++FrameNum;
				total_length += RecvSize + 1;
				if (total_length > 0xE10)
				{
					*ans = 0;
					ans[1] = FrameNum;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return total_length + 2;
				}
			}
			else
			{
				v12 = v7++;                             // 这里不知道为什么走这个分支
				if (v12 >= 4u)
					break;
			}
		}
	}
	if (FrameNum)
	{
		*ans = 0;
		ans[1] = FrameNum;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = total_length + 2;
	}
	else
	{
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}



// 源码没有这函数 也看不太懂
int ID612D_sub_803B2A0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	char v4; // r6
	char v5; // r7
	unsigned __int16 DelayTime; // r8
	unsigned int v7; // r9
	unsigned __int8 v8; // r4
	unsigned __int8 *v9; // r10
	unsigned __int16 v11; // r11
	char v12; // r7
	char v13; // [sp+0h] [bp-70h]
	unsigned __int8 v14; // [sp+1h] [bp-6Fh]
	unsigned __int16 DelayCnt; // [sp+2h] [bp-6Eh]
	unsigned __int8 Ans[2]; // [sp+4h] [bp-6Ch] BYREF
	unsigned __int16 v17; // [sp+6h] [bp-6Ah]
	unsigned int v18; // [sp+8h] [bp-68h]
	unsigned int v19; // [sp+Ch] [bp-64h]
	unsigned int v20; // [sp+10h] [bp-60h]
	char v21; // [sp+14h] [bp-5Ch]
	unsigned __int16 v22; // [sp+18h] [bp-58h]
	unsigned __int8 v23; // [sp+1Ah] [bp-56h]
	unsigned __int8 CmdHeadBuf[13]; // [sp+1Ch] [bp-54h] BYREF
	unsigned int v25; // [sp+2Ch] [bp-44h]
	unsigned __int8 DataBuf[20]; // [sp+30h] [bp-40h] BYREF

	v4 = 0;
	v5 = 0;
	v13 = 0;
	v25 = 0;
	DelayTime = 0xA * *argv;
	v7 = argv[1] + (argv[2] << 0x10) + (argv[3] << 8);
	v14 = argv[4];
	v8 = argv[6];
	v9 = argv + 7;
	v19 = argv[0xB] + (argv[9] << 0x10) + (argv[8] << 0x18) + (argv[0xA] << 8);
	v20 = v19 >> 3;
	v19 = (unsigned __int8)(v19 >> 0xB) | (v7 >> 8 << 8);
	v23 = v19;
	if ((unsigned __int8)v19 >= 0xF0u)
	{
		if (v23 == 0xFF)
			v19 = (v19 >> 8 << 8) | v14;
		else
			v20 = v19;
	}
	else
	{
		v20 = (BYTE1(v20) + ((unsigned __int8)v20 << 0x10)) & 0xFF00FF | v7 & 0xFF00;
	}
	if (DelayTime_2000C53C || TimeOut_2000C530)
	{
		v22 = DelayTime_2000C53C;
		DelayCnt = TimeOut_2000C530;
	}
	else
	{
		v22 = 5;
		DelayCnt = 0x1F4;
	}
	if (!DelayTime || DelayTime >= 0x3E9u)
		DelayTime = 0xC8;
	DataBuf[0] = 0;
	DataBuf[1] = 0xFF;
	SetCANFilter_sub_802D4D4(DataBuf);
	set_time0Stop_sub_802BB48();
	v21 = 1;
	while (v8)
	{
		if (!CanSendMsg_sub_802B874(v9, 4, &DataBuf[4]))
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		if (DataBuf[4] == 0x10 && !v5)
		{
			v5 = 1;
			Ans[0] = 2;
			v17 = DelayTime;
			v18 = v7;
			if (!sub_802B6E8(CmdHeadBuf, 0xD, Ans, DelayCnt))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			if (CmdHeadBuf[5] != 0x11)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
		}
		if (--v8)
		{
			v9 += (*v9 & 0xF) + 5;
			if (DataBuf[4] != 0x10)
				Delay_802EF34(v22);
		}
	}
	Ans[0] = 0;
	v17 = 0x1F4;
	v18 = v7;
	v11 = 2;
	*ans = 0;
	v12 = 0;
	v21 = 1;
	do
	{
		while (1)
		{
			if (!sub_802B6E8(CmdHeadBuf, 0xD, Ans, DelayCnt))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				if (v13 == 1)
					Can_sub_803289A(CAN_SetPara_2000C2F0.CanPort);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			if (Ans[0] == 1)
				break;
			if (Ans[0] == 2)
			{
				if (CmdHeadBuf[5] != 0x10 || v12)
				{
					if (CmdHeadBuf[5] == 0x20)
					{
						Copysub_802FB50(&ans[v11], CmdHeadBuf, 0xD);
						Ans[0] = 1;
						v18 = v14 + (CmdHeadBuf[3] << 0x10) + 0xEB00;
						DataBuf[0xC] = CmdHeadBuf[8];
						v4 = 2;
						v11 += 0xD;
					}
					else
					{
						if (CmdHeadBuf[5] != 0x13)
						{
							Copysub_802FB50(&ans[v11], CmdHeadBuf, 0xD);
							ans[1] = 1;
							v11 += 0xD;
							goto LABEL_55;
						}
						v25 = CmdHeadBuf[4] + (CmdHeadBuf[3] << 8);
						v13 = 1;
						SetCan_sub_80327A2(CAN_SetPara_2000C2F0.CanPort, v25, 0xFFFFu, 2);
						Ans[0] = 2;
						v21 = 0;
					}
				}
				else
				{
					v12 = 1;
					Copysub_802FB50(&ans[v11], CmdHeadBuf, 0xD);
					Copysub_802FB50(&DataBuf[4], CmdHeadBuf, 0xD);
					CmdHeadBuf[3] = DataBuf[8];
					CmdHeadBuf[4] = DataBuf[7];
					CmdHeadBuf[5] = 0x11;
					CmdHeadBuf[6] = DataBuf[0xC];
					CmdHeadBuf[7] = 1;
					CmdHeadBuf[8] = 0xFF;
					CmdHeadBuf[9] = 0xFF;
					SetCanRx_sub_802D8C0(CmdHeadBuf);
					Ans[0] = 1;
					v18 = DataBuf[8] + (DataBuf[7] << 0x10) + 0xEB00;
					v4 = 1;
					v11 += 0xD;
				}
			}
		}
		Copysub_802FB50(&ans[v11], CmdHeadBuf, 0xD);
		ans[1] = 1;
		v11 += 0xD;
		if (!v4)
			goto LABEL_55;
	} while (CmdHeadBuf[5] < (unsigned int)DataBuf[0xC]);
	ans[1] = DataBuf[0xC] + 1;
	if (v4 == 1)
	{
		Copysub_802FB50(CmdHeadBuf, &DataBuf[4], 0xD);
		CmdHeadBuf[3] = DataBuf[8];
		CmdHeadBuf[4] = DataBuf[7];
		CmdHeadBuf[5] = 0x13;
		SetCanRx_sub_802D8C0(CmdHeadBuf);
	}
LABEL_55:
	if (v13 == 1)
		Can_sub_803289A(CAN_SetPara_2000C2F0.CanPort);
	return v11;
}


// 源码没有这函数
int ID612E_sub_803B8EC(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v3; // r5
	unsigned int v4; // r9
	char v5; // r10
	char v6; // r7
	int v7; // r8
	unsigned int i; // r4
	unsigned int j; // r11
	unsigned int k; // r11
	int result; // r0
	unsigned int l; // r11
	unsigned __int8 v13; // r6
	unsigned __int8 v14; // r6
	unsigned __int8 v15; // [sp+4h] [bp-54h]
	unsigned __int8 v16; // [sp+5h] [bp-53h]
	unsigned __int8 v17; // [sp+6h] [bp-52h]
	unsigned __int8 v18[4]; // [sp+8h] [bp-50h] BYREF
	unsigned __int8 v19[4]; // [sp+Ch] [bp-4Ch] BYREF
	unsigned __int8 *v20; // [sp+10h] [bp-48h]
	__int16 v21; // [sp+14h] [bp-44h]
	int v22; // [sp+18h] [bp-40h]
	size_t v23; // [sp+1Ch] [bp-3Ch]
	int v24; // [sp+20h] [bp-38h]
	unsigned int v25; // [sp+24h] [bp-34h]

	v24 = 0;
	v25 = 0;
	v23 = 0;
	v3 = 0;
	v22 = 0;
	v4 = 0;
	v20 = ans;
	v21 = 0;
	v5 = 0;
	*(_DWORD *)v19 = 0;
	*(_DWORD *)v18 = 0;
	v21 = argv[1] + (*argv << 8);
	set_time0Stop_sub_802BB48();
	if (v21 == 1)
	{
		v24 = argv[4] + (argv[3] << 8);
		v6 = argv[5];
		v15 = argv[6];
		v17 = argv[7];
		v16 = argv[8];
		v25 = argv[9];
		v22 = 0xA;
		v7 = 2;
		for (i = 0; i < v25; ++i)
		{
			v23 = argv[v22];
			memset(CmdBuf_2000C554, 0, 0x14);
			memmove(CmdBuf_2000C554, &argv[v22 + 1], v23);
			if (i == 1)
			{
				v5 = 0;
				if (v6 == 4)
				{
					CmdBuf_2000C554[8] = v18[0];
					CmdBuf_2000C554[9] = v18[1];
					CmdBuf_2000C554[0xA] = v18[2];
					CmdBuf_2000C554[0xB] = v18[3];
					for (j = 0; j < 8; ++j)
						v5 += CmdBuf_2000C554[j + 5];
				}
				else if (v6 == 2)
				{
					CmdBuf_2000C554[6] = v18[0];
					CmdBuf_2000C554[7] = v18[1];
					CmdBuf_2000C554[8] = v18[2];
					CmdBuf_2000C554[9] = v18[3];
					for (k = 0; k < 8; ++k)
						v5 += CmdBuf_2000C554[k + 3];
				}
			}
			else if (i == 2)
			{
				if (v6 == 4)
				{
					CmdBuf_2000C554[5] = -v5;
				}
				else if (v6 == 2)
				{
					CmdBuf_2000C554[3] = -v5;
				}
			}
			if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, v6, specialdata_2000C670))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*v20 = szFBREAK_20004A0C[0];
				v20[1] = szFBREAK_20004A0C[1];
				return 2;
			}
			if (i)
			{
				if (i == 1)
				{
					if (v16)
						Delay_802EF34(v16);
				}
				else if (i == 2)
				{
					v14 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], v6, specialdata_2000C670, 1u, v24);
					if (v14)
					{
						++v3;
						memmove(&ans[v7], &CmdBuf_2000C554[0x14], v14);
						v7 += v14;
						v4 += v14;
					}
					else if (v4 < 3)
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						*v20 = szFBREAK_20004A0C[0];
						v20[1] = szFBREAK_20004A0C[1];
						return 2;
					}
				}
			}
			else
			{
				for (l = 0; l < 3; ++l)
				{
					v13 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], v6, specialdata_2000C670, 1u, v24);
					if (!v13 && !l)
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						*v20 = szFBREAK_20004A0C[0];
						v20[1] = szFBREAK_20004A0C[1];
						return 2;
					}
					if (!l)
					{
						if (v6 == 4)
						{
							if ((CmdBuf_2000C554[0x17] & 0xFu) < 8)
							{
								if (timer_open_flag_2000C6B7 == 1)
									TIM_sub_802EEEC(0);
								*v20 = szFBREAK_20004A0C[0];
								v20[1] = szFBREAK_20004A0C[1];
								return 2;
							}
							v19[0] = CmdBuf_2000C554[0x1F];
							v19[1] = CmdBuf_2000C554[0x20];
							v19[2] = CmdBuf_2000C554[0x21];
							v19[3] = CmdBuf_2000C554[0x22];
						}
						else if (v6 == 2)
						{
							if ((CmdBuf_2000C554[0x17] & 0xFu) < 8)
							{
								if (timer_open_flag_2000C6B7 == 1)
									TIM_sub_802EEEC(0);
								*v20 = szFBREAK_20004A0C[0];
								v20[1] = szFBREAK_20004A0C[1];
								return 2;
							}
							v19[0] = CmdBuf_2000C554[0x1D];
							v19[1] = CmdBuf_2000C554[0x1E];
							v19[2] = CmdBuf_2000C554[0x1F];
							v19[3] = CmdBuf_2000C554[0x20];
						}
						switch (v15)
						{
						case 1u:
							sub_803B704(v19, v18);
							break;
						case 2u:
							sub_803B790(v19, v18);
							break;
						case 3u:
							sub_803B878(v19, v18);
							break;
						}
						if (v17)
							Delay_802EF34(v17);
						++v3;
						memmove(&ans[v7], &CmdBuf_2000C554[0x14], v13);
						v7 += v13;
						v4 += v13;
					}
				}
			}
			v22 += v23 + 1;
		}
		*ans = 0;
		ans[1] = v3;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = v4 + 2;
	}
	else
	{
		*v20 = szFBREAK_20004A0C[0];
		v20[1] = szFBREAK_20004A0C[1];
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = 2;
	}
	return result;
}



int ID6201_Can20SendTwoFrameQuickGetInfo_1_sub_8038784(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	__int16 timeOut; // r7
	unsigned __int8 *ansHead; // r8
	int result; // r0
	unsigned __int8 *v8; // r8
	int v9; // r9
	unsigned __int8 specialdata[4]; // [sp+4h] [bp-54h] BYREF
	data_info RecvInfo; // [sp+8h] [bp-50h] BYREF
	unsigned __int8 SendLenPos; // [sp+22h] [bp-36h]
	unsigned __int8 CmdHeadBuf[52]; // [sp+24h] [bp-34h] BYREF

	*(_DWORD *)specialdata = 0;
	timeOut = 500;
	ansHead = ans + 2;
	SendLenPos = 2;
	RecvInfo.number = 0;
	set_time0Stop_sub_802BB48();
	memmove(CmdHeadBuf, argv + 5, argv[2] - 2);
	SendLenPos = argv[2] + 6;
	Delay_802EF34(5);
	if (CanSendMsg_sub_802B874(CmdHeadBuf, 2, specialdata))
	{
		while (1)
		{
			RecvInfo.length = ReadOneFrameFromCANBuf_Ext_sub_802B550(&RecvInfo.data[1], 2, specialdata, 1u, timeOut);
			if (!RecvInfo.length)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = -1;
				ans[1] = 2;
				return 2;
			}
			if (specialdata[1] != 0x7F || specialdata[2] != 0x78)
				break;
			timeOut = 5000;
		}
		RecvInfo.data[0] = ++RecvInfo.length;
		memmove(ansHead, RecvInfo.data, RecvInfo.length + 1);
		v8 = &ansHead[RecvInfo.length + 1];
		v9 = RecvInfo.length + 1;
		++RecvInfo.number;
		memmove(CmdHeadBuf, &argv[SendLenPos + 3], argv[SendLenPos] - 2);
		if (CanSendMsg_sub_802B874(CmdHeadBuf, 2, specialdata))
		{
			while (1)
			{
				RecvInfo.length = ReadOneFrameFromCANBuf_Ext_sub_802B550(&RecvInfo.data[1], 2, specialdata, 1u, 500);
				if (!RecvInfo.length)
					break;
				RecvInfo.data[0] = ++RecvInfo.length;
				memmove(v8, RecvInfo.data, RecvInfo.length + 1);
				v8 += RecvInfo.length + 1;
				v9 += RecvInfo.length + 1;
				++RecvInfo.number;
			}
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0;
			ans[1] = RecvInfo.number;
			result = v9 + 2;
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0xFF;
			ans[1] = 2;
			result = 2;
		}
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}




int ID6202_sub_8038974(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int IDNum; // r8
	int argvPos; // r5
	unsigned __int8 *v6; // r4
	unsigned __int8 i; // r10
	size_t result; // r0
	unsigned int j; // r0
	size_t v10; // r7
	int v11; // r6
	unsigned __int8 *v12; // r4
	int v13; // r9
	size_t v14; // r11
	unsigned int v15; // r7
	char v16; // [sp+4h] [bp-54h]
	_BYTE v17[8]; // [sp+5h] [bp-53h]
	__int16 TimeOut; // [sp+Ch] [bp-4Ch]
	__int16 v20; // [sp+10h] [bp-48h]
	unsigned __int8 v21[20]; // [sp+18h] [bp-40h] BYREF

	memset(v21,0, 20u);
	v20 = 0;
	v17[2] = 0;
	*(_WORD *)v17 = *argv;
	IDNum = argv[1];
	if (IDNum >= 5)
		IDNum = 4;
	if (argv[2])
		TimeOut = 10 * argv[2];
	else
		TimeOut = 800;
	argvPos = 7;
	v6 = ans + 3;
	memmove(v21, argv + 7, IDNum + (argv[7] & 0xF) + 1);
	if (argv[3] == 0xAA)
	{
		v21[IDNum + 1] = 48;
		memset(&v21[IDNum + 2], 0, 7);
	}
	else if (argv[3] == 0xFF)
	{
		Copysub_802FB50(v21, CanEnterFrame_2000C47C.data, IDNum + (CanEnterFrame_2000C47C.data[0] & 0xF) + 1);
	}
	else
	{
		v21[IDNum + 1] = 48;
		v21[IDNum + 2] = argv[3];
		*(_WORD *)&v17[1] = argv[3];
		memset(&v21[IDNum + 3], 0, 6);
	}
	set_time0Stop_sub_802BB48();
	for (i = 0; i < (unsigned int)v17[0]; ++i)
	{
		memmove(CmdBuf_2000C554, &argv[argvPos], IDNum + (argv[argvPos] & 0xF) + 1);
		Delay_802EF34(5);
		if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, IDNum, specialdata_2000C670))
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		if ((specialdata_2000C670[0] & 0xF0) == 0x10)
		{
			while (ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], IDNum, specialdata_2000C670, 1u, TimeOut))
			{
				if ((specialdata_2000C670[0] & 0xF0) == 0x30)
					goto LABEL_23;
			}
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			return 2;
		}
	LABEL_23:
		argvPos += argv[argvPos - 3] + 3;
	}
	for (j = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], IDNum, specialdata_2000C670, 1u, TimeOut);
		;
		j = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], IDNum, specialdata_2000C670, 1u, 5000))
	{
		v10 = j;
		if (!j)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = -1;
			ans[1] = 2;
			return 2;
		}
		if ((specialdata_2000C670[0] & 0xF0) == 16)
			break;
		if (specialdata_2000C670[1] != 0x7F || specialdata_2000C670[2] != 0x78)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			memmove(v6, &CmdBuf_2000C554[20], v10);
			*ans = 0;
			ans[1] = 0;
			ans[2] = 1;
			return v10 + 3;
		}
		TimeOut = 5000;
	}
	v11 = 1;
	memmove(v6, &CmdBuf_2000C554[20], j + 1);
	v12 = &v6[v10];
	v13 = v10;
	v16 = 1;
	v14 = IDNum + specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) + 6 - v10;
	do
	{
		if (v16 == 1)
		{
			if (!CanSendMsg_sub_802B874(v21, IDNum, specialdata_2000C670))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = -1;
				ans[1] = 2;
				return 2;
			}
			v16 = 0;
		}
		v15 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], IDNum, specialdata_2000C670, 2u, TimeOut);
		if (!v15)
		{
			if (v11)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0;
				ans[1] = BYTE1(v11);
				ans[2] = v11;
				result = v13 + 3;
			}
			else
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = -1;
				ans[1] = 2;
				result = 2;
			}
			return result;
		}
		if (specialdata_2000C670[0] >= 0x20u)
		{
			++v11;
			if (7 - (IDNum & 1) < v14)
			{
				memmove(v12, &CmdBuf_2000C554[21], v15 - 1);
				v12 = &v12[v15 - 1];
				v13 = v15 + v13 - 1;
				v14 = v14 - v15 + 1;
				if (*(_WORD *)&v17[1])
				{
					if ((unsigned __int16)++v20 >= (unsigned int)*(unsigned __int16 *)&v17[1])
					{
						v20 = 0;
						v16 = 1;
					}
				}
			}
			else
			{
				memmove(v12, &CmdBuf_2000C554[21], v14);
				v12 += v14;
				v13 += v14;
			}
		}
		else if (specialdata_2000C670[0] == 16)
		{
			v16 = 1;
			++v11;
			memmove(v12, &CmdBuf_2000C554[24], v15 - 4);
			v12 = &v12[v15 - 4];
			v13 = v15 + v13 - 4;
			v14 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) - v15 + 2;
		}
	} while (v13 <= 3600);
	v21[(unsigned __int8)(IDNum + 1)] = 50;
	CanSendMsg_sub_802B874(v21, IDNum, specialdata_2000C670);
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	*ans = 0;
	ans[1] = BYTE1(v11);
	ans[2] = v11;
	return v13 + 3;
}



// 64 00 Argv:01 FF 03 09 61 01 04 DE 20 40 02 1A 80 
//            01 FF 03 0A 61 01 05 DE 20 10 03 22 F1 50 81 
int ID6203_sub_80372C8(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v3; // r8
	int v4; // r10
	unsigned __int8 *v5; // r9
	int HeadLen; // r5
	int v7; // r6
	BOOL v8; // r0 MAPDST
	unsigned int i; // r7
	int result; // r0
	unsigned int v11; // r0
	unsigned int Len; // r4
	signed int v13; // r11
	int v15; // [sp+8h] [bp-48h]
	int v16; // [sp+Ch] [bp-44h]
	__int16 v17; // [sp+10h] [bp-40h]
	size_t len; // [sp+14h] [bp-3Ch]
	unsigned int v20; // [sp+1Ch] [bp-34h]

	v3 = 0;
	v16 = 1;
	v4 = 0;
	v5 = ans + 3;
	HeadLen = argv[2];
	v20 = *argv;
	len = argv[3] - 2;
	v7 = 3;
	set_time0Stop_sub_802BB48();
	v8 = argv[4] == 0x61 && argv[5] == 3;
	for (i = 0; i < v20; ++i)
	{
		memset(CmdBuf_2000C554, 0, 20);
		memmove(CmdBuf_2000C554, &argv[v7 + 3], len);// CmdBuf_2000C554 地址的值04 DE 20 40 02 1A 80
		if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, HeadLen, specialdata_2000C670))
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			return 2;
		}
		if ((specialdata_2000C670[0] & 0xF0) == 0x10)
		{
			while (ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], HeadLen, specialdata_2000C670, 1u, 500))
			{
				if ((specialdata_2000C670[0] & 0x30) == 0x30)
					goto LABEL_17;
			}
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			return 2;
		}
	LABEL_17:
		if (DelayTime_2000C53C)
			Delay_802EF34(DelayTime_2000C53C);
		else
			Delay_802EF34(5);
		v7 += argv[v7] + 1;
	}
	if (v8)
	{
		*v5 = 0;
		v5[1] = 0;
		v5[2] = 1;
		v5[3] = 0x55;
		v5[4] = 0xAA;
		v5[5] = 1;
		v5[6] = 0;
		v5[7] = 1;
		result = 8;
	}
	else
	{
		if (TimeOut_2000C530)
		{
			v17 = TimeOut_2000C530;
			v11 = ReadOneFrameFromCANBuf_Ext_sub_802B550(
				&CmdBuf_2000C554[20],
				HeadLen,
				specialdata_2000C670,
				1u,
				TimeOut_2000C530);
		}
		else
		{
			v17 = 500;
			v11 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], HeadLen, specialdata_2000C670, 1u, 500);
		}
		Len = v11;
		if (v11)
		{
			while (1)
			{
			LABEL_30:
				if (v16 != 1)
					goto LABEL_68;
				if ((specialdata_2000C670[0] & 0xF0) == 16)
					break;
				if (specialdata_2000C670[1] != 0x7F || specialdata_2000C670[2] != 0x78)
				{
					memmove(v5, &CmdBuf_2000C554[20], Len);
					v4 += Len;
					++v3;
				LABEL_68:
					*ans = 0;
					ans[1] = 0;
					ans[2] = v3;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return v4 + 3;
				}
				Len = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], HeadLen, specialdata_2000C670, 1u, 20000);
				if (!Len)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = szFBREAK_20004A0C[0];
					ans[1] = szFBREAK_20004A0C[1];
					return 2;
				}
			}
			memmove(v5, &CmdBuf_2000C554[20], Len);
			v4 += Len;
			v5 += Len;
			++v3;
			if (CmdBuf_2000C554[23] >= 8u)
			{
				v15 = 1;
				v13 = HeadLen + specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) + 6 - Len;
				while (1)
				{
					if (v3 - 1 >= (unsigned __int8)CanEnterFrame_2000C47C.data[30]
						&& v3 - 1 == (unsigned __int8)CanEnterFrame_2000C47C.data[30]
						* ((v3 - 1)
							/ (unsigned __int8)CanEnterFrame_2000C47C.data[30])
						&& CanEnterFrame_2000C47C.data[30])
					{
						v15 = 1;
					}
					if (v15 == 1)
					{
						if (*(_DWORD *)dword_2000C668)
							Delay_802EF34(*(int *)dword_2000C668);
						if (!CanSendMsg_sub_802B874((unsigned __int8 *)CanEnterFrame_2000C47C.data, HeadLen, specialdata_2000C670))
						{
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							*ans = szFBREAK_20004A0C[0];
							ans[1] = szFBREAK_20004A0C[1];
							return 2;
						}
					}
					Len = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], HeadLen, specialdata_2000C670, 2u, v17);
					if (!Len)
						break;
					if (CmdBuf_2000C554[20] >= 0x20u)
					{
						v15 = 0;
						++v3;
						if (7 - (HeadLen & 1u) >= v13)
						{
							memmove(v5, &CmdBuf_2000C554[21], v13);
							v5 += v13;
							v4 += v13;
							v16 = 0;
							goto LABEL_30;
						}
						memmove(v5, &CmdBuf_2000C554[21], Len - 1);
						v5 = &v5[Len - 1];
						v4 = Len + v4 - 1;
						v13 = v13 - Len + 1;
					}
					else
					{
						if ((CmdBuf_2000C554[20] & 0xF0) != 16)
						{
							v16 = 0;
							goto LABEL_30;
						}
						v15 = 1;
						++v3;
						memmove(v5, &CmdBuf_2000C554[24], Len - 4);
						v5 = &v5[Len - 4];
						v4 = Len + v4 - 4;
						v13 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) - Len + 2;
					}
				}
				if (v13 < 1)
				{
					v16 = 0;
					goto LABEL_30;
				}
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = szFBREAK_20004A0C[0];
				ans[1] = szFBREAK_20004A0C[1];
				result = 2;
			}
			else
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0;
				ans[1] = 0;
				ans[2] = v3;
				result = v4 + 3;
			}
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			result = 2;
		}
	}
	return result;
}




int ID6204_sub_8037934(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v3; // r8
	int v4; // r10
	unsigned __int8 *AnsHead; // r9
	unsigned int v8; // r7
	char v9; // r0
	int v10; // r5
	unsigned int v11; // r0
	unsigned int i; // r6
	unsigned int v13; // r4
	unsigned __int8 v14; // r8
	int v15; // r10
	unsigned __int8 *v16; // r9
	unsigned int v17; // r4
	unsigned __int8 v18; // r8
	int v19; // r10
	unsigned __int8 *v20; // r9
	unsigned int v21; // r4
	unsigned int v22; // r0
	char v23; // [sp+4h] [bp-64h]
	char v24; // [sp+6h] [bp-62h]
	char v25; // [sp+7h] [bp-61h]
	unsigned __int8 v26; // [sp+8h] [bp-60h]
	unsigned __int8 v27; // [sp+9h] [bp-5Fh]
	unsigned __int8 v28; // [sp+Ah] [bp-5Eh]
	unsigned __int8 v29; // [sp+Bh] [bp-5Dh]
	unsigned __int8 v30; // [sp+Ch] [bp-5Ch]
	unsigned __int8 len; // [sp+Dh] [bp-5Bh]
	unsigned __int8 v32; // [sp+Eh] [bp-5Ah]
	unsigned __int8 v33; // [sp+Fh] [bp-59h]
	unsigned __int8 CmdHeadID[4]; // [sp+18h] [bp-50h] BYREF
	unsigned int v35; // [sp+1Ch] [bp-4Ch]
	unsigned int v37; // [sp+24h] [bp-44h]
	unsigned int v38; // [sp+28h] [bp-40h]
	int v39; // [sp+2Ch] [bp-3Ch]
	unsigned __int8 CmdHeadBuf[12]; // [sp+30h] [bp-38h] BYREF
	unsigned __int8 *v42; // [sp+40h] [bp-28h]

	argc = 0;
	v38 = 0;
	v39 = 0;
	v35 = 0;
	v37 = 0;
	v3 = 0;
	v25 = 0;
	v24 = 0;
	v23 = 0;
	*(_DWORD *)CmdHeadID = 1;
	*(_DWORD *)CmdHeadBuf = 0xA1000006;
	*(_DWORD *)&CmdHeadBuf[4] = 0x32FF8A0F;
	*(_DWORD *)&CmdHeadBuf[8] = 0xFF;
	v29 = 0xFF;
	v33 = 0;
	v28 = 0;
	v27 = 0;
	v4 = 0;
	AnsHead = ans + 2;
	v42 = argv + 1;
	memset(CmdBuf_2000C554, 0, 0x14);
	v30 = *v42;
	v35 = v42[2] + (v42[1] << 8);
	*(_WORD *)&CmdHeadID[1] = *(_WORD *)(v42 + 3);
	*(_WORD *)&CmdHeadBuf[1] = *(_WORD *)(v42 + 3);
	CmdBuf_2000C554[1] = v42[5];
	CmdBuf_2000C554[2] = v42[6];
	if (!v35)
	{
		*ans = 0xFF;
		ans[1] = 2;
		return 2;
	}
	set_time0Stop_sub_802BB48();
	v8 = v35 / 0xF;
	v26 = v35 % 0xF;
	if (v26)
		++v8;
	argc -= 8;
	if (argc >= 8 * v35)
		v9 = 8;
	else
		v9 = argc - 8 * (v35 - 1);
	len = v9;
	v10 = 7;
	while (2)
	{
		if (!v8)
		{
			v39 = 0x2710;
			v38 = 0;
			if (!byte_2000C6BB)
			{
				byte_2000C6BB = 1;
				v23 = 1;
			}
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			while (1)
			{
				while (1)
				{
					while (1)
					{
						while (1)
						{
							v13 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x15], 2u, specialdata_2000C670, 2u, v39);
							if (!v13)
							{
								if (timer_open_flag_2000C6B7 == 1)
									TIM_sub_802EEEC(0);
								if (v23 == 1)
									byte_2000C6BB = 0;
								*ans = 0xFF;
								ans[1] = 2;
								return 2;
							}
							v32 = CmdBuf_2000C554[0x16];
							if (v13 != 6 || CmdBuf_2000C554[0x15] != 0xA1)
								break;
							if ((unsigned __int8)++v24 >= 0x1Fu)
							{
								if (timer_open_flag_2000C6B7 == 1)
									TIM_sub_802EEEC(0);
								if (v23 == 1)
									byte_2000C6BB = 0;
								*ans = 0xFF;
								ans[1] = 2;
								return 2;
							}
						}
						v24 = 0;
						if ((CmdBuf_2000C554[0x15] & 0x10) == 0)
							break;
						v29 = 0xFF;
						CmdHeadID[3] = (CmdBuf_2000C554[0x15] + 1) & 0xF | 0xB0;
						Delay_802EF34(1);
						if (!SetCan_sub_802B9DE(CmdHeadID, 2, specialdata_2000C670))
						{
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							if (v23 == 1)
								byte_2000C6BB = 0;
							*ans = 0xFF;
							ans[1] = 2;
							return 2;
						}
						if (CmdBuf_2000C554[0x18] != 0x7F || CmdBuf_2000C554[0x1A] != 0x78)
						{
							if (v33 == 0xFF)
							{
								if (timer_open_flag_2000C6B7 == 1)
									TIM_sub_802EEEC(0);
								v14 = v3 + 1;
								CmdBuf_2000C554[0x14] = v13;
								memmove(AnsHead, &CmdBuf_2000C554[0x14], v13 + 1);
								v15 = v13 + v4 + 1;
								if (v30 == 1)
								{
									v16 = &AnsHead[v13 + 1];
									v17 = ReadOneFrameFromCANBuf_Ext_sub_802B550(
										&CmdBuf_2000C554[0x15],
										2u,
										specialdata_2000C670,
										2u,
										0x14u);
									if (v17 == 6 && CmdBuf_2000C554[0x15] == 0xA1)
										v17 = ReadOneFrameFromCANBuf_Ext_sub_802B550(
											&CmdBuf_2000C554[0x15],
											2u,
											specialdata_2000C670,
											2u,
											0x14u);
									if (v17)
									{
										CmdBuf_2000C554[0x14] = v17;
										memmove(v16, &CmdBuf_2000C554[0x14], v17 + 1);
										++v14;
										v15 += v17 + 1;
									}
								}
								*ans = 0;
								ans[1] = v14;
								if (v23 == 1)
									byte_2000C6BB = 0;
								return v15 + 2;
							}
							if (v28 == 0xFF)
							{
								++v3;
								CmdBuf_2000C554[0x14] = v13;
								memmove(AnsHead, &CmdBuf_2000C554[0x14], v13 + 1);
								AnsHead += v13 + 1;
								v4 += v13 + 1;
								v28 = 0;
							}
							else
							{
								if ((v32 & 0xF0) == 0)
								{
									if (timer_open_flag_2000C6B7 == 1)
										TIM_sub_802EEEC(0);
									v18 = v3 + 1;
									CmdBuf_2000C554[0x14] = v13;
									memmove(AnsHead, &CmdBuf_2000C554[0x14], v13 + 1);
									v19 = v13 + v4 + 1;
									if (v30 == 1)
									{
										v20 = &AnsHead[v13 + 1];
										v21 = ReadOneFrameFromCANBuf_Ext_sub_802B550(
											&CmdBuf_2000C554[0x15],
											2u,
											specialdata_2000C670,
											2u,
											0x14u);
										if (v21 == 6 && CmdBuf_2000C554[0x15] == 0xA1)
											v21 = ReadOneFrameFromCANBuf_Ext_sub_802B550(
												&CmdBuf_2000C554[0x15],
												2u,
												specialdata_2000C670,
												2u,
												0x14u);
										if (v21)
										{
											CmdBuf_2000C554[0x14] = v21;
											memmove(v20, &CmdBuf_2000C554[0x14], v21 + 1);
											++v18;
											v19 += v21 + 1;
										}
									}
									*ans = 0;
									ans[1] = v18;
									if (v23 == 1)
										byte_2000C6BB = 0;
									return v19 + 2;
								}
								++v3;
								CmdBuf_2000C554[0x14] = v13;
								memmove(AnsHead, &CmdBuf_2000C554[0x14], v13 + 1);
								AnsHead += v13 + 1;
								v4 += v13 + 1;
								if (v27 == 0xFF)
								{
									if (timer_open_flag_2000C6B7 == 1)
										TIM_sub_802EEEC(0);
									*ans = 0;
									ans[1] = v3;
									if (v23 == 1)
										byte_2000C6BB = 0;
									return v4 + 2;
								}
							}
						}
					}
					if ((CmdBuf_2000C554[0x15] & 0x20) != 0)
						break;
					if ((CmdBuf_2000C554[0x15] & 0xF0) == 0)
						v27 = 0xFF;
					CmdHeadID[3] = (CmdBuf_2000C554[0x15] + 1) & 0xF | 0xB0;
					Delay_802EF34(1);
					if (!SetCan_sub_802B9DE(CmdHeadID, 2, specialdata_2000C670))
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						if (v23 == 1)
							byte_2000C6BB = 0;
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
					v22 = v38++;
					if (v22 >= 0xB)
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						if (v23 == 1)
							byte_2000C6BB = 0;
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
				LABEL_112:
					++v3;
					CmdBuf_2000C554[0x14] = v13;
					memmove(AnsHead, &CmdBuf_2000C554[0x14], v13 + 1);
					AnsHead += v13 + 1;
					v4 += v13 + 1;
				}
				if ((CmdBuf_2000C554[0x15] & 0x80) == 0)
				{
					v25 = 0;
					v27 = 0;
					v28 = 0xFF;
					if (v29 == 0xFF)
					{
						v29 = 0;
						if ((CmdBuf_2000C554[0x16] & 0xF0) == 0)
							v33 = 0xFF;
					}
					goto LABEL_112;
				}
				if ((unsigned __int8)++v25 >= 0x14u)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					if (v23 == 1)
						byte_2000C6BB = 0;
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				if (!SetCan_sub_802B9DE(CmdHeadBuf, 2, specialdata_2000C670))
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					if (v23 == 1)
						byte_2000C6BB = 0;
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
			}
		}
		if (v8 == 1 && v26)
			v11 = v26;
		else
			v11 = 0xF;
		v37 = v11;
		for (i = 0; i < v37; ++i)
		{
			if (v8 == 1 && i == v37 - 1)
			{
				CmdBuf_2000C554[0] = len;
				memmove(&CmdBuf_2000C554[3], &v42[v10], len);
			}
			else
			{
				CmdBuf_2000C554[0] = 8;
				memmove(&CmdBuf_2000C554[3], &v42[v10], 8u);
			}
			if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, 2, specialdata_2000C670))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			if (DelayTime_2000C53C)
				Delay_802EF34(DelayTime_2000C53C);
			else
				Delay_802EF34(5);
			v10 += 8;
		}
		if (ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x15], 2u, specialdata_2000C670, 1u, 0x1F4u))
		{
			--v8;
			continue;
		}
		break;
	}
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	*ans = 0xFF;
	ans[1] = 2;
	return 2;
}


// Funtion:
// Input  : argc - 参数长度
//          argv - 数据格式
//          0x62 + 0x05 + 长度 + 内容 + ID高位 + ID 低位
// Output : ans - 回复到上位机的数据。
// Return : 回复到上位机的数据长度
// Info   : 6205
// 注意的问题:在接受多帧的时候没有发送流控制命令。
//Req:05 EA 20 10 00 02 1A 9B
//Ans:01 60 00 B1
//Ans:08 60 00 20 00 30 5a 9b 34 46 30
//Ans:08 60 00 21 39 31 30 35 35 32 53
//Ans:08 60 00 22 20 20 30 30 31 30 10
//Ans:08 60 00 23 00 00 00 02 32 15 ec
//Ans:08 60 00 24 10 d6 32 2e 34 6c 20
//Ans:08 60 00 25 56 36 20 4d 50 49 20
//Ans:08 60 00 26 20 20 20 20 20 20 20
//Ans:02 60 00 17 20
//Req:01 EA 20 B8
//目前实现的功能是:
//1.在接受到0x10的时候发送确认帧.并且不保存接受数据
//2.2012-12-19进行了返回接受数据的修改.
//上位机接受缓冲区的数据格式是:
//10,55,aa,0c,61,01,07,e8,00,10,00,04,31,b8,00,00,1e(校验位),e8,00,60,
int ID6205_VWCANSendDataToEcuGetMultiFrameAnswer1_1_sub_803814C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v3; // r7
	unsigned int v4; // r10
	int v5; // r9
	unsigned __int8 *v7; // r8
	int result; // r0
	int v9; // r4
	unsigned __int8 *v10; // r8
	unsigned int v11; // r4
	unsigned int v12; // r5
	int v13; // r9
	int v14; // r9
	unsigned int v15; // r0
	unsigned __int8 v16; // [sp+4h] [bp-54h]
	char v17; // [sp+5h] [bp-53h]
	unsigned __int8 v18; // [sp+6h] [bp-52h]
	unsigned __int8 v19; // [sp+7h] [bp-51h]
	unsigned __int8 v20; // [sp+8h] [bp-50h]
	unsigned __int8 v21; // [sp+9h] [bp-4Fh]
	__int16 v22; // [sp+Ah] [bp-4Eh]
	__int16 v23; // [sp+Ch] [bp-4Ch]
	unsigned __int8 CONFIG_FRAME[4]; // [sp+14h] [bp-44h] BYREF
	int send_length; // [sp+18h] [bp-40h]
	int v26; // [sp+1Ch] [bp-3Ch]
	unsigned __int8 VW_MULTI_FRM[16]; // [sp+20h] [bp-38h] BYREF
	unsigned __int8 *v28; // [sp+30h] [bp-28h]

	*(_DWORD *)&VW_MULTI_FRM[0xC] = argc;
	v28 = argv;
	send_length = 0;
	v26 = 0;
	v3 = 0;
	LOWORD(v4) = 0;
	*(_DWORD *)CONFIG_FRAME = 1;
	*(_DWORD *)VW_MULTI_FRM = 0xA1000006;
	*(_DWORD *)&VW_MULTI_FRM[4] = 0x32FF8A0F;
	*(_DWORD *)&VW_MULTI_FRM[8] = 0xFF;
	v19 = 0xFF;
	v21 = 0;
	v18 = 0;
	v17 = 0;
	v16 = 0;
	v5 = 0;
	v7 = ans + 2;
	send_length = *argv;
	v23 = argv[5] + (argv[4] << 8);
	*(_WORD *)&CONFIG_FRAME[1] = *(_WORD *)&argv[send_length + 1];
	*(_WORD *)&VW_MULTI_FRM[1] = *(_WORD *)&argv[send_length + 1];
	if (!send_length)
	{
		*ans = 0xFF;
		ans[1] = 2;
		return 2;
	}
	set_time0Stop_sub_802BB48();
	memset(CmdBuf_2000C554, 0, 0x14);
	memmove(CmdBuf_2000C554, v28 + 6, v28[6] + 3);
	if (DelayTime_2000C53C)
		Delay_802EF34(DelayTime_2000C53C);
	else
		Delay_802EF34(0xA);
	if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, 2, specialdata_2000C670))
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 2;
		return 2;
	}
	if (!ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x15], 2u, specialdata_2000C670, 1u, 0x1F4u))
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 2;
		return 2;
	}
	if (v23 == 0x6111)
	{
		if (CmdBuf_2000C554[0x18] != 7)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		v9 = CmdBuf_2000C554[0x17];
		v22 = CmdBuf_2000C554[CmdBuf_2000C554[0x17] + 0x15] + (CmdBuf_2000C554[CmdBuf_2000C554[0x17] + 0x16] << 8);
		memmove(CmdBuf_2000C554, &v28[v28[3] + 9], v28[v28[3] + 9] + 3);
		v22 *= 0x20;
		CmdBuf_2000C554[1] = HIBYTE(v22);
		CmdBuf_2000C554[2] = v22;
		v3 = 1;
		*v7 = v9 - 3;
		v10 = v7 + 1;
		memmove(v10, &CmdBuf_2000C554[0x1B], v9 - 3);
		v7 = &v10[v9 - 3];
		v5 = v9 - 2;
		if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, 2, specialdata_2000C670))
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
	}
	v26 = 0x5DC;
	v11 = 0;
	while (1)
	{
		while (1)
		{
			while (1)
			{
				v12 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x15], 2u, specialdata_2000C670, 2u, v26);
				if (!v12)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					if (v17 == 1)
					{
						v13 = *v7 + 1 + v5;
						*ans = 0;
						ans[1] = v3 + 1;
						result = v13 + 2;
					}
					else
					{
						*ans = 0xFF;
						ans[1] = 2;
						result = 2;
					}
					return result;
				}
				if (v23 == 0x6111)
				{
					CmdBuf_2000C554[0x14] = v12;
					memmove(v7, &CmdBuf_2000C554[0x14], v12 + 1);
					v14 = v12 + v5 + 1;
					*ans = 0;
					ans[1] = v3 + 1;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return v14 + 2;
				}
				v20 = CmdBuf_2000C554[0x16];
				v17 = 0;
				if ((CmdBuf_2000C554[0x15] & 0x10) == 0)
					break;
				v19 = 0xFF;
				CONFIG_FRAME[3] = (CmdBuf_2000C554[0x15] + 1) & 0xF | 0xB0;
				Delay_802EF34(1);
				if (!CanSendMsg_sub_802B874(CONFIG_FRAME, 2, specialdata_2000C670))
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				if (CmdBuf_2000C554[0x18] == 0x7F && CmdBuf_2000C554[0x1A] == 0x78)
				{
					if (CmdBuf_2000C554[0x16] == 0x80 && CmdBuf_2000C554[0x19] == 0x21)
					{
						v17 = 1;
						v26 = 0x1F4;
						CmdBuf_2000C554[0x14] = v12;
						memmove(v7, &CmdBuf_2000C554[0x14], v12 + 1);
					}
				}
				else
				{
					if (v21 == 0xFF)
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
					LABEL_48:
						CmdBuf_2000C554[0x14] = v12;
						memmove(v7, &CmdBuf_2000C554[0x14], v12 + 1);
						*ans = 0;
						ans[1] = v3 + 1;
						return v12 + v5 + 3;
					}
					if (v18 == 0xFF)
					{
						++v3;
						CmdBuf_2000C554[0x14] = v12;
						memmove(v7, &CmdBuf_2000C554[0x14], v12 + 1);
						v7 += v12 + 1;
						v5 += v12 + 1;
						v18 = 0;
					}
					else
					{
						if ((v20 & 0xF0) == 0)
						{
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							goto LABEL_48;
						}
						++v3;
						CmdBuf_2000C554[0x14] = v12;
						memmove(v7, &CmdBuf_2000C554[0x14], v12 + 1);
						v7 += v12 + 1;
						v5 += v12 + 1;
						if (v16 == 0xFF)
						{
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							*ans = 0;
							ans[1] = v3;
							return v5 + 2;
						}
					}
				}
			}
			if ((CmdBuf_2000C554[0x15] & 0x20) == 0)
				break;
			if ((CmdBuf_2000C554[0x15] & 0x80) == 0)
			{
				LOWORD(v4) = 0;
				v16 = 0;
				v18 = 0xFF;
				if (v19 == 0xFF)
				{
					v19 = 0;
					if ((CmdBuf_2000C554[0x16] & 0xF0) == 0)
						v21 = 0xFF;
				}
				goto LABEL_74;
			}
			v4 = (unsigned __int16)(v4 + 1);
			if (v4 >= 0x14)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			if (!CanSendMsg_sub_802B874(VW_MULTI_FRM, 2, specialdata_2000C670))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
		}
		if ((CmdBuf_2000C554[0x15] & 0xF0) == 0)
			v16 = 0xFF;
		CONFIG_FRAME[3] = (CmdBuf_2000C554[0x15] + 1) & 0xF | 0xB0;
		Delay_802EF34(1);
		if (!CanSendMsg_sub_802B874(CONFIG_FRAME, 2, specialdata_2000C670))
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		v15 = v11++;
		if (v15 >= 0xB)
			break;
	LABEL_74:
		++v3;
		CmdBuf_2000C554[0x14] = v12;
		memmove(v7, &CmdBuf_2000C554[0x14], v12 + 1);
		v7 += v12 + 1;
		v5 += v12 + 1;
	}
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	*ans = 0xFF;
	ans[1] = 2;
	return 2;
}





int ID6206_sub_802892A(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v5; // r6
	int result; // r0
	int argvPos; // r11
	int v8; // r8
	int v9; // r0
	int v10; // r11
	int v11; // r7
	int v12; // r0
	int v13; // r11
	int v14; // r0
	int v15; // r7
	int v16; // r0
	int v17; // r11
	int v18; // r7
	unsigned __int8 v19; // r9
	unsigned __int8 v20; // r10
	int v21; // r10
	char v22; // r9
	int v23; // r8
	unsigned __int8 RecvByte; // [sp+0h] [bp-38h] BYREF
	unsigned __int8 RcvFrameNum; // [sp+1h] [bp-37h]
	int v26; // [sp+4h] [bp-34h]
	int DelayMs; // [sp+8h] [bp-30h]
	int v28; // [sp+10h] [bp-28h]

	v28 = argc;
	v5 = 0;
	if (!*argv)
		ExitFlag_2000C6BA = 1;
	DelayMs = argv[2] + (argv[1] << 8);
	IOCTRLSelect_sub_8030606(1u, 0);
	IOCTRLSet_sub_8030658(0, DelayMs);
	IOCTRLSet_sub_8030658(1, 0);
	ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	RcvFrameNum = argv[3];
	if (RcvFrameNum)
	{
		set_time0Stop_sub_802BB48();
		argvPos = 4;
		v8 = 2;
		while (1)
		{
			v9 = argv[argvPos];
			v10 = argvPos + 1;
			v11 = v9;
			if (!v9)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 1;
				return 2;
			}
			while (1)
			{
				v12 = v11--;
				if (v12 < 2)
					break;
				ComSendByte_sub_802F1E0(argv[v10++]);
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			ComSendByte_sub_802F1E0(argv[v10]);
			v13 = v10 + 1;
			v14 = argv[v13];
			argvPos = v13 + 1;
			v15 = v14;
			if (v14)
				break;
			v16 = argv[argvPos];
			v17 = argvPos + 1;
			v18 = v16;
			if (v16)
			{
				v19 = 0;
				v20 = argv[v17];
				argvPos = v17 + 1;
				v26 = v8++;
				do
				{
					if (!ComByte_sub_802F6CC(&RecvByte, 0x1F4))
					{
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
					ans[v8++] = RecvByte;
					++v19;
					--v18;
				} while (v18 >= 1);
				RecvByte -= v20;
				RecvByte -= v19;
				v21 = RecvByte;
				do
				{
					if (!ComByte_sub_802F6CC(&RecvByte, 0x1F4))
					{
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
					ans[v8++] = RecvByte;
					++v19;
					--v21;
				} while ((_BYTE)v21);
				ans[v26] = v19;
			}
			else
			{
				argvPos = v17 + 1;
				v22 = 0;
				v26 = v8;
				v23 = v8 + 1;
				do
				{
					if (!ComByte_sub_802F6CC(&RecvByte, 0x1F4))
					{
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
					ans[v23++] = RecvByte;
					++v22;
				} while (RecvByte);
				if (!ComByte_sub_802F6CC(&RecvByte, 0x12C))
				{
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				ans[v23] = RecvByte;
				v8 = v23 + 1;
				ans[v26] = v22 + 1;
			}
		LABEL_35:
			Delay_802EF34(5);
			if (++v5 >= (unsigned int)RcvFrameNum)
			{
				*ans = 0;
				ans[1] = v5;
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return v8;
			}
		}
		ans[v8++] = v14;
		while (ComByte_sub_802F6CC(&RecvByte, 0x320))
		{
			ans[v8++] = RecvByte;
			if (--v15 < 1)
				goto LABEL_35;
		}
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	else
	{
		*ans = 0xFF;
		ans[1] = 1;
		result = 2;
	}
	return result;
}



int ID6207_sub_8039C8C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v4; // r11
	int send_number; // r5
	int v6; // r9
	int id_number; // r7
	unsigned __int8 i; // r10
	int result; // r0
	int v11; // r9
	unsigned int v12; // r6
	size_t v13; // r6
	unsigned __int8 v14; // [sp+4h] [bp-34h]
	__int16 time; // [sp+8h] [bp-30h]

	v4 = 0;
	time = 500;
	v14 = argv[1];
	send_number = *argv;
	v6 = 7;
	id_number = 2;
	if ((argv[7] & 0x80) != 0)
		id_number = 4;
	set_time0Stop_sub_802BB48();
	for (i = 0; i < (unsigned int)v14; ++i)
	{
		memmove(CmdBuf_2000C554, &argv[v6], id_number + (argv[v6] & 0xF) + 1);
		if ((CmdBuf_2000C554[0] & 0x80) != 0)
			id_number = 4;
		else
			id_number = 2;
		if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, id_number, specialdata_2000C670))
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = -1;
			ans[1] = 2;
			return 2;
		}
		if ((specialdata_2000C670[0] & 0xF0) == 16)
		{
			while (ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], id_number, specialdata_2000C670, 1u, 500))
			{
				if ((specialdata_2000C670[0] & 0xF0) == 48)
					goto LABEL_18;
			}
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			return 2;
		}
	LABEL_18:
		v6 += id_number + (argv[v6] & 0xF) + 7;
		Delay_802EF34(DelayTime_2000C53C);
	}
	v11 = 2;
	ans[1] = send_number;
	while (send_number)
	{
		v12 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[20], id_number, specialdata_2000C670, 1u, time);
		if (!v12)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			if (v4)
			{
				*ans = 0;
				result = v4 + 3;
			}
			else
			{
				*ans = -1;
				ans[1] = 2;
				result = 2;
			}
			return result;
		}
		if (specialdata_2000C670[1] == 0x7F && specialdata_2000C670[2] == 0x78)
		{
			time = 5000;
		}
		else
		{
			time = 500;
			v13 = v12 + 1;
			--send_number;
			memmove(&ans[v11], &CmdBuf_2000C554[20], v13);
			v11 += v13;
			v4 += v13;
		}
	}
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	if (v4)
	{
		*ans = 0;
		result = v4 + 2;
	}
	else
	{
		*ans = -1;
		ans[1] = 2;
		result = 2;
	}
	return result;
}





int ID6208_sub_8021008(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int v5; // r9
	unsigned __int8 i; // r4
	unsigned __int8 v7; // r11
	int result; // r0
	unsigned __int8 AnsPos; // r10
	int v10; // r0
	unsigned __int8 v11; // r11
	int v12; // r8
	unsigned __int16 v13; // r0
	__int16 v14; // r7
	int v15; // r10
	unsigned __int8 v16; // [sp+0h] [bp-50h]
	unsigned __int8 v17; // [sp+1h] [bp-4Fh] BYREF
	unsigned __int8 v18; // [sp+2h] [bp-4Eh]
	unsigned __int8 send_number; // [sp+3h] [bp-4Dh]
	unsigned __int8 v20[32]; // [sp+4h] [bp-4Ch] BYREF

	v17 = 0;
	LOBYTE(v5) = 0;
	send_number = 0;
	v18 = 0;
	i = 0;
	memset(v20,0, 0x20u);
	set_time0Stop_sub_802BB48();
	if (!*argv)
		ExitFlag_2000C6BA = 1;
	send_number = argv[1];
	v18 = argv[2];
	v7 = 4;
	v16 = argv[3];
	if (v16)
	{
		*ans = 0;
		ans[1] = v16;
		AnsPos = 2;
		do
		{
			v10 = argv[v7];
			v11 = v7 + 1;
			v12 = v10;
			if (!(_WORD)v10)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
			LABEL_33:
				PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
				return 2;
			}
			if (!SetTIM_sub_802F58C(0x1F4))
				goto LABEL_33;
			while (1)
			{
				v13 = v12--;
				if (v13 < 2u)
					break;
				ComSendByte_sub_802F1E0(argv[v11++]);
				Delay_sub_802EF46(0x80u);
			}
			ComSendByte_sub_802F1E0(argv[v11]);
			v7 = v11 + 1;
			v14 = 0x14;
			while (2)
			{
				if (v14)
				{
					for (i = 0; i < 0x20u; v20[i++] = v17)
					{
						if (i)
						{
							if (!ComByte_sub_802F6CC(&v17, 2))
								break;
						}
						else if (!ComByte_sub_802F6CC(&v17, 0x1F4))
						{
							if (timer_open_flag_2000C6B7 == 1)
								TIM_sub_802EEEC(0);
							goto LABEL_33;
						}
					}
					if (v20[0] != send_number || v20[1] != v18)
					{
						--v14;
						continue;
					}
					ans[AnsPos] = i;
					v15 = (unsigned __int8)(AnsPos + 1);
					Copysub_802FB50(&ans[v15], v20, i);
					AnsPos = i + v15;
				}
				break;
			}
			if (i >= 2u && !v14)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				goto LABEL_33;
			}
			Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
			v5 = (unsigned __int8)(v5 + 1);
		} while (v5 < v16);
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = AnsPos;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
		result = 2;
	}
	return result;
}




int ID6209_sub_802B168(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r9
	int v6; // r10
	int v7; // r11
	int v9; // r7
	int v10; // r0
	int v11; // r7
	int v12; // r10
	unsigned __int8 v13; // r6
	int v14; // r0
	int v15; // r7
	unsigned __int8 v16; // r8
	unsigned __int8 Rcvbyte; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 Delay; // [sp+1h] [bp-2Fh]
	int v19; // [sp+8h] [bp-28h]

	v19 = argc;
	Delay = 0;
	v5 = 0;
	set_time0Stop_sub_802BB48();
	v6 = *argv;
	v7 = 1;
	if (!*argv)
		return 2;
	*ans = 0;
	ans[1] = 1;
	v9 = 2;
	while (1)
	{
		v10 = v6--;
		if (v10 < 2)
			break;
		ComSendByte_sub_802F1E0(argv[v7++]);
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	ComSendByte_sub_802F1E0(argv[v7]);
	Delay = 10 * argv[v7 + 1];
	while (1)
	{
		if (!ComByte_sub_802F6CC(&Rcvbyte, Delay))
			return 2;
		v11 = v9 + 1;
		v12 = Rcvbyte;
		v13 = Rcvbyte;
		if (Rcvbyte == 72)
			break;
		ans[v11] = Rcvbyte;
		v9 = v11 + 1;
		v5 += Rcvbyte;
		while (1)
		{
			v14 = v12--;
			if (v14 < 1)
				break;
			if (!ComByte_sub_802F6CC(&Rcvbyte, 300))
				return 2;
			ans[v9++] = Rcvbyte;
			v5 += Rcvbyte;
			if (!v12)
			{
				ans[2] = v13 + 2;
				ans[v9] = v5;
				return v9 + 1;
			}
		}
	}
	ans[v11] = Rcvbyte;
	v15 = v11 + 1;
	v16 = 1;
	while (ComByte_sub_802F6CC(&Rcvbyte, 60))
	{
		++v16;
		ans[v15++] = Rcvbyte;
	}
	ans[2] = v16;
	return v15;
}




int ID620A_sub_8028592(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r8
	int result; // r0
	int v7; // r9
	unsigned __int8 i; // r10
	int v9; // r0
	unsigned __int8 RecvByte[40]; // [sp+0h] [bp-28h] BYREF

	v5 = 3;
	RecvByte[0] = 0;
	if (*argv == 17)
	{
		set_time0Stop_sub_802BB48();
		ComSendByte_sub_802F1E0(0x11u);
		if (ComByte_sub_802F6CC(RecvByte, 500))
		{
			if (RecvByte[0] == 0x11)
			{
				if (argv[1] == 0x80)
				{
					Delay_802EF34(13);
					ComSendByte_sub_802F1E0(0x80u);
					v7 = argv[2];
					*ans = 0;
					ans[1] = 1;
					ans[2] = v7;
					for (i = 0; i < 2u; ++i)
					{
						if (!ComByte_sub_802F6CC(RecvByte, 500))
						{
							*ans = -1;
							ans[1] = 2;
							return 2;
						}
						ComSendByte_sub_802F1E0(RecvByte[0]);
					}
					while (1)
					{
						v9 = v7--;
						if (v9 < 1)
							break;
						if (!ComByte_sub_802F6CC(RecvByte, 500))
						{
							*ans = -1;
							ans[1] = 2;
							return 2;
						}
						ans[v5++] = RecvByte[0];
						ComSendByte_sub_802F1E0(RecvByte[0]);
					}
					if (ComByte_sub_802F6CC(RecvByte, 500))
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						result = v5;
					}
					else
					{
						*ans = -1;
						ans[1] = 2;
						result = 2;
					}
				}
				else
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = -1;
					ans[1] = 0;
					result = 2;
				}
			}
			else
			{
				*ans = -1;
				ans[1] = 2;
				result = 2;
			}
		}
		else
		{
			*ans = -1;
			ans[1] = 2;
			result = 2;
		}
	}
	else
	{
		*ans = -1;
		ans[1] = 0;
		result = 2;
	}
	return result;
}




int ID620B_LandroverSendAndReceiveFault_1_sub_8028D14(int a1, unsigned __int8 *a2, _BYTE *ans)
{
	unsigned int v5; // r0
	unsigned __int8 i; // r7
	int result; // r0
	unsigned __int8 v8; // r8
	unsigned __int8 v9; // r7
	unsigned __int8 v10; // r7
	unsigned __int8 v11; // r8
	unsigned __int8 v12; // r7
	unsigned __int8 RecvByte[32]; // [sp+0h] [bp-20h] BYREF

	set_time0Stop_sub_802BB48();
	v5 = *a2;
	if (v5 == 1)
	{
		ComClose_sub_80B1D06_sub_802FA28(1);
		for (i = 0; i < 3u; ++i)
		{
			IOCTRLSelect_sub_8030606(1u, 0);
			IOCTRLSet_sub_8030658(1, 0x64);
			IOCTRLSet_sub_8030658(0, 0x64);
			IOCTRLSet_sub_8030658(1, 0);
			SC_com_portMode_20004964.BaudRate = 0x2580;
			SC_com_portMode_20004964.StopBits = 0;
			SC_com_portMode_20004964.WordLength = 0x1000;
			SC_com_portMode_20004964.Parity = 0x400;
			ComOpen_sub_80B1AEC_802F7DE(3, &SC_com_portMode_20004964);
			if (ComByte_sub_802F6CC(RecvByte, 2500) == 1 && RecvByte[0] == 0xFF)
				break;
		}
		if (i == 3)
		{
			for (i = 0; i < 3u; ++i)
			{
				ComSend_sub_802F3A4(0, 0);
				if (ComByte_sub_802F6CC(RecvByte, 0x154) == 1)
					break;
			}
		}
		if (i == 3)
		{
			*ans = 0xFF;
			ans[1] = 2;
			result = 2;
		}
		else
		{
			ans[1] = RecvByte[0];
			Delay_802EF34(0x34);
			ComSend_sub_802F3A4(0xAAu, 0);
			if (ComByte_sub_802F6CC(RecvByte, 0x154))
			{
				*ans = 0;
				ans[2] = RecvByte[0];
				if (timer_open_flag_2000C6B7 == 2)
					TIM_sub_802EEEC(0);
				result = 3;
			}
			else
			{
				*ans = 0xFF;
				ans[1] = 2;
				result = 2;
			}
		}
	}
	else
	{
		if (!*a2)
		{
		LABEL_43:
			*ans = 0xFF;
			ans[1] = 1;
			if (timer_open_flag_2000C6B7 == 2)
				TIM_sub_802EEEC(0);
			return 2;
		}
		if (v5 == 3)
		{
			v11 = 1;
			v12 = 2;
			while (a2[1])
			{
				ComSend_sub_802F3A4(a2[v12++], 0);
				--a2[1];
				if (!ComByte_sub_802F6CC(RecvByte, 0x154))
				{
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				ans[v11++] = RecvByte[0];
				Delay_802EF34(0xA);
			}
			*ans = 0;
			if (timer_open_flag_2000C6B7 == 2)
				TIM_sub_802EEEC(0);
			result = v11;
		}
		else
		{
			if (v5 >= 3)
				goto LABEL_43;
			if ((a2[1] & 1) != 0)
			{
				*ans = 0xFF;
				ans[1] = 2;
				result = 2;
			}
			else
			{
				v8 = 1;
				v9 = 2;
				Delay_802EF34(0x32);
				while (a2[1])
				{
					ComSend_sub_802F3A4(a2[v9], 1);
					v10 = v9 + 1;
					--a2[1];
					if (!ComByte_sub_802F6CC(RecvByte, 0x154))
					{
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
					Delay_802EF34(6);
					ComSend_sub_802F3A4(a2[v10], 0);
					v9 = v10 + 1;
					--a2[1];
					if (!ComByte_sub_802F6CC(RecvByte, 0x154))
					{
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
					ans[v8++] = RecvByte[0];
					Delay_802EF34(0x32);
				}
				*ans = 0;
				if (timer_open_flag_2000C6B7 == 2)
					TIM_sub_802EEEC(0);
				result = v8;
			}
		}
	}
	return result;
}




int ID620C_sub_8039EB0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int v5; // r8
	int v6; // r10
	int v7; // r7
	int v8; // r10
	int v11; // r7
	unsigned __int8 v12; // r9
	unsigned __int8 specialdata[4]; // [sp+4h] [bp-64h] BYREF
	unsigned __int8 v14[3]; // [sp+8h] [bp-60h] BYREF
	_BYTE v15[29]; // [sp+Bh] [bp-5Dh] BYREF
	unsigned __int8 RcvData[64]; // [sp+28h] [bp-40h] BYREF

	v5 = 0x1F4;
	set_time0Stop_sub_802BB48();
	v6 = argv[1] + (*argv << 8);
	v14[1] = argv[2];
	v14[2] = argv[3];
	v14[0] = argv[4];
	Copysub_802FB50(v15, argv + 5, v14[0]);
	v7 = v14[0] + 5;
	CanSendMsg_sub_802B874(v14, 2, specialdata);
	v8 = v6 - 1;
	if (!v8)
		goto LABEL_9;
	do
	{
		if (!ReadOneFrameFromCANBuf_Ext_sub_802B550(RcvData, 2u, specialdata, 0, 0x7D0u))
		{
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
	} while (specialdata[0] != 0x30);
	while (v8--)
	{
		v14[0] = argv[v7];
		v11 = v7 + 1;
		Copysub_802FB50(v15, &argv[v11], v14[0]);
		v7 = v14[0] + v11;
		if (DelayTime_2000C53C)
			Delay_802EF34(DelayTime_2000C53C);
		CanSendMsg_sub_802B874(v14, 2, specialdata);
	}
	while (1)
	{
	LABEL_9:
		v12 = ReadOneFrameFromCANBuf_Ext_sub_802B550(RcvData, 2u, specialdata, 1u, v5);
		if (!v12)
		{
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		if (specialdata[1] != 0x7F || specialdata[2] != 0x78)
			break;
		v5 = 0x1388;
	}
	memmove(ans + 3, RcvData, v12);
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	*ans = 0;
	ans[1] = 0;
	ans[2] = 1;
	return v12 + 3;
}




int ID620E_sub_8028F84(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int v5; // r0
	unsigned __int8 i; // r8
	int result; // r0
	unsigned __int8 v8; // r9
	unsigned __int8 v9; // r8
	unsigned __int8 v10; // r0
	unsigned __int8 v11; // r9
	unsigned __int8 v12; // r8
	unsigned __int8 v13; // r0
	unsigned __int8 AnsPos; // r9
	unsigned __int8 v15; // r8
	unsigned __int8 v16; // r0
	unsigned __int8 v17[32]; // [sp+0h] [bp-20h] BYREF

	set_time0Stop_sub_802BB48();
	v5 = *argv;
	if (v5 == 1)
	{
		ComClose_sub_80B1D06_sub_802FA28(1);
		for (i = 0; i < 3u; ++i)
		{
			IOCTRLSelect_sub_8030606(1u, 0);
			IOCTRLSet_sub_8030658(1, 0x64);
			IOCTRLSet_sub_8030658(0, 0x64);
			IOCTRLSet_sub_8030658(1, 0);
			SC_com_portMode_20004964.BaudRate = 0x2580;
			SC_com_portMode_20004964.StopBits = 0;
			SC_com_portMode_20004964.WordLength = 0x1000;
			SC_com_portMode_20004964.Parity = 0x400;
			ComOpen_sub_80B1AEC_802F7DE(3, &SC_com_portMode_20004964);
			if (ComByte_sub_802F6CC(v17, 0x9C4) == 1 && v17[0] == 0xFF)
				break;
		}
		if (i == 3)
		{
			for (i = 0; i < 3u; ++i)
			{
				ComSend_sub_802F3A4(0, 0);
				if (ComByte_sub_802F6CC(v17, 0x154) == 1)
					break;
			}
		}
		if (i == 3)
		{
			*ans = 0xFF;
			ans[1] = 2;
			result = 2;
		}
		else
		{
			ans[1] = v17[0];
			Delay_802EF34(0x34);
			ComSend_sub_802F3A4(0xAAu, 0);
			if (ComByte_sub_802F6CC(v17, 0x154))
			{
				*ans = 0;
				ans[2] = v17[0];
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				result = 3;
			}
			else
			{
				*ans = 0xFF;
				ans[1] = 2;
				result = 2;
			}
		}
		return result;
	}
	if (!*argv)
		goto LABEL_54;
	if (v5 == 3)
	{
		v11 = 1;
		v12 = 0;
		argv[1] = 0x20;
		while (1)
		{
			v13 = argv[1];
			argv[1] = v13 - 1;
			if (!v13)
				break;
			Delay_802EF34(0x32);
			ComSend_sub_802F3A4(0xF1u, 1);
			if (!ComByte_sub_802F6CC(v17, 0x154))
			{
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			Delay_802EF34(6);
			ComSend_sub_802F3A4(v12++, 0);
			if (!ComByte_sub_802F6CC(v17, 0x154))
			{
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			ans[v11++] = v17[0];
		}
		*ans = 0;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = v11;
	}
	else
	{
		if (v5 < 3)
		{
			v8 = 1;
			v9 = 0;
			argv[1] = 0x2F;
			while (1)
			{
				v10 = argv[1];
				argv[1] = v10 - 1;
				if (!v10)
					break;
				Delay_802EF34(0x32);
				ComSend_sub_802F3A4(0xF0u, 1);
				if (!ComByte_sub_802F6CC(v17, 0x154))
				{
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				Delay_802EF34(6);
				ComSend_sub_802F3A4(v9++, 0);
				if (!ComByte_sub_802F6CC(v17, 0x154))
				{
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				ans[v8++] = v17[0];
			}
			*ans = 0;
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			return v8;
		}
		if (v5 != 4)
		{
		LABEL_54:
			*ans = 0xFF;
			ans[1] = 1;
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			return 2;
		}
		AnsPos = 1;
		v15 = 0xFF;
		argv[1] = 1;
		while (1)
		{
			v16 = argv[1];
			argv[1] = v16 - 1;
			if (!v16)
				break;
			Delay_802EF34(0x32);
			ComSend_sub_802F3A4(0xF3u, 1);
			if (!ComByte_sub_802F6CC(v17, 0x154))
			{
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			Delay_802EF34(6);
			ComSend_sub_802F3A4(v15++, 0);
			if (!ComByte_sub_802F6CC(v17, 0x154))
			{
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			ans[AnsPos++] = v17[0];
		}
		*ans = 0;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = AnsPos;
	}
	return result;
}





int ID620F_sub_8028B98(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r7
	int v6; // r8
	char v7; // r11
	int v8; // r10
	int result; // r0
	int v10; // r0
	int v11; // r8
	int v12; // r9
	unsigned __int8 v13; // r0
	int i; // r7
	unsigned __int8 v15[40]; // [sp+0h] [bp-28h] BYREF

	v5 = 2;
	v6 = 1;
	v7 = 1;
	set_time0Stop_sub_802BB48();
	v8 = *argv;
	if ((_BYTE)v8)
	{
		while (1)
		{
			v10 = argv[v6];
			v11 = v6 + 1;
			v12 = v10;
			if (!(_BYTE)v10)
				break;
			while (1)
			{
				v13 = v12--;
				if (v13 < 2u)
					break;
				ComSendByte_sub_802F1E0(argv[v11++]);
				if (!ComByte_sub_802F6CC(v15, 0x5DC))
				{
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			ComSendByte_sub_802F1E0(argv[v11]);
			v6 = v11 + 1;
			do
			{
				if (!ComByte_sub_802F6CC(v15, 0x3E8))
				{
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				ComSendByte_sub_802F1E0(v15[0]);
				if (v15[0] == 1)
				{
					if (!ComByte_sub_802F6CC(v15, 0x3E8))
					{
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
					if (v15[0] != 0x80)
					{
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
				}
				else
				{
					ans[v5] = v15[0];
					for (i = v5 + 1; ; ++i)
					{
						if (!ComByte_sub_802F6CC(v15, 0x1F4))
						{
							*ans = 0xFF;
							ans[1] = 2;
							return 2;
						}
						if (v15[0] == 0x80)
							break;
						ans[i] = v15[0];
						ComSendByte_sub_802F1E0(v15[0]);
					}
					ans[i] = v15[0];
					v5 = i + 1;
					v7 = 0;
				}
			} while (v7 == 1);
			Delay_802EF34(5);
			if (!(_BYTE)--v8)
			{
				*ans = 0;
				ans[1] = v5 - 2;
				return v5;
			}
		}
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 1;
		result = 2;
	}
	else
	{
		*ans = 0xFF;
		ans[1] = 1;
		result = 2;
	}
	return result;
}



int ID6210_sub_8026480(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v4; // r7
	unsigned __int8 v5; // r8
	int v6; // r9
	unsigned __int8 v7; // r10
	unsigned __int8 *AnsHead; // r11
	unsigned int i; // r5
	unsigned int j; // r6
	int v11; // r6
	unsigned int v13; // [sp+0h] [bp-40h] BYREF
	unsigned __int8 SpeciData[2]; // [sp+8h] [bp-38h] BYREF
	unsigned __int8 *v16; // [sp+Ch] [bp-34h]
	int v17; // [sp+10h] [bp-30h]
	unsigned int v18; // [sp+14h] [bp-2Ch]
	int v19; // [sp+18h] [bp-28h]

	v19 = argc;
	v18 = argv[1];
	v17 = 0;
	v4 = 2;
	v16 = receive_buff_2000BF20;
	v13 = 0;
	*(_WORD *)SpeciData = 0;
	v5 = 0;
	v6 = 0;
	v7 = 0;
	AnsHead = ans + 2;
	set_time0Stop_sub_802BB48();
	for (i = 0; i < v18; ++i)
	{
		v17 = argv[v4 + 1] + (argv[v4] << 8);
		for (j = 0; j < v17 - 1; ++j)
		{
			ComSendByte_sub_802F1E0(argv[j + 2 + v4]);
			v7 += argv[j + 2 + v4];
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(v7);
		v7 = 0;
		v11 = SC_TagKWP2000_20004974.m_Maxwaittime;
		while (1)
		{
			if (!ReceiveOneKwpFrameFromECU_sub_802E188(v16 + 1, &v13, SC_TagKWP2000_20004974.m_Maxwaittime, SpeciData))
			{
				memset(AnsHead, 0, 4);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			if (SpeciData[0] != 0x7F || SpeciData[1] != 0x78)
				break;
			SC_TagKWP2000_20004974.m_Maxwaittime = 0x1388;
		}
		SC_TagKWP2000_20004974.m_Maxwaittime = v11;
		v4 += v17 + 2;
		*v16 = v13;
		memmove(AnsHead, v16, v13 + 1);
		++v5;
		AnsHead += v13 + 1;
		v6 += v13 + 1;
		if (i != v18 - 1)
			Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
	}
	*ans = 0;
	ans[1] = v5;
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return v6 + 2;
}



int ID6211_sub_80265D8(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v3; // r7
	unsigned __int8 v4; // r10
	int v5; // r11
	unsigned __int8 *v6; // r4
	__int16 v7; // r6
	unsigned int i; // r5
	int result; // r0
	unsigned int j; // r5
	int v11; // r9
	int v12; // r8
	char v14; // r0
	int v16; // [sp+4h] [bp-34h]

	v16 = *argv;
	v3 = 0;
	v4 = 0;
	v5 = 0;
	v6 = ans + 2;
	set_time0Stop_sub_802BB48();
	v7 = 10 * CalculateTimeOut_sub_802CC3E(argv[v16 + 1], 0xAu);
	for (i = 0; i < v16 - 1; ++i)
	{
		ComSendByte_sub_802F1E0(argv[i + 1]);
		v4 += argv[i + 1];
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	ComSendByte_sub_802F1E0(v4);
LABEL_5:
	if (ComByte_sub_802F6CC(&receive_buff_2000BF20[1], v7))
	{
		j = 2;
		if (receive_buff_2000BF20[1] == 128)
		{
			for (j = 2; j < 5; ++j)
				ComByte_sub_802F6CC(&receive_buff_2000BF20[j], v7);
			v11 = receive_buff_2000BF20[j - 1] + 1;
			v12 = receive_buff_2000BF20[j - 1] + 5;
		}
		else if (receive_buff_2000BF20[1] < 0x81u)
		{
			v11 = (receive_buff_2000BF20[1] & 0x7F) + 1;
			v12 = (receive_buff_2000BF20[1] & 0x7F) + 2;
		}
		else
		{
			v11 = (receive_buff_2000BF20[1] & 0x7F) + 2;
			v12 = (receive_buff_2000BF20[1] & 0x7F) + 3;
		}
		do
		{
			if (!v11--)
			{
				receive_buff_2000BF20[0] = v12;
				memmove(v6, receive_buff_2000BF20, v12 + 1);
				v6 += v12 + 1;
				v5 += v12 + 1;
				++v3;
				goto LABEL_5;
			}
			v14 = ComByte_sub_802F6CC(&receive_buff_2000BF20[j++], v7);
		} while (v14);
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = -1;
		ans[1] = 2;
		result = 2;
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0;
		ans[1] = v3;
		result = v5 + 2;
	}
	return result;
}




int ID6212_sub_8038E0C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v3; // r8
	int v5; // r10
	unsigned __int8 *v6; // r9
	int result; // r0
	unsigned int v8; // r4
	int v9; // r7
	signed int v10; // r11
	int v11; // r6
	int v12; // [sp+4h] [bp-5Ch]
	unsigned __int8 FlowControl[16]; // [sp+Ch] [bp-54h] BYREF
	unsigned __int8 v14[16]; // [sp+1Ch] [bp-44h] BYREF
	int v15; // [sp+34h] [bp-2Ch]
	unsigned __int8 *v16; // [sp+38h] [bp-28h]

	v15 = argc;
	v16 = argv;
	v3 = 0;
	v12 = 1;
	*(_DWORD *)FlowControl = 0x30000008;
	*(_DWORD *)&FlowControl[4] = 0;
	*(_DWORD *)&FlowControl[8] = 0;
	v5 = 0;
	v6 = ans + 3;
	set_time0Stop_sub_802BB48();
	memmove(v14, v16 + 6, 11u);
	*(_WORD *)&FlowControl[1] = *(_WORD *)&v14[1];
	Delay_802EF34(5);
	if (CanSendMsg_sub_802B874(v14, 2, specialdata_2000C670))
	{
		v8 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], 0, specialdata_2000C670, 1u, 0x1F4u);
		if (v8)
		{
			while (1)
			{
			LABEL_9:
				if (v12 != 1)
					goto LABEL_39;
				if ((specialdata_2000C670[0] & 0xF0) == 0x10)
					break;
				if (specialdata_2000C670[1] != 0x7F || specialdata_2000C670[2] != 0x78)
				{
					memmove(v6, &CmdBuf_2000C554[0x14], v8);
					v5 += v8;
					++v3;
				LABEL_39:
					*ans = 0;
					ans[1] = 0;
					ans[2] = v3;
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					return v5 + 3;
				}
				v8 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], 0, specialdata_2000C670, 1u, 0x1388u);
				if (!v8)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = szFBREAK_20004A0C[0];
					ans[1] = szFBREAK_20004A0C[1];
					return 2;
				}
			}
			memmove(v6, &CmdBuf_2000C554[0x14], v8);
			v5 += v8;
			v9 = (specialdata_2000C670[1] + (specialdata_2000C670[0] & 0xF)) / 7;
			if ((specialdata_2000C670[1] + (specialdata_2000C670[0] & 0xF)) % 7)
				++v9;
			v10 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) + 6 - v8;
			v6 += v8;
			++v3;
			v11 = 1;
			while (1)
			{
				if (v11 == 1 && !CanSendMsg_sub_802B874(FlowControl, 2, specialdata_2000C670))
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = szFBREAK_20004A0C[0];
					ans[1] = szFBREAK_20004A0C[1];
					return 2;
				}
				v8 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], 0, specialdata_2000C670, 2u, 0x1F4u);
				if (!v8)
					break;
				if (CmdBuf_2000C554[0x14] >= 0x20u)
				{
					v11 = 0;
					++v3;
					if (v10 >= 8)
					{
						memmove(v6, &CmdBuf_2000C554[0x15], v8 - 1);
						v6 = &v6[v8 - 1];
						v5 = v8 + v5 - 1;
						v10 = v10 - v8 + 1;
					}
					else
					{
						memmove(v6, &CmdBuf_2000C554[0x15], v10);
						v6 += v10;
						v5 += v10;
					}
				}
				else
				{
					if ((CmdBuf_2000C554[0x14] & 0xF0) != 0x10)
					{
						v12 = 0;
						goto LABEL_9;
					}
					++v3;
					v11 = 1;
					memmove(v6, &CmdBuf_2000C554[0x18], v8 - 4);
					v6 = &v6[v8 - 4];
					v5 = v8 + v5 - 4;
					v10 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) - v8 + 2;
				}
				if (v3 >= v9)
				{
					v12 = 0;
					goto LABEL_9;
				}
			}
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			result = 2;
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			result = 2;
		}
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}



int ID6213_sub_802675C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v4; // r6
	int v6; // r11
	unsigned __int8 *v7; // r8
	int v8; // r9
	unsigned int i; // r10
	int result; // r0
	unsigned int j; // r10
	unsigned __int8 v12; // [sp+0h] [bp-40h]
	unsigned __int8 v13[2]; // [sp+2h] [bp-3Eh] BYREF
	unsigned int v14; // [sp+4h] [bp-3Ch] BYREF
	int v15; // [sp+8h] [bp-38h]
	int v16; // [sp+Ch] [bp-34h]
	_BYTE v17[4]; // [sp+10h] [bp-30h] BYREF
	unsigned __int8 v18; // [sp+14h] [bp-2Ch]
	int v19; // [sp+18h] [bp-28h]

	v19 = argc;
	v15 = 0;
	v4 = 0;
	v14 = 0;
	v6 = 0;
	*(_WORD *)v13 = 0;
	v7 = ans + 2;
	v8 = argv[1] + (*argv << 8);
	v15 = argv[2];
	v16 = 0xA * CalculateTimeOut_sub_802CC3E(argv[v15 + 3], 0xAu);
	set_time0Stop_sub_802BB48();
	v12 = argv[4];
	for (i = 0; i < v15 - 1; ++i)
	{
		ComSendByte_sub_802F1E0(argv[i + 3]);
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	ComSendByte_sub_802F1E0(argv[i + 3]);
	do
	{
		while (1)
		{
			if (!ReceiveOneKwpFrameFromECU_sub_802E188(&receive_buff_2000BF20[1], &v14, v16, v13))
			{
				if (v4)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = 0;
					ans[1] = v4;
					result = v6 + 2;
				}
				else
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = 0xFF;
					ans[1] = 2;
					result = 2;
				}
				return result;
			}
			if (v13[0] == 0x7F)
				break;
			v16 = 0xA * CalculateTimeOut_sub_802CC3E(argv[v15 + 3], 0xAu);
			++v4;
			receive_buff_2000BF20[0] = v14;
			if (v14 + v6 > 0xE10)
			{
				ans[1] = v4 - 1;
				return v6 + 2;
			}
			v6 += v14 + 1;
			memmove(v7, receive_buff_2000BF20, v14 + 1);
			v7 += v14 + 1;
		}
		v16 = 0x1388;
		--v8;
	} while (v8);
	if (v4)
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0;
		ans[1] = v4;
		result = v6 + 2;
	}
	else
	{
		v17[0] = 0x81;
		v17[1] = v12;
		v17[2] = 0xF0;
		v17[3] = 0x82;
		v18 = v12 - 0xD;
		for (j = 0; j < 4; ++j)
		{
			ComSendByte_sub_802F1E0((unsigned __int8)v17[j]);
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(v18);
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0;
		ans[1] = 0;
		result = 2;
	}
	return result;
}



int ID6217_sub_8039144(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	char v5; // r9
	int v6; // r10
	unsigned int timeOut; // r6
	BOOL v8; // r7
	int result; // r0
	int v10; // r0
	int v11; // r10
	int v12; // r10
	int v13; // r10
	unsigned __int8 v14; // r9
	char v15; // [sp+4h] [bp-64h]
	unsigned __int8 v16; // [sp+4h] [bp-64h]
	unsigned __int8 v17; // [sp+4h] [bp-64h]
	unsigned __int8 v18; // [sp+4h] [bp-64h]
	unsigned __int8 v19; // [sp+6h] [bp-62h]
	unsigned __int8 v20; // [sp+7h] [bp-61h]
	unsigned __int8 v21; // [sp+8h] [bp-60h]
	unsigned __int8 RcvBuf[4]; // [sp+Ah] [bp-5Eh] BYREF
	_BYTE v23[18]; // [sp+Eh] [bp-5Ah] BYREF
	unsigned __int8 SpeciData[4]; // [sp+20h] [bp-48h] BYREF
	unsigned __int8 v25[4]; // [sp+24h] [bp-44h] BYREF
	unsigned __int8 FlowControl[4]; // [sp+28h] [bp-40h] BYREF
	unsigned __int8 v27; // [sp+2Ch] [bp-3Ch]
	unsigned __int8 v28; // [sp+2Eh] [bp-3Ah]
	unsigned __int8 v29[55]; // [sp+31h] [bp-37h] BYREF

	*(_DWORD *)v25 = 1;
	*(_DWORD *)FlowControl = 0x30000001;
	*(_DWORD *)SpeciData = 0;
	v5 = 0;
	v6 = 0;
	timeOut = 0x1F4;
	set_time0Stop_sub_802BB48();
	v20 = 4;
	v19 = 3;
	v27 = *argv;
	v28 = 3;
	*(_WORD *)&v25[1] = argv[1];
	FlowControl[1] = argv[1];
	v25[2] = argv[2];
	FlowControl[2] = argv[2];
	v15 = 0;
	do
	{
		if (SC_TagKWP2000_20004974.m_nFrameTime < 0xB)
			Delay_802EF34(2);
		else
			Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		memmove(v29, &argv[v28 + 6], argv[v28] - 6);
		CanSendMsg_sub_802B874(v29, 2, SpeciData);
		v8 = argv[7] == 0x61 && argv[8] == 3;
		argv += argv[v28] + 1;
		--v27;
	} while (v27);
	if (v8)
	{
		*ans = 0xFF;
		ans[1] = 0;
		result = 2;
	}
	else
	{
		while (1)
		{
			while (1)
			{
				v21 = ReadOneFrameFromCANBuf_Ext_sub_802B550(RcvBuf, 2u, SpeciData, 3u, timeOut);
				if (!v21)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				v10 = RcvBuf[3] & 0x30;
				if ((RcvBuf[3] & 0x30) == 0)
					break;
				switch (v10)
				{
				case 0x10:
					v25[3] = ((RcvBuf[3] & 0xF) + 1) | 0xB0;
					memmove(&ans[v20], v23, RcvBuf[0] - 1);
					v12 = RcvBuf[0] - 1 + v6;
					v17 = v15 + 1;
					ans[v19] = RcvBuf[0] - 1 + v5;
					CanSendMsg_sub_802B874(v25, 2, SpeciData);
					Delay_802EF34(0x32);
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = 0;
					ans[1] = 0;
					ans[2] = v17;
					return v17 + v12 + 3;
				case 0x20:
					if ((RcvBuf[3] & 0xF0) == 0xA0)
					{
						memmove(&ans[v20], RcvBuf, RcvBuf[0] - 1);
						v13 = RcvBuf[0] - 1 + v6;
						v18 = v15 + 1;
						ans[v19] = RcvBuf[0] - 1 + v5;
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						*ans = 0;
						ans[1] = 0;
						ans[2] = v18;
						return v18 + v13 + 3;
					}
					memmove(&ans[v20], v23, RcvBuf[0] - 1);
					v5 += RcvBuf[0] - 1;
					v20 += RcvBuf[0] - 1;
					v6 += RcvBuf[0] - 1;
					timeOut = 0x1F4;
					break;
				case 0x30:
					if (v23[3] == 0x7F && v23[5] == 0x78)
					{
						v5 = 0;
						CanSendMsg_sub_802B874(FlowControl, 2, SpeciData);
						timeOut = 0x1388;
					}
					else
					{
						memmove(&ans[v20], v23, RcvBuf[0] - 1);
						v14 = RcvBuf[0] - 1 + v5;
						ans[v19] = v14;
						v6 += RcvBuf[0] - 1;
						v20 += RcvBuf[0];
						v19 += v14 + 1;
						v5 = 0;
						++v15;
						CanSendMsg_sub_802B874(FlowControl, 2, SpeciData);
						timeOut = 0x1F4;
					}
					break;
				}
			}
			if (!v5)
				break;
			v25[3] = ((RcvBuf[3] & 0xF) + 1) | 0xB0;
			memmove(&ans[v20], v23, RcvBuf[0] - 1);
			v5 += RcvBuf[0] - 1;
			v6 += RcvBuf[0] - 1;
			v20 += RcvBuf[0] - 1;
			CanSendMsg_sub_802B874(v25, 2, SpeciData);
			Delay_802EF34(0x32);
			timeOut = 0x1F4;
		}
		memmove(&ans[v20], RcvBuf, v21 - 4);
		ans[v19] = v21 - 4;
		v11 = v21 - 3 + v6;
		v16 = v15 + 1;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0;
		ans[1] = 0;
		ans[2] = v16;
		result = v11 + 3;
	}
	return result;
}




int ID6218_sub_80286E4(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r7
	int v6; // r8
	int result; // r0
	int v8; // r11
	int v10; // r0
	int v11; // r11
	int v12; // r9
	unsigned __int8 v13; // r0
	int v14; // r6
	int v15; // r7
	unsigned __int8 v16; // r10
	unsigned __int8 v17[8]; // [sp+0h] [bp-30h] BYREF
	int v18; // [sp+8h] [bp-28h]

	v18 = argc;
	v5 = 2;
	set_time0Stop_sub_802BB48();
	v6 = argv[1];
	if ((_BYTE)v6)
	{
		v8 = 2;
		while ((_BYTE)v6--)
		{
			v10 = argv[v8];
			v11 = v8 + 1;
			v12 = v10;
			if (!(_BYTE)v10)
			{
				*ans = -1;
				ans[1] = 2;
				return 2;
			}
			while (1)
			{
				v13 = v12--;
				if (v13 < 2u)
					break;
				ComSendByte_sub_802F1E0(argv[v11++]);
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			ComSendByte_sub_802F1E0(argv[v11]);
			v8 = v11 + 1;
			v14 = v5;
			v15 = v5 + 1;
			if (!ComByte_sub_802F6CC(v17, SC_TagKWP2000_20004974.m_Maxwaittime))
			{
				*ans = -1;
				ans[1] = 2;
				return 2;
			}
			v16 = 1;
			ans[v15] = v17[0];
			v5 = v15 + 1;
			do
			{
				if (!ComByte_sub_802F6CC(v17, 500))
				{
					*ans = -1;
					ans[1] = 2;
					return 2;
				}
				ans[v5] = v17[0];
				++v16;
				++v5;
			} while (v17[0] != 13);
			ans[v14] = v16;
		}
		*ans = 0;
		ans[1] = argv[1];
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = v5;
	}
	else
	{
		*ans = -1;
		ans[1] = 2;
		result = 2;
	}
	return result;
}




int ID6219_sub_804D740(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	CAN_DeInit_sub_80348F4(&CAN1_BASE_40006400);
	CAN_DeInit_sub_80348F4(&CAN2_BASE_40006800);
	*ans = -1;
	ans[1] = 0;
	return 2;
}



int ID621F_sub_802694C(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned int v3 = 0; // r6
	int v5; // r7
	unsigned __int8 v6; // r8
	int v7; // r9
	unsigned int v8; // r11
	unsigned __int8 *v9; // r4
	int v10; // r5
	unsigned int v11; // r0
	unsigned int i; // r10
	int v13; // r9
	unsigned int j; // r6
	unsigned __int8 v16[2]; // [sp+0h] [bp-78h] BYREF
	char v17; // [sp+2h] [bp-76h]
	unsigned __int8 v18[5]; // [sp+3h] [bp-75h] BYREF
	unsigned __int8 *v19; // [sp+8h] [bp-70h]
	int v20; // [sp+Ch] [bp-6Ch]
	int v21; // [sp+10h] [bp-68h]
	unsigned __int8 v22[52]; // [sp+14h] [bp-64h] BYREF
	int v23; // [sp+4Ch] [bp-2Ch]
	unsigned __int8 *v24; // [sp+50h] [bp-28h]

	v23 = argc;
	v24 = argv;
	v21 = 0;
	v18[0] = 0;
	v20 = 0;
	v5 = 0;
	*(_DWORD *)&v18[1] = 0;
	v6 = 0;
	v19 = ans;
	v7 = 0;
	*(_WORD *)v16 = 0;
	LOBYTE(v8) = 0;
	memset(v22, 0,0x34u);
	v17 = 0;
	v9 = ans + 2;
	*(_DWORD *)v18 = v24[1];
	v10 = 2;
	v20 = SC_TagKWP2000_20004974.m_Maxwaittime;
	set_time0Stop_sub_802BB48();
	if (ComByte_sub_802F6CC(v22, 0) == 1)
	{
		do
		{
			if (ComByte_sub_802F6CC(v22, 5) != 1)
				break;
			v11 = v3++;
		} while (v11 < 0x33);
	}
	while (2)
	{
		v21 = v24[v10];
		for (i = 0; i < v21 - 1; ++i)
		{
			ComSendByte_sub_802F1E0(v24[i + 1 + v10]);
			v6 += v24[i + 1 + v10];
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(v6);
		v6 = 0;
		while (ReceiveOneKwpFrameFromECU_sub_802E188(&receive_buff_2000BF20[1], (unsigned int *)&v18[1], v20, v16))
		{
			v17 = 0;
			if (v16[0] == 0x7F)
			{
				switch (v16[1])
				{
				case 0x21u:
					goto LABEL_26;
				case 0x23u:
					v20 = 0x7D0;
					memset(v22, 0, 0x32);
					receive_buff_2000BF20[0] = v18[1];
					for (j = 0; j < *(_DWORD *)&v18[1] + 1; ++j)
						v22[j] = receive_buff_2000BF20[j];
					v17 = 1;
					break;
				case 0x78u:
					v20 = 0x1388;
					break;
				case 0xA0u:
				LABEL_26:
					v8 = (unsigned __int8)(v8 + 1);
					if (v8 >= 0x15)
					{
						LOBYTE(v8) = 0;
						++v5;
						receive_buff_2000BF20[0] = v18[1];
						memmove(v9, receive_buff_2000BF20, *(_DWORD *)&v18[1] + 1);
						v9 += *(_DWORD *)&v18[1] + 1;
						v7 += *(_DWORD *)&v18[1] + 1;
						v10 += v24[v10] + 1;
					}
					break;
				default:
					++v5;
					receive_buff_2000BF20[0] = v18[1];
					memmove(v9, receive_buff_2000BF20, *(_DWORD *)&v18[1] + 1);
					v9 += *(_DWORD *)&v18[1] + 1;
					v7 += *(_DWORD *)&v18[1] + 1;
					v10 += v24[v10] + 1;
					break;
				}
			}
			if (v16[0] != 0x7F || v16[1] != 0x78 && v16[1] != 0x23)
				goto LABEL_35;
		}
		if (v17)
		{
			v13 = v22[0] + 1;
			Copysub_802FB50(v9, v22, v13);
			*v19 = 0;
			v19[1] = v5 + 1;
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			return v13 + 2;
		}
		if (v16[0] == 0x7F && v16[1] == 0x23)
		{
			LOBYTE(v5) = v5 + 1;
			memmove(v9, v22, *(_DWORD *)&v18[1] + 1);
			v9 += *(_DWORD *)&v18[1] + 1;
			v7 += *(_DWORD *)&v18[1] + 1;
			v10 += v24[v10] + 1;
		LABEL_35:
			if ((v16[0] != 0x7F || v16[1] != 0x23)
				&& (v16[0] != 0x7F || v16[1] != 0x21)
				&& (v16[0] != 0x7F || v16[1] != 0xA0))
			{
				v20 = SC_TagKWP2000_20004974.m_Maxwaittime;
				LOBYTE(v5) = v5 + 1;
				receive_buff_2000BF20[0] = v18[1];
				memmove(v9, receive_buff_2000BF20, *(_DWORD *)&v18[1] + 1);
				v9 += *(_DWORD *)&v18[1] + 1;
				v7 += *(_DWORD *)&v18[1] + 1;
				v10 += v24[v10] + 1;
			}
			v5 = (unsigned __int8)v5;
			if ((unsigned __int8)v5 >= (unsigned int)v18[0])
			{
				*v19 = 0;
				v19[1] = v5;
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				return v7 + 2;
			}
			continue;
		}
		break;
	}
	*v19 = 0xFF;
	v19[1] = 2;
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return 2;
}




int ID6220_KWP_SendDataToEcuGetAnswer_Benz_1_sub_8026C32(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v4; // r11
	unsigned __int8 check_byte; // r8
	unsigned int v6; // r10
	unsigned __int8 *Ans; // r7
	int time; // r6
	unsigned int i; // r9
	int v10; // r9
	int result; // r0
	size_t receive_length; // [sp+0h] [bp-38h] BYREF
	unsigned __int8 *v13; // [sp+4h] [bp-34h]
	unsigned __int8 speci_data[2]; // [sp+8h] [bp-30h] BYREF
	int v15; // [sp+Ch] [bp-2Ch]
	int v16; // [sp+10h] [bp-28h]

	v16 = argc;
	v15 = 0;
	v4 = 0;
	receive_length = 0;
	check_byte = 0;
	v13 = ans;
	v6 = 0;
	*(_WORD *)speci_data = 0;
	Ans = ans + 2;
	v15 = *argv;
	time = 0xA * CalculateTimeOut_sub_802CC3E(argv[v15 + 1], 0xAu);
	set_time0Stop_sub_802BB48();
LABEL_2:
	for (i = 0; i < v15 - 1; ++i)
	{
		ComSendByte_sub_802F1E0(argv[i + 1]);
		check_byte += argv[i + 1];
		Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
	}
	ComSendByte_sub_802F1E0(check_byte);
	check_byte = 0;
	v10 = time;
	while (1)
	{
		if (!ReceiveOneKwpFrameFromECU_sub_802E188(&receive_buff_2000BF20[1], &receive_length, time, speci_data))
		{
			if (v4 && !receive_length)
			{
				*v13 = 0;
				v13[1] = v4;
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				result = v6 + 2;
			}
			else
			{
				*v13 = 0xFF;
				v13[1] = 0;
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				result = 2;
			}
			return result;
		}
		if (v6 > 0xE10)
			break;
		if (speci_data[0] == 0x7F)
		{
			if (speci_data[1] == 0x78 || speci_data[1] == 0x23)
			{
				time = 0x1388;
			}
			else if (speci_data[1] == 0x21)
			{
				goto LABEL_2;
			}
		}
		else
		{
			time = v10;
			++v4;
			receive_buff_2000BF20[0] = receive_length++;
			memmove(Ans, receive_buff_2000BF20, receive_length);
			Ans += receive_length;
			v6 += receive_length;
		}
	}
	*v13 = 0;
	v13[1] = v4;
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return v6 + 2;
}




int ID6221_KWP_SendDataToEcuGetMultiFrameAnswer_Benz_1_sub_80287F4(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r10
	int result; // r0
	int v7; // r9
	int v8; // r0
	int v9; // r8
	int v10; // r10
	int v12; // r8
	int v13; // r9
	int v14; // r9
	__int16 Delay; // r7
	int v16; // r8
	unsigned __int8 Rcvbyte[40]; // [sp+0h] [bp-28h] BYREF

	set_time0Stop_sub_802BB48();
	v5 = *argv;
	if (*argv)
	{
		v7 = 0;
		while (ComByte_sub_802F6CC(Rcvbyte, 2) == 1)
		{
			v8 = v7++;
			if (v8 == 10)
			{
				*ans = -1;
				ans[1] = 2;
				return 2;
			}
		}
		v9 = 1;
		v10 = v5 - 1;
		while (v10--)
		{
			ComSendByte_sub_802F1E0(argv[v9++]);
			Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
		}
		ComSendByte_sub_802F1E0(argv[v9]);
		v12 = v9 + 1;
		v13 = argv[v12] << 8;
		v14 = argv[++v12] + v13;
		Delay = 10 * CalculateTimeOut_sub_802CC3E(argv[v12 + 1], 0xAu);
		v16 = 3;
		if (v14)
		{
			while (v14 && ComByte_sub_802F6CC(Rcvbyte, Delay))
			{
				ans[v16++] = Rcvbyte[0];
				--v14;
			}
		}
		else
		{
			do
			{
				if (!ComByte_sub_802F6CC(Rcvbyte, Delay))
					break;
				ans[v16++] = Rcvbyte[0];
			} while (v16 <= 3600);
		}
		*ans = 0;
		ans[1] = 1;
		ans[2] = v16 - 3;
		if (v16 == 3)
		{
			*ans = -1;
			ans[1] = 2;
			result = 2;
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			result = v16;
		}
	}
	else
	{
		*ans = -1;
		ans[1] = 1;
		result = 2;
	}
	return result;
}



int ID6222_SendOneFrameToEcuGetMultiFrameAnswer_1_sub_803A008(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v5; // r9
	bool v6; // r11
	unsigned __int16 v7; // r7
	unsigned __int16 v8; // r8
	unsigned __int16 i; // r5
	unsigned __int16 v11; // r0 MAPDST
	unsigned __int16 v12; // r8
	unsigned __int16 j; // r6
	int v14; // r7
	unsigned __int16 k; // r6
	int v16; // r7
	unsigned __int8 v17; // [sp+8h] [bp-50h]
	__int16 v18; // [sp+Ah] [bp-4Eh]
	unsigned __int8 CmdDataBuf[8]; // [sp+Ch] [bp-4Ch] BYREF
	unsigned __int16 v21; // [sp+16h] [bp-42h]
	unsigned __int8 CmdHeadBuf[16]; // [sp+18h] [bp-40h] BYREF
	unsigned __int16 v23; // [sp+28h] [bp-30h]

	v21 = 0;
	v11 = 0;
	v5 = 0;
	*(_DWORD *)CmdDataBuf = 0;
	*(_DWORD *)&CmdDataBuf[4] = 0;
	memset(CmdHeadBuf, 0,0x10u);
	v6 = PHY_CAN_SetPara_20004984.Mode == 2;
	set_time0Stop_sub_802BB48();
	Delay_802EF34(2);
	v17 = *argv;
	v7 = 2;
	if (TimeOut_2000C530 < 0xC8)
		TimeOut_2000C530 = 0xC8;
	v8 = 2;
	v23 = argv[1];
	if (!v23)
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 2;
		return 2;
	}
	for (i = 0; ; ++i)
	{
		if (i >= (unsigned int)v23)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0;
			ans[1] = v5;
			return v7;
		}
		v11 = argv[v8];
		v12 = v8 + 1;
		if (!v11)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0xFF;
			ans[1] = 2;
			return 2;
		}
		if (v11 < 2u)
		{
			Copysub_802FB50(CmdHeadBuf, byte_803AFD8, 5);
			Copysub_802FB50(&CmdHeadBuf[5], &argv[v12], 8);
			v8 = v12 + 9;
			CanSendMsg_sub_802B874(CmdHeadBuf, 2, CmdDataBuf);
		}
		else
		{
			Copysub_802FB50(CmdHeadBuf, byte_803AFD0, 5);
			Copysub_802FB50(&CmdHeadBuf[5], &argv[v12], 8);
			v8 = v12 + 9;
			CanSendMsg_sub_802B874(CmdHeadBuf, 2, CmdDataBuf);
			if (!sub_802B3A6(CmdHeadBuf, 4, CmdDataBuf, 2, TimeOut_2000C530, v6))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			for (j = 0; j < (unsigned int)v11; ++j)
			{
				Copysub_802FB50(CmdHeadBuf, byte_803AFE0, 5);
				Copysub_802FB50(&CmdHeadBuf[5], &argv[v8], 8);
				v8 += 9;
				CanSendMsg_sub_802B874(CmdHeadBuf, 2, CmdDataBuf);
			}
			if (!sub_802B3A6(CmdHeadBuf, 4, CmdDataBuf, 2, TimeOut_2000C530, v6))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
		}
		if (v17 == 0xFF)
			break;
	LABEL_42:
		;
	}
	if (!sub_802B3A6(CmdHeadBuf, 4, CmdDataBuf, 2, TimeOut_2000C530, v6))
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = 0xFF;
		ans[1] = 2;
		return 2;
	}
	if ((CmdDataBuf[0] & 0x10) == 0)
	{
		ans[v7] = 8;
		v16 = (unsigned __int16)(v7 + 1);
		ans[v16] = 0;
		v14 = (unsigned __int16)(v16 + 1);
		Copysub_802FB50(&ans[v14], CmdHeadBuf, 8);
		v18 = 8;
	LABEL_41:
		v7 = v18 + v14;
		++v5;
		goto LABEL_42;
	}
	ans[v7] = CmdHeadBuf[1];
	v14 = (unsigned __int16)(v7 + 1);
	ans[v14] = CmdHeadBuf[2];
	LOWORD(v14) = v14 + 1;
	v18 = CmdHeadBuf[1] + (CmdHeadBuf[2] << 8);
	*(_WORD *)&CmdDataBuf[4] = *(_WORD *)&CmdHeadBuf[1];
	CmdDataBuf[6] = CmdHeadBuf[3];
	v21 = CmdHeadBuf[3];
	Copysub_802FB50(CmdHeadBuf, byte_803AFE8, 0xD);
	CmdHeadBuf[6] = CmdDataBuf[6];
	CanSendMsg_sub_802B874(CmdHeadBuf, 2, CmdDataBuf);
	for (k = 0; ; ++k)
	{
		if (k >= (unsigned int)v21)
		{
			Copysub_802FB50(CmdHeadBuf, byte_803B290, 0xD);
			*(_WORD *)&CmdHeadBuf[6] = *(_WORD *)&CmdDataBuf[4];
			CmdHeadBuf[8] = CmdDataBuf[6];
			CanSendMsg_sub_802B874(CmdHeadBuf, 2, CmdDataBuf);
			goto LABEL_41;
		}
		if (!sub_802B3A6(CmdHeadBuf, 4, CmdDataBuf, 2, TimeOut_2000C530, v6))
			break;
		Copysub_802FB50(&ans[7 * k + (unsigned __int16)v14], &CmdHeadBuf[1], 7);
	}
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	*ans = 0xFF;
	ans[1] = 2;
	return 2;
}



int ID6223_sub_8026DB0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v3; // r7
	unsigned __int8 v4; // r5
	unsigned int v5; // r6
	char v6; // r9
	unsigned int i; // r8
	int v8; // r4
	unsigned __int8 *v9; // r10
	int result; // r0
	int v11; // r7
	unsigned int j; // r8
	int v13; // r4
	unsigned int k; // r11
	unsigned int RcvLen; // [sp+4h] [bp-3Ch] BYREF
	unsigned int v17; // [sp+8h] [bp-38h]
	int m_Maxwaittime; // [sp+Ch] [bp-34h]
	unsigned __int8 v19[2]; // [sp+10h] [bp-30h]

	v17 = argv[1];
	v3 = 2;
	RcvLen = 0;
	*(_WORD *)v19 = 0;
	v4 = 0;
	v5 = 0;
	m_Maxwaittime = SC_TagKWP2000_20004974.m_Maxwaittime;
	v6 = 0;
	if (!argv[1])
		ExitFlag_2000C6BA = 1;
	for (i = 0; i < v17; ++i)
	{
		v8 = argv[v3];
		v6 += v8;
		v3 += v8 + 1;
	}
	v9 = ans + 2;
	if (argc >= 0)
	{
		set_time0Stop_sub_802BB48();
		v11 = 2;
		for (j = 0; j < v17; ++j)
		{
			v13 = argv[v11];
			for (k = 0; k < v13 - 1; ++k)
			{
				ComSendByte_sub_802F1E0(argv[k + 1 + v11]);
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			ComSendByte_sub_802F1E0(argv[k + 1 + v11]);
			while (1)
			{
				if (!sub_802E2F6(&receive_buff_2000BF20[1], &RcvLen, m_Maxwaittime))
				{
					memset(v9, 0, 4);
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				if (v19[0] != 0x7F || v19[1] != 0x78)
					break;
				m_Maxwaittime = 0x1388;
			}
			m_Maxwaittime = SC_TagKWP2000_20004974.m_Maxwaittime;
			receive_buff_2000BF20[0] = RcvLen;
			memmove(v9, receive_buff_2000BF20, RcvLen + 1);
			++v4;
			v9 += RcvLen + 1;
			v11 += v13 + 1;
			v5 += RcvLen + 1;
			if (v5 > 0xE10)
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0;
				ans[1] = v4;
				return v5 + 2;
			}
			if (j != v17 - 1)
				Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
		}
		*ans = 0;
		ans[1] = v4;
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		result = v5 + 2;
	}
	else
	{
		memset(v9, 0, 4);
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}




int ID6224_sub_8039550(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r10
	int v6; // r7
	unsigned int v7; // r8
	BOOL v8; // r9
	int result; // r0
	signed int v10; // r11
	BOOL v11; // r6
	unsigned __int8 v12; // [sp+4h] [bp-6Ch]
	unsigned __int16 v13; // [sp+6h] [bp-6Ah]
	unsigned __int8 v14; // [sp+8h] [bp-68h]
	unsigned __int8 v15; // [sp+8h] [bp-68h]
	unsigned __int8 Ch; // [sp+9h] [bp-67h] BYREF
	_BYTE TAnsBUf[3]; // [sp+Ah] [bp-66h] BYREF
	_BYTE v18[3]; // [sp+Dh] [bp-63h] BYREF
	unsigned __int8 v19; // [sp+24h] [bp-4Ch]
	unsigned __int16 v20; // [sp+26h] [bp-4Ah]
	unsigned __int8 v21[23]; // [sp+29h] [bp-47h] BYREF
	unsigned int IDNum; // [sp+40h] [bp-30h]

	v5 = 0;
	v6 = 1;
	v7 = 0x1F4;
	set_time0Stop_sub_802BB48();
	v20 = 3;
	v19 = *argv;
	v12 = 0;
	IDNum = argv[2];
	if (IDNum >= 5)
		IDNum = 4;
	v13 = 3;
	v8 = argv[v20 + 1] == 0x61 && argv[v20 + 2] == 3;
	while (1)
	{
		memmove(v21, &argv[v20 + 3], argv[v20] - 2);
		Delay_802EF34(5);
		CanSendMsg_sub_802B874(v21, IDNum, specialdata_2000C670);
		if ((specialdata_2000C670[0] & 0xF0) == 0x10)
			break;
	LABEL_13:
		v20 += argv[v20] + 1;
		if (!--v19)
		{
			if (v8)
			{
				*ans = 0;
				ans[1] = 0;
				ans[2] = 1;
				ans[3] = 0x55;
				ans[4] = 0xAA;
				ans[5] = 1;
				ans[6] = 0;
				ans[7] = 1;
				result = 8;
			}
			else
			{
				while (1)
				{
				LABEL_16:
					if (v6 != 1)
					{
					LABEL_43:
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						*ans = 0;
						ans[1] = 0;
						ans[2] = v12;
						return v5 + 3;
					}
					v14 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&Ch, IDNum, specialdata_2000C670, 1u, v7);
					if (!v14)
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						*ans = 0xFF;
						ans[1] = 2;
						return 2;
					}
					++v12;
					memmove(&ans[v13], &Ch, v14);
					v5 += v14;
					v13 += v14;
					if ((specialdata_2000C670[0] & 0xF0) == 0x10)
						break;
					if (specialdata_2000C670[1] != 0x7F || specialdata_2000C670[2] != 0x78)
						goto LABEL_43;
					--v12;
					v5 -= v14;
					v13 -= v14;
					v7 = 0x1388;
				}
				v10 = IDNum + specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) + 6 - v14;
				v11 = 1;
				while (1)
				{
					if (v11)
						CanSendMsg_sub_802B874(CanEnterFrame_2000C47C.data, IDNum, specialdata_2000C670);
					v15 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&Ch, IDNum, specialdata_2000C670, 2u, v7);
					if (!v15)
						break;
					if (specialdata_2000C670[0] >= 0x20u)
					{
						v11 = specialdata_2000C670[0] == 0x20 || specialdata_2000C670[0] == 0x28;
						++v12;
						if (v10 < 8)
						{
							memmove(&ans[v13], TAnsBUf, v10);
							v5 += v10;
							v13 += v10;
							v6 = 0;
							goto LABEL_16;
						}
						memmove(&ans[v13], TAnsBUf, v15 - 1);
						v5 += v15 - 1;
						v13 += v15 - 1;
						v10 = v10 - v15 + 1;
					}
					else
					{
						if ((specialdata_2000C670[0] & 0x30) != 0x10)
						{
							v6 = 0;
							goto LABEL_16;
						}
						++v12;
						memmove(&ans[v13], v18, v15 - 4);
						v13 += v15 - 4;
						v5 += v15 - 4;
						v10 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) - v15 + 2;
						v11 = 1;
					}
				}
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				result = 2;
			}
			return result;
		}
	}
	while (ReadOneFrameFromCANBuf_Ext_sub_802B550(&Ch, IDNum, specialdata_2000C670, 3u, 0x1F4u))
	{
		if (specialdata_2000C670[0] == 0x30)
			goto LABEL_13;
	}
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	*ans = 0xFF;
	ans[1] = 2;
	return 2;
}




int ID6226_sub_8039914(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v4; // r4
	int result; // r0
	unsigned int IDNum; // r7
	int v7; // r9
	int v8; // r11
	unsigned __int8 v9; // r8
	int v10; // r6
	int v11; // r10
	unsigned __int8 v12; // r8
	unsigned __int8 v13; // [sp+4h] [bp-54h]
	char v14; // [sp+5h] [bp-53h]
	unsigned __int8 SpeciData[4]; // [sp+8h] [bp-50h] BYREF
	unsigned int v16; // [sp+Ch] [bp-4Ch]
	int v17; // [sp+10h] [bp-48h]
	unsigned int v18; // [sp+14h] [bp-44h]
	unsigned __int8 v19; // [sp+18h] [bp-40h] BYREF
	unsigned __int8 v20[3]; // [sp+19h] [bp-3Fh] BYREF
	unsigned __int8 v21[16]; // [sp+1Ch] [bp-3Ch] BYREF
	int v22; // [sp+2Ch] [bp-2Ch]
	unsigned __int8 *v23; // [sp+30h] [bp-28h]

	v22 = argc;
	v23 = argv;
	*(_DWORD *)SpeciData = 0;
	v18 = 0;
	v14 = 0;
	v17 = 1;
	v16 = 0x1F4;
	set_time0Stop_sub_802BB48();
	v18 = *v23;
	v4 = v23[1];
	if ((_BYTE)v4)
	{
		v13 = v23[2];
		IDNum = v23[3];
		if (IDNum >= 5)
			LOBYTE(IDNum) = 4;
		if (v23[5] == 0x61 && v23[6] == 3)
			v14 = 1;
		v7 = 4;
		*ans = 0;
		ans[1] = 0;
		ans[2] = 0;
		v8 = 3;
		do
		{
			Delay_802EF34(5);
			CanSendMsg_sub_802B874(&v23[v7 + 3], IDNum, SpeciData);
			v7 += v23[v7] + 1;
			if ((SpeciData[0] & 0xF0) == 0x10)
			{
				do
					ReadOneFrameFromCANBuf_Ext_sub_802B550(ans, IDNum, SpeciData, 3u, 0x1F4u);
				while (SpeciData[0] != 0x30);
			}
			--v4;
		} while ((_BYTE)v4);
		if (v14 == 1)
		{
			*ans = 0;
			ans[1] = 0;
			ans[2] = 1;
			ans[3] = 0x55;
			ans[4] = 0xAA;
			ans[5] = 1;
			ans[6] = 0;
			ans[7] = 1;
			result = 8;
		}
		else
		{
			while (1)
			{
			LABEL_16:
				if (v17 != 1)
					goto LABEL_47;
				v9 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&v19, IDNum, SpeciData, 1u, v16);
				if (!v9)
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					*ans = 0xFF;
					ans[1] = 2;
					return 2;
				}
				if ((SpeciData[0] & 0xF0) == 0x10)
					break;
				if (SpeciData[1] == 0x7F && SpeciData[2] == 0x78)
				{
					v16 = 0x1388;
				}
				else
				{
					v16 = 0x1F4;
					++ans[2];
					memmove(&ans[v8], &v19, v9);
					v8 += v9;
					if (ans[2] >= v18)
					{
						v17 = 0;
					LABEL_47:
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						return v8;
					}
				}
			}
			++ans[2];
			memmove(&ans[v8], &v19, v9 - 1);
			v8 += v9 - 1;
			v10 = 1;
			if (v13 == 0xFF)
				v11 = (unsigned __int8)IDNum + SpeciData[1] + ((SpeciData[0] & 0xF) << 8) - v9 + 5 + 2;
			else
				v11 = (unsigned __int8)IDNum + v13 - v9 + 5 + 2;
			while (1)
			{
				if (v10 == 1)
					CanSendMsg_sub_802B874(CanEnterFrame_2000C47C.data, IDNum, SpeciData);
				v12 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&v19, IDNum, SpeciData, 2u, 0x1F4u);
				if (!v12)
					break;
				if (SpeciData[0] >= 0x20u)
				{
					v10 = 0;
					v11 = v11 - v12 + 1;
					++ans[2];
					memmove(&ans[v8], v20, v12 - 1);
					v8 += v12 - 1;
					if (v11 < 0)
						v8 += v11;
				}
				else
				{
					if ((SpeciData[0] & 0xF0) != 0x10)
					{
						v17 = 0;
						goto LABEL_16;
					}
					++ans[2];
					memmove(&ans[v8], v21, v12 - 4);
					v8 += v12 - 4;
					v10 = 1;
					v11 = SpeciData[1] + ((SpeciData[0] & 0xF) << 8) - v12 + 2;
				}
			}
			if (ans[2])
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				result = 2;
			}
			else
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				result = 2;
			}
		}
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}





int ID6227_sub_8053E00(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	int v5; // r8
	int result; // r0
	int v7; // r10
	unsigned __int8 v8; // r9
	int v9; // r0
	int v10; // r8
	int v11; // r11
	unsigned __int8 v12; // r0
	int v13; // r8
	int v14; // r0
	int v15; // r11
	int v16; // r10
	int v17; // r0
	int v18; // r8
	int v19; // r11
	int v20; // r6
	unsigned __int8 v21; // r6
	int v22; // r7
	unsigned __int8 Rcvbyte; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 v24; // [sp+1h] [bp-2Fh]
	unsigned __int8 v25; // [sp+2h] [bp-2Eh]
	int v26; // [sp+8h] [bp-28h]

	v26 = argc;
	set_time0Stop_sub_802BB48();
	if (!*argv)
		ExitFlag_2000C6BA = 1;
	v5 = 2;
	v24 = argv[1];
	if (v24)
	{
		*ans = 0;
		ans[1] = 0;
		v7 = 2;
	LABEL_8:
		v8 = 0;
		v9 = argv[v5];
		v10 = v5 + 1;
		v11 = v9;
		if ((_BYTE)v9)
		{
			while (1)
			{
				v12 = v11--;
				if (v12 < 2u)
					break;
				ComSendByte_sub_802F1E0(argv[v10++]);
				if (!ComByte_sub_802F6CC(&Rcvbyte, 1000))
					goto LABEL_37;
				Delay_sub_802EF46(SC_TagKWP2000_20004974.m_nBtyetime);
			}
			ComSendByte_sub_802F1E0(argv[v10]);
			v13 = v10 + 1;
			if (ComByte_sub_802F6CC(&Rcvbyte, 1000))
			{
				v14 = argv[v13];
				v5 = v13 + 1;
				v15 = v14;
				if ((_BYTE)v14)
				{
					ans[v7++] = v14;
					++ans[1];
					while (ComByte_sub_802F6CC(&Rcvbyte, SC_TagKWP2000_20004974.m_Maxwaittime))
					{
						ans[v7++] = Rcvbyte;
						if (!(_BYTE)--v15)
							goto LABEL_39;
					}
				}
				else
				{
					v16 = v7 + 1;
					++ans[1];
					v17 = argv[v5];
					v18 = v5 + 1;
					v19 = v17;
					if ((_BYTE)v17)
					{
						ans[v16] = v17;
						v7 = v16 + 1;
						v25 = argv[v18];
						v5 = v18 + 1;
						while (ComByte_sub_802F6CC(&Rcvbyte, SC_TagKWP2000_20004974.m_Maxwaittime))
						{
							++v8;
							ans[v7++] = Rcvbyte;
							if (!(_BYTE)--v19)
							{
								Rcvbyte -= v25;
								Rcvbyte -= v8;
								v20 = Rcvbyte;
								if (!Rcvbyte)
									goto LABEL_40;
								++ans[1];
								ans[v7++] = v20;
								while (ComByte_sub_802F6CC(&Rcvbyte, SC_TagKWP2000_20004974.m_Maxwaittime))
								{
									ans[v7++] = Rcvbyte;
									if (!(_BYTE)--v20)
										goto LABEL_39;
								}
								break;
							}
						}
					}
					else
					{
						v21 = argv[v18];
						v5 = v18 + 1;
						v22 = v16;
						v7 = v16 + 1;
						++ans[1];
						while (ComByte_sub_802F6CC(&Rcvbyte, SC_TagKWP2000_20004974.m_Maxwaittime))
						{
							ans[v7++] = Rcvbyte;
							++v8;
							if (Rcvbyte == v21)
							{
								if (!ComByte_sub_802F6CC(&Rcvbyte, SC_TagKWP2000_20004974.m_Maxwaittime))
									break;
								ans[v22] = v8;
							LABEL_39:
								Delay_802EF34(SC_TagKWP2000_20004974.m_nFrameTime);
								if (ans[1] >= (unsigned int)v24)
								{
								LABEL_40:
									if (timer_open_flag_2000C6B7 == 1)
										TIM_sub_802EEEC(0);
									return v7;
								}
								goto LABEL_8;
							}
						}
					}
				}
			}
		LABEL_37:
			PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, ans, 4);
			result = 2;
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
			result = 2;
		}
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
		result = 2;
	}
	return result;
}





int ID6228_sub_803ADF4(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v6; // r10
	int v7; // r6
	unsigned int v8; // r9
	unsigned int result; // r0
	signed int v10; // r11
	unsigned __int8 v11; // [sp+0h] [bp-38h]
	unsigned __int8 v12; // [sp+1h] [bp-37h]
	unsigned __int8 v13; // [sp+2h] [bp-36h]
	int v14; // [sp+4h] [bp-34h]

	v6 = 0;
	v12 = *argv;
	v14 = 0x64 * argv[2];
	v7 = 0x64 * argv[1];
	v11 = argv[3];
	v13 = argv[4];
	v8 = 2;
	set_time0Stop_sub_802BB48();
	if (sub_803AA2C(v11, argv + 0xC, v12) >= 0)
	{
		while (v6 < (unsigned int)v13)
		{
			if (v8 >= 0xF3C)
				v10 = 0xFFFFFFFB;
			else
				v10 = sub_803AC10(v11, &ans[v8 + 2], v12, v7);
			if (v10 >= 0)
			{
				++v6;
				ans[v8] = v10 / 0x100;
				ans[v8 + 1] = v10 % 0x100;
				v8 += v10 + 2;
			}
			else
			{
				if (v10 != 0xFFFFFFFE)
				{
					if (v10 == 0xFFFFFFFB)
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						*ans = szFNG_20004A08[0];
						ans[1] = szFNG_20004A08[1];
						result = 2;
					}
					else if (v6)
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						*ans = 0;
						ans[1] = v6;
						result = v8;
					}
					else
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						*ans = szFBREAK_20004A0C[0];
						ans[1] = szFBREAK_20004A0C[1];
						result = 2;
					}
					return result;
				}
				v7 = v14;
			}
		}
		if (v6)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = 0;
			ans[1] = v6;
			result = v8;
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			result = 2;
		}
	}
	else
	{
		if (timer_open_flag_2000C6B7 == 1)
			TIM_sub_802EEEC(0);
		*ans = szFBREAK_20004A0C[0];
		ans[1] = szFBREAK_20004A0C[1];
		result = 2;
	}
	return result;
}




int ID6229_sub_803A3B0(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v3; // r8
	int v4; // r10
	unsigned __int8 *v5; // r9
	int v6; // r5
	int v7; // r6
	unsigned int i; // r7
	int result; // r0
	unsigned int v10; // r0
	unsigned int v11; // r4
	int v12; // r11
	size_t v13; // r11
	char v14; // [sp+4h] [bp-5Ch]
	char v15; // [sp+5h] [bp-5Bh]
	char v16; // [sp+6h] [bp-5Ah]
	char v17; // [sp+7h] [bp-59h]
	char v19; // [sp+Ch] [bp-54h]
	char v20; // [sp+Dh] [bp-53h]
	char v21; // [sp+Eh] [bp-52h]
	unsigned int v22; // [sp+10h] [bp-50h]
	unsigned int v23; // [sp+14h] [bp-4Ch]
	int v24; // [sp+18h] [bp-48h]
	int v25; // [sp+1Ch] [bp-44h]
	size_t v26; // [sp+20h] [bp-40h]
	int v27; // [sp+28h] [bp-38h]
	int v28; // [sp+30h] [bp-30h]

	v14 = 1;
	v21 = 0;
	v20 = 0;
	v17 = 0;
	v19 = 0;
	v16 = 1;
	v3 = 0;
	v4 = 0;
	v25 = 0;
	v22 = 0;
	v24 = 0;
	v5 = ans + 3;
	v6 = argv[2];
	if ((argv[1] & 0xF0) == 0x10)
		v14 = 0;
	if (!argv[1] || argv[1] == 0xFF)
	{
		v23 = *argv;
	}
	else
	{
		v23 = *argv + ((argv[1] & 0xF) << 8);
		v17 = 1;
	}
	v26 = argv[3] - 2;
	v7 = 3;
	v28 = v6 & 1;
	if (v14)
		set_time0Stop_sub_802BB48();
	v27 = argv[5] + (argv[4] << 8);
	switch (v27)
	{
	case 0x6103:
		v19 = 1;
		break;
	case 0x6105:
		v21 = 1;
		break;
	case 0x6106:
		v20 = 1;
		break;
	case 0x6201:
		v6 = 1;
		break;
	}
	for (i = 0; i < v23; ++i)
	{
		if (v17 == 2)
		{
			memmove(&CmdBuf_2000C554[3], &argv[v7], v26);
			if ((CmdBuf_2000C554[0] & 0x80) != 0)
				v7 += 0xA;
			else
				v7 += 8;
		}
		else
		{
			memmove(CmdBuf_2000C554, &argv[v7 + 3], v26);
			if (v17 == 1)
			{
				v17 = 2;
				if ((CmdBuf_2000C554[0] & 0x80) != 0)
					v7 += 0x10;
				else
					v7 += 0xE;
			}
			else
			{
				v7 += argv[v7] + 1;
			}
		}
		if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, v6, specialdata_2000C670))
		{
			if (timer_open_flag_2000C6B7 == 1)
			{
				if (v14)
					TIM_sub_802EEEC(0);
			}
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			return 2;
		}
		if (v25 && v24)
			--v24;
		if ((specialdata_2000C670[0] & 0xF0) == 0x10 || v25 && !v24)
		{
			while (i + 1 < v23)
			{
				if (!ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], v6, specialdata_2000C670, 1u, 0x1F4u))
				{
					if (timer_open_flag_2000C6B7 == 1 && v14)
						TIM_sub_802EEEC(0);
					*ans = szFBREAK_20004A0C[0];
					ans[1] = szFBREAK_20004A0C[1];
					return 2;
				}
				if (v20)
				{
					if (specialdata_2000C670[0] == 0x30)
					{
						v25 = specialdata_2000C670[1];
						v22 = specialdata_2000C670[3];
						v24 = specialdata_2000C670[1];
						break;
					}
				}
				else if ((specialdata_2000C670[0] & 0x30) == 0x30)
				{
					v25 = specialdata_2000C670[1];
					v22 = specialdata_2000C670[3];
					v24 = specialdata_2000C670[1];
					break;
				}
			}
		}
		if (v22 && v22 < 0x80)
		{
			if (i < v23 - 1)
				Delay_802EF34(v22);
		}
		else if (v22 < 0xF1 || v22 >= 0xFA)
		{
			if (i < v23 - 1 && DelayTime_2000C53C)
				Delay_sub_802EF46(DelayTime_2000C53C);
		}
		else if (i < v23 - 1)
		{
			Delay_sub_802EF46(0x64 * (v22 - 0xF0));
		}
	}
	if (v19 == 1)
	{
		*v5 = 0;
		v5[1] = 0;
		v5[2] = 1;
		v5[3] = 0x55;
		v5[4] = 0xAA;
		v5[5] = 1;
		v5[6] = 0;
		v5[7] = 1;
		result = 8;
	}
	else
	{
		if (TimeOut_2000C530 == 0x7D0)
			v10 = ReadOneFrameFromCANBuf_Ext_sub_802B550(
				&CmdBuf_2000C554[0x14],
				v6,
				specialdata_2000C670,
				1u,
				(__int16)TimeOut_2000C530);
		else
			v10 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], v6, specialdata_2000C670, 1u, 0x1F4u);
		v11 = v10;
		if (v10)
		{
			while (1)
			{
			LABEL_73:
				if (v16 != 1)
					goto LABEL_115;
				if ((specialdata_2000C670[0] & 0xF0) == 0x10)
					break;
				if (specialdata_2000C670[1] != 0x7F || specialdata_2000C670[2] != 0x78)
				{
					memmove(v5, &CmdBuf_2000C554[0x14], v11);
					v4 += v11;
					++v3;
				LABEL_115:
					*ans = 0;
					ans[1] = 0;
					ans[2] = v3;
					if (timer_open_flag_2000C6B7 == 1 && v14)
						TIM_sub_802EEEC(0);
					return v4 + 3;
				}
				if (v21 == 1)
					TIM_sub_802EEEC(0);
				v11 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], v6, specialdata_2000C670, 1u, 0x61A8u);
				if (!v11)
				{
					if (timer_open_flag_2000C6B7 == 1 && v14)
						TIM_sub_802EEEC(0);
					*ans = szFBREAK_20004A0C[0];
					ans[1] = szFBREAK_20004A0C[1];
					return 2;
				}
			}
			memmove(v5, &CmdBuf_2000C554[0x14], v11);
			v4 += v11;
			if (v6 == 1)
			{
				v6 = 2;
				v28 = 0;
				v12 = specialdata_2000C670[3] + ((specialdata_2000C670[0] & 0xF) << 8) + 3;
			}
			else
			{
				v12 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8);
			}
			v5 += v11;
			++v3;
			v15 = 1;
			v13 = v6 + v12 + 6 - v11;
			while (1)
			{
				if (v3 - 1 >= CanEnterFrame_2000C47C.data[0x1E]
					&& v3 - 1 == CanEnterFrame_2000C47C.data[0x1E] * ((v3 - 1) / CanEnterFrame_2000C47C.data[0x1E])
					&& CanEnterFrame_2000C47C.data[0x1E])
				{
					v15 = 1;
				}
				if (v15 == 1)
				{
					if (dword_2000C668)
						Delay_802EF34(dword_2000C668);
					if (!CanSendMsg_sub_802B874(CanEnterFrame_2000C47C.data, v6, specialdata_2000C670))
					{
						if (timer_open_flag_2000C6B7 == 1 && v14)
							TIM_sub_802EEEC(0);
						*ans = szFBREAK_20004A0C[0];
						ans[1] = szFBREAK_20004A0C[1];
						return 2;
					}
				}
				v11 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], v6, specialdata_2000C670, 2u, 0x1F4u);
				if (!v11)
					break;
				if (CmdBuf_2000C554[0x14] >= 0x20u)
				{
					v15 = 0;
					++v3;
					if (7 - v28 >= v13)
					{
						memmove(v5, &CmdBuf_2000C554[0x15], v13);
						v5 += v13;
						v4 += v13;
						v16 = 0;
						goto LABEL_73;
					}
					memmove(v5, &CmdBuf_2000C554[0x15], v11 - 1);
					v5 = &v5[v11 - 1];
					v4 += v11 - 1;
					v13 = v13 - v11 + 1;
				}
				else
				{
					if ((CmdBuf_2000C554[0x14] & 0xF0) != 0x10)
					{
						v16 = 0;
						goto LABEL_73;
					}
					v15 = 1;
					++v3;
					memmove(v5, &CmdBuf_2000C554[0x18], v11 - 4);
					v5 = &v5[v11 - 4];
					v4 += v11 - 4;
					v13 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8) - v11 + 2;
				}
			}
			if (!v13)
			{
				v16 = 0;
				goto LABEL_73;
			}
			if (timer_open_flag_2000C6B7 == 1 && v14)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			result = 2;
		}
		else
		{
			if (timer_open_flag_2000C6B7 == 1 && v14)
				TIM_sub_802EEEC(0);
			*ans = szFBREAK_20004A0C[0];
			ans[1] = szFBREAK_20004A0C[1];
			result = 2;
		}
	}
	return result;
}




int ID622A_sub_802AF50(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v5; // r10
	int v6; // r5
	unsigned __int8 *v7; // r11
	unsigned __int16 ansPos; // r9
	char v9; // r7
	char v11; // r6
	__int16 v14; // r8
	unsigned __int8 Rcvbyte; // [sp+0h] [bp-38h] BYREF
	unsigned __int8 v16; // [sp+1h] [bp-37h]
	unsigned __int8 v17; // [sp+2h] [bp-36h]
	unsigned __int8 v18; // [sp+3h] [bp-35h]
	unsigned __int8 v19; // [sp+4h] [bp-34h]
	unsigned __int8 v20; // [sp+5h] [bp-33h]

	v19 = 0x14;
	v18 = 5;
	v17 = 0x32;
	v16 = 0x14;
	set_time0Stop_sub_802BB48();
	v20 = *argv++;
	v19 = *argv++;
	v18 = *argv++;
	v17 = *argv++;
	v16 = *argv;
	argv += 2;
	v5 = *argv++;
	v6 = *argv;
	v7 = argv + 1;
	ansPos = 3;
	v9 = 0;
LABEL_2:
	while (2)
	{
		if (!(_BYTE)v6--)
		{
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			return ansPos;
		}
		v11 = *v7++;
		while (v11--)
		{
			if (v20 != 0xFF || v9)
			{
			LABEL_10:
				ComSendByte_sub_802F1E0(*v7++);
				if (!ComByte_sub_802F6CC(&Rcvbyte, v19))
				{
					if (timer_open_flag_2000C6B7 == 1)
						TIM_sub_802EEEC(0);
					goto LABEL_13;
				}
				ans[ansPos++] = Rcvbyte;
				if (v20 != 0xFF)
					byte_2000C6BE = 0;
				if (v11)
					Delay_802EF34(v18);
				++v9;
			}
			else
			{
				if (*v7 != byte_2000C6BE)
				{
					byte_2000C6BE = *v7;
					goto LABEL_10;
				}
				++v7;
				ans[ansPos++] = Rcvbyte;
				v9 = 1;
			}
		}
		v14 = v17;
		while (ComByte_sub_802F6CC(&Rcvbyte, v14))
		{
		LABEL_27:
			ans[ansPos++] = Rcvbyte;
			v14 = v16;
			if (v5 && ansPos - 3 >= v5)
			{
				*ans = 0;
				ans[1] = 1;
				ans[2] = ansPos - 3;
				goto LABEL_2;
			}
		}
		if (ansPos != 3)
		{
			if (!v5)
			{
				*ans = 0;
				ans[1] = 1;
				ans[2] = ansPos - 3;
				continue;
			}
			goto LABEL_27;
		}
		break;
	}
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
LABEL_13:
	PutDataToAns_sub_802BCBC(szFNG_20004A08, ans, 4);
	return 2;
}




int ID622C_sub_803AFF8(int argc, unsigned __int8 *argv, unsigned __int8 *ans)
{
	unsigned __int8 v4; // r5
	int v5; // r6
	unsigned __int8 v6; // r11
	int v8; // r9
	int result; // r0
	int v10; // r8
	int v11; // r8
	unsigned int i; // r0
	unsigned int v13; // r7
	bool v14; // [sp+4h] [bp-64h]
	unsigned int v15; // [sp+8h] [bp-60h]
	unsigned int v16; // [sp+10h] [bp-58h]
	unsigned __int8 RcvBuf[20]; // [sp+14h] [bp-54h] BYREF
	unsigned __int8 v18[20]; // [sp+28h] [bp-40h] BYREF

	v4 = 0;
	v5 = 0;
	v6 = 2;
	memset(v18,0, 0x14u);
	memset(RcvBuf,0, 0x14u);
	v15 = 0x1F4;
	v16 = argv[4] + (argv[2] << 0xC) + (argv[1] << 0x18) + (argv[3] << 8);
	LOBYTE(v8) = argv[5];
	if ((_BYTE)v8)
	{
		v10 = 0xB;
		if ((argv[0xB] & 0x80) != 0)
			v6 = 4;
		set_time0Stop_sub_802BB48();
		while (1)
		{
			v14 = argv[v10 - 2] == 0x61 && argv[v10 - 1] == 3;
			memmove(v18, &argv[v10], v6 + (argv[v10] & 0xF) + 1);
			if (!CanSendMsg_sub_802B874(v18, v6, specialdata_2000C670))
			{
				if (timer_open_flag_2000C6B7 == 1)
					TIM_sub_802EEEC(0);
				*ans = 0xFF;
				ans[1] = 2;
				return 2;
			}
			v10 += v6 + (argv[v10] & 0xF) + 7;
			v8 = (unsigned __int8)(v8 - 1);
			if (!v8)
				break;
			Delay_sub_802EF46(v16);
		}
		v11 = 2;
		if (v14)
		{
			*ans = 0;
			ans[1] = 1;
			ans[2] = 5;
			ans[3] = 0x55;
			ans[4] = 0xAA;
			ans[5] = 1;
			ans[6] = 0;
			ans[7] = 1;
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			result = 8;
		}
		else
		{
			while (2)
			{
				for (i = ReadOneFrameFromCANBuf_Ext_sub_802B550(RcvBuf, v6, specialdata_2000C670, 1u, v15);
					;
					i = ReadOneFrameFromCANBuf_Ext_sub_802B550(RcvBuf, v6, specialdata_2000C670, 1u, 0x1388u))
				{
					if (!i)
					{
						if (timer_open_flag_2000C6B7 == 1)
							TIM_sub_802EEEC(0);
						if (v5)
						{
							*ans = 0;
							result = v5 + 3;
						}
						else
						{
							*ans = 0xFF;
							ans[1] = 2;
							result = 2;
						}
						return result;
					}
					if ((RcvBuf[0xA] != 0x7F || RcvBuf[0xC] != 0x78)
						&& ((specialdata_2000C670[0] & 0xF0) != 0xC0 || specialdata_2000C670[3] != 0x7E))
					{
						break;
					}
				}
				v15 = 0x1388;
				v13 = i + 1;
				++v4;
				memmove(&ans[v11], RcvBuf, i + 1);
				v11 += v13;
				v5 += v13;
				if ((specialdata_2000C670[0] & 0xF0) != 0xC0 && (specialdata_2000C670[0] & 0xF0) != 0x40)
					continue;
				break;
			}
			*ans = 0;
			ans[1] = v4;
			if (timer_open_flag_2000C6B7 == 1)
				TIM_sub_802EEEC(0);
			if (v5)
			{
				*ans = 0;
				result = v5 + 2;
			}
			else
			{
				*ans = 0xFF;
				ans[1] = 2;
				result = 2;
			}
		}
	}
	else
	{
		*ans = 0xFF;
		ans[1] = 2;
		result = 2;
	}
	return result;
}












