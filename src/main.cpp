#include <Arduino.h>
#include <functions.h>
#include <globals.h>

#ifdef ESP32
  #include <M5Stack.h>
#endif

void setup() {
  Serial.begin(9600);
  while (!Serial);
  DEBUG_ERROR_SERIAL.println("This is an error message");
  DEBUG_WARNING_SERIAL.println("This is a warning message");
  DEBUG_INFORMATION_SERIAL.print("Some output value");
  DEBUG_INFORMATION_SERIAL.println(digitalRead(5) ? "HIGH" : "LOW");

}

void loop() {}