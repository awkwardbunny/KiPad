# KiPad

Custom keypad made using KiCad.

![Assembled](/img/photo.jpeg)
![Side view](/img/photo_side.jpeg)

Custom PCB + 3D printed keycaps and case.

# PCB

The PCB was designed in KiCad and manufactured by JLCPCB.

![Circuit board](/img/kipad_render.png)

Most of the components have a custom field `DIGIKEY`, which corresponds to the Digikey part number.
Components can be ordered from Digikey easily by doing a BOM export and using Digikey's upload list feature.

The hotswap connectors, key switches, and stablizers do not have Digikey part numbers. Choose ones you like.

# Keycaps

The keycaps were generated using [this library](https://github.com/rsheldiii/KeyV2).

![Keycaps rendered](/img/keys_render.png)

# Case

The PCB was exported from KiCad and a case was modeled around it using OnShape. The models can be found under [case/](/case) or on [OnShape](https://cad.onshape.com/documents/05e5af1ac1cd92aec3ff415b/w/62ce95e3d910c49c77b0c6ec/e/b1757f7efc67fc1a5c9fca3c?renderMode=0&uiState=66b20bf3e3c77e6059daf154).

The bottom of the case is designed to fit 1.2mm thick boards, so keep that in mind when putting in the PCB order.

![Rendered case](/img/case_render.jpg)

# Firmware

To build the firmware, follow the [QMK setup](https://docs.qmk.fm/newbs_getting_started), and then copy/link the `qmk` directory into the keyboards directory:

```bash
# Clone project
git clone https://github.com/awkwardbunny/KiPad
cd KiPad
# By default, QMK installs to ~/qmk_firmware on linux
ln -s $(pwd)/qmk ~/qmk_firmware/keyboards/meirl
# Flash. Use the directory name above
qmk flash -kb meirl/kipad_v3_1 -km via
```

## Reset and DFU

The Atmega32u2 goes into DFU bootloader without any code on it. If you wish to reflash, connect the keypad while holding down the top-left key (A).

If a bad firmware was uploaded and you cannot get it into DFU mode with that method, you need to trigger a reset while the `HWB` pin is pulled low.
There is a pad exposed on the back for reset, and the `HWB` pin is connected to column 3. I solder one wire to each of these and do the following:

1. Connect the device
2. Take the wire connected to column 3 and make contact with ground (the USb shield works)
3. Touch the wire connected to the reset pin briefly to ground
4. Release the column 3 wire

And the device should show up in DFU mode

## Via

To use with [Via](https://usevia.app/), you need to enable `Settings -> Show design tab -> Enable`. A new tab should appear.
Open the new design tab and upload the keyboard definition [qmk/kipad_v3_1/via.json](/qmk/kipad_v3_1/via.json). Now you should be able to reconfigure it as you like.

### Udev

For linux, Via may not be able to access the keypad HID devices due to permissions. Try adding the following to `/etc/udev/rules.d/90-kipad.rules`:
```
# MEIRL KiPad v2.0
SUBSYSTEM=="usb", ATTRS{idVendor}=="4248", ATTRS{idProduct}=="4b50", MODE="0666"
KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="4248", ATTRS{idProduct}=="4b50", MODE="0666"

# MEIRL KiPad v3.0
SUBSYSTEM=="usb", ATTRS{idVendor}=="4248", ATTRS{idProduct}=="4b51", MODE="0666"
KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="4248", ATTRS{idProduct}=="4b51", MODE="0666"

# MEIRL KiPad v3.1
SUBSYSTEM=="usb", ATTRS{idVendor}=="4248", ATTRS{idProduct}=="4b52", MODE="0666"
KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="4248", ATTRS{idProduct}=="4b52", MODE="0666"
```

And then `sudo udevadm control --reload`.
