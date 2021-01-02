#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>

class Configurator {
  public:
    Configurator();
    void handleWebClients();

  protected:
    WebServer _webserver;
    AutoConnect *_portal;
    void configureWiFi();
    void bindRoutes();
    void renderRootPage();
};