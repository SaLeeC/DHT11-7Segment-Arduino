/*
 * Spazio per la gestione del display 7 segmenti 8 digit tramite MAX7219
*/


/* Include DigitLedDisplay Library */
//#include "DigitLedDisplay.h"

/* Arduino Pin to Display Pin
   12 to DIN,
   10 to CS,
   11 to CLK */
//DigitLedDisplay ld = DigitLedDisplay(12, 10, 11);

void MAX7219setup() 
{
  /* Set the brightness min:1, max:15 */
  ld.setBright(10);

  /* Set the digit count */
  ld.setDigitLimit(8);
}



void MAX7219TempUmid()
{
    ld.clear();
    ld.setBright(10);    
    ld.write(3, B00011100);    
    ld.printDigit(DHT11Umidita[0], 0);
    ld.write(5, B01100011);    
    ld.write(8, B00001111);    
    ld.printDigit(DHT11Temperatura[0], 5);
    DHT11News = 0;
}

void MAX7219Min()
{
    ld.clear();
    ld.setBright(10);    
    ld.write(3, B00011100);    
    ld.printDigit(DHT11Umidita[3], 0);
    ld.write(5, B01100011);    
    ld.write(8, B00001111);    
    ld.printDigit(DHT11Temperatura[3], 5);
    ld.write(4, B00011000);
}

void MAX7219Max()
{
    ld.clear();
    ld.setBright(10);    
    ld.write(3, B00011100);    
    ld.printDigit(DHT11Umidita[4], 0);
    ld.write(5, B01100011);    
    ld.write(8, B00001111);    
    ld.printDigit(DHT11Temperatura[4], 5);
    ld.write(4, B01000010);
}


void MAX7219FlashPoint()
{
  switch (MAX7219Flash)
  {
    case 0:
      ld.write(4, B01000000);
      MAX7219Flash++;
      break;
    case 1:
      ld.write(4, B00000001);
      MAX7219Flash++;
      break;
    case 2:
      ld.write(4, B00001000);
      MAX7219Flash = 0;
      break;
    default:
      break;
  }
}

