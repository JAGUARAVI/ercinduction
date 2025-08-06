long randNumber;
unsigned long startTime, endTime, reactionTime;
int buttonPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);            // LED output
  pinMode(buttonPin, INPUT_PULLUP); // Button input with pull-up resistor
  randomSeed(40);
  digitalWrite(7,LOW);
}
bool ledState = false;
void loop() {
  // random ON duration
  if(!ledState){
  randNumber = random(4, 12);
  
  // wait while LED is ON and check if button is pressed
  delay(randNumber * 200);
  digitalWrite(7, HIGH);
   startTime = millis();
 ledState=true;
  }
  if (digitalRead(buttonPin) == LOW && ledState ){
    endTime = millis();
    reactionTime = endTime - startTime;
    Serial.print("Reaction Time: ");
    Serial.print(reactionTime);
    Serial.println(" ms");
    digitalWrite(7,LOW);
    ledState=false;
  }
}
