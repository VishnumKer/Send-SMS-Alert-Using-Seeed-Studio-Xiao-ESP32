#include <WiFi.h>

// Ultrasonic sensor pins
#define TRIG_PIN 5
#define ECHO_PIN 3  // Safe GPIO for XIAO ESP32-S3

long duration;
float distance;

// WiFi credentials
const char *ssid = "Enter your SSID";   
const char *password = "********";   

// API credentials and SMS details
const char* apiKey = "your API Key";    
const char* templateID = "103";         
const char* mobileNumber = "91xxxxxxxxxx"; 
const char* var1 = "Sensor";        
const char* var2 = "In the Room";  

// Variable to avoid repeated SMS
bool alertSent = false;

void sendSMS() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client; 
    String apiUrl = "/send_sms?ID=" + String(templateID);

    Serial.print("Connecting to server...");
    if (client.connect("www.circuitdigest.cloud", 80)) { 
      Serial.println("connected!");

      // JSON payload
      String payload = "{\"mobiles\":\"" + String(mobileNumber) + 
                       "\",\"var1\":\"" + String(var1) + 
                       "\",\"var2\":\"" + String(var2) + "\"}";

      // HTTP POST request
      client.println("POST " + apiUrl + " HTTP/1.1");
      client.println("Host: www.circuitdigest.cloud");
      client.println("Authorization: " + String(apiKey));
      client.println("Content-Type: application/json");
      client.println("Content-Length: " + String(payload.length()));
      client.println();
      client.println(payload); 

      // Print server response
      while (client.connected() || client.available()) {
        if (client.available()) {
          String line = client.readStringUntil('\n');
          Serial.println(line);
        }
      }

      Serial.println("SMS sent (or attempted)!");
      client.stop(); 
    } else {
      Serial.println("Connection to server failed!");
    }
  } else {
    Serial.println("WiFi not connected!");
  }
}

// Function to read distance from ultrasonic sensor
float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Distance in cm
  return distance;
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Connect to WiFi
  Serial.println();
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float dist = readDistance();
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  // Trigger SMS if object closer than threshold (100 cm)
  if (dist < 100 && !alertSent) {
    Serial.println("Object too close! Sending SMS...");
    sendSMS();
    alertSent = true;  // prevent repeated SMS
  }

  // Reset alert once object moves away
  if (dist >= 100) {
    alertSent = false;
  }

  delay(500);
}
