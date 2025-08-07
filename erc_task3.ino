// Define pin numbers for button and IR sensor
#define BUTTON 11
#define IR 12

#include <math.h>

int counter = 0; // Tracks how many bits have been read (0 to 4)
int codeword =0;  // Stores the 5-bit binary codeword

void setup() {
  // put your setup code here, to run once:
  pinMode(IR, INPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Checks if the button is pressed
  if(digitalRead(BUTTON) == HIGH)
  {

    // Read the IR sensor
    if(digitalRead(IR) == HIGH){
    // IR sensor does NOT detect an object (i.e., black surface)
    // Append 0 to our codeword (no change needed)
      codeword += 0;
    }
    else{
      // IR sensor detects an object (i.e., white surface)
      // Append a binary 1 to our code. (i.e add 2^(4 - counter) to code using bit shifting)
      codeword += 1<<(4-counter);
    }

    // Increment counter and wrap around after 5 readings
    counter = (counter+1)%5;
    
    // Once 5 bits are read, convert the codeword to its corresponding letter and print it on the Serial Monitor
    if(counter == 0)
    {
      Serial.print((char)(codeword + 'a'));
      // Now Reset the codeword for the next cycle
      codeword =0;
    }

    // Add a delay to debounce the button and slow down readings
    delay(500);
  }

}
