// 431Box.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "431Box.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


extern SC_UserPak UserPak_2000AFD0[81];
unsigned __int8 BlueThBuf_200078C0[2048];//下位机接收到的数据的存储地址 给函数指针处理
unsigned char ExitFlag_2000C6BA;//盒子退出接收上位机通讯标识

unsigned char*pGetDataFlag = (unsigned char*)malloc(4);//串口数据中断过来会改变这个指针地址的值 是一个有数据过来的标识
unsigned __int8 BackPhoneBlueTH_20008E3C[256];//返回给上位机的数据

unsigned int DataGroupNum_2000C67C;//接收串口数据有几组 一串数据可能会被分成几次处理 以6x xx xx 6x xx 的这类数据
unsigned char BlueThBuf_200078C1[300];
unsigned char byte_2000B8E4[300];
char CheckSuccessFlag;
unsigned int dword_804F3EC[5] = { 0x6203, 0x6105, 0x6109, 0x6225, 0x622A };
St20000000 st2000;
int dword_2000435C; // weak
int dword_800D4FC = 63; // weak
int dword_800E13C[10] = { 0x1C5C, (int)&st2000.field_400.field_2428, 0, -315,2, 2, 0xFFFF4CE0,0x24E, (int)&st2000.field_400, 0x2328 };
unsigned int *pdword_20004374;
unsigned int Data20004388[23];
// 唯一的应用程序对象


