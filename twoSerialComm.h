#ifndef LMSHLIB_H
#define LMSHLIB_H

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <util/delay.h>


/*****************************/
#define MAX_BUF_SIZE      (128)

class twoSerialComm {
  
  public:
      twoSerialComm(HardwareSerial &serial1, SoftwareSerial &serial2); ///< Constructor with address of hardware serial object and software serial object. 
      ~twoSerialComm(); ///< Destructor
      void test(); ///< Test out put to hardware serial line
      void begin(unsigned long baud1, unsigned long baud2); ///< initializing of both serial lines
      void performRead(); ///< performs a read on both serial lines, saves result into buffer and check if line end of buffer end arrived.
	  void performRead2(); ///< optimized version! performs a read on both serial lines, saves result into buffer and check if line end of buffer end arrived.
      char *readSerial(char *buf, int line); ///< Read from serial line (int line --> 0 = both, 1 = hardware serial, 2 = software serial)
      int statusSerial(int line); ///< returns status of buffer, if finished 1 of not 0 (int line --> 0 = both, 1 = hardware serial, 2 = software serial)
      void printToSerial(const char *msg, int line); ///< prints a string to serial line (int line --> 0 = both, 1 = hardware serial, 2 = software serial)
	  void printToSerialSlow(const char* msg, int line); ///< delaySend is a workaround for a possible bug in SoftwareSerial, where to fast sending could corrupt the receiving
  
  private:
      HardwareSerial* _serial1; ///pointer to hardware serial object
      SoftwareSerial* _serial2; ///pointer to software serial object
      char _buf[MAX_BUF_SIZE]; ///buffer for serial 1
      char _buf2[MAX_BUF_SIZE]; ///buffer for serial 2
      int _c; /// helper variable to read one char from serial 1
      int _c2; ///helper variable to read one char from serial 2
      
      int _finished ; /// 0 if read from serial 1 has not been finished (no new line sign or buffer not full), 1 if finished and ready to be handout
      int _finished2; /// 0 if read from serial 2 has not been finished (no new line sign or buffer not full), 1 if finished and ready to be handout
      
      int _i; /// helper variable for serial 1
      int _i2; ///helper variable for serial 2
	  
	  
	  
	
	  
	  
      
};


#endif
