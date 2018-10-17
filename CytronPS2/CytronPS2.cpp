/*
Original written by:
            Cytron Technologies

Modified:
  29/06/15  Idris, Cytron Technologies    - Point to IDE SoftwareSerial
                                          - Restructure the code style to follow standard Arduino library
*/

#include "HardwareSerial.h"
#include "CytronPS2.h"

/*CytronPS2::CytronPS2(uint8_t rxpin, uint8_t txpin)
{
  _txpin = txpin;
  _rxpin = rxpin;
}
*/
CytronPS2::CytronPS2()
{
  _txpin = 1;
  _rxpin = 0;
}
void CytronPS2::Initialize(uint8_t rxpin, uint8_t txpin)
{
  _txpin = txpin;
  _rxpin = rxpin;
}
void CytronPS2::begin(uint32_t baudrate)
{
	if(_rxpin == 0 && _txpin == 1)
	{
		hardwareSerial = true;
		Serial.begin(baudrate);
		while(!Serial);
	}

	else
	{
		hardwareSerial = false;
		pinMode(_rxpin, INPUT);
		pinMode(_txpin, OUTPUT);
		PS2Serial = new SoftwareSerial(_rxpin, _txpin);
		PS2Serial->begin(baudrate);
	}
	pinMode(A1, OUTPUT);
	digitalWrite(A1, HIGH);
}

void CytronPS2::write(uint8_t data)
{
	if(hardwareSerial)
	{
		while(Serial.available() > 0) {
			Serial.read();
		}
		Serial.write(data);
		Serial.flush();		// Wait for all data transmitted
	}
	else
	{
		while(PS2Serial->available() > 0) {
			PS2Serial->read();
		}
		PS2Serial->write(data);
	}
}

uint8_t CytronPS2::read(void)
{
	uint8_t rec_data;
	long waitcount = 0;

	if(hardwareSerial)
	{
		while(true)
		{
			if(Serial.available() > 0)
			{
				rec_data = Serial.read();
				SERIAL_ERR = false;
				return(rec_data);
			}
			waitcount++;
			if(waitcount > 50000)
			{
				SERIAL_ERR = true;
				return(0xFF);
			}
		}
	}
	else
	{
		while(true)
		{
			if(PS2Serial->available() > 0)
			{
				rec_data = PS2Serial->read();
				SERIAL_ERR = false;
				return(rec_data);
			}
			waitcount++;
			if(waitcount > 50000)
			{
				SERIAL_ERR = true;
				return (0xFF);
			}
		}
	}
}

uint8_t CytronPS2::readButton(uint8_t key)
{
	if(!hardwareSerial) PS2Serial->listen();
	write(key);
	return read();
}

boolean CytronPS2::readAllButton()
{
	uint8_t nbyte;
	uint32_t waitcount;

	write(PS2_BUTTON_JOYSTICK);

	if(hardwareSerial)
	{
		nbyte = Serial.readBytes(ps_data, 6);

		if(nbyte == 6) return(true);
		else return (false);
	}

	else
	{
		waitcount = 0;
		while(PS2Serial->available() < 6)
		{
			waitcount++;
			if(waitcount > 50000) {
				return (false);
			}
		}
		for(int i = 0; i < 6; i++) {
			ps_data[i] = PS2Serial->read();
		}
		return(true);
	}
}

void CytronPS2::vibrate(uint8_t motor, uint8_t value)
{
	uint8_t _motor;

	if(motor == 1) _motor = PS2_MOTOR_1;
	else _motor = PS2_MOTOR_2;

	write(_motor);
	write(value);
}

void CytronPS2::reset(uint8_t reset)
{
	if(reset == 1) digitalWrite(A1, LOW);
	else digitalWrite(A1, HIGH);
}
