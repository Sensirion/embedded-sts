sts_driver_dir ?= ..
sensirion_common_dir ?= ${sts_driver_dir}/embedded-common
sts_utils_dir ?= ${sts_driver_dir}/utils

CFLAGS ?= -Os -Wall -fstrict-aliasing -Wstrict-aliasing=1 -Wsign-conversion -fPIC
CFLAGS += -I${sts_utils_dir} -I${sensirion_common_dir}

sensirion_temperature_unit_conversion_sources = \
    ${sts_utils_dir}/sensirion_temperature_unit_conversion.h \
    ${sts_utils_dir}/sensirion_temperature_unit_conversion.c
