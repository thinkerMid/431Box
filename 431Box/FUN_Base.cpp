#include "stdafx.h"
#include "FUN_Base.h"
#include "431Box.h"
#include "stm32f2xx.h"

CMPHY_Relay SC_RelayState; //继电器相关数据参数
CMPHY_Relay SC_RelayState_200049DC;
unsigned char GPIOPinWriteVal_2000C64C[8];
unsigned char UsartSendIsSuccessFlage_20004A2D;//这个值是与串口发送数据有关
USART_TypeDef *pUSART_200048BC[2] = {  };//&USART1,&USART2
char COM_ECUPORT_20004A2C;
char IoMode_2000C6B5;
char IoIndex_2000C6B4;
unsigned char PWMData;
SC_CML_ISO15765 SC_TagISO15765_2000C334;
SC_CML_ISO14230 SC_TagKWP2000_20004974;
SET_LINK_KEEP Keep_Link_200046C0;
SET_LINK_KEEP CANKeepLink_20004708;//暂时定义成 这个 可能在函数中不是这个结构体
unsigned __int8 timer_open_flag_2000C6B7;
COM_PORTMODE SC_com_portMode_20004964;
SC_UserPak UserPak_2000AFD0[81];
unsigned char PWMLinkAddrBuf[4];
unsigned __int16 dlytime_2000AA1C;
SC_CML_KWP1281 SC_TagKWP1281_200043E4;
unsigned char receive_buff_2000BF20[261];
char byte_2000C6BB;
unsigned __int8 SendPakdataPackData_2000BDF4[100];
typedef void(*InterruptFuntion)(void);
InterruptFuntion ComInterruptFunAddr_2000C23C[45];//定义在串口中断使用的函数指针数组1
InterruptFuntion TIMInterruptFunAddr_2000C5B0[45];//定义在定时中断使用的函数指针数组2
int DelayTime_2000C53C;
char CANRcv_TIM_Open_Flag_2000C6B8;
CanRxMsg CANTxMsgArr_2000C380[2];
char byte_2000C3BC;
int Cnt_2000C37C;
CAN_TypeDef *CANxArr_20004934[2];
unsigned __int8 CanPortArr_2000C6AE[6];
CAN_TypeDef CAN1_BASE_40006400;
CAN_TypeDef CAN2_BASE_40006800;
USART_TypeDef *USART1 = (USART_TypeDef *)malloc(sizeof(USART_TypeDef));
USART_TypeDef *USART2 = (USART_TypeDef *)malloc(sizeof(USART_TypeDef));
char unk_2000C6BF;
char unk_2000C6B6;
GPIO_TypeDef *dword_20004664[23];
SC_CMLISO15765ENTERFRAME CanEnterFrame_2000C47C;
char ucCan30ConfigMode_2000C6BD;
int dword_2000C668;
char unk_2000C6B9;
char kwp2000m_nBtyetime_2000C540;
char TimeOut_2000C530;
int dword_2000C538;
int FrameTime_2000C534;
GPIO_TypeDef *GPIOB_200048D4, *GPIOB_200048E8;
int CanDataPos;
unsigned __int8 CANDataPak_2000A430[128];
unsigned __int8 byte_2000C6BC[2];
SC_CMLISO15765para CAN_SetPara_2000C2F0;
CAN_CONFIGPARA PHY_CAN_SetPara_20004984;
int dword_20004A14;
TIM_TypeDef TIM4_BASE_40000800;
CAN_FilterInitTypeDef CAN_FilterInitStruct_2000C590;
int Addr200049E5;
int CANBaudrateArr_802E688[11] = { 1, 0, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB };
int dword_802C424[32] = { 0xBAA55,0, 0, 0, 0, 0, 0, 0 };
unsigned __int8 specialdata_2000C670[4];
unsigned __int8 CmdBuf_2000C554[20];
unsigned __int8 byte_802C1CC[32] = { 0x55, 0xAA, 0xB, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

__int16 word_803085C[24] = { 0x800, 0x400, 1, 1, 0x40, 0x80, 4, 0x800, 0x400, 8, 0x200, 0x20, 0x2000, 0x100, 0x200, 0x100,
0x200, 0x400, 0x40, 0x80, 0x100, 0x2000, 2, 0 };



int CANBadurateArr_8032104[24] = { 0x50000, 7, 0xA0000, 0x20002, 0xD0000, 0x20003, 0xA0001
,0x40002, 0xA0000, 0x80002, 0xA0000, 0x100002, 0xA0000
,0x200002, 0xA0000, 0x280002, 0x50000, 0x500007, 0xA0000
,0x140002, 0x20000, 0x1F0005, 0xA0000, 0x3C0002 };

unsigned char aV1168[8] = "V11.68";

unsigned char szFOK_20004A04[4] =
{
	0xff, 0x00
};


unsigned char szFNG_20004A08[4] =
{
	0xff, 0x01
};


unsigned char szFBREAK_20004A0C[4] =
{
	0xff, 0x02
};


unsigned char szFNOWAIT[4] =
{
	0xff, 0x03
};


unsigned char szErrorFrame[7] =
{
	0x00, 0x06, 0xff, 0xf9, 0xff, 0xff
};



TIM_TypeDef TIM3_BASE_40000400;
TIM_TypeDef TIM2_BASE_40000000;
TIM_TypeDef TIM5_BASE_40000C00;
TIM_TypeDef TIM6_BASE_40001000;
GPIO_TypeDef GPIOC_BASE_40020800;



















void CMPHY_Relay_Init_sub_8030B62(CMPHY_Relay *SC_RelayState)
{
	SC_RelayState->InputChannel = 1;
	SC_RelayState->OutputChannel = 1;
	SC_RelayState->CANH = 1;
	SC_RelayState->CANL = 1;
	SC_RelayState->CommType = -1;
	SC_RelayState->LogicType = 1;
	SC_RelayState->LevelType = 12;
	SC_RelayState->LLine = 0;
	SC_RelayState->Dts = 0;
}











//将GPIO 引脚复位或者不复位的值初始化为全都0
void MemsetAddr2000C64C_sub_80308A4()
{
	unsigned __int8 i; // r0

	for (i = 0; i < 6u; ++i)
		GPIOPinWriteVal_2000C64C[i] = 0;
}

//复位使用的GPIO的引脚为0
void CMPHY_Relay_Reset_sub_8030B88()
{
	MemsetAddr2000C64C_sub_80308A4();
	GPIOWrite_sub_803092C();
}




//设置GPIOx的引脚xx 初始化0 没有具体实例化 参考IDA中这个函数和硬件
void GPIOWrite_sub_803092C()
{
	int v0; // r5
	unsigned int i; // r4

	if (unk_2000C6B6 != 1)
	{
		//GPIO_WriteBit_80312F6(&GPIOH_BASE_40021C00, 0x400, 1);
		//GPIO_WriteBit_80312F6(&GPIOI_BASE40022000, 0x400, 0);
		//GPIO_WriteBit_80312F6(&GPIOC_BASE_40020800, 8, 1);
		//noUseLoopsub_803088C(0xA);
		//v0 = 5;
		//do
		//{
		//	for (i = 0; i < 8; ++i)
		//	{
		//		GPIO_WriteBit_80312F6(&GPIOC_BASE_40020800, 4, 0);
		//		GPIO_WriteBit_80312F6(&GPIOI_BASE40022000, 0x800, ((int)*(unsigned __int8 *)(v0 + 0x2000C64C) >> (7 - i)) & 1);// 0x2000C64C 这个地址 在上一级函数中已经被赋值
		//		noUseLoopsub_803088C(0xA);
		//		GPIO_WriteBit_80312F6(&GPIOC_BASE_40020800, 4, 1);
		//		noUseLoopsub_803088C(0xA);
		//	}
		//} while (v0--);
		//GPIO_WriteBit_80312F6(&GPIOI_BASE40022000, 0x400, 1);
		//noUseLoopsub_803088C(0x64);
		//noUseLoopsub_803088C(0x64);
		//noUseLoopsub_803088C(0x64);
		//GPIO_WriteBit_80312F6(&GPIOH_BASE_40021C00, 0x400, 0);
		//noUseLoopsub_803088C(0xA);
	}
}


//对使用到的引脚 重置为1  Bit_RESET: to clear the port pin  Bit_SET: to set the port pin
void GPIO_WriteBit_PIN_sub_8030DBC(char a1, char a2)
{

}


//------------------------------------------------------------------------------
// Funtion: 设置回复给上位机的数据包
// Input  : data - 回复给上位机的数据
//          Ans - 回复给上位机的数据包
//          dataLenth - 数据包的长度
// Output : ans - 回复到上位机的数据
// Return : 无
// Info   :
//------------------------------------------------------------------------------
void PutDataToAns_sub_802BCBC(unsigned char * data, unsigned char * Ans, int dataLenth)
{
	while (dataLenth--)
	{
		*(Ans++) = *(data++);
	}
}


//没有实现 功能是初始化GPIO 设置GPIO 使用的引脚 波特率 输入输出方式
void SetGPIOGPIO_Mode_IN_sub_8031E6C(char a1)
{
	
}

//系统滴答延时
void Delay_802EF34(int a1)
{
	
}



//关闭串口中断使能 将FunAddr_2000C23C函数指针数组设置为0
void ComClose_sub_80B1D06_sub_802FA28(char COM_ECUPORT)
{
	if (COM_ECUPORT != 2)
	{
		//USART_Cmd_8033544(pUSART_200048BC[COM_ECUPORT], 0);
		//COM_ECUPORT_20004A2C = 5;
		ComInterruptFunAddr_2000C23C[5 * COM_ECUPORT] = 0;
		ComInterruptFunAddr_2000C23C[5 * COM_ECUPORT + 1] = 0;
		//USART_ITConfig_sub_8033570(pUSART_200048BC[COM_ECUPORT], 0x26u, 0);
		//USART_ITConfig_sub_8033570(pUSART_200048BC[COM_ECUPORT], 0x25u, 0);
	}
}


//设置GPIO的哪个值 是复位还是不复位 0 或者 1   
void CMPHY_Relay_Set_sub_8030B94(CMPHY_Relay *SC_RelayState)
{
	unsigned int CommType; // r0
	unsigned int Dts; // r0

	MemsetAddr2000C64C_sub_80308A4();
	SetCmmst462DVal_sub_802F1D8(1);
	CommType = SC_RelayState->CommType;
	if (!SC_RelayState->CommType)
		goto LABEL_16;
	if (CommType == 2)
	{
		if (SC_RelayState->CANH < 0xEu)
			Givebyte_2000C64CVal_sub_80308BE(SC_RelayState->CANH, 1);
		Givebyte_2000C64CVal_sub_80308BE(0x1Cu, 1);
		Givebyte_2000C64CVal_sub_80308BE(0x1Du, 1);
		Givebyte_2000C64CVal_sub_80308BE(0x26u, 1);
		Givebyte_2000C64CVal_sub_80308BE(0x27u, 1);
		goto LABEL_53;
	}
	if (CommType < 2)
	{
		if (SC_RelayState->CANH < 0xEu)
			Givebyte_2000C64CVal_sub_80308BE(SC_RelayState->CANH, 1);
		if ((unsigned __int8)SC_RelayState->CANL < 0xEu)
			Givebyte_2000C64CVal_sub_80308BE(SC_RelayState->CANL + 0xE, 1);
		Givebyte_2000C64CVal_sub_80308BE(0x1Cu, 1);
		goto LABEL_53;
	}
	if (CommType == 4 || CommType < 4)
	{
		Givebyte_2000C64CVal_sub_80308BE(0x20u, 1);
		goto LABEL_53;
	}
	if (CommType == 5)
	{
	LABEL_16:
		if (SC_RelayState->InputChannel < 0xEu)
			Givebyte_2000C64CVal_sub_80308BE(SC_RelayState->InputChannel, 1);
		if (SC_RelayState->OutputChannel < 0xEu)
			Givebyte_2000C64CVal_sub_80308BE(SC_RelayState->OutputChannel + 0xE, 1);
		if (SC_RelayState->InputChannel != SC_RelayState->OutputChannel)
			SetCmmst462DVal_sub_802F1D8(0);
		if (!SC_RelayState->InputChannel && SC_RelayState->OutputChannel == 0xA)
			SetCmmst462DVal_sub_802F1D8(1);
		if (!SC_RelayState->LogicType)
			Givebyte_2000C64CVal_sub_80308BE(0x1Fu, 1);
		if (SC_RelayState->LogicType == 1)
			Givebyte_2000C64CVal_sub_80308BE(0x1Fu, 0);
		if (SC_RelayState->LevelType == 0xC)
			Givebyte_2000C64CVal_sub_80308BE(0x1Eu, 0);
		if (SC_RelayState->LevelType == 5)
			Givebyte_2000C64CVal_sub_80308BE(0x1Eu, 1);
		Dts = SC_RelayState->Dts;
		if (Dts == 1)
		{
			Givebyte_2000C64CVal_sub_80308BE(0x22u, 1);
			goto LABEL_42;
		}
		if (SC_RelayState->Dts)
		{
			if (Dts == 3)
			{
				Givebyte_2000C64CVal_sub_80308BE(0x24u, 1);
				goto LABEL_42;
			}
			if (Dts < 3)
			{
				Givebyte_2000C64CVal_sub_80308BE(0x23u, 1);
				goto LABEL_42;
			}
		}
		Givebyte_2000C64CVal_sub_80308BE(0x22u, 0);
		Givebyte_2000C64CVal_sub_80308BE(0x23u, 0);
		Givebyte_2000C64CVal_sub_80308BE(0x24u, 0);
	LABEL_42:
		if (SC_RelayState->LLine == 1 && SC_RelayState->OutputChannel != 0xD)
		{
			Givebyte_2000C64CVal_sub_80308BE(0x29u, 1);
			Givebyte_2000C64CVal_sub_80308BE(0x28u, 1);
		}
		if (SC_RelayState->LLine == 2 && SC_RelayState->InputChannel >= 0xEu)
		{
			Givebyte_2000C64CVal_sub_80308BE(0x29u, 0);
			Givebyte_2000C64CVal_sub_80308BE(0x28u, 1);
			SetCmmst462DVal_sub_802F1D8(1);
		}
		else
		{
			Givebyte_2000C64CVal_sub_80308BE(0x29u, 1);
		}
		if (SC_RelayState->CommType == 5)
			SetCmmst462DVal_sub_802F1D8(1);
	}
LABEL_53:
	if (SC_RelayState->field_9 == 1)
		Givebyte_2000C64CVal_sub_80308BE(0x21u, 1);
	if (SC_RelayState->field_A == 1)
	{
		Givebyte_2000C64CVal_sub_80308BE(0, 1);
		Givebyte_2000C64CVal_sub_80308BE(0x29u, 1);
		Givebyte_2000C64CVal_sub_80308BE(0x28u, 0);
	}
	GPIOWrite_sub_803092C();
}




void SetCmmst462DVal_sub_802F1D8(char result)
{
	UsartSendIsSuccessFlage_20004A2D = result;
}


// 设置GPIO端口 是清除端口还是设置端口的 数组值
void Givebyte_2000C64CVal_sub_80308BE(unsigned __int8 a1, char a2)
{
	__int16 v2; // r3

	if (a1 < 0x30u)
	{
		v2 = a1 % 8;
		if (a2)
			GPIOPinWriteVal_2000C64C[a1 / 8] |= 1 << v2;
		else
			GPIOPinWriteVal_2000C64C[a1 / 8] &= ~(1 << v2);
	}
}


//打开对应GPIO端口
int ComOpen_sub_80B1AEC_802F7DE(char COM_ECUPORT, COM_PORTMODE *SC_com_portMode)
{
	USART_InitTypeDef USART_InitStruct; // [sp+0h] [bp-20h] BYREF

	COM_ECUPORT_20004A2C = COM_ECUPORT;
	SetGPIOTIM_sub_802F0D4(COM_ECUPORT);
	if (COM_ECUPORT != 2)
	{
		USART_InitStruct.USART_BaudRate = SC_com_portMode->BaudRate;
		USART_InitStruct.USART_WordLength = SC_com_portMode->WordLength;
		USART_InitStruct.USART_StopBits = SC_com_portMode->StopBits;
		USART_InitStruct.USART_Parity = SC_com_portMode->Parity;
		USART_InitStruct.USART_HardwareFlowControl = 0;
		USART_InitStruct.USART_Mode = 12;
		USART_Init_8033448(pUSART_200048BC[COM_ECUPORT], &USART_InitStruct);
		USART_Cmd_8033544(pUSART_200048BC[COM_ECUPORT], 1);
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT], 64);
		if (USART_GetFlagStatus_sub_80335C6(pUSART_200048BC[COM_ECUPORT], 0x20u))
			USART_ReceiveData_sub_8033568(pUSART_200048BC[COM_ECUPORT]);
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT], 8);
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT], 4);
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT], 1);
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT], 2);
	}
	return 1;
}



void SetGPIOTIM_sub_802F0D4(unsigned __int8 a1)
{

}


//将某一个GPIO的引脚设置为1 并打开这一路的时钟  设置延时参数 参考IDA 代码 
void IOCTRLSelect_sub_8030606(unsigned __int8 IoIndex, unsigned __int8 IoMode)
{
	IoIndex_2000C6B4 = IoIndex;
	//GPIO_WriteBit_80312F6(dword_20004664[IoIndex], word_803085C[IoIndex], 1);
	IoMode_2000C6B5 = IoMode & 1;
	//RCC_AHB1PeriphClockCmd_sub_8032BAE(dword_8030800[IoIndex_2000C6B4], 1);
	//if ((IoMode & 2) != 0)
		//GPIO_Init_sub_80305D4();
	//else
		//GPIO_Init_sub_8030580();
}

//选择GPIO引脚设置为1 并延时
void IOCTRLSet_sub_8030658(char IOCtrl, int DelayMs)
{
	int v3; // r0

	//GPIO_WriteBit_80312F6(dword_20004664[IoIndex_2000C6B4], word_803085C[IoIndex_2000C6B4], IOCtrl);
	if (DelayMs)
	{
		if (IoMode_2000C6B5 == 1)
			v3 = DelayMs;
		else
			v3 = 1000 * DelayMs;
		//SetSysTickLOAD_sub_8031144(v3);
		//Delay_sub_8031194();
	}

}


//复用GPIO 引脚 设置时钟
void GPIO_PinAFConfigsub_802F062()
{
	RCC_AHB1PeriphClockCmd_sub_8032BAE(4, 1);
	RCC_APB1PeriphClockCmd_sub_8032C08(0x80000, 1);
	//GPIO_PinAFConfig_sub_8031304(dword_200048E0, 0xAu, 8u);
	//GPIO_PinAFConfig_sub_8031304(dword_200048F4, 0xBu, 8u);
}


//关闭tim 定时器
void TimerRelease_sub_802EF76(char index)
{
	//TIM_ITConfig_80332AE(pTIMArr_200049C4[index], 1, 0);
	//TimerStop_sub_802EF10(index);
}



void SetPWMLink_sub_802C398()
{
	if (Keep_Link_200046C0.IdleTime / SC_TagKWP2000_20004974.m_MsTime < ++Keep_Link_200046C0.timeCount
		&& Keep_Link_200046C0.IdleTime)
	{
		PWM_Init_sub_8032164();
		PWMData = Keep_Link_200046C0.dataBuf[2];
		if (!PWM_Send_sub_803216E(Keep_Link_200046C0.dataBuf, Keep_Link_200046C0.idleSendLen, 1, PWMLinkAddrBuf))
		{
			Delay_802EF34(1);
			PWM_Send_sub_803216E(Keep_Link_200046C0.dataBuf, Keep_Link_200046C0.idleSendLen, 1, PWMLinkAddrBuf);
		}
		Keep_Link_200046C0.linkState = 1;
		Keep_Link_200046C0.timeCount = 0;
	}
}


