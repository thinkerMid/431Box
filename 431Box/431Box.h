#pragma once

#include "resource.h"
#include "431Box.h"
#include "FUN_Base.h"

struct St20000000;
struct SC_UserPak;
struct CommSt;

int DataFFFF[506] =
{
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
	-1,  -1,  -1,  -1,  -1,  -1
}; // weak

void Reset_Handler();
int *InitRam_sub_800DF08();
void IRQPrioritySet_sub_80086E6();
void sub_800B718();
void sub_800D4A8();
void GiveToA2ValToA1Buf_sub_800D430(unsigned __int8 *A1Val, __int16 A2Val);

int sub_800B5D2();
int sub_800D442(unsigned int *a1, unsigned int a2, int a3, _BYTE *a4);
unsigned int * sub_800B5C0(int a1);
unsigned int *sub_800D1DA(unsigned int a1);
void sub_800D8D0(unsigned int result);
void sub_800D88C(unsigned int a1);

unsigned int * sub_800CC7C(unsigned int *a1, int a2);
unsigned int * sub_800D82A();
unsigned int * sub_800D8EC();
unsigned int * sub_800D908();
unsigned int *sub_800D938();
void sub_800C5FC(unsigned int *result, unsigned int *a2, int a3);
unsigned int * sub_800CB30(unsigned int *a1, unsigned int a2);
int sub_800C5C8();
unsigned int * sub_800CFF0(int *a1, int a2);

unsigned int *sub_800C638(unsigned int *a1, unsigned int *a2, unsigned int *a3, int a4);
unsigned int* sub_800C93E(unsigned int *a1, unsigned int *a2, int a3, int a4);
int * memset_0_sub_8001936(int *buf800E13C);
int *InitSRAM_sub_800E00C(int *a1);















void CheckVerhardWare_WaitAppStart_sub_80020AE(CommSt *token);
void SecondReset_Handler_sub_800023E();
void SecondReset_Handler_sub_80543B2();
void IRQPrioritySet_sub_8030FD6();
void EnterCmdLineProcessStart_sub_80407AC();
void CmdLineProcessStart_sub_804435C();
int CmdLineProcess_sub_8049A78(int *CmdLen, unsigned __int8 *BlueThBuf, _BYTE *Ans);
void SC_UserPak_SolveREQ_sub_804B3C6(unsigned __int8 *Temp, SC_UserPak *UserPak);
void SC_UserPak_SolveREQ_sub_804B038(unsigned __int8 *a1, SC_UserPak *UserPak);
void Delay_sub_802EF46(unsigned int a1);
void GiveBackToPhoneBlueTHBuf_sub_8030F00(unsigned __int8 *BackPhoneBlueTH, unsigned char Len);

void SendDataToPhone_sub_8040D9C(St20000000 *StAddr20000000, unsigned __int8 *BackPhoneBlueTH, unsigned __int8 *pLen);
void SendDataToPhonesub_8040CAE(St20000000 *St200, unsigned __int8 **a2, int *pLen, unsigned int LenbufLen);

typedef int(*pfnCmdLine)(int argc, unsigned char *argv, unsigned char *ans);








struct StA
{
	unsigned __int8 field_0;
	char field_1;
	char field_2;
	char field_3;
	char field_4;
	char field_5;
	__int16 field_6;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
};

/* 421 */
struct St373C
{
	unsigned __int8 field_0;
	unsigned __int8 field_1;
	char field_2;
	char field_3;
	__int16 field_4;
	__int16 field_6;
	char field_8;
	char field_9;
	char field_A;
	char field_B;
	unsigned int *field_C;
	_DWORD *field_10;
	int field_14;
	unsigned int *field_18[15];
	unsigned int *field_54[15];
	int field_90[15];
	unsigned int *field_CC[15];
	int field_108;
	_DWORD *field_10C;
	char field_110;
	char field_111;
	char field_112;
	char field_113;
	int field_114;
	int field_118[10];
	StA field_140;
	int field_158[14];
	int field_190[15];
	int field_1CC[15];
	int field_208[15];
	int field_244[15];
	int field_280[15];
	int field_2BC[15];
	int field_2F8[15];
	int field_334[15];
	int field_370[123];
	void(__fastcall *sub_80407AC)(St20000000 *);
	int field_560;
	void(__fastcall *NVIC_GenerateSystemReset_sub_80407FA)(St20000000 *);
	int(__fastcall *sub_8040410)(St20000000 *);
	int field_56C;
	void(__fastcall *sub_8040882)(St20000000 *, _DWORD, int);
	int(__fastcall *SendDataByUsart_sub_8040C30)(St20000000 *, unsigned __int8 *, unsigned int);
	void(__fastcall *SendDataToPhone_sub_8040D9C)(St20000000 *, unsigned __int8 *, int);
	void(__fastcall *SendDataToPhonesub_8040CAE)(St20000000 *, unsigned __int8 **, unsigned int *, int);
	int field_580;
	void(__fastcall *SetTIMUSART_sub_8040A9E)(St20000000 *, int);
	void(__fastcall *field_588)(St20000000 *);
	int(__fastcall *Pos7_case21sub_8040DB2)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *field_590)(St20000000 *, unsigned __int8 *, int);
	int(__fastcall *field_594)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *field_598)(St20000000 *, unsigned __int8 *, int);
	int(__fastcall *Pos7_case25_sub_80416EC)(St20000000 *, unsigned __int8 *, int);
	int(__fastcall *field_5A0)(St20000000 *, unsigned __int8 *, int);
	int(__fastcall *field_5A4)();
	int field_5A8;
	int field_5AC;
	int field_5B0;
	int field_5B4;
	int field_5B8;
	int field_5BC;
	int field_5C0;
	int field_5C4;
	unsigned int field_5C8;
	int field_5CC;
	int field_5D0;
	int field_5D4;
	int field_5D8;
	int field_5DC;
	int field_5E0;
	void(*field_5E4)(void);
	int field_5E8;
	int field_5EC;
};

