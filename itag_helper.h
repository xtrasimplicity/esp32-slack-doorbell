#include <BLEDevice.h>
#include "itag.h"

class iTagHelper {
  public:
    static void setSearchParameters(const std::string &TAG_UUID, const std::string &TAG_CHARACTERISTIC_UUID) {
      iTagHelper::m_serviceUUID = BLEUUID(TAG_UUID);
      iTagHelper::m_characteristicUUID = BLEUUID(TAG_CHARACTERISTIC_UUID);
    }
    static void scan();
    static bool tagExists();
    static bool shouldConnectToTag;
    static iTag* tag;
    static BLEUUID getServiceUUID() { return m_serviceUUID; }
    static BLEUUID getCharacteristicUUID() { return m_characteristicUUID; }

  private:
    static BLEUUID m_serviceUUID;
    static BLEUUID m_characteristicUUID;
};