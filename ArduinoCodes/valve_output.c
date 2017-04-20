#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Function definition
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);

int main (void){
  //Set up the parameter for serial communication
  USART_init();
  
  //Variables creation	
  float percentual_abertura;
  unsigned char byte_envio,byte_recebimento;
 
  //Enable the ADC and set the prescale of its counter to 64
  ADCSRA |= _BV(ADEN) | (1<<ADPS0) | (1<<ADPS1);

  //Set up the ADC to read the ADC0 input with external reference
  ADMUX |= 0b00000000;
  ADMUX &= 0b11110000;
  
  //Sets the pin 13 as an output
  pinMode(13, OUTPUT);
  
  //Main Loop
  while(1){  
    //Starts the A/D conversion and waits for it to finish
    ADCSRA |= _BV(ADSC);
    while(!(ADCSRA & _BV(ADIF)));
    
    //Calculates the variable percentual_abertura, which corresponds to the opening percentage of the valve based on the ADC obtained value
    percentual_abertura = (float)(ADC/512.0);
    if(percentual_abertura <= 1.0 || percentual_abertura >= 0){
      digitalWrite(13, HIGH);
    }else {
      digitalWrite(13, LOW);
    }
      
    //Translates the output value as an character to send via USART connection
    byte_envio = (unsigned char) floor(percentual_abertura * 255.0);
    
    //Sends the output value via the USART/serial port
    USART_send(byte_envio);

  }
  
  return 0;
}
void USART_init(void){
 UBRR0H = (uint8_t)(BAUD_PRESCALLER>>8);
 UBRR0L = (uint8_t)(BAUD_PRESCALLER);
 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
 UCSR0C = (3<<UCSZ00);
}
unsigned char USART_receive(void){
 
 while(!(UCSR0A & (1<<RXC0)));
 return UDR0;
 
}
void USART_send( unsigned char data){
 
 while(!(UCSR0A & (1<<UDRE0)));
 UDR0 = data;
 
}
