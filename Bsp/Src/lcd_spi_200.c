#include "lcd_spi_200.h"
#include "spi.h"
#include <stdio.h>
#define  LCD_SPI hspi1
static pFONT *LCD_AsciiFonts; 	// Store ASCII font
uint16_t  LCD_Buff[1024];

/* Forward declarations */
void LCD_WriteCommand(uint8_t lcd_command);
void LCD_WriteData_8bit(uint8_t lcd_data);
void LCD_WriteData_16bit(uint16_t lcd_data);
void LCD_WriteBuff(uint16_t *pBuff, uint16_t len);

struct
{
	uint32_t Color;
	uint32_t BackColor;
   uint8_t  ShowNum_Mode;
	uint8_t  Direction;
   uint16_t Width;
   uint16_t Height;
   uint8_t  X_Offset;
   uint8_t  Y_Offset;
}LCD;

/*初始化lcd*/
void SPI_LCD_Init(void)
{
   __HAL_SPI_ENABLE(&hspi1);


   HAL_Delay(10); 	// Delay ms

	LCD_CS_L; 	// CS low

 	LCD_WriteCommand(0x36);
	LCD_WriteData_8bit(0x00);

	LCD_WriteCommand(0x3A);
	LCD_WriteData_8bit(0x05);


 	LCD_WriteCommand(0xB2);			
	LCD_WriteData_8bit(0x0C);
	LCD_WriteData_8bit(0x0C); 
	LCD_WriteData_8bit(0x00); 
	LCD_WriteData_8bit(0x33); 
	LCD_WriteData_8bit(0x33); 			

	LCD_WriteCommand(0xB7);		   
	LCD_WriteData_8bit(0x35);

	LCD_WriteCommand(0xBB);

	LCD_WriteCommand(0xC0);
	LCD_WriteData_8bit(0x2C);

	LCD_WriteCommand(0xC2);
	LCD_WriteData_8bit(0x01);

	LCD_WriteCommand(0xC3);
	LCD_WriteData_8bit(0x12);
				
	LCD_WriteCommand(0xC4);
	LCD_WriteData_8bit(0x20);

	LCD_WriteCommand(0xC6);
	LCD_WriteData_8bit(0x0F);

	LCD_WriteCommand(0xD0);
	LCD_WriteData_8bit(0xA4);
	LCD_WriteData_8bit(0xA1);

	LCD_WriteCommand(0xE0);
	LCD_WriteData_8bit(0xD0);
	LCD_WriteData_8bit(0x04);
	LCD_WriteData_8bit(0x0D);
	LCD_WriteData_8bit(0x11);
	LCD_WriteData_8bit(0x13);
	LCD_WriteData_8bit(0x2B);
	LCD_WriteData_8bit(0x3F);
	LCD_WriteData_8bit(0x54);
	LCD_WriteData_8bit(0x4C);
	LCD_WriteData_8bit(0x18);
	LCD_WriteData_8bit(0x0D);
	LCD_WriteData_8bit(0x0B);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x23);

	LCD_WriteCommand(0xE1);
	LCD_WriteData_8bit(0xD0);
	LCD_WriteData_8bit(0x04);
	LCD_WriteData_8bit(0x0C);
	LCD_WriteData_8bit(0x11);
	LCD_WriteData_8bit(0x13);
	LCD_WriteData_8bit(0x2C);
	LCD_WriteData_8bit(0x3F);
	LCD_WriteData_8bit(0x44);
	LCD_WriteData_8bit(0x51);
	LCD_WriteData_8bit(0x2F);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x1F);
	LCD_WriteData_8bit(0x20);
	LCD_WriteData_8bit(0x23);

	LCD_WriteCommand(0x21);


	LCD_WriteCommand(0x11);
   HAL_Delay(120); 	// Delay ms


	LCD_WriteCommand(0x29);

	while( (LCD_SPI.Instance->SR & 0x0080) != RESET); 	// Wait TX idle
	LCD_CS_H; 	// CS high


   LCD_SetDirection(Direction_H_Flip);
   LCD_SetBackColor(LCD_BLACK);
   LCD_SetColor(LCD_WHITE);
   LCD_Clear();

   LCD_SetAsciiFont(&ASCII_Font24);
   LCD_ShowNumMode(Fill_Zero);


   LCD_Backlight_ON;
	
}
/* Write 8-bit command to LCD */
void  LCD_WriteCommand(uint8_t lcd_command)
{
	while((LCD_SPI.Instance->SR & 0x0080) != RESET); 	// Wait TX idle
	LCD_DC_Command; 	// DC low (cmd)
	(&LCD_SPI)->Instance->DR = lcd_command; 	// SPI data
	while( (LCD_SPI.Instance->SR & 0x0002) == 0); 	// Wait SPI ready
	while( (LCD_SPI.Instance->SR & 0x0080) != RESET); 	// Wait TX idle
   
	LCD_DC_Data; 	// DC high (data)
}