struct COM_PORTMODE
{
	int BaudRate;
	int WordLength;
	int StopBits;
	int Parity;
};


struct TIM_TypeDef
{
	volatile uint16_t CR1;
	uint16_t RESERVED0;
	volatile uint16_t CR2;
	uint16_t RESERVED1;
	volatile uint16_t SMCR;
	uint16_t RESERVED2;
	volatile uint16_t DIER;
	uint16_t RESERVED3;
	volatile uint16_t SR;
	uint16_t RESERVED4;
	volatile uint16_t EGR;
	uint16_t RESERVED5;
	volatile uint16_t CCMR1;
	uint16_t RESERVED6;
	volatile uint16_t CCMR2;
	uint16_t RESERVED7;
	volatile uint16_t CCER;
	uint16_t RESERVED8;
	volatile uint32_t CNT;
	volatile uint16_t PSC;
	uint16_t RESERVED9;
	volatile uint32_t ARR;
	volatile uint16_t RCR;
	uint16_t RESERVED10;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint16_t BDTR;
	uint16_t RESERVED11;
	volatile uint16_t DCR;
	uint16_t RESERVED12;
	volatile uint16_t DMAR;
	uint16_t RESERVED13;
	volatile uint16_t OR;
	uint16_t RESERVED14;
};



struct GPIO_TypeDef
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint16_t BSRRL;
	volatile uint16_t BSRRH;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
};



