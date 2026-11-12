#include <SparkFun_u-blox_GNSS_v3.h> // Install "SparkFun u-blox GNSS v3" via Library Manager

SFE_UBLOX_GNSS_SERIAL myGNSS;

// Define free digital pins on the Arduino Nano ESP32 for Serial1
const int GNSS_RX_PIN = D0; // Connect to NEO-F10 TX
const int GNSS_TX_PIN = D1; // Connect to NEO-F10 RX

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for USB Serial Monitor to open
  Serial.println("NEO-F10N UART Test on Nano ESP32");

  // Start hardware Serial1 on custom pins at the NEO-F10 default 38400 baud
  Serial1.begin(38400, SERIAL_8N1, GNSS_RX_PIN, GNSS_TX_PIN);

  // Connect the library to Serial1
  while (myGNSS.begin(Serial1) == false) {
    Serial.println("u-blox GNSS not detected at 38400 baud. Retrying...");
    delay(1000);
  }

  Serial.println("GNSS connected!");
  
  // Optional: Save CPU overhead by outputting only UBX binary messages instead of NMEA
  myGNSS.setUART1Output(COM_TYPE_UBX); 
}

void loop() {
  // getPVT() returns true when a new Position, Velocity, Time solution arrives
  if (myGNSS.getPVT()) {
    long latitude = myGNSS.getLatitude();
    long longitude = myGNSS.getLongitude();
    byte SIV = myGNSS.getSIV();

    Serial.print("Lat: ");
    Serial.print(latitude / 10000000.0, 7);
    Serial.print(" | Lon: ");
    Serial.print(longitude / 10000000.0, 7);
    Serial.print(" | Satellites: ");
    Serial.println(SIV);
  }
}
