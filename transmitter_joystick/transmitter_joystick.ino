/**

Library: TMRh20/RF24, https://github.com/tmrh20/RF24/

**/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN digital pins on Arduino
const byte address[6] = "01000"; // Address common to both the transmitter and receiver modules.

struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
};

MyData data;

void setup() {
  radio.begin();
  radio.openWritingPipe(address); // use radio.openWritingPipe(n, address) for more addresses
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
}

//  Function to constrain and map joystick values
void joystickValues(int val, int minVal, int midVal, int maxVal, boolean reverse) {
  val = constrain(val, minVal, maxVal);

  if (val < midVal) {
    val = map(val, minVal, midVal, 0, 127);
  }
  else {
    val = map(val, midVal, maxVal, 127, 255);
  }
  return (reverse ? 255 - val : val); // Accounting for a reversal of joystick functionality caused by wrong wiring.
}

void loop() {

  //  Populating the MyData struct
  data.throttle = joystickValues(analogRead(A0), 183, 473, 780, false);
  data.yaw = joystickValues(analogRead(A1), 122, 432, 744, false);
  data.pitch = joystickValues(analogRead(A2), 274, 593, 897, false);
  data.roll = joystickValues(analogRead(A3), 294, 593, 919, false);

  radio.write(&data, sizeof(MyData));

  Serial.print("T: ");
  Serial.print(data.throttle);
  Serial.print(" | ");
  Serial.print("Y: ");
  Serial.print(data.yaw);
  Serial.print(" | ");
  Serial.print("P: ");
  Serial.print(data.pitch);
  Serial.print(" | ");
  Serial.print("R: ");
  Serial.println(data.roll);
}
