#ifndef SRC_LORA_H_
#define SRC_LORA_H_

#include <stdint.h>
#include <main.h>

#define NSS_PIN_HIGH 	LL_GPIO_SetOutputPin(GPIOA, SPI_NSS_Pin);
#define NSS_PIN_LOW		LL_GPIO_ResetOutputPin(GPIOA, SPI_NSS_Pin);
#define SPI_HANDLER	SPI3



#define ADDR_REGFIFO					0x00
#define ADDR_REGOPMODE					0x01
#define ADDR_REGFRMSB					0x06
#define ADDR_REGFRMID					0x07
#define ADDR_REGFRLSB					0x08
#define ADDR_REGPACONFIG				0x09
#define ADDR_REGPARAMP					0x0A
#define ADDR_REGOCP						0x0B
#define ADDR_REGLNA						0x0C
#define ADDR_REGFIFOADDPTR				0x0D
#define ADDR_REGFIFOTXBASEADDR			0x0E
#define ADDR_REGFIFORXBASEADDR			0x0F
#define ADDR_REGFIFORXCURRENTADDR		0x10
#define ADDR_REGIRQFLAGS				0x12
#define ADDR_REGRXNBBYTES				0x13
#define ADDR_REGPKTRSSIVALUE			0x1A
#define	ADDR_REGMODEMCONFIG1			0x1D
#define ADDR_REGMODEMCONFIG2			0x1E
#define ADDR_REGMODEMSTAT				0x18
#define ADDR_REGSYMBTIMEOUTL			0x1F
#define ADDR_REGPREAMBLEMSB				0x20
#define ADDR_REGPREAMBLELSB				0x21
#define ADDR_REGPAYLOADLENGTH			0x22
#define ADDR_REGDIOMAPPING1				0x40
#define ADDR_REGDIOMAPPING2				0x41
#define ADDR_REGVERSION					0x42
#define ADDR_REGRSSIVALUE				0x1B

void LoRa_Write(uint8_t reg_address, uint8_t reg_value);
uint8_t LoRa_Receive(uint8_t reg_address);




#endif /* SRC_LORA_H_ */