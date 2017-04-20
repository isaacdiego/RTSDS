#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Function definition
void init_USART(void);
unsigned char receive(void);
void send( unsigned char data);

int main (void){
  //Initiates some variables
  int pin = 7;
  unsigned long duration, T = 100, ta, t1;  
  unsigned char byte_envio,byte_recebimento;

  init_USART();
  pinMode(pin, INPUT);
  
  while(1){
    //Counts the amount of time the pulse stays on HIGH
    duration = pulseIn(pin, HIGH)/1000;
    
    //Saturates the counted value, in case it exceeds the highest configured value for the cycle
    if (duration/T > 1)
      duration = 100;
    
    //Translates the long value into a char to send to the main component
    byte_envio = (floor(((float)duration/T) * 255));
    
    //Sends throught the serial port
    send (byte_envio);
  }
  
  return 0;
}

void init_USART(void){
 UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
 UBRR0L = (uint8_t)(BAUD_PRESCALLER);
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C = (3<<UCSZ00);
}
unsigned char receive(void){
 
 while(!(UCSR0A & (1<<RXC0)));
 return UDR0;
 
}
void send( unsigned char data){
 
 while(!(UCSR0A & (1<<UDRE0)));
 UDR0 = data;
 
}
