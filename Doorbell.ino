#include <WiFi.h>
#include <HTTPClient.h>
#include <BLEDevice.h>
#include "configurator.h"
#include "doorbell.h"
#include "itag_helper.h"

static Configurator* configurator;
static DoorBell* doorbell;
static iTagHelper* tagHelper;

const std::string SLACK_HOOK_URL = "https://hooks.slack.com/services/XXXXXXXXXXXXXXXXXX";
const std::string SLACK_PAYLOAD = "{'text':'There is someone at the door!'}";
const int DOOR_BELL_BUTTON = 0; // Currently mapped to IO0 on ESP32 WROOM
const std::string ITAG_DEVICE_UUID = "0000ffe0-0000-1000-8000-00805f9b34fb";
const std::string ITAG_BUTTON_CHARACTERISTIC_UUID = "0000ffe1-0000-1000-8000-00805f9b34fb";

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  configurator = new Configurator();
  doorbell = new DoorBell(SLACK_HOOK_URL, SLACK_PAYLOAD);
  tagHelper->setSearchParameters(ITAG_DEVICE_UUID, ITAG_BUTTON_CHARACTERISTIC_UUID);
  tagHelper->scan();

  pinMode(DOOR_BELL_BUTTON, INPUT);
}

void loop() {
    configurator->handleWebClients();

  if (digitalRead(DOOR_BELL_BUTTON) == LOW) {
    if (doorbell->trigger()) {
      Serial.println("Successfully triggered doorbell!");
    } else {
      Serial.println("Unable to trigger doorbell!");
    }
  }
  
  
  if (tagHelper->tagExists() && tagHelper->shouldConnectToTag) {
    // Attempt connection to the tag
    if (tagHelper->tag->connect()) {
      Serial.println("Successfully connected to the iTag!");
    } else {
       Serial.println("Couldn't connect to iTag with UUID ");
      Serial.print(ITAG_DEVICE_UUID.c_str());
      Serial.println("");
    }

    tagHelper->shouldConnectToTag = false; // We don't want to keep trying to re-connect
  }
}
