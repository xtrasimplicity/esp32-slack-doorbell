#include <string>
#include <BLEDevice.h>
#include <Arduino.h>
#include <functional>


class iTag {
  typedef void (*parameterless_func)();

  public:
    iTag(BLEAdvertisedDevice* advertisedDevice, BLEUUID serviceUUID, BLEUUID characteristicUUID) {
      this->device = advertisedDevice;
      this->serviceUUID = serviceUUID;
      this->characteristicUUID = characteristicUUID;
    };
    bool connect();
    BLEUUID serviceUUID;
    BLEUUID characteristicUUID;
    static void notificationCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify);
    static parameterless_func onButtonClickHandler;
    void onButtonClick(void(*f)());

  private:
    BLEAdvertisedDevice* device;
    BLERemoteCharacteristic* pRemoteCharacteristic;
};