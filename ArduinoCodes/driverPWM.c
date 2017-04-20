#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Definição de funções
void init_USART(void);
unsigned char receive(void);
void send( unsigned char data);



int main (void){
  int pin = 7;
  unsigned long duration, T = 100, ta, t1;  
  unsigned char byte_envio,byte_recebimento;

  init_USART();
  pinMode(pin, INPUT);
  
  //ta = millis();
  while(1){
    duration = pulseIn(pin, HIGH)/1000;
    //t1 = millis();
    //T = t1 - ta;
    //ta = t1;
    
    if (duration/T > 1)
      duration = 100;
    byte_envio = (floor(((float)duration/T) * 255));
    
    //Envio pela porta serial
    send (byte_envio);
    //Implementar rotina para reenvio no caso de erro
    //Necessidade de aguardar um certo tempo para se ter a confirmação
    //byte_recebimento = receive ();
    
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
