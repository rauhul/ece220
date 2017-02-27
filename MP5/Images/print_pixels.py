#!/usr/bin/python

from PIL import Image
import sys
print sys.argv[1]
if len(sys.argv)<2:
    print "Enter filename"
    sys.exit()
i = Image.open(sys.argv[1])
pixels = i.load() # this is not a list
width, height = i.size
if isinstance(pixels[1, 1],int): 
    i=i.convert("RGBA")
    pixels = i.load() # this is not a list
    if len(sys.argv) == 4:
	cur_pixel = pixels[int(sys.argv[2]), int(sys.argv[3])]
	print "Red: "
	print cur_pixel[0]
	print "Green: "
	print cur_pixel[1]
	print "Blue: "
	print cur_pixel[2]
	sys.exit()
    print "MonoColor Image"
    for y in range(height):
        row = []
        for x in range(width):
	    cur_pixel = pixels[x, y]
	    row.append(cur_pixel[0])
	print row
    print "Done Printing"
else: 
    if len(sys.argv) == 4:
        cur_pixel = pixels[int(sys.argv[2]), int(sys.argv[3])]
	print "Red: "
	print cur_pixel[0]
	print "Green: "
	print cur_pixel[1]
	print "Blue: "
	print cur_pixel[2]
	sys.exit()
    print "Red Image"
    for y in range(height):
        cur_row_ttl = 0 
        row = []
        for x in range(width):
            cur_pixel = pixels[x, y]
	    row.append(cur_pixel[0])
	print row
    print "Done Printing Red"
    print "Green Image"
    for y in range(height):
        cur_row_ttl = 0 
        row = []
        for x in range(width):
            cur_pixel = pixels[x, y]
	    row.append(cur_pixel[1])
	print row
    print "Done Printing Green"
    print "Blue Image"
    for y in range(height):
        cur_row_ttl = 0 
        row = []
        for x in range(width):
            cur_pixel = pixels[x, y]
	    row.append(cur_pixel[2])
	print row
    print "Done Printing Blue"
