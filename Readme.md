# ESP32 Doorbell with slack integration
_A simple ESP32-based IoT doorbell with Slack integration._

## ToDO
- Ability to customise the Slack hook URL and payload from within the Web UI.
- Improve appearance and security of the Web UI.

## Caveats
- iTag support:
  - iTag BLE devices don't require any authentication/registration to be able to subscribe to `notify` events. This is problematic, as the BLE library written by the ESP32 team expects this to occur and throws an exception.

    The code in this repository, most notably the ` pRemoteCharacteristic->registerForNotify(iTagNotificationCallback, true, false);` line, relies on a yet-to-be-merged change to the `BLERemoteCharacteristic::registerForNotify` method's signature. I've submitted a [pull request](https://github.com/espressif/arduino-esp32/pull/4659) upstream, which will hopefully be merged soon.