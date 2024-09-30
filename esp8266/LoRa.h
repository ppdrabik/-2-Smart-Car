#ifndef SRC_LORA_H_
#define SRC_LORA_H_

#include <stdint.h>
#include <SPI.h>
#include <stdbool.h>

#define NSS_PIN_HIGH 	digitalWrite(D1, HIGH);
#define NSS_PIN_LOW		digitalWrite(D1, LOW);


#define CLEAR_BIT(REG, MASK)    ((REG) &= ~(MASK))
#define SET_BIT(REG, MASK)      ((REG) |= (MASK))
#define CLEAR_BITS(REG, MASK)   ((REG) &= ~(MASK))
#define SET_BITS(REG, MASK)     ((REG) |= (MASK))

#define RX_BUFFER_SIZE 2

#define ADDR_REGFIFO 0x00
#define ADDR_REGOPMODE 0x01
#define ADDR_REGFRMSB 0x06
#define ADDR_REGFRMID 0x07
#define ADDR_REGFRLSB 0x08
#define ADDR_REGPACONFIG 0x09
#define ADDR_REGPARAMP 0x0A
#define ADDR_REGOCP 0x0B
#define ADDR_REGLNA 0x0C
#define ADDR_REGFIFOADDPTR 0x0D
#define ADDR_REGFIFOTXBASEADDR 0x0E
#define ADDR_REGFIFORXBASEADDR 0x0F
#define ADDR_REGFIFORXCURRENTADDR 0x10
#define ADDR_REGIRQFLAGS 0x12
#define ADDR_REGRXNBBYTES 0x13
#define ADDR_REGPKTRSSIVALUE 0x1A
#define ADDR_REGMODEMCONFIG1 0x1D
#define ADDR_REGMODEMCONFIG2 0x1E
#define ADDR_REGMODEMSTAT 0x18
#define ADDR_REGSYMBTIMEOUTL 0x1F
#define ADDR_REGPREAMBLEMSB 0x20
#define ADDR_REGPREAMBLELSB 0x21
#define ADDR_REGPAYLOADLENGTH 0x22
#define ADDR_REGDIOMAPPING1 0x40
#define ADDR_REGDIOMAPPING2 0x41
#define ADDR_REGVERSION 0x42
#define ADDR_REGRSSIVALUE 0x1B

typedef enum
{
	SLEEP = 0x00,
	STDBY = 0x01,
	FSTX = 0x02,
	TX = 0x03,
	FSRX = 0x04,
	RXCONTINUOUS = 0x05,
	RXSINGLE = 0x06,
	CAD = 0x07
} mode_e;

typedef enum
{
	khz_7_8,
	khz_10_4,
	khz_15_7,
	khz_20_8,
	khz_31_25,
	khz_41_7,
	khz_62_5,
	khz_125,
	khz_250,
	khz_500
} bandwidth_e;

typedef enum
{
	CR_4_5 = 0x01,
	CR_4_6,
	CR_4_7,
	CR_4_8,
} coding_rate_e;

typedef enum
{
	SF_6 = 0x06,
	SF_7,
	SF_8,
	SF_9,
	SF_10,
	SF_11,
	SF_12,
} spreading_factor_e;

typedef struct
{
	bandwidth_e bandwidth;
	spreading_factor_e sf;
	bool pa_boost;
	uint8_t max_power;
	uint8_t output_power;
	uint8_t lna_gain;
} lora_s;

typedef struct
{
	int8_t data[RX_BUFFER_SIZE];
} rx_buffer_s;

void LoRa_Write(uint8_t reg_address, uint8_t reg_value);
uint8_t LoRa_Receive(uint8_t reg_address);
void LoRa_Mode(mode_e mode);
void LoRa_Set_Bandwidth(bandwidth_e bandwidth);
void LoRa_Set_Coding_Rate(coding_rate_e coding_rate);
void LoRa_Set_Spreading_Factor(spreading_factor_e SF);
void LoRa_Set_CRC(bool set_rest);
void LoRa_Set_Pa_Boost(bool set_rest);
void LoRa_Set_Max_Output_Power(uint8_t value);
void LoRa_Set_Output_Power(uint8_t value);
void Lora_Set_Lna_Gain(uint8_t value);
void LoRa_Init(lora_s *lora);
void Lora_Init_Receive();
void LoRa_Recieve_8(int8_t *data_buffer);
void LoRa_Init_Transmit();
void LoRa_Transmit_8(int8_t *data, uint8_t length);
void LoRa_It_Rx_Callback(void);
const rx_buffer_s *LoRa_Get_Buffer(void);

#endif /* SRC_LORA_H_ */
