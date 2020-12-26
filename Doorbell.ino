#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>
#include <HTTPClient.h>
#include <BLEDevice.h>

WebServer server;
AutoConnect Portal(server);
AutoConnectConfig WiFiConfig;

const int DOOR_BELL_BUTTON = 0; // Currently mapped to IO0 on ESP32 WROOM
const char SLACK_HOOK_URL[] = "https://hooks.slack.com/services/XXXXXXXXXXXXXXXXXX";
const char ITAG_DEVICE_UUID[] = "0000ffe0-0000-1000-8000-00805f9b34fb";
const char ITAG_BUTTON_CHARACTERISTIC_UUID[] = "0000ffe1-0000-1000-8000-00805f9b34fb";

static BLEUUID serviceUUID(ITAG_DEVICE_UUID);
static BLEUUID characteristicUUID(ITAG_BUTTON_CHARACTERISTIC_UUID);
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* iTagDevice;
bool shouldConnectToBLEDevice = false;

void handleDoorbellButton() {
  HTTPClient http;
  char payload[] = "{'text':'There is someone at the door!'}";
  
  http.begin(SLACK_HOOK_URL);
  http.addHeader("Content-Type", "application/json");
  int httpRespCode = http.POST(payload);

  if (httpRespCode == 200) {
    Serial.println("Successfully triggered notification!");
  } else {
    Serial.println("An error occurred whilst triggering the notification!");
  }

  http.end();
}

static void iTagNotificationCallback(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) {
   Serial.println("Received button press from iTag. Triggering alert.");
   handleDoorbellButton();
}

class AdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      iTagDevice = new BLEAdvertisedDevice(advertisedDevice);
      shouldConnectToBLEDevice = true;
    }
  }
};

bool connectToiTag() {
  Serial.print("Preparing connection to ");
  Serial.println(iTagDevice->getAddress().toString().c_str());

  BLEClient* pClient = BLEDevice::createClient();
  pClient->connect(iTagDevice);
  Serial.println("Established a connection to the iTag. Preparing service...");

  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    Serial.print("Unable to prepare service with UUID ");
    Serial.print(serviceUUID.toString().c_str());
    Serial.println(". Aborting...");

    pClient->disconnect();
    return false;
  }

  pRemoteCharacteristic = pRemoteService->getCharacteristic(characteristicUUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.print("Unable to locate characteristic with UUID ");
    Serial.print(characteristicUUID.toString().c_str());
    Serial.println(". Aborting...");

    pClient->disconnect();
    return false;
  }

  if (pRemoteCharacteristic->canNotify()) {
    pRemoteCharacteristic->registerForNotify(iTagNotificationCallback, true, false);
  }

  return true;
}

void rootPage() {
  char content[] = "<a href=\"/_ac\">Configure WiFi</a>";
  server.send(200, "text/html", content);
}

void configureWiFi() {
  WiFiConfig.apid = "XS-ESP-DoorBell";
  WiFiConfig.psk = WiFi.macAddress();
  Portal.config(WiFiConfig);
  
  Serial.println("WiFi Credentials: SSID=" + WiFiConfig.apid + " ; Pass=" + WiFi.macAddress());
  
  if (Portal.begin()) {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
  }
}

void configureBLE() {
  BLEDevice::init("");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(10, false);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  configureWiFi();
  configureBLE();
  
  server.on("/", rootPage);

  pinMode(DOOR_BELL_BUTTON, INPUT);
}

void loop() {
  Portal.handleClient();

  if (shouldConnectToBLEDevice) {
    // Attempt connection to the BLE device
    if (connectToiTag()) {
      Serial.println("Successfully connected to the iTag!");
    } else {
       Serial.println("Couldn't connect to iTag with UUID ");
      Serial.print(ITAG_DEVICE_UUID);
      Serial.println("");
    }

    shouldConnectToBLEDevice = false; // We don't want to keep trying to re-connect
  }

  if (digitalRead(DOOR_BELL_BUTTON) == LOW) {
    Serial.println("Pressed button. Triggering alert...");
    handleDoorbellButton();
  }
}
