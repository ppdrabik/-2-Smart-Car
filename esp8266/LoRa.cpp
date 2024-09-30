/*
 * LoRa.c
 *
 *  Created on: 6 lip 2023
 *      Author: ppdra
 */

#include "LoRa.h"


static void SPI_Write_8(uint8_t data);
static uint8_t SPI_Receive_8(uint8_t reg_address);


static void SPI_Write_8(uint8_t data)
{
	  SPI.transfer(data);
}

static uint8_t SPI_Receive_8(uint8_t reg_address)
{
    uint8_t data_received = 0;
	  SPI.transfer(reg_address);
	  data_received = SPI.transfer(0xFF);
	  return data_received;
}

void LoRa_Write(uint8_t reg_address, uint8_t reg_value)
{
	SET_BIT(reg_address, 1<<7);

	NSS_PIN_LOW
	SPI_Write_8(reg_address);
	SPI_Write_8(reg_value);
	NSS_PIN_HIGH
}


uint8_t LoRa_Receive(uint8_t reg_address)
{
	uint8_t data_received = 0;
	CLEAR_BIT(reg_address, 1<<7);

	NSS_PIN_LOW
	data_received = SPI_Receive_8(reg_address);
	NSS_PIN_HIGH
	return data_received;
}

void LoRa_Mode(mode_e mode)
{
	uint8_t read_value = LoRa_Receive(ADDR_REGOPMODE);
	CLEAR_BITS(read_value, 0x07);
	SET_BITS(read_value, mode);
	LoRa_Write(ADDR_REGOPMODE, read_value);
}


void LoRa_Set_Bandwidth(bandwidth_e bandwidth)
{
	uint8_t read_value = LoRa_Receive(ADDR_REGMODEMCONFIG1);
	CLEAR_BITS(read_value, 0xf0);
	SET_BITS(read_value, (bandwidth << 4));
	LoRa_Write(ADDR_REGMODEMCONFIG1, read_value);
}


void LoRa_Set_Coding_Rate(coding_rate_e coding_rate)
{
	uint8_t read_value = LoRa_Receive(ADDR_REGMODEMCONFIG1);
	CLEAR_BITS(read_value, 0x0e);
	SET_BITS(read_value, coding_rate<<1);
	LoRa_Write(ADDR_REGMODEMCONFIG1, read_value);
}


void LoRa_Set_Spreading_Factor(spreading_factor_e SF)
{
	uint8_t read_value = LoRa_Receive(ADDR_REGMODEMCONFIG2);
	CLEAR_BITS(read_value, 0xf0);
	SET_BITS(read_value, SF<<4);
	LoRa_Write(ADDR_REGMODEMCONFIG2, read_value);
}


void LoRa_Set_CRC(bool set_rest)
{
	uint8_t read_value = LoRa_Receive(ADDR_REGMODEMCONFIG2);
	if(set_rest == true)
	{
		SET_BIT(read_value, 1<<2);
	}
	else
  	{
    	CLEAR_BIT(read_value, 1<<2);
  	}
  	LoRa_Write(ADDR_REGMODEMCONFIG2, read_value);
}


void LoRa_Set_Pa_Boost(bool set_rest)
{
	uint8_t read_value = LoRa_Receive(ADDR_REGPACONFIG);
  	if(set_rest == true)
  	{
		SET_BIT(read_value, 1<<7);
  	}
  	else
  	{
    	CLEAR_BIT(read_value, 1<<7);
  	}
  	LoRa_Write(ADDR_REGPACONFIG, read_value);
}

/*
 * Set Max Output Power: 0 to 7
 */

void LoRa_Set_Max_Output_Power(uint8_t value)
{
	if(value <= 7)
	{
		uint8_t read_value = LoRa_Receive(ADDR_REGPACONFIG);
		SET_BITS(read_value, (value)<<4);
		LoRa_Write(ADDR_REGPACONFIG, read_value);
	}
}

/*
 * Set Output Power: 0 to 15
 */
