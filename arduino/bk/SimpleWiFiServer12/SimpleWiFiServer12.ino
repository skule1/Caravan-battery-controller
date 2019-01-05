/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin

bat1 (true=innkoblet/false) og bat2 viser klientens forespørlel til server
ld1, ld2 low når den lyser, HIGH når den slukker, verdi for lcd-lamper.
alarm1/alarm2 (true/false)  alarm på hver kanal.

 
 */
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include <WiFi.h>

const char* ssid     = "dlink";
const char* password = "12345abc";

WiFiServer server(60);



#define batteri1  6
#define batteri2  7

#define  Led1 16
#define  Led2 17
#define  Rele1 26
#define  Rele2 25
#define  Push1 4
#define  Push2 0
#define  U1 A5
#define U2 A4
#define T1 A0
#define T2 A3
#define I1 A6
#define I2 A7
#define gas A17
#define kab_temp A18
#define lade_spenning A19

float grense_volt_min = 12;
float grense_volt_maxg = 15;
float strom_max = 20;
float grense_temp = 70;
float grense_temp_kab = 40;

int l = 0,k=0;



int ThermistorPin = A0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float Temp1 = 20, Temp2 = 20, Up1 = 13, Up2 = 13, Strom1 = 10, Strom2 = 10,gass=7 ;
float KabTemp = 0, LadeSpenning = 0;
float Max_temp = 60, Max_strom = 50, Min_spenning = 11, grense_gass = 10,offs1,offs2;
boolean bat1 = true, bat2 = true,alarm1=false,alarm2=false, alarm1_ok= false, alarm2_ok = false;;  // bat1 og bat2 viser klientens forespørlel til server

float rest,prevrest;
int tid;
boolean gg;
boolean  ld2,ld1;   // ld1, ld2 low når den lyser, HIGH når den slukker
IPAddress ip;

IPAddress local_IP(192, 168, 10, 95);
IPAddress gateway(192, 168, 10,1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(192,168, 10,113); //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

int value = 0;
int j;

int freq = 10000;
int channel = 0;
int resolution = 8;
int dutyCycle = 255;
#define pwa 22

void setupy()
{
	Serial.begin(115200);
	pinMode(gas, INPUT);
	//	pinMode(A16, INPUT);
	pinMode(4, INPUT);
	pinMode(A11, INPUT);
	pinMode(A0, INPUT);
	pinMode(A3, INPUT);
	pinMode(A6, INPUT);
	pinMode(A7, INPUT);
	pinMode(A4, INPUT);
	pinMode(A5, INPUT);
	pinMode(A18, INPUT);
	pinMode(Push1, INPUT);
	pinMode(Push2, INPUT);
	pinMode(Led1, OUTPUT); //
	pinMode(Led2, OUTPUT);
	pinMode(Rele1, OUTPUT);
	pinMode(Rele2, OUTPUT);
	digitalWrite(Rele1, LOW);
	if (digitalRead(Rele1) == HIGH) digitalWrite(Led1, HIGH); else digitalWrite(Led1, LOW);
	delay(1000);
	digitalWrite(Rele1, HIGH);
	if (digitalRead(Rele1) == HIGH) digitalWrite(Led1, HIGH); else digitalWrite(Led1, LOW);
}

void setup99()
{
	Serial.begin(115200);
//	pinMode(4, INPUT);
	pinMode(A10, INPUT);
}

void setup()
{
    Serial.begin(115200);
	Serial.println(__FILE__);
	Serial.print("Kompilert: "); Serial.println(__TIMESTAMP__);
 //   pinMode(5, OUTPUT);      // set the LED pin mode
//	pinMode(gas, INPUT);
	//pinMode(A16, INPUT);
    delay(10);
	

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		delay(5000);
		ESP.restart();
	}

	// Port defaults to 3232
	// ArduinoOTA.setPort(3232);

	// Hostname defaults to esp3232-[MAC]
	// ArduinoOTA.setHostname("myesp32");

	// No authentication by default
	// ArduinoOTA.setPassword("admin");

	// Password can be set with it's md5 value as well
	// MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
	// ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

	ArduinoOTA
		.onStart([]() {
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH)
			type = "sketch";
		else // U_SPIFFS
			type = "filesystem";

		// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
		Serial.println("Start updating " + type);
	})
		.onEnd([]() {
		Serial.println("\nEnd");
	})
		.onProgress([](unsigned int progress, unsigned int total) {
		Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	})
		.onError([](ota_error_t error) {
		Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR) Serial.println("End Failed");
	});

	ArduinoOTA.begin();

	Serial.println("Ready");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	


	pinMode(gas, INPUT);
