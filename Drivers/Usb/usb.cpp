#include "usb.h"

Usb usb;

void Usb::init() {
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Configure USB D+ D- Pins */
	GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Configure VBUS Pin */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// Enable VBUS sense (B device) via pin PA9
	USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_NOVBUSSENS;
	USB_OTG_FS->GCCFG |= USB_OTG_GCCFG_VBUSBSEN;

	// init tiny usb
	tud_init(0);
}

extern "C" {
	void OTG_FS_IRQHandler(void) {
		tud_int_handler(0);
	}
}