void LoRa_Set_Output_Power(uint8_t value)
{
	if(value <= 15)
	{
		uint8_t read_value = LoRa_Receive(ADDR_REGPACONFIG);
		SET_BITS(read_value, value);
		LoRa_Write(ADDR_REGPACONFIG, read_value);
	}

}

/*
 * Set Lna Gain: 0 to 7
 */
void LoRa_Set_Lna_Gain(uint8_t value)
{
	if(value <= 7)
	{
		uint8_t read_value = LoRa_Receive(ADDR_REGLNA);
		SET_BITS(read_value, (value)<<5);
		LoRa_Write(ADDR_REGLNA, read_value);
	}
}


void LoRa_Init_Transmit()
{
    LoRa_Write(ADDR_REGDIOMAPPING1, 0x40);  /* Map Pin DIO0 for interrupt when TX done */
    LoRa_Write(ADDR_REGIRQFLAGS, 0xFF);     /* Clear interrupts flags */
    LoRa_Set_CRC(true); 					/* SET CRC enable */
}


void LoRa_Transmit_8(int8_t *data, uint8_t length)
{
    uint8_t fifo_current_address = 0;
    LoRa_Mode(STDBY);
    fifo_current_address = LoRa_Receive(ADDR_REGFIFOTXBASEADDR);   /* Read pointer from where data to Tx will be stored */
    LoRa_Write(ADDR_REGFIFOADDPTR, fifo_current_address);       /* Write address of pointer */ 
    LoRa_Write(ADDR_REGPAYLOADLENGTH, length);                  /* Write data length */
    for (uint8_t i = 0; i < length; i++)
    {
        LoRa_Write(ADDR_REGFIFO, data[i]);                      /* Write data to FIFO, Pointer increment itself*/
    }
    LoRa_Mode(TX);
    while(digitalRead(D2) == 0){yield();};   
}

void Lora_Init_Receive()
{
    LoRa_Write(ADDR_REGDIOMAPPING1, 0x00);  /* Map Pin DIO0 for interrupt when RX done */
    LoRa_Write(ADDR_REGIRQFLAGS, 0xFF);     /* Clear interrupts flags */
	  LoRa_Set_CRC(false);				/* CRC only on TX side in Explicit mode */
}

void LoRa_Recieve_8(uint8_t *recieved_data, uint8_t length)
{
  uint8_t fifo_current_address = 0;
  uint8_t bytes_received = 0;


	LoRa_Mode(STDBY);
	fifo_current_address = LoRa_Receive(ADDR_REGFIFORXBASEADDR);
	LoRa_Write(ADDR_REGFIFOADDPTR, fifo_current_address);
	LoRa_Mode(RXCONTINUOUS);

  while(digitalRead(D2) == 0){yield();};

  bytes_received = LoRa_Receive(ADDR_REGRXNBBYTES);
	fifo_current_address = LoRa_Receive(ADDR_REGFIFORXBASEADDR);
	LoRa_Write(ADDR_REGFIFOADDPTR, fifo_current_address);
	for (uint8_t i = 0; i < bytes_received; i++)
	{
    /* Write data to FIFO, Pointer to next data increment itself*/
		recieved_data[i] = LoRa_Receive(ADDR_REGFIFO);  
    
	}
	LoRa_Write(ADDR_REGIRQFLAGS, 0xFF);
}


void LoRa_Init(lora_s *lora)
{
  pinMode(D1, OUTPUT); // NSS
  pinMode(D2, INPUT); // DIO0

  SPI.begin();
  SPI.beginTransaction(SPISettings(6500000, MSBFIRST, SPI_MODE0));

	LoRa_Mode(SLEEP);
	LoRa_Write(ADDR_REGOPMODE, 0x88); 		/* Set LoRa Mode */
	LoRa_Set_Bandwidth(lora->bandwidth);
	LoRa_Set_Spreading_Factor(lora->sf);
	LoRa_Set_Pa_Boost(lora->pa_boost);
	LoRa_Set_Max_Output_Power(lora->max_power);
	LoRa_Set_Output_Power(lora->output_power);
	LoRa_Set_Lna_Gain(lora->lna_gain);
}

