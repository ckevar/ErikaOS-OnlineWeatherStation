#include "ee.h"
#include "stm32f4xx.h"

/*
 * ESP8266 TRANSMITTER
 * */
void __IRQ EE_CORTEX_MX_DMA2_STREAM6_ISR(void) {
	if (DMA2->HISR & DMA_HISR_TCIF6) {
		// Ack at transfer complete
		DMA2->HIFCR = DMA_HIFCR_CTCIF6;
	} else if (DMA2->HISR & DMA_HISR_DMEIF6) {
		// Ack at Direct Mode went wrong
		DMA2->HIFCR = DMA_HIFCR_CDMEIF6;
	}
}

