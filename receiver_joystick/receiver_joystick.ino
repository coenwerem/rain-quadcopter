/*
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "01000";

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  struct MyData {
    byte throttle;
    byte yaw;
    byte pitch;
    byte roll;
  };
  MyData data;

  if (radio.available()) {
    // char data[32] = "";
    radio.read(&data, sizeof(MyData));

    // Output Values
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
