<p align="center">
    <a href="https://github.com/espressif/esp-now/blob/master/User_Guide.md">
        <img src="https://www.espressif.com/sites/all/themes/espressif/images/esp-now/esp-now.png" alt="ESP-NOW" style="width: 100px;">
    </a>
</p>

# All About ESP-NOW 📡

Welcome to the comprehensive guide on ESP-NOW! This document provides detailed information about the ESP-NOW protocol, its features, applications, and how to get started with ESP-NOW on ESP32 boards.

## Table of Contents
- [All About ESP-NOW 📡](#all-about-esp-now-)
  - [Table of Contents](#table-of-contents)
  - [📖 Introduction](#-introduction)
  - [📡 What is ESP-NOW?](#-what-is-esp-now)
  - [🔑 Key Features of ESP-NOW](#-key-features-of-esp-now)
  - [🔧 How ESP-NOW Works](#-how-esp-now-works)
    - [Peer-to-Peer Communication](#peer-to-peer-communication)
    - [Broadcast Communication](#broadcast-communication)
    - [Security and Encryption](#security-and-encryption)
  - [📚 Use Cases and Applications](#-use-cases-and-applications)
  - [🚀 Getting Started with ESP-NOW](#-getting-started-with-esp-now)
    - [1. Setting Up the Development Environment](#1-setting-up-the-development-environment)
    - [2. Basic ESP-NOW Example](#2-basic-esp-now-example)
      - [Transmitter Code](#transmitter-code)
      - [Receiver Code](#receiver-code)
  - [🔄 Advanced ESP-NOW Concepts](#-advanced-esp-now-concepts)
    - [Mesh Networking](#mesh-networking)
    - [Handling Multiple Peers](#handling-multiple-peers)
    - [Optimizing Power Consumption](#optimizing-power-consumption)
  - [🖥️ Contributions](#-contributions)

## 📖 Introduction
ESP-NOW is a wireless communication protocol developed by Espressif Systems, the company behind the popular ESP8266 and ESP32 microcontrollers. It allows multiple devices to communicate directly with each other without the need for a traditional Wi-Fi network or router, making it ideal for IoT applications that require low-latency and low-power communication.

## 📡 What is ESP-NOW?
ESP-NOW is a proprietary protocol that enables efficient, low-latency communication between ESP8266, ESP32, and other compatible devices. Unlike traditional Wi-Fi communication, ESP-NOW does not require a central access point or router, allowing devices to communicate directly in a peer-to-peer or broadcast manner.

## 🔑 Key Features of ESP-NOW
- **Low Latency:** ESP-NOW provides quick communication, making it suitable for real-time applications.
- **Low Power Consumption:** Designed for efficient power usage, ideal for battery-operated devices.
- **Direct Communication:** Devices communicate directly without a central router.
- **Broadcast and Peer-to-Peer:** Supports both unicast (one-to-one) and broadcast (one-to-many) communication.
- **Secure Communication:** Supports AES-128 encryption for secure data transmission.
- **Scalability:** Can communicate with up to 20 devices simultaneously.

## 🔧 How ESP-NOW Works
ESP-NOW simplifies network topology by allowing devices to communicate directly with each other. Here's how it works:

### Peer-to-Peer Communication
In peer-to-peer communication, two devices communicate directly without an intermediary. Each device needs to know the MAC address of the other device to establish communication.

### Broadcast Communication
In broadcast communication, a device sends a message to multiple devices simultaneously. This is useful for scenarios where the same message needs to be delivered to multiple recipients.

### Security and Encryption
ESP-NOW supports AES-128 encryption, ensuring secure data transmission between devices. Devices need to exchange encryption keys beforehand to communicate securely.

## 📚 Use Cases and Applications
ESP-NOW is versatile and can be used in various applications, including:
- **Home Automation:** Control lights, appliances, and other devices without Wi-Fi.
- **Remote Sensing:** Collect data from sensors and transmit it to a central device.
- **Real-Time Data Monitoring:** Monitor and control devices in real-time.
- **IoT Networks:** Create robust IoT networks for smart cities, agriculture, and industrial applications.
- **Wireless Control Systems:** Implement remote control systems for robots, drones, and other devices.

## 🚀 Getting Started with ESP-NOW

To get started with ESP-NOW, you will need:
- **ESP32 Dev Kit V1 boards**
- **Arduino IDE or PlatformIO**
- **Basic understanding of C++ programming**
- **Familiarity with the Arduino framework**

### 1. Setting Up the Development Environment
- **Install the Arduino IDE:** Download and install the [Arduino IDE](https://www.arduino.cc/en/Main/Software).
- **Install the ESP32 Board Package:** Follow the instructions to add the ESP32 board to your Arduino IDE [here](https://github.com/espressif/arduino-esp32#installation-instructions).

### 2. Basic ESP-NOW Example

Here is a simple example to get you started with ESP-NOW:

#### Transmitter Code

```cpp
#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x40, 0x22, 0xD8, 0x57, 0xE7, 0x98};

void setup() {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(onDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  uint8_t data[] = "Hello ESP-NOW";
  esp_now_send(broadcastAddress, data, sizeof(data));
  delay(2000);
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
```
#### Receiver Code

```cpp
#include <esp_now.h>
#include <WiFi.h>

void setup() {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onDataRecv);
}

void loop() {}

void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Data: ");
  Serial.println((char*)incomingData);
}
```

## 🔄 Advanced ESP-NOW Concepts

### Mesh Networking
ESP-NOW can be used to create mesh networks, where each device can communicate with multiple other devices, forming a robust and scalable network.

### Handling Multiple Peers
ESP-NOW supports communication with up to 20 devices simultaneously. Each device needs to register the MAC addresses of its peers to establish communication.

### Optimizing Power Consumption
ESP-NOW is designed for low power consumption. By optimizing sleep modes and transmission intervals, devices can operate for extended periods on battery power.

## 🖥️ Contributions
Contributions are welcome! Feel free to submit pull requests to add new projects or improve existing ones.

<p align="center">
    <img src="https://64.media.tumblr.com/tumblr_lp0f2fIhnF1qa2ip8o1_1280.gif" alt="Thank You">
</p>

---

For any questions or suggestions, feel free to open an issue or contact us directly.



<p align="center">
    <a href="https://github.com/dibyasn"><img src="https://img.icons8.com/color/48/000000/github.png" alt="Contribute Icon"></a>
</p>