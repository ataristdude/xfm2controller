# xfm2controller
A controller for the XFM2 Synthesizer using Qt 5.12.
XFM2 is a fantastic FPGA based synthesizer created by Futur3soundz see https://www.futur3soundz.com/xfm2
I do not own XFM2.  This project is just a controller for that synth.

I designed this controller for a Raspberry Pi running an 800x480 touch screen but it will also work for the Desktop.
Here's what you need to know:
1. The application uses the USB serial port to control the synth.  This is set up with a SERIALPORT define in the SynthModel.cpp file.
2. Patch names are stored by the application.  The filename is specified in the PATCHFILE define in the SynthModel.cpp file.
3. On the desktop you probably won't want to run it as a full sceeen app.  Comment out the visibility property in Main.qml

Enjoy!
