#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "Mi 9 Lite";          // Replace with your Wi-Fi SSID
const char* password = "345678912";  // Replace with your Wi-Fi Password


// Define LED pins
const int redLED = 4;
const int greenLED = 5;
const int yellowLED = 19;
const int blueLED = 22;

// Variables for polling (timers)
unsigned long prevRedTime = 0;
unsigned long prevGreenTime = 0;
unsigned long prevYellowTime = 0;
unsigned long prevBlueTime = 0;

// Blink intervals (in milliseconds)
const unsigned long redInterval = 800;
const unsigned long greenInterval = 650;
const unsigned long yellowInterval = 2350;
const unsigned long blueInterval = 3450;
void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

    // Initialize LEDs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  // Connect to your Wi-Fi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for the connection to establish
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Configure OTA
  ArduinoOTA.setHostname("esp32-ota");   // Optional: Set a custom hostname
  // ArduinoOTA.setPassword("admin");    // Optional: Set an OTA password

  // OTA Event Handlers (Optional but recommended for debugging)
  ArduinoOTA.onStart([]() {
    Serial.println("Start updating...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nUpdate Complete!");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("OTA Progress: %u%%\r", (progress * 100) / total);
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("OTA Error [%u]: ", error);
    if      (error == OTA_AUTH_ERROR)    Serial.println("Authentication Failed");
    else if (error == OTA_BEGIN_ERROR)   Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connection Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR)     Serial.println("End Failed");
  });

  // Start the OTA service
  ArduinoOTA.begin();

  Serial.println("Ready for OTA updates.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // Handle OTA updates
  ArduinoOTA.handle();
  // Get current time
  unsigned long currentMillis = millis();

  // Polling for Red LED
  if (currentMillis - prevRedTime >= redInterval) {
    prevRedTime = currentMillis;
    digitalWrite(redLED, !digitalRead(redLED)); // Toggle LED
  }

  // Polling for Green LED
  if (currentMillis - prevGreenTime >= greenInterval) {
    prevGreenTime = currentMillis;
    digitalWrite(greenLED, !digitalRead(greenLED)); // Toggle LED
  }

  // Polling for Yellow LED
  if (currentMillis - prevYellowTime >= yellowInterval) {
    prevYellowTime = currentMillis;
    digitalWrite(yellowLED, !digitalRead(yellowLED)); // Toggle LED
  }

  // Polling for Blue LED
  if (currentMillis - prevBlueTime >= blueInterval) {
    prevBlueTime = currentMillis;
    digitalWrite(blueLED, !digitalRead(blueLED)); // Toggle LED
  }
}
