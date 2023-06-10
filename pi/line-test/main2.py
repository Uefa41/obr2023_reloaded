import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    green_lr = np.array([50, 100, 0])
    green_ur = np.array([90, 255, 255])

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    green_mask = cv2.inRange(hsv, green_lr, green_ur)

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    _, black_mask = cv2.threshold(gray, 100, 255, cv2.THRESH_BINARY_INV)

    masked = cv2.bitwise_and(frame, frame, mask=cv2.bitwise_or(green_mask, black_mask))

    cv2.imshow('Original', frame)
    cv2.imshow('Masked', masked)

    if cv2.waitKey(1) & 0xFF == ord('x'):
        break