/* Write 8-bit data to LCD */
void  LCD_WriteData_8bit(uint8_t lcd_data)
{
	LCD_SPI.Instance->DR = lcd_data; 	// SPI data
	while( (LCD_SPI.Instance->SR & 0x0002) == 0); 	// Wait SPI ready
   
}

void LCD_SetColor(uint32_t Color)
{
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0; 	// B component

	Red_Value   = (uint16_t)((Color&0x00F80000)>>8); 	// R component
	Green_Value = (uint16_t)((Color&0x0000FC00)>>5);
	Blue_Value  = (uint16_t)((Color&0x000000F8)>>3);

	LCD.Color = (uint16_t)(Red_Value | Green_Value | Blue_Value); 	// B component
}
void LCD_SetBackColor(uint32_t Color)
{
	uint16_t Red_Value = 0, Green_Value = 0, Blue_Value = 0; 	// B component

	Red_Value   = (uint16_t)((Color&0x00F80000)>>8); 	// R component
	Green_Value = (uint16_t)((Color&0x0000FC00)>>5);
	Blue_Value  = (uint16_t)((Color&0x000000F8)>>3);

	LCD.BackColor = (uint16_t)(Red_Value | Green_Value | Blue_Value); 	// B component
}
/* Set display orientation 选择显示方向*/
void LCD_SetDirection(uint8_t direction)
{
	LCD.Direction = direction; 	// Set direction

	LCD_CS_L; 	// CS low
			
   if( direction == Direction_H )
   {
      LCD_WriteCommand(0x36);
      LCD_WriteData_8bit(0x70);
      LCD.X_Offset   = 0;
      LCD.Y_Offset   = 0;   
      LCD.Width      = LCD_Height; 	// Update width
      LCD.Height     = LCD_Width;		
   }
   else if( direction == Direction_V )
   {
      LCD_WriteCommand(0x36);
      LCD_WriteData_8bit(0x00);
      LCD.X_Offset   = 0;
      LCD.Y_Offset   = 0;     
      LCD.Width      = LCD_Width; 	// Update width
      LCD.Height     = LCD_Height;						
   }
   else if( direction == Direction_H_Flip )
   {
      LCD_WriteCommand(0x36);
      LCD_WriteData_8bit(0xA0);
      LCD.X_Offset   = 0;
      LCD.Y_Offset   = 0;      
      LCD.Width      = LCD_Height; 	// Update width
      LCD.Height     = LCD_Width;				
   }
   else if( direction == Direction_V_Flip )
   {
      LCD_WriteCommand(0x36);
      LCD_WriteData_8bit(0xC0);
      LCD.X_Offset   = 0;
      LCD.Y_Offset   = 0;     
      LCD.Width      = LCD_Width; 	// Update width
      LCD.Height     = LCD_Height;				
   }   
	while( (LCD_SPI.Instance->SR & 0x0080) != RESET); 	// Wait TX idle
	LCD_CS_H; 	// CS high
}




