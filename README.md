## Draft

gr-funcube is an linux oot-module for gnuradio to implementma funcube dongle pro+ source.  
On linux it autodetects the correct soundcard from /proc/asound/cards.  
This idea was taken from the osmosdr drivers.

To control the device the hidapi usb version is used.

1. Dependencies:  

 gnuradio (dev-4.0 branch) with pybind  
 alsa usb drivers activated  
 hidapi-libusb  

2. Installation:    

 git clone https://github.com/dl1ksv/gr-funcube --branch dev-4.0  
 cd gr-funcube  
 meson setup build  
 cd build && ninja   
 ninja test  
 ninja install # (sudo ninja install if not root)

 After that executing grc  you'll find in the section Funcube   


 Funcube Dongle Pro+  
 Funcube Dongle Pro+ control

     **Hint:**  
     You can install gr-funcube to an other directory than "path to gnuradio installation". But then you have to add
     the location of your python modules to the PYTHONPATH environment variable and add the location of
     the lib to the LD_LIBRARY_PATH environment variable.

     To see the newly created blocks in grc you have to set the local_blocks_path entry in ~/.gnuradio/config.yml.
     Example: If you choose /usr/local/oot as installation directory, you have to set 
     local_blocks_path: /usr/local/oot/share/gnuradio/grc/blocks
     

3.   Important  
    &nbsp;  
Don't forget the udev rules:  
For instance:  
&nbsp;  
    ## Udev rules for the Funcube Dongle Pro (0xfb56) and Pro+ (0xfb31)   
    ## HIDAPI/libusb:  
SUBSYSTEMS=="usb" ATTRS{idVendor}=="04d8" ATTRS{idProduct}=="fb56" MODE:="0666"    
SUBSYSTEMS=="usb" ATTRS{idVendor}=="04d8" ATTRS{idProduct}=="fb31" MODE:="0666"  
    ## HIDAPI/hidraw:  
KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="04d8", ATTRS{idProduct}=="fb56", MODE="0666"  
KERNEL=="hidraw*", ATTRS{busnum}=="1", ATTRS{idVendor}=="04d8", ATTRS{idProduct}=="fb31", MODE="0666"  

4.    Usage  
    &nbsp;  
Two modules are available:  
   - fcdpp_control  
   - funcube  

 The control modules only controls the dongles, while the other modules control the dongles and provide the IQ samples.
All modules accept messages to control the frequency. That was the reason to introduce the control modules.
&nbsp;  


5.    Credits  
    &nbsp;  
Some code is taken from qthid-4.1 by Alexandru Csete, OZ9AEC.  

Thanks to Michael Dickens, who gave valuable hints for implementing message in hier2_blocks.
