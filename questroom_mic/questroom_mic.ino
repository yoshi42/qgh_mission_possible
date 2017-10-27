unsigned long milisNow = 0;
unsigned long milisPrew = 0;
// the setup routine runs once when you press reset:
byte morseCode[12] ={0,2,1,2,0,2,1,2,0,2,0,2}; // 0 - short , 1 - long , 2 - delay
byte morseCounter = 0;
boolean morseFlag = false;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(13,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
	milisNow = millis();
	if ((milisNow-milisPrew)>=500)
	{	
		milisPrew=milisNow;
		if (morseCode[morseCounter]==0)
		{
			digitalWrite(13,HIGH);
			morseCounter++;
		}else
			if ((morseCode[morseCounter]==1)&&(morseFlag==false))
			{
				digitalWrite(13,HIGH);
				morseFlag = true;
			} else
				if ((morseCode[morseCounter]==1)&&(morseFlag==true))
				{
					digitalWrite(13,HIGH);
					morseFlag = false;
					morseCounter++;
				}else
					if (morseCode[morseCounter]==2)
					{
						digitalWrite(13,LOW);
						morseCounter++;
					}
		if (morseCounter > 13)
		{
			morseCounter = 0;
		}
	}
  // read the input on analog pin 0:
  /*int sensorValue = analogRead(A0);
  if (sensorValue>300)
  {
	  digitalWrite(13,HIGH);
	  delay(300);
	  digitalWrite(13,LOW);
	  
  }
  // print out the value you read:*/
  Serial.println(morseCode[morseCounter]);
  delay(1);        // delay in between reads for stability
}
