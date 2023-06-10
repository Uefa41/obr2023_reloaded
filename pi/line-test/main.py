import line
import cv2 as cv

cap = cv.VideoCapture(0)

while True:
    _, frame = cap.read()

    line_mask = line.get_line(frame, 100)

    masked = cv.bitwise_and(frame, frame, mask=line_mask)

    cv.imshow('Masked', masked)

    if cv.waitKey(1) & 0xFF == ord('q'):
        break