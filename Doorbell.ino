#include "configurator.h"
#include "doorbell.h"

static Configurator* configurator;
static DoorBell* doorbell;

const std::string SLACK_HOOK_URL = "https://hooks.slack.com/services/XXXXXXXXXXXXXXXXXX";
const std::string SLACK_PAYLOAD = "{'text':'There is someone at the door!'}";

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  configurator = new Configurator();
  doorbell = new DoorBell(SLACK_HOOK_URL, SLACK_PAYLOAD);

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
}
