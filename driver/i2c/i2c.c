//#include "i2c.h"
//
//void initI2c(){
	//I2C_DDR |= 1<< I2C_SCL | 1 << I2C_SDA;
	//TWBR = 72;			// 100khz SCL
	//// TWBR = 32;		// 200khz SCL
	//// TWBR = 12;		// 400khz SCL
	//TWSR = 0;
//}
//
//void transmitByteOnI2c(uint8_t SLA_W, uint8_t data){
	//startI2c();
	//transmitDeviceAddress(SLA_W);
	//transmitData(data);
	//stopI2c();
//}
//void transmitDeviceAddress(uint8_t SLA_W){
	//// Load SLA_W into TWDR Register.
	//TWDR = SLA_W;
	//// Clear TWINT bit in TWCR to start transmission of address
	//TWCR = (1<<TWINT) | (1<<TWEN);
	//
	//// Wait for TWINT flag set.
	//// This indicates that the SLA+W has been transmitted, and ACK/NACK has been received.
	//while (!(TWCR & (1<<TWINT)));
//}
//
//void startI2c(){
	//// Send START condition
	//TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	//
	//// Wait for TWINT flag set.
	//// This indicates that the START condition has been transmitted
	//while (!(TWCR & (1<<TWINT)));
//}
//
//void transmitData(uint8_t data){
	//// Load DATA into TWDR Register.
	//TWDR = data;
	//// Clear TWINT bit in TWCR to start transmission of data.
	//TWCR = (1<<TWINT) | (1<<TWEN);
	//
	//// Wait for TWINT flag set.
	//// This indicates that the DATA has been transmitted, and ACK/NACK has been received.
	//while (!(TWCR & (1<<TWINT)));
//}
//void stopI2c(){
	//// Transmit STOP condition
	//TWCR = (1<<TWINT)|(1<<TWEN)| (1<<TWSTO);
//
//}
