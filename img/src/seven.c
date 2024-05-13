/*********************************************
 * File generate from an image to be displayed
 * on an LCD of the STM32f4
 * - C. Alvarado
 *
 */

const unsigned char seven[5886] = {
0x42,0x4D,0xFE,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
0x00,0x00,0x36,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x03,0x00,
0x00,0x00,0xC8,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xC3,0x20,0x00,0x08,0x61,0x10,
0x03,0x29,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x61,0x10,0x44,0x29,0xA2,0x18,0x4D,0x6B,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0xC6,0x41,0x41,0x10,0x85,0x31,0x40,0x08,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x00,0x00,0x65,0x29,0xE3,0x18,0x85,0x29,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xEB,0x62,
0x61,0x08,0x44,0x29,0xC2,0x10,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xA2,0x10,0xE3,0x18,
0xA2,0x10,0x24,0x21,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x00,0x00,0x65,0x29,0x81,0x08,
0x6D,0x73,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x65,0x29,0x24,0x21,0x24,0x21,0xA2,0x18,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x20,0x00,0x24,0x21,0x81,0x10,0x69,0x52,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x69,0x4A,0xC2,0x10,0x24,0x29,0x81,0x10,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x61,0x08,
0x24,0x29,0x61,0x10,0x65,0x31,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xAE,0x7B,0x61,0x10,0x45,0x29,
0x21,0x08,0x2C,0x6B,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x45,0x29,0xC4,0x18,0xE4,0x18,0x04,0x21,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x83,0x10,0x45,0x29,0x00,0x00,0x49,0x52,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x6A,0x52,0x41,0x08,0x45,0x29,0x61,0x10,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x41,0x10,0x86,0x39,0xE3,0x20,0x03,0x21,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x8E,0x73,0x20,0x08,
0x44,0x29,0x40,0x08,0x2C,0x6B,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x25,0x31,0xA2,0x18,0x44,0x29,
0x81,0x10,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x61,0x10,0x65,0x31,0x61,0x10,0x28,0x4A,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0xA6,0x39,0xC2,0x18,0x24,0x29,0x41,0x08,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x61,0x10,0x24,0x29,0xE3,0x20,0x65,0x31,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xEB,0x62,
0x20,0x08,0x65,0x29,0x00,0x00,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xC3,0x18,0xC2,0x18,
0x45,0x29,0xA3,0x18,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x00,0x00,0x86,0x31,0x41,0x08,
0x49,0x4A,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0xC7,0x39,0x20,0x08,0x24,0x29,0x61,0x10,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x82,0x10,0x25,0x29,0xA2,0x18,0x24,0x29,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x8A,0x52,0x82,0x10,0x04,0x21,0x41,0x10,0x4D,0x73,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xE3,0x20,
0xE3,0x20,0x04,0x21,0xA2,0x18,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x21,0x08,0x45,0x29,
0x62,0x10,0xAB,0x5A,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x45,0x31,0x82,0x18,0x25,0x29,0x21,0x08,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x21,0x10,0xA7,0x39,0x82,0x10,0x86,0x31,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x69,0x52,0xC3,0x18,0x45,0x29,0x00,0x00,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x61,0x10,0xE4,0x20,0xE3,0x20,0xA2,0x18,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x4D,0x73,0xA2,0x18,
0x65,0x31,0x20,0x08,0xCB,0x62,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x04,0x29,0x62,0x18,0x45,0x29,
0x00,0x00,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x41,0x10,0x03,0x21,0xC3,0x18,0x45,0x29,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x49,0x52,0xA2,0x18,0x65,0x31,0x61,0x08,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0xA2,0x18,0x24,0x21,0xA3,0x18,0xC3,0x18,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x2C,0x6B,
0x20,0x00,0xA6,0x31,0x20,0x00,0xCB,0x5A,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x24,0x21,0xE3,0x18,
0xE4,0x20,0x61,0x10,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x00,0x00,0x66,0x31,0x82,0x10,
0xA7,0x39,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x08,0x42,0xC3,0x18,0x45,0x29,0x41,0x10,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x00,0x00,0x45,0x29,0xE3,0x20,0x62,0x18,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0xEB,0x62,0x82,0x10,0x45,0x29,0x61,0x10,0x69,0x52,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xC3,0x20,
0xE3,0x20,0xE3,0x20,0x61,0x10,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x41,0x10,0x65,0x31,
0x61,0x10,0xA6,0x39,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0xE7,0x41,0x61,0x10,0x24,0x29,0x00,0x00,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x61,0x10,0x04,0x21,0x44,0x29,0xE3,0x20,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x2C,0x6B,0x00,0x00,0x44,0x29,0x61,0x10,0x8A,0x52,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x85,0x31,0xC2,0x18,0x03,0x21,0x82,0x10,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x4C,0x6B,0xA2,0x10,
0x24,0x21,0x61,0x10,0xC6,0x39,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x00,0x08,0xA2,0x18,0xA2,0x18,
0xA2,0x18,0xA2,0x18,0xA2,0x18,0xA2,0x18,0xA2,0x10,0xA2,0x10,0xA3,0x18,0xA3,0x18,
0xA3,0x18,0xA3,0x18,0xA3,0x18,0xA3,0x18,0xA3,0x18,0xA3,0x18,0xA3,0x18,0xA3,0x18,
0xA3,0x18,0xA3,0x18,0xA3,0x18,0xA3,0x18,0xA3,0x18,0xA2,0x18,0x82,0x18,0xA2,0x18,
0xA2,0x18,0xA2,0x18,0xC2,0x18,0xC3,0x18,0xE3,0x18,0x03,0x21,0xE3,0x20,0x85,0x31,
0x40,0x08,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x61,0x10,0x82,0x18,0xA2,0x18,0xA2,0x18,0xA2,0x18,
0xA2,0x18,0xA2,0x10,0xA2,0x10,0xA2,0x10,0xA2,0x18,0xA2,0x18,0x82,0x18,0xA2,0x18,
0x82,0x18,0xA2,0x18,0x82,0x18,0xA2,0x18,0x82,0x18,0xA2,0x18,0x82,0x18,0xA2,0x18,
0x82,0x18,0xA2,0x18,0x82,0x18,0x82,0x18,0x82,0x18,0x82,0x18,0xA2,0x18,0xA2,0x18,
0xA2,0x18,0xA2,0x18,0xC2,0x18,0xC2,0x18,0xC2,0x18,0xA2,0x18,0x00,0x00,0xE3,0x20,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x65,0x31,0xA6,0x39,0xA6,0x39,0xA6,0x39,0xA6,0x39,0xA6,0x39,0xA6,0x39,
0xA6,0x39,0xA6,0x39,0x86,0x39,0x86,0x39,0x86,0x39,0x86,0x39,0x86,0x39,0x86,0x39,
0x86,0x39,0x86,0x39,0x86,0x39,0x86,0x39,0x86,0x39,0x86,0x39,0x86,0x39,0x86,0x39,
0x86,0x39,0x86,0x39,0x86,0x39,0xA6,0x39,0xA6,0x39,0xA6,0x39,0xA6,0x39,0xA6,0x39,
0xA6,0x39,0xA6,0x39,0x65,0x31,0x85,0x31,0xE7,0x41,0x24,0x29,0x12,0x7F,0x12,0x7F,
0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,0x12,0x7F,};

/********* GNU Licence - END OF FILE *********/
