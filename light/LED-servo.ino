


#include <Servo.h>  // servo library

Servo servo1;  // servo control object

const int sensorPin = 0;
const int servoPin = 9;
const int ledPin = 7;

int lightLevel, high = 0, low = 1023;

long previousMillis = 0; 
long interval = 100;

void setup()
{
  servo1.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}


void loop()
{

  lightLevel = analogRead(sensorPin);
 
  
//  manualTune();
  autoTune();
  int duration = map(lightLevel, 0, 1024, 0, 15);
  analogWrite(ledPin, lightLevel); 
  digitalWrite(ledPin, HIGH);
  delay(duration);  
  digitalWrite(ledPin, LOW);

  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    Serial.println(lightLevel);
    int angle =  map(lightLevel, 0, 255, 0, 179);
    servo1.write(angle);  
    Serial.println(lightLevel);
    Serial.println(angle);
    previousMillis = currentMillis; 
  }
  
  
}

void autoTune()
{  
  if (lightLevel < low)
  {
    low = lightLevel;
  }

  
  if (lightLevel > high)
  {
    high = lightLevel;
  }
  
  
  lightLevel = map(lightLevel, low+30, high-30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
  
}

void manualTune()
{
  lightLevel = map(lightLevel, 300, 800, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
} 
