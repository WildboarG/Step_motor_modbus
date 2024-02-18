#ifndef __MODBUS_H
#define __MODBUS_H
#include "stdio.h"
#include "stdint.h"

extern int16_t PwmNum;
extern int16_t modbus_virtual_register[2];
void modbus_service(void);
void modbus_04_function(void);
void modbus_06_function(void);
void modbus_16_function(void);
void modbus_send_data(uint8_t *buff,uint8_t len);


unsigned int CRC16(unsigned char *puchMsg,  unsigned char usDataLen);
uint8_t Compare_Register(int16_t *register_value,int16_t angle);
#endif