/* Select ASCII font from lcd_fonts.c 选择字体*/
void LCD_SetAsciiFont(pFONT *Asciifonts)
{
  LCD_AsciiFonts = Asciifonts;
}




/* Clear screen with current color清屏 */
void LCD_Clear(void)
{
	uint32_t i;

	LCD_SetAddress(0,0,LCD.Width-1,LCD.Height-1); 	// Update height

   LCD_SPI.Instance->CR1 &= 0xFFBF; 	// Disable SPI
   LCD_SPI.Instance->CR1 |= 0x0800; 	// 16-bit mode
   LCD_SPI.Instance->CR1 |= 0x0040; 	// Enable SPI
	
	LCD_CS_L; 	// CS low
	
	for(i=0;i<LCD.Width*LCD.Height;i++)				
	{

		LCD_SPI.Instance->DR = LCD.BackColor;
	   while( (LCD_SPI.Instance->SR & 0x0002) == 0); 	// Wait SPI ready
	}
	while( (LCD_SPI.Instance->SR & 0x0080) != RESET); 	// Wait TX idle
	LCD_CS_H; 	// CS high
	
	LCD_SPI.Instance->CR1 &= 0xFFBF; 	// Disable SPI
   LCD_SPI.Instance->CR1 &= 0xF7FF; 	// 8-bit mode
   LCD_SPI.Instance->CR1 |= 0x0040; 	// Enable SPI
}




void LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	uint16_t i;

   LCD_SetAddress( x, y, x+width-1, y+height-1); 	// Set draw area

   LCD_SPI.Instance->CR1 &= 0xFFBF; 	// Disable SPI
   LCD_SPI.Instance->CR1 |= 0x0800; 	// 16-bit mode
   LCD_SPI.Instance->CR1 |= 0x0040; 	// Enable SPI
	
	LCD_CS_L; 	// CS low
	
	for(i=0;i<width*height;i++)				
	{

		LCD_SPI.Instance->DR = LCD.BackColor;
	   while( (LCD_SPI.Instance->SR & 0x0002) == 0); 	// Wait SPI ready
	}
	while( (LCD_SPI.Instance->SR & 0x0080) != RESET); 	// Wait TX idle
	LCD_CS_H; 	// CS high
	
	LCD_SPI.Instance->CR1 &= 0xFFBF; 	// Disable SPI
   LCD_SPI.Instance->CR1 &= 0xF7FF; 	// 8-bit mode
   LCD_SPI.Instance->CR1 |= 0x0040; 	// Enable SPI
}
void LCD_ShowNumMode(uint8_t mode)
{
	LCD.ShowNum_Mode = mode;
}
/* Show integer at (x,y) 显示整数*/
void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number, uint8_t len) 
{  
	char   Number_Buffer[15]; 	// String buffer

	if( LCD.ShowNum_Mode == Fill_Zero) 	// Set fill mode
	{
		sprintf( Number_Buffer , "%0.*d",len, number ); 	// String buffer
	}
	else
	{	
		sprintf( Number_Buffer , "%*d",len, number ); 	// String buffer
	}
	
	LCD_DisplayString( x, y,(char *)Number_Buffer) ; 	// String buffer
	
}



