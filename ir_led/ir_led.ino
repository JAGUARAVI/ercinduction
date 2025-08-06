int irPin = 7;    // IR sensor output pin
int buzzer = 8;   // Buzzer or LED pin
int val;

void setup() {
  pinMode(irPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600); // start serial communication
}

void loop() {
  val = digitalRead(irPin);

  Serial.print("Digital read value is ");
  Serial.println(val);

  if (val == LOW) { // Object detected
    Serial.println("Object detected");
    digitalWrite(buzzer, HIGH); // turn buzzer/LED ON
  } else {
    Serial.println("No object");
    digitalWrite(buzzer, LOW);  // turn buzzer/LED OFF
  }

  delay(500);
}
