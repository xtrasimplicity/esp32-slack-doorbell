#include "configurator.h"
#include "doorbell.h"

static Configurator* configurator;
static DoorBell* doorbell;

const std::string SLACK_HOOK_URL = "https://hooks.slack.com/services/XXXXXXXXXXXXXXXXXX";
const std::string SLACK_PAYLOAD = "{'text':'There is someone at the door!'}";
const int DOOR_BELL_BUTTON = 13;
const int DOOR_BELL_BUTTON_GND = 14;
const int DOOR_BELL_BUTTON_LED = 15;
const int DOOR_BELL_BUTTON_LED_GND = 16;

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  configurator = new Configurator();
  doorbell = new DoorBell(SLACK_HOOK_URL, SLACK_PAYLOAD);

  pinMode(DOOR_BELL_BUTTON, INPUT);
  pinMode(DOOR_BELL_BUTTON_LED, OUTPUT);
  pinMode(DOOR_BELL_BUTTON_GND, OUTPUT);
  pinMode(DOOR_BELL_BUTTON_LED_GND, OUTPUT);

  digitalWrite(DOOR_BELL_BUTTON_GND, LOW);
  digitalWrite(DOOR_BELL_BUTTON_LED_GND, LOW);
}

void loop() {
    configurator->handleWebClients();

  if (digitalRead(DOOR_BELL_BUTTON) == LOW) {
    if (doorbell->trigger()) {
      Serial.println("Successfully triggered doorbell!");
      digitalWrite(DOOR_BELL_BUTTON_LED, HIGH);
      delay(500);
      digitalWrite(DOOR_BELL_BUTTON_LED, LOW);
    } else {
      Serial.println("Unable to trigger doorbell!");
    }
  }
}