pfnCmdLine g_sCmdTable_200040E4[3][0x30] = {

	{
		/*6000*/    0,
		/*6001*/    ID6001Fun_SetIoParameter_1_sub_804BEA6,                     // JV700 通讯IO 设置
		/*6002*/    ID6002Fun_SetEcuBaudRate_1_sub_804C234,                     // K Line 通讯波特率
		/*6003*/    ID6003Fun_SetEcuCommTimeInterval_1_sub_804C39A,             // 整体通讯时序
		/*6004*/    ID6004Fun_SetLinkData_1_sub_804C4CA,                        // 设置链路维持
		/*6005*/    ID6005_Set5BpsParameter_1_sub_8022EB0,                      // 普通 5 Bps 地址码进入
		/*6006*/    ID6006Fun_SetBosch_1_sub_80215FA,                           // bosch 5 Bps 地址码进入
		/*6007*/    ID6007Fun_SetCommunicationLineVoltage_1_sub_804C946,        // K LINE 电平拉高或拉低
		/*6008*/    ID6008_SetBoschLink_1_Fun_sub_804CBC0,                      // bosch 协议链路维持
		/*6009*/    ID6009Fun_BoschFiat_1_sub_8024570,                          // Fiat车型 bosch 5 Bps 地址码进入
		/*600A*/    ID600AFun_SetAddressFiat_1_sub_8024694,                     // Fiat车型 5 Bps 地址码进入
		/*600B*/    ID600B_SetLinkNoAnswer_1_sub_804CA4C,                       // 设置IOS15765 链路保持
		/*600C*/    ID600C_SetCANBusLinkData_1_sub_804C9BA,                     // 设置 CANBUS 链路维持
		/*600D*/    ID600DFun_SetCANBus2LinkData_1_sub_804C9CE,                 // 设置 CANBUS 链路维持
		/*600E*/    ID600E_sub_804CA0C,                                         // 没有设置硬件 返回ok 或者FNG
		/*600F*/    ID600B_SetLinkNoAnswer_1_sub_804CA4C,                       // 设置链路位置且不等待应答
		/*6010*/    ID6005_Set5BpsParameter_1_sub_8022EB0,                      // bosch 5 Bps 地址码进入
		/*6011*/    ID6011_LandroverABSEnter_1_sub_802423C,                     // Landrover 地址码进入
		/*6012*/    0,                                                          // 无效函数
		/*6013*/    0,                                                          // 无效函数
		/*6014*/    ID6014FunShangHuanBoschSystem_1_sub_8023FC4,                // ShangHuan bosch 5 Bps 地址码进入
		/*6015*/    ID6015Fun_FiatBoschSystem_1_sub_80227CC,                    // Fiat车型 bosch 5 Bps 地址码进入
		/*6016*/    ID6016FunBenz38SelectLine_1_sub_804CC78,                    // BENZ 38PIN 接头选线
		/*6017*/    ID6017Fun_SetMitLinkKeep_sub_804CE88,                       // SetMitLinkKeep CAN 中断模式还没有做
		/*6018*/    ID6018_SetEnterFrameData_1_sub_8037060,                     // 设置 CAN 流控制帧
		/*6019*/    ID6019Fun_SetConnectorBaudRate_1_sub_804CF62,               // 设置上下位机通讯波特率，此函数无效
		/*601A*/    ID601A_SendAddressCodeTimeAdjustable_1_sub_8021FE4,         // 普通 5 Bps 地址码进入
		/*601B*/    ID601B_SetBenzHMFLinkKeep_1_sub_804CF70,                    // SetBenzHMFLinkKeep
		/*601C*/    ID601C_AddressCodeWayAdjustTime_benz_1_sub_802371C,         // 普通 5 Bps 地址码进入 FOR BENZ
		/*601D*/    ID601D_AddressCodeCommunicationWay_Lline_1_sub_8023CF4,     // 普通 5 Bps 地址码进入
		/*601E*/    ID601EFun_SelectMultiIoLine_sub_804D040,                    // JV700 无效果，设置多个 IO 口
		/*601F*/    ID601F_SetEnterFrameDataExt_1_sub_80370D6,                  // 设置 CAN 流控制帧（扩展帧）
		/*6020*/    ID6020Fun_GetBoxInfo_sub_804D04E,                           // 获取 BOX 信息
		/*6021*/    ID6021_GetDownloadType_sub_804D1C0,                         // 获取升级类型
		/*6022*/    ID6022_sub_804D1DC,                                         // 待完成 SetTimeParameter
		/*6023*/    ID6023_sub_802AB34,                                         // None
		/*6024*/    ID6024Fun_sub_802AD94,                                      // None
		/*6025*/    ID6025Fun_sub_804D64E,                                      // None
		/*6026*/    ID6026Fun_sub_804D69E,                                      // None
		/*6027*/    0,                                                          // None
		/*6028*/    ID6028Fun_sub_804D78C,                                      // None
		/*6029*/    0,                                                          // None
		/*602A*/    0,                                                          // None
		/*602B*/    0,                                                          // None
		/*602C*/    0,                                                          // None
		/*602D*/    ID602D_Fun_sub_804D6F2,                                     // None
		/*602E*/    ID602E_sub_804D3E0,                                         // None
		/*602F*/    ID602F_sub_804D4F8,                                         // None
	},

	{
		/*6100*/    0,                                                          // None
		/*6101*/    ID6101_sub_80292C4,                                         // 待完成 FlashCodeFunction
		/*6102*/    ID6102_sub_8024E98,                                         // 待完成 OnlyReceiveFromEcu
		/*6103*/    0,                                                          // None
		/*6104*/    ID6104FunOnlySendToEcu_1_sub_8023BB4,                       // 向 ECU 发送一帧数据
		/*6105*/    ID6105Funsub_805383C,                                       // 向 ECU 发送一帧数据并接收一帧数据
		/*6106*/    ID6106_sub_8022594,                                         // 待完成 SendOneAndReceiveMultiFrameKnownAckFrameNumber
		/*6107*/    ID6107_ISO_SendDataToEcuGetMultiFrameAnswer_1_sub_8026F6E,  // ISO 发送一帧接收多帧
		/*6108*/    0,                                                          // None
		/*6109*/    ID6109FunKWPSendDataToEcuGetAnswer_1_sub_802606E,           // KWP 发送一帧接收一帧
		/*610A*/    ID610A_BoschSendDataToEcuGetMultiFrameAnswer_1_sub_8022C14, // BOSCH 发送一帧接收多帧
		/*610B*/    ID610B_KWPSendOneAndReceiveMultiFrame_1_sub_8026230,        // KWP 发送一帧接收多帧
		/*610C*/    ID610C_PWM_SendDataToEcuGetAnswer_1_sub_8051266,            // PWM 发送一帧接收一帧
		/*610D*/    0,                                                          // None
		/*610E*/    ID610EFun_VpwSendOneAndReceiveOneFrame_1sub_8050F60,        // VPW 发送一帧接收一帧
		/*610F*/    ID610F_BoschSendDataToEcuGetAnswer_1_sub_8022AB4,           // BOSCH 发送一帧接收多帧
		/*6110*/    ID6110_ISO_SendDataToEcuGetAnswer_1_sub_80270FE,            // ISO 发送一帧接收一帧
		/*6111*/    ID6111_SendOneFrameDataToEcuGetAnyFrameAnswer_1_sub_8027594,// 发一帧收任意帧 hejm k线发送，格式有点奇怪
		/*6112*/    ID6112Fun_PwmSendOneAndReceiveMultiFrame_1_sub_8051460,     // PWM 发送一帧接收多帧
		/*6113*/    ID6113_CanbusOnlySendDataToEcu_1_sub_8028506,               // CAN 仅发不收，hejm 函数实际上是k线发送，怎么回事？
		/*6114*/    0,                 // None
		/*6115*/    0,                                                          // ReadByteBytedataLand
		/*6116*/    ID6116FunFordIsoSendOneAndReceiveMultiFrame_1_sub_80277DC,  // Ford ISO 发送一帧接收多帧
		/*6117*/    ID6117Fun_HoldenNormalRingLinkSendOneAndOneFrame_1_sub_8027970, // HoldenNormalRingLinkSendOneAndOneFrame
		/*6118*/    ID6118FunHoldenOnlyKnowHeadOfFrame_1__sub_8027C20,              // HoldenOnlyKnowHeadOfFrame
		/*6119*/    ID6119_SubruOldProtocol_1_sub_8027EF8,                      // SubruOldProtocol
		/*611A*/    ID611A_sub_8028184,                                         // SYS_SENDDATA_VOLVE
		/*611B*/    ID611B_Fun_VPW_HDN_SendDataToEcuGetMultiFrameAnswer_1_sub_805166C,    // VPW_Holden专用_发多帧收多帧
		/*611C*/    ID611C_Fun_SendOneFrameDataToEcuGetAnyFrameAnswer_Check_1_sub_80282D0,//  SendOneFrameDataToEcuGetAnyFrameAnswer_Check
		/*611D*/    ID611D_VPW_HDN_SendDataToEcuGetMultiFrameAnswer_1_sub_80516EA,        // VPW发多收多Holden专用
		/*611E*/    ID611E_sub_802A530,                                                  // none
		/*611F*/    ID611F_HoldenCan20SendOneFrameReceiveDatas_1_sub_8037154,           // Holden Can 发一帧 接收多帧
		/*6120*/    ID6120_JAGUARPWM_SendDataToEcuGetMultiFrameAnswer_1_sub_8051586,    // 发一帧 PWM 接收指定 PWM 数据
		/*6121*/    ID6121_WabcoAbsSendOneAndReicveOneFrame_1_sub_80218F0,              // WabcoAbsSendOneAndReicveOneFrame
		/*6122*/    ID6122_WabcoAbsSendOneAndReicveMultiFrame_1_sub_8021A92,            //  WabcoAbsSendOneAndReicveMultiFrame
		/*6123*/    0,                                                          // none
		/*6124*/    0,                                                          // none
		/*6125*/    0,                                                         //  QuickSendTwoFrameReceiveMultiFrame
		/*6126*/    ID6126_OneToOne_SendLongDataToEcuGetLongAnswer_1_sub_8021DF8,  //  OneToOne_SendLongDataToEcuGetLongAnswer
		/*6127*/    ID6127_VpwSendMultiFrameAndReceiveMultiFrameKnownAckFrameNumber_1_sub_80510C0, // VPW 发多收多
		/*6128*/    ID6128_OneToOne_SendOneByteToEcuGetAnswerLM_1_sub_80272B8,    // OneToOne_SendOneByteToEcuGetAnswerLM
		/*6129*/    ID6129_KWPSendOneAndReceiveMultiFrameHasFilter_1_sub_80273FA,   // KWPSendOneAndReceiveMultiFrameHasFilter
		/*612A*/    0,                                                          //
		/*612B*/    ID612B_sub_802A3BC,                                         //
		/*612C*/    0,                                                          //
		/*612D*/    ID612D_sub_803B2A0,                                         //
		/*612E*/    ID612E_sub_803B8EC,                                         //
		/*612F*/    0,
	},

	{
		/*6200*/    0,                                                          // none
		/*6201*/    ID6201_Can20SendTwoFrameQuickGetInfo_1_sub_8038784,         // CANBUS 发两帧收一块
		/*6202*/    ID6202_sub_8038974,                              // CANBUS 发一帧收指定多帧
		/*6203*/    ID6203_sub_80372C8,                            // CANBUS 发一帧收未知多帧
		/*6204*/    ID6204_sub_8037934,                            // none
		/*6205*/    ID6205_VWCANSendDataToEcuGetMultiFrameAnswer1_1_sub_803814C,     // VW 发送一块接收一块
		/*6206*/    ID6206_sub_802892A,                                              // VwSpecialFunctionReadPassword
		/*6207*/    ID6207_sub_8039C8C,                        // OPEL CAN 发多帧收多帧
		/*6208*/    ID6208_sub_8021008,                 // 东风专用发多帧收一帧
		/*6209*/    0,                                                 // ChryslerCcdOneToOne
		/*620A*/    ID620A_sub_8028592,                                // LandroverSendAndReceiveFilter
		/*620B*/    ID620B_LandroverSendAndReceiveFault_1_sub_8028D14, // BenzReadByteFromECU
		/*620D*/    0,
		/*620E*/    ID620E_sub_8028F84,                                                          // none
		/*620F*/    ID620F_sub_8028B98,                                                          // 待完成 SsangyongSendOneByteAndReceiveByte
		/*6210*/    ID6210_sub_8026480,                                                          // 待完成 WabcoEcasSendOneByteAndReceiveByte
		/*6211*/    ID6211_sub_80265D8,                                // KWP 接收一帧发送一帧
		/*6212*/    ID6212_sub_8038E0C,                                // KWP 接收一帧发送一帧 VOVLO
		/*6213*/    ID6213_sub_802675C,                                // Toyota CAN 发送一帧接收一帧
		/*6214*/    0,                                                 // Toyota KWP 发送一帧接收一帧
		/*6215*/    0,                                                 // none
		/*6216*/    0,                                                 // SAE_J1708_SendDataToEcuGetAnswer
		/*6217*/    ID6217_sub_8039144,                                // CumminsDieselSAE1708_SendMultiFramesToEcuGetAnswer
		/*6218*/    ID6218_sub_80286E4,                                // Porsche CAN 接收多帧
		/*6219*/    ID6219_sub_804D740,                                // SysGazSendBankSingleFrame
		/*621A*/    0,                                                 // ResetComm
		/*621B*/    0,                                                 // none
		/*621C*/    0,                                                 // none
		/*621D*/    0,                                                 // none
		/*621E*/    0,                                                 // none
		/*621F*/    ID621F_sub_802694C,                                            // none
		/*6220*/    ID6220_KWP_SendDataToEcuGetAnswer_Benz_1_sub_8026C32,          // BENZ KWP 发一帧收一帧
		/*6221*/    ID6221_KWP_SendDataToEcuGetMultiFrameAnswer_Benz_1_sub_80287F4,// BENZ KWP 发一帧收多帧
		/*6222*/    ID6222_SendOneFrameToEcuGetMultiFrameAnswer_1_sub_803A008,     // SendOneFrameToEcuGetMultiFrameAnswer
		/*6223*/    ID6223_sub_8026DB0,                                            // 待完成 CumminsSAE1939_SendMultiFramesToEcuGetAnswer
		/*6224*/    ID6224_sub_8039550,                            // KWP BMW  发一帧收一帧
		/*6225*/    0,                                             // CAN 发一帧收多帧
		/*6226*/    ID6226_sub_8039914,                            // 待完成 OneToOne_SendLongDataToEcuGetLongAnswer
		/*6227*/    ID6227_sub_8053E00,                            // CAN 发多帧收一帧
		/*6228*/    ID6228_sub_803ADF4,                            // 待完成 OneToOne_SendOneByteToEcuGetAnswer
		/*6229*/    ID6229_sub_803A3B0,                            // none
		/*622A*/    ID622A_sub_802AF50,                            // none
		/*622B*/    0,                                             // none
		/*622C*/    ID622C_sub_803AFF8,                            // none
		/*622D*/    0,                                             // none
		/*622E*/    0,                                             // none
		/*622F*/    0,                                             // none
	}

};
CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 更改错误代码以符合您的需要
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
			Reset_Handler();
			CmdLineProcessStart_sub_804435C();//处理代码流程入口
        }
    }
    else
    {
        // TODO: 更改错误代码以符合您的需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}





void Reset_Handler()
{
	//InitRam_sub_800DF08();
	//IRQPrioritySet_sub_80086E6();

}



int *InitRam_sub_800DF08()
{
	int *result; // r0 MAPDST

	result = dword_800E13C;
	//do
	result = memset_0_sub_8001936(result);// 调用顺序memset_0_sub_8001936 sub_800E00C 
	InitSRAM_sub_800E00C(result + 1);
	//while (result != &DataFFFF[1]);
	return result;
}

void IRQPrioritySet_sub_80086E6()
{
	sub_800B718();                                // 初始化ram地址的一些数据
	st2000.field_400.sub_8002042(&st2000.field_400);// sub_8002042
}

void sub_800B718()
{
	sub_800D4A8();
	if (sub_800B5D2() != 1)
	{
		while (1)
			;
	}
}


void sub_800D4A8()
{
	
}


void GiveToA2ValToA1Buf_sub_800D430(unsigned __int8 *A1Val, __int16 A2Val)
{
	while (A2Val)
	{
		*A1Val++ = 0;
		--A2Val;
	}
}


int sub_800B5D2()
{

	return 1;
}




int sub_800D442(unsigned int *a1, unsigned int a2, int a3, _BYTE *a4)
{
	unsigned int *v4; // r5
	int result; // r0
	unsigned int *v6; // r7
	unsigned int *v7; // r6
	unsigned int i; // lr

	v4 = (unsigned int *)dword_2000435C;
	if (dword_2000435C)
		dword_2000435C = *(_DWORD *)(dword_2000435C + 4);
	if (v4)
	{
		v6 = a1;
		v7 = a1;
		for (i = 0; i < a2 - 1; ++i)
		{
			v7 = (unsigned int *)((char *)v7 + a3);
			*v6 = (unsigned int)v7;
			v6 = v7;
		}
		*v6 = 0;
		*v4 = (unsigned int)a1;
		v4[1] = (unsigned int)a1;
		v4[4] = a2;
		v4[3] = a2;
		v4[2] = a3;
		*a4 = 0;
		result = (int)v4;
	}
	else
	{
		*a4 = 0x5A;
		result = 0;
	}
	return result;
}




unsigned int * sub_800B5C0(int a1)
{
	return sub_800D1DA(a1);
}



unsigned int * sub_800D1DA(unsigned int a1)
{
	unsigned int v2; // r4
	unsigned int v3; // r3
	unsigned int v4; // r5
	unsigned int v5; // r3
	unsigned int *v6; // r5
	unsigned int *v7; // r2
	int v8; // r4
	unsigned int *v10; // r6
	unsigned int *v11; // r5
	int v12; // r3
	unsigned int v13; // r5
	int v14; // r3
	unsigned int v15; // r6
	int v16; // r5
	unsigned int v17; // r6
	int v18; // r7
	unsigned int v19; // r6
	int v20; // r5
	unsigned int *v21; // r6
	unsigned int *v22; // r3
	unsigned int *v23; // r12
	unsigned int v24; // r1
	unsigned int *v25; // r4
	unsigned int *v26; // r5
	unsigned int v27; // r7
	unsigned int *v28; // lr
	unsigned int v29; // r2
	unsigned int v30; // r3
	unsigned int *v31; // r1
	unsigned int *v32; // r2
	int v33; // r1

	sub_800D88C(1u);
	if (a1 >= 0xF5)
	{
		if (a1 < -0x40)
		{
			v2 = 8 * ((a1 + 0xB) >> 3);
			if (st2000.field_400.field_3B60)
			{
				v11 = sub_800CC7C(&st2000.field_400.field_3B5C, v2);
				if (v11)
					goto LABEL_49;
			}
		}
		else
		{
			v2 = 0xFFFFFFFF;
		}
		goto LABEL_41;
	}
	if (a1 >= 0xB)
		v2 = 8 * ((a1 + 0xB) >> 3);
	else
		v2 = 0x10;
	v3 = v2 >> 3;
	v4 = st2000.field_400.field_3B5C >> (v2 >> 3);
	if ((v4 & 3) == 0)
	{
		if (st2000.field_400.field_3B64 < v2)
		{
			if (v4)
			{
				v12 = (v4 << v3) & ((0xFFFFFFFE * (1 << v3)) | (2 * (1 << v3)));
				v13 = (v12 & -v12) - 1;
				v14 = (v13 >> 0xC) & 0x10;
				v15 = v13 >> v14;
				v16 = (v13 >> v14 >> 5) & 8;
				v17 = v15 >> v16;
				v18 = (v17 >> 2) & 4;
				v19 = v17 >> v18;
				v20 = (v19 >> ((v19 >> 1) & 2) >> (((v19 >> ((v19 >> 1) & 2)) & 2) != 0))
					+ v18
					+ v16
					+ v14
					+ ((v19 >> 1) & 2)
					+ ((v19 >> ((v19 >> 1) & 2) >> 1) & 1);
				v21 = &st2000.field_400.field_3B84[2 * v20];
				v22 = st2000.field_400.field_3B8C[2 * v20];
				if (8 * (v22[1] >> 3) != 8 * v20)
					return sub_800D82A();
				v23 = (unsigned int *)v22[2];
				if (v22 == v21 || v22 == v23)
					return sub_800D82A();
				if (v21 == v23)
				{
					st2000.field_400.field_3B5C &= ~(1 << v20);
				}
				else
				{
					if (v23 < st2000.field_400.field_3B6C)
						return sub_800D82A();
					st2000.field_400.field_3B8C[2 * v20] = v23;
					v23[3] = (unsigned int)v21;
				}
				v24 = 8 * v20 - v2;
				v22[1] = v2 | 3;
				v25 = (unsigned int *)((char *)v22 + v2);
				v25[1] = v24 | 1;
				*(unsigned int *)((char *)v25 + v24) = v24;
				if (st2000.field_400.field_3B64)
				{
					v26 = st2000.field_400.field_3B70;
					v27 = st2000.field_400.field_3B64 >> 3;
					if (st2000.field_400.field_3B64 >> 3 >= 0x20)
						return sub_800D82A();
					v28 = &st2000.field_400.field_3B84[2 * v27];
					if (st2000.field_400.field_3B64 < 0x10)
						return sub_800D82A();
					if ((st2000.field_400.field_3B5C & (1 << v27)) != 0)
					{
						v28 = st2000.field_400.field_3B8C[2 * v27];
						if (v28 < st2000.field_400.field_3B6C)
							return sub_800D82A();
					}
					else
					{
						st2000.field_400.field_3B5C |= 1 << v27;
					}
					st2000.field_400.field_3B8C[2 * v27] = st2000.field_400.field_3B70;
					v28[3] = (unsigned int)v26;
					v26[2] = (unsigned int)v28;
					v26[3] = (unsigned int)&st2000.field_400.field_3B84[2 * v27];
				}
				st2000.field_400.field_3B64 = v24;
				st2000.field_400.field_3B70 = v25;
				v11 = v22 + 2;
				goto LABEL_49;
			}
			if (!st2000.field_400.field_3B60)
			{
			LABEL_46:
				v33 = st2000.field_400.field_3B68;
				if (v2 >= st2000.field_400.field_3B68)
				{
					v11 = sub_800CB30(&st2000.field_400.field_3B5C, v2);
					goto LABEL_49;
				}
				st2000.field_400.field_3B68 -= v2;
				v7 = st2000.field_400.field_3B74;
				st2000.field_400.field_3B74 = (unsigned int *)((char *)st2000.field_400.field_3B74 + v2);
				st2000.field_400.field_3B74[1] = (v33 - v2) | 1;
				v7[1] = v2 | 3;
				goto LABEL_16;
			}
			v11 = sub_800CFF0((int *)&st2000.field_400.field_3B5C, v2);
			if (v11)
				goto LABEL_49;
		}
	LABEL_41:
		v29 = st2000.field_400.field_3B64;
		if (st2000.field_400.field_3B64 >= v2)
		{
			v30 = st2000.field_400.field_3B64 - v2;
			v31 = st2000.field_400.field_3B70;
			if (st2000.field_400.field_3B64 - v2 < 0x10)
			{
				st2000.field_400.field_3B64 = 0;
				st2000.field_400.field_3B70 = 0;
				v31[1] = v29 | 3;
				*(unsigned int *)((char *)v31 + v29 + 4) |= 1u;
			}
			else
			{
				st2000.field_400.field_3B70 = (unsigned int *)((char *)st2000.field_400.field_3B70 + v2);
				v32 = st2000.field_400.field_3B70;
				st2000.field_400.field_3B64 -= v2;
				st2000.field_400.field_3B70[1] = v30 | 1;
				*(unsigned int *)((char *)v32 + v30) = v30;
				v31[1] = v2 | 3;
			}
			v11 = v31 + 2;
			goto LABEL_49;
		}
		goto LABEL_46;
	}
	v5 = ((v4 & 1) == 0) + v3;
	v6 = &st2000.field_400.field_3B84[2 * v5];
	v7 = st2000.field_400.field_3B8C[2 * v5];
	v8 = 2 * v5;
	if (8 * (v7[1] >> 3) != 8 * v5)
		return sub_800D82A();
	v10 = (unsigned int *)v7[2];
	if (v7 == v6 || v7 == v10 || 2 * (v7[1] >> 3) != v8)
		return sub_800D82A();
	if (v6 != v10)
	{
		if (v10 >= st2000.field_400.field_3B6C)
		{
			st2000.field_400.field_3B8C[2 * v5] = v10;
			v10[3] = (unsigned int)v6;
			goto LABEL_15;
		}
		return sub_800D82A();
	}
	st2000.field_400.field_3B5C &= ~(1 << v5);
LABEL_15:
	v7[1] = (v8 * 4) | 3;
	v7[v8 + 1] |= 1u;
LABEL_16:
	v11 = v7 + 2;
LABEL_49:
	sub_800D8D0(1u);
	return v11;
}

void sub_800D8D0(unsigned int result)
{
	if (result < 5)
		return;//nullsub_3();
}

void sub_800D88C(unsigned int a1)
{

}


unsigned int * sub_800CC7C(unsigned int *a1, int a2)
{
	unsigned int *v2; // r2
	unsigned int v3; // r3
	unsigned int v4; // r4
	unsigned int v5; // r4
	unsigned int v6; // r5
	unsigned int v7; // r4
	unsigned int v8; // r4
	unsigned int *v9; // r5
	int v10; // r6
	unsigned int v11; // r6
	unsigned int *v12; // r7
	unsigned int v13; // r12
	unsigned int *v14; // r12
	int v15; // r4
	unsigned int v16; // r5
	int v17; // r4
	unsigned int v18; // r6
	int v19; // r5
	unsigned int v20; // r6
	int v21; // r7
	unsigned int v22; // r6
	unsigned int *v23; // r4
	unsigned int v24; // r5
	unsigned int *v26; // r7
	unsigned int *v27; // r6
	unsigned int *v28; // r12
	unsigned int *v29; // r12
	unsigned int *v30; // lr
	unsigned int *v31; // r12
	unsigned int *v32; // r7
	unsigned int *v33; // r7
	unsigned int v34; // r1
	unsigned int *v35; // r3
	unsigned int *v36; // r6
	int v37; // r1
	unsigned int v38; // r1
	unsigned int v39; // r6
	unsigned int v40; // r5
	unsigned int v41; // r1
	unsigned int v42; // r1
	unsigned int *v43; // r1
	unsigned int v44; // r7
	int v45; // r5
	unsigned int v46; // r5
	unsigned int **v47; // r7
	unsigned int *v48; // r3
	unsigned int v49; // r5

	v2 = 0;
	v3 = -a2;
	v4 = a2 >> 8;
	if (a2 >> 8)
	{
		if (v4 < 0x10000)
		{
			v6 = ((v4 - 0x100) >> 0x10) & 8;
			v7 = v4 << v6;
			v8 = 0xE
				- v6
				- (((v7 - 0x1000) >> 0x10) & 4)
				- ((((v7 << (((v7 - 0x1000) >> 0x10) & 4)) - 0x4000) >> 0x10) & 2)
				+ (v7 << (((v7 - 0x1000) >> 0x10) & 4) << ((((v7 << (((v7 - 0x1000) >> 0x10) & 4)) - 0x4000) >> 0x10) & 2) >> 0xF);
			v5 = ((a2 >> (v8 + 7)) & 1) + 2 * v8;
		}
		else
		{
			v5 = 0x1F;
		}
	}
	else
	{
		v5 = 0;
	}
	v9 = (unsigned int *)a1[v5 + 0x4C];
	if (!v9)
	{
	LABEL_21:
		v15 = ((2 * (1 << v5)) | (0xFFFFFFFE * (1 << v5))) & a1[1];
		if (!v15)
			return 0;
		v16 = (v15 & -v15) - 1;
		v17 = (v16 >> 0xC) & 0x10;
		v18 = v16 >> v17;
		v19 = (v16 >> v17 >> 5) & 8;
		v20 = v18 >> v19;
		v21 = (v20 >> 2) & 4;
		v22 = v20 >> v21;
		v9 = (unsigned int *)a1[(v22 >> ((v22 >> 1) & 2) >> (((v22 >> ((v22 >> 1) & 2)) & 2) != 0))
			+ 0x4C
			+ v21
			+ v19
			+ v17
			+ ((v22 >> 1) & 2)
			+ ((v22 >> ((v22 >> 1) & 2) >> 1) & 1)];
		goto LABEL_23;
	}
	if (v5 == 0x1F)
		LOBYTE(v10) = 0;
	else
		v10 = 0x19 - (v5 >> 1);
	v11 = a2 << v10;
	v12 = 0;
	while (1)
	{
		v13 = 8 * (v9[1] >> 3) - a2;
		if (v13 < v3)
		{
			v2 = v9;
			v3 = 8 * (v9[1] >> 3) - a2;
			if (!v13)
				break;
		}
		v14 = (unsigned int *)v9[5];
		v9 = (unsigned int *)v9[(v11 >> 0x1F) + 4];
		if (v14 && v14 != v9)
			v12 = v14;
		if (!v9)
		{
			v9 = v12;
			break;
		}
		v11 *= 2;
	}
	if (!v9)
	{
		if (v2)
			goto LABEL_30;
		goto LABEL_21;
	}
LABEL_23:
	while (v9)
	{
		while (1)
		{
			if (8 * (v9[1] >> 3) - a2 < v3)
			{
				v3 = 8 * (v9[1] >> 3) - a2;
				v2 = v9;
			}
			if (!v9[4])
				break;
			v9 = (unsigned int *)v9[4];
		}
		v9 = (unsigned int *)v9[5];
	}
LABEL_30:
	if (v2 && v3 < a1[2] - a2)
	{
		if ((unsigned int)v2 < a1[4])
			return sub_800D82A();
		v23 = (unsigned int *)((char *)v2 + a2);
		v24 = a2 + v3;
		if (8 * (v2[1] >> 3) != a2 + v3 || v2 >= v23)
			return sub_800D82A();
		v26 = (unsigned int *)v2[6];
		v27 = (unsigned int *)v2[3];
		if (v27 == v2)
		{
			v29 = v2 + 5;
			v27 = (unsigned int *)v2[5];
			if (v27 || (v29 = v2 + 4, (v27 = (unsigned int *)v2[4]) != 0))
			{
				while (1)
				{
					v30 = v27 + 5;
					if (!v27[5])
					{
						v30 = v27 + 4;
						if (!v27[4])
							break;
					}
					v29 = v30;
					v27 = (unsigned int *)*v30;
				}
				if ((unsigned int)v29 < a1[4])
					return sub_800D82A();
				*v29 = 0;
			}
		}
		else
		{
			v28 = (unsigned int *)v2[2];
			if ((unsigned int)v28 < a1[4])
				return sub_800D82A();
			v28[3] = (unsigned int)v27;
			v27[2] = (unsigned int)v28;
		}
		if (v26)
		{
			v31 = &a1[v2[7] + 0x4C];
			if (v2 == (unsigned int *)*v31)
			{
				*v31 = (unsigned int)v27;
				if (!v27)
				{
					a1[1] &= ~(1 << v2[7]);
					goto LABEL_63;
				}
			}
			else
			{
				if ((unsigned int)v26 < a1[4])
					return sub_800D82A();
				if ((unsigned int *)v26[4] == v2)
					v26[4] = (unsigned int)v27;
				else
					v26[5] = (unsigned int)v27;
			}
			if (v27)
			{
				if ((unsigned int)v27 < a1[4])
					return sub_800D82A();
				v27[6] = (unsigned int)v26;
				v32 = (unsigned int *)v2[4];
				if (v32)
				{
					if ((unsigned int)v32 < a1[4])
						return sub_800D82A();
					v27[4] = (unsigned int)v32;
					v32[6] = (unsigned int)v27;
				}
				v33 = (unsigned int *)v2[5];
				if (v33)
				{
					if ((unsigned int)v33 < a1[4])
						return sub_800D82A();
					v27[5] = (unsigned int)v33;
					v33[6] = (unsigned int)v27;
				}
			}
		}
	LABEL_63:
		if (v3 < 0x10)
		{
			v2[1] = v24 | 3;
			*(unsigned int *)((char *)v2 + v24 + 4) |= 1u;
			return v2 + 2;
		}
		v2[1] = a2 | 3;
		v23[1] = v3 | 1;
		*(unsigned int *)((char *)v23 + v3) = v3;
		v34 = v3 >> 3;
		if (v3 >> 3 >= 0x20)
		{
			v38 = v3 >> 8;
			if (v3 >> 8)
			{
				if (v38 < 0x10000)
				{
					v40 = ((v38 - 0x100) >> 0x10) & 8;
					v41 = v38 << v40;
					v42 = 0xE
						- v40
						- (((v41 - 0x1000) >> 0x10) & 4)
						- ((((v41 << (((v41 - 0x1000) >> 0x10) & 4)) - 0x4000) >> 0x10) & 2)
						+ (v41 << (((v41 - 0x1000) >> 0x10) & 4) << ((((v41 << (((v41 - 0x1000) >> 0x10) & 4)) - 0x4000) >> 0x10) & 2) >> 0xF);
					v39 = ((v3 >> (v42 + 7)) & 1) + 2 * v42;
				}
				else
				{
					v39 = 0x1F;
				}
			}
			else
			{
				v39 = 0;
			}
			v43 = &a1[v39 + 0x4C];
			v23[7] = v39;
			v23[5] = 0;
			v23[4] = 0;
			v44 = a1[1];
			if ((v44 & (1 << v39)) == 0)
			{
				a1[1] = v44 | (1 << v39);
				*v43 = (unsigned int)v23;
			LABEL_77:
				v23[6] = (unsigned int)v43;
				v23[3] = (unsigned int)v23;
				v23[2] = (unsigned int)v23;
				return v2 + 2;
			}
			v43 = (unsigned int *)*v43;
			if (v39 == 0x1F)
				LOBYTE(v45) = 0;
			else
				v45 = 0x19 - (v39 >> 1);
			v46 = v3 << v45;
			while (8 * (v43[1] >> 3) != v3)
			{
				v47 = (unsigned int **)&v43[(v46 >> 0x1F) + 4];
				v46 *= 2;
				if (!*v47)
				{
					if ((unsigned int)v47 < a1[4])
						return sub_800D82A();
					*v47 = v23;
					goto LABEL_77;
				}
				v43 = *v47;
			}
			v48 = (unsigned int *)v43[2];
			v49 = a1[4];
			if ((unsigned int)v43 >= v49 && (unsigned int)v48 >= v49)
			{
				v48[3] = (unsigned int)v23;
				v43[2] = (unsigned int)v23;
				v23[2] = (unsigned int)v48;
				v23[3] = (unsigned int)v43;
				v23[6] = 0;
				return v2 + 2;
			}
		}
		else
		{
			v35 = &a1[2 * v34 + 0xA];
			v36 = v35;
			v37 = 1 << v34;
			if ((*a1 & v37) == 0)
			{
				*a1 |= v37;
			LABEL_69:
				v35[2] = (unsigned int)v23;
				v36[3] = (unsigned int)v23;
				v23[2] = (unsigned int)v36;
				v23[3] = (unsigned int)v35;
				return v2 + 2;
			}
			v36 = (unsigned int *)v35[2];
			if ((unsigned int)v36 >= a1[4])
				goto LABEL_69;
		}
		return sub_800D82A();
	}
	return 0;
}



unsigned int * sub_800D82A()
{
	return  sub_800D8EC();
}


unsigned int * sub_800D8EC()
{
	return sub_800D908();
	//while (1)	
		//__breakpoint(0xAB);
}

unsigned int * sub_800D908()
{
	unsigned int *v0; // r2
	unsigned int *v2; // [sp+0h] [bp-8h]

	v0 = sub_800D938();
	//v2 = (unsigned int *)v0[1];
	if (*v0 != 0xFFFFFFFF)
	{
		//__breakpoint(0xAB);
		*v0 = 0;
	}
	if (v0[1] != 0xFFFFFFFF)
	{
		//__breakpoint(0xAB);
		v0[1] = 0;
	}
	return (unsigned int *)v0[1];//这里可能会有问题 
}

unsigned int *sub_800D938()
{
	return (_DWORD *)(&st2000 + 0x2708);
}


unsigned int * sub_800D834()
{
	unsigned int *result; // r0

	if (pdword_20004374)
		return 0;
	result = Data20004388;
	pdword_20004374 = Data20004388;
	Data20004388[0] = 0x10000;
	return result;
}


void sub_800C5FC(unsigned int *result, unsigned int *a2, int a3)
{
	int v3; // r3
	unsigned int *v4; // r1
	unsigned int v5; // r2

	if ((((_BYTE)a2 + 8) & 7) != 0)
		v3 = (8 - (((_BYTE)a2 + 8) & 7)) & 7;
	else
		v3 = 0;
	v4 = (unsigned int *)((char *)a2 + v3);
	v5 = a3 - v3;
	result[6] = (unsigned int)v4;
	result[3] = v5;
	v4[1] = v5 | 1;
	*(unsigned int *)((char *)v4 + v5 + 4) = 0x28;
	result[7] = (unsigned int)g_sCmdTable_200040E4[2][0x2A];
}


unsigned int * sub_800CB30(unsigned int *a1, unsigned int a2)
{
	unsigned int *v4; // r0 MAPDST
	int v6; // r2
	unsigned int v7; // r0
	unsigned int v8; // r0
	unsigned int *v9; // r0
	int v10; // r3
	int v11; // r2
	unsigned int *i; // r3
	unsigned int v13; // r7
	unsigned int *j; // r3
	unsigned int *v15; // r0
	unsigned int v17; // r0
	unsigned int v18; // r0
	unsigned int *v19; // r1

	if (!g_sCmdTable_200040E4[2][0x26])
		sub_800C5C8();
	v4 = sub_800D834();
	if (!v4)
		return 0;
	v6 = *v4;
	if (v4 == (unsigned int *)0xFFFFFFFF)
		return 0;
	a1[0x6C] += v6;
	v7 = a1[0x6D];
	if (v7 < a1[0x6C])
		v7 = a1[0x6C];
	a1[0x6D] = v7;
	if (a1[6])
	{
		for (i = a1 + 0x6F; i; i = (unsigned int *)i[2])
		{
			if (v4 == (unsigned int *)(i[1] + *i))
			{
				if ((i[3] & 8) == 0 && a1[6] >= *i)
				{
					v13 = i[1];
					if (a1[6] < v13 + *i)
					{
						i[1] = v6 + v13;
						v11 = v6 + a1[3];
						v4 = (unsigned int *)a1[6];
						goto LABEL_15;
					}
				}
				break;
			}
		}
		if ((unsigned int)v4 < a1[4])
			a1[4] = (unsigned int)v4;
		for (j = a1 + 0x6F; j; j = (unsigned int *)j[2])
		{
			if ((unsigned int *)*j == (unsigned int *)((char *)v4 + v6))
			{
				if ((j[3] & 8) == 0)
				{
					v15 = (unsigned int *)*j;
					*j = (unsigned int)v4;
					j[1] += v6;
					return sub_800C638(a1, v4, v15, a2);
				}
				break;
			}
		}
		sub_800C93E(a1, v4, v6, 0);
	}
	else
	{
		v8 = a1[4];
		if (!v8 || (unsigned int)v4 < v8)
			a1[4] = (unsigned int)v4;
		a1[0x6F] = (unsigned int)v4;
		a1[0x70] = v6;
		a1[0x72] = 0;
		a1[9] = (unsigned int)g_sCmdTable_200040E4[2][0x26];
		a1[8] = 0xFFFFFFFF;
		v9 = a1;
		v10 = 0x20;
		do
		{
			v9[0xD] = (unsigned int)(v9 + 0xA);
			v9[0xC] = (unsigned int)(v9 + 0xA);
			v9 += 2;
			--v10;
		} while (v10);
		if (a1 == &st2000.field_400.field_3B5C)
		{
			v11 = v6 - 0x28;
		}
		else
		{
			v11 = (char *)v4 + v6 - (char *)&a1[2 * (*(a1 - 1) >> 3) - 2] - 0x28;
			v4 = &a1[2 * (*(a1 - 1) >> 3) - 2];
		}
	LABEL_15:
		sub_800C5FC(a1, v4, v11);
	}
	v17 = a1[3];
	if (a2 >= v17)
		return 0;
	v18 = v17 - a2;
	a1[3] = v18;
	v19 = (unsigned int *)a1[6];
	a1[6] = (unsigned int)v19 + a2;
	*(unsigned int *)((char *)v19 + a2 + 4) = v18 | 1;
	v19[1] = a2 | 3;
	return v19 + 2;
}


int sub_800C5C8()
{
	
	return 1;
}



unsigned int * sub_800CFF0(int *a1, int a2)
{
	unsigned int v2; // r3
	int v3; // r2
	unsigned int v4; // r3
	int v5; // r4
	unsigned int v6; // r3
	int v7; // r5
	unsigned int v8; // r3
	unsigned int *v9; // r4
	unsigned int *v10; // r3
	unsigned int v11; // r2
	unsigned int *v12; // r4
	unsigned int v13; // r5
	unsigned int *v15; // r7
	unsigned int *v16; // r6
	unsigned int *v17; // r12
	unsigned int *v18; // r12
	unsigned int *v19; // lr
	int *v20; // r12
	unsigned int *v21; // r7
	unsigned int *v22; // r7
	unsigned int v23; // r7
	unsigned int *v24; // r1
	unsigned int v25; // r12
	unsigned int *v26; // r6

	v2 = (a1[1] & -a1[1]) - 1;
	v3 = (v2 >> 0xC) & 0x10;
	v4 = v2 >> v3;
	v5 = (v4 >> 5) & 8;
	v6 = v4 >> v5;
	v7 = (v6 >> 2) & 4;
	v8 = v6 >> v7;
	v9 = (unsigned int *)a1[(v8 >> ((v8 >> 1) & 2) >> (((v8 >> ((v8 >> 1) & 2)) & 2) != 0))
		+ 0x4C
		+ ((v8 >> ((v8 >> 1) & 2) >> 1) & 1)
		+ ((v8 >> 1) & 2)
		+ v7
		+ v5
		+ v3];
	v10 = v9;
	v11 = 8 * (v9[1] >> 3) - a2;
	while (1)
	{
		v9 = (unsigned int *)(v9[4] ? v9[4] : v9[5]);
		if (!v9)
			break;
		if (8 * (v9[1] >> 3) - a2 < v11)
		{
			v11 = 8 * (v9[1] >> 3) - a2;
			v10 = v9;
		}
	}
	if ((unsigned int)v10 < a1[4])
		return sub_800D82A();
	v12 = (unsigned int *)((char *)v10 + a2);
	v13 = a2 + v11;
	if (8 * (v10[1] >> 3) != a2 + v11 || v10 >= v12)
		return sub_800D82A();
	v15 = (unsigned int *)v10[6];
	v16 = (unsigned int *)v10[3];
	if (v16 == v10)
	{
		v18 = v10 + 5;
		v16 = (unsigned int *)v10[5];
		if (v16 || (v18 = v10 + 4, (v16 = (unsigned int *)v10[4]) != 0))
		{
			while (1)
			{
				v19 = v16 + 5;
				if (!v16[5])
				{
					v19 = v16 + 4;
					if (!v16[4])
						break;
				}
				v18 = v19;
				v16 = (unsigned int *)*v19;
			}
			if ((unsigned int)v18 < a1[4])
				return sub_800D82A();
			*v18 = 0;
		}
	}
	else
	{
		v17 = (unsigned int *)v10[2];
		if ((unsigned int)v17 < a1[4])
			return sub_800D82A();
		v17[3] = (unsigned int)v16;
		v16[2] = (unsigned int)v17;
	}
	if (!v15)
		goto LABEL_39;
	v20 = &a1[v10[7] + 0x4C];
	if (v10 == (unsigned int *)*v20)
	{
		*v20 = (int)v16;
		if (!v16)
		{
			a1[1] &= ~(1 << v10[7]);
			goto LABEL_39;
		}
	}
	else
	{
		if ((unsigned int)v15 < a1[4])
			return sub_800D82A();
		if ((unsigned int *)v15[4] == v10)
			v15[4] = (unsigned int)v16;
		else
			v15[5] = (unsigned int)v16;
	}
	if (v16)
	{
		if ((unsigned int)v16 < a1[4])
			return sub_800D82A();
		v16[6] = (unsigned int)v15;
		v21 = (unsigned int *)v10[4];
		if (v21)
		{
			if ((unsigned int)v21 < a1[4])
				return sub_800D82A();
			v16[4] = (unsigned int)v21;
			v21[6] = (unsigned int)v16;
		}
		v22 = (unsigned int *)v10[5];
		if (v22)
		{
			if ((unsigned int)v22 < a1[4])
				return sub_800D82A();
			v16[5] = (unsigned int)v22;
			v22[6] = (unsigned int)v16;
		}
	}
LABEL_39:
	if (v11 >= 0x10)
	{
		v10[1] = a2 | 3;
		v12[1] = v11 | 1;
		*(unsigned int *)((char *)v12 + v11) = v11;
		v23 = a1[2];
		if (!v23)
		{
		LABEL_48:
			a1[2] = v11;
			a1[5] = (int)v12;
			return v10 + 2;
		}
		v24 = (unsigned int *)a1[5];
		v25 = v23 >> 3;
		if (v23 >> 3 < 0x20)
		{
			v26 = (unsigned int *)&a1[2 * v25 + 0xA];
			if (v23 >= 0x10)
			{
				if ((*a1 & (1 << v25)) == 0)
				{
					*a1 |= 1 << v25;
				LABEL_47:
					a1[2 * v25 + 0xC] = (int)v24;
					v26[3] = (unsigned int)v24;
					v24[2] = (unsigned int)v26;
					v24[3] = (unsigned int)&a1[2 * v25 + 0xA];
					goto LABEL_48;
				}
				v26 = (unsigned int *)a1[2 * v25 + 0xC];
				if ((unsigned int)v26 >= a1[4])
					goto LABEL_47;
			}
		}
		return sub_800D82A();
	}
	v10[1] = v13 | 3;
	*(unsigned int *)((char *)v10 + v13 + 4) |= 1u;
	return v10 + 2;
}



unsigned int *sub_800C638(unsigned int *a1, unsigned int *a2, unsigned int *a3, int a4)
{
	int v4; // r4
	unsigned int *v5; // r1
	int v6; // r4
	unsigned int *v7; // r5
	unsigned int *v8; // r2
	unsigned int v9; // r4
	unsigned int v11; // r6
	unsigned int v12; // r3
	unsigned int v13; // r3
	int v14; // r3
	unsigned int v15; // lr
	unsigned int *v16; // r7
	unsigned int *v17; // r12
	unsigned int *v18; // r6
	unsigned int *v19; // r7
	unsigned int *v20; // r6
	unsigned int *v21; // r12
	_DWORD *v22; // r12
	_DWORD *v23; // lr
	unsigned int *v24; // r12
	unsigned int *v25; // r7
	unsigned int *v26; // r7
	unsigned int v27; // r3
	unsigned int *v28; // r5
	unsigned int *v29; // r6
	int v30; // r3
	unsigned int v31; // r3
	unsigned int v32; // r5
	unsigned int v33; // r5
	unsigned int v34; // r3
	unsigned int v35; // r3
	unsigned int *v36; // r3
	unsigned int v37; // r7
	int v38; // r5
	unsigned int v39; // r5
	unsigned int **v40; // r7
	unsigned int *v41; // r4
	unsigned int v42; // r0

	if ((((_BYTE)a2 + 8) & 7) != 0)
		v4 = (8 - (((_BYTE)a2 + 8) & 7)) & 7;
	else
		v4 = 0;
	v5 = (unsigned int *)((char *)a2 + v4);
	if ((((_BYTE)a3 + 8) & 7) != 0)
		v6 = (8 - (((_BYTE)a3 + 8) & 7)) & 7;
	else
		v6 = 0;
	v7 = (unsigned int *)((char *)a3 + v6);
	v8 = (unsigned int *)((char *)v5 + a4);
	v9 = (char *)v7 - (char *)v5 - a4;
	v5[1] = a4 | 3;
	if ((unsigned int *)((char *)v5 + a4) >= v7)
		return sub_800D82A();
	v11 = v7[1];
	if ((v11 & 1) == 0 || v9 < 0x10)
		return sub_800D82A();
	if (v7 != (unsigned int *)a1[6])
	{
		if (v7 == (unsigned int *)a1[5])
		{
			v13 = v9 + a1[2];
			a1[2] = v13;
			a1[5] = (unsigned int)v8;
			v8[1] = v13 | 1;
			*(unsigned int *)((char *)v8 + v13) = v13;
			return v5 + 2;
		}
		if ((v7[1] & 3) != 1)
		{
		LABEL_54:
			v7[1] = 2 * (v7[1] >> 1);
			v8[1] = v9 | 1;
			*(unsigned int *)((char *)v8 + v9) = v9;
			v27 = v9 >> 3;
			if (v9 >> 3 >= 0x20)
			{
				v31 = v9 >> 8;
				if (v9 >> 8)
				{
					if (v31 < 0x10000)
					{
						v33 = ((v31 - 0x100) >> 0x10) & 8;
						v34 = v31 << v33;
						v35 = 0xE
							- v33
							- (((v34 - 0x1000) >> 0x10) & 4)
							- ((((v34 << (((v34 - 0x1000) >> 0x10) & 4)) - 0x4000) >> 0x10) & 2)
							+ (v34 << (((v34 - 0x1000) >> 0x10) & 4) << ((((v34 << (((v34 - 0x1000) >> 0x10) & 4)) - 0x4000) >> 0x10) & 2) >> 0xF);
						v32 = ((v9 >> (v35 + 7)) & 1) + 2 * v35;
					}
					else
					{
						v32 = 0x1F;
					}
				}
				else
				{
					v32 = 0;
				}
				v36 = &a1[v32 + 0x4C];
				v8[7] = v32;
				v8[5] = 0;
				v8[4] = 0;
				v37 = a1[1];
				if ((v37 & (1 << v32)) == 0)
				{
					a1[1] = (1 << v32) | v37;
					*v36 = (unsigned int)v8;
				LABEL_67:
					v8[6] = (unsigned int)v36;
					v8[3] = (unsigned int)v8;
					v8[2] = (unsigned int)v8;
					return v5 + 2;
				}
				v36 = (unsigned int *)*v36;
				if (v32 == 0x1F)
					LOBYTE(v38) = 0;
				else
					v38 = 0x19 - (v32 >> 1);
				v39 = v9 << v38;
				while (8 * (v36[1] >> 3) != v9)
				{
					v40 = (unsigned int **)&v36[(v39 >> 0x1F) + 4];
					v39 *= 2;
					if (!*v40)
					{
						if ((unsigned int)v40 < a1[4])
							return sub_800D82A();
						*v40 = v8;
						goto LABEL_67;
					}
					v36 = *v40;
				}
				v41 = (unsigned int *)v36[2];
				v42 = a1[4];
				if ((unsigned int)v36 >= v42 && (unsigned int)v41 >= v42)
				{
					v41[3] = (unsigned int)v8;
					v36[2] = (unsigned int)v8;
					v8[2] = (unsigned int)v41;
					v8[3] = (unsigned int)v36;
					v8[6] = 0;
					return v5 + 2;
				}
			}
			else
			{
				v28 = &a1[2 * v27 + 0xA];
				v29 = v28;
				if (v9 >= 0x10)
				{
					v30 = 1 << v27;
					if ((*a1 & v30) == 0)
					{
						*a1 |= v30;
					LABEL_59:
						v28[2] = (unsigned int)v8;
						v29[3] = (unsigned int)v8;
						v8[2] = (unsigned int)v29;
						v8[3] = (unsigned int)v28;
						return v5 + 2;
					}
					v29 = (unsigned int *)v28[2];
					if ((unsigned int)v29 >= a1[4])
						goto LABEL_59;
				}
			}
			return sub_800D82A();
		}
		v14 = 8 * (v11 >> 3);
		v15 = v11 >> 3;
		if (v11 >> 3 < 0x20)
		{
			v16 = (unsigned int *)v7[2];
			v17 = (unsigned int *)v7[3];
			if (v7 == v17 || v7 == v16)
				return sub_800D82A();
			if (v16 == v17)
			{
				*a1 &= ~(1 << v15);
			}
			else
			{
				v18 = &a1[2 * v15];
				if (v16 != v18 + 0xA && (unsigned int)v16 < a1[4] || v17 != v18 + 0xA && (unsigned int)v17 < a1[4])
					return sub_800D82A();
				v16[3] = (unsigned int)v17;
				v17[2] = (unsigned int)v16;
			}
			goto LABEL_53;
		}
		v19 = (unsigned int *)v7[6];
		v20 = (unsigned int *)v7[3];
		if (v20 == v7)
		{
			v22 = v7 + 5;
			v20 = (unsigned int *)v7[5];
			if (v20 || (v22 = v7 + 4, (v20 = (unsigned int *)v7[4]) != 0))
			{
				while (1)
				{
					v23 = v20 + 5;
					if (!v20[5])
					{
						v23 = v20 + 4;
						if (!v20[4])
							break;
					}
					v22 = v23;
					v20 = (unsigned int *)*v23;
				}
				if ((unsigned int)v22 < a1[4])
					return sub_800D82A();
				*v22 = 0;
			}
		}
		else
		{
			v21 = (unsigned int *)v7[2];
			if ((unsigned int)v21 < a1[4])
				return sub_800D82A();
			v21[3] = (unsigned int)v20;
			v20[2] = (unsigned int)v21;
		}
		if (!v19)
			goto LABEL_53;
		v24 = &a1[v7[7] + 0x4C];
		if (v7 == (unsigned int *)*v24)
		{
			*v24 = (unsigned int)v20;
			if (!v20)
			{
				a1[1] &= ~(1 << v7[7]);
			LABEL_53:
				v7 = (unsigned int *)((char *)v7 + v14);
				v9 += v14;
				goto LABEL_54;
			}
		}
		else
		{
			if ((unsigned int)v19 < a1[4])
				return sub_800D82A();
			if ((unsigned int *)v19[4] == v7)
				v19[4] = (unsigned int)v20;
			else
				v19[5] = (unsigned int)v20;
		}
		if (v20)
		{
			if ((unsigned int)v20 < a1[4])
				return sub_800D82A();
			v20[6] = (unsigned int)v19;
			v25 = (unsigned int *)v7[4];
			if (v25)
			{
				if ((unsigned int)v25 < a1[4])
					return sub_800D82A();
				v20[4] = (unsigned int)v25;
				v25[6] = (unsigned int)v20;
			}
			v26 = (unsigned int *)v7[5];
			if (v26)
			{
				if ((unsigned int)v26 < a1[4])
					return sub_800D82A();
				v20[5] = (unsigned int)v26;
				v26[6] = (unsigned int)v20;
			}
		}
		goto LABEL_53;
	}
	v12 = v9 + a1[3];
	a1[3] = v12;
	a1[6] = (unsigned int)v8;
	v8[1] = v12 | 1;
	return v5 + 2;
}



unsigned int * sub_800C93E(unsigned int *a1, unsigned int *a2, int a3, int a4)
{
	unsigned int *v5; // r5
	unsigned int *v6; // r0
	unsigned int v7; // r8
	unsigned int v8; // r0
	int v9; // r1
	unsigned int *v10; // r10
	unsigned int *v11; // r11
	unsigned int *v12; // r9
	int v13; // r7
	unsigned int v14; // r2
	unsigned int v15; // r3
	unsigned int v16; // r12
	unsigned int *result; // r0
	unsigned int v18; // r0
	unsigned int v19; // r1
	unsigned int *v20; // r3
	unsigned int v21; // r1
	unsigned int v22; // r2
	unsigned int v23; // r2
	unsigned int v24; // r1
	unsigned int v25; // r1
	unsigned int *v26; // r1
	int v27; // r3
	unsigned int v28; // r6
	int v29; // r2
	unsigned int v30; // r2
	unsigned int *v31; // r6
	unsigned int *v32; // r0
	unsigned int v33; // r2

	v5 = (unsigned int *)a1[6];
	v6 = a1 + 0x6F;
	do
	{
		if ((unsigned int)v5 >= *v6 && (unsigned int)v5 < v6[1] + *v6)
			break;
		v6 = (unsigned int *)v6[2];
	} while (v6);
	v7 = v6[1] + *v6;
	v8 = v7 - 0x2F;
	if ((((_BYTE)v7 - 0x27) & 7) != 0)
		v9 = (8 - (((_BYTE)v7 - 0x27) & 7)) & 7;
	else
		v9 = 0;
	v10 = (unsigned int *)(v9 + v8);
	if (v9 + v8 < (unsigned int)(v5 + 4))
		v10 = v5;
	v11 = v10 + 2;
	v12 = v10 + 6;
	v13 = 0;
	sub_800C5FC(a1, a2, a3 - 0x28);
	if (((unsigned int)(v10 + 2) & 7) != 0)
		return sub_800D82A();
	v10[1] = 0x1B;
	v14 = a1[0x70];
	v15 = a1[0x71];
	v16 = a1[0x72];
	*v11 = a1[0x6F];
	v10[3] = v14;
	v10[4] = v15;
	v10[5] = v16;
	a1[0x6F] = (unsigned int)a2;
	a1[0x70] = a3;
	a1[0x72] = a4;
	a1[0x71] = (unsigned int)v11;
	while (1)
	{
		result = v12 + 1;
		v12[1] = 7;
		++v13;
		if ((unsigned int)(v12 + 2) >= v7)
			break;
		++v12;
	}
	if (v13 < 2)
		return sub_800D82A();
	if (v10 != v5)
	{
		v18 = (char *)v10 - (char *)v5;
		v10[1] = 2 * (v10[1] >> 1);
		v5[1] = ((char *)v10 - (char *)v5) | 1;
		*v10 = (char *)v10 - (char *)v5;
		v19 = (unsigned int)((char *)v10 - (char *)v5) >> 3;
		if (v19 < 0x20)
		{
			v20 = &a1[2 * v19 + 0xA];
			if (v18 >= 0x10)
			{
				if ((*a1 & (1 << v19)) == 0)
				{
					result = (unsigned int *)((1 << v19) | *a1);
					*a1 = (unsigned int)result;
				LABEL_21:
					a1[2 * v19 + 0xC] = (unsigned int)v5;
					v20[3] = (unsigned int)v5;
					v5[2] = (unsigned int)v20;
					v5[3] = (unsigned int)&a1[2 * v19 + 0xA];
					return result;
				}
				v20 = (unsigned int *)a1[2 * v19 + 0xC];
				result = (unsigned int *)a1[4];
				if (v20 >= result)
					goto LABEL_21;
			}
			return sub_800D82A();
		}
		v21 = v18 >> 8;
		if (v18 >> 8)
		{
			if (v21 < 0x10000)
			{
				v23 = ((v21 - 0x100) >> 0x10) & 8;
				v24 = v21 << v23;
				v25 = 0xE
					- v23
					- (((v24 - 0x1000) >> 0x10) & 4)
					- ((((v24 << (((v24 - 0x1000) >> 0x10) & 4)) - 0x4000) >> 0x10) & 2)
					+ (v24 << (((v24 - 0x1000) >> 0x10) & 4) << ((((v24 << (((v24 - 0x1000) >> 0x10) & 4)) - 0x4000) >> 0x10) & 2) >> 0xF);
				v22 = ((v18 >> (v25 + 7)) & 1) + 2 * v25;
			}
			else
			{
				v22 = 0x1F;
			}
		}
		else
		{
			v22 = 0;
		}
		v26 = &a1[v22 + 0x4C];
		v5[7] = v22;
		v5[5] = 0;
		v5[4] = 0;
		v27 = 1 << v22;
		v28 = a1[1];
		if ((v28 & (1 << v22)) != 0)
		{
			v26 = (unsigned int *)*v26;
			if (v22 == 0x1F)
				LOBYTE(v29) = 0;
			else
				v29 = 0x19 - (v22 >> 1);
			v30 = v18 << v29;
			while (8 * (v26[1] >> 3) != v18)
			{
				v31 = &v26[(v30 >> 0x1F) + 4];
				v30 *= 2;
				if (!*v31)
				{
					result = (unsigned int *)a1[4];
					if (v31 < result)
						return sub_800D82A();
					*v31 = (unsigned int)v5;
					goto LABEL_31;
				}
				v26 = (unsigned int *)*v31;
			}
			v32 = (unsigned int *)v26[2];
			v33 = a1[4];
			if ((unsigned int)v26 >= v33 && (unsigned int)v32 >= v33)
			{
				v32[3] = (unsigned int)v5;
				v26[2] = (unsigned int)v5;
				v5[2] = (unsigned int)v32;
				v5[3] = (unsigned int)v26;
				result = 0;
				v5[6] = 0;
				return result;
			}
			return sub_800D82A();
		}
		result = (unsigned int *)(v27 | v28);
		a1[1] = v27 | v28;
		*v26 = (unsigned int)v5;
	LABEL_31:
		v5[6] = (unsigned int)v26;
		v5[3] = (unsigned int)v5;
		v5[2] = (unsigned int)v5;
	}
	return result;
}




// 传进来的参数 就是dword_800E13C 0x0800E13C
// 应该是初始化 0x20002728 这一块附近的值
// 长度是0x1C5C*4 
int * memset_0_sub_8001936(int *buf800E13C)
{
	int v1 = 0; // r9
	int *result; // r0
	int v3; // r1
	int v4; // t1
	int *v5; // r2
	int v6; // t1

	while (1)
	{
		v4 = *buf800E13C;
		result = buf800E13C + 1;
		v3 = v4;
		if (!v4)
			break;
		v6 = *result;
		buf800E13C = result+1;
		v5 = (int *)v6;
		if ((v6 & 1) != 0)
			v5 = (int *)((char *)v5 + v1 - 1);
		do
		{
			*v5++ = 0;

			v3 -= 4;
		} while (v3);
	}
	return result;
}



// 参数的地址是dword_800E14C
// 初始化 20000400 的这一块的地址 到0x20002728
int *InitSRAM_sub_800E00C(int *a1)
{
	int v1 = 0; // r9
	int *v2; // r1
	int *v3; // r2
	unsigned int v4; // r0
	int v5; // r3
	int *result; // r0
	char *v7; // r12
	char *v8; // lr
	int v9; // r4
	int v10; // r5
	char v12; // t1 MAPDST
	int *v14; // r2
	_BYTE *v15; // t1 MAPDST
	int v16; // t1
	_BYTE *v17; // r7
	int *v18; // r1
	int v19; // t1
	int v20; // t1
	int *v21; // r1
	int v22; // t1
	bool v23; // zf
	char v24; // t1

	v2 = a1 + 2;                                  // 0x0800E154
	v3 = &a1[*a1 + 2];                            // 0x0800E15C
	v4 = a1[1];                                   // 2
	v5 = v4 & 1;                                  // 0
	result = &v3[2 * (v4 >> 1)];                  // 0x0800E164
	v7 = 0;
	v8 = 0;
	v9 = 0;
	v10 = 1;
	while (v3 != result)                        // 0x0800E15C < 0x0800E164
	{
		v15 = (_BYTE *)*v3;                         // (_BYTE *)*v3 = 20000400 v14 = 0x0800E160
		v14 = v3 + 1;
		if (v5)
			v15 += v1;                                // 这一句好像一直不会执行
		v16 = *v14;                                 // v16 = 0x00002328  v3 = 0x0800E164
		v3 = v14 + 1;
		v17 = &v15[v16];                            // v17 = 0x20002728
	LABEL_6:
		while (v15 != v17)                        // 0x20000400 < 0x20002728
		{
			while (v7 == v8)
			{
				v7 = (char *)v2 + *v2;                  // *V2 = 0xFFFF4CE0  v7 = 0x08002E34
				v18 = v2 + 1;                           // v18 = 0x0800E158
				v19 = *v18;                             // v19 = 0x24E
				v2 = v18 + 1;
				v8 = &v7[v19];                          // v2 = 0x0800E15C  v8 = 0x08003082
			}
			if (v10)
			{
				v20 = *v7++;
				v9 = v20;
				v10 = 0;
				while (v7 == v8)
				{
					v7 = (char *)v2 + *v2;
					v21 = v2 + 1;
					v22 = *v21;
					v2 = v21 + 1;
					v8 = &v7[v22];
				}
			}
			if (v9 < 0)
			{
				v12 = *v7++;
				while (v15 != v17)
				{
					*v15++ = v12;                         // v15 = 20000400 往v15的地址存入数据
					v9 = (__int16)(v9 + 1);
					if (v9 >= 0)
						goto LABEL_5;
				}
			}
			else
			{
				while (1)
				{
					v9 = (__int16)v9;
					if ((v9 & 0x8000u) != 0)
						break;
					v23 = v15 == v17;
					if (v15 != v17)
						v23 = v7 == v8;
					if (v23)
						goto LABEL_6;
					v24 = *v7++;
					*v15++ = v24;                         // 往20000400这一块附近开始赋值
					LOWORD(v9) = v9 - 1;
				}
			LABEL_5:
				v10 = 1;
			}
		}
	}
	return result;
}


void CheckVerhardWare_WaitAppStart_sub_80087F6()
{
	while (1)
		CheckVerhardWare_WaitAppStart_sub_80020AE(&st2000.field_400);
}



// 这里的参数是对的  sub_80087F6() 调用这个函数
void CheckVerhardWare_WaitAppStart_sub_80020AE(CommSt *token)
{
	SecondReset_Handler_sub_800023E();
	
}


void SecondReset_Handler_sub_800023E()
{
	SecondReset_Handler_sub_80543B2();                                  // SecondReset_Handler_sub_80543B2
}




// 进入cmdline 之前的一些处理内容
void SecondReset_Handler_sub_80543B2()
{
	IRQPrioritySet_sub_8030FD6();
}

void IRQPrioritySet_sub_8030FD6()
{

	EnterCmdLineProcessStart_sub_80407AC();
}




// A1: 地址0x20000000  什么时候才会进入到这个sub_80407AC函数里面呢  IRQPrioritySet_sub_8030FD6 调用
void EnterCmdLineProcessStart_sub_80407AC()
{
	int v2; // r0	
	CmdLineProcessStart_sub_804435C();          // 这里就是不断处理程序和逻辑的地方

}



void CmdLineProcessStart_sub_804435C()
{
	int v0; // r4
	int CmdLenBuf[4]; // [sp+0h] [bp-10h] BYREF

	v0 = 0;
	BackPhoneBlueTH_20008E3C[0] = 0x67;
	BackPhoneBlueTH_20008E3C[1] = 1;
	*pGetDataFlag = 0;
	while (1)
	{
		do
		{
			while ((*pGetDataFlag & 4) != 0)        // 这里两个while 就是在等待有蓝牙数据进来
			{
				ExitFlag_2000C6BA = 0;
				CmdLenBuf[0] = DataGroupNum_2000C67C - 1;
				v0 = DataGroupNum_2000C67C - 1;
				//BlueThBuf_200078C1
				CmdLineProcess_sub_8049A78(CmdLenBuf, BlueThBuf_200078C1, &BackPhoneBlueTH_20008E3C[2]);
				if (ExitFlag_2000C6BA)
					memmove(byte_2000B8E4, BlueThBuf_200078C1, 300u);
				*pGetDataFlag = 0;
				GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, CmdLenBuf[0] + 2);// 这里是431盒子返回给手机的数据
				if (ExitFlag_2000C6BA)                // 经过6028函数后 返回的数据BackPhoneBlueTH_20008E3C 67 01 00 06 0B 02 D2 23 60 04 58
				{
					if (ExitFlag_2000C6BA == 1)
						Delay_sub_802EF46(90000u);
				}
			}
		} while (!ExitFlag_2000C6BA);               // 这里是一个死循环 sub_8037154 dui byte_2000C6BA 赋值
		CmdLenBuf[0] = v0;
		CmdLineProcess_sub_8049A78(CmdLenBuf, byte_2000B8E4, &BackPhoneBlueTH_20008E3C[2]);
		if (ExitFlag_2000C6BA == 1)
			Delay_sub_802EF46(90000u);
		if ((*pGetDataFlag & 4) != 0)
			*pGetDataFlag |= 0x10u;
		else
			GiveBackToPhoneBlueTHBuf_sub_8030F00(BackPhoneBlueTH_20008E3C, CmdLenBuf[0] + 2);
	}
}





