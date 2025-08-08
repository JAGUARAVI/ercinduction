#define SENSOR 10 // ir sensor at pin 10
#define LED 8     // led at pin 8

void setup() {
  pinMode(SENSOR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

// boolean variable to store the last state - if an object was detected or not | defaults to not detected
bool last = false;

void loop() {
  // millis function to get the current time since the beginning of the program in milliseconds
  unsigned long currentMillis = millis();

  if(digitalRead(SENSOR) == LOW) {
    // if last state true - i.e. if the object was present in the last iteration as well, then ignore, otherwise print the message + current time
    if(last == false) {
      Serial.print("Object Detected:\t");
      Serial.print(currentMillis / 1000.0);
      Serial.println("s");
      last = true;
    }
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
    // if last state false - i.e. if the object was NOT present in the last iteration as well, then ignore, otherwise print the message + current time
    if (last == true) {
      last = false;
      Serial.print("Object Lost:\t\t");
      Serial.print(currentMillis/1000.0);
      Serial.println("s");
    }
  }

  delay(100);
}
