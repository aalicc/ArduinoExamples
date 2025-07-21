#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

#define SLA_W (0x3F << 1)		                          //I2C device address & write bit (shifted left => 0x7E)

void I2C_setup(){
	TWSR = 0x00;						  // 
	TWBR = 0x48;						  // bit rate = 100kHz for 16MHz clock
	TWCR = (1 << TWEN);					  // enable TWI
}

void I2C_start(){
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);	  // 
	while (!(TWCR & (1 << TWINT)));				  // wait for TWINT flag
}

void I2C_stop(){
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);  // Send STOP
	_delay_ms(1);
}

void I2C_send(uint8_t some_data_to_i2c_device){
	TWDR = some_data_to_i2c_device;
	TWCR = (1 << TWEN) | (1 << TWINT);			  // start transmission
	while (!(TWCR & (1 << TWINT)));				  // wait for TWINT flag
}

int main()
{
  I2C_setup();

  while (1){
    I2C_start();
    I2C_send(SLA_W);
    I2C_send(0x00);                                  		//sends start bit (depends on device)
    I2C_send(100);                                   		//sends user-specified data, integer '100' in this case
    _delay_ms(100);
  }
I2C_stop();
}