// //Funtion: 指令解析
// //Input:  pcCmdLine - 输入指令
// //        CmdLen - 输入指令长度
// //OutPut: ans - 指令返回结果
// //        CmdLen - 输出指令长度
// //Return: true , CMDLINE_BAD_CMD, CMDLINE_TOO_MANY_ARGS
// //Info  : none
int CmdLineProcess_sub_8049A78(int *CmdLen, unsigned __int8 *BlueThBuf, _BYTE *Ans)
{
	int Pos; // r11
	unsigned int Cmdnumb; // r5
	int v8; // r7
	char v9; // r8
	int v10; // r9
	int v11; // r11
	_BYTE *v12; // r6
	char NoReEntFlag; // [sp+4h] [bp-3Ch]
	int tLen; // [sp+8h] [bp-38h]
	unsigned int FunID; // [sp+Ch] [bp-34h]
	unsigned int FunID1; // [sp+10h] [bp-30h]

	Pos = 0;
	tLen = *CmdLen;
	LOBYTE(Cmdnumb) = 0;
	NoReEntFlag = 0;
	Ans = 0;
	LOWORD(v8) = 0;
	v9 = 0;
	v10 = 0;
	while (Pos < tLen)
	{
		if (tLen - Pos < 3 && tLen >= 3)
		{
			*Ans = 0xFF;
			Ans[1] = 2;
			*CmdLen = 2;
			return 0;
		}
		if (NoReEntFlag)
			SC_UserPak_SolveREQ_sub_804B3C6(&BlueThBuf[Pos], &UserPak_2000AFD0[Cmdnumb]);// 0x2000AFD0 起始地址就是UserPack[16]的起始地址
		else
			SC_UserPak_SolveREQ_sub_804B038(&BlueThBuf[Pos], &UserPak_2000AFD0[Cmdnumb]);// 第一次进入走这里
		if (!NoReEntFlag && UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID == 0x6501)
		{
			NoReEntFlag = 1;
			Pos += 5;
			LOWORD(v8) = BlueThBuf[4] + (BlueThBuf[3] << 8);
			*Ans++ = 0;
			SC_UserPak_SolveREQ_sub_804B3C6(&BlueThBuf[Pos], (SC_UserPak *)(0xC * (unsigned __int8)Cmdnumb + 0x2000AFD0));
		}
		if (UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakLenth)
		{
			v11 = UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakLenth + Pos;
		}
		else
		{
			v11 = tLen - 2;
			UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakLenth = tLen - 2;
		}
		if (UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID >= 0x6400)// 如果>=0x6400
		{
			if (!CheckSuccessFlag)                     // unk_2000C6C3  只在ID6028 函数中赋值过
			{
				*Ans = 0xFF;
				Ans[1] = 2;
				*CmdLen = 2;
				return 0;
			}
			if (LOBYTE(UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID) < 5u)
				UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID = dword_804F3EC[LOBYTE(UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID)];
					// 这里对ID有一个转化
		}
		if (UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID < 0x6000
			|| UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID > 0x6400)
		{
			*Ans = 0xFF;
			Ans[1] = 2;
			*CmdLen = 2;
			return 0;
		}
		FunID = LOBYTE(UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID);
		FunID1 = (UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakCmdID >> 8) & 0xF;
		if (FunID >= 0x30)
		{
			*Ans = 0xFF;
			Ans[1] = 2;
			*CmdLen = 2;
			return 0;
		}
		if (g_sCmdTable_200040E4[FunID1][FunID])  // 跳到了这里 不知道是通过can 发送了命令 还是咋的
		{
			// 0x200040E4  Cmmst20000400.g_sCmdTable
			*CmdLen = g_sCmdTable_200040E4[FunID1][FunID](
				UserPak_2000AFD0[(unsigned __int8)Cmdnumb].PakLenth,
				UserPak_2000AFD0[(unsigned __int8)Cmdnumb].Pakdata,
				Ans);
		}
		else
		{
			*Ans = 0xFF;
			Ans[1] = 2;
			*CmdLen = 2;
		}
		if (NoReEntFlag == 1)
		{
			++v9;
			if (*CmdLen < 3)
			{
				if ((_WORD)v8)
				{
					*Ans = v9;
					v12 = Ans + 1;
					*v12++ = 0;
					*v12 = 0;
					Ans = v12 + 1;
					v10 += 3;
					v8 = (unsigned __int16)(v8 - 1);
					if (!v8)
					{
						v10 = (unsigned __int16)v10;
						*CmdLen = (unsigned __int16)v10 + 1;
					}
				}
			}
			else if ((_WORD)v8)
			{
				*Ans = v9;
				Ans += *CmdLen;
				v10 += *CmdLen;
				v8 = (unsigned __int16)(v8 - 1);
				if (!v8)
				{
					v10 = (unsigned __int16)v10;
					*CmdLen = (unsigned __int16)v10 + 1;
				}
			}
		}
		Pos = v11 + 2;
		Cmdnumb = (unsigned __int8)(Cmdnumb + 1);
		if (Cmdnumb >= 0x51)
			return 0;
	}
	return 0;
}





