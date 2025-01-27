// To get the MAC address, open the Serial Monitor after uploading the code.
#include <WiFi.h> // Include the WiFi library

void setup() {
  Serial.begin(115200); // Start the serial communication
  
}

void loop() {
  // Get MAC Address
  uint8_t mac[6]; 
  WiFi.macAddress(mac);

  // Print MAC Address in desired format
  Serial.print("MAC Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print("0x");
    if (mac[i] < 0x10) { // Add leading zero for single-digit values
      Serial.print("0");
    }
    Serial.print(mac[i], HEX); // Print in hexadecimal
    if (i < 5) { // Add a comma between bytes
      Serial.print(", ");
    }
  }
  Serial.println();
  delay(2000);
}