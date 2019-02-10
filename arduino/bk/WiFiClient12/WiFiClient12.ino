#include <LiquidCrystal_I2C.h>



/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
	R1, R2 rele inn/ut 0/1;
	bat1 on
 */

#include <WiFi.h>

const char* ssid     = "dlink";
const char* password = "12345abc";

const char* host = "192.168.10.95";

int freq = 2000;
int channel = 0;
int resolution = 8;

//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
//#include <LiquidCrystal_I2C.h>
// #include <Lstdlib.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);

// Set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x3F, 20, 4);

float T11,T22,U1,U2,I1,I2,G;
int R1, R2 ,st;
boolean Rel1_aktiv = true, Rel2_aktiv = true,debug=true;
int alarm1 = 0, alarm2 = 0;
static char outstr[15];
String kommando1,kommando = "status";

#include <Time.h>
#include <TimeLib.h>
time_t td;
/*
#define pin_R1 32;
#define pin_R2 33;
#define pin_reset 4;
#define pin_status 15;
*/
int pin_R1= 33,pin_R2=32,pin_reset=15,pin_status=4;

int tid, offset;
boolean bypass = true;
float rest, prevrest;
int value = 0;
String line = "";
WiFiClient client;


void setup()
{
	setTime(0, 0, 0, 0, 0, 0);
	Serial.begin(115200);
	Serial.println(__FILE__);
	Serial.print("Kompilert: "); Serial.println(__TIMESTAMP__);
    // We start by connecting to a WiFi network

	lcd.begin();
	lcd.clear();

	pinMode(pin_R1, INPUT);
	pinMode(pin_R2, INPUT);
	pinMode(pin_reset, INPUT);
	pinMode(pin_status, INPUT);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
      Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.print("Ready");
  lcd.setCursor(0, 1);
  lcd.print("IP adresse: ");
  lcd.setCursor(0, 2);
  lcd.print(WiFi.localIP());
  lcd.setCursor(0, 3); lcd.print(host); lcd.print(" (host)");
  kommando = "Initieres";
  delay(1000);
  st = 0;
}

//void loop(){}

void loop()
{
	
	if (Serial.available())
	{
		String str4 = Serial.readStringUntil('\r');
		Serial.println("Les kommando\t" + str4);
		if (str4 == "debug")
			debug = true;
		else if (str4 == "nodebug")
			debug = false;

	}


	delay(100);
	Serial.println("st1\t" + String(st));



les_touch();
velg_funksjon();
vis();
Serial.println("Kommando før serverkontakt:\t" + kommando);
komm_server();
Serial.println("tid: " + String(minute()) + "  "+ String(second()));
if ((alarm1) || (alarm2))
{
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(lydpin, channel);
}
}

void looperer()
{
	Serial.println("Inp1:" + String(digitalRead(4)));
	Serial.println("Inp2:" + String(digitalRead(pin_R2)));
	Serial.println("Inp3:" + String(digitalRead(pin_reset)));
	Serial.println("Inp4:" + String(digitalRead(pin_status)));
	Serial.println();

}
void loopll()
{
	delay(1000);
	++value;


	// Use WiFiClient class to create TCP connections
	WiFiClient client;
	const int httpPort = 50;
	if (!client.connect(host, httpPort)) {
		Serial.println("connection failed");
		return;
	}

	Serial.print("connecting to ");
	Serial.println(host);

	//client.println("bat1 on\r\n\r\n ");
	//client.print("status\r\n\r\n ");    
	unsigned long timeout = millis();
	while (client.available() == 0) {
		if (millis() - timeout > 5000) {
			Serial.println(">>> Client Timeout !");
			client.stop();
			return;
		}
	}

	// Read all the lines of the reply from server and print them to Serial
	while (client.available()) {
		String line = client.readStringUntil('\r');
		Serial.print("READ: " + line);
	}

	Serial.println();
	Serial.println("closing connection");
}
void loop55()
{
	delay(100);
	les_touch();
	vis();
	if (st == 1)	status();
	else if (st == 2)	reset_alarm();// meny();
	else if (st == 3)	Rele1();
	else if (st == 4)	Rele2();
	else st = 0;

}
void looptlt()
{
	les_touch();
	vis();
	if (st == 1)	status();  //T3
	else if (st == 2)	reset_alarm();// meny(); //T2
	else if (st == 3) {
		Rele1(); //T8
				 delay(500);
				// 	status();
	}
	else if (st == 4) {
		Rele2(); //T9
				 	delay(500);
				 	//status();
	}
 Serial.println("ST: " + String(st));
	delay(1000);
}


