#include <Wtv020sd16p.h>

//PUT YOUR CONSTANTS THERE
int timeInSeconds = 3600; //Put your time for timer in seconds. i.e. 60 minutes = 3600 seconds

//PIN Definition
byte aResetPin = 9;  // The pin number of the reset pin.
byte aClockPin = 2;  // The pin number of the clock pin.
byte aDataPin = 10;  // The pin number of the data pin.

byte startBtn = 8;
byte stopBtn = 7;

byte sDATA = A2;
byte sCLK = A3;
byte sLAT = A5;
byte sOE = A4;


//Time variables
unsigned long millisNow = 0;
unsigned long millisPrew = 0;
int interval = 1000;
boolean dotLedState = 1;

//global variables
byte diffCounter = 0;
int secondsLeft = timeInSeconds;

//display arrays
byte displayArray[4] = {255,255,255,255};//display memory

byte interstateMsg[4] = {63,63,63,63};
byte numArray[10] = {192,243,164,161,147,137,136,227,128,129};


//wire state arrays
boolean wireState[8] = {0,0,0,0,0,0,0,0};
boolean prevWireState[8] = {0,0,0,0,0,0,0,0};



Wtv020sd16p audio(aResetPin,aClockPin,aDataPin,NULL);




void updateDisplay()
{
	digitalWrite(sLAT,LOW);
	for (int i = 0;i<4;i++)
	{
		shiftOut(sDATA, sCLK, LSBFIRST, displayArray[i]);	
	}
	digitalWrite(sLAT,HIGH);
}

                                                                                                                 

void setup() {
	audio.reset();
	//Serial.begin(9600);
	//delay(1000);

	//pinmode setup
 
 
	pinMode(sDATA,OUTPUT);
	pinMode(sCLK,OUTPUT);
	pinMode(sLAT,OUTPUT);
	pinMode(sOE,OUTPUT);
	digitalWrite(sOE,LOW);

	
	pinMode(startBtn,INPUT_PULLUP);
	pinMode(stopBtn,INPUT_PULLUP);
	
	//clearDisplay form random garbage 
	clearDisplay();
	
	
	//wait for start button pressed
	for(int i = 0;i<4;i++)
	{
		displayArray[i]=interstateMsg[i];
	}
	updateDisplay();
	while (digitalRead(startBtn))
	{
	}
	millisNow = millis();
	millisPrew = millisNow;
}

/*void correctAnswer()
{	

	audio.asyncPlayVoice(0);//play audio tone
	for(int i = 0;i<4;i++)
	{
		displayArray[i]=interstateMsg[i];
	}
	updateDisplay();
	delay(2000);
	for(int i = 0;i<4;i++)
	{
		displayArray[i]=numArray[password[i]];
	}
	updateDisplay();
	while (1)
	{
		digitalWrite(sOE,LOW);
		digitalWrite(dotLed,LOW);
		delay(1000);
		digitalWrite(sOE,HIGH);
		digitalWrite(dotLed,HIGH);
		delay(1000);
	}
}
*/
void incorrectAnswer()
{
	clearDisplay();

	audio.playVoice(1);
	while(1)
	{

	}
}


void clearDisplay()
{
	//clear display
	for(int i = 0;i<4;i++)
	{
		displayArray[i]=255;
		updateDisplay();
	}
	
	
}


void infLoop ()
{
	while(1){
		delay(1000);
	}
}


void loop() {

	byte minutes = 0;
	byte seconds = 0;
	
	while(secondsLeft>0)
	{
		millisNow = millis();
		if (!(digitalRead(stopBtn)))
		{
			incorrectAnswer();	
		}
		if(millisNow - millisPrew > interval) 
		{ 
			digitalWrite(sOE,HIGH);
			delay(150);
			digitalWrite(sOE,LOW);
			millisPrew = millisNow;
			secondsLeft--;
			minutes = secondsLeft/60;
			seconds = secondsLeft%60;
			displayArray[0]=numArray[minutes/10];
			displayArray[1]=numArray[minutes%10];
			displayArray[2]=numArray[seconds/10];
			displayArray[3]=numArray[seconds%10];
			updateDisplay();
		}
	}
		
	
	
}












