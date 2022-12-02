#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid ="Xiaomi 12"; 
const char* password ="1234567890";
const char* topic = "test";
char hostname[] ="192.168.107.250"; 
int port = 1883;

// Our unique name - change to
#define TOKEN "AndyOpenScout"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

String inputString = "";
boolean stringComplete = false;

// Run once
void setup()
{
  Serial.begin(115200);
  
  // Give time to setup - probably not needed
  while (!Serial) continue;
  
  WiFi.begin(ssid, password);
  
  // This can take time
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  // MQTT setup once WiFi is up
  client.setServer(hostname, port);
}

// Publish these two values to MQTT
void MQTTPOST(int x, int z)
{

  String myX = String(x);
  String myZ = String(z);
  // My Serialisation string
  String s ="{";
  // x is forward velocity
  s +="\"x\":"; 
  s += myX; 
  s +=",";
  // z is angular velocity
  s +="\"z\":";
  s += myZ;
  s +="}";
  char attributes[1000];
  s.toCharArray( attributes, 1000 );
  client.publish(topic, attributes);
}


// Triggered when data arrives on serial port
void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    inputString += inChar;
    // Look for EOL char - newline
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

// Repeat forever
void loop()
{
  // Have we finished receiving data?
  if (stringComplete)
    {
      StaticJsonDocument<50> doc;
      DeserializationError err = deserializeJson(doc, inputString);
      if (err == DeserializationError::Ok) 
      {
        // Print the values
        // (we must use as<T>() to resolve the ambiguity)
        int x = doc["x"].as<int>();
        int z = doc["z"].as<int>();
        Serial.println("{x:" + String(5)+",z:"+String(5)+"}");
        MQTTPOST(x,z);
      } 
      // clear ready for next message
      inputString = "";
      stringComplete = false;
      if (!client.connected())
      {
        reconnect();
      }
    }
}

// If WiFi drops - try again
void reconnect() 
{
  while (!client.connected())
  {
    int status = WiFi.status();
    if ( status != WL_CONNECTED) 
    {
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) 
       {
          delay(5000);
       }
    }

    // Wait until we try again
    if ( !client.connect("ESP8266 Device", TOKEN, NULL) )
    {
      delay(5000);
    }

  }
}
