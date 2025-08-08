int sensorPin = 2;
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = digitalRead(sensorPin);
  if(sensorValue == HIGH) {
    Serial.println("0");
  }
  else {
    Serial.println("1");
  }
  delay(50);
}
