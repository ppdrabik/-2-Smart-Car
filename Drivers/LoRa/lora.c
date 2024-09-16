#include "LoRa.h"

static void SPI_Write_8(uint8_t data);
static uint8_t SPI_Receive_8(uint8_t data);


static void SPI_Write_8(uint8_t data)
{
	/* Wait until TX buffer is empty */
	while (!(LL_SPI_IsActiveFlag_TXE(SPI_HANDLER))){} 	
	LL_SPI_TransmitData8(SPI_HANDLER, data);

	/* Wait until RX buffer fills and read to clear buffer */
	while (!LL_SPI_IsActiveFlag_RXNE(SPI_HANDLER)){}
	LL_SPI_ReceiveData8(SPI_HANDLER);

	/* Wait until SPI finishes transmission */
	while(LL_SPI_IsActiveFlag_BSY(SPI_HANDLER));
}


static uint8_t SPI_Receive_8(uint8_t reg_address)
{
	uint8_t data_received = 0;

	SPI_Write_8(reg_address);
	
	/* Send dummy byte to generate clock signal and read data from register */
	LL_SPI_TransmitData8(SPI_HANDLER, 0xFF); 

	/* Wait until RX buffer fills with data */
	while (!LL_SPI_IsActiveFlag_RXNE(SPI_HANDLER)){}
	data_received = LL_SPI_ReceiveData8(SPI_HANDLER);

	/* Wait until SPI finishes receiving */
	while(LL_SPI_IsActiveFlag_BSY(SPI_HANDLER));

	return data_received;
}


void LoRa_Write(uint8_t reg_address, uint8_t reg_value)
{
	reg_address = SET_BIT(reg_address, 1<<7);
	
	NSS_PIN_LOW
	SPI_Write_8(reg_address);
	SPI_Write_8(reg_value);
	NSS_PIN_HIGH
}


uint8_t LoRa_Receive(uint8_t reg_address)
{
	uint8_t data_received = 0;
	reg_address = CLEAR_BIT(reg_address, 1<<7);

	NSS_PIN_LOW
	data_received = SPI_Receive_8(reg_address);
	NSS_PIN_HIGH
	return data_received;
}

