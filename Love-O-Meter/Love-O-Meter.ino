/* 
 This sketch takes advantage of arduino's Analog-to-Digital Converter (ADC).
 Analog pins A0-A5 can report back a value between 0-1023, which maps to a range from 0 to 5 volts.
 Uses a temperature sensor which outputs a changing voltage depending on the temperature it senses
 This sensor has three pins -- one that connects to ground, another that connects to power, and 
 another one that outputs the variable voltage to arduino.  There are several different models
 of temperature sensors; we are using a TMP36 which outputs voltage directly proportional to
 the temperature it senses in Celsius.  The order of the pins matters!  If the TMP36 is facing
 away form you, the right pin should be connected to power, the middle to an Analog input pin, and
 the left pin to ground.
 A baud rate (commonly set as 9600 for a serial port) is essentially the bits per second configuration.  A 'baud' 
 can represent any amount of bits.  For example, if a baud represents 1 bit, and the baud rate is 9600 bauds/second, then
 our media is capable of sending up to 9600 bits per second.
 Opening the serial monitor: cmd + shift + M
*/

// Define constants (constants cannot change; at compile time, they are converted to their values permanently)
const int sensorPin = A0;
const float baselineTemp = 25.0;
const int output_pins_size = 3;
const int temp_interval = 2;

// Our outputs pins which will be hooked to 3 LEDS
int outputPins [output_pins_size] = {2, 3, 4};

void setup() {

  // open up a serial port to log to my PC
  Serial.begin(9600); // set the buad rate to 9600 (9600 bits per second)
  
  // set our outputPins to output
  for (int pin = 0; pin < output_pins_size; pin++) {
    pinMode(outputPins[pin], OUTPUT);
    digitalWrite(outputPins[pin], LOW); // start them out as LOW (off)
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin); // analogRead will return a value between 0 and 1023, representing the voltage on the pin.

  // now to log to the Arduino IDE's serial monitor through our serial connection
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  // calculate voltage ( a fraction of the 5V we are running through our TMP36)
  
  float voltage = (sensorVal / 1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  /* 
   * Now let's calculate the Celsius from the voltage.  The 'datasheet' (manual for electronic components)
   * for this particularsensor describes that every 10 milivolts of change from the sensor is equivalent to
   * 1 degree Celsius.  It also indicates that the sensor can read temperatures below 0 Celsius.
  */

  float temperature = (voltage - 0.5) * 100;
  Serial.print(" , degrees C: "); 
  Serial.println(temperature); // println creates a new line after it prints the value.
  
  // check our temperature and adjust our output LEDs accordingly
  if (temperature < baselineTemp) {
    digitalWrite(outputPins[0], LOW);
    digitalWrite(outputPins[1], LOW);
    digitalWrite(outputPins[2], LOW);
  } else if ((temperature >= baselineTemp + temp_interval) && (temperature < baselineTemp + (2 * temp_interval))) {
    digitalWrite(outputPins[0], HIGH);
    digitalWrite(outputPins[1], LOW);
    digitalWrite(outputPins[2], LOW);
  } else if ((temperature >= baselineTemp + (2 * temp_interval)) && (temperature < baselineTemp + (3 * temp_interval))) {
    digitalWrite(outputPins[0], HIGH);
    digitalWrite(outputPins[1], HIGH);
    digitalWrite(outputPins[2], LOW);
  } else if (temperature >= baselineTemp + (3 * temp_interval)) {
    digitalWrite(outputPins[0], HIGH);
    digitalWrite(outputPins[1], HIGH);
    digitalWrite(outputPins[2], HIGH);
  }
  // Give arduino's ADC some time to process
  delay(1);
}
