# Arduino-Weather-Station-Lib
An Arduino Library for Weather station converstions

This is a work in progress. Just started my first Library.
This library includes converstions for a Arduino Weather station that gatheres temperature, humidity and berametric pressure.

The code is writen and tested on a Genuino Zero. With a DHT22 and a BMP280 Barometric pressure and a 20x4 I2C LCD.
Also in the circuit is a I2C frendly level shifter.
This is for the Library only but did not have time to test it on its own yet.

Delopment on this has stoped as I have attched it to a Arduino YUN shield and am logging directly to a MySQL database running on a desktop computer. Therefor this library is nolonger required as I use a Raspberry Pi 3 as web server and it calculates all this weather info. but this library has been running in my basement Since November 2016 and still logging and displaying on the LCD.
