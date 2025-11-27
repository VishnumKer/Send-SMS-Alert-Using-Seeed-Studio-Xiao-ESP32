# 🚨 Smart SMS Alert System using XIAO ESP32-S3

The **Smart SMS Alert System** is a compact IoT project built with the **XIAO ESP32-S3** and an **HC-SR04 ultrasonic sensor**.  
It works as a motion detection system—whenever an object moves close to the sensor and crosses a predefined threshold, it immediately triggers an **SMS alert**.  
The ESP32 sends these notifications directly to your phone using **Wi-Fi** and a **free SMS API provided by Circuit Digest Cloud**.

Circuit Digest Cloud offers a free SMS platform where users can generate an **API key** and **template ID**, allowing easy customization of messages without needing any backend server.

---

## 🧩 Components Required

| Component | Description | Qty |
|----------|-------------|-----|
| **XIAO ESP32-S3** | Main controller that reads sensor data and sends SMS alerts | 1 |
| **HC-SR04 Ultrasonic Sensor** | Detects movement by measuring object distance | 1 |
| **Breadboard** | Used for assembling the prototype | 1 |
| **Jumper Wires** | Connects components on the breadboard | 6–8 |

---

## 📡 How the System Works

The HC-SR04 ultrasonic sensor continuously checks the distance of nearby objects.  
If an object moves within the threshold (e.g., **100 cm**), the ESP32 sends an SMS alert using Seeed Studio’s XIAO board.

This setup is flexible—depending on your project, you can replace the ultrasonic sensor with another sensor such as:

- **DHT11** → temperature-based SMS alerts  
- **PIR motion sensor** → human detection  
- **Water sensor** → flood alert  
- **MQ gas sensor** → leak detection  

By using the same SMS-sending logic, any sensor can trigger automated alerts.

---

## 🔄 Workflow

1. **Initialization**  
   ESP32-S3 starts, configures the ultrasonic sensor, and connects to Wi-Fi.

2. **Distance Monitoring**  
   Sensor sends ultrasonic pulses and calculates the distance.

3. **Movement Detection**  
   If an object comes within the threshold distance (e.g., **100 cm**), the ESP32 marks it as a motion event.

4. **Alert Trigger**  
   The ESP32 prepares an HTTP POST request containing:  
   - API Key  
   - Template ID  
   - SMS variables  

5. **Cloud Processing**  
   Circuit Digest Cloud receives the request and formats the SMS based on the selected template.

6. **User Notification**  
   The SMS is delivered instantly to the user’s mobile number.

7. **System Reset**  
   Once movement stops, the ESP32 resets the alert flag so it’s ready for the next event.

---

## ⭐ Why XIAO ESP32-S3?

- **Ultra-miniature design**, ideal for compact or wearable applications  
- **Built-in Wi-Fi and Bluetooth**, perfect for IoT projects  
- Easy to program using the **Arduino IDE**  
- **Cost-effective**, yet powerful and reliable  
- Clear and easy-to-understand **pinout documentation** from Seeed Studio  

---

## 📘 Summary

This Smart SMS Alert System demonstrates how IoT devices can be used for real-time monitoring and alerting.  
Using the XIAO ESP32-S3 and Circuit Digest Cloud, you can easily create automated SMS notifications for security, safety, and monitoring applications.

---

