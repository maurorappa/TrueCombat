int trigPin1 = 8;    // Trigger
int echoPin1 = 7;    // Echo
unsigned long duration1, cm1;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);

  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH,2000);
  delay(10);

  // Convert the time into a distance
  cm1 = (duration1/2) / 14.6;     // Divide by 29.1 or multiply by 0.0343

  Serial.print(cm1);
  Serial.print(" cm1");
  Serial.println();

  
  delay(250);
}
