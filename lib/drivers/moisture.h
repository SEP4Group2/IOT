/**
 * @file moisture.h
 * @brief Moisture sensor driver for ATmega2560
 *
 * This file provides the API for initializing and reading the value from a moisture sensor
 * connected to pin PK1 (ADC9) on the ATmega2560.
 *
 * @author Your Name
 * @date September 2023
 */

#pragma once

#include <stdint.h>

/**
 * @brief Initialize ADC for moisture sensor
 *
 * This function initializes the ADC to read values from the moisture sensor connected to pin PK1 (ADC9).
 */
void moisture_init(void);

/**
 * @brief Read value from moisture sensor
 *
 * This function reads the ADC value from the moisture sensor connected to pin PK1 (ADC9).
 *
 * @return 10-bit ADC value read from the moisture sensor
 */
uint16_t moisture_read(void);
