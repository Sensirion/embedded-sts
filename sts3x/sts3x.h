/*
 * Copyright (c) 2019, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \file
 *
 * \brief Sensirion STS driver interface
 *
 * This module provides access to the STS functionality over a generic I2C
 * interface. It supports measurements without clock stretching only.
 */

#ifndef STS3X_H
#define STS3X_H

#include "sensirion_arch_config.h"
#include "sensirion_i2c.h"
#include "sts_git_version.h"

#ifdef __cplusplus
extern "C" {
#endif

#define STATUS_OK 0
#define STATUS_ERR_BAD_DATA (-1)
#define STATUS_CRC_FAIL (-2)
#define STATUS_UNKNOWN_DEVICE (-3)

#define STS3X_MEASUREMENT_DURATION_USEC 15500

/**
 * Detects if a sensor is connected by reading out the ID register.
 * If the sensor does not answer or if the answer is not the expected value,
 * the test fails.
 *
 * @return 0 if a sensor was detected
 */
int16_t sts3x_probe(void);

/**
 * Starts a measurement and then reads out the results. This function blocks
 * while the measurement is in progress. The duration of the measurement depends
 * on the sensor in use, please consult the datasheet.
 * Temperature is returned in [degree Celsius], multiplied by 1000
 *
 * @param temperature   the address for the result of the temperature
 * measurement
 * @return              0 if the command was successful, else an error code.
 */
int16_t sts3x_measure_blocking_read(int32_t* temperature);

/**
 * Starts a measurement in high precision mode. Use sts3x_read() to read out the
 * values, once the measurement is done. The duration of the measurement depends
 * on the sensor in use, please consult the datasheet.
 *
 * @return     0 if the command was successful, else an error code.
 */
int16_t sts3x_measure(void);

/**
 * Reads out the results of a measurement that was previously started by
 * sts3x_measure(). If the measurement is still in progress, this function
 * returns an error.
 * Temperature is returned in [degree Celsius], multiplied by 1000
 *
 * @param temperature   the address for the result of the temperature
 * measurement
 * @return              0 if the command was successful, else an error code.
 */
int16_t sts3x_read(int32_t* temperature);

/**
 * Set repeatability of the STS
 *
 * @param repeatability 0 for high repeatability mode (default)
 *                      1 for medium repeatability mode
 *                      2 for low repeatability mode
 */
void sts3x_set_repeatability(uint8_t repeatability);

/**
 * Enable internal heater. The heater is meant for plausibility check only.
 *
 * @return 0 if the command was successful,
 *         1 if an error occured
 */
int16_t sts3x_heater_on(void);

/**
 * Disable internal heater
 *
 * @return 0 if the command was successful,
 *         1 if an error occured
 */
int16_t sts3x_heater_off(void);

/**
 * Read out the serial number
 *
 * @param serial    the address for the result of the serial number
 * @return          0 if the command was successful, else an error code.
 */
int16_t sts3x_read_serial(uint32_t* serial);

/**
 * Return the driver version
 *
 * @return Driver version string
 */
const char* sts3x_get_driver_version(void);

/**
 * Returns the configured STSxx address.
 *
 * @return STSxx_ADDRESS
 */
uint8_t sts3x_get_configured_address(void);

#ifdef __cplusplus
}
#endif

#endif /* STS3X_H */
