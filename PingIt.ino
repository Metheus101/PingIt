/*
 Name:		PingIt.ino
 Created:	08.09.2016 14:40:44
 Author:	gutek
*/


//------------------Defines-------------------

//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define pin_lcd_sda 2;
#define pin_lcd_scl 3;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup() 
{
	lcd.begin(20, 4);               // initialize the lcd 
	lcd.backlight();
	delay(1000);
}

// the loop function runs over and over again until power down or reset
void loop() 
{

	lcd.home();                   // go home
	lcd.print("Hello, ARDUINO ");
	lcd.setCursor(0, 1);        // go to the next line
	lcd.print(" FORUM - fm   ");
	delay(2000);
  
}
