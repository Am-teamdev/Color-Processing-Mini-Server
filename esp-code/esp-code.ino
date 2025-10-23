#include "esp_camera.h"
#include <WiFi.h>
#include <WiFiClient.h>

const char ssid[] = "amir";
const char pass[] = "amir1387";
const char server[] = "192.168.43.107";
const int port = 5000;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  while (!config()) {
    Serial.println("ERROR config Camera");
    delay(1000);
  }

  while (!connect_wifi(ssid, pass)) {
    Serial.println("ERROR WiFi");
    delay(1000);
  }

  Serial.print("My IP Address: ");
  Serial.println(WiFi.localIP());

  // تلاش برای اتصال به سرور
  if (connect_to_server()) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Failed to connect to server");
  }

  Serial.println("Camera and WiFi are ready");
}

void loop() {
  if (Serial.available()) {
    int input = Serial.parseInt();

    if (input == 2002) {
      client.stop();
      Serial.println("Client disconnected");
    } else if (input != 0) {
      // اگر اتصال قطع شده، مجدداً وصل شو
      if (!client.connected()) {
        Serial.println("Client not connected, reconnecting...");
        if (!connect_to_server()) {
          Serial.println("Reconnection failed");
          return;
        }
      }

      send_image_to_server();
    }
  }
}

bool connect_to_server() {
  Serial.println("Connecting to server...");

  if (client.connect(server, port)) {
    Serial.println("Connected to server successfully");
    return true;
  } else {
    Serial.println("Connection to server failed");
    return false;
  }
}

void send_image_to_server() {
  camera_fb_t* fb = nullptr;
  uint8_t* jpeg_buf = nullptr;
  size_t jpeg_len = 0;

  // گرفتن عکس
  fb = get_pictuer();
  if (!fb) {
    Serial.println("Failed to capture image");
    return;
  }

  // تبدیل به JPEG
  if (!frame2jpg(fb, 80, &jpeg_buf, &jpeg_len)) {
    Serial.println("ERROR Convert to JPEG");
    esp_camera_fb_return(fb);
    return;
  }

  Serial.print("Image size: ");
  Serial.println((int)jpeg_len);

  // ارسال درخواست HTTP
  client.println("POST /upload HTTP/1.1");
  client.print("Host: ");
  client.println(server);
  client.println("Content-Type: image/jpeg");
  client.print("Content-Length: ");
  client.println(jpeg_len);
  client.println("Connection: keep-alive");  // تغییر این خط
  // client.println("Keep-Alive: timeout=30, max=100");
  client.println();

  // ارسال داده تصویر
  size_t sent = client.write(jpeg_buf, jpeg_len);
  Serial.print("Sent ");
  Serial.print(sent);
  Serial.println(" bytes");


  String line;
  while (client.connected()) {
    if (client.available()) {
      line = client.readStringUntil('\n');
      Serial.println("Response: " + line);
    }
  }
  Serial.println("Responsesssssssss: " + line);

  // پاکسازی
  esp_camera_fb_return(fb);
  free(jpeg_buf);
  client.stop();
  Serial.println("Image sent successfully");
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
  config.pixel_format = PIXFORMAT_YUV422;  // تغییر به JPEG برای سادگی
  config.grab_mode = CAMERA_GRAB_LATEST;
  config.frame_size = FRAMESIZE_HQVGA;
  config.jpeg_quality = 18;
  config.fb_count = 2;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return false;
  }
  return true;
}

bool connect_wifi(const char ssid[], const char pass[]) {
  WiFi.begin(ssid, pass);
  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 20) {
    delay(500);
    Serial.print(".");
    timeout++;
  }
  return WiFi.status() == WL_CONNECTED;
}

camera_fb_t* get_pictuer() {
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
  }
  return fb;
}
