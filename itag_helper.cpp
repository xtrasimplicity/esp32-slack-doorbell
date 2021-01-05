#include "itag_helper.h"

class AdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(iTagHelper::getServiceUUID())) {
      BLEDevice::getScan()->stop();
      iTagHelper::tag = new iTag(new BLEAdvertisedDevice(advertisedDevice), iTagHelper::getServiceUUID(), iTagHelper::getCharacteristicUUID());
      iTagHelper::shouldConnectToTag = true;
    }
  }
};

void iTagHelper::scan() {
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(10, false);
}

bool iTagHelper::tagExists() {
  // TBC
  return true;
}

bool iTagHelper::shouldConnectToTag = false;
iTag* iTagHelper::tag = nullptr;
BLEUUID iTagHelper::m_serviceUUID = BLEUUID("0000");
BLEUUID iTagHelper::m_characteristicUUID = BLEUUID("0000");