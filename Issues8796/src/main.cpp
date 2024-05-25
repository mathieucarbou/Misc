#include <DNSServer.h>
#include <WiFi.h>
#include <assert.h>

DNSServer dnsServer;

void setup() {
  Serial.begin(115200);
#if ARDUINO_USB_CDC_ON_BOOT
  Serial.setTxTimeoutMs(0);
#else
  while (!Serial)
    yield();
#endif
  delay(100);

  WiFi.persistent(false);
  assert(WiFi.setSleep(false));
  assert(WiFi.mode(WIFI_AP));
  assert(WiFi.softAP("esp-captive-portal"));

  assert(dnsServer.start(53, "*", WiFi.softAPIP()));

  Serial.println("SUCCESS !");
  ESP_LOGW("main", "SUCCESS !");
}

void loop() {
  dnsServer.processNextRequest();
}
