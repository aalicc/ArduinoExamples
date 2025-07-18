#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

/*
SPI pins:
PB4:	SS	    Output
PB5:	MOSI        Output
PB6:	MISO        Input
PB7:	SCK         Output
*/

void SPI_master_setup(){
	DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7);		// PB4 (SS), PB5 (MOSI), PB7 (SCK) as outputs	
	PORTB |= (1 << PB4);					// PB4 (SS) HIGH
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);		// set to master mode: SPE (SPI Enable), MSTR (Master/ Slave Select), SPR0 (SPI Clock Rate Select 0)
}

void SPI_master_send(uint8_t data){				// data declared as an 8-bit unsigned integer 
	
	PORTB &= ~(1 << PB4);					// PB4 (SS) LOW	
	_delay_ms(1);
	
	SPDR = data;						// sends specified data; SPDR (SPI Data Register)
	
	while (!(SPSR & (1 << SPIF))){				// special function to wait for transmission complete
	}
PORTB |= (1 << PB4);						// PB4 (SS) HIGH	
}

int main(void)
{
	SPI_master_setup(); 					
	
	while (1){
	SPI_master_send(0x01);					// data to send
	_delay_ms(100);
	}

}
