#! /usr/bin/env python3

import cv2, sys

if __name__ == "__main__":
    image = cv2.imread(sys.argv[1])
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    rows, cols = len(image), len(image[0])
    print(f"Dimension of Image = {cols}x{rows}")
    str_file = f"{rows}\n{cols}\n"
    for index, row in enumerate(image):
        print(f"\rCurrent Row = {index+1} ({(index+1)/rows*100:.2f}%)", end='')
        str_file += "\n".join([str(value) for value in row])
        str_file += "\n"
    with open(sys.argv[2], 'w') as file:
        file.write(str_file)
    print()