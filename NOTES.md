#NOTES

Reminder to me to add ISP programming headers.
Not sure if this is strictly necessary since I hear the chip comes from the factory with the AVR DFU
bootloader already flashed, but it requires a faster clock (?) for USB and its fuses need to be set to
use the external oscillator instead of internal 8MHz.


Reminder (mostly to myself) to correct the diode footprints since the parts I got wasn't the right size.

OH, on the USB-C connector, one side of the USB- net is not connected, making the cable only work in one orientation...

And minorly, I could probably move the decoupling caps closer (especially C6/C7 I think)
