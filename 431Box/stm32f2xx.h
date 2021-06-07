#pragma once
#include "stdafx.h"
#include "431Box.h"

#ifdef __cplusplus
#define     __I     volatile                /*!< defines 'read only' permissions      */
#else
#define     __I     volatile const          /*!< defines 'read only' permissions      */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

typedef struct CAN_TxMailBox_TypeDef
{
	__IO uint32_t TIR;  /*!< CAN TX mailbox identifier register */
	__IO uint32_t TDTR; /*!< CAN mailbox data length control and time stamp register */
	__IO uint32_t TDLR; /*!< CAN mailbox data low register */
	__IO uint32_t TDHR; /*!< CAN mailbox data high register */
} ;


typedef struct CAN_FIFOMailBox_TypeDef
{
	__IO uint32_t RIR;  /*!< CAN receive FIFO mailbox identifier register */
	__IO uint32_t RDTR; /*!< CAN receive FIFO mailbox data length control and time stamp register */
	__IO uint32_t RDLR; /*!< CAN receive FIFO mailbox data low register */
	__IO uint32_t RDHR; /*!< CAN receive FIFO mailbox data high register */
} ;

typedef struct
{
	__IO uint32_t FR1; /*!< CAN Filter bank register 1 */
	__IO uint32_t FR2; /*!< CAN Filter bank register 1 */
} CAN_FilterRegister_TypeDef;

typedef struct
{
	__IO uint32_t              MCR;                 /*!< CAN master control register,         Address offset: 0x00          */
	__IO uint32_t              MSR;                 /*!< CAN master status register,          Address offset: 0x04          */
	__IO uint32_t              TSR;                 /*!< CAN transmit status register,        Address offset: 0x08          */
	__IO uint32_t              RF0R;                /*!< CAN receive FIFO 0 register,         Address offset: 0x0C          */
	__IO uint32_t              RF1R;                /*!< CAN receive FIFO 1 register,         Address offset: 0x10          */
	__IO uint32_t              IER;                 /*!< CAN interrupt enable register,       Address offset: 0x14          */
	__IO uint32_t              ESR;                 /*!< CAN error status register,           Address offset: 0x18          */
	__IO uint32_t              BTR;                 /*!< CAN bit timing register,             Address offset: 0x1C          */
	uint32_t                   RESERVED0[88];       /*!< Reserved, 0x020 - 0x17F                                            */
	CAN_TxMailBox_TypeDef      sTxMailBox[3];       /*!< CAN Tx MailBox,                      Address offset: 0x180 - 0x1AC */
	CAN_FIFOMailBox_TypeDef    sFIFOMailBox[2];     /*!< CAN FIFO MailBox,                    Address offset: 0x1B0 - 0x1CC */
	uint32_t                   RESERVED1[12];       /*!< Reserved, 0x1D0 - 0x1FF                                            */
	__IO uint32_t              FMR;                 /*!< CAN filter master register,          Address offset: 0x200         */
	__IO uint32_t              FM1R;                /*!< CAN filter mode register,            Address offset: 0x204         */
	uint32_t                   RESERVED2;           /*!< Reserved, 0x208                                                    */
	__IO uint32_t              FS1R;                /*!< CAN filter scale register,           Address offset: 0x20C         */
	uint32_t                   RESERVED3;           /*!< Reserved, 0x210                                                    */
	__IO uint32_t              FFA1R;               /*!< CAN filter FIFO assignment register, Address offset: 0x214         */
	uint32_t                   RESERVED4;           /*!< Reserved, 0x218                                                    */
	__IO uint32_t              FA1R;                /*!< CAN filter activation register,      Address offset: 0x21C         */
	uint32_t                   RESERVED5[8];        /*!< Reserved, 0x220-0x23F                                              */
	CAN_FilterRegister_TypeDef sFilterRegister[28]; /*!< CAN Filter Register,                 Address offset: 0x240-0x31C   */
} CAN_TypeDef;


typedef struct
{
	uint32_t USART_BaudRate;           

	uint16_t USART_WordLength;          

	uint16_t USART_StopBits;            

	uint16_t USART_Parity;             

	uint16_t USART_Mode;                

	uint16_t USART_HardwareFlowControl; 
} USART_InitTypeDef;


typedef struct
{
	__IO uint16_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
	uint16_t      RESERVED0;  /*!< Reserved, 0x02                                                */
	__IO uint16_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
	uint16_t      RESERVED1;  /*!< Reserved, 0x06                                                */
	__IO uint16_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
	uint16_t      RESERVED2;  /*!< Reserved, 0x0A                                                */
	__IO uint16_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
	uint16_t      RESERVED3;  /*!< Reserved, 0x0E                                                */
	__IO uint16_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
	uint16_t      RESERVED4;  /*!< Reserved, 0x12                                                */
	__IO uint16_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
	uint16_t      RESERVED5;  /*!< Reserved, 0x16                                                */
	__IO uint16_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
	uint16_t      RESERVED6;  /*!< Reserved, 0x1A                                                */
} USART_TypeDef;





