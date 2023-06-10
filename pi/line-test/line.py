import cv2 as cv

def get_line(frame, thresh):
    gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)

    _, mask = cv.threshold(gray, 100, 255, cv2.THRESH_BINARY_INV)

    element = cv.getStructuringElement(cv.MORPH_ELLIPSE, (5, 5), (2, 2))
    mask_dilated = cv.dilate(mask, element);
    mask_eroded = cv.dilate(mask_dilated, element);

    return mask_eroded

def get_path(line):
    
