#include "itag.h"

void iTag::notificationCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
   Serial.println("Received button press from iTag. Triggering alert.");
   iTag::onButtonClickHandler();
}

bool iTag::connect() {
  Serial.print("Preparing connection to ");
  Serial.println(this->device->getAddress().toString().c_str());

  BLEClient* pClient = BLEDevice::createClient();
  pClient->connect(this->device);
  Serial.println("Established a connection to the iTag. Preparing service...");

  BLERemoteService* pRemoteService = pClient->getService(this->serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Unable to prepare service with UUID ");
    Serial.print(this->serviceUUID.toString().c_str());
    Serial.println(". Aborting...");

    pClient->disconnect();
    return false;
  }

  pRemoteCharacteristic = pRemoteService->getCharacteristic(this->characteristicUUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.print("Unable to locate characteristic with UUID ");
    Serial.print(this->characteristicUUID.toString().c_str());
    Serial.println(". Aborting...");

    pClient->disconnect();
    return false;
  }

  if (pRemoteCharacteristic->canNotify()) {
    pRemoteCharacteristic->registerForNotify(iTag::notificationCallback, true, false);
  }

  return true;
}

void iTag::onButtonClick(void(*f)()) {
  iTag::onButtonClickHandler = f;
}

iTag::parameterless_func iTag::onButtonClickHandler = [](){};