//PWM 初始化 包括GPIO 初始化 和TIM定时器 和850初始化差不多 多了TIM_DeInit_8032D5C 具体内容参考IDA
void PWM_Init_sub_8032164()
{

}


//这函数 看不懂 
BOOL PWM_Send_sub_803216E(unsigned __int8 *SendBuf, unsigned __int8 framesize, char Flag, unsigned __int8 *Addrress)
{
	return TRUE;
}


void TimerStop_sub_802EF10(char a1)
{

}

void Copysub_802FB50(void *a1, void *a2, int Len)
{
	memcpy(a1, a2, Len);
}



void setCanbusLinkDataToken_sub_802BEB4()
{
	int DataLen; // r3
	unsigned __int8 *temp_1; // r4
	int i; // r0

	if (Keep_Link_200046C0.dataBuf[3] == 0x61 && (unsigned int)Keep_Link_200046C0.dataBuf[4] - 1 <= 2)
	{
		byte_2000C6BB = Keep_Link_200046C0.dataBuf[4] == 3;
		DataLen = Keep_Link_200046C0.dataBuf[5] & 0xF;
		SC_TagISO15765_2000C334.m_chHoldDig.DLC = Keep_Link_200046C0.dataBuf[5] & 0xF;
		if ((Keep_Link_200046C0.dataBuf[5] & 0x40) != 0)
			SC_TagISO15765_2000C334.m_chHoldDig.RTR = 2;
		else
			SC_TagISO15765_2000C334.m_chHoldDig.RTR = 0;
		if ((Keep_Link_200046C0.dataBuf[5] & 0x80) != 0)
		{
			SC_TagISO15765_2000C334.m_chHoldDig.IDE = 4;
			temp_1 = (_BYTE *)(&Keep_Link_200046C0 + 0x1C);
			SC_TagISO15765_2000C334.m_chHoldDig.ExtId = (unsigned int)(Keep_Link_200046C0.dataBuf[9]
				+ (Keep_Link_200046C0.dataBuf[6] << 0x18)
				+ (Keep_Link_200046C0.dataBuf[7] << 0x10)
				+ (Keep_Link_200046C0.dataBuf[8] << 8)) >> 3;
		}
		else
		{
			SC_TagISO15765_2000C334.m_chHoldDig.IDE = 0;
			temp_1 = (_BYTE *)(&Keep_Link_200046C0 + 0x1A);
			SC_TagISO15765_2000C334.m_chHoldDig.StdId = (unsigned int)(Keep_Link_200046C0.dataBuf[7]
				+ (Keep_Link_200046C0.dataBuf[6] << 8)) >> 5;
			// while (dataLenth--)
			//                     {
			//                         //有效数据
			//                         SC_TagISO15765.m_chHoldDig.Data[i++] = * (temp_1++);
			//                     }
		}
		for (i = 0; (_BYTE)DataLen--; ++i)        // 这里for循环
			Keep_Link_200046C0.dataBuf[i+4] = *temp_1++;//这里的偏移不知道对不对 验证
	}
}


//设置定时时间 清除定时中断 重新设置定时器 参考IDA中代码
int TimerConfig_sub_802EDAE(char TimeIndex, unsigned __int8 a2)
{
	return 1;
}

//装载函数在定时器中去执行
void TimerInterruptFuntionLoad_sub_802EF66(unsigned __int8 Index, int FunAddr)
{
	if ((char)Index < 3)
		TIMInterruptFunAddr_2000C5B0[(char)Index + 0x10] = (void(*)(void))FunAddr;
}


//配置定时器中断
void TIM_sub_802EEEC(char a1)
{
	return;
}

//定时器中断中接收can 数据的函数
void SC_CML_ISO15765_Time_sub_802DFC8()
{
	if ((int)(Keep_Link_200046C0.IdleTime / 0xA) < ++SC_TagISO15765_2000C334.m_nMScount && Keep_Link_200046C0.IdleTime)
	{
		SC_TagISO15765_2000C334.m_nMScount = 0;
		if (!byte_2000C6BB)
		{
			if (CANRecv_sub_8031D7C(&SC_TagISO15765_2000C334.m_RXM, 1))
				receive_buff_2000BF20[260] = 0;
			else
				++receive_buff_2000BF20[260];
			if (receive_buff_2000BF20[260] >= 0xAu)
				TimerStop_sub_802EF10(0);
		}
		SetCanFrame_sub_80319D8((CanRxMsg *)&SC_TagISO15765_2000C334.m_chHoldDig);
	}
}

//接收can 包
int CANRecv_sub_8031D7C(CanRxMsg *a1, __int16 DelayCnt)
{
	return 1;
}

//设置can链路保持帧 感觉是这样 实现 参考IDA
BOOL SetCanFrame_sub_80319D8(CanRxMsg *CANTxMsg)
{
	return 1;
}




// // Funtion: 普通协议链路保持中断处理函数
// // Input  : 无
// // Output : 无
// // Return : void
// // Info   :
void SC_setlinkkeep_sub_802C1EC()
{
	++Keep_Link_200046C0.timeCount;
	switch (Keep_Link_200046C0.rightState)
	{
	case 1u:
		Keep_Link_200046C0.timeCount = 0;
		if (Keep_Link_200046C0.idleSendLen)
		{
			ComSendByte_sub_802F1E0(Keep_Link_200046C0.dataBuf[Keep_Link_200046C0.chCount]);
			if (++Keep_Link_200046C0.chCount >= (unsigned int)Keep_Link_200046C0.idleSendLen)
			{
				Keep_Link_200046C0.rightState = 2;
				Keep_Link_200046C0.timeCount = 0;
				Keep_Link_200046C0.chCount = 0;
			}
		}
		break;
	case 5u:
		if (Keep_Link_200046C0.IdleTime / SC_TagKWP2000_20004974.m_MsTime < Keep_Link_200046C0.timeCount// 这个偏移c是个什么值
			&& Keep_Link_200046C0.IdleTime)
		{
			Keep_Link_200046C0.linkState = 1;
			Keep_Link_200046C0.timeCount = 0;
			Keep_Link_200046C0.chCount = 0;
			if (sub_802FA88() == 3)
				ComSend_sub_802F3A4(Keep_Link_200046C0.dataBuf[Keep_Link_200046C0.chCount], 0);
			else
				ComSendByte_sub_802F1E0(Keep_Link_200046C0.dataBuf[Keep_Link_200046C0.chCount]);
			if (++Keep_Link_200046C0.chCount < (unsigned int)Keep_Link_200046C0.idleSendLen)
			{
				Keep_Link_200046C0.rightState = 1;
			}
			else
			{
				Keep_Link_200046C0.rightState = 2;
				Keep_Link_200046C0.timeCount = 0;
				Keep_Link_200046C0.chCount = 0;
			}
		}
		break;
	case 2u:
		while (Keep_Link_200046C0.chCount < (unsigned int)Keep_Link_200046C0.idleRecvLen)
		{
			if (!ComByte_sub_802F6CC(&receive_buff_2000BF20[0x104], 0x3E8))
			{
				Keep_Link_200046C0.rightState = 5;
				Keep_Link_200046C0.chCount = 0;
				return;
			}
			++Keep_Link_200046C0.chCount;
		}
		Keep_Link_200046C0.rightState = 5;
		break;
	}
}


//串口发送命令函数 每次发送一个字节
void ComSendByte_sub_802F1E0(unsigned int ArgvData)
{
	unsigned __int8 Data; // r4
	char i; // r5
	char BfPos; // r5
	unsigned int v4; // r0
	unsigned int v5; // r0
	unsigned __int8 Buf[16]; // [sp+0h] [bp-20h] BYREF

	Data = ArgvData;
	*(_DWORD *)&Buf[4] = 0;
	*(_DWORD *)&Buf[8] = 0;
	*(_DWORD *)&Buf[0xC] = 0x100;
	if (COM_ECUPORT_20004A2C == 2)
	{
		Buf[0] = 1;
		for (i = 1; i != 9; ++i)
		{
			if (((unsigned __int8)ArgvData & Buf[0]) != 0)
				Buf[i + 4] = 1;
			Buf[0] *= 2;
		}
		BfPos = 0;
		TIM_SetCounter_8032F42(&TIM3_BASE_40000400, 0);
		TIM_ClearFlag_80332DC(&TIM3_BASE_40000400, 1);
		TIM_UpdateDisableConfig_8032F62(&TIM3_BASE_40000400, 1);
		while (BfPos != 0xA)
		{
			if (TIM_GetFlagStatus_80332C4(&TIM3_BASE_40000400, 1))
			{
				if (Buf[BfPos + 4])
					GPIO_WriteBit_80312F6(&GPIOC_BASE_40020800, 0x40, 0);
				else
					GPIO_WriteBit_80312F6(&GPIOC_BASE_40020800, 0x40, 1);
				++BfPos;
				TIM_ClearFlag_80332DC(&TIM3_BASE_40000400, 1);
			}
		}
		TIM_UpdateDisableConfig_8032F62(&TIM3_BASE_40000400, 0);
	}
	else
	{
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x40);
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT_20004A2C], 8);
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x100);
		if (USART_GetFlagStatus_sub_80335C6(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x20u))
			USART_ReceiveData_sub_8033568(pUSART_200048BC[COM_ECUPORT_20004A2C]);
		USART_SendData_sub_8033560(pUSART_200048BC[COM_ECUPORT_20004A2C], Data);
		*(_DWORD *)Buf = 0;
		while (!USART_GetFlagStatus_sub_80335C6(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x40u))
		{
			v4 = (*(_DWORD *)Buf)++;
			if (v4 >= 120001)
				return;
		}
		if (UsartSendIsSuccessFlage_20004A2D)
		{
			*(_DWORD *)Buf = 0;
			do
			{
				if (USART_GetFlagStatus_sub_80335C6(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x20u))
					break;
				v5 = (*(_DWORD *)Buf)++;
			} while (v5 < 120001);
		}
		USART_ReceiveData_sub_8033568(pUSART_200048BC[COM_ECUPORT_20004A2C]);
	}
}


//返回COM_ECUPORT_20004A2C的值
int sub_802FA88()
{
	return COM_ECUPORT_20004A2C;
}



void ComSend_sub_802F3A4(unsigned __int8 UsArtData, char Flag)
{
	char i; // r6
	unsigned int v4; // r0
	unsigned int v5; // r0
	char v6; // [sp+0h] [bp-18h]
	int v7; // [sp+0h] [bp-18h]
	unsigned int v8; // [sp+0h] [bp-18h]
	unsigned int v9; // [sp+0h] [bp-18h]

	v6 = 0;
	for (i = 1; i; i *= 2)
	{
		if ((UsArtData & (unsigned __int8)i) != 0)
			++v6;
	}
	v7 = v6 & 1;
	if (Flag || !v7)
	{
		if (!Flag || v7)
			USART2->CR1 &= 0xFDFFu;
		else
			USART2->CR1 |= 0x200u;
	}
	else
	{
		USART2->CR1 |= 0x200u;
	}
	USART_ClearFlag_80335E6(USART2, 0x40);
	USART_ClearFlag_80335E6(USART2, 0x100);
	USART_SendData_sub_8033560(USART2, UsArtData);
	v8 = 0;
	while (!USART_GetFlagStatus_sub_80335C6(USART2, 0x40u))
	{
		v4 = v8++;
		if (v4 >= 120001)
			return;
	}
	if (UsartSendIsSuccessFlage_20004A2D)
	{
		v9 = 0;
		do
		{
			if (USART_GetFlagStatus_sub_80335C6(USART2, 0x20u))
				break;
			v5 = v9++;
		} while (v5 < 120001);
	}
	USART_ReceiveData_sub_8033568(USART2);
}


int ComByte_sub_802F6CC(unsigned __int8 *Rcv, __int16 Count)
{
	int result; // r0

	if (COM_ECUPORT_20004A2C == 2)
	{
	LABEL_10:
		if (COM_ECUPORT_20004A2C == 3 && USART_GetFlagStatus_sub_80335C6(pUSART_200048BC[COM_ECUPORT_20004A2C], 1u))
			USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT_20004A2C], 1);
		TIM_UpdateDisableConfig_8032F62(&TIM3_BASE_40000400, 0);
		result = 0;
	}
	else
	{
		TIM_SetCounter_8032F42(&TIM3_BASE_40000400, 0);
		TIM_ClearFlag_80332DC(&TIM3_BASE_40000400, 1);
		TIM_UpdateDisableConfig_8032F62(&TIM3_BASE_40000400, 1);
		while (1)
		{
			if (USART_GetFlagStatus_sub_80335C6(pUSART_200048BC[COM_ECUPORT_20004A2C], 8u))
			{
				USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT_20004A2C], 8);
				USART_ReceiveData_sub_8033568(pUSART_200048BC[COM_ECUPORT_20004A2C]);
			}
			if (USART_GetFlagStatus_sub_80335C6(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x20u))
				break;
			if (TIM_GetFlagStatus_80332C4(&TIM3_BASE_40000400, 1))
			{
				TIM_ClearFlag_80332DC(&TIM3_BASE_40000400, 1);
				--Count;
			}
			if (!Count)
				goto LABEL_10;
		}
		*Rcv = USART_ReceiveData_sub_8033568(pUSART_200048BC[COM_ECUPORT_20004A2C]);
		TIM_UpdateDisableConfig_8032F62(&TIM3_BASE_40000400, 0);
		result = 1;
	}
	return result;
}


//通过拉低拉高GPIO 引脚 发送地址码数据
void sendAddressToEcu_sub_802CF50(char ArgvData, unsigned int DelayMs)
{
	ComClose_sub_80B1D06_sub_802FA28(1);
	IOCTRLSet_sub_8030658(1, 0x64);
	IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	if ((ArgvData & 1) != 0)
		IOCTRLSet_sub_8030658(1, 1000000 / DelayMs);
	else
		IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	if ((ArgvData & 2) != 0)
		IOCTRLSet_sub_8030658(1, 1000000 / DelayMs);
	else
		IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	if ((ArgvData & 4) != 0)
		IOCTRLSet_sub_8030658(1, 1000000 / DelayMs);
	else
		IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	if ((ArgvData & 8) != 0)
		IOCTRLSet_sub_8030658(1, 1000000 / DelayMs);
	else
		IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	if ((ArgvData & 0x10) != 0)
		IOCTRLSet_sub_8030658(1, 1000000 / DelayMs);
	else
		IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	if ((ArgvData & 0x20) != 0)
		IOCTRLSet_sub_8030658(1, 1000000 / DelayMs);
	else
		IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	if ((ArgvData & 0x40) != 0)
		IOCTRLSet_sub_8030658(1, 1000000 / DelayMs);
	else
		IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	if ((ArgvData & 0x80) != 0)
		IOCTRLSet_sub_8030658(1, 1000000 / DelayMs);
	else
		IOCTRLSet_sub_8030658(0, 1000000 / DelayMs);
	IOCTRLSet_sub_8030658(1, 1);
}



// 使能L线
void EnableLLine_1_sub_802C560()
{
	SC_RelayState_200049DC.LLine = 1;
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
}



// 参数A1 延时次数
//自动 确认通讯的波特率 不知道这个函数什么原理 
unsigned int autoCheckBaudRate_sub_802CE7E(int DelayCnt)
{
	int i; // r6
	unsigned int v3; // r7
	unsigned int v5; // r7
	unsigned int v6; // r7
	int v7; // r7

	/*for (i = 0; i < DelayCnt && AboutSysTicksub_8030788(0, 100000u) != 1; ++i)
		;
	v3 = sub_803070C(10000u);
	if (v3 == 10000)
		return 0;
	if (!AboutSysTicksub_8030788(1, 10000u))
		return 0;
	v5 = sub_803070C(10000u) + v3;
	if (!AboutSysTicksub_8030788(0, 10000u))
		return 0;
	v6 = sub_803070C(10000u) + v5;
	AboutSysTicksub_8030788(1, 0x2710u);
	v7 = sub_803070C(0x2710u) + v6;
	AboutSysTicksub_8030788(0, 0x2710u);
	AboutSysTicksub_8030788(1, 0x2710u);
	AboutSysTicksub_8030788(0, 0x2710u);
	AboutSysTicksub_8030788(1, 0x2710u);
	AboutSysTicksub_8030788(0, 0x2710u);
	AboutSysTicksub_8030788(1, 0x2710u);
	return 0xF4240u / ((v7 >> 2) - 1);*/
	return 1;
}


//GPIO 引脚设置 
void IOCTRLInit_sub_802C570()
{
	SC_RelayState_200049DC.LLine = 0;
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
}



// //------------------------------------------------------------------------------
// // Funtion: 采用模拟方式发送5bps地址
// // Input  : 参数1：PAKRECV结构体指针
// // Output : none
// // Return : 无
// // Info   :
// //------------------------------------------------------------------------------
void sendAddressToEcu_sub_802CC82(char fiveBpsAddr)
{
	ComClose_sub_80B1D06_sub_802FA28(1);
	IOCTRLSet_sub_8030658(1, 100000);
	IOCTRLSet_sub_8030658(0, 200000);
	if ((fiveBpsAddr & 1) != 0)
		IOCTRLSet_sub_8030658(1, 200000);
	else
		IOCTRLSet_sub_8030658(0, 200000);
	if ((fiveBpsAddr & 2) != 0)
		IOCTRLSet_sub_8030658(1, 200000);
	else
		IOCTRLSet_sub_8030658(0, 200000);
	if ((fiveBpsAddr & 4) != 0)
		IOCTRLSet_sub_8030658(1, 200000);
	else
		IOCTRLSet_sub_8030658(0, 200000);
	if ((fiveBpsAddr & 8) != 0)
		IOCTRLSet_sub_8030658(1, 200000);
	else
		IOCTRLSet_sub_8030658(0, 200000);
	if ((fiveBpsAddr & 0x10) != 0)
		IOCTRLSet_sub_8030658(1, 200000);
	else
		IOCTRLSet_sub_8030658(0, 200000);
	if ((fiveBpsAddr & 0x20) != 0)
		IOCTRLSet_sub_8030658(1, 200000);
	else
		IOCTRLSet_sub_8030658(0, 200000);
	if ((fiveBpsAddr & 0x40) != 0)
		IOCTRLSet_sub_8030658(1, 200000);
	else
		IOCTRLSet_sub_8030658(0, 200000);
	if ((fiveBpsAddr & 0x80) != 0)
		IOCTRLSet_sub_8030658(1, 200000);
	else
		IOCTRLSet_sub_8030658(0, 200000);
	IOCTRLSet_sub_8030658(1, 1);
}



