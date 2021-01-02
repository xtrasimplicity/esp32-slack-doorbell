#include "doorbell.h"

boolean DoorBell::trigger() {
  HTTPClient http;
  
  http.begin(this->_slackHookURL.c_str());
  http.addHeader("Content-Type", "application/json");
  int httpRespCode = http.POST(this->_slackPayload.c_str());

  http.end();

  return httpRespCode == 200;
}