void SC_UserPak_SolveREQ_sub_804B3C6(unsigned __int8 *Temp, SC_UserPak *UserPak)
{
	int v2; // r6
	unsigned int v3; // r4
	unsigned int i; // r2
	unsigned __int8 *v5; // r5
	int v6; // r6
	unsigned int j; // r2
	int v8; // r3
	int v9; // [sp+4h] [bp-18h]

	v2 = 0;
	UserPak->PakCmdID = Temp[1] + (*Temp << 8);
	if (UserPak->PakCmdID == 0x6109)
	{
		v3 = Temp[3];
		v9 = 4;
		for (i = 0; i < v3; ++i)
		{
			v2 += Temp[v9];
			v9 += Temp[v9] + 1;
		}
		UserPak->PakLenth = v3 + v2 + 4;
		UserPak->PakLenth -= 2;
	}
	else if (UserPak->PakCmdID == 0x6203)
	{
		v5 = Temp + 5;
		v6 = 0;
		for (j = 0; j < Temp[2]; ++j)
		{
			v8 = *v5;
			v6 += v8 + 1;
			v5 += v8 + 1;
		}
		UserPak->PakLenth = v6 + 5;
		UserPak->PakLenth -= 2;
	}
	else
	{
		UserPak->PakLenth = 0;
	}
	UserPak->Pakdata = Temp + 2;
}




