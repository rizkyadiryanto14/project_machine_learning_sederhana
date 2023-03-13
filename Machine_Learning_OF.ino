#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "rizkyserver1";
const char* password = "12345678900";

ESP8266WebServer server(80);

// Declare the pin number where the LED is connected
const int LED_PIN = 5;

void handleRoot() {
  String html = "<html><head><title>NodeMCU LED Control</title></head><body>";
  html += "<h1>NodeMCU LED Control</h1>";
  html += "<form method='POST' action='/led'>";
  html += "<input type='submit' name='led' value='ON'>";
  html += "<input type='submit' name='led' value='OFF'>";
  html += "</form></body></html>";

  server.send(200, "text/html", html);
}

void handleLED() {
  if (server.hasArg("led")) {
    String ledState = server.arg("led");

    if (ledState == "ON") {
      digitalWrite(LED_PIN, HIGH);
    }
    else if (ledState == "OFF") {
      digitalWrite(LED_PIN, LOW);
    }
  }

  server.sendHeader("Location", "/");
  server.send(302);
}

void setup() {
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Start the server
  server.on("/", handleRoot);
  server.on("/led", handleLED);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