//	pinMode(A16, INPUT);
	pinMode(4, INPUT);
	pinMode(A11, INPUT);
    pinMode(A0, INPUT);
	pinMode(A3, INPUT);
	pinMode(A6, INPUT);
	pinMode(A7, INPUT);
	pinMode(A4, INPUT);
	pinMode(A5, INPUT);
	pinMode(A18, INPUT);
	pinMode(Push1, INPUT);
	pinMode(Push2, INPUT);
	pinMode(Led1, OUTPUT); //
	pinMode(Led2, OUTPUT);
	pinMode(Rele1, OUTPUT);
	pinMode(Rele2, OUTPUT);



	digitalWrite(Rele1, HIGH); // Rele p�sl�tt
	digitalWrite(Rele2, HIGH);
	delay(200);
	offs1 = analogRead(I1);
	offs2 = analogRead(I2);
	delay(200);
	digitalWrite(Led1, LOW); // led p�sl�tt
	digitalWrite(Led2, LOW);
	digitalWrite(Rele1, LOW); // Rele p�sl�tt
	digitalWrite(Rele2, LOW);

	
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
		Serial.println("STA Failed to configure");
	}

	Serial.println("");
	Serial.println("WiFi connected.");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	server.begin();
	// We start by connecting to a WiFi network

	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
	dutyCycle = 0;
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(pwa, channel);
//	ledcWrite(channel, dutyCycle);
//	freq = 10000;
 //   ledcWrite(channel, dutyCycle);
//ledcWriteTone(channel, freq);

}

void loop66()
{
	WiFiClient client = server.available();   // listen for incoming clients
	if (client)
	{
		Serial.println("New Client.");           // print a message out the serial port
		String currentLine = "";                // make a String to hold incoming data from the client
		while (client.connected()) {            // loop while the client's connected
			while (client.available()) {             // if there's bytes to read from the client,
				char c = client.read();             // read a byte, then
		//		Serial.print(c);
				if (c != '\n') { 	//			Serial.write(c);
					currentLine += c;
				}
				else
				{
					Serial.println(currentLine);
					currentLine = "";

				};
			};
				/*		else
						{
							client.stop();
							Serial.println("Client Disconnected.2");
						}
						*/
				Les_temperatur1();
				Les_spenning1();
				client.print("T1 \t");
				client.println(Temp1);
				//client.println(" C");
				client.print("U1 \t");
				client.println(Up1);
				client.stop();
				Serial.println("Client Disconnected2.");
			}
	
	client.stop();
		Serial.println("Client Disconnected.");
	}

}

void loop_tom() {}

void loop()
{
	ArduinoOTA.handle();
	//Serial.println("loop");
	Les_temperatur1();
	Les_temperatur2();
	Les_strom1();
	Les_strom2();
	Les_spenning1();
	Les_spenning2();
	Les_ladespenning();
	Les_kabinetttemp();
    Les_gass();
	sjekk_verdier(false);
	Send_til_klient();
	Vis_parametre();
	//	les_touch();
	//	alarm();
	if ((alarm1) || (alarm2)) blinkLCD();
	if (alarm1) digitalWrite(Rele1, HIGH); else
	{
		if (digitalRead(Rele1) == HIGH) digitalWrite(Led1, HIGH); else digitalWrite(Led1, LOW);
	}
	if (alarm2) digitalWrite(Rele2, HIGH); else
	{
		if (digitalRead(Rele2) == HIGH) digitalWrite(Led2, HIGH); else digitalWrite(Led2, LOW);
	}
	delay(1000);

}

