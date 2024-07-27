#include "dac.h"

Dac* Dac::dac_;

void Dac::init() {

	dac_ = this;

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/**I2S2 GPIO Configuration
	PB12     ------> I2S2_WS
	PB13     ------> I2S2_CK
	PB15     ------> I2S2_SD
	*/

	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	I2S_HandleTypeDef hi2s2;

	hi2s2.Instance = SPI2;
	hi2s2.Init.Mode = I2S_MODE_MASTER_TX;
	hi2s2.Init.Standard = I2S_STANDARD_PCM_SHORT;
	hi2s2.Init.DataFormat = I2S_DATAFORMAT_32B;
	hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
	hi2s2.Init.AudioFreq = I2S_AUDIOFREQ_16K * kNumChannels; // 64000
	hi2s2.Init.CPOL = I2S_CPOL_LOW;
	hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
	hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
	HAL_I2S_Init(&hi2s2);
	__HAL_I2S_ENABLE(&hi2s2);

	DMA_HandleTypeDef hdma_spi2_tx;

	hdma_spi2_tx.Instance = DMA1_Stream4;
	hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma_spi2_tx.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma_spi2_tx.Init.Mode = DMA_CIRCULAR;
	hdma_spi2_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
	hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	HAL_DMA_Init(&hdma_spi2_tx);
	__HAL_LINKDMA(&hi2s2, hdmatx, hdma_spi2_tx);
	HAL_I2S_Transmit_DMA(&hi2s2, (uint16_t*)dma_buffer_, kDmaBufferSize);
}

void Dac::start(void (*callback)(Buffer*, size_t)) {
	callback_ = callback;
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);
}

extern "C" {
	void DMA1_Stream4_IRQHandler(void) {
		uint32_t flags = DMA1->HISR;
		DMA1->HIFCR |= DMA_HIFCR_CTCIF4 | DMA_HIFCR_CHTIF4;

		if (flags & DMA_HISR_TCIF4) {
			Dac::dac_->fill(1);
		} else if (flags & DMA_HISR_HTIF4) {
			Dac::dac_->fill(0);
		}
	}
}
