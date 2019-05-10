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
 * \brief Sensirion STS3x driver implementation
 *
 * This module provides access to the STS3x functionality over a generic I2C
 * interface. It supports measurements without clock stretching only.
 */

#include "sensirion_arch_config.h"
#include "sensirion_common.h"
#include "sensirion_i2c.h"
#include "sts.h"
#include "sts_common.h"

/* all measurement commands return T (CRC) RH (CRC) */
#if USE_SENSIRION_CLOCK_STRETCHING
static const u8 CMD_MEASURE_HPM[] = {0x2C, 0x06};
static const u8 CMD_MEASURE_MPM[] = {0x2C, 0x0D};
static const u8 CMD_MEASURE_LPM[] = {0x2C, 0x10};
#else
static const u8 CMD_MEASURE_HPM[] = {0x24, 0x00};
static const u8 CMD_MEASURE_MPM[] = {0x24, 0x0B};
static const u8 CMD_MEASURE_LPM[] = {0x24, 0x16};
#endif /* USE_SENSIRION_CLOCK_STRETCHING */
static const u8 CMD_READ_STATUS_REG[] = {0xF3, 0x2D};
static const u8 CMD_HEATER_ON[] = {0x30, 0x6D};
static const u8 CMD_HEATER_OFF[] = {0x30, 0x66};
static const u8 COMMAND_SIZE = sizeof(CMD_MEASURE_HPM);
#ifdef STS_ADDRESS
static const u8 STS3X_ADDRESS = STS_ADDRESS;
#else
static const u8 STS3X_ADDRESS = 0x4A;
#endif

static const u16 MEASUREMENT_DURATION_USEC = 15000;

static const u8 *cmd_measure = CMD_MEASURE_HPM;

s8 sts_measure_blocking_read(s32 *temperature) {
    s8 ret = sts_measure();
    if (ret == STATUS_OK) {
        sensirion_sleep_usec(MEASUREMENT_DURATION_USEC);
        ret = sts_read(temperature);
    }
    return ret;
}

s8 sts_measure() {
    return sensirion_i2c_write(STS3X_ADDRESS, CMD_MEASURE_HPM, COMMAND_SIZE);
}

s8 sts_read(s32 *temperature) {
    return sts_common_read_measurement(STS3X_ADDRESS, temperature);
}

s8 sts_probe() {
    u8 data[3];
    sensirion_i2c_init();
    s8 ret =
        sensirion_i2c_write(STS3X_ADDRESS, CMD_READ_STATUS_REG, COMMAND_SIZE);
    if (ret)
        return ret;

    ret = sensirion_i2c_read(STS3X_ADDRESS, data, sizeof(data));
    if (ret)
        return ret;

    ret = sensirion_common_check_crc(data, 2, data[2]);
    if (ret)
        return ret;
    return STATUS_OK;
}

void sts_set_repeatability(u8 repeatability) {
    switch (repeatability) {
        case 2:
            cmd_measure = CMD_MEASURE_LPM;
            break;
        case 1:
            cmd_measure = CMD_MEASURE_MPM;
            break;
        case 0:
        default:
            cmd_measure = CMD_MEASURE_HPM;
            break;
    }
}

s8 sts_heater_on(void) {
    return sensirion_i2c_write(STS3X_ADDRESS, CMD_HEATER_ON, COMMAND_SIZE);
}

s8 sts_heater_off(void) {
    return sensirion_i2c_write(STS3X_ADDRESS, CMD_HEATER_OFF, COMMAND_SIZE);
}

const char *sts_get_driver_version() {
    return STS_DRV_VERSION_STR;
}

u8 sts_get_configured_sts_address() {
    return STS3X_ADDRESS;
}
