gr-funcube is an linux oot-module for gnuradio to implement a funcube dongle and a funcube dongle pro+ source.  
On linux it autodetects the correct soundcard from /proc/asound/cards.  
This idea was taken from the osmosdr drivers.

To control the device the hidapi usb version is used.


1.   Dependencies:  
    &nbsp;   
gnuradio (>= 3.9 ) with pybind  
alsa usb drivers activated  
hidapi-libusb  

2.   Installation:  
    &nbsp;  
The build process is cmake based.  
So get the latest code from https://github.com/dl1ksv/gr-funcube  
and change to the code directory. There   
&nbsp;  
$mkdir build  
$cd build  
$cmake -DCMAKE_INSTALL_PREFIX= "path to gnuradio installation" ../  
$make  
$su  
$make install  
&nbsp;      
After that executing grc  you'll find in the section Funcube   
&nbsp;  
Funcube Dongle  
Funcube Dongle control  
Funcube Dongle Pro+  
Funcube Dongle Pro+ control

3.   Important  
    &nbsp;  
Don't forget the udev rules:  
For instance:  
&nbsp;  
    #### Udev rules for the Funcube Dongle Pro (0xfb56) and Pro+ (0xfb31)   
    # HIDAPI/libusb:  
SUBSYSTEMS=="usb" ATTRS{idVendor}=="04d8" ATTRS{idProduct}=="fb56" MODE:="0666"    
SUBSYSTEMS=="usb" ATTRS{idVendor}=="04d8" ATTRS{idProduct}=="fb31" MODE:="0666"  
    # HIDAPI/hidraw:  
KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="04d8", ATTRS{idProduct}=="fb56", MODE="0666"  
KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="04d8", ATTRS{idProduct}=="fb31", MODE="0666"  

4.    Usage  
    &nbsp;  
Four modules are available:  
   - fcd_control  
   - fcd  
   - fcdpp_control  
   - funcube  
&nbsp;  
    The control modules only controls the dongles, while the other modules control the dongles and provide the IQ samples.
All modules accept messages to control the frequency. That was the reason to introduce the control modules.
&nbsp;  
    The fcd modules where introduced, as gnuradio 3.8 does not contain gr-fcd at the moment.  
See the examples of a simple fm receiver in the examples directory or see a more complex example in in gr-display


5.    Credits  
    &nbsp;  
Some code is taken from qthid-4.1 by Alexandru Csete, OZ9AEC.  

Thanks to Michael Dickens, who gave valuable hints for implementing message in hier2_blocks.
