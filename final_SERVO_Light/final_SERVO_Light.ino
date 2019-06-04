/*  CSE176A Continuous Servo Starter Code
 *   This example code makes the servo move counter-clockwise for two seconds, then
 *   switch directions for two seconds.
 *   
*/

#include <Servo.h>

Servo leftHand;  // Create servo object to control a servo
Servo rightHand;
unsigned long time;

int servo_speed = 0; // The speed ranges between -90 and 90. Negative values
                     // move the servo clockwise and positive values move the
                     // servo counter-clockwise. A larger distance from 0 will
                     // make the servo move faster.

int backSensorRight = 2;
int backSensorLeft = 3;
int headSensor = 4;
int frontSensor = 5;

int touchValueBackRight = 0; // Variable to store the value coming from the sensor
int touchValueBackLeft = 0; // Variable to store the value coming from the sensor
int touchValueHead = 0; // Variable to store the value coming from the sensor
int touchValueFront = 0; // Variable to store the value coming from the sensor

int startPressed = 0; // Variable to track when the button was pressed
int endPressed = 0; // Variable to track when button was released
int lastSensorState = 0; // Variable to keep track of last sensor state
int heldTime = 0;

void setup() {
  rightHand.attach(9);  // Attaches the servo on pin 9 to the servo object
  leftHand.attach(10); // Attaches the servo on pin 10 to the servo object
  pinMode(6, OUTPUT); // Set pins 6 and 7 as LED output
  pinMode(7, OUTPUT);
  digitalWrite(6, HIGH); // Set pins 6 and 7 to be off at setup
  digitalWrite(7, HIGH);
  Serial.begin(9600); // Enable the serial terminal for debugging.
}

void loop() {

  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  if(sensorValue < 500) {
      Serial.println("T"); // send the letter T (for Trigger) once the sensor value is bigger than 200  
  } else {
      Serial.println("K");
  }

  delay(1000);

  touchValueBackRight = digitalRead(backSensorRight); // Read values from each sensor
  touchValueBackLeft = digitalRead(backSensorLeft);
  touchValueHead = digitalRead(headSensor);
  touchValueFront = digitalRead(frontSensor);

  if (touchValueBackRight == 1 || touchValueBackLeft == 1 ||
  touchValueHead == 1 || touchValueFront == 1) {
  // If any of the sensors are touched, the robot will hug you

  if ((touchValueBackRight == 1 && touchValueBackLeft == 1)) {
    lightLED();
  }

  Serial.println(touchValueBackRight);
    
  rightHand.attach(9);
  rightHand.write(set_speed(-40)); // myservo.write() changes the speed of the servo.
                                  // set_speed() normalizes the speed between -90 and 90.
  leftHand.attach(10);
  leftHand.write(set_speed(40));  
                                
  delay(4000);                  // This delay tells the microcontroller to do 
                                // nothing for 5 seconds -- the servo
                                // will continue its last command for 5 seconds.
  }

  else {
  rightHand.write(set_speed(40));
  leftHand.write(set_speed(-40));
  // rightHand.detach();
  // leftHand.detach();
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH); // turn both LEDs off once hugging stops
  // time = millis();
  delay(1000);
  endPressed = millis();
  }
}

void lightLED() {
   if (touchValueBackRight == 1 && touchValueBackLeft == 1) {
      startPressed = millis(); // start time of when button was pressed
      heldTime = startPressed - endPressed;
      if (heldTime > 5000) {
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
      }
  }
}

//This function controls the speed of the servo
int set_speed(int pos){
  return(90 + pos); // This returns the new speed with an offset of 90 to normalize the
                    // speed between -90 and 90.
}
