#include <ArduinoJson.h>


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void serialEvent3()
{
  while (Serial3.available())
  {
    // get the new byte:
    char inChar = (char)Serial3.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

void setup() {
  // Initialize "debug" serial port
  Serial.begin(115200);
  // Serial link to ESP8266
  Serial3.begin(115200);
}
 
void loop() {
  // Values we want to transmit
  long timestamp = millis();
  int value = random(300);

  // Send the JSON document over the "link" serial port
  Serial3.println("{x:" + String(timestamp)+",z:"+String(value)+"}");
  
  // Receive
  if (stringComplete)
  {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  delay(1);
}
