
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBluetoothTerminal;

// Handle received messages
char incomingChar;              // Each letter of the message will be received and stored here, one at a time.
String firstfinalmessage = "";  // Every letter from incomingChar will be concatenated and will form a string.
String nombrewifi = "nada";
String thirdfinalmessage = "";
//String confirmacion = "";

String recibir_primer_mensaje_bluetoothterminal() {  // NO NECESITA TENER PARAMETROS DE ENTRADA (inputs), YA QUE SOLAMENTE REALIZA UNA TAREA Y LUEGO DEVUELVE UN VALOR (finalmessage), POR LO TANTO NO HACE FALTA UN INPUT PARA LA FUNCION.

  SerialBluetoothTerminal.print("First final message: ");
  SerialBluetoothTerminal.println(firstfinalmessage);

  if (SerialBluetoothTerminal.available()) {

    incomingChar = SerialBluetoothTerminal.read();

    if (incomingChar != '\n') {

      firstfinalmessage += String(incomingChar);
    }

    else {

      firstfinalmessage = "";
    }

    //Serial.write(incomingChar);
    Serial.println("-------");
    Serial.println(firstfinalmessage);
    Serial.println("-------");
    //confirmacion == finalmessage;  ---> no se almacenan strings en otros strings de esta forma
  }
  delay(5000);

  return firstfinalmessage;
}

void cortar_bluetooth_con_LISTO() {

  if (firstfinalmessage == "LISTO") {

    SerialBluetoothTerminal.end();
    SerialBluetoothTerminal.print("MENSAJE FUERA DEL BLUETOOTH");
    Serial.println("MENSAJE SIN BLUETOOTH");
    delay(3000);
  }
}

void setup() {
  Serial.begin(115200);
  SerialBluetoothTerminal.begin("ESP32test");  //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  while (!SerialBluetoothTerminal.connect()) {
    //SerialBluetoothTerminal.disconnect();
    Serial.println("There is not a device connected");
    delay(2000);
  }

  /*if(! SerialBT.begin("ESP32test", true) ) {
    Serial.println("========== serialBT failed!");
    abort();
  }*/

  while (!SerialBluetoothTerminal.available()){

    Serial.println("Write your WiFi password: ");
    delay(2000);
  }

  while (true){

    recibir_primer_mensaje_bluetoothterminal();

  }
}

void loop() {

  /*

  recibir_primer_mensaje_bluetoothterminal();

  while (nombrewifi == "nada") {
    nombrewifi += firstfinalmessage;
        
  }
  cortar_bluetooth_con_LISTO();

  */
}
