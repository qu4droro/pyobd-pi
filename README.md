# RPI-ECU Tuner
by Ryan Switzer

## Hardware & Installation
#### Hardware
* Raspberry Pi 3
* Aftermarket head unit (Note: Must support Auxiliary input)
* Plugable USB Bluetooth 4.0 Low Energy Micro Adapter
* 2A Car Supply
* ELM327 Bluetooth Adapter
* PiCAN2
* DB9-to-OBD cable
* OBD Splitter
* RCA cable (+HDMI-to-RCA Adapter)
* Keyboard (*optional)

#### Installation
1. Insert the USB Bluetooth dongle into the Raspberry Pi along with the SD card.
2. Insert the OBD Splitter into the SAE J196216 (OBD Port) connector.
3. Insert the OBD-II Bluetooth adapter into the OBD Splitter.
4. Insert the DB9-to-OBD cable into the OBD Splitter.
5. Attach the PiCAN2 onto the Rasbeery Pi UART and connect to the DB9-to-OBD cable.
4. Connect you RCA cable to the back of your aftermarket head unit and plug the other end the converter and then into your Raspberry Pi.
4. Install your 2A Car Supply / Switch or Micro USB Car Charger.
5. Finally turn your key to the ON position and navigate your head unit to Auxiliary input.


## Software Installation

Before proceeding, execute the following:
<pre>
$  sudo apt-get update
$  sudo apt-get upgrade
$  sudo apt-get autoremove
$  sudo reboot
</pre>

### pyOBD

Install dependecies using the following commands:
<pre>
$  sudo apt-get install python-serial
$  sudo apt-get install bluetooth bluez-utils blueman
$  sudo apt-get install python-wxgtk2.8 python-wxtools wx2.8-i18n libwxgtk2.8-dev
$  sudo reboot
</pre>

Next copy the source code over to the home directory via flash drive (or whatever preffered means).



### SocketCAN

Copy, untar and register the rpi-can modules
<pre>
$  cd /tmp; wget http://lnxpps.de/rpie/rpi-can-3.12.28+.tar.bz2
$  cd /; tar jxvf /tmp/rpi-can-3.12.28+.tar.bz2
$  depmod -a
$  reboot
</pre>

Add the spi-config and mcp2515 modules
<pre>
$  nano /etc/modules
</pre>
Copy and paste the following
<pre>
# /etc/modules: kernel modules to load at boot time.
#
# This file contains the names of kernel modules that should be loaded
# at boot time, one per line. Lines beginning with "#" are ignored.
# Parameters can be specified after the module name.

snd-bcm2835
spi_bcm2708

# MCP2515 configuration for PICAN module
spi-config devices=\
bus=0:cs=0:modalias=mcp2515:speed=10000000:gpioirq=25:pd=20:pds32-0=16000000:pdu32-4=0x2002:force_release

# load the module
mcp251x
</pre>

Update the raspi-backlist.conf
<pre>
$  nano /etc/modprobe.d/raspi-blacklist.conf
</pre>
Enable the spi-bcm2708 & mcp251x driver
<pre>
# blacklist spi and i2c by default (many users don't need them)

#blacklist spi-bcm2708
blacklist i2c-bcm2708
#blacklist mcp251x
</pre>


## Execution

### pyOBD

Enter your login credentials and execute (dependent on OS boot format):
<pre>
$  startx
</pre>

Launch BlueZ, the Bluetooth stack for Linux. Pair + Trust your ELM327 Bluetooth Adapter and Connect To: SPP Dev. You should see the Notification "Serial port connected to /dev/rfcomm0"

Note: Click the Bluetooth icon, bottom right (Desktop) to configure your device. Right click on your Bluetooth device to bring up Connect To: SPP Dev.

Open the terminal and enter the following:
<pre>
$  cd pyobd-pi
$  sudo su
$  python obd_gui.py
</pre>

Now use the Left and Right arrow key to cycle through the gauge display.
(Note: Left and Right mouse click will also work)

To exit the program just press Control and C or Alt and Esc.

Data Logging
If you would like to log your data run:
<pre>
$  cd pyobd-pi
$  python obd_recorder.py
</pre>
The logged data file will be saved under:
/home/username/pyobd-pi/log/

### SocketCAN