void reset_alarm()
{
	//alarm1 = 0;
	//alarm2 = 0;
	kommando = "resett_alarm";
	lcd.clear();
	lcd.setCursor(0, 1);
	lcd.print("Resetter alarm");

}
void Rele1()
{
	Serial.println("R1:\t" + String(R1) + "\t" + String(alarm1));
	//	client.println("Rele 1 avl�tt");
	lcd.clear();
	if (R1 == 1) Rel1_aktiv = false; else Rel1_aktiv = true;
	if (Rel1_aktiv)  // skift
	{
		Rel1_aktiv = false;
		kommando = "bat1 off";
		if (R1 == 0)
		{
			lcd.clear();
			lcd.setCursor(0, 1);
			lcd.print("Batteri 1 utkobles..");
		}
		else
		{
			lcd.clear();
			lcd.setCursor(0, 1);
			lcd.print("Batteri 1 utkoblet  ");
			delay(500);
			//	kommando = "status";
			status();
		}
	}
	else
	{
		Rel1_aktiv = true;
		kommando = "bat1 on";
		if (R1 == 0)
		{
			lcd.clear();
			lcd.setCursor(0, 1);
			lcd.print("Batteri 1 innkoblet  ");
			delay(500);
			//	kommando = "status";
			status();
		}
		else
		{
			lcd.clear();
			lcd.setCursor(0, 1);
			lcd.print("Batteri 1 innkobles.");
			delay(200);
		}
	}
}
void Rele2()
{
	if (R2 == 1) Rel2_aktiv = false; else Rel2_aktiv = true;

	if (Rel2_aktiv)
	{
		Rel2_aktiv = false;
		kommando = "bat2 off";
		lcd.clear();
		if (R1 == 0)
		{
			lcd.setCursor(0, 1);
			lcd.print("Batteri 2 Utkobles..");
		}
		else
		{
			lcd.setCursor(0, 1);
			lcd.print("Batteri 2 Utkoblet  ");
		}
	}
	else
	{
		Rel2_aktiv = true;
		kommando = "bat2 on";
		lcd.clear();
		if (R2 == 0)
		{
			lcd.setCursor(0, 1);
			lcd.print("Batteri 2 Innkoblet ");
		}
		else
		{
			lcd.setCursor(0, 1);
			lcd.print("Batteri 2 Innkobles.");
		}

	}
}
void les_touch()
{
	if (digitalRead(pin_R1)==LOW) {
		lcd.clear();
		st = 1;
		kommando = "status";
	}
	else if (digitalRead(pin_R2) == LOW) {
		lcd.clear();
		st = 2;
		kommando = "reset_alarm";
	}
	else if (digitalRead(pin_reset) == LOW) {
		lcd.clear();
		st = 3;
	}
	else if (digitalRead(pin_status) == LOW) {
		lcd.clear();
		st = 4;
	}
	else
		st = 0;

	/*	if (touchRead(T2) < 50)  st = 3;
if (touchRead(T3) < 50)  st = 4;
if (touchRead(T8) < 50)  st = 5;
if (touchRead(T9) < 50)  st = 6;

	Serial.println("inp1: \t" + String(digitalRead(15)));
	Serial.println("inp2: \t" + String(digitalRead(2)));
	Serial.println("inp3: \t" + String(digitalRead(33)));
	Serial.println("inp4: \t" + String(digitalRead(32)));
/

/*		if (st == 1)
		{
			st = 0;
			lcd.noBacklight();
		//	lcd.noDisplay();
		}
		else 
		{
			st = 1;
		//	lcd.backlight();
			lcd.clear();
		}
	if (touchRead(T1) < 50)
		if (st == 2)
		{
			st = 0;
			lcd.noBacklight();
			//	lcd.noDisplay();
		}
		else
		{
			st = 1;
		//	lcd.backlight();
			lcd.clear();
		}
*/


}
void velg_funksjon()
{


	if (debug)  Serial.println("st:\t" + String(st));
	if (st == 1) {
		if (minute() > 1)
		{
			setTime(0, 0, 0, 0, 0, 0);
			lcd.display();
			lcd.backlight();
			lcd.clear();
		};
		status();  //T3
	}
	else if (st == 2) {
		if (minute() > 1)
		{
			setTime(0, 0, 0, 0, 0, 0);
			lcd.display();
			lcd.backlight();
			lcd.clear();
		};
		status();
		reset_alarm();// meny(); //T2
//		kommando = "reset_alarm";
	//	Serial.println("Kommando: " + kommando);
	}

	else if (st == 3) {
		if (minute() > 1)
		{
			setTime(0, 0, 0, 0, 0, 0);
			lcd.display();
			lcd.backlight();
			lcd.clear();
		};
		Rele1(); //T8
		delay(200);
		//	Serial.println("Kommando: " + kommando);
		Serial.println("Rele1: " + kommando);
	}
	else if (st == 4) {
		if (minute() > 1)
		{
			setTime(0, 0, 0, 0, 0, 0);
			lcd.display();
			lcd.backlight();
			lcd.clear();
		};
		Rele2(); //T9
		delay(200);
		//	Serial.println("Kommando: " + kommando);
	}


	//	Serial.println("ST: " + String(st));
		//Serial.println("kommando slutt:\t" + kommando);
	kommando1 = kommando;
	//if ((kommando=="") || (kommando="status")) status();
}
void komm_server()
{

	Serial.print("connecting to ");
	Serial.println(host);


	// Use WiFiClient class to create TCP connections

	const int httpPort = 50;
	if (!client.connect(host, httpPort)) {
		Serial.println("connection failed");
		lcd.clear();
		lcd.print("Ikke kontakt med ");
		lcd.setCursor(0, 1);
		lcd.print("SSID: ");
		lcd.print(ssid);
		lcd.setCursor(0, 2);
		lcd.print("IP:   ");
		lcd.print(host);
		//	kommando == "feil1";
		return;
		//asm  ("  jmp 0");
	}
	else if (((kommando == "status") || (kommando == "") || (kommando == "Initieres")))
	{
		//	lcd.clear();
		status();
		st = 1;

		Serial.println("else if..\t" + kommando);
		kommando = "les";

	};

	//	client.print("bat1 on\r\n\r\n ");
	if ((kommando == "Initieres") || (kommando == "feil"))
	{
		//	kommando = "status";
	//	lcd.clear();
		status();
		kommando = "les";
	};
	//	kommando = "test";
	if (debug) Serial.println("Kommando sendt: " + kommando);
	client.print(kommando);
	client.print("\r\n\r\n");
	unsigned long timeout = millis();
	while (client.available() == 0)
	{
		if (millis() - timeout > 5000) {
			Serial.println(">>> Client Timeout !");
			client.stop();
			return;
		}
	}

	// line = "";


	while (client.available()) {
		/*	char c = client.read();
			if (!((int(c) == 10) || (int(c) == 13)))
			line += c;
			};
			*/
		line = client.readStringUntil('\r');
		if (int(line[0]) == 10) line = line.substring(1);
		//	if (debug)
		Serial.println("Readstring: " + line);

		if (line.startsWith("T1"))
		{
			int i = line.indexOf("\t");
			T11 = line.substring(i + 1).toFloat();
		}

		else  if (line.startsWith("T2"))
		{
			int i = line.indexOf("\t");
			T22 = line.substring(i + 1).toFloat();
		}
		else  if (line.startsWith("U1"))
		{
			int i = line.indexOf("\t");
			U1 = line.substring(i + 1).toFloat();
		}
		else  if (line.startsWith("U2"))
		{
			int i = line.indexOf("\t");
			U2 = line.substring(i + 1).toFloat();
		}
		else  if (line.startsWith("I1"))
		{
			int i = line.indexOf("\t");
			I1 = line.substring(i + 1).toFloat();
		}
		else  if (line.startsWith("I2"))
		{
			int i = line.indexOf("\t");
			I2 = line.substring(i + 1).toFloat();
		}
		else  if (line.startsWith("G1"))
		{
			int i = line.indexOf("\t");
			G = line.substring(i + 1).toFloat();
		}

		else  if (line.startsWith("R1"))
		{
			int i = line.indexOf("\t");
			R1 = line.substring(i + 1).toInt();
			if ((R1 == 0) && (kommando == "bat1 on")) {
				//				lcd.clear();
						//		lcd.print("ret bat1 on");
				status();
				//	kommando="les";
			};

			if (R1 == 1)
			{
				if (kommando == "bat1 off") {
					//			lcd.clear();
					//			lcd.print("ret bat1 off");
					status();
					//		kommando="les";
				}
				else
					Rel1_aktiv = true;

			}
		}
		else  if (line.startsWith("R2"))
		{
			int i = line.indexOf("\t");
			R2 = line.substring(i + 1).toInt();
			if ((R2 == 0) && (kommando == "bat2 on")) {
				//		lcd.clear();
				status();
				//	kommando="";
			}
			if ((R2 == 1) && (kommando == "bat2 off")) {
				//		lcd.clear();
				status();
				//	kommando="";
			}

		}
		else  if (line.startsWith("Alarm 1"))
		{
			int i = line.indexOf("\t");
			alarm1 = line.substring(i + 1).toInt();
			//   	setTime(0, 0, 0, 0, 0, 0);
			  //	lcd.display();
			 //    lcd.backlight();

			if (alarm1 == 1) {
				Serial.println("Alarm1 lest: \t" + String(alarm1));
				if (minute() > 1)
				{
					setTime(0, 0, 0, 0, 0, 0);
					lcd.clear();
					lcd.display();
					lcd.backlight();
				};
				status();
				kommando = "les";
			}
			else
			{
				//		    	alarm1=0;
						//		lcd.clear();
				status();
			}

		}
		else  if (line.startsWith("Alarm 2"))
		{
			int i = line.indexOf("\t");
			alarm2 = line.substring(i + 1).toInt();
			//	setTime(0, 0, 0, 0, 0, 0);
			lcd.display();
			//	lcd.backlight();

			if (alarm2 == 1) {
				if (minute() > 1)
				{
					setTime(0, 0, 0, 0, 0, 0);
					lcd.clear();
					lcd.display();
				};
				status();
				kommando = "les";
			}

			else
			{
				alarm2 = 0;
				//		lcd.clear();
				status();
			}

		}

		//client.println("bat1 off\r\n\r\n ");
	}
  
		//	client.println("bat2 off\r\n\r\n ");
	
}

