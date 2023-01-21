/*
 * AMG8833
 *
 *  Created on: Jan 2, 2023
 *      Author: Maulana Reyhan Savero
 */

#ifndef AMG8833_H_
#define AMG8833_H_

#include "main.h"

#include <stdbool.h>

#define AMG8833_OPR_MODE 0x00
#define AMG8833_RST 0x01
#define AMG8833_FPSC 0x02
#define AMG8833_INTC 0x03
#define AMG8833_STAT 0x04
#define AMG8833_SCLR 0x05
#define AMG8833_AVE 0x07
#define AMG8833_INTHL 0x08
#define AMG8833_INTHH 0x09
#define AMG8833_INTLL 0x0A
#define AMG8833_INTLH 0x0B
#define AMG8833_IHYSL 0x0C
#define AMG8833_IHYSH 0x0D
#define AMG8833_TTHL 0x0E
#define AMG8833_TTHH 0x0F
#define AMG8833_INT0 0x10
#define AMG8833_INT7 0x17
#define AMG8833_T01L 0x80
#define AMG8833_T01H 0x81
#define AMG8833_T64L 0xFE
#define AMG8833_T64H 0xFF

// Power Mode
#define AMG8833_NORMAL_MODE 0x00
#define AMG8833_SLEEP_MODE 0x10
#define AMG8833_STANDBY_60 0x20
#define AMG8833_STANBY_10 0x21

// Reset
#define AMG8833_FLAG_RST 0x30
#define AMG8833_INIT_RST 0x3F

// Frame Rate
#define AMG8833_FRAME_1 0x01
#define AMG8833_FRAME_10 0x00

// Interrupt Control Register
#define AMG8833_INTMODE_ABSOLUTE 0x01
#define AMG8833_INTMODE_DIFF 0x00
#define AMG8833_INTEN_ACTIVE 0x01
#define AMG8833_INTEN_REACTIVE 0x00

// Status Register
typedef struct{
	uint8_t INTF;
	uint8_t OVF_IRS;
	uint8_t OVF_THS;
}amg8833_status_t;

typedef struct{
	uint8_t INTCLR;
	uint8_t OVS_CLR;
	uint8_t OVT_CLR;
}amg8833_status_clear_t;

// Moving Average Output Mode
#define AMG8833_MAMOD_ON 0x20
#define AMG8833_MAMOD_OFF 0x00

// Interrupt Register
typedef struct{
	uint8_t INTHL;
	uint8_t INTHH;
	uint8_t INTLL;
	uint8_t INTLH;
	uint8_t IHYSL;
	uint8_t IHYSH;
}amg8833_interrupt_t;

// Thermistor Temperature
typedef struct{
	double val;
}amg8833_thermistor_t;

// Interrupt Table
typedef struct{
	uint8_t pix[64];
}amg8833_interrupt_table_t;

// Temperature Table
typedef struct{
	double pix[64];
}amg8833_temperature_table_t;

void amg8833_writeData(uint8_t reg, uint8_t data);
void amg8833_readData(uint8_t reg, uint8_t *data, uint8_t len);
bool amg8833_setup(I2C_HandleTypeDef *i2cHandler);

// Get Power Mode
uint8_t amg8833_get_opr_mode(void);

void amg8833_set_opr_mode(uint8_t mode);

void amg8833_reset_flag(void);

// Set Reset Init
void amg8833_reset_init(void);

// Set Frame Rate
void amg8833_framerate_1(void);

// Set Frame Rate
void amg8833_framerate_10(void);

// Get Interrupt Mode
void amg8833_get_int_mode(uint8_t data);

// Set Interrupt Mode
void amg8833_int_abs(void);

// Set Interrupt Mode
void amg8833_int_diff(void);

// Set Interrupt Mode
void amg8833_int_active(void);

// Set Interrupt Mode
void amg8833_int_reactive(void);

// Get Status System
amg8833_status_t amg8833_get_status_sys(void);

// Get Status System CLR
amg8833_status_clear_t amg8833_get_status_clr(void);

// Set Status System CLR
void amg8833_set_status_clr(amg8833_status_clear_t data);

// Set MAMOD ON
void amg8833_MAMOD_on(void);

// Set MAMOD OFF
void amg8833_MAMOD_off(void);

// Get Interrupt Level Register
amg8833_interrupt_t amg8833_get_interrupt_reg(void);

// Set Interrupt Level Register
void amg8833_set_interrupt_reg(amg8833_interrupt_t data);

// Get thermistor value
amg8833_thermistor_t amg8833_get_thermistor(void);

// Get Interrupt Table
amg8833_interrupt_table_t amg8833_get_int_table(void);

// Get Temperature
amg8833_temperature_table_t amg8833_get_temp(void);
#endif 
