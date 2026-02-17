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

Enter the bootloader in 2 ways:

* **Keycode in layout**: Press Fn+Esc while the keyboard is powered on.
* **Physical reset**: Short the pads below the space bar labeled "J3" while plugging in the keyboard.
