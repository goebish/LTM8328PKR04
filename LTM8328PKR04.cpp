//
// LTM-8328PKR-04 4x7 segments display library for Arduino
// goebish 2011
//
//
#include "LTM8328PKR04.h"

// 7 segs digits pattern ( 0,1,2,3,4,5,6,7,8,9,empty,- )
const byte LTM8328PKR04::num[12]={
  		B11111100,B01100000,B11011010,
  		B11110010,B01100110,B10110110,
  		B10111110,B11100000,B11111110,
  		B11110110,B00000000,B00000010};
  		
// letters pattern ( A,C,E,H,L,P,U,°,q )
const byte LTM8328PKR04::letter[9]={
			B11101110,B10011100,B10011110,
			B01101110,B00011100,B11001110,
			B01111100,B11000110,B11100110};

LTM8328PKR04::LTM8328PKR04(byte dataPin,byte clockPin)
{
	m_dataPin=dataPin;
	m_clockPin=clockPin;
  pinMode(m_dataPin, OUTPUT);
  pinMode(m_clockPin, OUTPUT);
  m_leadingZeros=false;
  clear();
}

void LTM8328PKR04::clear()
{
	pushBit(1);
	pushDigit(10);
  pushDigit(10);
  pushDigit(10);
  pushDigit(10);
  pushBit(0);
  pushBit(0);
  pushBit(0);
};

void LTM8328PKR04::printWord(char* word, byte dpPosition)
{
	pushBit(1);
	for(int i=0;i<4;i++)
		pushLetter(word[i],i==dpPosition-1);
	pushBit(0);
	pushBit(0);
	pushBit(0);
}

void LTM8328PKR04::pushLetter(char car,bool decimal)
{
	if(car==' ')
	{
		pushDigit(10,decimal);
		return;
	}
	if(car=='-')
	{
		pushDigit(11,decimal);
		return;
	}	
	if(car>='0' && car<='9')
	{
		pushDigit(car-0x30,decimal);
		return;
	}
	int index=-1;
	switch(car)
	{
		case 'A':
			index=0;
			break;
		case 'C':
			index=1;
			break;
		case 'E':
			index=2;
			break;
		case 'H':
			index=3;
			break;
		case 'L':
			index=4;
			break;
		case 'P':
			index=5;
			break;
		case 'U':
			index=6;
			break;
		case 'd': // ° symbol
			index=7;
			break;
		case 'q':
			index=8;
			break;
	}
	
	if(index==-1)
	{
		pushLetter(' ');
		return;
	}
	for(int segment=7;segment!=0;segment--)
		pushBit((letter[index]>>segment)&1);
	pushBit(decimal);
}

void LTM8328PKR04::print(int number, byte dpPosition)
{
  // send a "1" first
  pushBit(1);
  if( number<-999 or number>9999)
	{
    // ---- out of range
    pushDigit(11);
    pushDigit(11);
    pushDigit(11);
    pushDigit(11);
    pushBit(0);
  	pushBit(0);
  	pushBit(0);
  	return;
  }
  bool positive=number>=0;
  number=abs(number);
  if( number>999)
  {
    pushDigit(number/1000, dpPosition==1);
    pushDigit((number%1000)/100, dpPosition==2);
    pushDigit((number%100)/10, dpPosition==3);
    pushDigit(number%10, dpPosition==4);
  }
  else if( number>99)
  {
    if(positive)
    	pushDigit(m_leadingZeros?0:10, dpPosition==1);
    else
    	pushDigit(11, dpPosition==1);
    pushDigit(number/100, dpPosition==2);
    pushDigit((number%100)/10, dpPosition==3);
    pushDigit(number%10, dpPosition==4);
  }
  else if( number>9)
  {
    if(positive)
    {
    	pushDigit(m_leadingZeros?0:10, dpPosition==1);
    	pushDigit(m_leadingZeros?0:10, dpPosition==2);
    }
    else
    {
    	pushDigit(m_leadingZeros?11:10, dpPosition==1);
    	pushDigit(m_leadingZeros?0:11, dpPosition==2);
    }
    pushDigit(number/10, dpPosition==3);
    pushDigit(number%10, dpPosition==4);
  }
  else
  {
    if(positive)
    {
    	pushDigit(m_leadingZeros?0:10, dpPosition==1);
    	pushDigit(m_leadingZeros?0:10, dpPosition==2);
    	pushDigit(m_leadingZeros?0:10, dpPosition==3);
  	}
  	else
  	{
  		pushDigit(m_leadingZeros?11:10, dpPosition==1);
  		pushDigit(m_leadingZeros?0:10, dpPosition==2);
  		pushDigit(m_leadingZeros?0:11, dpPosition==3);
  	}
    pushDigit(number, dpPosition==4);
  }  
  // then send 3 other bits (2 external leds + 1 final latch clock)
  pushBit(0);
  pushBit(0);
  pushBit(0);
}

void LTM8328PKR04::pushDigit(int digit,bool decimal)
{
  for(int segment=7;segment!=0;segment--)
    pushBit((num[digit]>>segment)&1);
  pushBit(decimal);
}

void LTM8328PKR04::pushBit(bool state)
{
  digitalWrite(m_dataPin, state ? HIGH : LOW);
  digitalWrite(m_clockPin, HIGH);
  digitalWrite(m_clockPin, LOW);
}
