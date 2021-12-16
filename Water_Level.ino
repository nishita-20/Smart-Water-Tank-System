
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>  //ESP8266 LIBRARY
#include <BlynkSimpleEsp8266.h>  //BLYNK LIBRARY

BlynkTimer timer;

char auth[] = "QaaDaDhkJ-oJqqXoERcdhG9gGOKKMQQN"; //AUTH TOKEN

char ssid[] = "NAME";  // Type your wifi name 

char pass[] = "password";  // Type your wifi password1

#define trig D5   // Trig pin
#define echo D6   // Echo Pin 
long m,inches,duration;

void notify()
{
  digitalWrite(trig, LOW);// NOW STARTS THE WORK OF ULTRASONIC SENSOR
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long m = t / 29 / 2;
  Serial.println(m);
  long level= 15-m; // Change 15 according to your tank depth
  if (level<0)
  level=0;
  Blynk.virtualWrite(V1, level);
}

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L,notify); // CALLIG THE NOTIFY FUNCTION 0.1 SEC
}

void loop()
{
  Blynk.run();
  timer.run();
}
