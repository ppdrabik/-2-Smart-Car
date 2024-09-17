#include "LoRa.h"

static void SPI_Write_8(uint8_t data);
static uint8_t SPI_Receive_8(uint8_t data);

static rx_buffer_s rx_buffer;

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
	if(set_rest == SET)
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
  	if(set_rest == SET)
  	{
		SET_BIT(read_value, 1<<7);
  	}
  	else
  	{
    	CLEAR_BIT(read_value, 1<<7);
  	}
  	LoRa_Write(ADDR_REGPACONFIG, read_value);
}


void LoRa_Set_Max_Output_Power(uint8_t value)
{
	if(value <= 7)
	{
		uint8_t read_value = LoRa_Receive(ADDR_REGPACONFIG);
		SET_BITS(read_value, (value)<<4);
		LoRa_Write(ADDR_REGPACONFIG, read_value);
	}
}


void LoRa_Set_Output_Power(uint8_t value)
{
	if(value <= 15)
	{
		uint8_t read_value = LoRa_Receive(ADDR_REGPACONFIG);
		SET_BITS(read_value, value);
		LoRa_Write(ADDR_REGPACONFIG, read_value);
	}

}


void LoRa_Set_Lna_Gain(uint8_t value)
{
	if(value <= 7)
	{
		uint8_t read_value = LoRa_Receive(ADDR_REGLNA);
		SET_BITS(read_value, (value)<<5);
		LoRa_Write(ADDR_REGLNA, read_value);
	}
}


void LoRa_Init(lora_s *lora)
{
	LoRa_Mode(SLEEP);
	/* Set LoRa Mode */
	LoRa_Write(ADDR_REGOPMODE, 0x88);		
	LoRa_Set_Bandwidth(lora->bandwidth);
	LoRa_Set_Spreading_Factor(lora->sf);
	LoRa_Set_Pa_Boost(lora->pa_boost);
	LoRa_Set_Max_Output_Power(lora->max_power);
	LoRa_Set_Output_Power(lora->output_power);
	LoRa_Set_Lna_Gain(lora->lna_gain);
}


void Lora_Init_Receive()
{
	uint8_t fifo_current_address = 0;

	/* Map Pin DIO0 for RX done interrupt */
    LoRa_Write(ADDR_REGDIOMAPPING1, 0x00);  
	/* Clear interrupts flags */
    LoRa_Write(ADDR_REGIRQFLAGS, 0xFF);    
	/* CRC only on TX side in Explicit mode */
	LoRa_Set_CRC(false);					
	LoRa_Mode(STDBY);
	fifo_current_address = LoRa_Receive(ADDR_REGFIFORXBASEADDR);	
	LoRa_Write(ADDR_REGFIFOADDPTR, fifo_current_address);
	LoRa_Mode(RXCONTINUOUS);
}


void LoRa_Recieve_8(int8_t *data_buffer)
{
	uint8_t bytes_received = LoRa_Receive(ADDR_REGRXNBBYTES);
	for (uint8_t i = 0; i < bytes_received; i++)
	{
		/* Write data to FIFO. Pointer increment itself */
		data_buffer[i] = LoRa_Receive(ADDR_REGFIFO);     			
	}
	/* Clear interrupts flags */
	LoRa_Write(ADDR_REGIRQFLAGS, 0xFF);
}


void LoRa_Init_Transmit()
{
	/* Map Pin DIO0 for interrupt when TX done */
    LoRa_Write(ADDR_REGDIOMAPPING1, 0x40);
	/* Clear interrupts flags */
    LoRa_Write(ADDR_REGIRQFLAGS, 0xFF);     
    LoRa_Set_CRC(true); 					
}


void LoRa_Transmit_8(uint8_t *data, uint8_t length)
{
	uint8_t fifo_current_address = 0;
	LoRa_Mode(STDBY);
	/* Read pointer from where data to Tx will be stored */
	fifo_current_address = LoRa_Receive(ADDR_REGFIFOTXBASEADDR);
	/* Write address of pointer */
	LoRa_Write(ADDR_REGFIFOADDPTR, fifo_current_address);       
	LoRa_Write(ADDR_REGPAYLOADLENGTH, length);                  
	for (uint8_t i = 0; i < length; i++)
	{
		LoRa_Write(ADDR_REGFIFO, data[i]);                      
	}
	LoRa_Mode(TX);
}

void LoRa_It_Rx_Callback(void)
{
	LoRa_Recieve_8(rx_buffer.data);
}

const rx_buffer_s *LoRa_Get_Buffer(void)
{
	return &rx_buffer;
}