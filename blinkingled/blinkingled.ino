int led = 7; // initialize LED pin

void setup() {
  pinMode(led, OUTPUT); 
    Serial.begin(9600); // start serial communication

}

void loop() {
//   connect smaller_pin(cathode) to GND
//           larger_pin(anode) to 5V/Vin
  digitalWrite(led, HIGH); // turn LED on
  Serial.println("LED is ON");
  delay(1000);             // wait 1 second
  digitalWrite(led, LOW);  // turn LED off
  Serial.println("LED is OFF");
  delay(1000);             // wait 1 second
}
