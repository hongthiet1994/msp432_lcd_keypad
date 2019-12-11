#include "lcd.h"

const unsigned char font[][6] ={   //Font 5x7
  {0x00, 0x40, 0x60, 0x70, 0x60, 0x40}// mui ten len
  ,{0x00, 0x02, 0x06, 0x0e, 0x06, 0x02}// mui ten xuong
  ,{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 20
  ,{0x00, 0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
  ,{0x00, 0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
  ,{0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
  ,{0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
  ,{0x00, 0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
  ,{0x00, 0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
  ,{0x00, 0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
  ,{0x00, 0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
  ,{0x00, 0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
  ,{0x00, 0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
  ,{0x00, 0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
  ,{0x00, 0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
  ,{0x00, 0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
  ,{0x00, 0x00, 0x60, 0x60, 0x00, 0x00} // 2f .
  ,{0x00, 0x20, 0x10, 0x08, 0x04, 0x02} // 2e /
  ,{0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E} // 30 0
  ,{0x00, 0x00, 0x42, 0x7F, 0x40, 0x00} // 31 1
  ,{0x00, 0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
  ,{0x00, 0x21, 0x41, 0x45, 0x4B, 0x31} // 33 3
  ,{0x00, 0x18, 0x14, 0x12, 0x7F, 0x10} // 34 4
  ,{0x00, 0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
  ,{0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30} // 36 6
  ,{0x00, 0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
  ,{0x00, 0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
  ,{0x00, 0x06, 0x49, 0x49, 0x29, 0x1E} // 39 9
  ,{0x00, 0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
  ,{0x00, 0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
  ,{0x00, 0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
  ,{0x00, 0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
  ,{0x00, 0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
  ,{0x00, 0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
  ,{0x00, 0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
  ,{0x00, 0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
  ,{0x00, 0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
  ,{0x00, 0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
  ,{0x00, 0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
  ,{0x00, 0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
  ,{0x00, 0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
  ,{0x00, 0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
  ,{0x00, 0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
  ,{0x00, 0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
  ,{0x00, 0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
  ,{0x00, 0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
  ,{0x00, 0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
  ,{0x00, 0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
  ,{0x00, 0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
  ,{0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
  ,{0x00, 0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
  ,{0x00, 0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
  ,{0x00, 0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
  ,{0x00, 0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
  ,{0x00, 0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
  ,{0x00, 0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
  ,{0x00, 0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
  ,{0x00, 0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
  ,{0x00, 0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
  ,{0x00, 0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
  ,{0x00, 0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
  ,{0x00, 0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
  ,{0x00, 0x02, 0x04, 0x08, 0x10, 0x20} // 5c �
  ,{0x00, 0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
  ,{0x00, 0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
  ,{0x00, 0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
  ,{0x00, 0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
  ,{0x00, 0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
  ,{0x00, 0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
  ,{0x00, 0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
  ,{0x00, 0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
  ,{0x00, 0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
  ,{0x00, 0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
  ,{0x00, 0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
  ,{0x00, 0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
  ,{0x00, 0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
  ,{0x00, 0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
  ,{0x00, 0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
  ,{0x00, 0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
  ,{0x00, 0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
  ,{0x00, 0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
  ,{0x00, 0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
  ,{0x00, 0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
  ,{0x00, 0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
  ,{0x00, 0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
  ,{0x00, 0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
  ,{0x00, 0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
  ,{0x00, 0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
  ,{0x00, 0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
  ,{0x00, 0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
  ,{0x00, 0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
  ,{0x00, 0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
  ,{0x00, 0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
  ,{0x00, 0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
  ,{0x00, 0x00, 0x7e, 0x7e, 0x00, 0x00} // 7c |
  ,{0x00, 0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
  ,{0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18} // 7e ->
  ,{0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18} // 7f <-
  
};

char logo [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0x60, 0x30, 0x18,
  0x18, 0x0C, 0x04, 0x04, 0x06, 0x02, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03,
  0x03, 0x02, 0x02, 0x06, 0x06, 0x04, 0x0C, 0x18, 0x10, 0x30, 0x20, 0x60, 0xC0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x30, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0x60, 0x30, 0x18, 0x08, 0x04, 0x04, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x08,
  0x18, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xC0, 0x70, 0x0E, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xF0, 0x0F, 0x03, 0x06, 0x04, 0x08, 0xF0, 0x08, 0x0C, 0x06, 0x02, 0x02, 0x06, 0x0C, 0x08, 0xF0,
  0x08, 0x06, 0x03, 0x01, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x80, 0x40, 0x20, 0x10, 0x1F, 0x08, 0x0C, 0x04, 0x04, 0x04, 0x0C, 0x08, 0x98, 0x7F,
  0x00, 0x00, 0x00, 0x00, 0xC0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFC, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
  0x06, 0x06, 0xC6, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x06,
  0x06, 0x06, 0x06, 0x02, 0x00, 0x80, 0xC0, 0x70, 0x38, 0x1C, 0x0E, 0x06, 0x06, 0x06, 0x06, 0x06,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFE, 0x06, 0x06, 0x3E, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x1E, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x0E, 0x01, 0x00, 0x00, 0x00, 0xF0, 0x98, 0x04, 0x04, 0x06, 0x02, 0x82, 0xC1, 0xC0, 0x60,
  0x30, 0x10, 0x1C, 0x06, 0x3F, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x08, 0x20, 0x20, 0x20, 0x20,
  0x30, 0x30, 0x1F, 0x0F, 0x00, 0x80, 0x40, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,
  0x00, 0x00, 0x00, 0x0E, 0x87, 0x83, 0x81, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x78, 0x78, 0x78,
  0x78, 0x78, 0x58, 0x58, 0x58, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0x0E, 0xF0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x0F,
  0x38, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x0F, 0x78, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFC, 0xFC, 0xFC, 0xFE, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFC,
  0xFC, 0xF8, 0xFE, 0x01, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x38, 0x79, 0xFE, 0xFC, 0xF0, 0xC0, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xF8, 0xF8, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFC, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x0E, 0x10, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3F, 0x26, 0x22, 0x22, 0x22, 0x26, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0x0E, 0x08, 0x08, 0x08, 0x08, 0x0B, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07,
  0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07,
  0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x0E, 0x08, 0x18,
  0x10, 0x30, 0x20, 0x60, 0x40, 0x40, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0,
  0x40, 0x60, 0x60, 0x20, 0x30, 0x10, 0x18, 0x18, 0x0C, 0x06, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



const unsigned int  key1[4][4] ={{1,2,3,13}
,{4,5,6,14}
,{7,8,9,15}
,{11,10,12,16}};

const unsigned char     key2[10][5] =  {{'+','-','*','/','1'}
,{'A','B','C','|','2'}
,{'D','E','F','%','3'}
,{'G','H','I','(','4'}
,{'J','K','L',')','5'}
,{'M','N','O','@','6'}
,{'P','Q','R','S','7'}
,{'T','U','V',',','8'}
,{'W','X','Y','Z','9'}
,{'#','$','.','?','0'}};
const unsigned char     key3[10][5] =  {{'+','-','*','/','1'}
,{'a','b','c','|','2'}
,{'d','e','f','%','3'}
,{'g','h','i','(','4'}
,{'j','k','l',')','5'}
,{'m','n','o','@','6'}
,{'p','q','r','s','7'}
,{'t','u','v',',','8'}
,{'w','x','y','z','9'}
,{'#','$','.','?','0'}};

void delay(uint32_t t)
{
  for(uint32_t i =0;i<10000;i++)
  {
    for(uint32_t j=0;j<t;j++);
  }
}

time_t getsec(RTC_C_Calendar x)
{
  struct tm t;
  t.tm_year = x.year - 1970;
  t.tm_mon = x.month;
  t.tm_mday = x.dayOfmonth;
  t.tm_hour = x.hours;
  t.tm_min = x.minutes;
  t.tm_sec = x.seconds;
  t.tm_isdst = -1;
  return mktime(&t);
}
void lcd_init(void)
{
  
  GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0 + GPIO_PIN2 + GPIO_PIN4 + GPIO_PIN5 );
  GPIO_setAsOutputPin(GPIO_PORT_P2, RST );
  GPIO_setOutputLowOnPin(GPIO_PORT_P2, RST);
  GPIO_setOutputHighOnPin(GPIO_PORT_P2, RST);
  lcd_write(0,0xE2); 
  lcd_write(0,0xAF); 
  lcd_write(0,0x2F);  
  
}
void keybad_init()
{
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P6, GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7 );
  GPIO_interruptEdgeSelect(GPIO_PORT_P6, GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7 ,
                           GPIO_HIGH_TO_LOW_TRANSITION);
  GPIO_clearInterruptFlag(GPIO_PORT_P6, GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7);
  GPIO_enableInterrupt(GPIO_PORT_P6, GPIO_PIN4 + GPIO_PIN5 + GPIO_PIN6 + GPIO_PIN7);
  
  GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0+GPIO_PIN1+GPIO_PIN4+GPIO_PIN5);
  GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN7);
  
  OUTPUT_LOW(GPIO_PORT_P5,GPIO_PIN0+GPIO_PIN1+GPIO_PIN4+GPIO_PIN5);
  OUTPUT_LOW(GPIO_PORT_P7,GPIO_PIN7);
  Interrupt_enableInterrupt(INT_PORT6);
  
}
/*
// function to print the screen one character
// @param:   data is ASCII code
//              form 30 - 7f
// @param:   color is Choose black or white 
//              - 0 : black
//              - 1 : white
// return NULL
*/
void lcd_putc(uint16_t data,bool color)
{
  
  uint8_t v;
  if((data >= 0x1E) && (data <= 0x7f))
  {
    data=data-30;
    for(v=0;v<6;v++)
    {
      if(color)
      {
        lcd_write(1, font[data][v]);
      }
      else
      {
        lcd_write(1, ~font[data][v]);
      }
    }
  }
}
/*
// function to delete the screen according to the selected size
// @param : x1 is column start
// @param : x2 is column ends
//          - 0 <= x1,x2 <= 20;
// @param : y1 is row start
// @param : y2 is column ends
//          - 0 <= y1,y2 <= 7;
// return NULL
*/
void lcd_clear(uint8_t x1,uint8_t x2,uint8_t y1, uint8_t y2)
{
  unsigned char u,w;
  for(u=y1;u<=y2;u++)
  {
    for(w=x1;w<=x2;w++)
    {
      lcd_gotoxy(w,u);
      lcd_putc(' ',1);
    }
  }
}

/*
// function to delete full screen
// return NULL
*/
void lcd_clear_all()
{
  lcd_clear(0,21,0,7);
}

/*
// Protocol SPI with LCD Gphone 128x64
// @param : cd is choose operation with LCD
//      - 0 : Control pointer LCD
//      - 1 : Transmission data 
// @param : byte is data and information
// return NULL
*/
void lcd_write(bool cd, uint8_t byte)
{
  int8_t h;
  OUTPUT_LOW(Port_lcd,Cs);
  if(cd)
  {
    OUTPUT_HIGH(Port_lcd, A0);
  }
  else
  {
    OUTPUT_LOW(Port_lcd, A0);
  }
  for(h=0;h<8;h++)
  {
    if(byte&0x80) 
    {
      OUTPUT_HIGH(Port_lcd, SDA);
    }
    else
    {
      OUTPUT_LOW(Port_lcd, SDA);
    }
    
    OUTPUT_LOW(Port_lcd, SCLK);
    OUTPUT_HIGH(Port_lcd, SCLK);
    
    byte<<=1;
  }
  GPIO_toggleOutputOnPin(Port_lcd,A0);
  OUTPUT_HIGH(Port_lcd, Cs);
  
}

/*
// Function return cursor position on LCD
// @param :  x is column
//           - 0 <= x <= 20
// @param :  y is row
//           - 0 <= y <= 7
// return NULL
*/

void lcd_gotoxy(uint8_t x, uint8_t y)
{
  x=x*6;
  lcd_write(0,(x&0x0f));
  lcd_write(0,((x>>4)&0x07)|0x10);
  lcd_write(0,(y&0x0f)|0xb0);
}
/*
// Function return cursor position on LCD with BITMAP
// @param :  x is column
//           - 0 <= x <= 128
// @param :  y is row
//           - 0 <= y <= 7
// return NULL
*/
void glcd_gotoxy(uint8_t x, uint8_t y)
{
  
  lcd_write(0,(x&0x0f));
  lcd_write(0,((x>>4)&0x07)|0x10);
  lcd_write(0,(y&0x0f)|0xb0);
}
/*
// Function prints the screen to a string
// @param : *s is string
// @param:   color is Choose black or white 
//              - 0 : black
//              - 1 : white
// return NULL
*/
void lcd_puts(char *s,bool color)
{
  while(*s)
  {
    if(color)
    {
      lcd_putc(*s++,1);
    }
    else
    {
      lcd_putc(*s++,0);
    }
  }
}

/*
// Function prints a BITMAP to the screen
// @param x1 is column begins
//      - 0 <= x1 <= 128
// @param x2 is column ends
//      - 0 <= x1 <= x2 <= 128
// @param y1 is row begins
//      - 0 <= y1 <= 7
// @param y2 � row ends
//      - 0 <= y1 <= y2 <= 7
// @param array is code of BITMAP
// return NULL
*/
void lcd_image(char x1, char y1, char array[],char x2,char y2)
{
  char count;
  char buffer_string_RFIDferX2;
  buffer_string_RFIDferX2=x2;
  count = y2/8;
  glcd_gotoxy(x1,y1/8);
  while(x2--)
  {
    lcd_write(1,*array++);
  }
  while(count--)
  {
    glcd_gotoxy(x1,(y1/8)+(y2/8)-count);
    for(char i=x1;i<buffer_string_RFIDferX2;i++)
    {
      lcd_write(1,*array++);
    }
  }
}