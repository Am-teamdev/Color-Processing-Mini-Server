#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>
const char* ssid = "amir";
const char* password = "amir1387";
uint8_t* jpeg_buf = nullptr;
size_t jpeg_len = 0;
WiFiClient client;
String text = "amir";
int input;
camera_fb_t* fb = NULL;
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

// String getLineAfterEmptyLine(const String& input) {
//   int start = 0;
//   int lastEmptyIndex = -1;

//   while (start < input.length()) {
//     int end = input.indexOf('\n', start);
//     if (end == -1) end = input.length();

//     String line = input.substring(start, end);
//     line.trim();

//     if (line.length() == 0) {
//       lastEmptyIndex = end;
//     } else if (lastEmptyIndex != -1) {
//       return line;
//     }

//     start = end + 1;
//   }
//   return "";
// }


bool prepareFrame(camera_fb_t* fb_in, int quality, uint8_t** jpeg_buf, size_t* jpeg_len) {
  if (!fb_in) return false;
  if (fb_in->format == PIXFORMAT_JPEG) {
    *jpeg_buf = fb_in->buf;
    *jpeg_len = fb_in->len;
    return true;
  }
  bool success = frame2jpg(fb_in, quality, jpeg_buf, jpeg_len);
  if (!success) return false;

  return true;
}





void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_YUV422;
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.frame_size = FRAMESIZE_CIF;
  config.jpeg_quality = 18;
  config.fb_count = 2;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera init failed");
    return;
  }
  Serial.println("esp is ready.");
}

void loop() {

  // if (Serial.available() && ) {
  //   input = Serial.parseInt();
  //   if (input != 0) {
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("EROR Camera");
    return;
  } else if (!prepareFrame(fb, 80, &jpeg_buf, &jpeg_len)) {
    Serial.println("EROR convert to jpg");
    return;
  }
  if (client.connect("192.168.43.107", 5000)) {
    Serial.println("EROR convert to jpg");
    return;
  }
  // Serial.println("s");
  // client.println("POST /upload HTTP/1.1");
  // client.print("Host: ");
  // client.println(WiFi.localIP());
  // client.println("Content-Type: text/plain");
  // client.print("Content-Length: ");
  // client.println(text.length());
  // client.println("Connection: close");
  // client.println();
  // client.println(text);
  Serial.println("s");
  client.println("POST /upload HTTP/1.1");
  client.print("Host: 192.168.43.107");
  client.println("Content-Type: image/jpeg");
  client.print("Content-Length: ");
  client.println((int)jpeg_len);
  client.println("Connection: close");
  client.println("");
  client.write(jpeg_buf, (int)jpeg_len);
  client.stop();
  Serial.println("f");
  esp_camera_fb_return(fb);

  free(jpeg_buf);
}


