// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       vifte.ino
    Created:	09.09.2018 21.57.43
    Author:     KONTORMASKIN\skule
*/
int i=0;
int freq = 2000;
int channel = 0;
int resolution = 8;
int dutyCycle = 250;
//#define stby 23
//#define ain1 22
//#define ain2 19

#define pwa 22

// The setup() function runs once each time the micro-controller starts
void setup()
{
	Serial.begin(115200);
	pinMode(pwa, OUTPUT); // pwm

//	pinMode(ain1, OUTPUT); //A1
//	pinMode(stby, OUTPUT); //A1
/*
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(22, channel);
	ledcWrite(22, 100);
*/
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(pwa, channel);
	ledcWrite(channel, 0);
	freq = 10000;
	ledcWriteTone(channel, freq);
/*
	digitalWrite(ain2, HIGH);
	digitalWrite(ain1, HIGH);
	digitalWrite(stby, HIGH);
	*/
//	digitalWrite(pwa, HIGH);
 i = 10;
 Serial.println(i);
}

// Add the main program code into the continuous loop() function
void loop()
{
/* 	Serial.println(i);
		ledcAttachPin(pwa, channel);
		ledcWrite(channel, i);
    Serial.println(i);
		i=i+10;
		delay(100);
		if (i > 1000) i = 10;

		*/
}
