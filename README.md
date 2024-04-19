# embedded-sts [![GitHub license](https://img.shields.io/badge/license-BSD3-blue.svg)](https://raw.githubusercontent.com/Sensirion/embedded-sts/master/LICENSE)

This repository is deprecated, please use the new drivers:
* STS3x: https://github.com/Sensirion/embedded-i2c-sts4x
* STS4x: https://github.com/Sensirion/embedded-i2c-sts4x

This repository contains the embedded driver sources for Sensirion's
STS product line.

If you just want to use the driver, it is recommended to download the release
zip from https://github.com/Sensirion/embedded-sts/releases

## Clone this repository
```
 git clone --recursive https://github.com/Sensirion/embedded-sts.git
```

## Repository content
* `embedded-common` submodule repository for the common embedded driver HAL
* `sts-common` common files for all STS drivers
* `sts3x` STS3x driver

## Collecting resources
```
make release
```
This will create the `release` folder and release zip file with the necessary
driver files in it, including a Makefile. That way, you have just ONE folder
with all the sources ready to build your driver for your platform.

## Files to adjust (from embedded-common)
To adapt the driver to your platform, you only need to touch the following
files:

* `sensirion_arch_config.h` (architecture specifics, you need to specify
the integer sizes if your compiler toolchain does not provide `stdint.h`)

and depending on your i2c implementation either of the following:

* `embedded-common/hw_i2c/sensirion_hw_i2c_implementation.c`
  functions for hardware i2c communication if your platform has a dedicated I2C
  controller.
* `embedded-common/sw_i2c/sensirion_sw_i2c_implementation.c`
  functions for software i2c communication if your platform does not have a
  dedicated I2C controller and communication happens with GPIOs. In this case
  you need to make sure that appropriate I2C pull-up resistors are used.

## Building the driver
1. Adjust `sensirion_arch_config.h` if you don't have the `<stdint.h>` header
   file available.
2. Either use one of the provided sample implementations implement necessary
   functions in one of the `*_implementation.c` files described above (either in
   the `hw_i2c` or `sw_i2c` folder).

   To reuse a provided sample implementation you can specify it in a custom
   build configuration. For this adapt the file `user_config.inc` in the
   driver:

   `user_config.inc` for hardware i2c with dedicated i2c controller:
   ```
   CONFIG_I2C_TYPE=hw_i2c
   hw_i2c_impl_src = ${embedded-common}/hw_i2c/sample-implementations/linux_user_space/sensirion_hw_i2c_implementation.c
   ```

   `user_config.inc` for software i2c with bit-banging on GPIOs:
   ```
   CONFIG_I2C_TYPE=sw_i2c
   sw_i2c_impl_src = ${embedded-common}/sw_i2c/sample-implementations/linux_user_space/sensirion_sw_i2c_implementation.c
   ```

3. Run `make`
4. Run the compiled example usage with `./sts30_example_usage`. Note that
   hardware access permissions (e.g. `sudo`) might be needed.

---

Please check the [embedded-common](https://github.com/Sensirion/embedded-common)
repository for further information and available sample implementations.

---