void loop33()
{
	int i = analogRead(gas);
	Serial.println(i);
	delay(500);
}
boolean sjekk_verdier(boolean mode)
{
	if ((Temp1 > Max_temp) || (Strom1 > Max_strom) || (Up1 < Min_spenning)) alarm1 = true;
		else if (mode) alarm1 = false;

	if ((Temp2 > Max_temp) || (Strom2 > Max_strom) || (Up2 < Min_spenning)) alarm2 = true;
		else if (mode) alarm2 = false;
		
		/*	if (Temp2 > Max_temp) alarm2 = true;
	if (Strom1 > Max_strom) alarm1 = true;
	if (Strom2 > Max_strom) alarm2 = true;
	if (Up1 < Min_spenning) alarm1 = true;
	if (Up2 < Min_spenning) alarm2 = true;
	//	if (gass > grense_gass) alarm1 = true;

*/	return alarm1 || alarm2;

/*	if (digitalRead(Rele1) == HIGH) digitalWrite(Led1, LOW); else digitalWrite(Led1, HIGH);
	if (digitalRead(Rele2) == HIGH) digitalWrite(Led2, LOW); else digitalWrite(Led2, HIGH);
	*/

}
void Les_temperatur1() {
	Vo = analogRead(A0) / 2.80;
	//  Vo = 550;
//	Serial.print("Vo:");
//	Serial.println(Vo);
	R2 = R1 * (1023.0 / (float)Vo - 1.0);
	logR2 = log(R2);
	T = (1.0 / (c1 + c2 * logR2 + c3 * logR2*logR2*logR2)); 
	Temp1 = T - 273.15;
//	Serial.println(String("Temp1a: ") + Temp1);
	//	  Temp1 = (Tc * 9.0) / 5.0 + 32.0;
}
void Les_temperatur2() {
	Vo = analogRead(A3) / 2.8;
	//Serial.print("Vo:");
	//Serial.println(Vo);
	R2 = R1 * (1023.0 / (float)Vo - 1.0);
	logR2 = log(R2);
	T = (1.0 / (c1 + c2 * logR2 + c3 * logR2*logR2*logR2));
	Temp2 = T - 273.15;
//	Serial.println(String("Temp2a: ") + Temp2);
	//  Temp2 = (Tc * 9.0) / 5.0 + 32.0;
}
void Les_strom1() {
     Serial.print("Les I1: ");
     Serial.print(offs1);
     Serial.print("\t");
     Serial.print(analogRead(I1));
     Serial.print("\t");
  //   Serial.println(analogRead(I1)-offs1);
     Strom1 = (analogRead(I1)-offs1)/10;
      Strom1=Strom1*5.6/7.7;
      Serial.println(Strom1);
}
void Les_strom2() {
     Serial.print("Les I2: ");
     Serial.println(analogRead(I2)-offs1);
	Strom2 = (analogRead(I2)-offs2)/30; // 5,6A -- -8,0
 Strom2=Strom2*5.6/7.7;

}
void Les_spenning1() {
	  int Vo = analogRead(U1);
	  Up1 = Vo *12.0 / 550.0;

  }
void Les_spenning2() {
	  int Vo = analogRead(A4);
	  Up2 = Vo * 12.0 / 550.0;

  }
void Les_gass() 
	  //https://www.elecrow.com/wiki/index.php?title=Analog_CO/Combustible_Gas_Sensor(MQ9)
  {
	  float sensor_volt;
	  float RS_air; //  Get the value of RS via in a clear air
	  float R0;  // Get the value of R0 via in LPG
	  float sensorValue;

	  /*--- Get a average data by testing 100 times ---*/
	  for (int x = 0; x < 100; x++)
	  {
		//  int i = analogRead(gas);
		//  Serial.print(i);
		  j = analogRead(gas);
		 // Serial.print(" : ");
	//  Serial.println("Gass1: "+String(j));
	  sensorValue = sensorValue + j;// analogRead(gas);
	  }
	  sensorValue = sensorValue / 100.0;
	  /*-----------------------------------------------*/
//  Serial.println(j);
	  sensor_volt = sensorValue / 1024 * 5.0;
	  RS_air = (5.0 - sensor_volt) / sensor_volt; // omit *RL
	  R0 = RS_air / 9.9; // The ratio of RS/R0 is 9.9 in LPG gas
	  gass = RS_air;

	  Serial.print("sensor_volt = ");
	  Serial.print(sensor_volt);
	  Serial.println("V");

	  Serial.print("R0 = ");
	  Serial.println(R0);
	//  delay(1000);

  }
