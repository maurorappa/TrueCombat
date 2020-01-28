#include "PinChangeInterrupt.h"
#include <TimerOne.h>

const int IRSensorPin = 4;  // the number of the IR sensor input pin       // the current state of the output pin
int burp;
int rpmStart = 8;
int rpmEnd = 12;
unsigned long time;
unsigned long elapsed;

// ---------------------------------------------------------------
void setup(void) {
  pinMode(IRSensorPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  Timer1.initialize(1000000);// 1 second  // Set the timer to 1,000,000 microseconds (1 second)
  Timer1.attachInterrupt(timerIsr);  // Attach the service routine here
  attachPCINT(digitalPinToPCINT(IRSensorPin), counter, FALLING);
}

void counter(void) {
  burp++;
    if (burp >= rpmEnd && time != 0) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.print("Finish ");
      elapsed = (micros() - time)/100000;
      Serial.println(elapsed);
      time = 0;
      burp = 0;
  }
}


void loop(void) {
}

void timerIsr()
{ 
  Serial.print(" RPS: ");
  Serial.println(burp);
  if (burp >= rpmStart && time == 0) {
    Serial.println("Start");
    time = micros();
    digitalWrite(LED_BUILTIN, HIGH);
  }
  noInterrupts();
  burp = 0;   
  interrupts();
}
