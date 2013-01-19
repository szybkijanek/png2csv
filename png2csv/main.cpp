//
//  main.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include <iostream>
#include "pngmatrix.h"
#include "patto.h"

using namespace std;

int main(int argc, const char * argv[]){
    
    /*
     1 3 15429046
     o 4 3132751872
     0 5 672785844850
     2 5 673340286496
     3 5 673347373682
     4 5 217935742150
     5 5 610709637746
     6 5 672736561778
     7 5 37795291928
     8 5 672820447858
     9 5 672786844274
     E 5 18824611360
     N 6 80465050134820
     */
    
    char *chars = (char *) "1o023456789EN";
    int widths[13] = {3,4,5,5,5,5,5,5,5,5,5,5,6};
    unsigned long long int patterns[13] = {15429046, 3132751872, 672785844850, 673340286496, 673347373682, 217935742150, 610709637746, 672736561778, 37795291928, 672820447858, 672786844274, 18824611360, 80465050134820};
    
    patto *pattern_generator = new patto;

    pattern_generator -> load_file((char *) "meteorogram.png");
    // wiersz, kolumna, szerokość, wysokość
    // 540 x 660
    int line = -1;
    for (int x = 0; x < 660 - 8; x++) {
        for (int y = 0; y < 540 - 6; y++) {
            for (int i=0; i<13; i++) {
                if (patterns[i] == pattern_generator -> pattern_for_point_and_size(x, y, widths[i], 8)) {
                    if (line != x) printf("\n%3i | ", x);
                    printf("%c", chars[i]);
                    line = x;
                    break;
                }
            }
        }
    }
    return 0;
}

