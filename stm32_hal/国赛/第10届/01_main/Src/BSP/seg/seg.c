#include "seg\seg.h"

uint8_t Seg[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00};

void Seg_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);
	
	GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	
}

void Seg_Display_Value(uint8_t Bit1, uint8_t Bit2, uint8_t Bit3)
{
	uint8_t Temp = 0;
	uint8_t	i = 0;
	
	SCK_L;
	RCK_L;
	
	Temp = Seg[Bit3];
	for(i = 0; i < 8; i++)
	{
		if(Temp & (0x80 >> i))
			SER_H;		
		else
			SER_L;

		
		SCK_H;
		SCK_L;
	}
	
	Temp = Seg[Bit2];
	for(i = 0; i < 8; i++)
	{
		if(Temp & (0x80 >> i))
		{
			SER_H;		
		}
		else
		{
			SER_L;
		}
		
		SCK_H;
		SCK_L;
	}
	
	Temp = Seg[Bit1];
	for(i = 0; i < 8; i++)
	{
		if(Temp & (0x80 >> i))
		{
			SER_H;		
		}
		else
		{
			SER_L;
		}
	
		SCK_H;
		SCK_L;
	}
	
	RCK_H;
	
}
