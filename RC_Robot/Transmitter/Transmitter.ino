#include <esp_now.h>
#include <WiFi.h>

#define VRX_PIN 33 // ESP32 pin connected to VRX pin of joystick
#define VRY_PIN 32 // ESP32 pin connected to VRY pin of joystick

// MAC Address of the receiver ESP32
uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0xE1, 0xEE, 0x60};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int x;
  int y;
} struct_message;

// Create a struct_message called myData
struct_message myData;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
}

void loop() {
  // Read joystick values
  myData.x = analogRead(VRX_PIN);
  myData.y = analogRead(VRY_PIN);

  // Debug print joystick values
  Serial.print("Joystick X: ");
  Serial.print(myData.x);
  Serial.print(" Joystick Y: ");
  Serial.println(myData.y);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(100);
}
