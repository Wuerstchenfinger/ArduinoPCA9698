#ifndef PCA9698_h
#define PCA9698_h

#include "Arduino.h"

//
//!@bief Class for the I2C Port Expander PCA9698 from NXP
class PCA9698{
public:
	//
	//!@brief The Constructor
	PCA9698(void);
	//~PCA9698(void);
	//
	//!@param Adr I2C Adress of the IC.
	//!@brief Starts the Communication between the Arduino and the PCA9698.
	//!@warning The Adresses of the IC can be found in the datasheet. This methode shifts the adress by one to the 
	//! right because the Wire library wants a 7 bit adress.
	void begin(byte Adr);
	//
	//!@param Port The port of the pin.
	//!@param Pin The pin.
	//!@param Func Desired function. OUTPUT or INPUT
	//!@brief Sets the pin of the port as input or output
	void pinMode(byte Port, byte Pin, bool Func);
	//
	//!@param Port The port of the pin.
	//!@param Pin The pin.
	//!@param Stat The logic level of the pin which should be applyed. HIGH or LOW
	//!@brief Sets the pin of the port to the high or low.
	void digitalWrite(byte Port, byte Pin, bool Stat);
	//
	//!@param Port The port of the pin.
	//!@param Pin The pin.
	//!@return The logic level of the pin.
	//!@brief Reads the pin of the port and returns the logic level.
	bool digitalRead(byte Port, byte Pin);
	//
	//!@brief Enables all Ouputs.
	void outputEnable(void);
	//
	//!@brief Disalbes all Ouputs.
	void outputDisable(void);
	//
	//!@param Stat The logic level which should be applyed. HIGH or LOW
	//!@brief Sets all Ouputs of to Low or HiGH
	void digitalWriteALL(bool Stat);
	
	//
	void setOutputs(byte bank0, byte bank1, byte bank2, byte bank3, byte bank4);
	
private:
	//!
	//!Contains the I2C Adress of the slave.
	byte Adr = 0;
	//
	//!@param Reg Register of the IC which should be read.
	//!@return Content of the register.
	//!@brief Retruns one byte which contains the content of the register.
	byte readReg(byte Reg);
	//
	//!@param Reg Register of the IC which should be written to.
	//!@Data One byte of data.
	//!@brief Writes one byte of data to the selected register.
	void writeReg(byte Reg, byte Data);
	
	//
	//!@param Reg Register of the IC which should be written to. 
	//!@param Data A pointer on the first field of an array.
	//!@param length The number of bytes which should be written to the PCA9698.
	//!@brief Writes an array of bytes to the PCA9698.
	//!@waring The last bit of the Reg needs to be set to HIGH for auto incrementation (AI bit).
	void writeMultiReg(byte Reg, byte *Data, int length);
};

#endif
