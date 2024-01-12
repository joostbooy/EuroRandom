#ifndef Display_h
#define Display_h

#include "stmf4lib.h"
#include "debug.h"


class Display {

public:
	void init();

	inline void select(){
		GPIOB->BSRR = GPIO_PIN_5 << 16;
	}

	inline void deselect(){
		GPIOB->BSRR = GPIO_PIN_5;
	}

	inline void cd_high(){
		GPIOD->BSRR = GPIO_PIN_7;
	}

	inline void cd_low(){
		GPIOD->BSRR = GPIO_PIN_7 << 16;
	}

	void sendCommand(uint8_t cmd) {
		cd_low();
		spi_write(cmd);
	}

	void sendData(uint8_t data) {
		cd_high();
		spi_write(data);
	}

	void sendCommand(uint8_t cmd, uint8_t data) {
		sendCommand(cmd);
		sendData(data);
	}

	void sendCommand(uint8_t cmd, uint8_t data_a, uint8_t data_b) {
		sendCommand(cmd);
		sendData(data_a);
		sendData(data_b);
	}

	void set_col_address(uint8_t a, uint8_t b) {
		sendCommand(0x15, a, b);
	}

	void set_row_address(uint8_t a, uint8_t b) {
		sendCommand(0x75, a, b);
	}

	void enable_write() {
		sendCommand(0x5C);
	}

	void unlock_dma() {
		SPI2->CR2 &= ~SPI_CR2_TXDMAEN;
		DMA1_Stream4->CR &= ~DMA_SxCR_EN;
		dma_busy_ = false;
	}

	volatile bool dma_busy() {
		return dma_busy_;
	}

	void sendBuffer(uint8_t* data, uint32_t size) {
		while (dma_busy_) {};
		dummy = SPI2->DR;

		set_col_address(0x1C, 0x5B);
		set_row_address(0x00, 0x3F);
		enable_write();

		cd_high();

		DMA1->HIFCR |= DMA_HIFCR_CTCIF4 | DMA_HIFCR_CHTIF4 | DMA_HIFCR_CTEIF4 | DMA_HIFCR_CDMEIF4 | DMA_HIFCR_CFEIF4;
		DMA1_Stream4->PAR = reinterpret_cast<uint32_t>(&SPI2->DR);
		DMA1_Stream4->M0AR = reinterpret_cast<uint32_t>(&data[0]);
		DMA1_Stream4->NDTR = size;
		DMA1_Stream4->CR |= DMA_SxCR_EN;
		SPI2->CR2 |= SPI_CR2_TXDMAEN;

		dma_busy_ = true;
	}


private:
	volatile uint8_t dummy;
	volatile bool dma_busy_;


	void spi_write(uint8_t data) {
		while (!(SPI2->SR & SPI_FLAG_TXE));
		SPI2->DR = data;

		while (!(SPI2->SR & SPI_FLAG_RXNE));
		dummy = SPI2->DR;
	}
};

extern Display display;

#endif
