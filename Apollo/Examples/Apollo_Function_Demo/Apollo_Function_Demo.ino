// This code demonstrates the usage of the Apollo2 library for
//
// 1. A digital input in the form of a bumper switch.
// 2. Commanding the 3-wire motor ports (Motor port number and speed from -100% to 100%)
//

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#include <Apollo2.h>
#include <Servo.h>
Apollo2 APOLLO;

Servo motor2;
//              A, B, X, Y,UP,DN,LT,RT,L1,L2,L3,R1,R2,R3,LX,LY,RX,RY,Start,Select
int remote[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,    0,     0};
boolean stringComplete = false;
String inputString = "";
char tempChar[5];

void setup() {
  APOLLO.enableDebug(true);         // Print out extra debug information
  motor2.attach(APOLLO.motor[2]);   // Attach a motor to position M2

  SerialBT.begin("TA0050J2XR");     // Bluetooth device name

  // Configure an internal pullup on the button
  pinMode(APOLLO.sensor[0], INPUT_PULLUP);
}

long lastMessage = 0;
int counter = 0;
void readRemoteInput() {
  while (SerialBT.available()) {
    char inChar = (char)SerialBT.read();
    Serial.println("incoming");
    if (inChar == '.') {     // Handle the end of the message
      stringComplete = true;
      counter = 0;
    }
    else if (inChar == ',') { // Each time a comma is hit
      inputString.toCharArray(tempChar, 5);
      remote[counter] = atoi(tempChar);
      //Serial.print(counter);
      //Serial.print(" : ");
      //Serial.println(remote[counter]);
      inputString = "";
      counter++;
    }
    else {
      inputString += inChar;
    }
  }

  // Each Time there is a new message, this will trigger
  if (stringComplete) {
    stringComplete = false;
    lastMessage = millis();
    SerialBT.println(millis());
  }
}

void loop() {
  // Read a Bumper Sensor
  if (digitalRead(APOLLO.sensor[0])) {
    //Serial.println("Bumped!");
  }
  else {
    //Serial.println("Not Bumped!");
  }

  if (remote[APOLLO.X] == 1) {
    APOLLO.setLED(true);
  }
  else if (remote[APOLLO.Y] == 1) {
    APOLLO.setLED(false);
  }

  motor2.write(map(remote[APOLLO.RY],-100,100,0,180));

  readRemoteInput();
}
