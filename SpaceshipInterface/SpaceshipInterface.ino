// Instantiate global variables here
// Have to declare a type, then value.  End declarations with a semi-colon (;)
int switch_state = 0;
int input_pin = 2;
int ON = 1;

// at compile time, arduino will place all instances of variable with the value
#define MY_SIZE 2
int red_output_pins[MY_SIZE] = {4,5};
int green_output_pin = 3;

void setup() {
  // These three output pins are connected to our three LEDs anode legs
  for(int x = 0; x < MY_SIZE; x++) {
    pinMode(red_output_pins[x], OUTPUT);
  }
  pinMode(green_output_pin, OUTPUT);
  // This input pin is for reading the state of our switch
  // A 10k 'pull-down' resistor is connects our switch to ground when the switch is open
  // so that the input pin reads LOW when there is no voltage coming through the switch
  pinMode(2, INPUT);
}

void loop() {
  switch_state = digitalRead(input_pin); // digitalRead returns either 1 (HIGH) or 0 (LOW)

  if (switch_state == ON) {
    // write green LED to LOW
    digitalWrite(green_output_pin, LOW);

    // write first red LED to HIGH and second red LED to LOW
    digitalWrite(red_output_pins[0], HIGH);
    digitalWrite(red_output_pins[1], LOW);

    // wait for a quarter of a second
    delay(250);
    // write second red LED to HIGH and first red LED to LOW
    digitalWrite(red_output_pins[0], LOW);
    digitalWrite(red_output_pins[1], HIGH);
    delay(250);
    
  } else {
    // write both red LEDS to LOW
    for(int x = 0; x < MY_SIZE; x++) {
      digitalWrite(red_output_pins[x], LOW);
    }
    // write green LED to HIGH
    digitalWrite(green_output_pin, HIGH);
    
  }

}
