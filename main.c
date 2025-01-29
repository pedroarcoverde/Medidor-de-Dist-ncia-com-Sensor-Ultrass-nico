#include <msp430.h>
#include <stdio.h>

// Definições dos pinos do HC-SR04
#define TRIG_PIN BIT0  // P1.0
#define ECHO_PIN BIT1  // P1.1

// Definições dos pinos do LCD
#define RS_PIN BIT0    // P2.0
#define E_PIN BIT1     // P2.1
#define DATA_PINS (BIT2 | BIT3 | BIT4 | BIT5)  // P2.2, P2.3, P2.4, P2.5

// Função para delay em microssegundos
void delay_us(unsigned int us) {
    while (us--) {
        __delay_cycles(1);  // Ajuste conforme o clock do MSP430
    }
}

// Função para enviar comandos ao LCD
void lcd_command(unsigned char cmd) {
    P2OUT &= ~RS_PIN;  // RS = 0 (modo comando)
    P2OUT = (P2OUT & ~DATA_PINS) | ((cmd >> 4) & DATA_PINS);  // Envia os 4 bits mais significativos
    P2OUT |= E_PIN;    // Enable HIGH
    delay_us(10);      // Aguarda um curto período
    P2OUT &= ~E_PIN;   // Enable LOW
    delay_us(10);      // Aguarda um curto período

    P2OUT = (P2OUT & ~DATA_PINS) | (cmd & DATA_PINS);  // Envia os 4 bits menos significativos
    P2OUT |= E_PIN;    // Enable HIGH
    delay_us(10);      // Aguarda um curto período
    P2OUT &= ~E_PIN;   // Enable LOW
    delay_us(10);      // Aguarda um curto período
}

// Função para enviar dados ao LCD
void lcd_data(unsigned char data) {
    P2OUT |= RS_PIN;   // RS = 1 (modo dados)
    P2OUT = (P2OUT & ~DATA_PINS) | ((data >> 4) & DATA_PINS);  // Envia os 4 bits mais significativos
    P2OUT |= E_PIN;    // Enable HIGH
    delay_us(10);      // Aguarda um curto período
    P2OUT &= ~E_PIN;   // Enable LOW
    delay_us(10);      // Aguarda um curto período

    P2OUT = (P2OUT & ~DATA_PINS) | (data & DATA_PINS);  // Envia os 4 bits menos significativos
    P2OUT |= E_PIN;    // Enable HIGH
    delay_us(10);      // Aguarda um curto período
    P2OUT &= ~E_PIN;   // Enable LOW
    delay_us(10);      // Aguarda um curto período
}

// Função para inicializar o LCD
void lcd_init() {
    delay_us(15000);   // Aguarda 15 ms para inicialização
    lcd_command(0x02); // Modo 4 bits
    lcd_command(0x28); // Configura LCD 2 linhas, 5x7 pontos
    lcd_command(0x0C); // Liga o display, sem cursor
    lcd_command(0x06); // Incrementa cursor, sem shift
    lcd_command(0x01); // Limpa o display
    delay_us(2000);    // Aguarda 2 ms
}

// Função para escrever uma string no LCD
void lcd_print(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

// Função para medir a distância com o HC-SR04
unsigned int measure_distance() {
    unsigned int duration = 0;

    // Envia pulso de 10 µs no TRIG
    P1OUT |= TRIG_PIN;
    delay_us(10);
    P1OUT &= ~TRIG_PIN;

    // Espera o ECHO ficar em HIGH
    while (!(P1IN & ECHO_PIN));

    // Mede o tempo que ECHO fica em HIGH
    while (P1IN & ECHO_PIN) {
        duration++;
        delay_us(1);  // Ajuste conforme a precisão desejada
    }

    // Calcula a distância em cm (velocidade do som ~343 m/s)
    return (duration * 343) / (2 * 10000);  // Ajuste conforme o clock
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // Desabilita Watchdog Timer

    // Configura pinos do HC-SR04
    P1DIR |= TRIG_PIN;  // TRIG como saída
    P1DIR &= ~ECHO_PIN; // ECHO como entrada
    P1OUT &= ~TRIG_PIN; // TRIG em LOW

    // Configura pinos do LCD
    P2DIR |= RS_PIN | E_PIN | DATA_PINS;  // Configura como saída
    lcd_init();  // Inicializa o LCD

    while (1) {
        unsigned int distance = measure_distance();

        // Exibe a distância no LCD
        lcd_command(0x01);  // Limpa o display
        lcd_command(0x80);  // Posiciona o cursor na primeira linha
        lcd_print("Distancia:");
        lcd_command(0xC0);  // Posiciona o cursor na segunda linha
        char buffer[16];
        sprintf(buffer, "%u cm", distance);  // Formata a distância
        lcd_print(buffer);

        __delay_cycles(1000000);  // Aguarda 1 segundo antes de medir novamente
    }
}
