#include "sdio.h"

Sdio sdio;

void Sdio::init() {
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	//powerOff();

	/**GPIO Configuration
	PA8     ------> Card detect
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	/**SDIO GPIO Configuration
	PC8     ------> SDIO_D0
	PC9     ------> SDIO_D1
	PC10     ------> SDIO_D2
	PC11     ------> SDIO_D3
	PC12     ------> SDIO_CK
	PD2     ------> SDIO_CMD
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIO_InitStruct.Alternate = GPIO_AF12_SDIO;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	// Enable dma interrupt
	HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
}


// DMA2 steam 3 Channel 4
const uint32_t kChannel4				= (4 << 25);
const uint32_t kMemoryBurst_inc4		= (1 << 23);
const uint32_t kPeripheralBurst_inc4	= (1 << 21);
const uint32_t kPriorityVeryHigh		= (3 << 16);
const uint32_t kMemorySize_32bit		= (2 << 13);
const uint32_t kPeripheralSize_32bit	= (2 << 11);
const uint32_t kEnableMemoryIncrement	= (1 << 10);
const uint32_t kEnableFifo				= (1 << 8);
const uint32_t kMemoryToPeripheral		= (1 << 6);
const uint32_t kPeripheralFlowControl	= (1 << 5);
const uint32_t kEnable_TC_interupt		= (1 << 4);

void Sdio::init_dma(uint32_t buffer, DmaType dmaType) {
	DMA2_Stream3->CR &= ~DMA_SxCR_EN;			// disable stream & wait
	while (DMA2_Stream3->CR & DMA_SxCR_EN) {};

	uint32_t direction = 0;
	if (dmaType == MEM_TO_SD) {
		direction =	kMemoryToPeripheral;
	} else if (dmaType == SD_TO_MEM) {
		direction =	0;
	}

	DMA2_Stream3->CR = 0;
	DMA2_Stream3->CR = (kChannel4 | kMemoryBurst_inc4 | kPeripheralBurst_inc4 | kPriorityVeryHigh | kMemorySize_32bit | kPeripheralSize_32bit | kEnableMemoryIncrement | kPeripheralFlowControl | direction | kEnable_TC_interupt);

	DMA2_Stream3->FCR |= DMA_SxFCR_DMDIS;	// disable direct mode (enables fifo mode)
	DMA2_Stream3->FCR |= (3 << 0); 			// fifo treshold full

	DMA2->LIFCR |= DMA_LIFCR_CTCIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CFEIF3;
	DMA2_Stream3->PAR = reinterpret_cast<uint32_t>(&SDIO->FIFO);
	DMA2_Stream3->M0AR = buffer;
	DMA2_Stream3->NDTR = 0;
	DMA2_Stream3->CR |= DMA_SxCR_EN;		// enable stream

	sdio.lock_dma();
}

extern "C" {
	void DMA2_Stream3_IRQHandler(void) {
		uint32_t flags = DMA2->LISR;
		DMA2->LIFCR |= DMA_LIFCR_CTCIF3 | DMA_LIFCR_CHTIF3;

		if (flags & DMA_LISR_TCIF3) {
			sdio.unlock_dma();
		}
	}
}
