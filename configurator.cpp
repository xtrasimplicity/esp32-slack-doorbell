#include "configurator.h"

Configurator::Configurator() {
  Serial.println("Configuring WiFi...");

  this->_portal = new AutoConnect(_webserver);
  this->configureWiFi();
  this->bindRoutes();
}

void Configurator::handleWebClients() {
  this->_portal->handleClient();
}

void Configurator::configureWiFi() {
  AutoConnectConfig WiFiConfig;

  WiFiConfig.apid = "XS-ESP-DoorBell";
  WiFiConfig.psk = WiFi.macAddress();
  this->_portal->config(WiFiConfig);

  Serial.println("WiFi Credentials: SSID=" + WiFiConfig.apid + " ; Pass=" + WiFi.macAddress());
  
  if (this->_portal->begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
}

void Configurator::renderRootPage() {
  char content[] = "<a href=\"/_ac\">Configure WiFi</a>";
  _webserver.send(200, "text/html", content);
}

void Configurator::bindRoutes() {
  _webserver.on("/", std::bind(&Configurator::renderRootPage, this));
}