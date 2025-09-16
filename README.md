# ESP32-CAM Color Detection Project

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Language: C++ & Python](https://img.shields.io/badge/Language-C++%20%26%20Python-blue)](https://github.com/)
[![GitHub issues](https://img.shields.io/github/issues/yourusername/your-repo)](https://github.com/yourusername/your-repo/issues)

این پروژه شامل دو بخش کد است و عمدتاً برای **ESP32-CAM** طراحی شده است، اما می‌تواند برای پروژه‌های مشابه دیگر نیز استفاده شود. پروژه به شما امکان می‌دهد تصاویر را بگیرید، به سرور ارسال کنید و رنگ غالب تصویر را شناسایی کنید. در حال حاضر فقط رنگ‌های **سبز و قرمز** پشتیبانی می‌شوند.

## Features

- گرفتن عکس با **ESP32-CAM** و ارسال به سرور  
- پردازش تصویر در سرور و تشخیص رنگ غالب (سبز یا قرمز)  
- قابل توسعه برای تشخیص رنگ‌های بیشتر یا پردازش‌های دیگر  
- مناسب برای پروژه‌های IoT و نمونه‌های آزمایشی پردازش تصویر  

## Requirements

- ماژول **ESP32-CAM** 
## Installation

1. کد ESP32-CAM را روی ماژول آپلود کنید (با استفاده از Arduino IDE یا PlatformIO)  
2. کد سرور را در محیط مورد نظر اجرا کنید (Python, Node.js یا هر زبان دیگر که استفاده کرده‌اید)  
3. مطمئن شوید که ESP32-CAM و سرور روی یک شبکه قابل دسترسی هستند  

## Project Structure

/ESP32-CAM-Color-Detection
│
├── esp32-cam/ # کد مربوط به ماژول ESP32-CAM
│ └── main.ino
│
├── server/ # کد مربوط به سرور برای دریافت و پردازش تصاویر
│ └── server.py
│
├── LICENSE # فایل لایسنس پروژه (MIT)
└── README.md # این فایل


## Usage

_این بخش را خودتان پر کنید_

## License

این پروژه تحت **MIT License** منتشر شده است. برای جزئیات بیشتر، لطفاً فایل `LICENSE` را مشاهده کنید.
