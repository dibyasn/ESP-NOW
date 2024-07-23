//Receiver Code
#include <esp_now.h>
#include <WiFi.h>

// Motor control pins
#define MOTORA_ENABLE 23

#define MOTORA_INPUT_1 19
#define MOTORA_INPUT_2 18

#define MOTORB_ENABLE 5

#define MOTORB_INPUT_1 2
#define MOTORB_INPUT_2 4

// Structure to receive data
typedef struct struct_message {
  int x;
  int y;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Received X: ");
  Serial.print(myData.x);
  Serial.print(" Received Y: ");
  Serial.println(myData.y);
  controlMotors(myData.x, myData.y);
}

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

  // Register the receive callback
  esp_now_register_recv_cb(OnDataRecv);

  // Initialize motor control pins
  pinMode(MOTORA_ENABLE, OUTPUT);
  pinMode(MOTORA_INPUT_1, OUTPUT);
  pinMode(MOTORA_INPUT_2, OUTPUT);
  pinMode(MOTORB_ENABLE, OUTPUT);
  pinMode(MOTORB_INPUT_1, OUTPUT);
  pinMode(MOTORB_INPUT_2, OUTPUT);
  
  // Enable motors
  digitalWrite(MOTORA_ENABLE, HIGH);
  digitalWrite(MOTORB_ENABLE, HIGH);

  Serial.println("Setup complete");
}

void controlMotors(int x, int y) {
  // Define thresholds
  int LowL = 1500;
  int HighL = 2000;


  // Debug print motor values
  Serial.print("Received X: ");
  Serial.print(x);
  Serial.print(" Received Y: ");
  Serial.println(y);

  if (y > HighL ) {
    // Move forward
    Serial.println("Moving forward");
    digitalWrite(MOTORA_INPUT_1, LOW);
    digitalWrite(MOTORA_INPUT_2, HIGH);
    digitalWrite(MOTORB_INPUT_1, HIGH);
    digitalWrite(MOTORB_INPUT_2, LOW);
  } else if (y < LowL ) {
    // Move backward
    Serial.println("Moving backward");
    digitalWrite(MOTORA_INPUT_1, HIGH);
    digitalWrite(MOTORA_INPUT_2, LOW);
    digitalWrite(MOTORB_INPUT_1, LOW);
    digitalWrite(MOTORB_INPUT_2, HIGH);
  } else if (x > HighL ) {
    // Turn left
    Serial.println("Turning left");
    digitalWrite(MOTORA_INPUT_1, HIGH);
    digitalWrite(MOTORA_INPUT_2, LOW);
    digitalWrite(MOTORB_INPUT_1, HIGH);
    digitalWrite(MOTORB_INPUT_2, LOW);
  } else if (x < LowL) {
    // Turn right
    Serial.println("Turning right");
    digitalWrite(MOTORA_INPUT_1, LOW);
    digitalWrite(MOTORA_INPUT_2, HIGH);
    digitalWrite(MOTORB_INPUT_1, LOW);
    digitalWrite(MOTORB_INPUT_2, HIGH);
  } else {
    // Stop
    Serial.println("Stopping");
    digitalWrite(MOTORA_INPUT_1, LOW);
    digitalWrite(MOTORA_INPUT_2, LOW);
    digitalWrite(MOTORB_INPUT_1, LOW);
    digitalWrite(MOTORB_INPUT_2, LOW);
  }

  // Enable PWM (not used here, but kept for reference)
  digitalWrite(MOTORA_ENABLE, HIGH);
  digitalWrite(MOTORB_ENABLE, HIGH);
}

void loop() {
  // Do nothing in loop, waiting for data
}
