/* Code for remote power cycling of home security system 
 * Turns on/off the power bank on the press of a button
 * LED for indication of the ON condition
 * Dylan Brenneis, December 21, 2019, with help from Alex Kearney
 * 
 * Draws from the following references: 
 * 1. Arduino Button Tutorial (https://www.arduino.cc/en/tutorial/button)
 * 2. Arduino Button Debounce Tutorial (https://www.arduino.cc/en/tutorial/debounce)
 */

//Initialize variables to be used throughout the program

//these variables will not change
const int buttonPin = 2;   //the pin to which the button is connected
const int ledPin = 13;     //the pin to which the indicator LED is connected
const int relayPin = 12;   //the pin to which the relay switch is connected

//these variables will change
int buttonState;              //the current state of the button (HIGH = pressed, LOW = not pressed)
int lastButtonState = LOW;    //the previous state of the button
int relayState = LOW;         //the current state of the relay (HIGH = on, LOW = off)

unsigned long lastDebounceTime = 0;   //the last time in milliseconds that the button state changed
int debounceDelay = 50;               //the amount of time in milliseconds to wait before considering the buttonState actually changed (avoids spurious flicker due to mechanical properties of buttons)


//code in this loop runs once when the Arduino boots up:
void setup() {
  //initialize the pins as either inputs or outputs
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(relayPin, OUTPUT);

}

//code in this loop runs continuously over and over as long as the Arduino is powered:
void loop() {
  //Take the reading of the button state
  int reading = digitalRead(buttonPin);
  //If the reading is different from what it was before, either from noise or from pressing:
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); //take the current timestamp
    }

  //Whatever reading the signal is at, if it's been there longer than the debounce delay take it as real:
  if ((millis() - lastDebounceTime) > debounceDelay) {

     //if the button state has changed:
     if (reading != buttonState) {
        buttonState = reading;

       //if the buttonState is now HIGH, the button is being pressed, so change the state of the relay and status LED
       if (buttonState == HIGH){
         relayState = !relayState; //change the relayState to be opposite to what it was before
         digitalWrite(relayPin,relayState); //write the new relayState to the relay
         digitalWrite(ledPin,relayState); //write the new relayState to the indicator LED
       }
     } 
  }
  
  //save the reading for comparison for the next time through the loop
  lastButtonState = reading;
}
