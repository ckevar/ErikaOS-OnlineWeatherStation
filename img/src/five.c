/*********************************************
 * File generate from an image to be displayed
 * on an LCD of the STM32f4
 * - C. Alvarado
 *
 */

const unsigned char five[5886] = {
0x42,0x4D,0xFE,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
0x00,0x00,0x36,0x00,0x00,0x00,0x36,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x03,0x00,
0x00,0x00,0xC8,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xAB,0x5A,0x49,0x4A,
0x28,0x42,0x69,0x52,0x0C,0x63,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x8A,0x52,0xC3,0x18,0x82,0x10,0xA3,0x18,0xA3,0x18,0xC3,0x18,0x82,0x10,0x82,0x10,
0xA2,0x10,0x82,0x10,0x62,0x10,0x45,0x29,0x48,0x4A,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x08,0x42,0x41,0x08,0xC3,0x18,0xC3,0x18,
0x82,0x10,0x82,0x10,0x61,0x08,0xA3,0x18,0xC3,0x18,0xC3,0x18,0xA2,0x10,0x82,0x10,
0x82,0x10,0xA2,0x10,0xC3,0x18,0x61,0x10,0x49,0x52,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0xEB,0x62,0x21,0x08,0x82,0x10,0x04,0x21,0xC3,0x18,0xA2,0x18,0x49,0x4A,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x69,0x52,0x04,0x21,
0x20,0x08,0xE3,0x20,0x81,0x18,0xA2,0x18,0xCB,0x62,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x08,0x42,0xA2,0x18,0x24,0x29,
0x61,0x10,0x04,0x29,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x45,0x31,
0x61,0x10,0x85,0x31,0x61,0x10,0x65,0x31,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x08,0x42,0x61,0x10,0xC3,0x20,0x21,0x10,0x6D,0x73,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x6D,0x73,0x40,0x08,
0xC2,0x18,0xE3,0x20,0x44,0x31,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xA7,0x39,
0x00,0x00,0xE3,0x20,0xA3,0x18,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x03,0x21,0x81,0x10,
0xA2,0x18,0x65,0x39,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xAA,0x5A,0xC3,0x18,0xC3,0x18,0x04,0x21,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x24,0x29,0xC2,0x18,0xE3,0x20,
0x28,0x52,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x20,0x08,0xA7,0x39,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xC3,0x20,0x82,0x18,0xE3,0x28,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x45,0x31,
0xE3,0x20,0x21,0x08,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x61,0x10,0xA2,0x18,0x04,0x29,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE3,0x20,0x41,0x10,0x49,0x52,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xAA,0x5A,0xA2,0x18,0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x07,0x42,0x41,0x08,0xA2,0x18,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0xC3,0x18,0x82,0x10,0xC7,0x39,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x81,0x10,0x81,0x10,0x89,0x52,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x69,0x52,0x82,0x10,
0x41,0x08,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xAE,0x7B,0x40,0x08,0xA2,0x18,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x82,0x10,0x82,0x10,0xCB,0x5A,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x48,0x4A,0x61,0x10,0x44,0x29,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x04,0x21,0x04,0x21,0x45,0x29,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0xC2,0x18,0x20,0x08,0xE7,0x41,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x49,0x4A,0xA2,0x10,0x04,0x21,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x6E,0x73,
0x21,0x08,0xE3,0x20,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x41,0x08,0x41,0x08,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x82,0x10,0x82,0x10,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x61,0x10,0xA3,0x18,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x6D,0x6B,
0x41,0x08,0xC3,0x18,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x8A,0x52,0x61,0x10,0xE3,0x20,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x29,0xA2,0x18,0x86,0x31,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x82,0x10,0x82,0x10,0x0C,0x63,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x2C,0x6B,0x82,0x10,
0x82,0x10,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x24,0x21,0x24,0x21,0xC2,0x18,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x2C,0x6B,0x61,0x10,0xA2,0x18,0x8D,0x73,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x81,0x10,
0x65,0x31,0x03,0x21,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xC2,0x20,0x44,0x29,0x00,0x00,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x44,0x31,0x24,0x29,0x00,0x00,0xAA,0x5A,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xE3,0x28,0xE3,0x20,
0xA2,0x18,0x04,0x29,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x24,0x29,0x00,0x00,0x61,0x10,
0x61,0x10,0x00,0x00,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0xC2,0x20,0xA2,0x18,0xE3,0x20,0xE3,0x20,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x31,0x03,0x21,0x24,0x21,0xE3,0x18,0x45,0x29,
0xC3,0x18,0xA6,0x39,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xC7,0x41,
0x81,0x18,0xE3,0x28,0x81,0x18,0x03,0x29,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x24,0x29,0x03,0x21,0x03,0x21,0x44,0x21,0x41,0x08,0xA2,0x10,0xA2,0x18,
0xA2,0x18,0x65,0x31,0xCB,0x5A,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x2C,0x6B,0x86,0x31,0x41,0x08,0xC2,0x20,0xE3,0x20,0x00,0x08,
0xEB,0x62,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xA6,0x39,
0xC2,0x18,0xC3,0x18,0x97,0x7E,0x97,0x7E,0x86,0x31,0x00,0x00,0xC3,0x18,0x24,0x21,
0x62,0x10,0x61,0x10,0x04,0x21,0x24,0x21,0xE3,0x18,0xA2,0x18,0xA2,0x10,0x82,0x10,
0x61,0x08,0xA2,0x10,0x04,0x21,0x00,0x08,0xA6,0x39,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0xA6,0x39,0xC2,0x18,0xE3,0x18,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x28,0x4A,0x61,0x10,0x61,0x10,0xA2,0x18,
0x00,0x00,0x82,0x10,0x82,0x10,0xC3,0x18,0xC3,0x18,0x82,0x10,0x82,0x10,0x04,0x21,
0xA6,0x39,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x86,0x39,0xC2,0x18,0xE3,0x20,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x8E,0x73,0xEB,0x62,0xE7,0x41,
0xC7,0x39,0xE7,0x41,0x69,0x52,0x2C,0x6B,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x85,0x39,0xA2,0x18,0xE3,0x20,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,
0xA2,0x18,0xE3,0x20,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,0x82,0x18,0xE3,0x28,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,0x82,0x20,0xC3,0x28,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x65,0x39,0x82,0x20,0xE3,0x28,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,
0xA2,0x20,0xE3,0x28,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,0xA2,0x20,0xE3,0x28,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,0xA2,0x20,0xE3,0x28,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x65,0x39,0xA2,0x20,0xE3,0x28,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,
0xA2,0x20,0xE3,0x28,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,0xA2,0x20,0xE3,0x28,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,0xA2,0x20,0xE3,0x28,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x65,0x39,0xA2,0x20,0xE3,0x28,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,
0x82,0x18,0xC3,0x20,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x65,0x39,0xC3,0x20,0x04,0x29,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x85,0x39,0xE3,0x20,0x04,0x29,0x82,0x18,0x61,0x08,
0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,
0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x08,0x61,0x10,
0x61,0x10,0x40,0x08,0xA2,0x18,0x00,0x08,0xEB,0x62,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x04,0x29,0x00,0x00,0x61,0x18,0x20,0x08,0xA2,0x10,0xA2,0x10,0xA2,0x10,
0xA2,0x10,0xA2,0x10,0xA2,0x10,0xA2,0x10,0xA2,0x10,0xA2,0x10,0xA2,0x10,0xA2,0x10,
0xA2,0x10,0xA2,0x10,0xA2,0x10,0xA2,0x10,0xA2,0x10,0x81,0x10,0x81,0x10,0x61,0x10,
0xA2,0x18,0x00,0x00,0xCB,0x62,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,
0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,0x97,0x7E,};

/********* GNU Licence - END OF FILE *********/