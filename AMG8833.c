/*
 * AMG8833
 *
 *  Created on: Jan 2, 2023
 *      Author: Maulana Reyhan
 */

#include "AMG8833.h"

extern uint8_t AMG8833_ADDR;

extern I2C_HandleTypeDef hi2c2;

void amg8833_writeData(uint8_t reg, uint8_t data) {
  uint8_t txdata[2] = {reg, data};
  uint8_t status;
  status = HAL_I2C_Master_Transmit(&hi2c2, AMG8833_ADDR,
                                   txdata, sizeof(txdata), 10);
  if (status == HAL_OK) {
    return;
  }

  if (status == HAL_ERROR) {
    printf("HAL_I2C_Master_Transmit HAL_ERROR\r\n");
  } else if (status == HAL_TIMEOUT) {
    printf("HAL_I2C_Master_Transmit HAL_TIMEOUT\r\n");
  } else if (status == HAL_BUSY) {
    printf("HAL_I2C_Master_Transmit HAL_BUSY\r\n");
  } else {
    printf("Unknown status data %d", status);
  }

  uint32_t error = HAL_I2C_GetError(&hi2c2);
  if (error == HAL_I2C_ERROR_NONE) {
    return;
  } else if (error == HAL_I2C_ERROR_BERR) {
    printf("HAL_I2C_ERROR_BERR\r\n");
  } else if (error == HAL_I2C_ERROR_ARLO) {
    printf("HAL_I2C_ERROR_ARLO\r\n");
  } else if (error == HAL_I2C_ERROR_AF) {
    printf("HAL_I2C_ERROR_AF\r\n");
  } else if (error == HAL_I2C_ERROR_OVR) {
    printf("HAL_I2C_ERROR_OVR\r\n");
  } else if (error == HAL_I2C_ERROR_DMA) {
    printf("HAL_I2C_ERROR_DMA\r\n");
  } else if (error == HAL_I2C_ERROR_TIMEOUT) {
    printf("HAL_I2C_ERROR_TIMEOUT\r\n");
  }

  HAL_I2C_StateTypeDef state = HAL_I2C_GetState(&hi2c2);
  if (state == HAL_I2C_STATE_RESET) {
    printf("HAL_I2C_STATE_RESET\r\n");
  } else if (state == HAL_I2C_STATE_READY) {
    printf("HAL_I2C_STATE_RESET\r\n");
  } else if (state == HAL_I2C_STATE_BUSY) {
    printf("HAL_I2C_STATE_BUSY\r\n");
  } else if (state == HAL_I2C_STATE_BUSY_TX) {
    printf("HAL_I2C_STATE_BUSY_TX\r\n");
  } else if (state == HAL_I2C_STATE_BUSY_RX) {
    printf("HAL_I2C_STATE_BUSY_RX\r\n");
  } else if (state == HAL_I2C_STATE_LISTEN) {
    printf("HAL_I2C_STATE_LISTEN\r\n");
  } else if (state == HAL_I2C_STATE_BUSY_TX_LISTEN) {
    printf("HAL_I2C_STATE_BUSY_TX_LISTEN\r\n");
  } else if (state == HAL_I2C_STATE_BUSY_RX_LISTEN) {
    printf("HAL_I2C_STATE_BUSY_RX_LISTEN\r\n");
  } else if (state == HAL_I2C_STATE_ABORT) {
    printf("HAL_I2C_STATE_ABORT\r\n");
  } else if (state == HAL_I2C_STATE_TIMEOUT) {
    printf("HAL_I2C_STATE_TIMEOUT\r\n");
  } else if (state == HAL_I2C_STATE_ERROR) {
    printf("HAL_I2C_STATE_ERROR\r\n");
  }
}

void amg8833_readData(uint8_t reg, uint8_t *data, uint8_t len) {
  HAL_I2C_Master_Transmit(&hi2c2, AMG8833_ADDR, &reg, 1,
                          100);
  HAL_I2C_Master_Receive(&hi2c2, AMG8833_ADDR, data, len,
                         100);
}

void amg8833_setup(void){
	for(uint8_t i = 0; i <255; i++){
		if(HAL_I2C_IsDeviceReady(&hi2c2, i, 1, 10) == HAL_OK){
			AMG8833_ADDR = i;
			break;
		}
	}
	
	// Set Normal Mode
	amg8833_set_opr_mode(AMG8833_NORMAL_MODE);
	
	// Reset Init
	amg8833_reset_init();
	
	// Set Framerate to 10FPS
	amg8833_framerate_10();
}

// Get Power Mode
uint8_t amg8833_get_opr_mode(void){
	uint8_t buf;
  amg8833_readData(AMG8833_OPR_MODE, &buf, 1);
	return buf;
}

// Set Power Mode
void amg8833_set_opr_mode(uint8_t mode){
	amg8833_writeData(AMG8833_OPR_MODE, mode);
}

// Set Reset Flag
void amg8833_reset_flag(void){
	amg8833_writeData(AMG8833_RST, AMG8833_FLAG_RST);
}

// Set Reset Init
void amg8833_reset_init(void){
	amg8833_writeData(AMG8833_RST, AMG8833_INIT_RST);
}

// Set Frame Rate
void amg8833_framerate_1(void){
	amg8833_writeData(AMG8833_FPSC, AMG8833_FRAME_1);
}

// Set Frame Rate
void amg8833_framerate_10(void){
	amg8833_writeData(AMG8833_FPSC, AMG8833_FRAME_10);
}

