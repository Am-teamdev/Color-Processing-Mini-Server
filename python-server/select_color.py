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

    crop_left = int(width * 0.33)
    crop_right = int(width * 0.33)
    center_w = width - crop_left - crop_right

    center_img = img[:, crop_left:crop_left + center_w]

    hsv = cv2.cvtColor(center_img, cv2.COLOR_BGR2HSV)

    lower_red1 = np.array([0, 70, 50])
    upper_red1 = np.array([10, 255, 255])
    lower_red2 = np.array([170, 70, 50])
    upper_red2 = np.array([180, 255, 255])

    lower_green = np.array([57, 232, 228])
    upper_green = np.array([189, 255, 255])

    mask_red = cv2.inRange(hsv, lower_red1, upper_red1) | cv2.inRange(hsv, lower_red2, upper_red2)
    mask_green = cv2.inRange(hsv, lower_green, upper_green)

    def find_largest_contour(mask):
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if not contours:
            return None, 0
        largest = max(contours, key=cv2.contourArea)
        return largest, cv2.contourArea(largest)

    largest_red, area_red = find_largest_contour(mask_red)
    largest_green, area_green = find_largest_contour(mask_green)

    min_area = 5000

    if area_red > area_green and area_red > min_area:
        card_color = "red"
        largest_contour = largest_red
    elif area_green > area_red and area_green > min_area:
        card_color = "green"
        largest_contour = largest_green
    else:
        return None, None, img

    x, y, w, h = cv2.boundingRect(largest_contour)
    x_full = x + crop_left

    return card_color, (x_full, y, w, h), img


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