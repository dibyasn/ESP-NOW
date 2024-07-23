// To get the MAC address, open the Serial Monitor after uploading the code.
// The MAC address will be printed three times, with a 4-second delay between each print.

#include <WiFi.h>

void setup() {
  Serial.begin(115200);

  // Get the MAC address of the ESP32 as per the required format
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);

  // Print the MAC address in the desired format three times with a delay
  for (int j = 0; j < 3; j++) {
    Serial.print("MAC Address: ");
    for (int i = 0; i < 6; i++) {
      Serial.print("0x");
      if (mac[i] < 16) Serial.print("0");
      Serial.print(mac[i], HEX);
      if (i < 5) Serial.print(", ");
    }
    Serial.println();

    // Delay for 4 seconds
    delay(4000);
  }
}

void loop() {
  // Nothing to do here
}
