#ifndef __spi_lcd
#define __spi_lcd

#include "main.h"

#include "lcd_fonts.h"	// Font/image includes not required; can be removed

/* Display parameters */
#define LCD_Width     240		// LCD width in pixels
#define LCD_Height    320		// LCD height in pixels

/* Display orientation */
#define	Direction_H				0					// Landscape
#define	Direction_H_Flip	   1					// Landscape, flipped
#define	Direction_V				2					// Portrait
#define	Direction_V_Flip	   3					// Portrait, flipped

/* Number display: leading zero fill mode */
#define  Fill_Zero  0		// Fill with zeros (e.g. 123 -> 000123)
#define  Fill_Space 1		// Fill with spaces

/* Common colors (24-bit RGB888, auto-converted to 16-bit RGB565) */
#define 	LCD_WHITE       0xFFFFFF	 // White
#define 	LCD_BLACK       0x000000    // Black
#define 	LCD_BLUE        0x0000FF	 // Blue
#define 	LCD_GREEN       0x00FF00    // Green
#define 	LCD_RED         0xFF0000    // Red
#define 	LCD_CYAN        0x00FFFF    // Cyan
#define 	LCD_MAGENTA     0xFF00FF    // Magenta
#define 	LCD_YELLOW      0xFFFF00    // Yellow
#define 	LCD_GREY        0x2C2C2C    // Grey
#define 	LIGHT_BLUE      0x8080FF    // Light blue
#define 	LIGHT_GREEN     0x80FF80    // Light green
#define 	LIGHT_RED       0xFF8080    // Light red
#define 	LIGHT_CYAN      0x80FFFF    // Light cyan
#define 	LIGHT_MAGENTA   0xFF80FF    // Light magenta
#define 	LIGHT_YELLOW    0xFFFF80    // Light yellow
#define 	LIGHT_GREY      0xA3A3A3    // Light grey
#define 	DARK_BLUE       0x000080    // Dark blue
#define 	DARK_GREEN      0x008000    // Dark green
#define 	DARK_RED        0x800000    // Dark red
#define 	DARK_CYAN       0x008080    // Dark cyan
#define 	DARK_MAGENTA    0x800080    // Dark magenta
#define 	DARK_YELLOW     0x808000    // Dark yellow
#define 	DARK_GREY       0x404040    // Dark grey


/* Function prototypes */
void  SPI_LCD_Init(void);      // Init LCD and SPI
void  LCD_Clear(void);			 // Clear entire screen
void  LCD_ClearRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);	// Clear area

void  LCD_SetAddress(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);	// Set draw window
void  LCD_SetColor(uint32_t Color); 				   //	Set foreground color
void  LCD_SetBackColor(uint32_t Color);  				//	Set background color
void  LCD_SetDirection(uint8_t direction);  	      //	Set display orientation

//>>>>>	ASCII character display
void  LCD_SetAsciiFont(pFONT *fonts);										//	Select ASCII font
void 	LCD_DisplayChar(uint16_t x, uint16_t y,uint8_t c);				//	Display one ASCII char
void 	LCD_DisplayString( uint16_t x, uint16_t y, char *p);	 		//	Display ASCII string

//>>>>>	Mixed CJK + ASCII text display
void 	LCD_SetTextFont(pFONT *fonts);										// Set text font (CJK + ASCII)
void 	LCD_DisplayChinese(uint16_t x, uint16_t y, char *pText);		// Display one CJK char
void 	LCD_DisplayText(uint16_t x, uint16_t y, char *pText) ;		// Display mixed text

//>>>>>	Integer / decimal display
void  LCD_ShowNumMode(uint8_t mode);		// Set zero/space fill mode for numbers
void  LCD_DisplayNumber( uint16_t x, uint16_t y, int32_t number,uint8_t len) ;					// Display integer
void  LCD_DisplayDecimals( uint16_t x, uint16_t y, double number,uint8_t len,uint8_t decs);	// Display decimal

//>>>>>	2D drawing functions
void  LCD_DrawPoint(uint16_t x,uint16_t y,uint32_t color);   	// Draw pixel
void  LCD_DrawLine_V(uint16_t x, uint16_t y, uint16_t height);          // Draw vertical line
void  LCD_DrawLine_H(uint16_t x, uint16_t y, uint16_t width);           // Draw horizontal line
void  LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);	// Draw line between two points
void  LCD_DrawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			// Draw rectangle outline
void  LCD_DrawCircle(uint16_t x, uint16_t y, uint16_t r);									// Draw circle outline
void  LCD_DrawEllipse(int x, int y, int r1, int r2);											// Draw ellipse outline

//>>>>>	Filled shape functions
void  LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height);			// Fill rectangle
void  LCD_FillCircle(uint16_t x, uint16_t y, uint16_t r);									// Fill circle

// >>>>>	Monochrome image drawing
void 	LCD_DrawImage(uint16_t x,uint16_t y,uint16_t width,uint16_t height,const uint8_t *pImage);

/* Pin configuration macros */
#define 	LCD_SCK_PIN      		 GPIO_PIN_5									// SCK pin (SPI3 remap)
#define 	LCD_SCK_PORT     		 GPIOA                 					// SCK GPIO port
#define 	GPIO_LCD_SCK_CLK      __HAL_RCC_GPIOB_CLK_ENABLE()  		// SCK clock enable

#define 	LCD_SDA_PIN      		 GPIO_PIN_7									// SDA pin (SPI3 remap)
#define 	LCD_SDA_PORT    		 GPIOA                 					// SDA GPIO port
#define 	GPIO_LCD_SDA_CLK      __HAL_RCC_GPIOB_CLK_ENABLE()  		// SDA clock enable

#define 	LCD_CS_PIN       				GPIO_PIN_4						// CS pin (active low)
#define 	LCD_CS_PORT      				GPIOA                 			// CS GPIO port
#define 	GPIO_LCD_CS_CLK     			__HAL_RCC_GPIOA_CLK_ENABLE()	// CS clock enable

#define  LCD_DC_PIN						GPIO_PIN_8				         // Data/Command pin
#define	LCD_DC_PORT						GPIOA									// Data/Command port
#define 	GPIO_LCD_DC_CLK     			__HAL_RCC_GPIOD_CLK_ENABLE()	// Data/Command clock enable

#define  LCD_Backlight_PIN				GPIO_PIN_11				         // Backlight pin
#define	LCD_Backlight_PORT			GPIOA									// Backlight port
#define 	GPIO_LCD_Backlight_CLK     __HAL_RCC_GPIOD_CLK_ENABLE()	// Backlight clock enable

/* Control macros (register-level for speed) */
#define 	LCD_CS_H    		 	LCD_CS_PORT->BSRR  = LCD_CS_PIN							// CS high
#define 	LCD_CS_L     			LCD_CS_PORT->BSRR  = (uint32_t)LCD_CS_PIN << 16U	// CS low
#define	LCD_DC_Command		   HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET)	  		// DC low -> command
#define 	LCD_DC_Data		      HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET)				// DC high -> data
#define 	LCD_Backlight_ON      HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_SET)		// BL on (high)
#define 	LCD_Backlight_OFF  	 HAL_GPIO_WritePin(LCD_Backlight_PORT, LCD_Backlight_PIN, GPIO_PIN_RESET)	// BL off (low)

#endif //__spi_lcd
