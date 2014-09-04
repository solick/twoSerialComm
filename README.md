twoSerialComm
=============

Library for working with two serial lines on arduino (e.g. hardware serial and XBee Software serial)

A complete documentation can be found at /html/index.php which has been created with doxygen.

This small project was created to work on an arduino with two serial interfaces, read and write complete lines and provide some abstration to the interfacing with the Hardware- and SoftwareSerial libraries.

# Installation

- Place the folder twoSerialComm into your Arduino library folder.
- Restart Arduino IDE
- Include the library at your source code with `#include <twoSerialComm.h>`
- Include also the SoftwareSerial library with `#include <SoftwareSerial.h>`
- Initialize your SoftwareSerial instance with e.g. `SoftwareSerial mySerial(10, 11); // RX, TX`
- Than initialize the twoSerialComm instance with `twoSerialComm serCom(Serial, mySerial);`

# Usage

Within your setup function you need to initialize both serial lines.

	serCom.begin(57600, 9600); /* baud rate serial 1, baud rate serial2
	serCom.test(); /* prints a test message to serial 1
	serCom.printToSerial("Device ready",0); /* prints Device ready to both serial lines

At your loop function you can now read from both seria line buffers by just calling the following function:

	serCom.performRead();
	serCom.performRead2();

The main difference between both functions is, that performRead only reads one sign per loop while performRead2 reads all available signs within one loop. 

Now you can check if some message has been read from serial buffer by using the function call `serCom.statusSerial(1)` where the parameter is the serial line number.

It returns 0 if nothing is available, 1 if something has been read out from buffer. 

** Please note that the performRead and performRead2 end the read from buffer if a CL sign (integer 10) or the maximum buffer (127 Byte) has reached.**

If statusSerial returns 1 for a line, you can get the result with `sercom.readSerial(pointer, line)`

A complete example for readout would be like the following:

	char buf1[160];
	buf1[0] = 0;
	char *bufP1 = buf1;
	serCom.readSerial(bufP1, 1);