void sendAddressToEcu_sub_802CD84(char fiveBpsAddr)
{
	ComClose_sub_80B1D06_sub_802FA28(1);
	IOCTRLSet_sub_8030658(1, 0x186A0);
	IOCTRLSet_sub_8030658(0, 0x30D40);
	if ((fiveBpsAddr & 1) != 0)
		IOCTRLSet_sub_8030658(1, 0x30D40);
	else
		IOCTRLSet_sub_8030658(0, 0x30D40);
	if ((fiveBpsAddr & 2) != 0)
		IOCTRLSet_sub_8030658(1, 0x30D40);
	else
		IOCTRLSet_sub_8030658(0, 0x30D40);
	if ((fiveBpsAddr & 4) != 0)
		IOCTRLSet_sub_8030658(1, 0x30D40);
	else
		IOCTRLSet_sub_8030658(0, 0x30D40);
	if ((fiveBpsAddr & 8) != 0)
		IOCTRLSet_sub_8030658(1, 0x30D40);
	else
		IOCTRLSet_sub_8030658(0, 0x30D40);
	if ((fiveBpsAddr & 0x10) != 0)
		IOCTRLSet_sub_8030658(1, 0x30D40);
	else
		IOCTRLSet_sub_8030658(0, 0x30D40);
	if ((fiveBpsAddr & 0x20) != 0)
		IOCTRLSet_sub_8030658(1, 0x30D40);
	else
		IOCTRLSet_sub_8030658(0, 0x30D40);
	if ((fiveBpsAddr & 0x40) != 0)
		IOCTRLSet_sub_8030658(1, 0x30D40);
	else
		IOCTRLSet_sub_8030658(0, 0x30D40);
	if ((fiveBpsAddr & 0x80) != 0)
		IOCTRLSet_sub_8030658(1, 0x30D40);
	else
		IOCTRLSet_sub_8030658(0, 0x30D40);
	IOCTRLSet_sub_8030658(1, 0x27100);
}


//设置继电器的哪个引脚的高低电平  具体怎么对应的不清楚
int SetRelayPara_sub_802BCD0(char a1, unsigned __int8 a2)
{
	if (a2 == 1)
	{
		SC_RelayState_200049DC.InputChannel = a1;
	}
	else if (a2)
	{
		if (a2 == 3)
		{
			SC_RelayState_200049DC.CANH = a1;
		}
		else if (a2 >= 3u)
		{
			if (a2 == 5)
			{
				SC_RelayState_200049DC.CommType = a1;
			}
			else if (a2 >= 5u)
			{
				if (a2 == 7)
				{
					SC_RelayState_200049DC.LevelType = a1;
				}
				else if (a2 >= 7u)
				{
					if (a2 == 9)
					{
						SC_RelayState_200049DC.Dts = a1;
					}
					else if (a2 < 9u)
					{
						SC_RelayState_200049DC.LLine = a1;
					}
				}
				else
				{
					SC_RelayState_200049DC.LogicType = a1;
				}
			}
			else
			{
				SC_RelayState_200049DC.CANL = a1;
			}
		}
		else
		{
			SC_RelayState_200049DC.OutputChannel = a1;
		}
	}
	return 0;
}


int pTIMArr_200049C4[6] = { 0x40000000,0x40000C00,0x40001000,0x00000001,0x00000008,0x00000010 };


void SetTIMCLOCK_RCC_APB1PeriphClockCmd_sub_802ED88(int a1)
{
	int v1; // r5
	unsigned __int8 i; // r4

	v1 = 0;
	for (i = 0; i < 3u; ++i)
		v1 |= (unsigned int)pTIMArr_200049C4[i + 3];
	RCC_APB1PeriphClockCmd_sub_8032C08(v1, 1);
}


//串口中断中执行的函数
void SC_CML_KWP1281_Time_sub_802C5B0()
{

	++SC_TagKWP1281_200043E4.m_nMScount;
	switch (Keep_Link_200046C0.rightState)
	{
	case 1u:
		if (SC_TagKWP1281_200043E4.m_chCount)
		{
			if (SC_TagKWP1281_200043E4.m_nMScount >= SC_TagKWP1281_200043E4.m_nBtyetime
				&& SC_TagKWP1281_200043E4.m_Senddata
				&& SC_TagKWP1281_200043E4.m_SendFinishFlag == 1)
			{
				ComReadSign_sub_802F614(0);
				SC_TagKWP1281_200043E4.m_nMScount = 0;
				if (SC_TagKWP1281_200043E4.m_chCount == 1)
					ComSendByteInIsr_sub_802F4BA(SC_TagKWP1281_200043E4.m_Framecount);
				else
					ComSendByteInIsr_sub_802F4BA(SC_TagKWP1281_200043E4.m_Senddata[SC_TagKWP1281_200043E4.m_chCount]);
				++SC_TagKWP1281_200043E4.m_chCount;
				SC_TagKWP1281_200043E4.m_SendFinishFlag = 0;
			}
		}
		else if (SC_TagKWP1281_200043E4.m_nFrameTime < SC_TagKWP1281_200043E4.m_nMScount
			&& SC_TagKWP1281_200043E4.m_Senddata)
		{
			ComReadSign_sub_802F614(0);
			SC_TagKWP1281_200043E4.m_nMScount = 0;
			if (SC_TagKWP1281_200043E4.m_chCount == 1)
				ComSendByteInIsr_sub_802F4BA(SC_TagKWP1281_200043E4.m_Framecount);
			else
				ComSendByteInIsr_sub_802F4BA(SC_TagKWP1281_200043E4.m_Senddata[SC_TagKWP1281_200043E4.m_chCount]);
			++SC_TagKWP1281_200043E4.m_chCount;
			SC_TagKWP1281_200043E4.m_SendFinishFlag = 0;
		}
		break;
	case 3u:
		if (SC_TagKWP1281_200043E4.m_nMScount >= SC_TagKWP1281_200043E4.m_ReserveTime
			&& SC_TagKWP1281_200043E4.m_SendFinishFlag == 1)
		{
			SC_TagKWP1281_200043E4.m_nMScount = 0;
			ComReadSign_sub_802F614(0);
			ComSendByteInIsr_sub_802F4BA(-1 - SC_TagKWP1281_200043E4.m_Reverse);
			SC_TagKWP1281_200043E4.m_SendFinishFlag = 0;
		}
		break;
	case 5u:
		if (SC_TagKWP1281_200043E4.m_LinkFG)
		{
			if (SC_TagKWP1281_200043E4.m_Idletime < SC_TagKWP1281_200043E4.m_nMScount)
			{
				if (SC_TagKWP1281_200043E4.m_Idletime)
				{
					ComReadSign_sub_802F614(0);
					SC_TagKWP1281_200043E4.m_nMScount = 0;
					SC_TagKWP1281_200043E4.m_chCount = 0;
					SC_TagKWP1281_200043E4.m_Senddata = (_BYTE *)(&SC_TagKWP1281_200043E4 + 160);
					SC_TagKWP1281_200043E4.m_Lenth = SC_TagKWP1281_200043E4.m_chHoldDataLen;
					if (SC_TagKWP1281_200043E4.m_chHoldDataLen)
					{
						ComSendByteInIsr_sub_802F4BA(SC_TagKWP1281_200043E4.m_Senddata[SC_TagKWP1281_200043E4.m_chCount]);
						++SC_TagKWP1281_200043E4.m_chCount;
						Keep_Link_200046C0.rightState = 1;
						SC_TagKWP1281_200043E4.m_SendFinishFlag = 0;
					}
				}
			}
		}
		break;
	}
	return ;
}


//串口发送使能 或者禁止发送
void ComReadSign_sub_802F614(int result)
{
	if ((unsigned __int8)result == 1)
		pUSART_200048BC[COM_ECUPORT_20004A2C]->CR1 |= 4u;
	else
		pUSART_200048BC[COM_ECUPORT_20004A2C]->CR1 &= 0xFFFBu;
}


//串口发送数据
void ComSendByteInIsr_sub_802F4BA(unsigned __int8 Framecount)
{
	char v1; // r6
	char i; // r5
	char v3; // r5
	unsigned __int8 v4[12]; // [sp+0h] [bp-20h] BYREF

	*(_DWORD *)v4 = 0;
	*(_DWORD *)&v4[4] = 0;
	*(_DWORD *)&v4[8] = 0x100;
	if (COM_ECUPORT_20004A2C == 2)
	{
		v1 = 1;
		for (i = 1; i != 9; ++i)
		{
			if ((Framecount & (unsigned __int8)v1) != 0)
				v4[i] = 1;
			v1 *= 2;
		}
		v3 = 0;
		TIM_SetCounter_8032F42(&TIM3_BASE_40000400, 0);
		TIM_ClearFlag_80332DC(&TIM3_BASE_40000400, 1);
		TIM_UpdateDisableConfig_8032F62(&TIM3_BASE_40000400, 1);
		while (v3 != 0xA)
		{
			if (TIM_GetFlagStatus_80332C4(&TIM3_BASE_40000400, 1))
			{
				if (v4[v3])
					GPIO_WriteBit_80312F6(&GPIOC_BASE_40020800, 0x40, 0);
				else
					GPIO_WriteBit_80312F6(&GPIOC_BASE_40020800, 0x40, 1);
				++v3;
				TIM_ClearFlag_80332DC(&TIM3_BASE_40000400, 1);
			}
		}
		TIM_UpdateDisableConfig_8032F62(&TIM3_BASE_40000400, 0);
	}
	else
	{
		USART_SendData_sub_8033560(pUSART_200048BC[COM_ECUPORT_20004A2C], Framecount);
	}
}


void ComInterruptFuntionLoad_sub_802F8A0(int FunAddr, unsigned __int8 a2)
{
	if (COM_ECUPORT_20004A2C != 2 && a2 < 6u)
	{
		*(&ComInterruptFunAddr_2000C23C[5 * COM_ECUPORT_20004A2C] + a2) = (void(*)(void))FunAddr;
		if (!a2)
		{
			USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x40);
			USART_ITConfig_sub_8033570(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x26u, 1);
		}
		if (a2 == 1)
		{
			USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x20);
			USART_ITConfig_sub_8033570(pUSART_200048BC[COM_ECUPORT_20004A2C], 0x25u, 1);
		}
	}
}



//串口中断中执行的函数
void SC_CML_KWP1281_Comread_sub_802C860()
{
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	if (Keep_Link_200046C0.rightState == 2)
	{
		SC_TagKWP1281_200043E4.m_Reverse = sub_802F660();
		SC_TagKWP1281_200043E4.m_chTemp[SC_TagKWP1281_200043E4.m_chCount++] = SC_TagKWP1281_200043E4.m_Reverse;
		if (SC_TagKWP1281_200043E4.m_chCount == 1)
			SC_TagKWP1281_200043E4.m_Lenth = SC_TagKWP1281_200043E4.m_Reverse + 1;
		if (SC_TagKWP1281_200043E4.m_chCount == 2)
			SC_TagKWP1281_200043E4.m_Framecount = SC_TagKWP1281_200043E4.m_Reverse + 1;
		if (SC_TagKWP1281_200043E4.m_chCount == SC_TagKWP1281_200043E4.m_Lenth)
		{
			Keep_Link_200046C0.rightState = 5;
			SC_TagKWP1281_200043E4.m_chCount = 0;
		}
		else
		{
			Keep_Link_200046C0.rightState = 3;
		}
	}
	else if (Keep_Link_200046C0.rightState == 4)
	{
		Keep_Link_200046C0.rightState = 1;
	}
	TIM_SetCounter_sub_802EF52(0);
	SC_TagKWP1281_200043E4.m_nMScount = 0;
}



//如果 要看这个函数返回值 只能调试 看接收的内容是什么
int sub_802F660()
{
	unsigned __int8 v0; // r4

	if (COM_ECUPORT_20004A2C == 2)
		v0 = 0;
	else
		v0 = USART_ReceiveData_sub_8033568(pUSART_200048BC[COM_ECUPORT_20004A2C]);
	if (COM_ECUPORT_20004A2C == 3 && USART_GetFlagStatus_sub_80335C6(pUSART_200048BC[COM_ECUPORT_20004A2C], 1u))
		USART_ClearFlag_80335E6(pUSART_200048BC[COM_ECUPORT_20004A2C], 1);
	return v0;
}


//设置TIMx 计数寄存器的值
void TIM_SetCounter_sub_802EF52(char a1)
{
	TIM_SetCounter_8032F42((TIM_TypeDef*)pTIMArr_200049C4[a1], 0);
}

//串口中断中执行的函数
void SC_CML_KWP1281_Comsend_sub_802C7DC()
{
	if (Keep_Link_200046C0.rightState == 1)
	{
		if (SC_TagKWP1281_200043E4.m_chCount == SC_TagKWP1281_200043E4.m_Lenth)
		{
			SC_TagKWP1281_200043E4.m_Senddata = 0;
			SC_TagKWP1281_200043E4.m_chCount = 0;
			Keep_Link_200046C0.rightState = 2;
		}
		else
		{
			Keep_Link_200046C0.rightState = 4;
			TIM_SetCounter_sub_802EF52(0);
		}
	}
	else if (Keep_Link_200046C0.rightState == 3)
	{
		Keep_Link_200046C0.rightState = 2;
	}
	SC_TagKWP1281_200043E4.m_SendFinishFlag = 1;
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	ComReadSign_sub_802F614(1);
}


// // Funtion: 关闭定时器，清空计数器
// // Input  : 无
// // Output : 无
// // Return : void
// // Info  
void set_time0Stop_sub_802BB48()
{
	int DelayTime; // r4

	if (DelayTime_2000C53C)
	{
		DelayTime = FrameTime_2000C534;
	}
	else if (SC_RelayState_200049DC.CommType)
	{
		DelayTime = 0;
	}
	else
	{
		DelayTime = SC_TagKWP2000_20004974.m_nFrameTime;
	}
	switch (timer_open_flag_2000C6B7)
	{
	case 1u:
		while (Keep_Link_200046C0.rightState != 5)
			;
		TimerStop_sub_802EF10(0);
		if (Keep_Link_200046C0.linkState != 1 || Keep_Link_200046C0.idleRecvLen)
		{
			if (SC_TagISO15765_2000C334.m_nMScount && SC_TagKWP2000_20004974.m_MsTime)
			{
				if (SC_TagISO15765_2000C334.m_nMScount * SC_TagKWP2000_20004974.m_MsTime < DelayTime)
					Delay_802EF34(DelayTime - SC_TagKWP2000_20004974.m_MsTime * SC_TagISO15765_2000C334.m_nMScount);
			}
			else
			{
				Delay_802EF34(DelayTime);
			}
		}
		else
		{
			Delay_802EF34(Keep_Link_200046C0.IdleTime >> 1);
		}
		Keep_Link_200046C0.linkState = 0;
		break;
	case 2u:
		while (Keep_Link_200046C0.rightState != 5)
			;
		TimerStop_sub_802EF10(0);
		if (Keep_Link_200046C0.linkState == 1)
			Delay_802EF34(Keep_Link_200046C0.IdleTime);
		Keep_Link_200046C0.linkState = 0;
		break;
	case 3u:
		TimerStop_sub_802EF10(1);
		if (Keep_Link_200046C0.linkState == 1)
			Delay_802EF34(Keep_Link_200046C0.IdleTime >> 1);
		Keep_Link_200046C0.linkState = 0;
		break;
	default:
		if (SC_TagKWP2000_20004974.UnknowByte)
			Delay_802EF34(DelayTime);
		else
			SC_TagKWP2000_20004974.UnknowByte = 1;  // 这个字段没弄明白是什么意思
		break;
	}
	if (!Keep_Link_200046C0.field_46)
		Keep_Link_200046C0.timeCount = 0;
	SC_TagISO15765_2000C334.m_nMScount = 0;
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	receive_buff_2000BF20[0x104] = 0;
}


int SC_CML_KWP1281_Recv_sub_802CBCC(SC_PAKRECV *pakRcv)
{
	unsigned __int8 i; // r5

	while (Keep_Link_200046C0.rightState != 5)
	{
		if (SC_TagKWP1281_200043E4.m_nMScount >= 0x9C5)
			return 0;
	}
	set_time0Stop_sub_802BB48();
	pakRcv->PakLenth = SC_TagKWP1281_200043E4.m_Lenth;
	for (i = 0; i < pakRcv->PakLenth; ++i)
		pakRcv->PakdataAddr[i] = SC_TagKWP1281_200043E4.m_chTemp[i];
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	Keep_Link_200046C0.rightState = 5;
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return 1;
}


int SC_CML_KWP1281_Sendsub_802CB36(SC_PAKSEND *pakSend)
{
	while (Keep_Link_200046C0.rightState != 5)
	{
		if (SC_TagKWP1281_200043E4.m_nMScount >= 0x9C5)
			return 0;
	}
	set_time0Stop_sub_802BB48();
	if (!pakSend)
		return 1;
	SC_TagKWP1281_200043E4.m_Lenth = pakSend->PakLenth;
	SC_TagKWP1281_200043E4.m_Senddata = pakSend->PakdataAddr;
	SC_TagKWP1281_200043E4.m_chCount = 0;
	SC_TagKWP1281_200043E4.m_nMScount = 0;
	Keep_Link_200046C0.rightState = 1;
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	while (Keep_Link_200046C0.rightState == 1 || Keep_Link_200046C0.rightState == 4)
	{
		if (SC_TagKWP1281_200043E4.m_nMScount >= 0x9C5)
			return 0;
	}
	return 1;
}


// // Funtion: 进行异或校验检查
// // Input  : datalenth - 进行校验的数据长度
// //          dataPos - 进行校验的数据头指针
// // Output :
// // Return : 校验正确返回TRUE,否则返回FALSE
// // Info   :
BOOL checkXOR_Parity_sub_802BD40(int a1, unsigned __int8 *dataPos)
{
	char i; // r3

	for (i = 0; a1--; i ^= *dataPos++)
		;
	return i == 0;
}



//第二种设置链路保持的函数 在已有源码上没有这个函数
int SetLinkData_2_sub_804C77E(int a1, unsigned __int8 *Argv, unsigned __int8 *Ans)
{
	unsigned int DelayCnt; // r9
	unsigned __int8 v6; // r7
	unsigned __int8 v7; // r8
	int result; // r0

	DelayCnt = 0;
	if (CANRcv_TIM_Open_Flag_2000C6B8 == 1)
	{
		while (CANKeepLink_20004708.rightState != 5)
		{
			Delay_sub_802EF46(0x64u);
			if (++DelayCnt >= 0x2711)
			{
				CANKeepLink_20004708.rightState = 5;
				break;
			}
		}
		TimerStop_sub_802EF10(1);
	}
	v6 = *Argv;
	v7 = Argv[3];
	CANKeepLink_20004708.idleSendLen = *Argv;
	CANKeepLink_20004708.linkState = 0;
	CANKeepLink_20004708.field_46 = 0;
	if (v7)
	{
		Copysub_802FB50(CANKeepLink_20004708.dataBuf, Argv + 1, v6);
		CANKeepLink_20004708.idleRecvLen = Argv[v6 + 1];
		if (Argv[v6 + 2]
			&& ((CANKeepLink_20004708.IdleTime = 0xA * Argv[v6 + 2],
				CANKeepLink_20004708.linkType = 1,
				CANKeepLink_20004708.dataBuf[2] != 1)
				|| (byte_2000C3BC = 1, GiveValToA1CANPack_sub_802BD62(&CANKeepLink_20004708.dataBuf[3], 0)))
			&& CANKeepLink_20004708.dataBuf[2] == 2
			&& (byte_2000C3BC = 2, GiveValToA1CANPack_sub_802BD62(&CANKeepLink_20004708.dataBuf[3], 0)))
		{
			if (GiveValToA1CANPack_sub_802BD62(&CANKeepLink_20004708.dataBuf[0x12], 1u))
			{
				CANKeepLink_20004708.rightState = 5;
				TimerConfig_sub_802EDAE(1, 0xAu);
				TimerInterruptFuntionLoad_sub_802EF66(1u, (int)CAN_SetLink_sub_802E0D4);
				TIM_sub_802EEEC(1);
				CANRcv_TIM_Open_Flag_2000C6B8 = 1;
				PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
			}
			else
			{
				PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
			}
			result = 2;
		}
		else
		{
			PutDataToAns_sub_802BCBC(szFNG_20004A08, Ans, 4);
			result = 2;
		}
	}
	else
	{
		if (CANRcv_TIM_Open_Flag_2000C6B8 == 1)
		{
			while (CANKeepLink_20004708.rightState != 5)
			{
				++DelayCnt;
				Delay_sub_802EF46(0x64u);
				if (DelayCnt >= 0x2711)
				{
					CANKeepLink_20004708.rightState = 5;
					break;
				}
			}
		}
		CANKeepLink_20004708.linkType = 0;
		CANRcv_TIM_Open_Flag_2000C6B8 = 0;
		PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
		result = 2;
	}
	return result;
}



