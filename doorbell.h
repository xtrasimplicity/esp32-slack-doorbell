#include <string>
#include <HTTPClient.h>

class DoorBell {
  public:
    DoorBell(const std::string &slackHookURL, const std::string &slackPayload) : _slackHookURL(slackHookURL),_slackPayload(slackPayload) {};
    bool trigger();

  protected:
    const std::string& _slackHookURL;
    const std::string& _slackPayload;
};
