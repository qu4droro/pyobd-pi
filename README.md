# RPI-ECU Tuner
by Ryan Switzer

## Hardware & Installation
#### Hardware
* Raspberry Pi
* Aftermarket head unit (Note: Must support Auxiliary input)
* Plugable USB Bluetooth 4.0 Low Energy Micro Adapter
* 2A Car Supply / Switch or Micro USB Car Charger
* ELM327 Bluetooth Adapter or ELM327 USB Cable
* RCA cable
* Keyboard (*optional)

#### Installation
1. Insert the USB Bluetooth dongle into the Raspberry Pi along with the SD card.
2. Insert the OBD-II Bluetooth adapter into the SAE J196216 (OBD Port) connector.
3. Connect you RCA cable to the back of your aftermarket head unit and plug the other end into your Raspberry Pi.
4. Install your 2A Car Supply / Switch or Micro USB Car Charger.
5. Finally turn your key to the ON position and navigate your head unit to Auxiliary input.


## Software Installation

### pyOBD
Before proceeding, execute the following:
<pre>
#  sudo apt-get update
#  sudo apt-get upgrade
#  sudo apt-get autoremove
#  sudo reboot
</pre>

Install dependecies using the following commands:
<pre>
#  sudo apt-get install python-serial
#  sudo apt-get install bluetooth bluez-utils blueman
#  sudo apt-get install python-wxgtk2.8 python-wxtools wx2.8-i18n libwxgtk2.8-dev
#  sudo reboot
</pre>

Next copy the source code over to the home directory via flash drive (or whatever preffered means).

Enter your login credentials and execute (dependent on OS boot format):
<pre>
#  startx
</pre>

Launch BlueZ, the Bluetooth stack for Linux. Pair + Trust your ELM327 Bluetooth Adapter and Connect To: SPP Dev. You should see the Notification "Serial port connected to /dev/rfcomm0"

Note: Click the Bluetooth icon, bottom right (Desktop) to configure your device. Right click on your Bluetooth device to bring up Connect To: SPP Dev.


### SocketCAN


## Execution

### pyOBD
Open the terminal and enter the following:
<pre>
#  cd pyobd-pi
#  sudo su
#  python obd_gui.py
</pre>

Now use the Left and Right arrow key to cycle through the gauge display.
(Note: Left and Right mouse click will also work)

To exit the program just press Control and C or Alt and Esc.

Data Logging
If you would like to log your data run:
<pre>
#  cd pyobd-pi
#  python obd_recorder.py
</pre>
The logged data file will be saved under:
/home/username/pyobd-pi/log/