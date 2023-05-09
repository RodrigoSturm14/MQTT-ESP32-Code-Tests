#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBluetoothTerminal;

// Handle received messages
char incomingChar;         // Each letter of the message will be received and stored here, one at a time.
String finalmessage = "";  // Every letter from incomingChar will be concatenated and will form a string.
//String confirmacion = "";

void setup() {
  Serial.begin(115200);
  SerialBluetoothTerminal.begin("ESP32test");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBluetoothTerminal.available()) {

    char incomingChar = SerialBluetoothTerminal.read();

    if (incomingChar != '\n') {

      finalmessage += String(incomingChar);
    }

    else {

      finalmessage = "";
    }

    //Serial.write(incomingChar);
    Serial.println("-------");
    Serial.println(finalmessage);
    //confirmacion == finalmessage;  ---> no se almacenan strings en otros strings de esta forma
  }

  if (finalmessage == "LISTO") {
    SerialBluetoothTerminal.end();
    SerialBluetoothTerminal.print("MENSAJE FUERA DEL BLUETOOTH");
    Serial.println("MENSAJE SIN BLUETOOTH");
    delay(3000);
  }
}