void SC_UserPak_SolveREQ_sub_804B038(unsigned __int8 *a1, SC_UserPak *UserPak)
{
	int v2; // r5
	unsigned int i; // r2
	unsigned int m; // r2
	unsigned int n; // r2
	unsigned int v6; // r3
	unsigned int j; // r2
	unsigned int v8; // r3
	unsigned int ii; // r2
	unsigned int l; // r2
	unsigned int v11; // r4
	unsigned int k; // r2
	int v13; // [sp+4h] [bp-14h]

	v2 = 0;
	UserPak->PakCmdID = a1[1] + (*a1 << 8);
	switch (UserPak->PakCmdID)
	{
	case 0x6001u:
		UserPak->PakLenth = 7;
		break;
	case 0x6002u:
		if (a1[2])
			UserPak->PakLenth = 3;
		else
			UserPak->PakLenth = 5;
		break;
	case 0x6003u:
		UserPak->PakLenth = 5;
		break;
	case 0x6004u:
		if (a1[2])
			UserPak->PakLenth = a1[2] + 3;
		else
			UserPak->PakLenth = 3;
		break;
	case 0x6005u:
		if (a1[2] == 2)
		{
			if (a1[7])
				UserPak->PakLenth = a1[7] + 6;
			else
				UserPak->PakLenth = 7;
		}
		else if (a1[6])
		{
			UserPak->PakLenth = a1[6] + 5;
		}
		else
		{
			UserPak->PakLenth = 6;
		}
		break;
	case 0x6006u:
		UserPak->PakLenth = 2;
		break;
	case 0x6007u:
		UserPak->PakLenth = 3;
		break;
	case 0x6008u:
		UserPak->PakLenth = 1;
		break;
	case 0x6009u:
		UserPak->PakLenth = 1;
		break;
	case 0x600Au:
		UserPak->PakLenth = 6;
		break;
	case 0x600Cu:
		if (a1[2])
			UserPak->PakLenth = a1[2] + 3;
		else
			UserPak->PakLenth = 3;
		break;
	case 0x600Du:
		goto LABEL_129;
	case 0x600Eu:
		UserPak->PakLenth = 2;
		break;
	case 0x6011u:
		UserPak->PakLenth = 4;
		break;
	case 0x6014u:
		UserPak->PakLenth = 1;
		break;
	case 0x6015u:
		UserPak->PakLenth = 1;
		break;
	case 0x6017u:
		UserPak->PakLenth = 1;
		for (i = 0; i < a1[2]; ++i)
			UserPak->PakLenth += a1[UserPak->PakLenth + 2] + 2;
		++UserPak->PakLenth;
		break;
	case 0x6018u:
		UserPak->PakLenth = a1[2] + 1;
		break;
	case 0x601Au:
		if (a1[2] == 1)
			UserPak->PakLenth = a1[9] + 8;
		if (a1[2] == 2)
			UserPak->PakLenth = a1[10] + 9;
		break;
	case 0x601Bu:
	LABEL_129:
		if (a1[2])
			UserPak->PakLenth = a1[2] + 3;
		else
			UserPak->PakLenth = 3;
		break;
	case 0x601Cu:
		if (a1[2] == 1)
			UserPak->PakLenth = a1[10] + 9;
		if (a1[2] == 2)
			UserPak->PakLenth = a1[11] + 10;
		break;
	case 0x601Eu:
		UserPak->PakLenth = *a1 + 1;
		break;
	case 0x601Fu:
		UserPak->PakLenth = a1[3] + 2;
		break;
	case 0x6106u:
		UserPak->PakLenth = a1[2] + 1;
		v6 = a1[UserPak->PakLenth++];
		for (j = 0; j < v6; ++j)
		{
			if (a1[UserPak->PakLenth])
				++UserPak->PakLenth;
			else
				UserPak->PakLenth += 2;
		}
		break;
	default:
		switch (UserPak->PakCmdID)
		{
		case 0x6107u:
			UserPak->PakLenth = a1[2] + 3;
			goto LABEL_126;
		case 0x6109u:
		LABEL_120:
			v11 = a1[3];
			v13 = 4;
			for (k = 0; k < v11; ++k)
			{
				v2 += a1[v13];
				v13 += a1[v13] + 1;
			}
			UserPak->PakLenth = v11 + v2 + 4;
			goto LABEL_126;
		case 0x610Au:
			UserPak->PakLenth = a1[2] + 2;
			goto LABEL_126;
		case 0x610Bu:
			UserPak->PakLenth = a1[2] + 3;
			goto LABEL_126;
		}
		if (UserPak->PakCmdID != 0x610F)
		{
			if (UserPak->PakCmdID != 0x6110)
			{
				switch (UserPak->PakCmdID)
				{
				case 0x6111u:
					UserPak->PakLenth = a1[2] + 4;
					break;
				case 0x6117u:
					UserPak->PakLenth = 5;
					for (l = 0; l < a1[3]; ++l)
						UserPak->PakLenth += a1[UserPak->PakLenth + 3] + 2;
					break;
				case 0x6118u:
					UserPak->PakLenth = 2;
					break;
				case 0x611Cu:
					UserPak->PakLenth = a1[4] + 8;
					break;
				case 0x611Fu:
					UserPak->PakLenth = a1[3] * (a1[5] + 2) + 3;
					break;
				case 0x6121u:
					UserPak->PakLenth = 3;
					for (m = 0; m < a1[2]; ++m)
						UserPak->PakLenth += a1[UserPak->PakLenth] + 2;
					break;
				case 0x6122u:
					UserPak->PakLenth = a1[2] + 3;
					break;
				case 0x6125u:
					UserPak->PakLenth = 2;
					for (n = 0; n < 2; ++n)
						UserPak->PakLenth += a1[UserPak->PakLenth] + 1;
					break;
				case 0x6126u:
					UserPak->PakLenth = a1[3] + (a1[2] << 8) + 2;
					break;
				case 0x6129u:
					UserPak->PakLenth = a1[3] + 3;
					break;
				default:
					UserPak->PakLenth = 0;
					break;
				}
				break;
			}
			goto LABEL_120;
		}
		v8 = a1[3];
		UserPak->PakLenth = 2;
		for (ii = 0; ii < v8; ++ii)
			UserPak->PakLenth += a1[UserPak->PakLenth + 2] + 1;
		break;
	}
LABEL_126:
	UserPak->Pakdata = a1 + 2;
}


