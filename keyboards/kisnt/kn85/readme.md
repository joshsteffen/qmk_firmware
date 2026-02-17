# Kisnt KN85

![Kisnt KN85](https://i.imgur.com/HOQ6ZHl.jpeg)

A 75% hot-swappable RGB keyboard.

* Keyboard Maintainer: [Josh Steffen](https://github.com/joshsteffen)
* Hardware Supported: Kisnt KN85
* Hardware Availability: [Amazon](https://www.amazon.com/Kisnt-Wireless-Mechanical-Bluetooth-Swappable/dp/B0DBZGH5XM)

Make example for this keyboard (after setting up your build environment):

    make kisnt/kn85:default

Flashing example for this keyboard:

    make kisnt/kn85:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
* **Physical reset**: Short the pads on the PCB beneath the space bar labeled "J3"
