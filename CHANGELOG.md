# Changelog

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

 * [`fixed`]  Improved compatibility with C++ compilers
 * [`changed`]  Return types are now `int16_t` instead of `int8_t` (in line with
                other embedded drivers).
 * [`changed`]  Functions are now dedicated per sensor (e.g. `sts3x_probe()`
                instead of `sts_probe()`)
 * [`changed`]  Move the i2c init call out of `probe()` and into the example
 * [`changed`]  Rename `git_version.[ch]` to `sts_git_version.[ch]`
 * [`added`]  Add `sts3x_read_serial()` to read out the serial number
 * [`changed`]  Split out `default_config.inc` from Makefile to configure paths
                and CFLAGS
 * [`changed`]  Only one example with either `hw_i2c` or `sw_i2c` is built,
                depending on `CONFIG_I2C_TYPE`. Defaults to `hw_i2c`.
 * [`fixed`]  Measurement duration could take at most 15.5ms (datasheet) but we
              only waited 15ms
 * [`added`]  Add `STS3X_MEASUREMENT_DURATION_USEC` to header

## [1.0.0] - 2019-05-13

 * Initial support for STS3x

[Unreleased]: https://github.com/Sensirion/embedded-sts/compare/1.0.0...master
[1.0.0]: https://github.com/Sensirion/embedded-sts/releases/tag/1.0.0
