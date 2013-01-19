//
//  patto.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include "patto.h"


unsigned long long int patto::full_pattern_for_file(char * filename){
    unsigned long long int mask = 0;
    char character = filename[0];
    pngmatrix *png = new pngmatrix;
    png -> read_png_file(filename);
        
    int comparator = png -> red_pixel(0, 0), value = 0;
    for (int y = 0; y < png -> height; y++) {
        for (int x = 0; x < png -> width; x++) {
            value = png -> red_pixel(x, y);
            mask += comparator != value;
            mask = mask << 1;
            comparator = value;
        }
    }
    
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
    
    return mask;
}
