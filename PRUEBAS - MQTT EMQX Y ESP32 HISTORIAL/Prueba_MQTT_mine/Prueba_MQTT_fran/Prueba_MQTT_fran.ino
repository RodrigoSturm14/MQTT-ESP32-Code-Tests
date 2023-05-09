#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient esp32Client;
PubSubClient mqttClient(esp32Client);

const char* ssid = "Estudiantes";
const char* password = "educar_2018";

char* server = "broker.emqx.io";
int port = 1883;

int ledpin = 26;
int ledpin1 = 27;
int ledpin2 = 14;
int ledpin3 = 12;
int ledpin4 = 13;

int aux = 0;
char datos[40];
String resultS = "";

void wifiInit() {
  Serial.print("Conectándose a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Conectado a WiFi");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");

  char payload_string[length + 1];

  int resultI;

  memcpy(payload_string, payload, length);
  payload_string[length] = '\0';
  resultI = atoi(payload_string);

  aux = resultI;

  resultS = "";

  for (int i = 0; i < length; i++) {
    resultS = resultS + (char)payload[i];
  }
  Serial.println();
  Serial.print("resultS:");
  Serial.print("?");
  Serial.print(resultS);
  Serial.print("?");
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.print("Intentando conectarse MQTT...");

    if (mqttClient.connect("arduinoClient")) {
      Serial.println("Conectado");

      mqttClient.subscribe("Entrada/01");

    } else {
      Serial.print("Fallo, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" intentar de nuevo en 5 segundos");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ledpin, OUTPUT);
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);
  pinMode(ledpin4, OUTPUT);
  Serial.begin(115200);
  delay(10);
  wifiInit();
  mqttClient.setServer(server, port);
  mqttClient.setCallback(callback);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

  Serial.print("String: ");
  Serial.println(resultS);
  Serial.print("Aux: ");
  Serial.println(aux);
  if (aux == 0) {
    digitalWrite(ledpin, LOW);
  } else if (aux == 1) {
    digitalWrite(ledpin, HIGH);
  } else if (aux == 2) {
    digitalWrite(ledpin1, LOW);
  } else if (aux == 3) {
    digitalWrite(ledpin1, HIGH);
  } else if (aux == 4) {
    digitalWrite(ledpin2, LOW);
  } else if (aux == 5) {
    digitalWrite(ledpin2, HIGH);
  } else if (aux == 6) {
    digitalWrite(ledpin3, LOW);
  } else if (aux == 7) {
    digitalWrite(ledpin3, HIGH);
  } else if (aux == 8) {
    digitalWrite(ledpin4, LOW);
  } else if (aux == 9) {
    digitalWrite(ledpin4, HIGH);
  }



  delay(5000);
}
