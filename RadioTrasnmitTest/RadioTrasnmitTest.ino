// Radio Trasnmitter Test Code
#include <LoRa.h>

String text = "test";
void setup() {
  Serial.begin(9600);

}

void loop() {
  LoRa.beginPacket();
  LoRa.print(text);
  LoRa.endPacket();
  delay(500);
}
