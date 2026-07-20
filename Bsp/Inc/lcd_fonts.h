#ifndef __FONTS_H
#define __FONTS_H

#include <stdint.h>

/* Font structure definition */
typedef struct _pFont
{    
	const uint8_t 		*pTable;  		// Font bitmap data pointer
	uint16_t 			Width; 		 	// Character width in pixels
	uint16_t 			Height; 			// Character height in pixels
	uint16_t 			Sizes;	 		// Data size per character (bytes)
	uint16_t				Table_Rows;		// Number of rows (for CJK font 2D array)
} pFONT;

/* CJK font declarations */
// extern	pFONT	CH_Font12 ;		// 12x12 CJK font
// extern	pFONT	CH_Font16 ;    // 16x16 CJK font
// extern	pFONT	CH_Font20 ;    // 20x20 CJK font
// extern	pFONT	CH_Font24 ;    // 24x24 CJK font
// extern	pFONT	CH_Font32 ;    // 32x32 CJK font

/* ASCII font declarations */
// extern pFONT ASCII_Font32;		// 32x16 ASCII font
extern pFONT ASCII_Font24;		// 24x12 ASCII font
// extern pFONT ASCII_Font20; 	// 20x10 ASCII font
extern pFONT ASCII_Font16; 	// 16x8 ASCII font
// extern pFONT ASCII_Font12; 	// 12x6 ASCII font

#endif 
