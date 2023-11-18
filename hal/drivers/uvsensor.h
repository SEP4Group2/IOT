/**
 * @file uvsensor.h
 * @brief Uv sensor driver for ATmega2560
 *
 * This file provides the API for initializing and reading the value from a uv sensor
 * connected to pin PK1 (ADC9) on the ATmega2560.
 *
 * @author Your Name
 * @date September 2023
 */

#pragma once

#include <stdint.h>

/**
 * @brief Initialize ADC for uv sensor
 *
 * This function initializes the ADC to read values from the uv sensor connected to pin PK1 (ADC9).
 */
void uvsensor_init(void);

/**
 * @brief Read value from uv sensor
 *
 * This function reads the ADC value from the uv sensor connected to pin PK1 (ADC9).
 *
 * @return 10-bit ADC value read from the uv sensor
 */
uint16_t uvsensor_read(void);
