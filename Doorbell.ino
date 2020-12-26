#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>
#include <HTTPClient.h>

WebServer server;
AutoConnect Portal(server);
AutoConnectConfig WiFiConfig;

const int DOOR_BELL_BUTTON = 0; // Currently mapped to IO0 on ESP32 WROOM
const char SLACK_HOOK_URL[] = "https://hooks.slack.com/services/XXXXXXXXXXXXXXX";

void handleDoorbellButton() {
  HTTPClient http;
  char payload[] = "{'text':'There is someone at the door!'}";
  
  http.begin(SLACK_HOOK_URL);
  http.addHeader("Content-Type", "application/json");
  int httpRespCode = http.POST(payload);

  if (httpRespCode == 200) {
    Serial.println("Successfully triggered notification!");
  } else {
    Serial.println("An error occurred whilst triggering the notification!");
  }

  http.end();
}

void rootPage() {
  char content[] = "<a href=\"/_ac\">Configure WiFi</a>";
  server.send(200, "text/html", content);
}

void configureWiFi() {
  WiFiConfig.apid = "XS-ESP-DoorBell";
  WiFiConfig.psk = WiFi.macAddress();
  Portal.config(WiFiConfig);
  
  Serial.println("WiFi Credentials: SSID=" + WiFiConfig.apid + " ; Pass=" + WiFi.macAddress());
  
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  configureWiFi();
  
  server.on("/", rootPage);
  

  pinMode(DOOR_BELL_BUTTON, INPUT);
}

void loop() {
  Portal.handleClient();

  if (digitalRead(DOOR_BELL_BUTTON) == LOW) {
    Serial.println("Pressed button. Triggering alert...");
    handleDoorbellButton();
  }
}
