import threading

import cv2
import numpy as np

current_img = None
lock = threading.Lock()


def detect_card_color(image_path):
    img = cv2.imread(image_path)
    if img is None:
        raise FileNotFoundError(f"Cannot open image: {image_path}")

    height, width = img.shape[:2]
    total_area = height * width

    # محاسبه 70% از مساحت تصویر
    min_required_area = total_area * 0.7

    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

    # محدوده‌های رنگی قرمز
    lower_red1 = np.array([0, 70, 50])
    upper_red1 = np.array([10, 255, 255])
    lower_red2 = np.array([170, 70, 50])
    upper_red2 = np.array([180, 255, 255])

    # محدوده رنگی سبز
    lower_green = np.array([40, 70, 50])  # گسترش محدوده سبز
    upper_green = np.array([80, 255, 255])

    # ایجاد ماسک‌ها
    mask_red = cv2.inRange(hsv, lower_red1, upper_red1) | cv2.inRange(hsv, lower_red2, upper_red2)
    mask_green = cv2.inRange(hsv, lower_green, upper_green)

    def calculate_color_percentage(mask):
        # محاسبه مجموع مساحت تمام نواحی رنگی
        total_color_pixels = cv2.countNonZero(mask)
        return (total_color_pixels / total_area) * 100

    # محاسبه درصد هر رنگ
    red_percentage = calculate_color_percentage(mask_red)
    green_percentage = calculate_color_percentage(mask_green)

    print(f"Red: {red_percentage:.2f}%")
    print(f"Green: {green_percentage:.2f}%")

    threshold = 60.0  # آستانه 70%

    if red_percentage >= threshold and red_percentage > green_percentage:
        card_color = "red"
        # پیدا کردن بزرگترین کانتور قرمز برای نمایش
        contours, _ = cv2.findContours(mask_red, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if contours:
            largest_contour = max(contours, key=cv2.contourArea)
            x, y, w, h = cv2.boundingRect(largest_contour)
            bbox = (x, y, w, h)
        else:
            bbox = (0, 0, width, height)

    elif green_percentage >= threshold and green_percentage > red_percentage:
        card_color = "green"
        # پیدا کردن بزرگترین کانتور سبز برای نمایش
        contours, _ = cv2.findContours(mask_green, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if contours:
            largest_contour = max(contours, key=cv2.contourArea)
            x, y, w, h = cv2.boundingRect(largest_contour)
            bbox = (x, y, w, h)
        else:
            bbox = (0, 0, width, height)
    else:
        card_color = "none"
        bbox = None

    return card_color, bbox, img, red_percentage, green_percentage


def process_and_show(card_color, rect, img):
    global current_img
    try:
        if (card_color is not None) and (rect is not None):
            x, y, w, h = rect
            color_bgr = (0, 0, 255) if card_color == "red" else (0, 255, 0)
            cv2.rectangle(img, (x, y), (x + w, y + h), color_bgr, 3)
            cv2.putText(img, card_color, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, color_bgr, 2)

        with lock:
            current_img = img.copy()

    except Exception as e:
        print("Error in process_and_show:", e)


def show_loop():
    global current_img
    while True:
        with lock:
            if current_img is not None:
                cv2.imshow("Detected Card", current_img)
        if cv2.waitKey(30) & 0xFF == 27:
            break
    cv2.destroyAllWindows()