void Vis_parametre() {
	  Serial.print("T1 \t");
	  Serial.println(Temp1);
	  Serial.print("T2 \t");
	  Serial.println(Temp2);
	  Serial.print("V1: \t");
	  Serial.println(Up1);
	  Serial.print("V2: \t");
	  Serial.println(Up2);
    Serial.print("I1: \t");
    Serial.println(Strom1);
    Serial.print("I2: \t");
    Serial.println(Strom2);
    Serial.print("Gass2: \t");
    Serial.println(gass);
	Serial.print("ld1 \t");
	Serial.println(ld1);
	Serial.print("ld2 \t");
	Serial.println(ld2);
	Serial.print("Rele1 \t");
	Serial.println(digitalRead(Rele1));
	Serial.print("Rele2 \t");
	Serial.println(digitalRead(Rele2));
	Serial.print("bat1 \t");
	Serial.println(bat1);
	Serial.print("bat2 \t");
	Serial.println(bat2);
	Serial.print("Alarm 1 \t");
	Serial.println(alarm1);
	Serial.print("Alarm 2 \t");
	Serial.println(alarm2);
	Serial.print("Alarm_ok 1 \t");
	Serial.println(alarm1_ok);
	Serial.print("Alarm_ok 2 \t");
	Serial.println(alarm2_ok);

  }
boolean alarm() {
 //  float Max_temp = 60, Max_strom = 50, Min_spenning = 11, grense_gass = 10;
	  exit;

  Serial.print("Alarm  1\t");
  Serial.print(Up1<Min_spenning);
  Serial.print("  \t ");
  Serial.print(Temp1>Max_temp);
  Serial.print("  \t ");
  Serial.print(Strom1>Max_strom);
  Serial.print("  \t ");
  Serial.print(alarm1);
  Serial.print("  \t ");
  Serial.println((Up1<Min_spenning) || (Temp1>Max_temp) || ( Strom1>Max_strom) ||alarm1) ;

  Serial.print("Alarm  2\t");
  Serial.print(Up2<Min_spenning);
  Serial.print("  \t ");
  Serial.print(Temp2>Max_temp);
  Serial.print("  \t ");
  Serial.print(Strom2>Max_strom);
  Serial.print("  \t ");
  Serial.print(alarm2);
  Serial.print("  \t ");
  Serial.println((Up2<Min_spenning) || (Temp2>Max_temp) || (Strom2>Max_strom) || alarm2);

   if ((Up1<Min_spenning) || (Temp1>Max_temp) || ( Strom1>Max_strom) || alarm1 )
    {
     Serial.println("Utkoblet");
      digitalWrite(Rele1, HIGH);
	  alarm1 = true;
     blinkLCD();   
    }
    else
    {
     Serial.println("Innkoblet");
      digitalWrite(Rele1, LOW);
      digitalWrite(Led1, LOW); 
    };


    if ((Up2<Min_spenning) || (Temp2>Max_temp) || ( Strom2>Max_strom) || alarm2)
    {
      digitalWrite(Rele2, HIGH);   
      blinkLCD();
	 alarm2 = true;
    }
    else
    {
    digitalWrite(Rele2, LOW);
       digitalWrite(Led2, LOW); 
      };
 

    

}
void blinkLCD()
  {

	  tid = millis();
	  prevrest = rest;
	  rest = tid % 100;
	  Serial.print("alarm: " + String(tid));
	  Serial.print(" : ");
	  Serial.print(rest);
	  Serial.print(" : ");
	  Serial.println(gg);
	  Serial.println("R1: \t" + String(digitalRead(R1)) + "\tled1: \t" + String(digitalRead(Led1)));
	  Serial.println("R2: \t" + String(digitalRead(R2)) + "\tLed2: \t" + String(digitalRead(Led2)));

	  //if ((rest < 20));// && (prevrest > 500))
	  {
		  gg = !gg;
	  //if ((rest>500) && (prevrest<500)) Serial.println("B");
		  {
			  if ((alarm1))// && (!bat1))
			  {
  				if (gg)  digitalWrite(Led1, LOW);
				  else digitalWrite(Led1, HIGH);
			  }
				  else
					  digitalWrite(Led1, LOW);

			  if ((alarm2) && (!bat2))
				{
				  if (gg)  digitalWrite(Led2, LOW);
				  else digitalWrite(Led2, HIGH);
     			  }
				  else
					  digitalWrite(Led2, LOW);

			  }
		  }
	  }


