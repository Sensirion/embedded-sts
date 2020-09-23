include ../embedded-common/test-config/base_config.inc
sts_driver_dir := ${driver_dir}/embedded-sts
include ${sts_driver_dir}/sts3x/default_config.inc

sts3x_test_binaries := sts3x-test-hw_i2c sts3x-test-sw_i2c

.PHONY: all clean prepare test

all: clean prepare test

prepare:
	cd ${sts_driver_dir} && $(MAKE) prepare

sts3x-test-hw_i2c: sts-test.cpp ${sts3x_sources} ${hw_i2c_sources} ${sensirion_test_sources}
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

sts3x-test-sw_i2c: CONFIG_I2C_TYPE := sw_i2c
sts3x-test-sw_i2c: sts-test.cpp ${sts3x_sources} ${sw_i2c_sources} ${sensirion_test_sources}
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) ${sts3x_test_binaries}

test: prepare ${sts3x_test_binaries}
	set -ex; for test in ${sts3x_test_binaries}; do echo $${test}; ./$${test}; echo; done;
