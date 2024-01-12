#ifndef uart_h
#define uart_h

#include "stmf4lib.h"

class Uart {

public:
	void init();

	inline void write(uint8_t index, uint8_t data) {
		port[index].write(data);
	}

	inline bool writeable(uint8_t index) {
		return port[index].writeable();
	}

	inline uint8_t read(uint8_t index) {
		return port[index].read();
	}

	inline bool readable(uint8_t index) {
		return port[index].readable();
	}

private:

	// MIDI 1 - USART 6
	static inline void write_1(uint8_t data) {
		USART6->DR = data;
	}

	static inline bool writeable_1() {
		return USART6->SR & UART_FLAG_TXE;
	}

	static inline uint8_t read_1() {
		return USART6->DR;
	}

	static inline bool readable_1() {
		return USART6->SR & UART_FLAG_RXNE;
	}

	// MIDI 2 - USART 2
	static inline void write_2(uint8_t data) {
		USART2->DR = data;
	}

	static inline bool writeable_2() {
		return USART2->SR & UART_FLAG_TXE;
	}

	static inline uint8_t read_2() {
		return USART2->DR;
	}

	static inline bool readable_2() {
		return USART2->SR & UART_FLAG_RXNE;
	}

	// MIDI 3 - USART 3
	static inline void write_3(uint8_t data) {
		USART3->DR = data;
	}

	static inline bool writeable_3() {
		return USART3->SR & UART_FLAG_TXE;
	}

	static inline uint8_t read_3() {
		return USART3->DR;
	}

	static inline bool readable_3() {
		return USART3->SR & UART_FLAG_RXNE;
	}

	// MIDI 4 - UART 7
	static inline void write_4(uint8_t data) {
		UART7->DR = data;
	}

	static inline bool writeable_4() {
		return UART7->SR & UART_FLAG_TXE;
	}

	static inline uint8_t read_4() {
		return UART7->DR;
	}

	static inline bool readable_4() {
		return UART7->SR & UART_FLAG_RXNE;
	}


	struct Port {
		void(*const write)(uint8_t);
		bool(*const writeable)();
		uint8_t(*const read)();
		bool(*const readable)();
	};

	const Port port[4] = {
		{ &write_1, &writeable_1, &read_1, &readable_1 },
		{ &write_2, &writeable_2, &read_2, &readable_2 },
		{ &write_3, &writeable_3, &read_3, &readable_3 },
		{ &write_4, &writeable_4, &read_4, &readable_4 },
	};
};

extern Uart uart;

#endif