void vis()
{
	if (debug)
	{
		Serial.println();
		Serial.println("T11:\t" + String(T11));
		Serial.println("U1: \t" + String(U1));
		Serial.println("I1: \t" + String(I1));
		Serial.println("T22: \t" + String(T22));
		Serial.println("U2: \t" + String(U2));
		Serial.println("T1: \t" + String(I1));
		Serial.println("G: \t" + String(G));
		Serial.println(String("Rele 1: \t") + String(R1));
		Serial.println(String("Rele 2: \t") + String(R2));
		Serial.println(String("Alarm 1: \t") + String(alarm1));
		Serial.println(String("Alarm 2: \t") + String(alarm2));
	};

	if ((R1 == 0) && (kommando == "bat1 on")) {
		lcd.clear();
		//		lcd.print("ret bat1 on");
	//	status();
//		kommando = "";
	}

	if ((R1 == 1) && (kommando == "bat1 off")) {
		lcd.clear();
		//			lcd.print("ret bat1 off");
//		status();
//		kommando = "";
	}
}
void status()
{
//	kommando = "status";

	if (minute() >0) {
         lcd.noDisplay();
         lcd.noBacklight();
		exit;
	}
//	else if (minute()<1)
	//{
//	   lcd.display();
	//   lcd.backlight();
  // }
	

	//     	 lcd.clear();
			 lcd.setCursor(0, 0);
			 lcd.print("Batt1:");
	         lcd.setCursor(0,1);
			 dtostrf(U1, 2, 1, outstr);
			 lcd.print(outstr);
     	     lcd.print("V");
			 lcd.setCursor(7,1);
			 dtostrf(I1, 2, 1, outstr);
	    	 lcd.print(outstr);
			 lcd.print("A");
			 lcd.setCursor(14,1);
			 dtostrf(T11, 3, 1, outstr);
			 lcd.print(outstr);
			 lcd.print("C");
			// lcd.setCursor(14,1);
			 dtostrf(G, 2, 1, outstr);
			 //lcd.print(outstr);
			 //lcd.print("pH");
			 lcd.setCursor(0, 2);
			 lcd.print("Batt2:");
			 lcd.setCursor(0, 3);
			 dtostrf(U2, 3, 1, outstr);
			 lcd.print(outstr);
			 lcd.print("V");
			 lcd.setCursor(7, 3);
			 dtostrf(I2,2, 1, outstr);
			 lcd.print(outstr);
			 lcd.print("A");
			 lcd.setCursor(14, 3);
			 dtostrf(T22, 3, 1, outstr);
			 lcd.print(outstr);
			 lcd.print("C");
			 lcd.setCursor(7, 0);
			 if (alarm1 == 1)
			 {
				 // lcd.blink_on();
				  //lcd.blink();
				 lcd.print("Alarm -utkobl");
				 //				 lcd.blink_off();
			 }
			 else
			 {
				 if (R1 == 1) lcd.print("Utkoblet"); else lcd.print("Innkoblet");
			 };

			 lcd.setCursor(7,2);

			 if (alarm2 == 1)
			 {
				 // lcd.blink_on();
				 //lcd.blink();
				 lcd.print("Alarm -utkobl");
				 //				 lcd.blink_off();
			 }
			 else
			 {
				 if (R2 == 1) lcd.print("Utkoblet"); else lcd.print("Innkoblet");
			 }
//	 lcd.display();

			// kommando = "";
		 }
void meny()
{
	//lcd.noDisplay();
//	lcd.clear();
//	lcd.backlight();
	lcd.print("->");
	lcd.setCursor(3, 0);
	lcd.print("1.Status");
	lcd.setCursor(3, 1);
	lcd.print("2.Koble ut batt 1");
	lcd.setCursor(3, 2);
	lcd.print("2.Koble ut batt 2");
	lcd.setCursor(3, 3);
	lcd.print("3.Resett");
}
