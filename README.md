# `renard-phy-s2lp-hal-esp32` - ESP32 Hardware Abstraction Layer for [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp)

`renard-phy-s2lp-hal-esp32` is the ESP32 hardware abstraction layer (HAL) for the open source Sigfox PHY layer [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp), which interfaces with STMicroelectronics' S2-LP ultra-low power transceiver chip. It can simply be included as an [esp-idf](https://github.com/espressif/esp-idf) component.

See [`renard-phy-s2lp`](https://github.com/Jeija/renard-phy-s2lp) for more information.

# Pin Configuration
`renard-phy-s2lp-hal-esp32` uses the following pin configuration by default:

S2-LP Pin Name | ESP32 Pin
---:|:---
MISO (SPI) | IO 19 (VSPI)
MOSI (SPI) | IO 23 (VSPI)
SCLK (SPI) | IO 18 (VSPI)
CS (SPI) | IO 5 (VSPI)
SDN | IO 16
GPIO3 | IO 4

You can configure these pin definitions by running
```
idf.py menuconfig
```
in your application and then choosing the `Renard HAL Config` menu.

# Usage
See [renard-phy-s2lp-demo-esp32](https://github.com/Jeija/renard-phy-s2lp-demo-esp32/) for sample code that demonstrates how to integrate this HAL together with `renard-phy-s2lp` into your project.

# Licensing
`renard-phy-s2lp-hal-esp32` is licensed under the MIT License. See `LICENSE` for details.