// Get Interrupt Mode
void amg8833_get_int_mode(uint8_t data){
	amg8833_readData(AMG8833_INTC, &data, 1);
}

// Set Interrupt Mode
void amg8833_int_abs(void){
	uint8_t buf;
	amg8833_get_int_mode(buf);
	amg8833_writeData(AMG8833_INTC, (buf & ((AMG8833_INTMODE_ABSOLUTE << 1) | 0x01 )));
}

// Set Interrupt Mode
void amg8833_int_diff(void){
	uint8_t buf;
	amg8833_get_int_mode(buf);
	amg8833_writeData(AMG8833_INTC, ((buf | (AMG8833_INTMODE_DIFF << 1 ) | 0x01 )));
}

// Set Interrupt Mode
void amg8833_int_active(void){
	uint8_t buf;
	amg8833_get_int_mode(buf);
	amg8833_writeData(AMG8833_INTC, (buf | (AMG8833_INTEN_ACTIVE | 0x02)));
}

// Set Interrupt Mode
void amg8833_int_reactive(void){
	uint8_t buf;
	amg8833_get_int_mode(buf);
	amg8833_writeData(AMG8833_INTC, (buf | (AMG8833_INTEN_REACTIVE | 0x02)));
}

// Get Status System
amg8833_status_t amg8833_get_status_sys(void){
	amg8833_status_t handler;
	uint8_t buf;
	amg8833_readData(AMG8833_STAT, &buf, 1);
	handler.INTF = (buf >> 1) & 0x01;
	handler.OVF_IRS = (buf >> 2) & 0x01;
	handler.OVF_THS = (buf >> 3) & 0x01;
	return handler;
}

// Get Status System CLR
amg8833_status_clear_t amg8833_get_status_clr(void){
	amg8833_status_clear_t handler;
	uint8_t buf;
	amg8833_readData(AMG8833_SCLR, &buf, 1);
	handler.INTCLR = (buf >> 1) & 0x01;
	handler.OVS_CLR = (buf >> 2) & 0x01;
	handler.OVT_CLR = (buf >> 3) & 0x01;
	return handler;
}

// Set Status System CLR
void amg8833_set_status_clr(amg8833_status_clear_t data){
	uint8_t buf;
	buf = (data.INTCLR << 1) | (data.OVS_CLR << 2) | (data.OVT_CLR << 3);
	amg8833_writeData(AMG8833_SCLR, buf);
}

// Set MAMOD ON
void amg8833_MAMOD_on(void){
	amg8833_writeData(AMG8833_AVE, 0x20);
}

// Set MAMOD OFF
void amg8833_MAMOD_off(void){
	amg8833_writeData(AMG8833_AVE, 0x00);
}

// Get Interrupt Level Register
amg8833_interrupt_t amg8833_get_interrupt_reg(){
	amg8833_interrupt_t data;
	uint8_t buf[6];
	for(int i = 0; i<6;i++){
			amg8833_readData(AMG8833_INTHL + i, &buf[i], 1);
	}
	data.INTHL = buf[0];
	data.INTLH = buf[1];
	data.INTLL = buf[2];
	data.INTLH = buf[3];
	data.IHYSL = buf[4];
	data.IHYSH = buf[5];
	
	return data;
}

// Set Interrupt Level Register
void amg8833_set_interrupt_reg(amg8833_interrupt_t data){
	uint8_t buf[6];
	memcpy(buf, &data.INTHL, 1);
	memcpy(buf + 1, &data.INTHH, 1);
	memcpy(buf + 2, &data.INTLL, 1);
	memcpy(buf + 3, &data.INTLH, 1);
	memcpy(buf + 4, &data.IHYSL, 1);
	memcpy(buf + 5, &data.IHYSH, 1);
	
	for(int i = 0; i < 6; i++){
		amg8833_writeData(AMG8833_INTHL + i, buf[i]);
	}
}

// Get thermistor value
amg8833_thermistor_t amg8833_get_thermistor(void){
	amg8833_thermistor_t handler;
	uint8_t buf[2];
	amg8833_readData(AMG8833_TTHL, &buf[0], 1);
	amg8833_readData(AMG8833_TTHH, &buf[1], 1);
	handler.val = ((double)(((buf[1] & 0x07) << 8) | buf[0]))*0.0625;
	if((buf[1] & 0x08) == 1){
		handler.val = handler.val*(-1.0);
	}
	return handler;
}

// Get Interrupt Table
amg8833_interrupt_table_t amg8833_get_int_table(void){
	amg8833_interrupt_table_t handler;
	uint8_t buf[8];
	for(int i = 0; i < 8; i++){
		amg8833_readData(AMG8833_INT0 + i, &buf[i], 1);
		for(int j = 0; j < 8; j++){
			handler.pix[((i*8)+j)] = (buf[i] >> j) & 0x01;
		}
	}
	return handler;
}

// Get Temperature
amg8833_temperature_table_t amg8833_get_temp(void){
	amg8833_temperature_table_t handler;
	uint8_t buf[128];
	for(int i = 0; i < 128; i = i+2){
		amg8833_readData((AMG8833_T01L+i), &buf[i], 1);
		amg8833_readData((AMG8833_T01L+i+1), &buf[(i+1)], 1);
		handler.pix[i/2] = ((double) (((buf[i+1] & 0x07) << 8)| buf[i]))*0.25;
		if((buf[i+1] >> 3 & 0x01) == 1){
			handler.pix[i/2] = handler.pix[i/2]*(-1);
		}
	}
	return handler;
}
