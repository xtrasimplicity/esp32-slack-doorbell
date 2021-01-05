#include "itag.h"

iTag::iTag(BLEAdvertisedDevice* advertisedDevice) {
  this->device = advertisedDevice;
}

bool iTag::connect() {
  // TBC
  return true;
}