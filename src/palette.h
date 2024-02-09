/*
  @file palette.h

  General purpose HSV-based 256 color palette.

  by Miloslav Ciz (drummyfish), 2019

  Released under CC0 1.0 (https://creativecommons.org/publicdomain/zero/1.0/)
  plus a waiver of all other intellectual property. The goal of this work is
  be and remain completely in the public domain forever, available for any use
  whatsoever.
*/

#ifndef PALETTE_256_H
#define PALETTE_256_H

SFG_PROGRAM_MEMORY


uint16_t paletteRGB565[256] = {
0x0000, 0xE30C, 0x071E, 0x2D33, 0xB24C, 0xF75D, 0x5C77, 0xFF7F, 0x6304, 0xE70C, 0x8C19, 0x3022, 0xF52E, 0xB93B, 0x7E44, 0x7F55, 0xC304, 0x8811, 0x6C1A, 0x7127, 0x752C, 0x593D, 0x5E4E, 0x3F57, 0x0309, 0x070E, 0x2B1B, 0x4F24, 0x5335, 0x983E, 0xBC4F, 0xFF5F, 0x0209, 0x050E, 0x471B, 0x4A24, 0x4E2D, 0x713E, 0xB447, 0xF85F, 0x0109, 0x0416, 0x2623, 0x4934, 0x4C3D, 0x6E4E, 0xB15F, 0xF66F, 0x0211, 0x041E, 0x072F, 0x4944, 0x2D55, 0x6F66, 0xB27F, 0xF67F, 0x820C, 0x441D, 0x0632, 0xE842, 0xEC53, 0xCF64, 0xB27D, 0x967E, 0x410C, 0xE420, 0x8731, 0x2A42, 0xED52, 0xB067, 0x537C, 0x777D, 0x6310, 0xE620, 0x8B31, 0x2F42, 0xF356, 0xD767, 0x7B74, 0x9F7D, 0x6408, 0xE818, 0x8C25, 0x3036, 0xF546, 0xB953, 0x7E64, 0x7F75, 0x0500, 0x2900, 0x2D04, 0x3308, 0x7708, 0xFB10, 0x3F15, 0x5F2A, 0xA500, 0x4905, 0x2D0A, 0xF206, 0xB70B, 0x7B14, 0x5F15, 0xFF2D, 0x6301, 0x6702, 0x8B07, 0xCF04, 0xF30D, 0xF716, 0xFB17, 0xFD2F, 0x6001, 0x6202, 0x8307, 0xC30C, 0xE70D, 0xE916, 0xEB1F, 0xEE27, 0x6009, 0x600E, 0x8117, 0xA224, 0xE32D, 0xE536, 0xE33F, 0xE94F, 0x6015, 0x6026, 0x803B, 0xA24C, 0xC45D, 0xE36E, 0xE67F, 0xEB7F, 0x4014, 0xE024, 0x6235, 0xE249, 0xC45A, 0x416F, 0xE67F, 0xC97C, 0x2214, 0x2124, 0x4234, 0x6448, 0xC55C, 0x086D, 0x6A7D, 0x6D7E, 0x0314, 0x2724, 0x2B38, 0x8E4C, 0x935C, 0x366D, 0x7A7D, 0x7C7E, 0x0508, 0x2914, 0x2D20, 0x532C, 0x973C, 0xFB44, 0x3F55, 0x7F5E, 0x2500, 0x0900, 0x0D00, 0x3100, 0x1600, 0x5A00, 0x5E00, 0x3F00, 0x6500, 0xC900, 0x6D01, 0xF101, 0xB602, 0x3A03, 0xDE03, 0x7F04, 0x6401, 0x6802, 0x6C03, 0x8F04, 0xB405, 0xD806, 0xDC07, 0xFF07, 0x6201, 0x6102, 0x6303, 0x8504, 0xA605, 0xC606, 0xC907, 0xEC07, 0x6101, 0x6002, 0x6003, 0x8104, 0x8205, 0xA00E, 0xC007, 0xE00F, 0x6005, 0x601A, 0x6023, 0x802C, 0x803D, 0xA046, 0xC057, 0xE05F, 0xC014, 0x6025, 0x2036, 0xE046, 0xA05B, 0x8264, 0x607D, 0x047E, 0x0014, 0x0024, 0x2134, 0x4044, 0x6258, 0xA068, 0xC178, 0x407D, 0x0110, 0x0224, 0x0234, 0x0444, 0x4458, 0x0668, 0x0878, 0x497C, 0x0514, 0x2728, 0x0B34, 0x0F48, 0x1358, 0x1768, 0x1B78, 0x1E7C, 0x0504, 0x090C, 0x0D18, 0x1120, 0x1628, 0x3A34, 0x5E3C, 0x7F44
};

/** Adds value (brightness), possibly negative, to given color (represented by
  its palette index). If you know you'll only be either adding or substracting,
  use plusValue() or minusValue() functions, which should be faster. */
static inline uint8_t palette_addValue(uint8_t color, int8_t add)
{
  uint8_t newValue = color + add;
  
  if ((newValue >> 3) == (color >> 3))
    return newValue;
  else
    return add > 0 ? (color | 0x07) : 0;
}

/** Adds a positive value (brightness) to given color (represented by its
  palette index). This should be a little bit faster than addValue(). */
static inline uint8_t palette_plusValue(uint8_t color, uint8_t plus)
{
  uint8_t newValue = color + plus;
  return ((newValue >> 3) == (color >> 3)) ? newValue : (color | 0x07);
}

/** Substracts a positive value (brightness) from given color (represented by
  its palette index). This should be a little bit faster than addValue(). */
static inline uint8_t palette_minusValue(uint8_t color, uint8_t minus)
{
  uint8_t newValue = color - minus;
  return ((newValue >> 3) == (color >> 3)) ? newValue : 0;
}

#endif //guard