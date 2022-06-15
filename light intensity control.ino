#include <Servo.h>
#include<SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial ble(0,1);
const int ldr = A0;
const int relay = 5;
Servo a;
int cahaya,cahaya1;
int update_interval = 100;
unsigned long last_time=0;
char data_in;
String text,text1,text2;
void setup() {
  Serial.begin(9600);
Serial.println("*.kwl");
Serial.println("clear_panel()");
Serial.println("set_grid_size(11,5)");
Serial.println("add_text_box(2,1,8,L,Text,245,240,245,A)");
Serial.println("add_switch(2,2,4,D,d,0,0");
Serial.println("set_panel_notes(,,,)");
Serial.println("run()");
Serial.println("*");
 pinMode(ldr,INPUT);
 pinMode(relay,OUTPUT);
 lcd.begin();
 lcd.backlight();
 a.attach(9);
 lcd.setCursor(0,0);
 lcd.print("Azimi Alfaresyi");
 lcd.setCursor(0,1);
 lcd.print("182408025");
 delay(2000);
 lcd.clear();
}

void loop() {
cahaya  = analogRead(ldr);
cahaya1 = map(cahaya, 100, 950, 0, 180);
if(cahaya1 < 0){ cahaya1 = 0;}
if(cahaya1 >180){ cahaya1 =180;}
Serial.println(cahaya);
a.write(cahaya1);
if(Serial.available()){
  data_in = Serial.read();
if(data_in =='D'){
  digitalWrite(relay,HIGH);
}
if (data_in =='d'){
 digitalWrite(relay,LOW);
}
}
unsigned long t=millis();
if((t-last_time)>update_interval){
  last_time=t;
  Serial.print("*A"+text+"*");
  Serial.println("*BDimmer: "+text1+"*");
  Serial.println("*C"+text2+"*");
}
if( cahaya < 200){
  text = "Siang";
  lcd.setCursor(0,0);
  lcd.print("Siang");
  digitalWrite(relay,HIGH);
  if( data_in == 'd'){digitalWrite(relay,LOW);}
}
else if ( cahaya >=200&&cahaya<=700){
  text = "Sore";
  lcd.setCursor(0,0);
  lcd.print("Sore ");
  digitalWrite(relay,LOW);
  if( data_in == 'D'){digitalWrite(relay,HIGH);}
}
else{
  text = "Malam";
  lcd.setCursor(0,0);
  lcd.print("Malam");
  digitalWrite(relay,LOW);
  if( data_in == 'D'){digitalWrite(relay,HIGH);}
}
text2 = cahaya;
text1 = cahaya1;
lcd.setCursor(8,0);
lcd.print("n=");
if(cahaya<=9){lcd.print("000");}
else if(cahaya >=10 && cahaya <=99){lcd.print("00");}
else if(cahaya >=100 && cahaya <=999){lcd.print("0");}
lcd.print(cahaya);
lcd.setCursor(0,1);
lcd.print("Dimmer:");
if(cahaya1<=9){lcd.print("00");}
else if(cahaya1 >=10 && cahaya1 <=99){lcd.print("0");}
lcd.print(cahaya1,DEC);
lcd.setCursor(10,1);
lcd.print((char)223);
delay(1000);
}
