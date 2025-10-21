// void handleCapture() {
//   Serial.println("ssss");
//   // WiFiClient client = server.client();
//   // client.println("HTTP/1.1 200 OK");
//   // client.println("Content-Type: image/jpeg");
//   if (Serial.available()) {
//     int input = Serial.parseInt();
//     if (input != 0) {


//       camera_fb_t* fb = esp_camera_fb_get();  // گرفتن فریم از دوربین
//       if (!fb) {
//         server.send(500, "text/plain", "Camera capture failed");
//         return;
//       } else if (!prepareFrame(fb, 80, &jpeg_buf, &jpeg_len)) {
//         server.send(500, "text/plain", "convert failed");
//         return;
//       }

//       // ارسال مستقیم داده‌ی JPG
//       Serial.println("start");
//       WiFiClient client = server.client();
//       client.println("HTTP/1.1 200 OK");
//       client.println("Content-Type: image/jpeg");
//       client.print("Content-Length: ");
//       client.println((int)jpeg_len);
//       client.println("Connection: close");
//       client.println();
//       client.write(jpeg_buf, jpeg_len);  // ارسال مستقیم داده‌ها
//       esp_camera_fb_return(fb);
//       client.stop();
//       free(jpeg_buf);
//       Serial.println("finish");
//     }
//   }
//   // آزاد کردن حافظه
// }