//通过系统滴答延时
void Delay_sub_802EF46(unsigned int a1)
{
	
}




void GiveBackToPhoneBlueTHBuf_sub_8030F00(unsigned __int8 *BackPhoneBlueTH_20008E3C, unsigned char Len)
{
	
	SendDataToPhone_sub_8040D9C(&st2000, BackPhoneBlueTH_20008E3C, &Len);// SendDataToPhone_sub_8040D9C
}



// 这里A1的地址是从0x20000000开始的
void SendDataToPhone_sub_8040D9C(St20000000 *StAddr20000000, unsigned __int8 *BackPhoneBlueTH_20008E3C, unsigned __int8 *pLen)
{
	SendDataToPhonesub_8040CAE(StAddr20000000, &BackPhoneBlueTH_20008E3C, (int*)&pLen, 1);// SendDataToPhonesub_8040CAE
}


// A1:0x20000000地址
// A2:指向BackPhoneBlueTH_20008E3C的指针
// A3:指向长度的指针
// A4:长度的数据 占用多少字节
void SendDataToPhonesub_8040CAE(St20000000 *St200, unsigned __int8 **a2, int *pLen, unsigned int LenbufLen)
{
	unsigned int v8; // r9
	unsigned int i; // r8
	unsigned __int8 *v10; // r10
	unsigned int j; // r8
	unsigned __int8 v12 = 0; // r0
	unsigned __int8 v13[8]; // [sp+0h] [bp-28h] BYREF

	v8 = 0;
	for (i = 0; i < LenbufLen; ++i)
		v8 += pLen[i];
	if (v8 && v8 < 0x2009)
	{
		St200->field_400.BlueThToPhoneData[0] = 0x55;
		St200->field_400.BlueThToPhoneData[1] = 0xAA;
		St200->field_400.BlueThToPhoneData[2] = St200->field_B;
		St200->field_400.BlueThToPhoneData[3] = St200->field_A;
		St200->field_400.BlueThToPhoneData[4] = (unsigned __int16)(v8 + 1) >> 8;
		St200->field_400.BlueThToPhoneData[5] = v8 + 1;
		St200->field_400.BlueThToPhoneData[6] = St200->DataValidLen;
		v10 = &St200->field_400.BlueThToPhoneData[7];
		for (j = 0; j < LenbufLen; ++j)           // St200->field_2038处的值为55 AA F8 F0 00 0C 02 00
		{
			Copysub_802FB50(v10, a2[j], pLen[j]);     // 55 AA F8 F0 00 0C 02 67 01 00 06 0B 02 D2 03 60 04 58
			v10 += pLen[j];
		}                                           // SendDataByUsart_sub_8040C30
		St200->field_400.SendDataByUsart_sub_8040C30(St200, St200->field_400.BlueThToPhoneData, v8 + 7);
		v13[0] = v12;                               // 通过串口将命令发送出去
		St200->field_400.SendDataByUsart_sub_8040C30(St200, v13, 1);// SendDataByUsart_sub_8040C30
		St200->field_400.BlueThToPhoneData[v8 + 7] = v13[0];
		St200->field_400.BlueThNum = v8 + 8;
	}
	St200->field_400.SetTIMUSART_sub_8040A9E(St200, 1);// SetTIMUSART_sub_8040A9E
}