int GiveValToA1CANPack_sub_802BD62(unsigned __int8 *a1, unsigned __int8 a2)
{
	unsigned int v3; // r7
	unsigned __int8 *v4; // r3
	int v5; // r6
	unsigned __int8 *v6; // r3
	int v7; // r5
	int i; // r4

	if (a2 >= 2u)
		return 0;
	byte_2000C6BB = a1[2] == 3;
	v3 = a1[3] & 0xF;
	if (v3 >= 9)
		return 0;
	CANTxMsgArr_2000C380[a2].DLC = v3;
	if ((a1[3] & 0x40) != 0)
		CANTxMsgArr_2000C380[a2].RTR = 2;
	else
		CANTxMsgArr_2000C380[a2].RTR = 0;
	v4 = a1 + 4;
	if ((a1[3] & 0x80) != 0)
	{
		CANTxMsgArr_2000C380[a2].IDE = 4;
		v5 = *v4 << 0x18;
		v6 = a1 + 8;
		CANTxMsgArr_2000C380[a2].ExtId = (unsigned int)(a1[7] + v5 + (a1[5] << 0x10) + (a1[6] << 8)) >> 3;
	}
	else
	{
		CANTxMsgArr_2000C380[a2].IDE = 0;
		v7 = *v4 << 8;
		v6 = a1 + 6;
		CANTxMsgArr_2000C380[a2].StdId = ((unsigned int)a1[5] + v7) >> 5;
	}
	for (i = 0; (_BYTE)v3--; ++i)
		CANTxMsgArr_2000C380[a2].Data[i] = *v6++;;// CANTxMsgArr_2000C380[a2].data[i] = *v6++;
	return 1;
}


void CAN_SetLink_sub_802E0D4()
{
	++Cnt_2000C37C;
	if (Cnt_2000C37C == CANKeepLink_20004708.IdleTime / 0xE * (Cnt_2000C37C / (CANKeepLink_20004708.IdleTime / 0xE))
		&& CANKeepLink_20004708.IdleTime)
	{
		SetCanFrame_sub_8031B58(CANTxMsgArr_2000C380);
	}
	if (CANKeepLink_20004708.IdleTime / 6 < Cnt_2000C37C)
	{
		if (CANKeepLink_20004708.IdleTime)
		{
			SetCanFrame_sub_8031B58(CANTxMsgArr_2000C380);
			Cnt_2000C37C = 0;
		}
	}
}


//超过0x7FFFF 次数 就返回false 具体看IDA中实现
BOOL SetCanFrame_sub_8031B58(CanRxMsg *CANTxMsg)
{
	unsigned __int8 v1; // r5
	int v2; // r6

	v1 = CAN_Transmit_sub_8034BD8(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], CANTxMsg);
	v2 = 0;
	if (CAN_GetFlagStatus_sub_8034FA4(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0x38000001))
		CAN_ClearFlag_sub_8035020(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0x38000001);
	if (CAN_GetFlagStatus_sub_8034FA4(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0x32000010))
		CAN_ClearFlag_sub_8035020(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0x32000010);
	if (CAN_GetFlagStatus_sub_8034FA4(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0x32000008))
		CAN_ClearFlag_sub_8035020(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0x32000008);
	if (CAN_GetFlagStatus_sub_8034FA4(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0x30F00070))
		CAN_ClearFlag_sub_8035020(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0x30F00070);
	while (CAN_TransmitStatus_sub_8034CFE(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], v1) != 1 && v2 != 0x7FFFF)
	{
		if (!CAN_TransmitStatus_sub_8034CFE(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], v1))
			return 0;
		++v2;
	}
	return v2 != 0x7FFFF;
}


int CheckLLine_sub_802C580()
{
	return SC_RelayState_200049DC.LLine;
}


//设置GPIO pin 使能 同时延时
void GPIO_WriteBit_Delay_sub_803069E(char a1, char a2, unsigned int a3)
{
	unsigned int v4; // r0

	//GPIO_WriteBit_80312F6(dword_20004664[a1], word_803085C[a1], a2);
	if (a3)
	{
		if (IoMode_2000C6B5 == 1)
			v4 = a3;
		else
			v4 = 0x3E8 * a3;
		SetSysTickLOAD_sub_8031144(v4);
		Delay_sub_8031194();
	}
}

//具体实现看IDA
void SetSysTickLOAD_sub_8031144(unsigned int result)
{
	return;
}

//具体实现看IDA
void Delay_sub_8031194()
{
	return;
}


void Set2000C6BF_is_1_sub_8030D78()
{
	unk_2000C6B6 = 0;
}


void Set2000C6BF_is_1_sub_8030D70()
{
	unk_2000C6B6 = 1;                             // 不知道这个值赋值为1 是什么意思
}


//判断是否为高电平 高电平返回1 低电平返回0
BOOL IOCTRLGet_sub_80306E2()
{
	return (dword_20004664[IoIndex_2000C6B4]->IDR & (unsigned __int16)word_803085C[IoIndex_2000C6B4]) != 0;
}



void KeepLinkFrameSet_sub_802BF9E()
{
	unsigned __int8 *v0; // r5
	unsigned int i; // r0
	_BYTE *v2; // r5
	int v3; // r4
	_BYTE *v4; // r6
	unsigned __int8 *v5; // r5
	int v6; // r3
	unsigned __int8 *v7; // r5
	int v8; // r3
	int v9; // r3
	unsigned int v10; // r3
	unsigned __int8 *v11; // r5
	int v12; // r2
	unsigned __int8 *v13; // r5
	unsigned int v14; // r2
	int j; // r1

	if (Keep_Link_200046C0.dataBuf[3] == 0x61)
	{
		v0 = (_BYTE *)(&Keep_Link_200046C0 + 0x16);
		if ((unsigned int)Keep_Link_200046C0.dataBuf[4] - 1 <= 2)
		{
			for (i = 0; i < SC_TagISO15765_2000C334.m_PakMode; ++i)
			{
				byte_2000C6BB = *v0 == 3;
				v2 = v0 + 1;
				v3 = *v2 & 0xF;
				*(&SC_TagISO15765_2000C334.m_chHoldDig.DLC + 0x14 * i) = v3;
				if ((*v2 & 0x40) != 0)
					*(&SC_TagISO15765_2000C334.m_chHoldDig.RTR + 0x14 * i) = 2;
				else
					*(&SC_TagISO15765_2000C334.m_chHoldDig.RTR + 0x14 * i) = 0;
				v4 = v2;
				v5 = v2 + 1;
				if ((*v4 & 0x80) != 0)
				{
					*(&SC_TagISO15765_2000C334.m_chHoldDig.IDE + 0x14 * i) = 4;
					v6 = *v5 << 0x18;
					v7 = v5 + 1;
					v8 = v6 + (*v7++ << 0x10);
					v9 = v8 + (*v7++ << 8);
					v10 = *v7 + v9;
					v11 = v7 + 1;
					*(&SC_TagISO15765_2000C334.m_chHoldDig.ExtId + 5 * i) = v10 >> 3;
				}
				else
				{
					*(&SC_TagISO15765_2000C334.m_chHoldDig.IDE + 0x14 * i) = 0;
					v12 = *v5 << 8;
					v13 = v5 + 1;
					v14 = *v13 + v12;
					v11 = v13 + 1;
					*(&SC_TagISO15765_2000C334.m_chHoldDig.StdId + 5 * i) = v14 >> 5;
				}
				for (j = 0; (_BYTE)v3--; ++j)
					SC_TagISO15765_2000C334.m_chHoldDig.Data[4 + i] = *v11++;// SC_TagISO15765_2000C334.m_chHoldDig.Data[4+i] = *v11++
				v0 = v11 + 7;
			}
		}
	}
}


//在定时器中断中 触发 执行
void TImCANLinkSend_sub_802E040()
{
	if ((int)(Keep_Link_200046C0.IdleTime / 0xA) < ++SC_TagISO15765_2000C334.m_nMScount && Keep_Link_200046C0.IdleTime)
	{
		receive_buff_2000BF20[0x104] = SC_TagISO15765_2000C334.m_PakMode;
		SC_TagISO15765_2000C334.m_nMScount = 0;
		CANRecv_sub_8031D7C(&SC_TagISO15765_2000C334.m_RXM, 0);
		SetCanFrame_sub_80319D8((CanRxMsg *)&SC_TagISO15765_2000C334.m_chHoldDig);
		if (--SC_TagISO15765_2000C334.m_PakMode)
		{
			CANRecv_sub_8031D7C(&SC_TagISO15765_2000C334.m_RXM, 0x64);
			SetCanFrame_sub_80319D8((CanRxMsg *)((char *)&SC_TagISO15765_2000C334.m_TXM.StdId + 1));
		}
		SC_TagISO15765_2000C334.m_PakMode = receive_buff_2000BF20[0x104];
	}
}


void SC_setlinkkeep_sub_802C444()
{
	++Keep_Link_200046C0.timeCount;
	switch (Keep_Link_200046C0.rightState)
	{
	case 1u:
		Keep_Link_200046C0.timeCount = 0;
		if (Keep_Link_200046C0.idleSendLen)
		{
			ComSend_sub_802F3A4(Keep_Link_200046C0.dataBuf[Keep_Link_200046C0.chCount], 0);
			++Keep_Link_200046C0.chCount;
			Keep_Link_200046C0.rightState = 2;
		}
		break;
	case 5u:
		if (Keep_Link_200046C0.IdleTime / SC_TagKWP2000_20004974.m_MsTime < Keep_Link_200046C0.timeCount
			&& Keep_Link_200046C0.IdleTime)
		{
			Keep_Link_200046C0.linkState = 1;
			Keep_Link_200046C0.timeCount = 0;
			Keep_Link_200046C0.chCount = 0;
			ComSend_sub_802F3A4(Keep_Link_200046C0.dataBuf[0], 1);
			++Keep_Link_200046C0.chCount;
			Keep_Link_200046C0.rightState = 2;
		}
		break;
	case 2u:
		if (ComByte_sub_802F6CC(&receive_buff_2000BF20[260], 340))
		{
			if (Keep_Link_200046C0.chCount < (unsigned int)Keep_Link_200046C0.idleSendLen)
			{
				Keep_Link_200046C0.timeCount = 0;
				Keep_Link_200046C0.rightState = 1;
			}
			else
			{
				Keep_Link_200046C0.rightState = 5;
				Keep_Link_200046C0.timeCount = 0;
				Keep_Link_200046C0.chCount = 0;
			}
		}
		else
		{
			Keep_Link_200046C0.IdleTime = 0;
			Keep_Link_200046C0.rightState = 5;
			Keep_Link_200046C0.chCount = 0;
		}
		break;
	}
}


//根据得到的字节内容 返回字节长度
int GetSeries_Ver_sub_8040000(char a1, unsigned __int8 *SeriesBuf, unsigned __int16 SeriesLen)
{
	return 0x0D;
}



//配置系统时钟 具体看IDA
int SysTick_Config_sub_80311BE()
{
	return 1;
}



//获取系统延时时间
uint32_t GetDelayTim_sub_803112E()
{
	//dword_2000C664 + SysTick_Type_E000E010.VAL / 0x78;
	return 1;
}


// 设置GPIo复用 以及时钟
void GPIO_PINAFConfig_RCCSet_sub_802EFE0()
{
	RCC_AHB1PeriphClockCmd_sub_8032BAE(2, 1);
	RCC_APB1PeriphClockCmd_sub_8032C08(0x40000, 1);
	GPIO_PinAFConfig_sub_8031304(GPIOB_200048D4, 0xAu, 7u);
	GPIO_PinAFConfig_sub_8031304(GPIOB_200048E8, 0xBu, 7u);
	RCC_AHB1PeriphClockCmd_sub_8032BAE(4, 1);
	RCC_APB1PeriphClockCmd_sub_8032C08(2, 1);
}

//系统滴答延时 延时多少秒不知道
int AboutSysTicksub_8030788(char a1, unsigned int a2)
{

	return 1;
}


// 选择IO 引脚 并延时等待IO引脚为低电平
int Delay_WaitIoSetLow_sub_802E440(unsigned int *DelayAllTime, unsigned __int16 DelayCnt)
{
	unsigned int v4; // r6

	v4 = 0;
	IOCTRLSelect_sub_8030606(0, 2u);
	while (v4 < 0xFF)
	{
		++v4;
		AboutSysTicksub_803120C(DelayCnt);
		if (!IOCTRLGet_sub_80306E2())
		{
			++v4;
			AboutSysTicksub_803120C(DelayCnt);
			if (!IOCTRLGet_sub_80306E2())           // 判断是否是低电平 低电平进入if 高电平判断if失败
			{
				*DelayAllTime = DelayCnt * v4;
				return 1;
			}
		}
	}
	*DelayAllTime = DelayCnt * v4;
	return 0;
}



//系统滴答延时的程序 可能是
void AboutSysTicksub_803120C(unsigned int a1)
{
	SetSysTickLOAD_sub_8031144(a1);
	Delay_sub_8031194();
}


// 一直在等待IO引脚设置为高电平 高电平后退出while while 最多循环255次
int Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(unsigned int *DelayTime, unsigned __int16 OnceTimes)
{
	unsigned int v4; // r6

	v4 = 0;
	IOCTRLSelect_sub_8030606(0, 2u);
	while (v4 < 0xFF)
	{
		++v4;
		Delay_802EF34(OnceTimes);
		if (IOCTRLGet_sub_80306E2())              // 判断是否为高电平 高电平进入if 低电平判断失败
		{
			++v4;
			Delay_802EF34(OnceTimes);
			if (IOCTRLGet_sub_80306E2())
			{
				*DelayTime = OnceTimes * v4;
				return 1;
			}
		}
	}
	*DelayTime = OnceTimes * v4;
	return 0;
}



int Delay_WaitIoSetLow_sub_802E396(unsigned int *a1, unsigned __int16 OnceTimes)
{
	unsigned int v4; // r6

	v4 = 0;
	IOCTRLSelect_sub_8030606(0, 2u);
	while (v4 < 0xFF)
	{
		++v4;
		Delay_802EF34(OnceTimes);
		if (!IOCTRLGet_sub_80306E2())             // 低电平时 进入if 返回1
		{
			++v4;
			Delay_802EF34(OnceTimes);
			if (!IOCTRLGet_sub_80306E2())
			{
				*a1 = OnceTimes * v4;
				return 1;
			}
		}
	}
	*a1 = OnceTimes * v4;
	return 0;
}



// 一直在时间内拉低拉高IO引脚
int LowHighSet_sub_802E4E0(_DWORD *DelayTime)
{
	__int16 v2; // r5
	__int16 v3; // r7
	__int16 v4; // r6
	int Ret; // r0
	unsigned int DelayTimeT; // [sp+0h] [bp-18h] BYREF

	v2 = 0;
	v3 = 0;
	v4 = 0;
	do
	{
		if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTimeT, 0x32u))// 如果一直等不到高电平就返回0 结束这个函数
			return 0;
		if (!Delay_WaitIoSetLow_sub_802E396(&DelayTimeT, 0x32u))
			return 0;
		++v3;
	} while (DelayTimeT < 1750);
	if (DelayTimeT < 4250)
	{
		do
		{
			if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTimeT, 0x32u))
				return 0;
			if (!Delay_WaitIoSetLow_sub_802E396(&DelayTimeT, 0x32u))
				return 0;
			++v4;
		} while (DelayTimeT < 0x6D6);
		if (DelayTimeT < 0xEA6)
		{
			do
			{
				if (!Delay_WaitIoSetHIGH_sub_802E440sub_802E3F0(&DelayTimeT, 0x32u))
					return 0;
				if (!Delay_WaitIoSetLow_sub_802E396(&DelayTimeT, 0x32u))
					return 0;
				++v2;
			} while (DelayTimeT < 0x6D6);
			*DelayTime = (unsigned __int16)(v2 + 0xA * v4 + 0x64 * v3);
			Ret = 1;
		}
		else
		{
			*DelayTime = (unsigned __int8)(v4 + 0xA * v3);
			Ret = 1;
		}
	}
	else
	{
		*DelayTime = 0xA;
		Ret = 1;
	}
	return Ret;
}



int Delay_OpenPort_sub_802DE94(int DelayTime, int a2, char a3)
{
	int v5; // r7
	uint32_t v7; // r8
	uint32_t v8; // r9

	v5 = 0;
	if (a3)
		ComClose_sub_80B1D06_sub_802FA28(1);

	IOCTRLSelect_sub_8030606(0, 2u);
	SetSysTickLOAD_sub_8031144(0x3E8 * DelayTime);
	v7 = GetDelayTim_sub_803112E();
	while (SysTick_Config_sub_80311BE())
	{
		if (IOCTRLGet_sub_80306E2())
		{
			v5 = 0;
			v8 = GetDelayTim_sub_803112E();
			if (v8 < v7 && 0x3E8 * a2 < v7 - v8)
			{
				if (a3)
					ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				return 0;
			}
		}
		else if ((unsigned __int8)++v5 >= 0xAu)
		{
			v5 = 0;
			v7 = GetDelayTim_sub_803112E();
		}
	}
	if (a3)
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	return 1;
}



BOOL sub_802E980(_BYTE *RcvData)
{
	int i; // r7
	unsigned __int8 j; // r6

	for (i = 0; ; i = 0)
	{
		while (IOCTRLGet_sub_80306E2())           // 判断是否高电平
		{
			Delay_sub_802EF46(0x64u);
			if ((unsigned __int16)++i >= 441u)
				return 0;
		}
		Delay_802EF34(1);
		if (!JudgeHighAndLowCnt_sub_802E938(6u))
			break;
	}
	for (j = 0; j < 8u; ++j)
	{
		Delay_802EF34(2);
		*RcvData >>= 1;
		if (JudgeHighAndLowCnt_sub_802E938(6u))   // 如果高电平次数大于低电平次数 那么就 将第7位设为1 
			*RcvData |= 0x80u;
		else
			*RcvData &= 0x7Fu;
	}
	Delay_802EF34(2);
	return JudgeHighAndLowCnt_sub_802E938(6u);
}



// 再20*a1 次数下高电平的次数 大于低电平的次数
BOOL JudgeHighAndLowCnt_sub_802E938(unsigned __int16 a1)
{
	unsigned int v1; // r6
	int v2; // r5

	v1 = 0x10000;
	v2 = 20 * a1;
	do
	{
		if (IOCTRLGet_sub_80306E2())              // 循环内 一直判断高电平 和低电平 如果高电平次数>=低电平次数 返回1 其他返回0
			++v1;
		else
			--v1;
		Delay_sub_802EF46(0x32u);
		--v2;
	} while (v2);
	return v1 >= 0x10000;
}


