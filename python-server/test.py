import cv2
import numpy as np

img = cv2.imread('esp.jpg')
data = img[:,:,0]
print(data.max())