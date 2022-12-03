#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* subTopic = "command";

const char* ssid ="Xiaomi 12"; 
const char* password ="1234567890";
const char* topic = "velocity";
char hostname[] ="192.168.107.250"; 
int port = 1883;

// Our unique name - change to
#define TOKEN "AndyOpenScout"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

String inputString = "";
boolean stringComplete = false;
boolean busy = false;
boolean flag = false;
String MQTTin = "";

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

  client.connect(TOKEN);

  // Subscribe to the command topic
  client.subscribe("command");
  
  // Set the message received callback
  client.setCallback(onMessage);
}

// This function handles MQTT received messages
void onMessage(char* t, byte* payload, unsigned int length)
{
  
  if (strcmp(t, subTopic)==0)
  {
    flag = true;
    // Convert the message payload from bytes to a string
    String message = "";
    for (unsigned int i=0; i< length; i++)
    {
      message = message + (char)payload[i];
    }
    
    // make message available
    MQTTin = message;
  }
}

// Publish these two values to MQTT
void MQTTPOST(int x, int z)
{

  String myX = String(x);
  String myZ = String(z);
  // My Serialisation string
  String s ="{";
  // x is forward velocity
  s +="\"x\":" + myX + ",";
  // z is angular velocity
  s +="\"z\":" + myZ + "}";
  char attributes[1000];
  s.toCharArray(attributes, 1000);
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
      MQTTPOST(x,z);
    } 
    // clear ready for next message
    inputString = "";
    stringComplete = false;
  }
  
  // Has a motor command been received
  if (flag)
  {
    Serial.println(MQTTin);
    MQTTin = "";
    flag = false;
  }
  
  // If MQTT has disconnected
  if (!client.connected())
  {
    reconnect();
  }
  
  // Keep checking MQTT subscribed topic
  client.loop();
}

// If MQTT connection breaks
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

    // Keep trying MQTT connection
    if ( !client.connect(TOKEN) )
    {
      delay(5000);
    }

  }
}
