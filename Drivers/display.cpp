#include "display.h"
#include "micros.h"

Display display;

void Display::init() {
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/**GPIO Configuration
	PD7     ------> DC
	PB5     ------> CS
	PB7     ------> RESET
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/**SPI2 GPIO Configuration
	PC2     ------> SPI2_MISO
	PC3     ------> SPI2_MOSI
	PD3     ------> SPI2_SCK
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// SPI 2
	SPI_HandleTypeDef hspi2;
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi2);
	__HAL_SPI_ENABLE(&hspi2);

	//DMA
	DMA1_Stream4->CR &= ~DMA_SxCR_EN;	// disable stream & wait
	while ((DMA1_Stream4->CR) & DMA_SxCR_EN);

	DMA1_Stream4->CR = (0 << 25) | DMA_SxCR_MINC | DMA_SxCR_DIR_0 | DMA_SxCR_TCIE | DMA_SxCR_DMEIE;
	DMA1_Stream4->FCR &= ~DMA_SxFCR_DMDIS;

	dma_busy_ = false;

	// Select, Reset & wait
	select();

	GPIOB->BSRR = GPIO_PIN_7 << 16;
	micros.delay(150 * 1000);
	GPIOB->BSRR = GPIO_PIN_7;
	micros.delay(150 * 1000);

	// Start lcd configuration
	sendCommand(0xfd, 0x12);		// Set Command Lock (MCU protection status) | 0x12 = reset
	sendCommand(0xae);				// Set Display Off
	sendCommand(0xb3, 0xd1);		// Set Front Clock Divider / Oscillator Frequency
	sendCommand(0xca, 0x3f);		// Set MUX Ratio | 0x3f = 64mux
	sendCommand(0xa2, 0x00);		// Set Display Offset | 0x00 = reset
	sendCommand(0xa1, 0x00);		// Set Display Start Line, 0x00 = register
	sendCommand(0xa0, 0x14, 0x11);	// Set Re-map and Dual COM Line mode
									// 0x14 = Reset except Enable Nibble Re-map, Scan from COM[N-1] to COM0, where N is the Multiplex ratio
									// 0x11 = Reset except Enable Dual COM mode (MUX = 63)
	sendCommand(0xb5, 0x00);		// Set GPIO
	sendCommand(0xab, 0x00);		// Function Selection | 0x01 = reset = Enable internal VDD regulator
	sendCommand(0xb4, 0xa0, 0xb5);	// Display Enhancement A | 0xa0 = Enable external VSL |  0xb5 = Normal (reset)
	sendCommand(0xc1, 0x9f);		// Set Contrast Current
	sendCommand(0xc7, 0x0f);		// Master Contrast Current Control | 0x0f = no change
	sendCommand(0xb9);				// Select Default Linear Gray Scale table
	sendCommand(0xb1, 0x74);		// Set Phase Length | 0xe2 = Phase 1 period (reset phase length) = 5 DCLKs, Phase 2 period (first pre-charge phase length) = 14 DCLKs
	sendCommand(0xd1, 0xa2, 0x20);	// Display Enhancement B | 0xa2 = Normal (reset) | 0x20 = n/a
	sendCommand(0xbb, 0x17);		// Set Pre-charge voltage | 0x1f = 0.6 * VCC
	sendCommand(0xb6, 0x08);		// Set Second Precharge Period | 0x08 = 8 dclks
	sendCommand(0xbe, 0x07);		// Set VCOMH | 0x07 = = 0.86 x VCC
	sendCommand(0xa6);				// Set Display Mode = Normal Display
	sendCommand(0xa9);				// Exit Partial Display
	micros.delay(10 * 1000);
	sendCommand(0xaf);				// Set Sleep mode OFF (Display ON),
	micros.delay(50 * 1000);

	// Start dma interrupt
	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
}

extern "C" {
	void DMA1_Stream4_IRQHandler(void) {
		uint32_t flags = DMA1->HISR;
		DMA1->HIFCR |= DMA_HIFCR_CTCIF4 | DMA_HIFCR_CHTIF4;

		if (flags & DMA_HISR_TCIF4) {
			display.unlock_dma();
		}
	}
}
