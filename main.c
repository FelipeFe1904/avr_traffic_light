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


char bp(void)
{
    return ( (PINB & (1<<0) ? 0 : 1 ) ); // Considerando botão com pull-up interno e pressionado = LOW
}

int main(void)
{
    int tempo = 0;

    // Configuração dos pinos como saída ou entrada
    DDRB |= (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5); // Saídas
    DDRB &= ~(1<<0); // Pino do botão como entrada

    // Habilita pull-up interno para botão
    PORTB |= (1<<0);

    while(1)
    {
        _delay_ms(1);
        tempo++;

        if(tempo >= 60000)
        {
            tempo = 0;
        }

        GL_OFF; YL_OFF; RL_OFF;
        GP_OFF; RP_OFF;

        if(tempo < 42000)
        {
            if(bp() && tempo < 32000)
            {
                tempo = 32000;
            }
            GL_ON;
            RP_ON;

            YL_OFF;
            RL_OFF;
            GP_OFF;
        }
        else if (tempo < 47000)
        {
            YL_ON;
            RP_ON;

            GL_OFF;
            RL_OFF;

            GP_OFF;
        }
        else 
        {
            RL_ON;
            GP_ON;

            GL_OFF;
            YL_OFF;

            RP_OFF;
        }
    }
}
