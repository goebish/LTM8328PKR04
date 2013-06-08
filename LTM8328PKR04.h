#ifndef LTM8328PKR04_H_
#define LTM8328PKR04_H_

#if (ARDUINO >= 100)
	#include <Arduino.h>
#else
	#include <WProgram.h>
#endif

class LTM8328PKR04
{
	public:
		LTM8328PKR04(byte dataPin,byte clockPin);
		void setLeadingZeros(bool value=true){m_leadingZeros=value;}
		void clear();
		void print(int number, byte dpPosition=0); // print number with optional decimal point at position dpPosition
		void printWord(char* word, byte dpPosition=0); // print a 4 letters word with the few available letters
	private:
		void pushDigit(int digit,bool decimal=false);
		void pushLetter(char car,bool decimal=false);
		void pushBit(bool state);
		byte m_dataPin,m_clockPin;
		bool m_leadingZeros;
		static const byte num[12];
		static const byte letter[9];
};

#endif