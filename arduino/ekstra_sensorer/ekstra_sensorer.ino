/*
 * Ekstra mikrokontroller, Arduino mini pro,
 * som senser gass, kabinettteperatur og utspenning
 * og sender det til hovedkontroller over serieporten.
 * 
 */
 
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void setup() {
  Serial.begin(115200);

}

void loop() {
int gas=analogRead(A0);
int kabtmp=analogRead(A1);
int utsp =analogRead(A2);

R2 = R1 * (1023.0 / (float)gas - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
float    Gass = T - 273.15;
    
  R2 = R1 * (1023.0 / (float)kabtmp - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
float    KabTemp = T - 273.15;
    
  R2 = R1 * (1023.0 / (float)utsp - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));
float    Utspenning = T - 273.15;    

    Serial.println(String("Gass ")+String(Gass));
    Serial.println(String("KabTemp ")+String(KabTemp));
    Serial.println(String("Utspenning ")+String(Utspenning));

}
	