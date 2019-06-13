sensirion_common_dir := ../embedded-common
sts_common_dir := ../sts-common
sw_i2c_dir := ${sensirion_common_dir}/sw_i2c
hw_i2c_dir := ${sensirion_common_dir}/hw_i2c

CFLAGS := -Wall -I. -I${sensirion_common_dir} -I${sts_common_dir}

sensirion_common_objects := sensirion_common.o
sts_common_objects := sts_git_version.o
sts3x_binaries := sts3x_example_usage_sw_i2c sts3x_example_usage_hw_i2c
sts_binaries += ${sts3x_binaries}

sw_objects := ${sensirion_common_dir}/sw_i2c/sensirion_sw_i2c.o ${sensirion_common_dir}/sw_i2c/sensirion_sw_i2c_implementation.o
hw_objects := ${sensirion_common_dir}/hw_i2c/sensirion_hw_i2c_implementation.o
all_objects := ${sensirion_common_objects} ${sts_common_objects} ${hw_objects} ${sw_objects} sts3x.o

.PHONY: all

all: ${sts_binaries}

sts_git_version.o: ${sts_common_dir}/sts_git_version.c
	$(CC) $(CFLAGS) -c -o $@ $^
sensirion_common.o: ${sensirion_common_dir}/sensirion_common.c
	$(CC) $(CFLAGS) -c -o $@ $^
sensirion_sw_i2c_implementation.o: ${sw_i2c_dir}/sensirion_sw_i2c_implementation.c
	$(CC) $(CFLAGS) -c -o $@ $^
sensirion_hw_i2c_implementation.o: ${hw_i2c_dir}/sensirion_hw_i2c_implementation.c
	$(CC) $(CFLAGS) -c -o $@ $^

sensirion_sw_i2c.o: ${sw_i2c_dir}/sensirion_sw_i2c.c
	$(CC) -I${sw_i2c_dir} $(CFLAGS) -c -o $@ $^

sts3x.o: ${sensirion_common_dir}/sensirion_i2c.h ${sts_common_dir}/sts_git_version.c sts3x.h sts3x.c

sts3x_example_usage_sw_i2c: ${sensirion_common_objects} ${sts_common_objects} ${sw_objects} sts3x.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS) sts3x_example_usage.c

sts3x_example_usage_hw_i2c: ${sensirion_common_objects} ${sts_common_objects} ${hw_objects} sts3x.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS) sts3x_example_usage.c

clean:
	$(RM) ${all_objects} ${sts_binaries}