typedef struct  
{
	uint16_t CAN_FilterIdHigh;
	uint16_t CAN_FilterIdLow;
	uint16_t CAN_FilterMaskIdHigh;
	uint16_t CAN_FilterMaskIdLow;
	uint16_t CAN_FilterFIFOAssignment;
	uint8_t CAN_FilterNumber;
	uint8_t CAN_FilterMode;
	uint8_t CAN_FilterScale;
	char CAN_FilterActivation;
}CAN_FilterInitTypeDef;

typedef struct 
{
	uint16_t CAN_Prescaler;
	uint8_t CAN_Mode;
	uint8_t CAN_SJW;
	uint8_t CAN_BS1;
	uint8_t CAN_BS2;
	char CAN_TTCM;
	char CAN_ABOM;
	char CAN_AWUM;
	char CAN_NART;
	char CAN_RFLM;
	char CAN_TXFP;
}CAN_InitTypeDef;



typedef struct
{
	uint16_t TIM_Prescaler;
	uint16_t TIM_CounterMode;
	uint32_t TIM_Period;
	uint16_t TIM_ClockDivision;
	uint8_t TIM_RepetitionCounter;
}TIM_TimeBaseInitTypeDef;







void CAN_DeInit_sub_80348F4(CAN_TypeDef *CANx);
void USART_Init_8033448(USART_TypeDef *USARTx, USART_InitTypeDef *USART_InitStruct);
void USART_Cmd_8033544(USART_TypeDef *USARTx, char NewState);
void USART_ClearFlag_80335E6(USART_TypeDef *USARTx, __int16 TIM_FLAG);
BOOL USART_GetFlagStatus_sub_80335C6(USART_TypeDef *USARTx, unsigned __int16 TIM_FLAG);
int USART_ReceiveData_sub_8033568(USART_TypeDef *USARTx);
int RCC_AHB1PeriphClockCmd_sub_8032BAE(int RCC_AHB1Periph, char NewState);
void GPIO_PinAFConfig_sub_8031304(GPIO_TypeDef *GPIOx, unsigned __int16 a2, unsigned __int8 a3);
void RCC_APB1PeriphClockCmd_sub_8032C08(int RCC_APB1Periph, char NewState);
void TIM_SetCounter_8032F42(TIM_TypeDef *TIMx, int a2);
void TIM_ClearFlag_80332DC(TIM_TypeDef *TIMx, __int16 TIM_FLAG);
void TIM_UpdateDisableConfig_8032F62(TIM_TypeDef *TIMx, char NewState);
BOOL TIM_GetFlagStatus_80332C4(TIM_TypeDef *TIMx, __int16 TIM_FLAG);
void GPIO_WriteBit_80312F6(GPIO_TypeDef *GPIOx, __int16 GPIO_Pin, char BitVal);
void USART_SendData_sub_8033560(USART_TypeDef *USARTx, __int16 Data);
void USART_ITConfig_sub_8033570(USART_TypeDef *USARTx, unsigned __int8 USART_IT, char NewState);
char CAN_Transmit_sub_8034BD8(CAN_TypeDef *CANx, CanRxMsg *CANRx);
char CAN_GetFlagStatus_sub_8034FA4(CAN_TypeDef *CANx, int CAN_FLAG);
char CAN_TransmitStatus_sub_8034CFE(CAN_TypeDef *CANx, unsigned __int8 TransmitMailbox);
void CAN_StructInit_sub_8034B64(CAN_InitTypeDef *CAN_InitStruct);
char CAN_Init_sub_803492C(CAN_TypeDef *CANx, CAN_InitTypeDef *CAN_InitStruct);
void TIM_TimeBaseInit_8032ED8(TIM_TypeDef *TIMx, TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct);
void CAN_FilterInit_sub_8034A50(CAN_FilterInitTypeDef *CAN_FilterInitStruct);
void CAN_OperatingModeRequest_sub_8034ED0(CAN_TypeDef *CANx, char a2);
uint8_t CAN_MessagePending_sub_8034EA4(CAN_TypeDef *CANx, char FIFONumber);
void CAN_ClearFlag_sub_8035020(CAN_TypeDef *CANx, int CAN_FLAG);
int CAN_Receive_sub_8034DA2(CAN_TypeDef *CANx, unsigned __int8 a2, CanRxMsg *RxMessage);