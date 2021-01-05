#include <string>
#include <BLEDevice.h>
#include <Arduino.h>
#include <functional>


class iTag {
  public:
    iTag(BLEAdvertisedDevice* advertisedDevice, BLEUUID serviceUUID, BLEUUID characteristicUUID) {
      this->device = advertisedDevice;
      this->serviceUUID = serviceUUID;
      this->characteristicUUID = characteristicUUID;
    };
    bool connect();
    BLEUUID serviceUUID;
    BLEUUID characteristicUUID;

  private:
    BLEAdvertisedDevice* device;
    BLERemoteCharacteristic* pRemoteCharacteristic;
};