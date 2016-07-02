/*  Arduino cannot vary the output voltage on its pins, it can only output 5V.  We will have
 *  to use a different technique to fade LEDs called Pulse Width Modulation (PWM).  PWM
 *  rapidly turns the output pin high and low over a fixed period of time.  The change
 *  happens faster than the human eye can see so we don't notice it.  When we rapidly turn
 *  the pin from HIGH to LOW and vice versa, it's as if we were changing the voltage.  
 *  The percentage of time a pin is HIGH in a period is called 'duty cycle.'  For
 *  example is HIGH for half of the period and LOW for the other half, the 'duty cycle'
 *  if 50%.  A lower duty cycle gives you a dimmer LED than a higher duty cycle.   The arduino 
 *  has six pins set aside for PWM (they are marked by the ~ next to their number on the
 *  board).  Photoresistors change their resistance depending on the amount of light 
 *  that hits them (a.k.a. photocells or light-dependent resistors).  You can measur the
 *  change in resistance by checking the voltage of the pin.  We put different colored
 *  filters over the three photoresistors.  These will only let specific wavelengths of light
 *  in; this way we can detect the relative color levels in the light that hits
 *  the sensors.  A common cathode RGB LED has separate red, green, and blue elements inside,
 *  and one common ground -- the longest leg is ground, the only leg to the left of the ground leg
 *  is red, and the other two from left to right are green and blue, respectively.
 */

// set our pins to their respective PWM digital pins
const int redLEDPin = 11;
const int blueLEDPin = 10;
const int greenLEDPin = 9;

// set our sensor pins to their respective analog inputs. NOTE: couldn't find red filter
const int redSensorPin = A0;
const int greenSensorPin  = A1;
const int blueSensorPin  = A2;

// instantiate variables for the output LED values used to fade the LED
int redValue = 0;
int greenValue = 0;
int blueValue = 0;

// instantiate variables for the input sensor values
int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup() {

  // enable serial port for monitoring purposes
  Serial.begin(9600);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  

}

void loop() {
  
  redSensorValue = analogRead(redSensorPin); // read the sensor value (will be a value between 0 and 1024)
  delay(5); // pause while the ADC -- analog to digital converter -- does its work 
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  blueSensorValue = analogRead(blueSensorPin);
  delay(5);
  Serial.print("Raw sensor values \t Red: ");
  Serial.print(redSensorValue);
  Serial.print("\t Green: ");
  Serial.print(greenSensorValue);
  Serial.print("\t Blue: ");
  Serial.println(blueSensorValue);

  // convert the sensor readings to values between 0 and 255 for analogWrite() to change LED's brightness via PWM
  redValue = redSensorValue / 4.0;
  greenValue = greenSensorValue / 4.0;
  blueValue = blueSensorValue / 4.0;

  // log the new analog values
  Serial.print("Mapped sensor values \t RED: ");
  Serial.print(redValue);
  Serial.print("\t Green: ");
  Serial.print(greenValue);
  Serial.print("\t Blue: ");
  Serial.println(blueValue);

  // now write a value to our pins (will be a value between 0 and 255)
  // analogWrite takes two args --> the pin to write to, and a value between 0-255
  // ex. a value of 127 (duty cycle = 50%) will set the pin HIGH half the time, 
  // a value of 0 (duty cycle = 0%) would set the pin to LOW all of the time, etc.
  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
}

