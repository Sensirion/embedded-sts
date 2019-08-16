# See user_config.inc for build customizations
-include user_config.inc
include default_config.inc

.PHONY: all clean

all: sts3x_example_usage

sts3x_example_usage: clean
	$(CC) $(CFLAGS) -o $@ ${sts3x_sources} ${${CONFIG_I2C_TYPE}_sources} ${sts3x_dir}/sts3x_example_usage.c

clean:
	$(RM) sts3x_example_usage