int CheckIoBusy_sub_802DF38(int a1, int a2, char a3)
{
	uint32_t v6; // r7
	uint32_t v7; // r8

	if (a3)
		ComClose_sub_80B1D06_sub_802FA28(1);

	IOCTRLSelect_sub_8030606(0, 2u);
	SetSysTickLOAD_sub_8031144(0x3E8 * a1);
	v6 = GetDelayTim_sub_803112E();
	while (SysTick_Config_sub_80311BE())
	{
		if (IOCTRLGet_sub_80306E2())
		{
			v7 = GetDelayTim_sub_803112E();
			if (v7 < v6 && 0x3E8 * a2 < v6 - v7)
			{
				if (a3)
					ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
				return 0;
			}
		}
		else
		{
			v6 = GetDelayTim_sub_803112E();
		}
	}
	if (a3)
		ComOpen_sub_80B1AEC_802F7DE(1, &SC_com_portMode_20004964);
	return 1;
}



// ID6001 ID6002 ID6003 6004 6005 ...对应的函数 然后再走分支
// // Funtion: 设置canbus通信引脚
// // Input  : 无
// // Output : 无
// // Return : void
// // Info   :
// 
// 03 60 05 FF 99 00 03 FC 00
int setCanbusNormalDataToken_sub_802DD42(unsigned __int8 *DataPos)
{
	int dataLenth; // r8
	unsigned __int8 ii; // r5
	int checkXOR; // r6
	unsigned __int8 i; // r7
	int Ret; // r0
	unsigned __int8 data[256]; // [sp+0h] [bp-118h] BYREF

	memset(data,0, 0x100u);
	dataLenth = *DataPos;
	data[0] = *DataPos;
	ii = 1;
	checkXOR = *DataPos;
	for (i = 1; dataLenth--; ++i)
	{
		data[ii++] = DataPos[i];
		checkXOR ^= DataPos[i];
	}
	Ret = data[1];
	if (data[1] == 0x60)
	{
		Ret = data[2];
		if (data[2] == 1)
		{
			CanDataPos = 0;
			CANDataPak_2000A430[0] = 0;
			byte_2000C6BC[0] = 0;
			SetCANFilter_sub_802D4D4(DataPos + 3);    // Ex:参数内容00 01 FD 00 9B 00 03 FC 00 1E 01 01 2C
													  //            00 01 C2 00 A4 00 03 FC 00 1E 08 01 2C
		}
		else if (data[2] == 2)
		{
			CanDataPos = 0;
			CANDataPak_2000A430[0] = 0;
			byte_2000C6BC[0] = 0;
			SetCanBaudRate_sub_802D86C(DataPos + 4);  // 03 65 00 03
		}
		else if (data[2] != 4)
		{
			switch (data[2])
			{
			case 5u:
				SetCanCommunicatioIO_sub_802D810(DataPos + 3);// FF 99 00 03 FC 00
				break;
			case 6u:
				SetCanMaskFilterID_sub_802D2AC(DataPos + 3, (*DataPos - 2) / 8);
				break;
			case 7u:
				SetCanDataFrameReceiveMode_sub_802D744(DataPos + 3);
				break;
			}
		}
	}
	else if (data[1] >= 0x60u)
	{
		if (data[1] == 0x62)
		{
			Ret = data[2];
			if (data[2] == 1)
				sub_802DC20(DataPos + 3);
		}
		else if (data[1] < 0x62u)
		{
			Ret = data[2];
			if (data[2] == 1)
			{
				CanDataPos = 0;
				CANDataPak_2000A430[0] = 0;
				byte_2000C6BC[0] = 0;
				Ret = SetCanFrame_sub_802DC44(DataPos + 3);
			}
			else if (data[2] == 3)
			{
				Ret = sub_802D942(DataPos + 3);
			}
		}
	}
	return Ret;
}



// // Funtion: 设置can通信模式：1、单线can，2、双线can。 设置can通信过滤ID
// // Input  : 无
// // Output : 无
// // Return : void
// // Info   :
void SetCANFilter_sub_802D4D4(unsigned __int8 *dataPos)
{
	int v2; // r0 00 01 C2 00 A4 00 03 FC 00 1E 08 01 2C
	unsigned __int8 i; // r5
	unsigned __int8 j; // r5
	unsigned __int8 pMaskArray[24]; // [sp+0h] [bp-18h] BYREF

	*(_DWORD *)pMaskArray = 0xF070301;
	*(_DWORD *)&pMaskArray[4] = 0xFF7F3F1F;
	if (!SC_RelayState_200049DC.CommType || SC_RelayState_200049DC.CommType == 1)
	{
		SC_RelayState_200049DC.CommType = 1;
		CAN_SetPara_2000C2F0.CanPort = 0;           // //双线can
	}
	else
	{
		switch (SC_RelayState_200049DC.CommType)
		{
		case 2u:                                  // //单线can
			SC_RelayState_200049DC.CommType = 2;
			CAN_SetPara_2000C2F0.CanPort = 1;
			break;
		case 0x20u:
			CAN_SetPara_2000C2F0.CanPort = 0;
			break;
		case 0x21u:
			CAN_SetPara_2000C2F0.CanPort = 1;
			break;
		default:
			SC_RelayState_200049DC.CommType = 1;
			CAN_SetPara_2000C2F0.CanPort = 0;
			break;
		}
	}
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);// Ex:09 0A 09 0A 应该就4个字节
	CAN_SetPara_2000C2F0.FilterNum = 0;
	if (!*dataPos || *dataPos == 0xFF)
	{
		v2 = dataPos[1];
		if (dataPos[1])
		{
			if (v2 == 0xFD)                         // //掩码
			{
				CAN_SetPara_2000C2F0.FilterNum = 1;
				SC_TagISO15765_2000C334.m_chState = 1;
				if (*dataPos)
				{
					PHY_CAN_SetPara_20004984.Mode = 2;
					CAN_SetPara_2000C2F0.ECUID[0] = dataPos[7] + (dataPos[5] << 0x10) + (dataPos[4] << 0x18) + (dataPos[6] << 8);
					CAN_SetPara_2000C2F0.Mask = pMaskArray[dataPos[3] - 1] << dataPos[2];
				}
				CAN_SetPara_2000C2F0.Mask = ~CAN_SetPara_2000C2F0.Mask;
				CAN_SetPara_2000C2F0.ECUID[0] &= CAN_SetPara_2000C2F0.Mask;
				CAN_SetPara_2000C2F0.Mask = (unsigned int)CAN_SetPara_2000C2F0.Mask >> 3;
				CAN_SetPara_2000C2F0.ECUID[0] >>= 3;
			}
			else if (v2 != 0xFE && v2 != 0xFF)
			{
				for (i = 0; i < (unsigned int)dataPos[1]; ++i)
				{
					if (*dataPos)
					{
						// 拓展can
						CAN_SetPara_2000C2F0.ECUID[CAN_SetPara_2000C2F0.FilterNum++] = ((dataPos[4 * i + 5]
							+ (dataPos[4 * i + 3] << 0x10)
							+ (dataPos[4 * i + 2] << 0x18)
							+ (dataPos[4 * i + 4] << 8)) >> 3) & 0x1FFFFFFF;
						PHY_CAN_SetPara_20004984.Mode = 2;
					}
					else
					{
						CAN_SetPara_2000C2F0.ECUID[CAN_SetPara_2000C2F0.FilterNum++] = ((dataPos[2 * i + 3]
							+ (dataPos[2 * i + 2] << 8)) >> 5) & 0x7FF;
						PHY_CAN_SetPara_20004984.Mode = 1;  // 标准帧
					}
				}
			}
		}
		if (!SC_TagISO15765_2000C334.m_chState)   // byte_2000C334 在ID6001有被赋值为0
		{
			for (j = 0; j < (unsigned int)CAN_SetPara_2000C2F0.FilterNum; ++j)
				CAN_SetPara_2000C2F0.ECUID[j + 8] = 0x1FFFFFFF;
		}
		PHY_CAN_SetPara_20004984.FilterNum = CAN_SetPara_2000C2F0.FilterNum;
		PHY_CAN_SetPara_20004984.ECUID = CAN_SetPara_2000C2F0.ECUID;
		PHY_CAN_SetPara_20004984.pMask = &CAN_SetPara_2000C2F0.Mask;
		CANOpen_sub_8031530(CAN_SetPara_2000C2F0.CanPort, &PHY_CAN_SetPara_20004984);
	}
}



int CANOpen_sub_8031530(char CANPort, CAN_CONFIGPARA *PHY_CAN_SetPara)
{
	int result; // r0
	unsigned int v4; // r8
	unsigned int v5; // r9
	uint8_t i; // r7
	CAN_InitTypeDef CAN_InitStruct; // [sp+0h] [bp-38h] BYREF
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct; // [sp+Ch] [bp-2Ch] BYREF

	CanPortArr_2000C6AE[4] = CANPort;
	CAN_DeInit_sub_80348F4(CANxArr_20004934[CANPort]);
	CAN_StructInit_sub_8034B64(&CAN_InitStruct);
	CAN_InitStruct.CAN_TTCM = 0;
	CAN_InitStruct.CAN_ABOM = 0;
	CAN_InitStruct.CAN_AWUM = 0;
	CAN_InitStruct.CAN_NART = 0;
	CAN_InitStruct.CAN_RFLM = 0;
	CAN_InitStruct.CAN_TXFP = 0;
	CAN_InitStruct.CAN_Mode = 0;
	CAN_InitStruct.CAN_SJW = CANBadurateArr_8032104[2 * PHY_CAN_SetPara->Badurate];
	CAN_InitStruct.CAN_BS1 = HIWORD(CANBadurateArr_8032104[2 * PHY_CAN_SetPara->Badurate]);
	CAN_InitStruct.CAN_BS2 = CANBadurateArr_8032104[2 * PHY_CAN_SetPara->Badurate + 1];
	CAN_InitStruct.CAN_Prescaler = HIWORD(CANBadurateArr_8032104[2 * PHY_CAN_SetPara->Badurate + 1]);
	if (CAN_Init_sub_803492C(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], &CAN_InitStruct) != 1)
		return 0;
	TIM_TimeBaseInitStruct.TIM_Period = 0x3E8;
	TIM_TimeBaseInitStruct.TIM_Prescaler = (dword_20004A14 >> 1) / 0xF4240 - 1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStruct.TIM_CounterMode = 0;
	TIM_TimeBaseInit_8032ED8(&TIM4_BASE_40000800, &TIM_TimeBaseInitStruct);
	if (PHY_CAN_SetPara->FilterNum)
	{
		v4 = 0;
		v5 = 0xFFFFFFFF;
		for (i = 0; i < (unsigned int)PHY_CAN_SetPara->FilterNum; ++i)
		{
			if ((int)CANxArr_20004934[(char)CanPortArr_2000C6AE[4]] == (int)&CAN1_BASE_40006400)
				CAN_FilterInitStruct_2000C590.CAN_FilterNumber = i;
			else
				CAN_FilterInitStruct_2000C590.CAN_FilterNumber = i + 0xE;
			if (PHY_CAN_SetPara->ECUID)
				v4 = PHY_CAN_SetPara->ECUID[i];
			if (PHY_CAN_SetPara->pMask)
				v5 = PHY_CAN_SetPara->pMask[i];
			CAN_FilterInitStruct_2000C590.CAN_FilterMode = 0;
			CAN_FilterInitStruct_2000C590.CAN_FilterScale = 1;
			if (PHY_CAN_SetPara->Mode == 2)
			{
				CAN_FilterInitStruct_2000C590.CAN_FilterIdHigh = v4 >> 0xD;// CAN Filter bank register
				CAN_FilterInitStruct_2000C590.CAN_FilterIdLow = (8 * v4) | 4;
				CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdHigh = v5 >> 0xD;
				CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdLow = (8 * v5) | 4;
			}
			else
			{
				CAN_FilterInitStruct_2000C590.CAN_FilterIdHigh = 0x20 * v4;
				CAN_FilterInitStruct_2000C590.CAN_FilterIdLow = 0;
				CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdHigh = 0x20 * v5;
				CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdLow = 0;
			}
			CAN_FilterInitStruct_2000C590.CAN_FilterFIFOAssignment = 0;
			CAN_FilterInitStruct_2000C590.CAN_FilterActivation = 1;
			CAN_FilterInit_sub_8034A50(&CAN_FilterInitStruct_2000C590);
		}
		result = 1;
	}
	else
	{
		if ((int)CANxArr_20004934[(char)CanPortArr_2000C6AE[4]] == (int)&CAN1_BASE_40006400)
			CAN_FilterInitStruct_2000C590.CAN_FilterNumber = 0;
		else
			CAN_FilterInitStruct_2000C590.CAN_FilterNumber = 0xE;
		CAN_FilterInitStruct_2000C590.CAN_FilterMode = 0;
		CAN_FilterInitStruct_2000C590.CAN_FilterScale = 1;
		CAN_FilterInitStruct_2000C590.CAN_FilterIdHigh = 0;
		CAN_FilterInitStruct_2000C590.CAN_FilterIdLow = 0;
		*(_DWORD *)&CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdHigh = 0;
		CAN_FilterInitStruct_2000C590.CAN_FilterFIFOAssignment = 0;
		CAN_FilterInitStruct_2000C590.CAN_FilterActivation = 1;
		CAN_FilterInit_sub_8034A50(&CAN_FilterInitStruct_2000C590);
		result = 1;
	}
	return result;
}



// // Funtion: 设置can通信模波特率
// // Input  : 无
// // Output : 无
// // Return : void
// // Info   :
void SetCanBaudRate_sub_802D86C(unsigned __int8 *buff)
{
	_DWORD BadurateArr[14]; // [sp+0h] [bp-38h] BYREF

	memcpy(BadurateArr, CANBaudrateArr_802E688, 0x2Cu);
	if (*buff)
	{
		if (*buff < 0xCu)
		{
			PHY_CAN_SetPara_20004984.Badurate = BadurateArr[*buff - 1];
			CANOpen_sub_8031530(CAN_SetPara_2000C2F0.CanPort, &PHY_CAN_SetPara_20004984);
		}
	}
}



// FF 99 00 03 FC 00
void SetCanCommunicatioIO_sub_802D810(unsigned __int8 *dataPos)
{
	if (SC_RelayState_200049DC.CommType != 0x20 && SC_RelayState_200049DC.CommType != 0x21)
		SC_RelayState_200049DC.CommType = 1;
	if (*dataPos)
	{
		if (*dataPos == 0xFF)
		{
			SC_RelayState_200049DC.CANL = 0xA;
			SC_RelayState_200049DC.CANH = 9;
		}
	}
	else
	{
		SC_RelayState_200049DC.CANL = 6;
		SC_RelayState_200049DC.CANH = 5;
	}
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
}


void sub_802DB42()
{
	unsigned __int8 i; // r5
	unsigned __int8 SendByte[8]; // [sp+0h] [bp-18h] BYREF
	int v2; // [sp+8h] [bp-10h]

	*(_DWORD *)SendByte = 0xB2134084;
	*(_DWORD *)&SendByte[4] = 0x7C03F0;
	v2 = 0;
	Addr200049E5 = 1;
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	SC_com_portMode_20004964.BaudRate = 0x28A0;
	SC_com_portMode_20004964.WordLength = 0;
	SC_com_portMode_20004964.StopBits = 0;
	SC_com_portMode_20004964.Parity = 0;
	ComOpen_sub_80B1AEC_802F7DE(2, &SC_com_portMode_20004964);
	for (i = 0; i < 7u; ++i)
		ComSendByte_sub_802F1E0(SendByte[i]);
	Delay_802EF34(0x64);
	Keep_Link_200046C0.idleSendLen = 7;
	Keep_Link_200046C0.IdleTime = 0xDAC;
	Copysub_802FB50(Keep_Link_200046C0.dataBuf, SendByte, 7);
	TimerConfig_sub_802EDAE(0, 0x14u);
	SC_TagKWP2000_20004974.m_MsTime = 0x14;
	Keep_Link_200046C0.rightState = 5;
	TimerInterruptFuntionLoad_sub_802EF66(0, (int)KWP2000_Time_sub_802DABE);
	TIM_sub_802EEEC(0);
	timer_open_flag_2000C6B7 = 0;
	Keep_Link_200046C0.field_46 = 1;
}


void sub_802DA40()
{
	unsigned __int8 i; // r5
	unsigned __int8 SendByte[8]; // [sp+0h] [bp-18h] BYREF
	int v2; // [sp+8h] [bp-10h]

	*(_DWORD *)SendByte = 0xB2134084;
	*(_DWORD *)&SendByte[4] = 0x7900F0;
	v2 = 0;
	Addr200049E5 = 1;
	CMPHY_Relay_Set_sub_8030B94(&SC_RelayState_200049DC);
	SC_com_portMode_20004964.BaudRate = 0x28A0;
	SC_com_portMode_20004964.WordLength = 0;
	SC_com_portMode_20004964.StopBits = 0;
	SC_com_portMode_20004964.Parity = 0;
	TimerStop_sub_802EF10(0);
	Keep_Link_200046C0.field_46 = 0;
	Delay_802EF34(0x1F4);
	for (i = 0; i < 7u; ++i)
		ComSendByte_sub_802F1E0(SendByte[i]);
	ComClose_sub_80B1D06_sub_802FA28(2);
}





//定时器中断中去执行的函数
void KWP2000_Time_sub_802DABE()
{
	if (Keep_Link_200046C0.IdleTime / SC_TagKWP2000_20004974.m_MsTime < ++Keep_Link_200046C0.timeCount
		&& Keep_Link_200046C0.IdleTime)
	{
		Keep_Link_200046C0.timeCount = 0;
		for (Keep_Link_200046C0.chCount = 0; Keep_Link_200046C0.chCount < 7u; ++Keep_Link_200046C0.chCount)
			ComSendByte_sub_802F1E0(Keep_Link_200046C0.dataBuf[Keep_Link_200046C0.chCount]);
		Keep_Link_200046C0.chCount = 0;
	}
}


void sub_802DC20(unsigned __int8 *a1)
{
	int v1; // r0

	v1 = *a1;
	if (v1)
	{
		if (v1 == 0xFF)
			sub_802DB42();
	}
	else
	{
		sub_802DA40();
	}
}




//设置can的一些参数
BOOL sub_802D942(unsigned __int8 *a1)
{
	unsigned __int8 v1; // r5
	int v2; // r8
	unsigned int j; // r7
	int v4; // r8
	unsigned int i; // r7
	CanRxMsg CANRx; // [sp+0h] [bp-30h] BYREF

	v1 = *a1;
	if ((*a1 & 0x80) != 0)
	{
		CANRx.IDE = 4;
		v4 = 5;
		CANRx.ExtId = (unsigned int)(a1[4] + (a1[1] << 0x18) + (a1[2] << 0x10) + (a1[3] << 8)) >> 3;
		CANRx.RTR = v1 & 0x40;
		CANRx.DLC = v1 & 0x3F;
		for (i = 0; i < CANRx.DLC; ++i)
			CANRx.Data[i] = a1[v4++];
	}
	else
	{
		CANRx.IDE = 0;
		v2 = 3;
		CANRx.StdId = (unsigned int)(a1[2] + (a1[1] << 8)) >> 5;
		CANRx.RTR = v1 & 0x40;
		CANRx.DLC = v1 & 0x3F;
		for (j = 0; j < CANRx.DLC; ++j)
			CANRx.Data[j] = a1[v2++];
	}
	return SetCanFrame_sub_80319D8(&CANRx);
}




