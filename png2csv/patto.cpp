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
    int comparator = png -> red_pixel(_y, _x);
    int value = 0;
    
    //printf("%i x %i [%i]\n", _width, _height, comparator);

    for (int x = _x; x < _x + _height; x++) {
        for (int y = _y; y < _y + _width; y++) {
            value = png -> red_pixel(y, x);
            mask += comparator != value;
            mask = mask << 1;
            comparator = value;
        }
    }

    /*
    for (int x = _x; x < _x + _height; x++) {
        for (int y = _y ; y < _y + _width; y++) {
            if (png -> red_pixel(y, x) == value) printf("#");
            else printf(" ");
        }
        printf("\n");
    }

     */
    return mask;
}

unsigned long long int patto::full_pattern(){
    return pattern_for_point_and_size(0, 0, png -> width, png -> height);    
}

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