/* Show decimal at (x,y)显示小数 */
void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double decimals, uint8_t len, uint8_t decs) 
{  
	char  Number_Buffer[20]; 	// String buffer
	
	if( LCD.ShowNum_Mode == Fill_Zero) 	// Set fill mode
	{
		sprintf( Number_Buffer , "%0*.*lf",len,decs, decimals ); 	// String buffer
	}
	else
	{
		sprintf( Number_Buffer , "%*.*lf",len,decs, decimals ); 	// String buffer
	}
	
	LCD_DisplayString( x, y,(char *)Number_Buffer) ; 	// String buffer
}
/* Show one ASCII character 显示单个字符*/
void LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c)
{
	uint16_t  index = 0, counter = 0 ,i = 0, w = 0; 	// Index
   uint8_t   disChar; 	// Font byte

	c = c - 32;
	
	LCD_CS_L; 	// CS low


	for(index = 0; index < LCD_AsciiFonts->Sizes; index++)	
	{
		disChar = LCD_AsciiFonts->pTable[c*LCD_AsciiFonts->Sizes + index]; 	// Font byte
		for(counter = 0; counter < 8; counter++)
		{ 
			if(disChar & 0x01)	
			{		
            LCD_Buff[i] =  LCD.Color; 	// Foreground color
			}
			else		
			{		
            LCD_Buff[i] = LCD.BackColor; 	// Background color
			}
			disChar >>= 1;
			i++;
         w++;
 			if( w == LCD_AsciiFonts->Width ) 	// Store ASCII font
			{
				w = 0;
				break;
			}        
		}	
	}		
   LCD_SetAddress( x, y, x+LCD_AsciiFonts->Width-1, y+LCD_AsciiFonts->Height-1); 	// Store ASCII font
   LCD_WriteBuff(LCD_Buff,LCD_AsciiFonts->Width*LCD_AsciiFonts->Height); 	// Write buffer
}


/* Show ASCII string */
void LCD_DisplayString( uint16_t x, uint16_t y, char *p) 
{  
	while ((x < LCD.Width) && (*p != 0)) 	// Update width
	{
		 LCD_DisplayChar( x,y,*p);
		 x += LCD_AsciiFonts->Width; 	// Store ASCII font
		 p++;
	}
}
/* Set draw window coordinates 设置绘制窗口*/
void LCD_SetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)		
{
	LCD_CS_L; 	// CS low
	
	LCD_WriteCommand(0x2a);
	LCD_WriteData_16bit(x1+LCD.X_Offset);
	LCD_WriteData_16bit(x2+LCD.X_Offset);

	LCD_WriteCommand(0x2b);
	LCD_WriteData_16bit(y1+LCD.Y_Offset);
	LCD_WriteData_16bit(y2+LCD.Y_Offset);

	LCD_WriteCommand(0x2c);
	
	while( (LCD_SPI.Instance->SR & 0x0080) != RESET); 	// Wait TX idle
	LCD_CS_H; 	// CS high
}

/* Write 16-bit data to LCD */
void  LCD_WriteData_16bit(uint16_t lcd_data)
{
	LCD_SPI.Instance->DR = lcd_data>>8; 	// SPI data
	while( (LCD_SPI.Instance->SR & 0x0002) == 0); 	// Wait SPI ready
	LCD_SPI.Instance->DR = lcd_data; 	// SPI data
	while( (LCD_SPI.Instance->SR & 0x0002) == 0); 	// Wait SPI ready
}

/* Write data buffer to LCD RAM */
void  LCD_WriteBuff(uint16_t *DataBuff, uint16_t DataSize)
{
	uint32_t i;

   LCD_SPI.Instance->CR1 &= 0xFFBF; 	// Disable SPI
   LCD_SPI.Instance->CR1 |= 0x0800; 	// 16-bit mode
   LCD_SPI.Instance->CR1 |= 0x0040; 	// Enable SPI

	LCD_CS_L; 	// CS low

	for(i=0;i<DataSize;i++)
	{
		LCD_SPI.Instance->DR = DataBuff[i];
	   while( (LCD_SPI.Instance->SR & 0x0002) == 0); 	// Wait SPI ready
	}
	while( (LCD_SPI.Instance->SR & 0x0080) != RESET); 	// Wait TX idle
	LCD_CS_H; 	// CS high

	LCD_SPI.Instance->CR1 &= 0xFFBF; 	// Disable SPI
   LCD_SPI.Instance->CR1 &= 0xF7FF; 	// 8-bit mode
   LCD_SPI.Instance->CR1 |= 0x0040; 	// Enable SPI
}