BOOL SetCanFrame_sub_802DC44(unsigned __int8 *DataPos)
{
	unsigned __int8 v1; // r5
	int v2; // r8
	unsigned int j; // r7
	int v4; // r8
	unsigned int i; // r7
	CanRxMsg CANRx; // [sp+0h] [bp-30h] BYREF

	v1 = *DataPos;
	if ((*DataPos & 0x80) != 0)
	{
		CANRx.IDE = 4;
		v4 = 5;
		CANRx.ExtId = (unsigned int)(DataPos[4] + (DataPos[1] << 24) + (DataPos[2] << 16) + (DataPos[3] << 8)) >> 3;
		CANRx.RTR = v1 & 0x40;
		CANRx.DLC = v1 & 0x3F;
		for (i = 0; i < CANRx.DLC; ++i)
			CANRx.Data[i] = DataPos[v4++];
	}
	else
	{
		CANRx.IDE = 0;
		v2 = 3;
		CANRx.StdId = (unsigned int)(DataPos[2] + (DataPos[1] << 8)) >> 5;
		CANRx.RTR = v1 & 0x40;
		CANRx.DLC = v1 & 0x3F;
		for (j = 0; j < CANRx.DLC; ++j)
			CANRx.Data[j] = DataPos[v2++];
	}
	return SetCanFrame_sub_80319D8(&CANRx);
}




void SetCanMaskFilterID_sub_802D2AC(unsigned __int8 *DataPos, unsigned __int8 FilterNum)
{
	unsigned __int8 i; // r6
	unsigned __int8 j; // r6
	unsigned __int8 k; // r6

	CAN_SetPara_2000C2F0.FilterNum = FilterNum;
	SC_TagISO15765_2000C334.m_chState = 1;
	PHY_CAN_SetPara_20004984.Mode = 1;
	for (i = 0; i < (unsigned int)CAN_SetPara_2000C2F0.FilterNum; ++i)
	{
		CAN_SetPara_2000C2F0.ECUID[i] = DataPos[8 * i + 3]
			+ (DataPos[8 * i + 1] << 0x10)
			+ (DataPos[8 * i] << 0x18)
			+ (DataPos[8 * i + 2] << 8);
		CAN_SetPara_2000C2F0.ECUID[i + 8] = DataPos[8 * i + 7]
			+ (DataPos[8 * i + 5] << 0x10)
			+ (DataPos[8 * i + 4] << 0x18)
			+ (DataPos[8 * i + 6] << 8);
		if (CAN_SetPara_2000C2F0.ECUID[i] << 0x10)
			PHY_CAN_SetPara_20004984.Mode = 2;
	}
	if (PHY_CAN_SetPara_20004984.Mode == 1)
	{
		for (j = 0; j < (unsigned int)CAN_SetPara_2000C2F0.FilterNum; ++j)
		{
			CAN_SetPara_2000C2F0.ECUID[j + 8] = ~CAN_SetPara_2000C2F0.ECUID[j + 8];
			CAN_SetPara_2000C2F0.ECUID[j] &= CAN_SetPara_2000C2F0.ECUID[j + 8];
			CAN_SetPara_2000C2F0.ECUID[j + 8] >>= 0x15;
			CAN_SetPara_2000C2F0.ECUID[j] >>= 0x15;
		}
	}
	else
	{
		for (k = 0; k < (unsigned int)CAN_SetPara_2000C2F0.FilterNum; ++k)
		{
			CAN_SetPara_2000C2F0.ECUID[k + 8] = ~CAN_SetPara_2000C2F0.ECUID[k + 8];
			CAN_SetPara_2000C2F0.ECUID[k] &= CAN_SetPara_2000C2F0.ECUID[k + 8];
			CAN_SetPara_2000C2F0.ECUID[k + 8] >>= 3;
			CAN_SetPara_2000C2F0.ECUID[k] >>= 3;
		}
	}
	PHY_CAN_SetPara_20004984.FilterNum = CAN_SetPara_2000C2F0.FilterNum;
	PHY_CAN_SetPara_20004984.ECUID = CAN_SetPara_2000C2F0.ECUID;
	PHY_CAN_SetPara_20004984.pMask = &CAN_SetPara_2000C2F0.Mask;
	CANOpen_sub_8031530(CAN_SetPara_2000C2F0.CanPort, &PHY_CAN_SetPara_20004984);
}



void SetCanDataFrameReceiveMode_sub_802D744(unsigned __int8 *DataPos)
{
	unsigned int CANID; // r5
	unsigned int FilterID; // r6

	if (!SC_RelayState_200049DC.CommType || SC_RelayState_200049DC.CommType == 1)
	{
		SC_RelayState_200049DC.CommType = 1;
		CAN_SetPara_2000C2F0.CanPort = 0;
	}
	else
	{
		switch (SC_RelayState_200049DC.CommType)
		{
		case 2u:
			SC_RelayState_200049DC.CommType = 2;
			CAN_SetPara_2000C2F0.CanPort = 1;
			break;
		case 0x20u:
			CAN_SetPara_2000C2F0.CanPort = 0;
			break;
		case 0x21u:
			CAN_SetPara_2000C2F0.CanPort = 1;
			break;
		default:
			SC_RelayState_200049DC.CommType = 1;
			CAN_SetPara_2000C2F0.CanPort = 0;
			break;
		}
	}
	CANID = DataPos[3] + (DataPos[1] << 0x10) + (*DataPos << 0x18) + (DataPos[2] << 8);
	FilterID = DataPos[7] + (DataPos[5] << 0x10) + (DataPos[4] << 0x18) + (DataPos[6] << 8);
	Can_sub_803289A(CAN_SetPara_2000C2F0.CanPort);
	SetCan_sub_80327A2(CAN_SetPara_2000C2F0.CanPort, CANID, FilterID, 1);
}



void Can_sub_803289A(char canport)
{
	uint8_t i; // r5

	CAN_OperatingModeRequest_sub_8034ED0(CANxArr_20004934[canport], 0);
	for (i = 0; i < (unsigned int)CanPortArr_2000C6AE[5]; ++i)
	{
		if ((int)CANxArr_20004934[canport] == (int)&CAN1_BASE_40006400)// CAN1_BASE    0x40006400
			CAN_FilterInitStruct_2000C590.CAN_FilterNumber = i;
		else
			CAN_FilterInitStruct_2000C590.CAN_FilterNumber = i + 0xE;
		CAN_FilterInitStruct_2000C590.CAN_FilterActivation = 0;
		CAN_FilterInit_sub_8034A50(&CAN_FilterInitStruct_2000C590);
	}
	CanPortArr_2000C6AE[5] = 0;
	CAN_OperatingModeRequest_sub_8034ED0(CANxArr_20004934[canport], 1);
}



int SetCan_sub_80327A2(char CANPort, unsigned int CANID, unsigned int FilterID, char CANMode)
{
	if (!CANID)
		return 1;
	CAN_OperatingModeRequest_sub_8034ED0(CANxArr_20004934[CANPort], 0);
	if ((int)CANxArr_20004934[CANPort] == (int)&CAN1_BASE_40006400)
		CAN_FilterInitStruct_2000C590.CAN_FilterNumber = CanPortArr_2000C6AE[5];
	else
		CAN_FilterInitStruct_2000C590.CAN_FilterNumber = CanPortArr_2000C6AE[5] + 0xE;
	CAN_FilterInitStruct_2000C590.CAN_FilterMode = 0;
	CAN_FilterInitStruct_2000C590.CAN_FilterScale = 1;
	if (CANMode == 2)
	{
		CAN_FilterInitStruct_2000C590.CAN_FilterIdHigh = CANID >> 0xD;
		CAN_FilterInitStruct_2000C590.CAN_FilterIdLow = (8 * CANID) | 4;
		CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdHigh = FilterID >> 0xD;
		CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdLow = (8 * FilterID) | 4;
	}
	else
	{
		CAN_FilterInitStruct_2000C590.CAN_FilterIdHigh = 0x20 * CANID;
		CAN_FilterInitStruct_2000C590.CAN_FilterIdLow = 0;
		CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdHigh = 0x20 * FilterID;
		CAN_FilterInitStruct_2000C590.CAN_FilterMaskIdLow = 0;
	}
	CAN_FilterInitStruct_2000C590.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStruct_2000C590.CAN_FilterActivation = 1;
	CAN_FilterInit_sub_8034A50(&CAN_FilterInitStruct_2000C590);
	++CanPortArr_2000C6AE[5];
	CAN_OperatingModeRequest_sub_8034ED0(CANxArr_20004934[CANPort], 1);
	return 1;
}





int sub_802D03C(_BYTE *a1)
{
	char v2; // r7
	int v3; // r8
	unsigned int v4; // r10
	__int16 DelayCnt; // r8
	unsigned int v6; // r10
	unsigned __int8 i; // r6
	unsigned int v8; // r10
	unsigned __int8 j; // r6
	int v11; // r9
	unsigned __int8 k; // r6
	unsigned __int8 l; // r6
	unsigned __int8 v14; // r9
	CanRxMsg RcvPack; // [sp+0h] [bp-38h] BYREF

	v2 = 0;
	v3 = SC_TagKWP2000_20004974.m_Maxwaittime;
	if (Keep_Link_200046C0.IdleTime)
		set_time0Stop_sub_802BB48();
	*a1 = 0x55;
	a1[1] = 0xAA;
	v4 = 1;
	if (v3 == 0x5DC)
		DelayCnt = 0x5DC;
	else
		DelayCnt = 0x1F4;
	if (!CanDataPos)
	{
		do
		{
			if (!CANRecv_sub_8031D7C(&RcvPack, DelayCnt))
				break;
			DelayCnt = 0x3C;
			++CANDataPak_2000A430[0];
			if (RcvPack.IDE == 4)
			{
				CANDataPak_2000A430[v4] = RcvPack.DLC + 5;
				v6 = v4 + 1;
				CANDataPak_2000A430[v6++] = RcvPack.DLC | 0x80;
				RcvPack.ExtId *= 8;
				CANDataPak_2000A430[v6] = HIBYTE(RcvPack.ExtId);
				CANDataPak_2000A430[++v6] = BYTE2(RcvPack.ExtId);
				CANDataPak_2000A430[++v6] = BYTE1(RcvPack.ExtId);
				CANDataPak_2000A430[++v6] = RcvPack.ExtId;
				v4 = v6 + 1;
				for (i = 0; i < (unsigned int)RcvPack.DLC; ++i)
					CANDataPak_2000A430[v4++] = RcvPack.Data[i];
			}
			else
			{
				CANDataPak_2000A430[v4] = RcvPack.DLC + 3;
				v8 = v4 + 1;
				CANDataPak_2000A430[v8++] = RcvPack.DLC;
				RcvPack.StdId *= 0x20;
				CANDataPak_2000A430[v8] = BYTE1(RcvPack.StdId);
				CANDataPak_2000A430[++v8] = RcvPack.StdId;
				v4 = v8 + 1;
				for (j = 0; j < (unsigned int)RcvPack.DLC; ++j)
					CANDataPak_2000A430[v4++] = RcvPack.Data[j];
			}
		} while (v4 < 0x3F3);
		if (!CANDataPak_2000A430[0])
			return 0;
		CanDataPos = 1;
	}
	a1[2] = CANDataPak_2000A430[CanDataPos++];
	v11 = 3;
	for (k = 0; k < (unsigned int)(unsigned __int8)a1[2]; ++k)
		a1[v11++] = CANDataPak_2000A430[CanDataPos++];
	for (l = 0; (unsigned __int8)a1[2] >= (unsigned int)l; ++l)
		v2 ^= a1[l + 2];
	a1[v11] = v2;
	v14 = v11 + 1;
	if (++byte_2000C6BC[0] == CANDataPak_2000A430[0])
	{
		CanDataPos = 0;
		CANDataPak_2000A430[0] = 0;
		byte_2000C6BC[0] = 0;
	}
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return v14;
}



int CalculateTimeOut_sub_802CC3E(unsigned int a1, unsigned int a2)
{
	int result; // r0
	int v4; // r0

	if (!a2)
		return 250;
	if (!(a1 / a2))
		return 10;
	if (a1 / a2 >= 0x19)
		return 250;
	v4 = a1 / a2;
	if (a1 == a2 * (a1 / a2))
		result = 10 * v4;
	else
		result = 10 * v4 + 5;
	return result;
}




// 
int PWM_Receive_sub_8032208(unsigned __int8 *Ans, unsigned __int8 a2, unsigned int *firstms, unsigned int a4, char a5, int a6, ...)
{
	return 1;
}


int VPW_Send_sub_8051862(unsigned __int8 *a1, unsigned __int8 FrameSize)
{
	return 1;
}



int VPW_Receive_sub_8051896(unsigned __int8 *a1, int a2, int *firstms, int a4)
{
	return 1;
}

void VPW_Init_sub_8051858()
{
	return;
}



int sub_80243CE(int Argc, unsigned __int8 *ArgvData, unsigned __int8 *Ans)
{
	char v5; // r7
	char v6; // r8
	unsigned __int8 v7; // r9
	unsigned __int8 v8; // r10
	unsigned __int8 v9; // r11
	int result; // r0
	unsigned __int8 i; // r6
	unsigned __int8 v12; // [sp+0h] [bp-30h] BYREF
	unsigned __int8 Rcvbyte; // [sp+1h] [bp-2Fh] BYREF
	char v14; // [sp+2h] [bp-2Eh]
	unsigned __int8 v15; // [sp+3h] [bp-2Dh]

	Rcvbyte = 0;
	v12 = 0;
	v15 = 0;
	v14 = 0;
	v5 = 0;
	v6 = 0;
	IOCTRLInit_sub_802C570();
	v7 = *ArgvData;
	if (*ArgvData)
	{
		IOCTRLSelect_sub_8030606(0x13u, 1u);
	}
	if (v7 == 1)
	{
		IOCTRLSet_sub_8030658(1, 0x7A120);
		IOCTRLSet_sub_8030658(0, 0xC3500);
		IOCTRLSet_sub_8030658(1, 0x3F7A0);
	}
	else if (v7 == 2)
	{
		IOCTRLSet_sub_8030658(0, 0x30D40);
		IOCTRLSet_sub_8030658(1, 0xC3500);
		IOCTRLSet_sub_8030658(0, 0x186A0);
	}
	v8 = ArgvData[1];
	v9 = ArgvData[2];
	v15 = ArgvData[3];
	if (v15 >= 2u)
	{
		if (ArgvData[4] == 0xFF)
			v14 = 1;
		for (i = 0; i < 0x3Cu; ++i)
		{
			Delay_802EF34(v8);
			ComSendByte_sub_802F1E0(ArgvData[4]);
			if (ComByte_sub_802F6CC(&Rcvbyte, v9))
				v5 = 1;
			Delay_802EF34(v8);
			ComSendByte_sub_802F1E0(ArgvData[5]);
			if (ComByte_sub_802F6CC(&v12, v9))
				v6 = 1;
			if (v14 == 1)
			{
				if (Rcvbyte == 0xFF && v5 == 1)
					goto LABEL_20;
			}
			else if (v12 == 0xFF && v6 == 1)
			{
			LABEL_20:
				PutDataToAns_sub_802BCBC(szFOK_20004A04, Ans, 4);
				return 2;
			}
			v5 = 0;
			v6 = 0;
			Rcvbyte = 0;
			v12 = 0;
		}
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
		result = 2;
	}
	else
	{
		PutDataToAns_sub_802BCBC(szFBREAK_20004A0C, Ans, 4);
		result = 2;
	}
	return result;
}




// CmdHeaderBuf canID 08 E0
// HeaderLen ID的长度 2
// CmdDataBuf 命令的长度 02 3E 在这个函数里面被赋值的
BOOL CanSendMsg_sub_802B874(unsigned __int8 *CmdHeaderBuf, char HeaderLen, _BYTE *CmdDataBuf)
{
	unsigned __int8 v3; // r7
	int v4; // r11
	unsigned int j; // r10
	int v6; // r11
	unsigned int i; // r10
	bool v8; // r8
	CanRxMsg CANTxSt; // [sp+0h] [bp-38h] BYREF

	v3 = *CmdHeaderBuf;
	if ((*CmdHeaderBuf & 0x80) != 0)            // 拓展can
	{
		CANTxSt.IDE = 4;
		v6 = 5;
		CANTxSt.ExtId = (unsigned int)(CmdHeaderBuf[4]
			+ (CmdHeaderBuf[1] << 0x18)
			+ (CmdHeaderBuf[2] << 0x10)
			+ (CmdHeaderBuf[3] << 8)) >> 3;
		CANTxSt.RTR = v3 & 0x40;
		CANTxSt.DLC = v3 & 0x3F;
		for (i = 0; i < CANTxSt.DLC; ++i)
			CANTxSt.Data[i] = CmdHeaderBuf[v6++];
	}
	else                                          // 标准can
	{
		CANTxSt.IDE = 0;
		v4 = 3;
		CANTxSt.StdId = (unsigned int)(CmdHeaderBuf[2] + (CmdHeaderBuf[1] << 8)) >> 5;
		CANTxSt.RTR = v3 & 0x40;
		CANTxSt.DLC = v3 & 0x3F;
		for (j = 0; j < CANTxSt.DLC; ++j)
			CANTxSt.Data[j] = CmdHeaderBuf[v4++];
	}
	if (HeaderLen == 3)
	{
		*CmdDataBuf = CANTxSt.Data[1];
		CmdDataBuf[1] = CANTxSt.Data[2];
		CmdDataBuf[2] = CANTxSt.Data[3];
	}
	else
	{
		*CmdDataBuf = CANTxSt.Data[0];
		CmdDataBuf[1] = CANTxSt.Data[1];
		CmdDataBuf[2] = CANTxSt.Data[2];
	}
	if (CANRcv_TIM_Open_Flag_2000C6B8 == 1)
		TimerStop_sub_802EF10(1);
	v8 = SetCanFrame_sub_80319D8(&CANTxSt);
	if (CANRcv_TIM_Open_Flag_2000C6B8 == 1)
		TIM_sub_802EEEC(1);
	return v8;
}



