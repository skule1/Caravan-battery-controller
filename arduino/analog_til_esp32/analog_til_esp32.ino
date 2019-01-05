/*
 * Serieporten er satt til 38400
 */

void setup() {
Serial.begin(38400); // serieporten bruker 19200 med denne settingen.

}

void loop() {
int a0=analogRead(A0);
int a1=analogRead(A1);
int a2=analogRead(A2);
int a3=analogRead(A3);
Serial.println(String(a0)+"\t"+String(a1)+"\t"+String(a2)+"\t"+String(a3)+"\t");
delay(1000);


}
