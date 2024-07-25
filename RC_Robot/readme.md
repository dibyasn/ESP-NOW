# Two-Wheel Drive Mobile Robot with Joystick Control 🤖

Welcome to the Two-Wheel Drive Mobile Robot Project! This project uses an ESP32 board with the ESP-NOW protocol to control a mobile robot using a joystick.

## Table of Contents
- [Two-Wheel Drive Mobile Robot with Joystick Control 🤖](#two-wheel-drive-mobile-robot-with-joystick-control-)
  - [Table of Contents](#table-of-contents)
  - [📖 Introduction](#-introduction)
  - [📡 About ESP-NOW](#-about-esp-now)
  - [🔧 Components](#-components)
  - [🔌 Circuit Diagram](#-circuit-diagram)
    - [Transmitter Connections:](#transmitter-connections)
    - [Receiver Connections:](#receiver-connections)
  - [🚀 Setup Instructions](#-setup-instructions)
    - [1. Clone the Repository](#1-clone-the-repository)
    - [2. Install Required Libraries](#2-install-required-libraries)
    - [3. Find MAC Address](#3-find-mac-address)
    - [4. Upload the Code](#4-upload-the-code)
  - [💡 Code Explanation](#-code-explanation)
    - [Transmitter Code](#transmitter-code)
    - [Receiver Code](#receiver-code)
    - [Customization Notes](#customization-notes)
  - [🖥️ Usage](#️-usage)
  - [🎉 Acknowledgments](#-acknowledgments)

## 📖 Introduction
This project demonstrates how to control a two-wheel drive robot using a joystick. An ESP32 board with ESP-NOW communication sends joystick values to another ESP32, which then controls the robot's motors.

## 📡 About ESP-NOW
ESP-NOW is a connectionless Wi-Fi communication protocol developed by Espressif. It allows multiple devices to communicate with one another without the need for a router. Key features of ESP-NOW include:

- **Low Latency:** ESP-NOW has very low latency, making it ideal for real-time applications like remote controls.
- **Low Power Consumption:** ESP-NOW consumes less power compared to traditional Wi-Fi communication.
- **Peer-to-Peer Communication:** Devices can communicate directly with each other, which simplifies network topology and reduces complexity.
- **Up to 20 Peers:** ESP-NOW supports communication with up to 20 devices simultaneously, making it suitable for large-scale networks.
- **AES Encryption:** ESP-NOW supports AES-128 encryption, ensuring secure communication between devices.
- **Range:** The range of ESP-NOW communication can vary based on the environment and obstacles, but typically, it can reach up to 200 meters (656 feet) in an open space without obstructions. Indoors, the range might be reduced to around 50 meters (164 feet) due to walls and other obstacles.

## 🔧 Components
- **2 x ESP32 Boards**
- **Joystick Module**
- **DC Motors (2)**
- **L293D Motor Driver Module**
- **Jumper Wires**
- **Breadboard**

## 🔌 Circuit Diagram

### Transmitter Connections:
```
  Joystick         Transmitter ESP32
  ─────────────    ─────────────────
  VRX  ──────────> GPIO 33
  VRY  ──────────> GPIO 32
  3.3V ──────────> 3.3V
  GND ──────────> GND
```

### Receiver Connections:
```plaintext
+------------------+           +-------------+
|  Motor Driver    |           |   ESP32     |
|   Module         |           |             |
|                  |           |             |
|   VCC            -----> +5V Power Supply   |
|   GND            -----> GND Power Supply   |
|   MOTORA_ENABLE  -----> GPIO 23            |
|   MOTORA_INPUT_1 -----> GPIO 19            |
|   MOTORA_INPUT_2 -----> GPIO 18            |
|   MOTORB_ENABLE  -----> GPIO 5             |
|   MOTORB_INPUT_1 -----> GPIO 2             |
|   MOTORB_INPUT_2 -----> GPIO 4             |
+------------------+           +-------------+



+------------------+           +------------+
|  Motor Driver    |           |   DC Motors|
|   Module         |           |            |
|                  |           |            |
|   Vbat            -----> +V Power Supply  |
|   GND            -----> GND Power Supply  |
|   MOTORA_OUT1    -----> Motor A Terminal 1  |
|   MOTORA_OUT2    -----> Motor A Terminal 2  |
|   MOTORB_OUT1    -----> Motor B Terminal 1  |
|   MOTORB_OUT2    -----> Motor B Terminal 2  |
+------------------+           +------------+
```

## 🚀 Setup Instructions
### 1. Clone the Repository
```sh
git clone https://github.com/dibyasn/ESP-NOW.git
```

### 2. Install Required Libraries
Ensure you have the following libraries installed in the Arduino IDE:
- **ESP-NOW** 🌐
- **WiFi** 🌐

### 3. [Find MAC Address](https://github.com/dibyasn/ESP-NOW/tree/main/RC_Robot/MAC_Adds)
Upload the "Find MAC Address" code to reciver ESP32 board to get their MAC addresse. Replace `broadcastAddress[]` in the Transmitter code with the MAC address of the Receiver ESP32.

```cpp

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

//if you are not getting the MAC address in serial monitor press the "EN" button of ESP32 board

```

### 4. Upload the Code
1. **Upload the MAC Address Code to Receiver:**
   - Connect the receiver ESP32 to your computer.
   - Upload the MAC address code.
   - Open the Serial Monitor to find the MAC address of the receiver.

2. **Replace MAC Address in Transmitter Code:**
   - Replace `broadcastAddress[]` in the transmitter code with the MAC address obtained from the receiver.

3. **Upload the Transmitter Code:**
   - Connect the transmitter ESP32 to your computer.
   - Upload the transmitter code.

4. **Upload the Receiver Code:**
   - Connect the receiver ESP32 to your computer.
   - Upload the receiver code.

5. **Connect the Joystick and Motors:**
   - Follow the circuit diagram to connect the joystick to the transmitter ESP32.
   - Connect the motor driver and motors to the receiver ESP32.

## 💡 Code Explanation

### [Transmitter Code](https://github.com/dibyasn/ESP-NOW/tree/main/RC_Robot/Transmitter)
**Purpose:** Sends joystick values to the receiver ESP32.

**Features:**
- Reads values from the joystick.
- Sends these values using ESP-NOW.

```cpp
#include <esp_now.h>
#include <WiFi.h>

#define VRX_PIN 33 // ESP32 pin connected to VRX pin of joystick
#define VRY_PIN 32 // ESP32 pin connected to VRY pin of joystick

// MAC Address of the receiver ESP32
uint8_t broadcastAddress[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

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
```

### [Receiver Code](https://github.com/dibyasn/ESP-NOW/tree/main/RC_Robot/Receiver)
**Purpose:** Receives joystick values and controls motors based on these values.

**Features:**
- Receives joystick data via ESP-NOW.
- Controls motor direction (forward, backward, left, right, stop) based on joystick input.

```cpp
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

  if (y > HighL) {
    // Move forward
    Serial.println("Moving forward");
    digitalWrite(MOTORA_INPUT_1, LOW);
    digitalWrite(MOTORA_INPUT_2, HIGH);
    digitalWrite(MOTORB_INPUT_1, HIGH);
    digitalWrite(MOTORB_INPUT_2, LOW);
  } else if (y < LowL) {
    // Move backward
    Serial.println("Moving backward");
    digitalWrite(MOTORA_INPUT_1, HIGH);
    digitalWrite(MOTORA_INPUT_2, LOW);
    digitalWrite(MOTORB_INPUT_1, LOW);
    digitalWrite(MOTORB_INPUT_2, HIGH);
  } else if (x > HighL) {
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
```

### Customization Notes
**Joystick Center Value Calibration:** 
- The joystick in this project is connected to 3.3V. When at the center position, the values typically range from 1500 to 2000. 
- If your joystick is connected to a different voltage or exhibits different center values, you can adjust the `LowL` and `HighL` accordingly.

```cpp
int LowL = 1500;
int HighL = 2000;
```

**Motor Direction Adjustment:**
- Motor direction control depends on how you have physically connected the motors and motor driver to the ESP32.
- If your motor connections are different, you may need to modify the logic in the `controlMotors` function to match your setup.

```cpp
void controlMotors(int x, int y) {
  // Your customized motor control logic here
}
```

## 🖥️ Usage
1. Power on both the transmitter and receiver ESP32 boards.
2. Use the joystick to control the robot:
   - Push the joystick up to move forward.
   - Pull the joystick down to move backward.
   - Push the joystick left to turn left.
   - Push the joystick right to turn right.
   - Release the joystick to stop the robot.

## 🎉 Acknowledgments
This project makes use of ESP32's powerful features and ESP-NOW communication. Thanks to the ESP32 community for their support and resources.

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

Feel free to contribute, report issues, or suggest enhancements. Happy building! 🚀

<p align="center">
    <a href="https://github.com/dibyasn"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>