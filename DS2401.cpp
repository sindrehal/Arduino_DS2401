/*
The MIT License (MIT)

Copyright (c) 2016 Sindre Halbjørhus - sindre@ihemsedal.no

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#define DEBUG

#include "DS2401.h"

DS2401::DS2401(OneWire* _oneWire)
{
	_wire = _oneWire;
	_crcValid = false;
}

bool DS2401::init()
{
	if (_wire->reset())
	{
		GetData();
		return true;
	}
	else
	{
		return false;
	} 
}

bool DS2401::isDS2401()
{
	if (_data[0] == DS2401_FAMILY_CODE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

uint32_t DS2401::GetSerial()
{
	IsCRCValid();

	if (!_crcValid)
	{
		Serial.println("CRC Not Valid!!!");
		return false;
	}

	for (int i = 1; i < 6; i++)
	{
		Serial.print(_data[i]);
	}
}

void DS2401::GetData()
{
	_wire->write(DS2401_READ_ROM_COMMAND);

	for (int i = 0; i < 7; i++)
	{
		_data[i] = _wire->read();
	}
}

void DS2401::IsCRCValid()
{
	byte crc = _data[7];
	byte calc = _wire->crc8(_data, 7);

	if (calc != crc)
	{
		_crcValid = false;
	}
	else
	{
		_crcValid = true;
	}
}