typedef struct __unaligned __declspec(align(1)) CommSt
{
	char field_0;
	char field_1;
	unsigned __int8 field_2;
	char field_3;
	char USARTBadurateCaseVal_RCCSetFlag;
	char field_5;
	char field_6;
	char ReStartFlag0400;
	char field_8;
	char field_9;
	unsigned __int8 field_A;
	char field_B;
	char field_C;
	char field_D;
	char field_E;
	char field_F;
	__int16 field_10;
	__int16 field_12;
	unsigned int field_14;
	int field_18;
	char field_1C;
	char field_1D;
	unsigned __int16 Cnt;
	int Len;
	char BlueThData[12];
	int field_30[52];
	char field_100[528];
	char field_310[16];
	char field_320[704];
	int field_5E0;
	void(**field_5E4)(void);
	int field_5E8;
	unsigned __int16 *field_5EC;
	char field_5F0[1218];
	int field_AB2;
	char field_AB6[74];
	char field_B00[1332];
	int DataLen;
	char SendToPhoneData[16];
	char field_1048[3052];
	int BlueThNum;
	unsigned __int8 BlueThToPhoneData[96];
	void(__fastcall *field_1C98)(St20000000 *);
	int field_1C9C;
	int field_1CA0;
	int field_1CA4;
	int field_1CA8;
	int field_1CAC;
	int field_1CB0;
	void(__fastcall *field_1CB4)(St20000000 *, int *, int);
	void(__fastcall *SendDataToPhonesub_8040CAE)(St20000000 *, unsigned __int8 **, unsigned __int8 **, int);
	int field_1CBC;
	int field_1CC0;
	int field_1CC4;
	int(__fastcall *field_1CC8)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *field_1CCC)(St20000000 *, unsigned __int8 *, int);
	int(__fastcall *field_1CD0)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *field_1CD4)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *field_1CD8)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *field_1CDC)(St20000000 *, unsigned __int8 *, int);
	int(__fastcall *return_0_sub_8041582_1CE0)();
	int field_1CE4;
	int field_1CE8;
	int field_1CEC;
	int field_1CF0;
	int field_1CF4;
	int field_1CF8;
	int field_1CFC;
	int field_1D00;
	int field_1D04;
	char field_1D08[832];
	__int16 field_2048;
	char field_204A[32];
	int field_206A;
	int field_206E;
	char field_2072[34];
	int field_2094;
	void(__cdecl *sub_8002042)(CommSt *token);
	void(__fastcall *field_209C)(_DWORD);
	void(__fastcall *field_20A0)(CommSt *);
	int(__fastcall *sub_8001CE6)(CommSt *);
	int field_20A8;
	void(__fastcall *sub_800214A)(_DWORD, _DWORD, _DWORD);
	int(__fastcall *UsartSendData_sub_8002422)(CommSt *, char *, unsigned int SendLen);
	void(__fastcall *SendData_sub_800258C)(CommSt *, unsigned __int8 *, int);
	void(__fastcall *sub_800249E)(CommSt *, int **, int *, int);
	void(__fastcall *field_20BC)(CommSt *);
	void(__cdecl *Set_IT_sub_8002358_20C0)(CommSt *token, int a2);
	void(__fastcall *sub_800238C)(CommSt *);
	int(__fastcall *Pos7_Case21_KeilStartFirst_sub_80025A2)(CommSt *, unsigned __int8 *, _DWORD);
	int(__fastcall *ID22sub_8002712)(CommSt *, unsigned __int8 *, int);
	int(__fastcall *ID23_sub_8002730)(CommSt *, unsigned __int8 *, _DWORD);
	int(__fastcall *ID24_sub_80027C0)(CommSt *, unsigned __int8 *, _DWORD);
	int(__fastcall *ID25_sub_80029D4)(CommSt *, unsigned __int8 *, _DWORD);
	int(__fastcall *ID26_sub_8002980)(CommSt *, unsigned __int8 *, _DWORD);
	int(__fastcall *Return_0_sub_80028FA)(CommSt *, unsigned __int8 *, _DWORD);
	int field_20E4;
	int field_20E8[67];
	void *field_21F4[15];
	int field_2230;
	int field_2234[21];
	int field_2288;
	int field_228C[6];
	unsigned __int8 *field_22A4;
	int field_22A8;
	int field_22AC;
	int field_22B0;
	int field_22B4;
	int field_22B8;
	int field_22BC;
	void(*field_22C0)(void);
	char field_22C4[20];
	char field_22D8;
	char field_22D9;
	int field_22DA;
	char field_22DE[50];
	char field_2310;
	char field_2311;
	char field_2312;
	char field_2313;
	unsigned int field_2314;
	int field_2318;
	void(__fastcall *field_231C)(St373C *, _DWORD);
	int field_2320;
	int field_2324;
	int field_2328;
	int field_232C;
	int field_2330;
	int field_2334;
	int field_2338;
	int field_233C;
	int field_2340;
	int field_2344;
	int field_2348;
	int field_234C;
	int field_2350;
	int field_2354;
	int field_2358[16];
	int field_2398[32];
	int field_2418[4];
	int field_2428;
	int field_242C[27];
	int field_2498[86];
	int field_25F0[40];
	int field_2690[10];
	int field_26B8[20];
	int field_2708;
	int field_270C;
	int field_2710;
	int field_2714;
	int field_2718;
	int field_271C;
	int field_2720;
	int field_2724;
	int field_2728;
	int field_272C[21];
	int field_2780[6];
	int field_2798[745];
	St373C field_333C;
	char field_392C[560];
	unsigned int field_3B5C;
	int field_3B60;
	unsigned int field_3B64;
	int field_3B68;
	unsigned int *field_3B6C;
	unsigned int *field_3B70;
	unsigned int *field_3B74;
	int field_3B78;
	int field_3B7C;
	int field_3B80;
	unsigned int field_3B84[2];
	unsigned int *field_3B8C[67];
	void(__fastcall *sub_80407AC)(St20000000 *);
	int field_3C9C;
	void(__fastcall *sub_80407FA)();
	int(__fastcall *sub_8040410)(St20000000 *);
	int field_3CA8;
	int field_3CAC;
	void(__fastcall *SendDataByUsart_sub_8040C30)(St20000000 *, unsigned __int8 *, int);
	void(__fastcall *SendDataToPhone_sub_8040D9C)(St20000000 *, unsigned __int8 *, int);
	void(__fastcall *field_3CB8)(St20000000 *, unsigned __int8 **, unsigned __int8 **, int);
	int field_3CBC;
	void(__fastcall *SetTIMUSART_sub_8040A9E)(St20000000 *, _DWORD);
	void(__fastcall *sub_8040AD2)(St20000000 *);
	int(__fastcall *Pos7_case21sub_8040DB2)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *ID22_sub_8040FC8)(St20000000 *, unsigned __int8 *, int);
	int(__fastcall *ID23_sub_80410B0)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *ID24_sub_8041130)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *Pos7_case25_sub_80416EC)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *ID26_sub_8041608)(St20000000 *, unsigned __int8 *, _DWORD);
	int(__fastcall *field_3CE0)();
	int field_3CE4;
	char field_3CE8[68];
	char field_3D2C[504];
	int field_3F24;
	__int16 field_3F28;
	__int16 field_3F2A;
	int field_3F2C[7];
	int field_3F48;
	int field_3F4C;
	int field_3F50;
	int field_3F54;
	int field_3F58;
	int field_3F5C;
	int field_3F60;
	int field_3F64;
	int field_3F68;
	int field_3F6C;
	int field_3F70;
	int field_3F74;
	__int16 field_3F78;
	unsigned __int16 field_3F7A;
	unsigned __int8 field_3F7C;
	char field_3F7D;
	unsigned __int8 field_3F7E;
	char field_3F7F[3];
	char field_3F82;
	int field_3F83;
	char field_3F87;
	int field_3F88;
	char field_3F8C;
	char field_3F8D;
	char field_3F8E;
	char field_3F8F[89];
	int field_3FE8;
	int field_3FEC;
	int field_3FF0;
	int field_3FF4;
	int field_3FF8;
	char field_3FFC[132];
	int field_4080;
	char field_4084;
	char field_4085;
	char field_4086;
	char field_4087;
	char field_4088;
	char field_4089;
	char field_408A;
	char field_408B;
	char field_408C;
	char field_408D;
	char field_408E;
	char field_408F;
	char field_4090;
	char field_4091;
	char field_4092;
	unsigned __int8 field_4093;
	char field_4094;
	char field_4095;
	char field_4096[10];
	void(__fastcall *field_40A0)(CommSt *);
	int field_40A4;
	int field_40A8;
	int field_40AC;
	int field_40B0;
	void(__fastcall *field_40B4)(CommSt *, void *, int);
	void(__fastcall *field_40B8)(CommSt *, unsigned __int8 *, unsigned __int8 *, int);
	int field_40BC[106];
	int field_4264[24];
	unsigned int DelayTM;
	char field_42C8;
	char field_42C9;
	char field_42CA;
	char field_42CB;
	int WhileFlag_field_42CC;
	char field_42D0;
	char field_42D1;
	char field_42D2[31];
	int field_42F1[4];
	__int16 field_4301;
	char field_4303;
	unsigned __int8 field_4304;
	char field_4305;
	char field_4306;
	char field_4307;
	char field_4308;
	char field_4309[203];
	int field_43D4[58];
	TIM_TypeDef *field_44BC[29];
	int field_4530;
	void *CanBaseArr[2];
	GPIO_TypeDef *GPIOxArr[10];
	COM_PORTMODE SC_com_portMode;
	int DelayTime;
	int field_4578;
	int field_457C;
	unsigned __int8 field_4580;
	char field_4581;
	char field_4582;
	char field_4583;
	char field_4584;
	char field_4585;
	__int16 field_4586;
	int field_4588;
	int field_458C;
	char field_4590;
	char field_4591;
	__int16 field_4592;
	char field_4594[48];
	TIM_TypeDef *field_45C4[6];
	CMPHY_Relay SC_RelayState;
	char field_45E5;
	char field_45E6;
	char field_45E7[29];
	int field_4604;
	int field_4608;
	int field_460C;
	unsigned __int8 *field_4610;
	int field_4614;
	int field_4618;
	int field_461C;
	int field_4620;
	int field_4624;
	int field_4628;
	char field_462C;
	char field_462D;
	char field_462E[10450];
	char field_6F00;
};

typedef struct __unaligned __declspec(align(1)) St20000000
{
	char field_0;
	char field_1;
	char field_2;
	char field_3;
	char UsartBadurate;
	char field_5;
	char field_6;
	char ReStartFlag;
	char field_8;
	char field_9;
	unsigned __int8 field_A;
	char field_B;
	char DataValidLen;
	char field_D;
	char field_E;
	char field_F;
	__int16 field_10;
	__int16 field_12;
	int field_14;
	int field_18;
	char field_1C;
	char field_1D;
	unsigned __int16 field_1E;
	__int16 BlueThPos;
	unsigned __int8 BoxBlueData[990];
	CommSt field_400;
	char field_7301[8192];
	char field_9301[94139];
	char field_202BC;
}St20000000;










