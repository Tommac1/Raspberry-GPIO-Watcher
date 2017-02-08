# RaspberryGPIOWatcher

Program to watch signal on Raspi Pins and display their status on touchscreen.

The main program compiled by Qt cmake calls fileProgram to update status to pinStatus.txt file. Then the main program updates the display depending on pinStatus.txt file. All files must be in the same folder to work.

# Used technologies

C with wiringPi library, C++ with Qt, RaspberryPi, cross-compilation.

# Video 

https://youtu.be/DNHHEwHQQEc
