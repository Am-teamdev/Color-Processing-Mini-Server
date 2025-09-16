# ESP32-CAM Color Detection Project

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Language: C++ & Python](https://img.shields.io/badge/Language-C++%20%26%20Python-blue)](https://github.com/)
[![GitHub issues](https://img.shields.io/github/issues/yourusername/your-repo)](https://github.com/yourusername/your-repo/issues)

این پروژه شامل دو بخش کد است و عمدتاً برای **ESP32-CAM** طراحی شده است، اما می‌تواند برای پروژه‌های مشابه دیگر نیز استفاده شود. پروژه به شما امکان می‌دهد تصاویر را بگیرید، به سرور ارسال کنید و رنگ غالب تصویر را شناسایی کنید. در حال حاضر فقط رنگ‌های **سبز و قرمز** پشتیبانی می‌شوند.

## قابلیت

- گرفتن عکس با **ESP32-CAM** و ارسال به سرور  
- پردازش تصویر در سرور و تشخیص رنگ غالب (سبز یا قرمز)  
- قابل توسعه برای تشخیص رنگ‌های بیشتر یا پردازش‌های دیگر  
- مناسب برای پروژه‌های IoT و نمونه‌های آزمایشی پردازش تصویر  

## پیش نیاز 

- ماژول **ESP32-CAM**  

## راه اندازی

1. کد ESP32-CAM را روی ماژول آپلود کنید (با استفاده از Arduino IDE یا PlatformIO)  
2. کد سرور را در محیط مورد نظر اجرا کنید (Python, Node.js یا هر زبان دیگر که استفاده کرده‌اید)  
3. مطمئن شوید که ESP32-CAM و سرور روی یک شبکه قابل دسترسی هستند  

## ساختار پروژه

ESP32-CAM-Color-Detection/
│
├── esp32-cam/
│   └── esp32_cam_capture.ino
│
├── server/
│   ├── server.py
│   ├── requirements.txt
│   ├── utils.py
│   └── bin/                   # فایل‌های اجرایی
│       ├── server-linux        # فایل اجرایی لینوکس
│       └── server-windows.exe  # فایل اجرایی ویندوز
│   
│
├── README.md
├── README-fa.md
└── LICENSE
## راه اندازی

#### ویندوز

```bash
git clone https://github.com/yourusername/Color-Processing-Mini-Server.git
cd Color-Processing-Mini-Server/server
# اجرای فایل اجرایی سرور
bin/server-windows.exe




