# handwired/mercklone

![handwired/mercklone](imgur.com image replace me!)

An approximate clone of the game-pad side of the Ideazon MercStealth keyboard and or Fang game-pad, since the drivers no longer "work" in windows. 

* Keyboard Maintainer: [Jinkz](https://github.com/jinxanarexi)
* Hardware Supported: ProMicro (or compatible)

Make example for this keyboard (after setting up your build environment):

    make handwired/mercklone:default

Flashing example for this keyboard:

    make handwired/mercklone:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead (SparkFun -> double tap reset button for 8s in bootloader)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
