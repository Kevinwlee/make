
int ledPin = 9;      // LED connected to digital pin 9
int analogPin = 3;   // potentiometer connected to analog pin 3
int val = 0;         // variable to store the read value
int vuPin = 7;
int alertPin = 11;

boolean eventActive;

unsigned long time;
unsigned long eventTime;


void setup() {
  pinMode(ledPin, OUTPUT);   // sets the pin as output
  pinMode(vuPin, OUTPUT);
  pinMode(alertPin, OUTPUT);
  eventActive = false;
  Serial.begin(9600);
}


void loop() {  
  time = millis();
  val = analogRead(analogPin);   // read the input pin  
  analogWrite(ledPin, val);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255  
  checkForEvent(val);
  Serial.println(val);
}

void checkForEvent(int val) {
  
  if  (val > 150) {
    eventTime = millis();
    analogWrite(alertPin, 255);
    eventActive = true;
    Serial.println("event triggered");
  }
   
  if (eventActive) {
    long diff = time - eventTime;
  
    Serial.println(diff);
  
    if (diff > 2000) {
       analogWrite(alertPin, 0);
       eventActive = false;
       Serial.println("event OFF");
    }
  }
}

