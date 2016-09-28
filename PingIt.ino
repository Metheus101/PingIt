/*
 Name:		PingIt.ino
 Created:	08.09.2016 14:40:44
 Author:	gutek
*/
String version="V0.1.2";
//--------------------------------------------------
int sendelay = 50;
int sensornr = 1;//|1=HC-SR04|
//--------------------------------------------------

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//------------------Defines-------------------

//LCD
#define pin_lcd_sda 2
#define pin_lcd_scl 3
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

//Ultraschall Sensor HC SR-04
#define pin_senhc1_trig A0
#define pin_senhc1_echo A1
#define pin_senhc2_trig A2
#define pin_senhc2_echo A3
float dist_sen1 = 0;
float time_sen1 = 0;
float dist_sen2 = 0;
float time_sen2 = 0;
uint32_t mtimestart = 0;
uint32_t mtime = 0;
float mcount = 0;

void setup() 
{
	switch (sensornr)
	{
	case 1:
		hcinit();
		break;
	}

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
	delay(2000);
	lcd.clear();
}

//Initialisierung HC
void hcinit()
{
	//Ultraschall Sensor HC SR-04
	pinMode(pin_senhc1_trig, OUTPUT);
	pinMode(pin_senhc1_echo, INPUT);
	pinMode(pin_senhc2_trig, OUTPUT);
	pinMode(pin_senhc2_echo, INPUT);
	digitalWrite(pin_senhc1_trig, LOW);
	digitalWrite(pin_senhc2_trig, LOW);
}
//Messung HC
void hcmeasure()
{
	//Messung Sensor 1
	noInterrupts();
	digitalWrite(pin_senhc1_trig, HIGH); //Trigger Impuls 10 us
	delayMicroseconds(10);
	digitalWrite(pin_senhc1_trig, LOW);
	time_sen1 = pulseIn(pin_senhc1_echo, HIGH); // Echo-Zeit messen
	interrupts();
	time_sen1 = (time_sen1 / 2); // Zeit halbieren
	dist_sen1 = time_sen1 / 29.1; // Zeit in Zentimeter umrechnen
	delay(sendelay);
	//Messung Sensor 2
	noInterrupts();
	digitalWrite(pin_senhc2_trig, HIGH); //Trigger Impuls 10 us
	delayMicroseconds(10);
	digitalWrite(pin_senhc2_trig, LOW);
	time_sen2 = pulseIn(pin_senhc2_echo, HIGH); // Echo-Zeit messen
	interrupts();
	time_sen2 = (time_sen2 / 2); // Zeit halbieren
	dist_sen2 = time_sen2 / 29.1; // Zeit in Zentimeter umrechnen
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	mtimestart = millis();
	switch (sensornr)
	{
	case 1:
		hcmeasure();
		break;
	}
	
	mtime = (millis() - mtimestart);
	mcount = 1 / (mtime*0.001);

	//Ergebnis anzeigen
	lcd.home();
	lcd.print(String("Sen1:  ")+(dist_sen1) + ("cm     "));
	lcd.setCursor(0, 1);
	lcd.print(String("Sen2:  ")+(dist_sen2) + ("cm     "));
	lcd.setCursor(0, 2);
	lcd.print(String("Messzeit:  ")+ (mtime)+("ms     "));
	lcd.setCursor(0, 3);
	lcd.print(String("Messungen/s:  ")+(mcount)+(" "));
	delay(500);
	
}
