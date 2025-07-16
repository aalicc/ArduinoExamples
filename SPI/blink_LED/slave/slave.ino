#include <SPI.h>

volatile byte received_data = 0;
const int MISO_slave = PB6;

void setup() {
  pinMode(MISO_slave, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  SPCR |= _BV(SPE);              
  SPI.attachInterrupt();        // Enable interrupt on SPI transfer
}

ISR(SPI_STC_vect) {
  received_data = SPDR;         // Read received byte
}

void loop() {
  
  if (received_data == 0x01) {
    digitalWrite(LED_BUILTIN, HIGH); // Turn ON LED
  } else if (received_data == 0x00){
    digitalWrite(LED_BUILTIN, LOW);  // Turn OFF LED
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);  // Turn OFF LED
  }
}
