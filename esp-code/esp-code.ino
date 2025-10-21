#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>

const char ssid[] = "amir";
const char pass[] = "amir1387";

// uint8_t* jpeg_buf = nullptr;
// size_t jpeg_len = 0;





void setup() {
  Serial.begin(115200);
  while (!config()) { Serial.println("EROR config Camera"); }
  while (!biuld_wifie(ssid, pass)) { Serial.println("EROR Wifie"); }

  Serial.print("My IP Address: ");
  Serial.println(WiFi.localIP());

  // http.begin("http://192.168.4.2:5000/upload");
  // http.addHeader("Content-Type", "text/plain");

  Serial.println("Camera and Wifie is redey");
}

void loop() {
  if (Serial.available()) {
    int input = Serial.parseInt();
    if (input != 0) {
      HTTPClient http;
      http.begin("http://192.168.4.2:5000/upload");
      http.addHeader("Content-Type", "text/plain");
      int httpResponseCode = http.POST((String)input);
      Serial.println(httpResponseCode);
      http.end();
    }
  }
}


bool config() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_YUV422;  // یا RGB565 برای پردازش
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.frame_size = FRAMESIZE_SVGA;  // یا FRAMESIZE_QVGA, FRAMESIZE_UXGA
  config.jpeg_quality = 5;             // 0-63 (کم = بهتر)
  config.fb_count = 2;
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return false;
  }
  return true;
}

bool biuld_wifie(const char ssid[], const char pass[]) {
  bool result = WiFi.softAP(ssid, pass);
  if (result) {
    return true;
  } else {
    return false;
  }
}

camera_fb_t* get_pictuer(camera_fb_t* fb) {
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
  }
  return fb;
}