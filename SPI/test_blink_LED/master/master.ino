#include <SPI.h>

const int slave_select_master = PB4;

void setup() {
  pinMode(slave_select_master, OUTPUT);
  digitalWrite(slave_select_master, HIGH);
  // initialize SPI:
  SPI.begin();
}

void loop() {     

  digitalWrite(slave_select_master, LOW);
  delayMicroseconds(10);  
  SPI.transfer(0x01);       //LED ON byte
  //SPI.transfer(0x00);     //LED OFF byte
  SPI.endTransaction(); 
  digitalWrite(slave_select_master, HIGH);
  delay(500);                               

}
