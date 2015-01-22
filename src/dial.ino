#define NUM_DIGITS 4
//HARDWARE SETUP:
//ground the green and black wires of the dial.
const unsigned int dialEnablePin=10; //blue
const unsigned int dialTickPin=16; //purple
const unsigned int lockPin=A2; //low=lock
const unsigned int code[4]={1,2,3,4};


void setup()   {
	Serial.begin(9600);
	TX_RX_LED_INIT;
	pinMode(dialEnablePin,INPUT_PULLUP);
	pinMode(dialTickPin,INPUT_PULLUP);
	pinMode(lockPin,OUTPUT);
	digitalWrite(lockPin,LOW);
}

boolean tickArmed=false;
unsigned int ticks=0;
unsigned int incomingDigitCount=0;

void loop()
{

while(digitalRead(dialEnablePin)==HIGH) RXLED0; //wait for start of dial

while(digitalRead(dialEnablePin)==LOW)
	{
		RXLED1;

		if(digitalRead(dialTickPin)==HIGH && tickArmed==true) //Rising edge
			{
				ticks++;
				tickArmed=false;
				TXLED1;
				delay(50);
			}

		else if(digitalRead(dialTickPin)==LOW) //falling edge
			{
				tickArmed=true;
				TXLED0;
				delay(50);
			}

	}

if(ticks>9) ticks=0; //10 ticks = 0

//check if input digit matches code
if(ticks!=code[incomingDigitCount++]) while(1){ /* WRONG CODE LOOP */ }

ticks=0;

if (incomingDigitCount==NUM_DIGITS) //when NUM_DIGITS correct digits have been input
	{
		digitalWrite(lockPin,HIGH); //unlock
		while(1){/*wait for reset*/}
	}

}
