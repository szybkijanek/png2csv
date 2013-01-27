//
//  pngmatrix.h
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#ifndef __png2csv__pngmatrix__
#define __png2csv__pngmatrix__

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <png.h>

class pngmatrix {
    int x, y;
    
    
    
    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep * row_pointers;
    
public:
    png_byte bit_depth;
    png_byte color_type;

    int width, height;
    
    void read_png_file(char* file_name);
    void process_file(void);
    int red_pixel(int _x, int _y);
    int green_pixel(int _x, int _y);
};

#endif /* defined(__png2csv__pngmatrix__) */