// //函数名称:ReadOneFrameFromCANBuf_Ext
// //函数的参数:*ch接受的数据
// //           IDNum接受的ID数
// //           specialdata 特殊数字//包括0x30,0x7f,0x78
// //           bretMode模式字:
// //             1.表示的是:ch里面的格式是：0x55,0xaa,len,0x08,0xid1,0xid2,,,,,
// //               这里有校验位。对于没有校验位的处理，要在程序中进行修改。
// //             2.表示的是:ch里面的格式是：data(除去数据去里面的0x21,0x22,.0x2f等的值)
// //             3.表示的是:ch里面的格式是：0x08,0xid1,0xid2,data0,data1,,,,,,,.
// //           timeout:接受超时。
// //函数的返回值：0表示接受失败 ;
// //              非0表示的是返回的是数据区的长度.
unsigned int ReadOneFrameFromCANBuf_Ext_sub_802B550(unsigned __int8 *RcvData, char IDNum, unsigned __int8 *specialdata, unsigned __int8 bretMode, __int16 timeout)
{
	unsigned __int8 v9; // r5
	unsigned int v11; // r4
	unsigned int i; // r6
	unsigned int j; // r6
	CanRxMsg CANRx1; // [sp-Ch] [bp-6Ch] BYREF
	unsigned __int8 v15[32]; // [sp+8h] [bp-58h] BYREF
	CanRxMsg CANRx; // [sp+28h] [bp-38h] BYREF

	memcpy(v15, &dword_802C424, 0x20u);
	v9 = 0;
	memset(&CANRx, 0, 20u);
	if (!CANRecv_sub_8031D7C(&CANRx, timeout))
		return 0;
	memcpy(&CANRx1, &CANRx, 0x14u);
	v11 = CANUnPacket_sub_802B30C(RcvData, CANRx);//这里CANRx的值
	switch (IDNum)
	{
	case 1:
		*specialdata = RcvData[3];
		specialdata[1] = RcvData[4];
		specialdata[2] = RcvData[6];
		specialdata[3] = RcvData[7];
		break;
	case 3:
		*specialdata = RcvData[4];
		specialdata[1] = RcvData[5];
		specialdata[2] = RcvData[7];
		specialdata[3] = RcvData[6];
		break;
	case 4:
		*specialdata = RcvData[5];
		specialdata[1] = RcvData[6];
		specialdata[2] = RcvData[8];
		specialdata[3] = RcvData[7];
		break;
	default:
		*specialdata = RcvData[3];
		specialdata[1] = RcvData[4];
		specialdata[2] = RcvData[6];
		specialdata[3] = RcvData[5];
		break;
	}
	if (bretMode == 1)
	{
		Copysub_802FB50(&v15[3], RcvData, v11);
		v15[2] = v11;
		Copysub_802FB50(RcvData, v15, v11 + 4);
		for (i = 0; i < v11; ++i)
			v9 ^= RcvData[i + 3];
		RcvData[v11 + 3] = v9;
		v11 += 3;
	}
	else if (bretMode)
	{
		if (bretMode == 3)
		{
			for (j = 0; j < v11; ++j)
				v9 ^= RcvData[j];
			RcvData[v11] = v9;
			Copysub_802FB50(v15, RcvData, ++v11);
		}
		else if (bretMode < 3u)
		{
			if (IDNum == 3)
			{
				v11 -= 4;
				Copysub_802FB50(v15, RcvData + 4, v11);
				Copysub_802FB50(RcvData, v15, v11);
			}
			else
			{
				if (IDNum == 4)
				{
					v11 -= 5;
					Copysub_802FB50(v15, RcvData + 5, v11);
				}
				else
				{
					v11 -= 3;
					Copysub_802FB50(v15, RcvData + 3, v11);
				}
				Copysub_802FB50(RcvData, v15, v11);
			}
		}
	}
	return v11;
}



// sub_802B30C
int CANUnPacket_sub_802B30C(unsigned __int8 *Buff, CanRxMsg RxMsg)
{
	__int16 v3; // r2
	int v4; // r3
	char length; // r0
	unsigned int v6; // r2
	unsigned __int8 *buffT; // r1
	unsigned int i; // r3

	if (RxMsg.IDE)
	{
		v6 = 8 * RxMsg.ExtId;
		*Buff = RxMsg.DLC | (RxMsg.RTR << 6) | 0x80;
		Buff[1] = BYTE3(v6);                       // BYTE3
		Buff[2] = BYTE2(v6);
		Buff[3] = BYTE1(v6);
		Buff[4] = v6;
		v4 = 5;
		length = 5;
	}
	else
	{
		v3 = 0x20 * LOWORD(RxMsg.StdId);
		*Buff = RxMsg.DLC & 0xF | (RxMsg.RTR << 6);
		Buff[1] = HIBYTE(v3);
		Buff[2] = v3;
		v4 = 3;
		length = 3;
	}
	buffT = &Buff[v4];
	for (i = 0; i < RxMsg.DLC; ++i)
		buffT[i] = RxMsg.Data[i];
	return (unsigned __int8)(RxMsg.DLC + length);
}




// //recmode = 0 : normal --- 80, 8x, 0x
// //          1 : C0
// //          2 : 00 xx(>80)
int ReceiveOneKwpFrameFromECUHasMode_sub_802C940(char recmode, unsigned __int8 *RecvBuf, unsigned int *Size, __int16 OverTime)
{
	int dataLen; // r9
	int ret; // r0
	int rcvlen; // r10
	int datalen; // r10
	int v13; // r10
	unsigned __int8 rcvbyte; // [sp+0h] [bp-28h] BYREF

	*Size = 0;
	dataLen = 10;
	do
	{
		if (!ComByte_sub_802F6CC(&rcvbyte, OverTime))
			return 0;
		if (recmode == 1)
		{
			if (rcvbyte == 0xC0)
				break;
		}
		else if (recmode == 2)
		{
			if (!rcvbyte)
				break;
		}
		else if (rcvbyte)
		{
			break;
		}
		--dataLen;
	} while (dataLen);
	if (!dataLen)
		return 0;
	*RecvBuf++ = rcvbyte;
	++*Size;
	if (recmode == 1)
	{
		if (rcvbyte != 0xC0)
			goto LABEL_44;
		rcvlen = 3;
		while (ComByte_sub_802F6CC(&rcvbyte, 300))
		{
			*RecvBuf++ = rcvbyte;
			++*Size;
			if (!--rcvlen)
			{
				dataLen = rcvbyte + 1;
				goto LABEL_44;
			}
		}
		ret = 0;
	}
	else if (recmode == 2)
	{
		if (rcvbyte)
			goto LABEL_44;
		datalen = 10;
		while (1)
		{
			if (!ComByte_sub_802F6CC(&rcvbyte, 300))
				return 0;
			if (rcvbyte)
				break;
			if (!--datalen)
				goto LABEL_31;
		}
		*RecvBuf++ = rcvbyte;
		++*Size;
	LABEL_31:
		if (datalen)
		{
			dataLen = rcvbyte + 1;
			goto LABEL_44;
		}
		ret = 0;
	}
	else if (rcvbyte == 0x80)
	{
		v13 = 3;
		while (ComByte_sub_802F6CC(&rcvbyte, 300))
		{
			*RecvBuf++ = rcvbyte;
			++*Size;
			if (!--v13)
			{
				dataLen = rcvbyte + 1;
				goto LABEL_44;
			}
		}
		ret = 0;
	}
	else
	{
		if (rcvbyte < 0x81u)
			dataLen = (rcvbyte & 0x3F) + 1;
		else
			dataLen = (rcvbyte & 0x3F) + 3;
	LABEL_44:
		while (dataLen--)
		{
			if (!ComByte_sub_802F6CC(&rcvbyte, 300))
				return 0;
			*RecvBuf++ = rcvbyte;
			++*Size;
		}
		ret = 1;
	}
	return ret;
}


int GetKwpFrameBusyFlag_sub_802CAF8(unsigned __int8 *a1, unsigned __int8 *a2)
{
	int v3; // r0

	v3 = *a1;
	if (v3)
	{
		if (v3 == 0x80)
		{
			*a2 = a1[4];
			a2[1] = a1[6];
		}
		else if (*a1 < 0x81u)
		{
			*a2 = a1[1];
			a2[1] = a1[3];
		}
		else
		{
			*a2 = a1[3];
			a2[1] = a1[5];
		}
	}
	else
	{
		*a2 = a1[2];
		a2[1] = a1[4];
	}
	return 1;
}




BOOL SetCanRx_sub_802D8C0(unsigned __int8 *a1)
{
	unsigned __int8 v1; // r5
	int v2; // r7
	unsigned int i; // r6
	CanRxMsg CANRx; // [sp+0h] [bp-28h] BYREF

	v1 = *a1;
	CANRx.IDE = 4;
	CANRx.ExtId = a1[4] + (a1[1] << 24) + (a1[2] << 16) + (a1[3] << 8);
	v2 = 5;
	CANRx.RTR = v1 & 0x40;
	CANRx.DLC = v1 & 0x3F;
	for (i = 0; i < CANRx.DLC; ++i)
		CANRx.Data[i] = a1[v2++];
	return SetCanFrame_sub_80319D8(&CANRx);
}


int sub_802B6E8(unsigned __int8 *a1, int Len, unsigned __int8 *Ans, int DelayCnt)
{
	__int16 v6; // r6
	unsigned __int8 *v8; // r9
	unsigned __int8 i; // r10
	unsigned __int8 v10; // r11
	int v11; // r7
	CanRxMsg RcvSt; // [sp+0h] [bp-40h] BYREF
	int v13; // [sp+14h] [bp-2Ch]

	v13 = Len;
	v6 = *((_WORD *)Ans + 1);
	if ((unsigned __int8)Len < 0xDu)
		return 0;
	while (v6)
	{
		if (!CANRecv_sub_8031D7C(&RcvSt, DelayCnt))
			return 0;
		*a1 = RcvSt.DLC | (RcvSt.RTR << 6) | 0x80;
		a1[1] = HIBYTE(RcvSt.ExtId);                // 改成BYTE3
		a1[2] = BYTE2(RcvSt.ExtId);
		a1[3] = BYTE1(RcvSt.ExtId);
		a1[4] = RcvSt.ExtId;
		v8 = a1 + 5;
		for (i = 0; i < (unsigned int)RcvSt.DLC; ++i)
			*v8++ = RcvSt.Data[i];
		v10 = RcvSt.DLC + 5;
		if (!Ans[0x10])
			return v10;
		if (*Ans)
		{
			if (*Ans == 1)
			{
				if (a1[4] + (a1[2] << 8) + (a1[3] << 0x10) == *((_DWORD *)Ans + 1))
					return v10;
			}
			else
			{
				if (*Ans != 2)
					return 0;
				if (a1[0xC] + (a1[0xB] << 8) + (a1[0xA] << 0x10) == *((_DWORD *)Ans + 1))
					return v10;
			}
		}
		else
		{
			v11 = a1[4] + (a1[2] << 8) + (a1[3] << 0x10);
			if (v11 == *((_DWORD *)Ans + 2) || v11 == *((_DWORD *)Ans + 3))
			{
				*Ans = 1;
				return v10;
			}
			if (a1[0xC] + (a1[0xB] << 8) + (a1[0xA] << 0x10) == *((_DWORD *)Ans + 1)
				&& (unsigned __int8)*((_DWORD *)Ans + 2) == a1[4])
			{
				*Ans = 2;
				return v10;
			}
		}
		--v6;
	}
	return 0;
}



void sub_803B704(unsigned __int8 *a1, unsigned __int8 *a2)
{
	int v2; // r3
	unsigned __int8 v3; // r5
	unsigned __int8 v4; // r7

	v2 = ((a1[3] >> 5) + 8 * a1[2]) ^ 0x13 ^ a1[3];
	v3 = (8 * a1[1]) ^ 0x5B ^ a1[2] ^ BYTE1(v2);
	v4 = (8 * *a1) ^ 0x2E ^ a1[1] ^ ((unsigned __int16)((8 * a1[1]) ^ 0x5B ^ a1[2] ^ (v2 >> 8)) >> 8);
	*a2 = *a1 ^ (8 * a1[3]) ^ 0x72 ^ ((unsigned __int16)((8 * *a1) ^ 0x2E ^ a1[1] ^ (((8 * a1[1]) ^ 0x5B ^ a1[2] ^ (v2 >> 8)) >> 8)) >> 8);
	a2[1] = v4;
	a2[2] = v3;
	a2[3] = v2;
}



void sub_803B790(unsigned __int8 *a1, unsigned __int8 *a2)
{
	int v2; // r3
	unsigned __int8 v3; // r5
	unsigned __int8 v4; // r7

	v2 = ((a1[3] >> 5) + 8 * a1[2]) ^ 0xE3 ^ a1[3];
	v3 = (8 * a1[1]) ^ 0xCB ^ a1[2] ^ BYTE1(v2);
	v4 = (8 * *a1) ^ a1[1] ^ ((unsigned __int16)((8 * a1[1]) ^ 0xCB ^ a1[2] ^ (v2 >> 8)) >> 8);
	*a2 = *a1 ^ (8 * a1[3]) ^ 0x82 ^ ((unsigned __int16)((8 * *a1) ^ a1[1] ^ (((8 * a1[1]) ^ 0xCB ^ a1[2] ^ (v2 >> 8)) >> 8)) >> 8);
	a2[1] = v4;
	a2[2] = v3;
	a2[3] = v2;
}



void sub_803B878(unsigned __int8 *a1, unsigned __int8 *a2)
{
	int v2; // r3
	unsigned __int8 v3; // r5
	unsigned __int8 v4; // r7

	v2 = ((a1[3] >> 5) + 8 * a1[2]) ^ a1[3];
	v3 = (8 * a1[1]) ^ a1[2] ^ BYTE1(v2);
	v4 = (8 * *a1) ^ 0x3E ^ a1[1] ^ ((unsigned __int16)((8 * a1[1]) ^ a1[2] ^ (v2 >> 8)) >> 8);
	*a2 = *a1 ^ (8 * a1[3]) ^ 0x7C ^ ((unsigned __int16)((8 * *a1) ^ 0x3E ^ a1[1] ^ (((8 * a1[1]) ^ a1[2] ^ (v2 >> 8)) >> 8)) >> 8);
	a2[1] = v4;
	a2[2] = v3;
	a2[3] = v2;
}


//设置定时器 出发定时器中断
int SetTIM_sub_802F58C(__int16 a1)
{

	return 1;
}



unsigned int sub_802B3A6(unsigned __int8 *CmdHeadBuf, char a2, unsigned __int8 *CmdDataBuf, int a4, __int16 TimeOut, char Mode)
{
	unsigned __int8 CheckOr; // r5
	unsigned __int8 v10; // r9
	unsigned int v12; // r4
	unsigned int i; // r6
	unsigned int j; // r6
	CanRxMsg TRxMsg; // [sp-Ch] [bp-74h] OVERLAPPED BYREF
	_BYTE Buf[3]; // [sp+8h] [bp-60h] BYREF
	char v17; // [sp+Bh] [bp-5Dh] BYREF
	CanRxMsg CANRx; // [sp+28h] [bp-40h] BYREF
	int v19; // [sp+40h] [bp-28h]
	CanRxMsg TTRxMsg; // 0:r1.12,12:^C.8

	v19 = a4;
	memcpy(Buf, byte_802C1CC, 0x20u);
	CheckOr = 0;
	v10 = 0;
	memset(&CANRx, 0,0x14u);
	if ((Mode & 1) != 0)
		v10 = PHY_CAN_SetPara_20004984.Mode;
	if (!sub_8031CA0(&CANRx, TimeOut, v10))
		return 0;
	memcpy(&TRxMsg, &CANRx, 0x14u);
	TTRxMsg.StdId = TRxMsg.StdId;
	*(_QWORD *)&TTRxMsg.ExtId = *(_QWORD *)&TRxMsg.ExtId;
	v12 = CANUnPacket_sub_802B30C(CmdHeadBuf, TTRxMsg);
	switch (a2)
	{
	case 1:
		*CmdDataBuf = CmdHeadBuf[3];
		CmdDataBuf[1] = CmdHeadBuf[4];
		CmdDataBuf[2] = CmdHeadBuf[6];
		CmdDataBuf[3] = CmdHeadBuf[7];
		break;
	case 3:
		*CmdDataBuf = CmdHeadBuf[4];
		CmdDataBuf[1] = CmdHeadBuf[5];
		CmdDataBuf[2] = CmdHeadBuf[7];
		CmdDataBuf[3] = CmdHeadBuf[6];
		break;
	case 4:
		*CmdDataBuf = CmdHeadBuf[5];
		CmdDataBuf[1] = CmdHeadBuf[6];
		CmdDataBuf[2] = CmdHeadBuf[8];
		CmdDataBuf[3] = CmdHeadBuf[7];
		break;
	default:
		*CmdDataBuf = CmdHeadBuf[3];
		CmdDataBuf[1] = CmdHeadBuf[4];
		CmdDataBuf[2] = CmdHeadBuf[6];
		CmdDataBuf[3] = CmdHeadBuf[5];
		break;
	}
	if ((unsigned __int8)v19 == 1)
	{
		Copysub_802FB50(&v17, CmdHeadBuf, v12);
		Buf[2] = v12;
		Copysub_802FB50(CmdHeadBuf, Buf, v12 + 4);
		for (i = 0; i < v12; ++i)
			CheckOr ^= CmdHeadBuf[i + 3];
		CmdHeadBuf[v12 + 3] = CheckOr;
		v12 += 3;
	}
	else if ((_BYTE)v19)
	{
		if ((unsigned __int8)v19 == 3)
		{
			for (j = 0; j < v12; ++j)
				CheckOr ^= CmdHeadBuf[j];
			CmdHeadBuf[v12] = CheckOr;
			Copysub_802FB50(Buf, CmdHeadBuf, ++v12);
		}
		else if ((unsigned __int8)v19 < 3u)
		{
			if (a2 == 3)
			{
				v12 -= 4;
				Copysub_802FB50(Buf, CmdHeadBuf + 4, v12);
				Copysub_802FB50(CmdHeadBuf, Buf, v12);
			}
			else
			{
				if (a2 == 4)
				{
					v12 -= 5;
					Copysub_802FB50(Buf, CmdHeadBuf + 5, v12);
				}
				else
				{
					v12 -= 3;
					Copysub_802FB50(Buf, CmdHeadBuf + 3, v12);
				}
				Copysub_802FB50(CmdHeadBuf, Buf, v12);
			}
		}
	}
	return v12;
}


BOOL sub_8031CA0(CanRxMsg *RcPak, __int16 TimeOut, int a3)
{
	char v6; // r8

	v6 = 0;
	TIM_SetCounter_8032F42(&TIM4_BASE_40000800, 0);
	TIM_ClearFlag_80332DC(&TIM4_BASE_40000800, 1);
	TIM_UpdateDisableConfig_8032F62(&TIM4_BASE_40000800, 1);
	while (1)
	{
		if (!CAN_MessagePending_sub_8034EA4(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0))
			goto LABEL_11;
		CAN_Receive_sub_8034DA2(CANxArr_20004934[(char)CanPortArr_2000C6AE[4]], 0, RcPak);
		if (a3 == 2)
		{
			if (RcPak->IDE == 4)
				goto LABEL_10;
			goto LABEL_11;
		}
		if (a3 != 1)
			break;
		if (!RcPak->IDE)
			goto LABEL_10;
	LABEL_11:
		if (TIM_GetFlagStatus_80332C4(&TIM4_BASE_40000800, 1))
		{
			TIM_ClearFlag_80332DC(&TIM4_BASE_40000800, 1);
			--TimeOut;
		}
		if (!TimeOut)
			return v6 != 0;
	}
	if (a3)
		goto LABEL_11;
LABEL_10:
	v6 = 1;
	TIM_UpdateDisableConfig_8032F62(&TIM4_BASE_40000800, 0);
	return v6 != 0;
}


int sub_802E2F6(unsigned __int8 *receive_buff, _DWORD *RcvLen, __int16 WaitTime)
{
	unsigned int i; // r8
	unsigned int v8; // r10
	unsigned int j; // r8

	*RcvLen = 0;
	if (!ComByte_sub_802F6CC(receive_buff, WaitTime))
		return 0;
	if (*receive_buff != 0xB8)
		return 0;
	for (i = 0; i < 3; ++i)
	{
		if (!ComByte_sub_802F6CC(&receive_buff[i + 1], WaitTime))
			return 0;
	}
	v8 = receive_buff[3] + 1;
	for (j = 0; j < v8; ++j)
	{
		if (!ComByte_sub_802F6CC(&receive_buff[j + 4], WaitTime))
			return 0;
	}
	*RcvLen = v8 + 3;
	return 1;
}




