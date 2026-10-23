// Radio Receiver Test Code
#include <LoRa.h>

String inText = "";
String inMessage = "";
int packetSize;
int inChar;
void setup() {
  Serial.begin(9600);

}

void loop() {
  packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read Packet
    while (LoRa.available()) {
        inChar = LoRa.read();
        inText += (char)inChar;
        inMessage = inText;
    }
    inText = "";
    LoRa.packetRssi();
  }
  Serial.println(inMessage);

}
