/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

uint16 adc_value;
float time = 0.0;
char tstr[16];

float M = 450.0; // Vehicle mass in Kg
float K = 1.0; // Seeming mass increase 
float RO = 1.18; // Air density
float CD = 0.51; // Aerodynamic friction coefficient
float Afr = 2.4; // Frontal Area in m^2
float C0 = 0.015; // Constant
float C1 = 0.0; // Constant
float G = 9.81; // Gravity acceleration
float R = 0.26; // Wheel radius
float v_max = 150.0; // Maximum car speed

volatile float tm = 1000.0; // Motor traction
volatile float v = 0.0; // Car velocity

volatile float displayedData = 0;
volatile unsigned int output_voltage = 0;

float T_INCR = 0.1; // Time increment: 100ms

volatile float it = 0.0;
volatile float alpha = 0.0;
	
/*Defining created functions*/
int sgn(float x);
float vehicle_mod(float tm, float theta, float xAnt);
void init(void);

CY_ISR(sleep){
	//INICIA O PROCESSAMENTO
	PINO_PROCESSAMENTO_Write( 1 );
	
	// ESCREVE NO DA
	MSG_1_SetValue( (unsigned int) output_voltage);
	
	// ESPERA PELA LEITURA DOS ADs
	MAD_1_StartConvert();
	MAD_1_IsEndConversion(MAD_1_WAIT_FOR_RESULT);
	MAD_2_StartConvert();
	MAD_2_IsEndConversion(MAD_2_WAIT_FOR_RESULT);
	
	// CONVERTE O VALOR INTEIRO LIDO EM VALOR COM UNIDADE
	tm = ((float) MAD_1_GetResult16())*2000.0/4096.0; //TM MAX: 2000.0 N*M
	alpha = ((float) MAD_2_GetResult16())*(PI/4.0)/4096.0; // ALFA MAX: PI/4 RAD
	
	// CALCULA O VALOR DA ALTURA
	v = vehicle_mod(tm, alpha, v);
	displayedData = v;
	output_voltage = (unsigned int) displayedData*254.0/v_max;
	if (output_voltage>254){
		output_voltage = 254;
	}
		
	it += T_INCR;
	
	// FIM DO PROCESSAMENTO
	PINO_PROCESSAMENTO_Write( 0 );
}

void init(){
	LCD_Start();
	MSG_1_Start();
	MAD_1_Start();
	MAD_2_Start();
	isr_1_Start();
	isr_1_SetVector(sleep);
	Timer_Start();
}

void main()
{
	/* Place your initialization/startup code here (e.g. MyInst_Start()) */
	init();
	CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
		// IMPRIMINDO O TEMPO
		//LCD_ClearDisplay();
		//LCD_Position(0u, 0u);
	    //LCD_PrintString("TIME:");
		//sprintf(tstr, "%.2f", it );
		//LCD_Position(0u, 5u);
		//LCD_PrintString(tstr);
		
		// IMPRIMINDO O TORQUE
		LCD_Position(0u, 0u);
	    LCD_PrintString("TM:");
		sprintf(tstr, "%.2f", tm );
		LCD_Position(0u, 3u);
		LCD_PrintString(tstr);
		
		// IMPRIMINDO A VELOCIDADE
		LCD_Position(1u, 0u);
	    LCD_PrintString("V:");
		LCD_Position(1u, 2u);
		sprintf(tstr, "%.2f", displayedData );
		LCD_PrintString(tstr);
		
		// IMPRIMINDO O ALFA
		LCD_Position(0u, 9u);
	    LCD_PrintString("A:");
		sprintf(tstr, "%.2f", alpha );
		LCD_Position(0u, 11u);
		LCD_PrintString(tstr);
		
	}
}

float vehicle_mod(float tm, float theta, float xAnt){
	
	float fd = sgn(xAnt)*(0.5*RO*CD*Afr*pow(xAnt,2)); // Aerodynamic drag
	float fr = sgn(xAnt)*(M*G*(C0 + C1*pow(xAnt,2))); // Rolling resistance
	float fg = M*G*sin(theta); // Gravitational friction
	float fa = fd + fr + fg;
	float ft = tm/R;
	
	float x_dot = (ft - fa)/(M*K);
	float x = xAnt + x_dot*T_INCR;
	
	return x;
}

/*Sign function*/
int sgn(float x) {
    return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

/* [] END OF FILE */