unsigned int sub_803AC10(int a1, unsigned __int8 *a2, unsigned __int8 a3, int a4)
{
	int v6; // r6
	int v7; // r7
	unsigned int v8; // r11
	unsigned int v9; // r8
	int v10; // r9
	unsigned int v11; // r5
	unsigned int v13; // r0
	unsigned int v14; // r5
	unsigned __int8 v15; // [sp+4h] [bp-44h]
	unsigned __int8 v16[20]; // [sp+8h] [bp-40h] BYREF
	int v17; // [sp+1Ch] [bp-2Ch]
	int v18; // [sp+20h] [bp-28h]

	v17 = a1;
	v18 = a4;
	v6 = 0;
	v7 = 0;
	v15 = 1;
	v8 = 0;
	v9 = 0;
	v10 = 0;
	memset(v16, 0,0x10u);
	while (1)
	{
		while (v15 != 1)
		{
			if (v15 == 3)
			{
				Copysub_802FB50(v16, CanEnterFrame_2000C47C.data, 0xD);
				if ((v17 & 0xF) == 1)
					v16[3] = (CmdBuf_2000C554[0x19] + (CmdBuf_2000C554[0x18] << 8) - 0xC000) / 0x20;
				if (!CanSendMsg_sub_802B874(v16, a3, specialdata_2000C670))
					return 0xFFFFFFFD;
				if (CanEnterFrame_2000C47C.data[0x1E])
					v10 = 0;
				v15 = 2;
			}
			else if (v15 < 3u)
			{
				v13 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], a3, specialdata_2000C670, 2u, v18);
				v14 = v13 - 1;
				if (v13 == 1)
					return 0xFFFFFFFF;
				memmove(a2, &CmdBuf_2000C554[0x15], v13 - 1);
				a2 += v14;
				v6 += v14;
				++v7;
				v9 += 7;
				if (a3 == 3)
					--v9;
				if (v9 >= v8)
					return a3 + v8 + 6;
				if (CanEnterFrame_2000C47C.data[0x1E])
				{
					if (++v10 >= (unsigned int)CanEnterFrame_2000C47C.data[0x1E])
						v15 = 3;
				}
			}
		}
		v11 = ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], a3, specialdata_2000C670, 1u, v18);
		if (!v11)
			return 0xFFFFFFFF;
		if ((specialdata_2000C670[0] & 0xF0) != 0x10)
			break;
		memmove(a2, &CmdBuf_2000C554[0x14], v11);
		a2 += v11;
		v6 += v11;
		++v7;
		v8 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8);
		v9 += 6;
		if (a3 == 3)
			--v9;
		v15 = 3;
	}
	if (specialdata_2000C670[1] == 0x7F && specialdata_2000C670[2] == 0x78)
		return 0xFFFFFFFE;
	memmove(a2, &CmdBuf_2000C554[0x14], v11);
	return v11 + v6;
}




int sub_803AA2C(int a1, unsigned __int8 *a2, unsigned __int8 a3)
{
	unsigned int v5; // r6
	unsigned int v6; // r7
	unsigned int v7; // r8
	unsigned int v8; // r9
	int v9; // r10
	unsigned __int8 v10; // r11

	v5 = 0;
	v6 = 0;
	v7 = 0;
	v8 = 0;
	v9 = 0;
	v10 = 1;
	do
	{
		while (1)
		{
			while (1)
			{
				while (v10 == 1)
				{
					memmove(CmdBuf_2000C554, a2, 0xDu);
					if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, a3, specialdata_2000C670))
						return 0xFFFFFFFF;
					if ((specialdata_2000C670[0] & 0xF0) == 0x10)
					{
						v5 = specialdata_2000C670[1] + ((specialdata_2000C670[0] & 0xF) << 8);
						v6 += 6;
						if (a3 == 3)
							--v6;
						v10 = 3;
					}
					else
					{
						v10 = 4;
					}
				}
				if (v10 != 3)
					break;
				if (!ReadOneFrameFromCANBuf_Ext_sub_802B550(&CmdBuf_2000C554[0x14], a3, specialdata_2000C670, 1u, 0x1F4u))
					return 0xFFFFFFFE;
				if ((specialdata_2000C670[0] & 0x30) == 0x30)
				{
					v7 = specialdata_2000C670[1];
					v8 = specialdata_2000C670[3];
					v9 = 0;
					v10 = 2;
				}
			}
			if (v10 >= 3u)
				break;
			memmove(&CmdBuf_2000C554[a3 + 2], &a2[v6 + 3 + a3], 7u);
			if ((CmdBuf_2000C554[a3 + 1] & 0xF0) == 0x10)
				CmdBuf_2000C554[a3 + 1] = 0x21;
			if (v8 && v8 < 0x80)
			{
				Delay_802EF34(v8);
			}
			else if (v8 < 0xF1 || v8 >= 0xFA)
			{
				Delay_sub_802EF46(DelayTime_2000C53C);
			}
			else
			{
				Delay_sub_802EF46(0x64 * (v8 - 0xF0));
			}
			if (!CanSendMsg_sub_802B874(CmdBuf_2000C554, a3, specialdata_2000C670))
				return 0xFFFFFFFF;
			if (++CmdBuf_2000C554[a3 + 1] == 0x30)
				CmdBuf_2000C554[a3 + 1] = 0x20;
			v6 += 7;
			if (a3 == 3)
				--v6;
			if (v6 < v5)
			{
				if (v7)
				{
					if (++v9 >= v7)
						v10 = 3;
				}
			}
			else
			{
				v10 = 4;
			}
		}
	} while (v10 != 4);
	return a3 + v6 + 3;
}




int sub_802E5B4(_DWORD *a1)
{
	__int16 v2; // r5
	__int16 v3; // r6
	__int16 v4; // r7
	int result; // r0
	unsigned int v6[6]; // [sp+0h] [bp-18h] BYREF

	v2 = 0;
	v3 = 0;
	v4 = 0;
	do
	{
		if (!sub_802E490(v6, 0x190u))
			return 0;
		if (!Delay_WaitIoSetLow_sub_802E440(v6, 0x190u))
			return 0;
		++v3;
	} while (v6[0] < 0xFA0);
	if (v6[0] < 0x5DC0)
	{
		do
		{
			if (!sub_802E490(v6, 0x190u))
				return 0;
			if (!Delay_WaitIoSetLow_sub_802E440(v6, 0x190u))
				return 0;
			++v4;
		} while (v6[0] < 0xFA0);
		if (v6[0] < 0x5DC0)
		{
			do
			{
				if (!sub_802E490(v6, 0x190u))
					return 0;
				if (!Delay_WaitIoSetLow_sub_802E440(v6, 0x190u))
					return 0;
				++v2;
			} while (v6[0] < 0xFA0);
			*a1 = (unsigned __int16)(v4 + 0xA * v3 + 0x64 * v2);
			result = 1;
		}
		else
		{
			*a1 = (unsigned __int8)(v4 + 0xA * v3);
			result = 1;
		}
	}
	else
	{
		*a1 = 0xA;
		result = 1;
	}
	return result;
}



int sub_802E490(_DWORD *a1, unsigned __int16 a2)
{
	unsigned int v4; // r6

	v4 = 0;
	IOCTRLSelect_sub_8030606(0, 2u);
	while (v4 < 0xFF)
	{
		++v4;
		AboutSysTicksub_803120C(a2);
		if (IOCTRLGet_sub_80306E2())
		{
			++v4;
			AboutSysTicksub_803120C(a2);
			if (IOCTRLGet_sub_80306E2())
			{
				*a1 = a2 * v4;
				return 1;
			}
		}
	}
	*a1 = a2 * v4;
	return 0;
}



int sub_802E78E(_DWORD *a1)
{
	__int16 v2; // r5
	__int16 v3; // r6
	__int16 v4; // r7
	int result; // r0
	unsigned int v6[6]; // [sp+0h] [bp-18h] BYREF

	v2 = 0;
	v3 = 0;
	v4 = 0;
	do
	{
		if (!sub_802E490(v6, 0xC8u))
			return 0;
		if (!Delay_WaitIoSetLow_sub_802E440(v6, 0xC8u))
			return 0;
		++v3;
	} while (v6[0] < 0x1F40);
	if (v6[0] < 0x5DC0)
	{
		do
		{
			if (!sub_802E490(v6, 0xC8u))
				return 0;
			if (!Delay_WaitIoSetLow_sub_802E440(v6, 0xC8u))
				return 0;
			++v4;
		} while (v6[0] < 0x1F40);
		if (v6[0] < 0x5DC0)
		{
			do
			{
				if (!sub_802E490(v6, 0xC8u))
					return 0;
				if (!Delay_WaitIoSetLow_sub_802E440(v6, 0xC8u))
					return 0;
				++v2;
			} while (v6[0] < 0x1F40);
			*a1 = (unsigned __int16)(v4 + 0xA * v3 + 0x64 * v2);
			result = 1;
		}
		else
		{
			*a1 = (unsigned __int8)(v4 + 0xA * v3);
			result = 1;
		}
	}
	else
	{
		*a1 = 0xA;
		result = 1;
	}
	return result;
}




int sub_802E864(unsigned int *a1)
{
	__int16 v2; // r5
	__int16 v3; // r7
	__int16 v4; // r6
	int result; // r0
	unsigned int v6[6]; // [sp+0h] [bp-18h] BYREF

	v2 = 0;
	v3 = 0;
	v4 = 0;
	do
	{
		if (!sub_802E490(v6, 0xC8u))
			return 0;
		if (!Delay_WaitIoSetLow_sub_802E396(v6, 0x19u))
			return 0;
		++v3;
	} while (v6[0] < 0x2EE);
	if (v6[0] < 0xBB8)
	{
		do
		{
			if (!sub_802E490(v6, 0xC8u))
				return 0;
			if (!Delay_WaitIoSetLow_sub_802E396(v6, 0x19u))
				return 0;
			++v4;
		} while (v6[0] < 0x2EE);
		if (v6[0] < 0xBB8)
		{
			do
			{
				if (!sub_802E490(v6, 0xC8u))
					return 0;
				if (!Delay_WaitIoSetLow_sub_802E396(v6, 0x19u))
					return 0;
				++v2;
			} while (v6[0] < 0x2EE);
			*a1 = (unsigned __int16)(v4 + 0xA * v3 + 0x64 * v2);
			result = 1;
		}
		else
		{
			*a1 = (unsigned __int8)(v4 + 0xA * v3);
			result = 1;
		}
	}
	else
	{
		*a1 = 0xA;
		result = 1;
	}
	return result;
}



int sub_802EB50(unsigned __int8 *a1, unsigned __int16 a2)
{
	int result; // r0
	int v4; // r8
	unsigned __int8 v5; // r6
	unsigned __int8 v6; // r7
	char v8; // r9
	int v9; // r6
	unsigned __int16 v10; // [sp+0h] [bp-30h] BYREF
	unsigned int v11[11]; // [sp+4h] [bp-2Ch] BYREF

	if (a2 < 0x80u)
		return 0;
	v11[0] = 5;
	v11[1] = 0x14;
	v11[2] = 0x28;
	v4 = 0x61A80;
	IOCTRLSelect_sub_8030606(0, 2u);
	v5 = 0;
	v6 = 0;
	Delay_802EF34(0x4B0);
	while (IOCTRLGet_sub_80306E2())
	{
		Delay_sub_802EF46(0x32u);
		if (!v4--)
			return 0;
	}
	while (1)
	{
		v8 = sub_802EA12(&v10, v11);
		if (v8 != 1)
			break;
		a1[v5] = v10 / 0x100;
		v9 = (unsigned __int8)(v5 + 1);
		a1[v9] = v10;
		v5 = v9 + 1;
		++v6;
	}
	if (v8 == 6 && v6)
		result = v6;
	else
		result = 0;
	return result;
}



int sub_802EA12(unsigned __int16 *a1, unsigned int *a2)
{
	unsigned __int8 v4; // r7
	unsigned int v5; // r8
	unsigned __int8 i; // r6
	unsigned __int8 v9[4]; // [sp+0h] [bp-20h] BYREF

	*(_DWORD *)v9 = 0;
	v4 = 0;
	v5 = 0x3E8 * a2[2] / 0x32;
	while (IOCTRLGet_sub_80306E2())
	{
		Delay_sub_802EF46(0x32u);
		if (!(_WORD)v5--)
			return 6;
	}
	if (JudgeHighAndLowCnt_sub_802E938(*a2))
		return 2;
	while (1)
	{
		do
		{
			if (!JudgeHighAndLowCnt_sub_802E938(*a2))
				return 3;
			if (v4 >= 3u)
				return 3;
			if (++v9[v4] >= 0xAu)
				return 3;
		} while (!JudgeHighAndLowCnt_sub_802E938(*a2));
		for (i = 0; i < a2[1] / *a2 - 2; ++i)
		{
			if (!JudgeHighAndLowCnt_sub_802E938(*a2))
				return 3;
		}
		if (JudgeHighAndLowCnt_sub_802E938(*a2))
			break;
		++v4;
	}
	if (!JudgeHighAndLowCnt_sub_802E938(*a2))
		return 3;
	if (!JudgeHighAndLowCnt_sub_802E938(*a2))
		return 3;
	*a1 = v9[0];
	if (v9[1])
	{
		*a1 = v9[1] + 0xA * v9[0];
	}
	else if (v9[0] == 1)
	{
		*a1 = 0xA;
		return 1;
	}
	if (v9[2])
		*a1 += 0x64 * v9[2];
	return 1;
}



BOOL SetCan_sub_802B9DE(unsigned __int8 *CmdHeaderBuf, char HeaderLen, _BYTE *CmdDataBuf)
{
	unsigned __int8 v3; // r7
	int v4; // r11
	unsigned int j; // r10
	int v6; // r11
	unsigned int i; // r10
	bool v8; // r8
	CanRxMsg CANRx[2]; // [sp+0h] [bp-38h] BYREF

	v3 = *CmdHeaderBuf;
	if ((*CmdHeaderBuf & 0x80) != 0)
	{
		CANRx[0].IDE = 4;
		v6 = 5;
		CANRx[0].ExtId = (unsigned int)(CmdHeaderBuf[4]
			+ (CmdHeaderBuf[1] << 24)
			+ (CmdHeaderBuf[2] << 16)
			+ (CmdHeaderBuf[3] << 8)) >> 3;
		CANRx[0].RTR = v3 & 0x40;
		CANRx[0].DLC = v3 & 0x3F;
		for (i = 0; i < CANRx[0].DLC; ++i)
			CANRx[0].Data[i] = CmdHeaderBuf[v6++];
	}
	else
	{
		CANRx[0].IDE = 0;
		v4 = 3;
		CANRx[0].StdId = (unsigned int)(CmdHeaderBuf[2] + (CmdHeaderBuf[1] << 8)) >> 5;
		CANRx[0].RTR = v3 & 0x40;
		CANRx[0].DLC = v3 & 0x3F;
		for (j = 0; j < CANRx[0].DLC; ++j)
			CANRx[0].Data[j] = CmdHeaderBuf[v4++];
	}
	if (HeaderLen == 3)
	{
		*CmdDataBuf = CANRx[0].Data[1];
		CmdDataBuf[1] = CANRx[0].Data[2];
		CmdDataBuf[2] = CANRx[0].Data[3];
	}
	else
	{
		*CmdDataBuf = CANRx[0].Data[0];
		CmdDataBuf[1] = CANRx[0].Data[1];
		CmdDataBuf[2] = CANRx[0].Data[2];
	}
	if (timer_open_flag_2000C6B7 == 1)
		TimerStop_sub_802EF10(0);
	v8 = SetCanFrame_sub_80319D8(CANRx);
	if (timer_open_flag_2000C6B7 == 1)
		TIM_sub_802EEEC(0);
	return v8;
}



int sub_802E6B4(unsigned int *a14)
{
	__int16 v2; // r5
	__int16 v3; // r7
	__int16 v4; // r6
	int result; // r0
	unsigned int v6[6]; // [sp+0h] [bp-18h] BYREF

	v2 = 0;
	v3 = 0;
	v4 = 0;
	do
	{
		if (!sub_802E490(v6, 0x190u))
			return 0;
		if (!Delay_WaitIoSetLow_sub_802E440(v6, 0x190u))
			return 0;
		++v3;
	} while (v6[0] < 0x4E20);
	if (v6[0] < 0xEA60)
	{
		do
		{
			if (!sub_802E490(v6, 0x190u))
				return 0;
			if (!Delay_WaitIoSetLow_sub_802E440(v6, 0x190u))
				return 0;
			++v4;
		} while (v6[0] < 0x4E20);
		if (v6[0] < 0x9C40)
		{
			do
			{
				if (!sub_802E490(v6, 0x190u))
					return 0;
				if (!Delay_WaitIoSetLow_sub_802E440(v6, 0x190u))
					return 0;
				++v2;
			} while (v6[0] < 0x9C40);
			*a14 = (unsigned __int16)(v4 + 0xA * v3 + 0x64 * v2);
			result = 1;
		}
		else
		{
			*a14 = (unsigned __int8)(v4 + 0xA * v3);
			result = 1;
		}
	}
	else
	{
		*a14 = 0xA;
		result = 1;
	}
	return result;
}



int sub_802EC18(unsigned __int8 *AnsBuf, _DWORD *RecvSize, __int16 OverTime, _BYTE *SpeciData)
{
	int v9; // r9
	int v10; // r8
	unsigned int l; // r10
	int v12; // r8
	unsigned int k; // r10
	int v14; // r8
	unsigned int j; // r10
	int v16; // r8
	unsigned int i; // r10

	*RecvSize = 0;
	if (!ComByte_sub_802F6CC(AnsBuf, OverTime))
		return 0;
	++*RecvSize;
	v9 = *AnsBuf & 0xC0;
	if (v9 == 0x40)
		return 0;
	if ((unsigned __int8)v9 < 0x80u || (*AnsBuf & 0x3F) != 0)
	{
		if ((unsigned __int8)v9 < 0x80u)
		{
			if ((*AnsBuf & 0x3F) != 0)
			{
				v16 = *AnsBuf;
				for (i = 1; v16 + 3 >= i; ++i)
				{
					if (!ComByte_sub_802F6CC(&AnsBuf[i], 3))
						return 0;
					++*RecvSize;
				}
				*SpeciData = AnsBuf[1];
				SpeciData[1] = AnsBuf[3];
			}
			else
			{
				v14 = 0;
				for (j = 1; v14 + 2 >= j; ++j)
				{
					if (!ComByte_sub_802F6CC(&AnsBuf[j], OverTime))
						return 0;
					++*RecvSize;
					if (j == 1)
						v14 = AnsBuf[1];
				}
				*SpeciData = AnsBuf[2];
				SpeciData[1] = AnsBuf[4];
			}
		}
		else
		{
			v12 = *AnsBuf & 0x3F;
			for (k = 1; v12 + 3 >= k; ++k)
			{
				if (!ComByte_sub_802F6CC(&AnsBuf[k], OverTime))
					return 0;
				++*RecvSize;
			}
			*SpeciData = AnsBuf[3];
			SpeciData[1] = AnsBuf[5];
		}
	}
	else
	{
		v10 = 0;
		for (l = 1; v10 + 4 >= l; ++l)
		{
			if (!ComByte_sub_802F6CC(&AnsBuf[l], OverTime))
				return 0;
			++*RecvSize;
			if (l == 3)
				v10 = AnsBuf[3];
		}
		*SpeciData = AnsBuf[4];
		SpeciData[1] = AnsBuf[6];
	}
	return 1;
}