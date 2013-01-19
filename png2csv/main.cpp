//
//  main.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include <iostream>
#include "pngmatrix.h"

using namespace std;

int main(int argc, const char * argv[])
{    
    pngmatrix *png = new pngmatrix;
    png -> read_png_file("0.png");
    //printf("%i x %i\n", png -> width, png -> height);
    
    unsigned long long int mask = 0;
    unsigned long long int mask2 = 18824611360;
    
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
    printf("mask: %lli\n\n", mask);
    
    for (int y = 0; y < png -> height; y++) {
        for (int x = 0; x < png -> width; x++) {
            if (png -> red_pixel(x, y) == value) printf("#");
            else printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    
    printf("Egual? [%i]\n", mask == mask2);
    
    // insert code here...
    return 0;
}

