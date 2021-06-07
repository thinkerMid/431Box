#include "stdafx.h"
#include "stm32F2xx.h"
#include "431Box.h"


void CAN_DeInit_sub_80348F4(CAN_TypeDef *CANx)
{

}


void USART_Init_8033448(USART_TypeDef *USARTx, USART_InitTypeDef *USART_InitStruct)
{

}


void USART_Cmd_8033544(USART_TypeDef *USARTx, char NewState)
{
	
}

void USART_ClearFlag_80335E6(USART_TypeDef *USARTx, __int16 TIM_FLAG)
{
	USARTx->SR = ~TIM_FLAG;
}


BOOL USART_GetFlagStatus_sub_80335C6(USART_TypeDef *USARTx, unsigned __int16 TIM_FLAG)
{
	return (USARTx->SR & TIM_FLAG) != 0;
}


int USART_ReceiveData_sub_8033568(USART_TypeDef *USARTx)
{
	return USARTx->DR & 0x1FF;
}


int RCC_AHB1PeriphClockCmd_sub_8032BAE(int RCC_AHB1Periph, char NewState)
{
	return 1;
}


void GPIO_PinAFConfig_sub_8031304(GPIO_TypeDef *GPIOx, unsigned __int16 a2, unsigned __int8 a3)
{
	return;
}


void RCC_APB1PeriphClockCmd_sub_8032C08(int RCC_APB1Periph, char NewState)
{
	return;
}


void TIM_SetCounter_8032F42(TIM_TypeDef *TIMx, int a2)
{
	TIMx->CNT = a2;
}


void TIM_ClearFlag_80332DC(TIM_TypeDef *TIMx, __int16 TIM_FLAG)
{
	TIMx->SR = ~TIM_FLAG;
}


void TIM_UpdateDisableConfig_8032F62(TIM_TypeDef *TIMx, char NewState)
{
	if (NewState)
		TIMx->CR1 |= 1u;
	else
		TIMx->CR1 &= 0xFFFEu;
}


BOOL TIM_GetFlagStatus_80332C4(TIM_TypeDef *TIMx, __int16 TIM_FLAG)
{
	return 1;
}


void GPIO_WriteBit_80312F6(GPIO_TypeDef *GPIOx, __int16 GPIO_Pin, char BitVal)
{
	if (BitVal)
		GPIOx->BSRRL = GPIO_Pin;
	else
		GPIOx->BSRRH = GPIO_Pin;
}


void USART_SendData_sub_8033560(USART_TypeDef *USARTx, __int16 Data)
{
	USARTx->DR = Data & 0x1FF;
}


void USART_ITConfig_sub_8033570(USART_TypeDef *USARTx, unsigned __int8 USART_IT, char NewState)
{

}


char CAN_Transmit_sub_8034BD8(CAN_TypeDef *CANx, CanRxMsg *CANRx)
{
	char result; // r0

	if ((CANx->TSR & 0x4000000) != 0)
	{
		result = 0;
	}
	else if ((CANx->TSR & 0x8000000) != 0)
	{
		result = 1;
	}
	else if ((CANx->TSR & 0x10000000) != 0)
	{
		result = 2;
	}
	else
	{
		result = 4;
	}

	return result;
}


char CAN_GetFlagStatus_sub_8034FA4(CAN_TypeDef *CANx, int CAN_FLAG)
{
	if ((CAN_FLAG & 0xF00000) != 0)
		return (CANx->ESR & CAN_FLAG) << 0xC != 0;
	if ((CAN_FLAG & 0x1000000) != 0)
		return (CANx->MSR & CAN_FLAG) << 0xC != 0;
	if ((CAN_FLAG & 0x8000000) != 0)
		return (CANx->TSR & CAN_FLAG) << 0xC != 0;
	if ((CAN_FLAG & 0x2000000) != 0)
		return (CANx->RF0R & CAN_FLAG) << 0xC != 0;
	return (CANx->RF1R & CAN_FLAG) << 0xC != 0;
}


void CAN_ClearFlag_sub_8035020(CAN_TypeDef *CANx, int CAN_FLAG)
{

}






char CAN_TransmitStatus_sub_8034CFE(CAN_TypeDef *CANx, unsigned __int8 TransmitMailbox)
{
	uint32_t state; // r0

	if (TransmitMailbox)
	{
		if (TransmitMailbox == 2)
		{
			state = CANx->TSR & 0x10030000;
		}
		else if (TransmitMailbox >= 2u)
		{
			state = 0;
		}
		else
		{
			state = CANx->TSR & 0x8000300;
		}
	}
	else
	{
		state = CANx->TSR & 0x4000003;
	}
	switch (state)
	{
	case 0u:
		return 2;
	case 0x4000001u:
		return 0;
	case 0x4000003u:
		return 1;
	case 0x8000100u:
		return 0;
	case 0x8000300u:
		return 1;
	case 0x10010000u:
		return 0;
	}
	return state == 0x10030000;
}




void CAN_StructInit_sub_8034B64(CAN_InitTypeDef *CAN_InitStruct)
{

}


char CAN_Init_sub_803492C(CAN_TypeDef *CANx, CAN_InitTypeDef *CAN_InitStruct)
{
	return 0;
}


void TIM_TimeBaseInit_8032ED8(TIM_TypeDef *TIMx, TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct)
{

}



void CAN_FilterInit_sub_8034A50(CAN_FilterInitTypeDef *CAN_FilterInitStruct)
{

}



void CAN_OperatingModeRequest_sub_8034ED0(CAN_TypeDef *CANx, char a2)
{

}



uint8_t CAN_MessagePending_sub_8034EA4(CAN_TypeDef *CANx, char FIFONumber)
{
	return 1;
}


int CAN_Receive_sub_8034DA2(CAN_TypeDef *CANx, unsigned __int8 a2, CanRxMsg *RxMessage)
{
	return 1;
}