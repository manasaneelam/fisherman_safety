#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Received a packet
    Serial.print("Received packet: ");

    // Read packet until there's no data left
    while (LoRa.available()) {
      // Read the incoming byte
      String packetData = LoRa.readStringUntil(',');

      // Check if the received data starts with "Latitude: "
      if (packetData.startsWith("Latitude: ")) {
        // Extract latitude and longitude
        String latitude = packetData.substring(10); // Skip "Latitude: "
        String longitude = LoRa.readStringUntil(',');

        // Read counter value
        int counter = LoRa.parseInt();

        // Print parsed data
        Serial.print("Latitude: ");
        Serial.print(latitude);
        Serial.print(", Longitude: ");
        Serial.print(longitude);
        Serial.print(", Counter: ");
        Serial.println(counter);
      }
    }

    // Print RSSI of packet
    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());
  }
}