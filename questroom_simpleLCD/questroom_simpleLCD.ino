// include the library code:
#include <LiquidCrystal.h>

byte led = A0;
byte sen1 = A4;
byte sen2 = A5;
byte iteration = 0;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
	pinMode(led,OUTPUT);
	pinMode(sen1,INPUT_PULLUP);
	pinMode(sen2,INPUT_PULLUP);
	lcd.begin(16,2);
	Serial.begin(9600);
}

void loop() {
	if (iteration == 2)
	{
		iteration = 0;
	}
	if ((digitalRead(sen1))&&(digitalRead(sen2)))//insert key
	{
		digitalWrite(led,HIGH);
		lcd.clear();
		lcd.home();
		lcd.print("     PLEASE");
		lcd.setCursor(0,1);
		lcd.print("   INSERT KEY");
	} else //leave the building
	{
		digitalWrite(led,LOW);
		if (iteration == 1)
		{
			iteration = 2;
			lcd.clear();
			lcd.home();
			lcd.print("   LEAVE  THE");
			lcd.setCursor(0,1);
			lcd.print("    BUILDING");
			delay(1300);
		}
		if (iteration == 0)
		{
			iteration = 1;
			lcd.clear();
			lcd.home();
			lcd.print("     SYSTEM");
			lcd.setCursor(0,1);
			lcd.print("    UNLOCKED");
			delay(1300);
		} 
	}
	delay(1000);
}