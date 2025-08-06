int irPin = 7; // connect IR sensor output to digital pin 7
int val;

void setup() {
  pinMode(irPin, INPUT);
  Serial.begin(9600); // start serial communication
}

void loop() {
  val = digitalRead(irPin);
  if (val == LOW) {
    Serial.print("Digital read value is ");
    Serial.println(val);
    Serial.println("Object detected");
  } else {
    Serial.print("Digital read value is ");
    Serial.println(val);
    Serial.println("No object");
  }
  delay(500);
}
