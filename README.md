gr-funcube is an linux oot-module for gnuradio to implement a funcube dongle and a funcube dongle pro+ source.  
On linux it autodetects the correct soundcard from /proc/asound/cards.  
This idea was taken from the osmosdr drivers.

To control the device the hidapi usb version is used.


1.   Dependencies:  

    gnuradio (>= 3.9 )  
alsa usb drivers activated  
hidapi-libusb  

2.   Installation:  
  
    The build process is cmake based.  
    So get the latest code from https://github.com/dl1ksv/gr-funcube  
and change to code the directory. There   

    $mkdir build  
$cd build  
$cmake -DCMAKE_INSTALL_PREFIX= "path to gnuradio installation" ../  
$make  
$su  
$make install  
    
    After that executing grc  you'll find in Fcd  

    Funcube Dongle   
Funcube Dongle control  
Funcube Dongle Pro+  
Funcube Dongle Pro+ control

3.   Important  
Don't forget the udev rules:  
For instance:  

  > #### Udev rules for the Funcube Dongle Pro (0xfb56) and Pro+ (0xfb31)
  # HIDAPI/libusb:  
  SUBSYSTEMS=="usb" ATTRS{idVendor}=="04d8" ATTRS{idProduct}=="fb56" MODE:="0666"
  SUBSYSTEMS=="usb" ATTRS{idVendor}=="04d8" ATTRS{idProduct}=="fb31" MODE:="0666"  
  # HIDAPI/hidraw:  
  KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="04d8", ATTRS{idProduct}=="fb56", MODE="0666"
  KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="04d8", ATTRS{idProduct}=="fb31", MODE="0666"

4.    Usage  

    Four modules are available:  
   - fcd control  
   - fcd  
   - fcdpp_control  
   - funcube  
   The control modules only controls the dongles, while the other modules control the dongles and provide the IQ samples.
All modules accept messages to control the frequency. That was the reason to introduce the control modules.

    The fcd modules where introduced, as gnuradio 3.8 does not contain gr-fcd at the moment.  
See the examples of a simple fm receiver in the examples directory or see a more complex example in in gr-display


5.    Credits  

    Some code is taken from qthid-4.1 by Alexandru Csete, OZ9AEC.  

Thanks to Michael Dickens, who gave valuable hints for implementing message in hier2_blocks.
