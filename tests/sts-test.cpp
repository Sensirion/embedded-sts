#include "sensirion_common.h"
#include "sensirion_test_setup.h"
#include "sts3x.h"

TEST_GROUP (STSTestGroup) {
    void setup() {
        int16_t ret;
        sensirion_i2c_init();

        ret = sensirion_i2c_mux_set_single_channel(0x72, 0);
        CHECK_EQUAL_TEXT(0, ret,
                         "sensirion_i2c_mux_set_single_channel(0x72, 0)");

        ret = sensirion_i2c_general_call_reset();
        CHECK_EQUAL_TEXT(0, ret, "sensirion_i2c_general_call_reset");
        sensirion_sleep_usec(1500);  // wait 1.5ms after reset
    }

    void teardown() {
        int16_t ret = sensirion_i2c_general_call_reset();
        CHECK_EQUAL_TEXT(0, ret, "sensirion_i2c_general_call_reset");
        sensirion_i2c_release();
    }
};

TEST (STSTestGroup, STS30Test) {
    int16_t ret;
    int32_t temperature;
    uint32_t serial;

    ret = sts3x_probe();
    CHECK_ZERO_TEXT(ret, "sts3x_probe");

    ret = sts3x_measure_blocking_read(&temperature);
    CHECK_ZERO_TEXT(ret, "sts3x_measure_blocking_read");
    CHECK_TRUE_TEXT(temperature >= 5000 && temperature <= 45000,
                    "sts3x_measure_blocking_read");

    ret = sts3x_heater_on();
    CHECK_ZERO_TEXT(ret, "sts3x_heater_on");

    sensirion_sleep_usec(500);  // undocumented time, sensor not ready before

    ret = sts3x_measure();
    CHECK_ZERO_TEXT(ret, "sts3x_measure");

    sensirion_sleep_usec(STS3X_MEASUREMENT_DURATION_USEC);

    ret = sts3x_read(&temperature);
    CHECK_ZERO_TEXT(ret, "sts3x_read");
    CHECK_TRUE_TEXT(temperature >= 5000 && temperature <= 45000, "sts3x_read");

    ret = sts3x_heater_off();
    CHECK_ZERO_TEXT(ret, "sts3x_heater_off");

    sensirion_sleep_usec(500);  // undocumented time, sensor not ready before

    sts3x_set_repeatability(0);

    ret = sts3x_read_serial(&serial);
    CHECK_ZERO_TEXT(ret, "sts3x_read_serial");
    printf("STS30 serial: %u", serial);

    const char* version = sts3x_get_driver_version();
    printf("sts3x_get_driver_version: %s\n", version);

    uint8_t addr = sts3x_get_configured_address();
    CHECK_EQUAL_TEXT(0x4a, addr, "sts3x_get_configured_address");
}
