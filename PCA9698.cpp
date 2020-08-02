#include "Arduino.h"
#include "Wire.h"
#include "PCA9698.h"

PCA9698::PCA9698()
{
	Adr = 0x0;
}


void PCA9698::begin(byte adr)
{
	Adr = adr;
	Wire.begin();
	Wire.setClock(400000);
}

void PCA9698::pinMode(byte Port, byte Pin, bool Func)
{
	if(Port >= 0 && Port <= 4 && Pin >= 0 && Pin <= 7)
	{
		byte Reg = 0x18 + Port;
		byte Data = readReg(Reg);
		if(Func == OUTPUT)
		{
			Data &= ~(1 << Pin);
		}
		if(Func == INPUT)
		{
			Data |= (1 << Pin);
		}
		writeReg(Reg, Data);	
	}
	
}
void PCA9698::digitalWrite(byte Port, byte Pin, bool Stat)
{
	if(Port >= 0 && Port <= 4 && Pin >= 0 && Pin <= 7)
	{
		byte Reg = 0x08 + Port;
		byte Data = readReg(Reg);
		if(Stat == LOW)
		{
			Data &= ~(1 << Pin);
		}
		if(Stat == HIGH)
		{
			Data |= (1 << Pin);
		}
		writeReg(Reg, Data);	
	}
}

void PCA9698::setOutputs(byte bank0, byte bank1, byte bank2, byte bank3, byte bank4)
{
	byte Reg = 0x88; //AI bit 1 
	int length = 5;
	byte Data [] = {bank0, bank1, bank2, bank3, bank4};
	writeMultiReg(Reg, Data, length);
}

bool PCA9698::digitalRead(byte Port, byte Pin)
{
	if(Port >= 0 && Port <= 4 && Pin >= 0 && Pin <= 7)
	{
		byte Reg = 0x00 + Port;
		byte Data = readReg(Reg);
		return bool((Data >> Pin) & 0x01);
	}
}

void PCA9698::outputEnable(void)
{
	byte Reg = 0x2A;
	byte Data = readReg(Reg);
	Data &= ~(1 << 0);
	writeReg(Reg, Data);
}

void PCA9698::outputDisable(void)
{
	byte Reg = 0x2A;
	byte Data = readReg(Reg);
	Data |= (1 << 0);
	writeReg(Reg, Data);
}

void PCA9698::digitalWriteALL(bool Stat)
{
	byte Reg = 0x29;
	byte Data = 0;
	byte Data2 = 0;
	byte Data3 = 0;
	if(Stat == HIGH)
	{
		Data = 0b10011111;
		Data3 = 0b11111111;
		Data2 = 0b00011111;
	}
	else if(Stat == LOW)
	{
		Data = 0b00000000;
		Data3 = 0b00000000;
		Data2 = 0b10000000;
	}
	writeReg(Reg, Data);
	for(uint8_t RegOut = 0x08; RegOut <= 0x0C; RegOut++) //refresh Output register
		writeReg(RegOut, Data3);
	writeReg(Reg, Data2);
}


void PCA9698::writeReg(byte Reg, byte Data)
{
	Wire.beginTransmission(Adr);
	Wire.write(uint8_t(Reg));
	Wire.write(uint8_t(Data));
	Wire.endTransmission();
}

void PCA9698::writeMultiReg(byte Reg, byte *Data, int length)
{
	Wire.beginTransmission(Adr);
	Wire.write(Reg);
	Wire.write(Data, length);
	Wire.endTransmission(Adr);
}

byte PCA9698::readReg(byte Reg)
{
	Wire.beginTransmission(Adr);
	Wire.write(uint8_t(Reg));
	Wire.endTransmission();
	Wire.requestFrom(Adr, 1);
	return Wire.read();
}