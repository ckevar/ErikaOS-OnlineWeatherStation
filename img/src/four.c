/*********************************************
 * File generate from an image to be displayed
 * on an LCD of the STM32f4
 * - C. Alvarado
 *
 */

const unsigned char four[5886] = {
0x42,0x4D,0xFE,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
0x00,0x00,0x36,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x03,0x00,
0x00,0x00,0xC8,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x85,0x39,0x00,0x08,0x00,0x00,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x07,0x42,0xC2,0x18,0x81,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x07,0x42,0xA2,0x18,0x81,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x07,0x42,
0xA2,0x18,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,0xA2,0x18,0x61,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,0xA2,0x18,0x81,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xE7,0x41,0xA2,0x18,0x81,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x07,0x42,
0xA2,0x18,0x81,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,0xA2,0x18,0x62,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xC7,0x41,0xA2,0x18,0x82,0x18,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xC8,0x41,0x62,0x10,0x01,0x08,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x28,0x4A,
0x04,0x21,0xA3,0x18,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x6D,0x7B,0x97,0x7E,0x97,0x7E,0x8E,0x73,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0xAE,0x7B,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x29,0xE3,0x18,0xE3,0x18,
0xEC,0x5A,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,0x20,0x08,
0x61,0x10,0xA2,0x18,0x00,0x00,0x41,0x08,0x20,0x00,0xA2,0x10,0xA2,0x10,0x41,0x08,
0x82,0x10,0xC2,0x18,0x81,0x10,0x81,0x10,0x81,0x10,0x81,0x10,0x81,0x10,0x81,0x10,
0x81,0x10,0x81,0x10,0x81,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x82,0x10,
0x82,0x10,0x82,0x10,0x82,0x08,0xC3,0x10,0xE3,0x18,0x24,0x21,0x82,0x08,0x62,0x08,
0xC3,0x18,0x82,0x10,0x82,0x10,0xA2,0x18,0x00,0x08,0xA6,0x39,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x24,0x29,0x04,0x21,0x65,0x29,
0x04,0x21,0xE3,0x18,0xA2,0x10,0x61,0x08,0xA2,0x10,0x61,0x08,0x41,0x08,0xC2,0x10,
0x61,0x08,0x81,0x10,0x81,0x10,0x81,0x10,0x81,0x10,0xA1,0x10,0xA1,0x10,0xA1,0x10,
0x81,0x10,0x81,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x82,0x10,0x82,0x08,
0xA2,0x08,0x24,0x19,0x24,0x19,0x65,0x29,0xA2,0x10,0x62,0x08,0xE4,0x18,0xA2,0x10,
0xA2,0x10,0xE3,0x20,0x00,0x00,0xA6,0x39,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x00,0x00,0x45,0x29,0xC2,0x18,0xC7,0x39,
0xAE,0x73,0x6D,0x6B,0x6D,0x6B,0xAE,0x73,0x6D,0x6B,0xAE,0x73,0x4C,0x6B,0x6C,0x6B,
0x6C,0x6B,0x6C,0x6B,0x6C,0x6B,0x6C,0x6B,0x6C,0x6B,0x6C,0x6B,0x4C,0x6B,0x4C,0x6B,
0x4C,0x6B,0x4C,0x6B,0x4C,0x6B,0x4D,0x6B,0x6D,0x6B,0x6D,0x6B,0x6D,0x6B,0x85,0x29,
0xC2,0x10,0xA2,0x10,0x69,0x4A,0xAE,0x73,0x6D,0x6B,0x4D,0x6B,0x4D,0x6B,0x2C,0x6B,
0xCB,0x62,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x6D,0x73,0x20,0x08,0xE3,0x20,0x44,0x29,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x28,0x42,0xA2,0x10,0x81,0x08,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xE7,0x41,0xE3,0x20,0x82,0x10,0xA6,0x31,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x07,0x42,0xA2,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0xC3,0x18,0x44,0x29,0x00,0x00,0x6D,0x73,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xE7,0x41,0xA2,0x18,0x62,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x41,0x10,
0x04,0x29,0x00,0x00,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,
0x82,0x18,0x61,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xAA,0x5A,0x82,0x18,0x04,0x29,
0x82,0x18,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,0x82,0x18,0x61,0x18,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x31,0x82,0x18,0xA2,0x18,0xE8,0x49,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,0xA2,0x18,0x61,0x18,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x00,0x00,0x04,0x21,0x82,0x10,0x2C,0x6B,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xE7,0x41,0xA2,0x18,0x61,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x00,0x00,0xC7,0x39,0x41,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,
0xA2,0x18,0x61,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x49,0x4A,0x82,0x10,0x04,0x21,0xA2,0x18,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE7,0x41,0xA2,0x18,0x82,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xC2,0x18,
0xE3,0x20,0x82,0x10,0xE7,0x41,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x81,0x10,0x24,0x29,
0xA2,0x18,0x2D,0x6B,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x6D,0x73,0x61,0x10,0xE4,0x20,0x61,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,
0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xA6,0x39,0xC3,0x18,0xC3,0x20,0x24,0x29,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x61,0x10,0xE4,0x20,0xE3,0x20,0x08,0x4A,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x41,0x08,0xE4,0x20,0x41,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x8A,0x5A,
0x62,0x18,0xE3,0x20,0xA2,0x18,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,
0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x04,0x29,0xC3,0x20,
0x62,0x18,0xE4,0x28,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x41,0x10,0x24,0x29,0x41,0x10,
0x69,0x52,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x00,0x00,0x86,0x39,0xA2,0x18,0x4D,0x6B,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x08,0x4A,0xA2,0x18,0xE3,0x20,0x62,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,
0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xC3,0x18,0xE3,0x18,0x04,0x21,0x24,0x29,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x20,0x00,0x25,0x21,0x82,0x10,0x28,0x4A,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x2D,0x6B,0x20,0x00,
0x24,0x21,0x61,0x08,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x08,0x42,0xC3,0x18,0x04,0x21,
0x81,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,
0xA3,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x61,0x08,0x03,0x21,0xE2,0x18,0x85,0x31,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0xA3,0x10,0x82,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x60,0x08,0x65,0x29,0x40,0x00,0xCA,0x52,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE8,0x41,0x82,0x10,0x21,0x08,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x48,0x4A,0xC2,0x10,0x24,0x21,0x40,0x00,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xC8,0x41,0xA3,0x18,0x62,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x85,0x29,0xE3,0x18,0x44,0x29,0x20,0x00,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xC7,0x39,
0xC3,0x18,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x61,0x08,
0x44,0x29,0xA3,0x18,0x04,0x21,0x97,0x7E,0x97,0x7E,0xC7,0x39,0xA3,0x18,0x41,0x08,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x2C,0x6B,0x41,0x08,0x86,0x31,
0x61,0x08,0xCB,0x5A,0x97,0x7E,0x28,0x42,0xC3,0x18,0x20,0x00,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xA6,0x39,0xA2,0x10,0x85,0x29,0x41,0x00,
0x97,0x7E,0x28,0x42,0x03,0x19,0x41,0x08,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x81,0x10,0xE3,0x18,0x04,0x19,0x04,0x19,0x86,0x29,
0x04,0x19,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x61,0x08,0x44,0x21,0x03,0x19,0xE3,0x10,0xE3,0x18,0xA2,0x10,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x69,0x4A,0x82,0x10,0x45,0x21,0xE3,0x18,0x65,0x29,0x40,0x08,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x29,
0xC3,0x18,0x03,0x19,0x44,0x21,0x41,0x08,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x82,0x10,0x03,0x21,
0xE3,0x18,0x41,0x08,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x4C,0x6B,0x20,0x08,0x20,0x08,0x00,0x08,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,};

/********* GNU Licence - END OF FILE *********/
