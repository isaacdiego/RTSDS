#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

//Definição de funções
void USART_init(void);
unsigned char USART_receive(void);
void USART_send( unsigned char data);




int main (void){
  //Configura os parametros para a comunicação serial
  USART_init();
  
  //Declaração de variáveis	
  float percentual_abertura;
  unsigned char byte_envio,byte_recebimento;

 //Habilita o ADC e seta o prescale do seu contador como 64*
  ADCSRA |= _BV(ADEN) | (1<<ADPS0) | (1<<ADPS1);

  //Configura o ADC para ler da entrada ADC0 com referencia externa
  ADMUX |= 0b00000000;
  ADMUX &= 0b11110000;
  
  //Pino 13 como saida
  pinMode(13, OUTPUT);
  
  while(1){  
    //Inicia a conversao A/D e aguarda a finalização
    ADCSRA |= _BV(ADSC);
    while(!(ADCSRA & _BV(ADIF)));
    
    //Calculo do percentual_abertura para a valvula com base no valor do ADC
    //percentual_abertura = (float)((ADC - 512)/512.0);
    percentual_abertura = (float)(ADC/512.0);
    if(percentual_abertura <= 1.0 || percentual_abertura >= 0){
      //percentual_abertura = 0.5;
      digitalWrite(13, HIGH);
    }else {
      digitalWrite(13, LOW);
    }
      
    
    //Adequando valor para envio
    byte_envio = (unsigned char) floor(percentual_abertura * 255.0);
    //byte_envio = (unsigned char) 128;
    
    //Envio pela porta serial
    USART_send(byte_envio);
    
    
    //Implementar rotina para reenvio no caso de erro
    //Necessidade de aguardar um certo tempo para se ter a confirmação
    //byte_recebimento = receive ();

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
