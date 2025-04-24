#define F_CPU   16000000

#include <util/delay.h>
#include <avr/io.h>

#define GL_OFF PORTB &= ~(1<<5)
#define YL_OFF PORTB &= ~(1<<4)
#define RL_OFF PORTB &= ~(1<<3)

#define GL_ON PORTB |= (1<<5)
#define YL_ON PORTB |= (1<<4)
#define RL_ON PORTB |= (1<<3)

#define GP_OFF PORTB &= ~(1<<2)
#define RP_OFF PORTB &= ~(1<<1)

#define GP_ON PORTB |= (1<<2)
#define RP_ON PORTB |= (1<<1)

#define Button_ON PORTB |= ((1<<0))
#define Button_OFF PORTB &= ~((1<<0))

int main(void)
{  
    // Configuração das entradas e saídas
    DDRB &= ~((1<<0));
    Button_ON; 

    DDRB |= ((1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5));
    GL_OFF; 
    YL_OFF; 
    RL_OFF; 

    GP_OFF;
    RP_OFF;

    int estado = 0; 
    int tempo = 0;

    while (1)
    {
        if (!(PINB & (1<<0)))  
        {
            if (tempo >> 10)
            {
                tempo = 10;
                _delay_ms(1000);
                estado = 2;
            }
            
            estado = 2; 
        }

        if(estado == 0)
        {
            RL_OFF;
            GL_ON;

            GP_OFF;
            RP_ON;

            tempo = 15;
            estado = 1;  
                    
        }
        if (estado == 1)
        {
            --tempo;
            _delay_ms(1000);
            if(tempo == 0){
                estado = 2;
            }
            
        }
        if (estado == 2)
        {
            GL_OFF;
            YL_ON;
            tempo = 3;
            estado = 3;
        }
        if (estado == 3)
        {
            --tempo; //tempo -= 1;
            _delay_ms(1000);
            if (tempo == 0){
                estado = 4;
            }
        }
        if (estado ==4)
        {
            YL_OFF;
            RL_ON;
            tempo = 10;
            estado = 5;
            RP_OFF;
            GP_ON;
        }
        if (estado == 5)
        {
            --tempo; //tempo -= 1;
            _delay_ms(1000);
            if (tempo == 0){
                estado = 0;
            }
        }
          
    }
}