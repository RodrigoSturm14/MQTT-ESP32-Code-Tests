#include <WiFi.h>
#include <PubSubClient.h>
#include "BluetoothSerial.h"

// WiFi
const char *ssid = "False";     // Enter your WiFi name
const char *password = "False";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";  // broker address
const char *topic = "SALIDA/01";            // define topic
const char *mqtt_username = "RodSturm";     // username for authentication
const char *mqtt_password = "racing2018";   // password for authentication
const int mqtt_port = 1883;                  // port of MQTT over TCP

// Output control components
#define PINLED 18
int PAYLOADINT;

// Define espClient as a WiFiClient object class and  client as PubSubClient object class.
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Set PINLED as output
  pinMode(PINLED, OUTPUT);
  // Set software serial baud to 115200;
  Serial.begin(115200);
  



  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  //connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public emqx mqtt broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  // publish and subscribe
  client.publish(topic, "Hola EMQX y CELULAR I'm ESP32 ^^");
  client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  
  char payload_string[length + 1];

  memcpy(payload_string, payload, length);
  payload_string[length] = '\0';
  PAYLOADINT = atoi(payload_string);

  Serial.println();
  Serial.print("Payload as a integer:");
  Serial.print(PAYLOADINT);

  Serial.println();
  Serial.println("-----------------------");

  if(PAYLOADINT == 1){
    digitalWrite(PINLED, HIGH);
  }
  else if(PAYLOADINT == 0){
    digitalWrite(PINLED, LOW);
  }
}

void loop() {
  client.loop();
}