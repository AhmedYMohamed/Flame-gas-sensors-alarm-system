/*
 * Microcontroller: ATmega32
 * Frequency: 8 MHz
 * Project: Fire & Gas Monitor with LED Alerts
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// --- LCD Pin Definitions (PORTB) ---
#define LCD_Dir  DDRB
#define LCD_Port PORTB
#define RS PB1
#define EN PB0

// --- LED Pin Definitions (PORTC) ---
#define LED_Dir  DDRC
#define LED_Port PORTC
#define RED_LED  PC0
#define GREEN_LED PC1

// --- Function Prototypes ---
void ADC_Init();
uint16_t ADC_Read(uint8_t channel);
void LCD_Init();
void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void LCD_String(char *str);
void LCD_Set_Cursor(unsigned char row, unsigned char col);
void LCD_Pulse();

int main(void)
{
    uint16_t fire_val, gas_val;
    char buffer[16];

    // 1. Setup I/O
    DDRA = 0x00;        // PORTA Input (Sensors)
    LCD_Dir = 0xF3;     // PORTB Output (LCD)
    
    // Set PC0 and PC1 as Output for LEDs
    LED_Dir |= (1 << RED_LED) | (1 << GREEN_LED) | (1 << PC2);
    
    // 2. Initialize Modules
    ADC_Init();
    LCD_Init();
    
    LCD_String("System Ready");
    _delay_ms(1000);
    LCD_Command(0x01); // Clear screen

    while(1)
    {
        // 3. Read Sensors
        fire_val = ADC_Read(0); // PA0
        gas_val  = ADC_Read(1); // PA1

        // 4. Check Conditions
        // Fire usually goes LOW when detected (< 700)
        // Gas usually goes HIGH when detected (> 20)
        
        if (fire_val < 700 || gas_val > 40)
        {
            // --- DANGER MODE ---
            
            // Red LED ON, Green LED OFF
            LED_Port |= (1 << RED_LED);
			LED_Port |= (1 << PC2);
            LED_Port &= ~(1 << GREEN_LED);
            
            LCD_Command(0x01); // Clear Screen to show alert clearly
            
            // Check specifically which one triggered the alarm
            if (fire_val < 700) {
                LCD_Set_Cursor(1, 1);
                LCD_String("FIRE DETECTED!");
            }
            
            if (gas_val > 40) {
                LCD_Set_Cursor(2, 1);
                LCD_String("GAS DETECTED!");
            }
        }
        else
        {
            // --- SAFE MODE ---
            
            // Red LED OFF, Green LED ON
			LED_Port &= ~(1<<PC2);
            LED_Port &= ~(1 << RED_LED);
            LED_Port |= (1 << GREEN_LED);
            
            // Print Values
            LCD_Command(0x01); // Clear Screen
            
            LCD_Set_Cursor(1, 1);
            sprintf(buffer, "Fire: %4u Safe", fire_val);
            LCD_String(buffer);

            LCD_Set_Cursor(2, 1);
            sprintf(buffer, "Gas : %4u Safe", gas_val);
            LCD_String(buffer);
        }

        _delay_ms(300); // Update speed
    }
}

// --- ADC Functions ---
void ADC_Init()
{
    ADMUX = (1 << REFS0); // AVCC as ref
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable, Prescaler 128
}

uint16_t ADC_Read(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

// --- LCD Functions ---
void LCD_Pulse()
{
    LCD_Port |= (1 << EN);
    _delay_us(1);
    LCD_Port &= ~(1 << EN);
    _delay_us(100);
}

void LCD_Send_Nibble(unsigned char data, unsigned char type)
{
    if(type) LCD_Port |= (1 << RS);
    else     LCD_Port &= ~(1 << RS);

    LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0);
    LCD_Pulse();
}

void LCD_Command(unsigned char cmnd)
{
    LCD_Send_Nibble(cmnd, 0);
    LCD_Send_Nibble(cmnd << 4, 0);
    _delay_ms(2);
}

void LCD_Char(unsigned char data)
{
    LCD_Send_Nibble(data, 1);
    LCD_Send_Nibble(data << 4, 1);
    _delay_us(50);
}

void LCD_Init()
{
    _delay_ms(20);
    LCD_Send_Nibble(0x30, 0);
    _delay_ms(5);
    LCD_Send_Nibble(0x30, 0);
    _delay_us(200);
    LCD_Send_Nibble(0x30, 0);
    LCD_Send_Nibble(0x20, 0);
    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Command(0x01);
}

void LCD_String(char *str)
{
    int i;
    for(i=0; str[i]!=0; i++) LCD_Char(str[i]);
}

void LCD_Set_Cursor(unsigned char row, unsigned char col)
{
    unsigned char cmd;
    if(row == 1) cmd = 0x80 + (col - 1);
    else         cmd = 0xC0 + (col - 1);
    LCD_Command(cmd);
}