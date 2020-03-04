#include <RTClib.h>
#include <Wire.h>

DS1307 RTC;
char msg,data = 0; //Variable for storing received data
int second=0, minute=0, hour=0, munit=0, hunit=0, st=0, sure=0 ;
String minute1,minute2,minute_char,hour_char, incoming, setminute1, setminute2, sethour1, sethour2;

void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
    pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
    for (int i=2; i <= 9; i++){ 
        pinMode(i, OUTPUT);
    }
    pinMode(10, INPUT); // summer time switch
    Wire.begin();
    RTC.begin();
    // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
    if (! RTC.isrunning()) {
      Serial.println("RTC is NOT running!");
      digitalWrite(5, HIGH);
      digitalWrite(9, HIGH);
      delay(10000);
      // This will reflect the time that your sketch was compiled
      RTC.adjust(DateTime(__DATE__, __TIME__));
    }
    //selfcheck();
    Serial.println("Binary clock ready!");
}

void selfcheck() {
   for (int i=1; i <= 13; i++){  
    digitalWrite(i, HIGH);
   } 
   analogWrite(A0,255);
   delay(1000);
  for (int i=1; i <= 13; i++){  
    digitalWrite(i, LOW);
   } 
  analogWrite(A0,LOW);
}

void loop()
{
   DateTime now = RTC.now();
   st = digitalRead(10); 
   hour=now.hour();
   // if pin 10 is ON, we'll remove 1h
   // sure is a basic debounce
   if (st > 0 && sure > 0 ) {
      Serial.println("summer time adjusted");
      hour--;
   }
   sure = st;
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
    
    Serial.print(hour, DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
    
   }  

   minute=now.minute();
   static unsigned long lastTick = 0; // set up a local variable to hold the last time we moved forward one second
   // (static variables are initialized once and keep their values between function calls)
   // move forward one second every 1000 millisecond 

   if (millis() - lastTick >= 1400) {
      lastTick = millis();
      second++;
   }
 
   // move forward one minute every 60 seconds
   if (second >= 60) {
      minute++;
      second = 0; // reset seconds to zero
   }
  
   // move forward one hour every 60 minutes
   if (minute >=60) {
      hour++;
      minute = 0; // reset minutes to zero
   }

   if (hour >=24) {
      hour  = 0;
      minute  = 0; // reset minutes to zero
   }  

   munit = minute%10; //sets the variable munit and hunit for the unit digits
   hunit = hour%10;

   //minutes 
   if((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60))  {digitalWrite(4, HIGH);} else {digitalWrite(4,LOW);}
   if(minute >= 20 && minute < 40)  {digitalWrite(3, HIGH);} else {digitalWrite(3,LOW);}
   if(minute >= 40 && minute < 60) {digitalWrite(2, HIGH);} else {digitalWrite(2,LOW);}
  
   //minutes units
   if(munit == 1 || munit == 3 || munit == 5 || munit == 7 || munit == 9) {  digitalWrite(5, HIGH);} else {  digitalWrite(5,LOW);}
   if(munit == 2 || munit == 3 || munit == 6 || munit == 7) {digitalWrite(6, HIGH);} else {digitalWrite(6,LOW);}
   if(munit == 4 || munit == 5 || munit == 6 || munit == 7) {digitalWrite(7, HIGH);} else {digitalWrite(7,LOW);}
   if(munit == 8 || munit == 9) {digitalWrite(8, HIGH);} else {digitalWrite(8,LOW);}
  
   //hour units
   if(hunit == 1 || hunit == 3 || hunit == 5 || hunit == 7 || hunit == 9) {digitalWrite(9, HIGH);} else {digitalWrite(9,LOW);}
   if(hunit == 2 || hunit == 3 || hunit == 6 || hunit == 7) {analogWrite(A2,255);} else {analogWrite(A2,0);}
   if(hunit == 4 || hunit == 5 || hunit == 6 || hunit == 7) {digitalWrite(13, HIGH);} else {digitalWrite(13,LOW);}
   if(hunit == 8 || hunit == 9) {analogWrite(A1,255);} else {analogWrite(A1,0);}

   //hour
   if(hour >= 10 && hour < 20)  {analogWrite(A3,255);} else {analogWrite(A3,0);}
   if(hour >= 20 && hour < 24)  {analogWrite(A0,255);} else {analogWrite(A0,0);}
   delay(500);
}
