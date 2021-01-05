#include <string>
#include <BLEDevice.h>
#include <Arduino.h>
#include <functional>


class iTag {
  public:
    iTag(BLEAdvertisedDevice* advertisedDevice);
    bool connect();

  private:
    BLEAdvertisedDevice* device;
};