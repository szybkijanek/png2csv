//
//  patto.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include "patto.h"

void patto::load_file(char * _filename){
    png = new pngmatrix;
    filename = _filename;
    png -> read_png_file(filename);
}

char patto::character(){
    return filename[0];
}

int patto::width(){
    return png -> width;
}

unsigned long long int patto::pattern_for_point_and_size(int _x, int _y, int _width, int _height){
    unsigned long long int mask = 0;
    int comparator = png -> red_pixel(_x, _y), value = 0;
    
    for (int y = _y; y < _y + _height; y++) {
        for (int x = _x; x < _x + _width; x++) {
            value = png -> red_pixel(x, y);
            mask += comparator != value;
            mask = mask << 1;
            comparator = value;
        }
    }
    return mask;
}

unsigned long long int patto::full_pattern(){
    return pattern_for_point_and_size(0, 0, png -> width, png -> height);
    

    /*
    printf("\n");
    printf("pattern: %c %i %lli\n\n", character, png -> width, mask);
    
    for (int y = 0; y < png -> height; y++) {
        for (int x = 0; x < png -> width; x++) {
            if (png -> red_pixel(x, y) == value) printf("#");
            else printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    */
    
}
