# Color-Processing-Mini-Server

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Language: C++ & Python](https://img.shields.io/badge/Language-C++%20%26%20Python-blue)](https://github.com/)

This project is designed mainly for **ESP32-CAM**, but it can be adapted for similar projects. It allows capturing images, sending them to a server, and detecting the dominant color (currently **red and green** only).

For Persian (فارسی) version, click [here](README-fa.md)

## Features

- Capture images with **ESP32-CAM** and send them to the server
- Server processes images and detects dominant color
- Expandable to detect more colors or perform other image processing
- Suitable for IoT projects and simple image processing experiments

## Requirements

- ESP32-CAM module
- run Server even on your PC

## Installation / Setup

### 1.Clone project

```bash
git clone https://github.com/Am-teamdev/Color-Processing-Mini-Server.git
```

### 2.ESP32-CAM Setup

- Open file `esp32-cam/esp32_cam_capture.ino` in Arduino IDE.  
- Set your Wi-Fi SSID, password, server IP, and port correctly in file `esp32_cam_capture.ino` .   Upload the code to the ESP32-CAM board.  
- Power on the ESP32-CAM and connect it to the configured Wi-Fi network.   
- Open the Serial Monitor, send any number, and the ESP32-CAM will capture an image and send it to the server.   
- You can view the server's response in the Serial Monitor.

### 3.SERVER Setup
before run in terminal should clone project
#### linux
```bash
cd Color-Processing-Mini-Server/server
sudo chmod +x server_linux
```
#### windows
open folder `Color-Processing-Mini-Server\server` and run `server_windows`

# point
before run server first connect to ESP32
