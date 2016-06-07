
#include "twoSerialComm.h"


//<<constructor>>
/****************************************************************************/
twoSerialComm::twoSerialComm(HardwareSerial &serial1, SoftwareSerial &serial2)
/****************************************************************************/
{
  _serial1 = &serial1; //operate on the adress of serial1
  _serial2 = &serial2;
  
  
   _buf[0] = 0;
   _buf2[0] = 0;
 
   _i = 0;
   _i2 = 0;
 
   _c = 0;
   _c2 = 0;
 
   _finished = 0;
   _finished2 = 0;
   
   
}

//<<destructor>>
/****************************************************************************/
twoSerialComm::~twoSerialComm() 
/****************************************************************************/
{

}

/****************************************************************************/
void twoSerialComm::test() 
/****************************************************************************/
{
   _serial1->println("Hello library with serial connectivity!");
}

/****************************************************************************/
void twoSerialComm::begin(unsigned long baud1, unsigned long baud2)
/****************************************************************************/
{
	_serial1->begin(baud1);
	_delay_ms(100);
	_serial2->begin(baud2);
	
	char msg1[100];
	sprintf(msg1, "Set serial line 1 to %lu Baud.", baud1);
	
	char msg2[100];
	sprintf(msg2, "Set serial line 2 to %lu Baud.", baud2);
   
	_serial1->println(msg1);
	_serial1->println(msg2);
}

/****************************************************************************/
void twoSerialComm::performRead()
/****************************************************************************/
{
  _c = 0;
  _c2 = 0;
  
  /* read form Serial line 1 */
   if(_serial1->available() > 0)
  {
    _c = _serial1->read();
    if(_c == 0)
    {
      return;
    }
    _buf[_i] = _c;
    _i++;
    
    if(_c == 10)
    {
      _buf[_i] = 0;
      _finished = 1;
      
    }
    else
    {
      if( _i > 0 && _i == MAX_BUF_SIZE -1)
      {
         _buf[_i] = 0;
        _finished = 1; 
      }
      
      
    } 
    
  }
  
  /* read from Serial Line 2 */
   if(_serial2->available() > 0)
  {
    _c2 = _serial2->read();
    if(_c2 == 0)
    {
      return;
    }
    _buf2[_i2] = _c2;
    _i2++;

    if(_c2 == 10)
    {
      _buf2[_i2] = 0;
      _finished2 = 1;
      
    }
    else
    {
      if( _i2 > 0 && _i2 == MAX_BUF_SIZE -1)
      {
         _buf2[_i2] = 0;
        _finished2 = 1; 
        
      }
      
      
    } 
    
  }
  
  
}

/****************************************************************************/
void twoSerialComm::performRead2()
/****************************************************************************/
{
  _c = 0;
  _c2 = 0;
  int i = 0;
  
  int byteCount = 0;
  
  byteCount = _serial1->available();
  
  /* read form Serial line 1 */
  if(byteCount > 0)
  {
	for(i = 0; i < byteCount; i++)
	{
		  _c = _serial1->read();
		    if(_c == 0)
		    {
		      return;
		    }
		    _buf[_i] = _c;
		    _i++;
		    
		    if(_c == 10)
		    {
		      _buf[_i] = 0;
		      _finished = 1;
			  return;
		      
		    }
		    else
		    {
		      if( _i > 0 && _i == MAX_BUF_SIZE -1)
		      {
		         _buf[_i] = 0;
		        _finished = 1; 
				return;
		      }
		      
		      
		    } 
		    
	}
	  
  }
  
  byteCount = 0;
  
  byteCount = _serial2->available();
  
  /* read from Serial Line 2 */
  if(byteCount > 0)
  {
	  
	  
	 for(i = 0; i < byteCount; i++)
	 {
		 _c2 = _serial2->read();
    	if(_c2 == 0)
    	{
      		return;
    	}
    	_buf2[_i2] = _c2;
    	_i2++;
    
		
	    if(_c2 == 10)
	    {
	      _buf2[_i2] = 0;
	      _finished2 = 1;
		  return;
	      
	    }
	    else
	    {
	      if( _i2 > 0 && _i2 == MAX_BUF_SIZE -1)
	      {
	         _buf2[_i2] = 0;
	        _finished2 = 1; 
			return;
	        
	      }
	      
	      
	    } 
		
	 }
	 
  }
  
  
}


/****************************************************************************/
char *twoSerialComm::readSerial(char *buf, int line)
/****************************************************************************/
{
	
    switch(line) 
    {
      case 1:
      
          if(_finished == 1)
          {
			  strcpy(buf, _buf);
			  
            
              /* Clean up buffer */
              _i = 0;
              _buf[_i] = 0;
              _finished = 0;
              
              return buf;
            
          }
          else
          {
            return NULL;
            
          }
          
      
        break;
        
        
      case 2:
      
        if(_finished2 == 1)
          {
			  strcpy(buf, _buf2);
              
				
             /* Clean up buffer */
              _i2 = 0;
              _buf2[_i2] = 0;
              _finished2 = 0;
			  
              return buf;
              
 
          }
          else
          {
            return NULL;
            
          }
      
        break;
        
        
      default:
      
        return NULL;
        
        break;
      
      
    }
}

/****************************************************************************/
int twoSerialComm::statusSerial(int line)
/****************************************************************************/
{
  if(line == 1)
  {
    return _finished;
    
  }
  else if(line == 2)
  {
    return _finished2;
  }
  else
  {
    return -1;
    
  }
  
}





/****************************************************************************/
void twoSerialComm::printToSerial(const char* msg, int line)
/****************************************************************************/
{
	
	
	switch(line) {

	    case 0:
		
	      _serial1->println(msg);
	      _serial2->println(msg);
	      break;
	   
	   case 1:
	     _serial1->println(msg);
	     break;
	     
	  case 2:
	    _serial2->println(msg);
	    break;
	    
	   default:
	   
	     break;
	    
	 }


	
  
}


/****************************************************************************/
void twoSerialComm::printToSerialSlow(const char* msg, int line)
/****************************************************************************/
{
	int i = 0;
	int length = strlen(msg);
	
	
	for(i=0; i < length; i++) {
		
		switch(line) {
			case 0:
				_serial1->write(msg[i]);
				_serial2->write(msg[i]);
			
			break;
			
			case 1:
				_serial1->write(msg[i]);
			
			break;
			
			case 2:
				_serial2->write(msg[i]);
			
			break;
			
			default:
			
			break;
		}
		delay(1);
	}
	
	//send CR
	switch(line) {
			case 0:
				_serial1->write(13);
				_serial1->write(10); //for more comfort reading the serial interface
				_serial2->write(13);
			
			break;
			
			case 1:
				_serial1->write(13);
				_serial1->write(10); //for more comfort reading the serial interface
			
			break;
			
			case 2:
				_serial2->write(13);
			
			break;
			
			default:
			
			break;
		}
	
	
	
}