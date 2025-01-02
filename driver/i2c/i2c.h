// TODO: abstraction

///*
 //* i2c.h
 //*
 //* Created: 2024-08-05 오후 3:12:45
 //*  Author: iot04
 //*/ 
//
//
//#ifndef I2C_H_
//#define I2C_H_
//
//#define F_CPU 16000000UL
//#include <avr/io.h>
//#include <util/delay.h>
//#include <util/delay.h>
//#include <stddef.h>
//#include <stdint.h>
//
//#define I2C_DDR DDRD
//#define I2C_SCL 0
//#define I2C_SDA 1
//
//
//void initI2c();
//void transmitByteOnI2c(uint8_t SLA_W, uint8_t data);
//void transmitDeviceAddress(uint8_t SLA_W);
//void startI2c();
//void transmitData(uint8_t data);
//void stopI2c();
//
//#endif /* I2C_H_ */
//
//
///*
//
//
//I2C ; https://en.wikipedia.org/wiki/I%C2%B2C
//[Pinout]
//SDA	Data Pin
//SCL	Clock Pin
//[Data] ★ 면접에 나옴! UART 등과의 비교.
//Protocol	Serial, half-duplex
//Width		1-bit (SDA) with separate clock (SCL)
//... I2C (Inter-Integrated Circuit; pronounced as “eye-squared-see” or “eye-two-see”), alternatively known as I2C or IIC, is a synchronous, multi-controller/multi-target (historically-termed as master/slave), ...
//... TWI (Two-Wire Interface) or TWSI (Two-Wire Serial Interface) is essentially the same bus implemented on various system-on-chip processors from Atmel and other vendors
//# Design
//# Physical layer
//# Addressing structure
//7-bit addressing
//10-bit addressing
//
//
//
//*/