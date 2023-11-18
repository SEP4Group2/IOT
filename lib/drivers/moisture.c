/**
 * @file moisture.c
 * @brief Moisture sensor driver implementation for ATmega2560
 *
 * This file provides the implementation for initializing and reading the value from a moisture sensor
 * connected to pin PK1 (ADC9) on the ATmega2560.
 *
 * @author YOUR NAME
 * @date October 2023
 */

#include "moisture.h"
#include "includes.h"

/**
 * @brief Initialize ADC for moisture sensor
 *
 * This function initializes the ADC to read values from the moisture sensor connected to pin PK1 (ADC9).
 */
/**
 * @brief Initialize ADC for moisture sensor
 *
 * This function initializes the ADC to read values from the moisture sensor connected to pin PF5 (ADC5).
 */

// TODO -this is a definition for used only to pass the testing, need to be removed/testes with the real sensor
#define MUX0 1
#define MUX2 2
#define ADC5D 5
// TODO until here -remove 

void moisture_init(void) {
    // Set reference voltage to AVCC and left adjust ADC result
    // The  MUX1:5 should be set to 10000 for choosing ADC8, which ius placed on PK0 (look at page 283)
    //ADMUX = (1 << REFS0);//|(1<<MUX1);
    //ADCSRB = (1<<MUX5);


//ADC5 for moisture Sensor Analog
    ADMUX = (1 << REFS0)|(1<<MUX0)|(1<<MUX2);//|(1<<MUX1);
    ADCSRB = 0;

    // Enable ADC and set prescaler to 64 (16MHz/128 = 125kHz)
    // ADC must operate between 50kHz and 200kHz for its full 10-bit resolution
   ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1)| (1 << ADPS0);
}

/**
 * @brief Read value from uv sensor
 *
 * This function reads the ADC value from the uv sensor connected to pin PK1 (ADC9).
 *
 * @return 10-bit ADC value read from the uv sensor
 */
uint16_t moisture_read(void) {

     ADMUX = (1 << REFS0)|(1<<MUX0)|(1<<MUX2);//|(1<<MUX1);
    ADCSRB = 0;

uint32_t timeout = 1000;//if 2cc for incrementing and evaluation the timeout is 1ms
    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete
    while ((ADCSRA & (1 << ADSC))&& timeout > 0){timeout--;};

    // Read the 10-bit ADC value
    // ADCL must be read first, then ADCH
    uint16_t adc_value = ADCL;
    adc_value |= (ADCH << 8);

    return adc_value;
}