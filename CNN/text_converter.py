#! /usr/bin/env python3

import cv2, numpy, sys

if __name__ == "__main__":
    with open(sys.argv[1], 'r') as file:
        str_file = [[float(value) for value in line.split(',') if value != ''] for line in file.read().split('\n') if line != '']
    str_file = numpy.array(str_file)
    str_file = numpy.absolute(str_file)
    str_file = numpy.array(str_file, dtype=numpy.uint8)
    cv2.imwrite(sys.argv[2], str_file)