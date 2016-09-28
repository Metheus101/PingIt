/*
 Name:		PingIt.ino
 Created:	08.09.2016 14:40:44
 Author:	gutek
*/
String version="V0.1.1";

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//------------------Defines-------------------

//LCD
#define pin_lcd_sda 2
#define pin_lcd_scl 3
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

//Ultraschall Sensor HC SR-04
#define pin_senhc1_trig 0
#define pin_senhc1_echo 1
#define pin_senhc2_trig 2
#define pin_senhc2_echo 3
long dist_sen1 = 0;
long time_sen1 = 0;
long dist_sen2 = 0;
long time_sen2 = 0;


void setup() 
{
	//Ultraschall Sensor HC SR-04
	pinMode(pin_senhc1_trig, OUTPUT);
	pinMode(pin_senhc1_echo, INPUT);
	pinMode(pin_senhc2_trig, OUTPUT);
	pinMode(pin_senhc2_echo, INPUT);

	//LCD
	lcd.begin(20, 4);             // initialize the lcd 
	lcd.backlight();			//Licht an
	lcd.home();                   // go home
	lcd.print("Ping It");
	lcd.setCursor(12, 0);        
	lcd.print(version);
	lcd.setCursor(0, 1);        // go to the next line
	lcd.print("Autor:");
	lcd.setCursor(0, 2);        // go to the next line
	lcd.print("Markus Gutekunst");
	lcd.setCursor(0, 3);        // go to the next line
	lcd.print("Lab. Prof. Haller");
	delay(400);

	delay(1000);
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	//Messung Sensor 1
	long dist_sen1 = 0;
	long time_sen1 = 0;

	digitalWrite(trigger, LOW);
	delayMicroseconds(3);
	noInterrupts();
	digitalWrite(trigger, HIGH); //Trigger Impuls 10 us
	delayMicroseconds(10);
	digitalWrite(trigger, LOW);
	zeit = pulseIn(echo, HIGH); // Echo-Zeit messen
	interrupts();
	zeit = (zeit / 2); // Zeit halbieren
	entfernung = zeit / 29.1; // Zeit in Zentimeter umrechnen
	return(entfernung);
  
}