void 	les_touch() {}



void Send_til_klient(){
	pinMode(Rele1, OUTPUT);
	pinMode(Rele2, OUTPUT);

	WiFiClient client = server.available();   // listen for incoming clients

	if (client)
	{
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
	//	Serial.println("Connected " + String(k));
		while (client.available()) {             // if there's bytes to read from the client,
		//	Serial.println("Available " + String(l));
			char c = client.read();             // read a byte, then
	  //      Serial.write(c);                    // print it out the serial monitor
			if (c == '\n') {                    // if the byte is a newline character


				Serial.println("kommando: " + currentLine);

				if (currentLine == "bat1 on")
				{
					/*	  if (alarm(1))
						  {
							  digitalWrite(Rele1, LOW);
							  digitalWrite(Led1, LOW);
							  bat1 = true;
							  client.println("R1\t0");
							  //Rel1_aktiv = true;

						//	  blinkLCD(1);
						  }
						  else
					*/
					{
						Serial.println("BATT ON");
						digitalWrite(Led1, LOW);
						digitalWrite(Rele1, LOW);
						bat1 = true;
					}

				}
				else if (currentLine == "bat1 off")
				{
					Serial.println("BATT OFF");
					digitalWrite(Rele1, HIGH);

					//	 Rel1_aktiv = false;
					offs1 = analogRead(I1);
					bat1 = false;
					digitalWrite(Led1, HIGH);
         delay(1000);
          offs1 = analogRead(I1);
				}
				else if (currentLine == "bat2 on")
				{
					/*  if (alarm(2))
						  {
				/*			  digitalWrite(Rele2, LOW);
							  client.println("R2\t0");
							  //Rel2_aktiv = true;
							  bat2 = true;

						//  blinkLCD(2);

						  }
						  else
						*/ {
						digitalWrite(Led2, LOW);
						digitalWrite(Rele2, LOW);
						bat2 = true;
					}

				}
				else if (currentLine == "bat2 off")
				{
					digitalWrite(Rele2, HIGH);
					digitalWrite(Led2, HIGH);
					client.println("R2\t1");
				//	Rel2_aktiv = false;
					bat2 = false;
          delay(1000);
          offs2 = analogRead(I2);
				}
				else if (currentLine == "resett_alarm")
				{
					Serial.println("Lest resett alarm");
					//		  alarm1 = false;
					//		  alarm2 = false;
					if (!sjekk_verdier(true))
					{
						Serial.println("!sjekk_verdier");
						if (alarm1_ok)
						{
							Serial.println("alarm1_ok");
							digitalWrite(Led1, HIGH);
							digitalWrite(Rele1, HIGH);
							bat1 = true;
							alarm1_ok = false;
							ld1 = false;
						}
						if (alarm2_ok)
						{
							digitalWrite(Led2, HIGH);
							digitalWrite(Rele2, HIGH);
							bat2 = true;
							alarm2_ok = false;
							ld2 = false;
						}
					}

				};


				// if the current line is blank, you got two newline characters in a row.
				// that's the end of the client HTTP request, so send a response:
				if (currentLine.length() == 0)
				{
					client.println("Fra server: ");
					// break out of the while loop:
					break;
				}
				else
				{    // if you got a newline, then clear currentLine:
					currentLine = "";
				};
			}
			else if (c != '\r') {  // if you got anything else but a carriage return character,
				currentLine += c;      // add it to the end of the currentLine
			}
		};
		client.print("T1 \t");
		client.println(Temp1);
		//client.println(" C");
		client.print("T2 \t");
		client.println(Temp2);
		//client.println(" C");
		client.print("U1 \t");
		client.println(Up1);
		client.print("U2 \t");
		client.println(Up2);
		client.print("I1 \t");
		client.println(Strom1);
		client.print("I2 \t");
		client.println(Strom2);
		client.print("G1 \t");
		client.println(gass);
		client.print("R1 \t");
		client.println(digitalRead(Rele1));
		client.print("R2 \t");
		client.println(digitalRead(Rele2));
		client.print("Batt1 \t");
		client.println(bat1);
		client.print("Batt2 \t");
		client.println(bat2);
		client.print("Alarm 1 \t");
		client.println(alarm1);
		client.print("Alarm 2 \t");
		client.println(alarm2);
		client.print("KabTemp \t");
		client.println(KabTemp);
		
		Serial.println("Data sendt til klient");

		Serial.println("Client Disconnected 1.");
		client.stop();
	  

    } //while
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
void Send_til_klient1() {
	  WiFiClient client = server.available();   // listen for incoming clients

	  if (client)
	  {
		  Serial.println("New Client.");           // print a message out the serial port
		  String currentLine = "";                // make a String to hold incoming data from the client
		  while (client.connected()) {            // loop while the client's connected
			  if (client.available()) {             // if there's bytes to read from the client,
				  char c = client.read();             // read a byte, then
//				  Serial.write(c);                    // print it out the serial monitor
				  if (c == '\n') {                    // if the byte is a newline character


					  Serial.println("kommando: " + currentLine);
					  if (currentLine == "bat1 on")
					  {
						  Serial.println("BAT1 ON");
						  digitalWrite(Led1, LOW);
					  }
					  else if (currentLine == "bat1 off")
					  {
						  Serial.println("BAT1 OFF");
						  digitalWrite(Led1, HIGH);
					  }
					  else if (currentLine == "bat2 on")
					  {
						  Serial.println("BAT2 ON");
						  digitalWrite(Led2, LOW);
					  }
					  else if (currentLine == "bat2 off")
					  {
						  Serial.println("BAT2 OFF");
						  digitalWrite(Led2, HIGH);
					  };
					  if (currentLine.length() == 0) {
						  client.println("Fra server: ");
						  // break out of the while loop:
						  break;
					  }
					  else {    // if you got a newline, then clear currentLine:
						  currentLine = "";
						  break;
				  }
			  }
					  else if (c != '\r') {  // if you got anything else but a carriage return character,
						  currentLine += c;      // add it to the end of the currentLine
					  }
					  /*
					  // Check to see if the client request was "GET /H" or "GET /L":
					  if (currentLine.endsWith("GET /H")) {
					  digitalWrite(5, HIGH);               // GET /H turns the LED on
					  }
					  if (currentLine.endsWith("GET /L")) {
					  digitalWrite(5, LOW);                // GET /L turns the LED off
					  }*/
			  };
			  client.stop();
			  Serial.println("Client Disconnected.");
		  }
		  client.stop();
		  Serial.println("Client Disconnected.");

	  }
  }
void Les_ladespenning()
{
	int Vo = analogRead(lade_spenning);
	LadeSpenning = Vo * 12 / 550;
}
void Les_kabinetttemp()
{
	Vo = analogRead(kab_temp) / 2.8;
	R2 = R1 * (1023.0 / (float)Vo - 1.0);
	logR2 = log(R2);
	T = (1.0 / (c1 + c2 * logR2 + c3 * logR2*logR2*logR2));
	KabTemp = T - 273.15;
	/*
 if (KabTemp > Max_temp)
	  {
        ledcWrite(channel, dutyCycle);
//		  ledcSetup(channel, freq, resolution);
//		  ledcAttachPin(kab_temp, channel);
	  }
 */
}
